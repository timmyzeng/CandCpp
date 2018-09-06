#include "Socks5.h"
// 异步调用

// 连接fd到来，进行插入到map中，已经添加到epoll中
// 此时的con只有client一边被写入
void Socks5Server::ConnectEventHandler(int fd){
    LOG(INFO) << "ConnectEventHandler begin ...";
    // 加入到epoll中
    SetNonBlock(fd);
    OpCtl(fd, EPOLL_CTL_ADD, EPOLLIN);

    Connect* con = new Connect();
    CHECK_NOTNULL(con);

    con->client_channel.fd_ = fd;
    con->state_ = APPROVE;
    
    // 加入到map中
    connect_map_[fd] = con;
    con->ref_ ++;
    LOG(INFO) << "ConnectEventHandler done ...";
}

void Socks5Server::ReadEventHandler(int fd){
    LOG(INFO) << "ReadEventHandler begin...";
    std::unordered_map<int, Connect*>::iterator it = connect_map_.find(fd);
    if(it != connect_map_.end()){
        Connect* con = it->second;
        // 认证
        // 建立了client_channel通道
        if(con->state_ == APPROVE){
            char ans[2];
            ans[0] = 0x05;

            int num = Approve(fd);
            // 成功
            if(num == 1){
                ans[1] = 0x00;
                con->state_ = ESTABLISH;
            }
            // 数据没有抵达
            else if(num == 0){
                return;
            }
            // 失败
            else if(num == -1){
                ans[1] = 0xFF;
                ConnectRemove(fd);
                LOG(ERROR) << "Approve faild";
            }
            Encry(ans, 2);
            LOG_IF(ERROR, send(fd, ans, sizeof(ans), 0) != 2);
        }
        // 建立连接
        // 建立server_channel通道
        else if(con->state_ == ESTABLISH){
            char reply[10] = {0};
            reply[0] = 0x05;
            int server_fd = Establish(fd);
            // 对端关闭
            if(server_fd == -2){
                LOG(WARNING) << "server close";
                return;
            }
            // 失败
            else if(server_fd == -1){
                reply[1] = 0x01;
                ConnectRemove(fd);
                LOG(ERROR) << "Establish faild";
            }
            else{
                reply[1] = 0x00;
                reply[3] = 0x01;
            }

            Encry(reply, 10);
            if(send(fd, reply, 10, 0) != 10){
                LOG(FATAL) << "send faild";
            }

            if(server_fd >= 0){
                SetNonBlock(server_fd);
                OpCtl(server_fd, EPOLL_CTL_ADD, EPOLLIN);

                connect_map_[server_fd] = con;

                con->server_channel.fd_ = server_fd;
                con->ref_ ++;
                con->state_ = FORWARDING;
            }
        }
        // 转发
        else if(con->state_ == FORWARDING){
            // 此时将client_channel和server_channel规定不考虑是服务器还是浏览器
            Channel* ClientChannel = &con->client_channel;
            Channel* ServerChannel = &con->server_channel;
            bool sendencry = false, recvdecrypt = true;

            if(fd == ServerChannel->fd_){
                std::swap(ClientChannel, ServerChannel);
                std::swap(sendencry, recvdecrypt);
            }
            Forwarding(ClientChannel, ServerChannel, sendencry, recvdecrypt);
        }
        // 失败
        else{
            // 关闭fd
            // ConnectRemove();
            LOG(FATAL) << "state wrong";
        }
    } //if
    else{
        LOG(FATAL) << "not find in map";
    }
    LOG(INFO) << "ReadEventHandler done ...";
}


// -1 表示失败
// 0  表示数据没有抵达
// 1  表示成功
int Socks5Server::Approve(int connect_fd){
    LOG(INFO) << "Approve begin...";
    // 获取头部字段，判断是否使用socks5协议，并将所有的字段获取完全
    char buf[260] = {0};

    // 因为不知道具体的认证字段长度，所以先使用MSG_PEEK窥探
    int num = recv(connect_fd, buf, sizeof(buf), MSG_PEEK);
    if(num <= 0){
        LOG(WARNING) << "recv < 3";
        return -1;
    }
    else if(num < 3){
        return 0;
    }
    // 此时将所有的字段进行获取
    int total = recv(connect_fd, buf, num, 0);
    if(total < 0){
        LOG(WARNING) << "recv faild";
        return -1;
    }
    else if(total == 0){
        return 0;
    }

    Decry(buf, total);

    // 判断第一个字节是否是0x05，是的话就是socks5协议
    // 如果不是socks5协议，回一个0xff的包，同时将连接关闭
    if(buf[0] != 0x05){
        LOG(WARNING) << "not socks5";
        return -1;
    }
    LOG(INFO) << "Approve done ...";
    return 1;
}

// 从浏览器中判断协议中的数据，获取到真实想要连接的地址
// 和端口号，然后创建socks5服务器到真实地址的连接
// 返回-2表示对端已经关闭， 返回-1表示出错，返回>= 0的数据，
// 表示返回的文件描述符
int Socks5Server::Establish(int connect_fd){
    LOG(INFO) << "Establish begin ...";
    // 用于保存recv获取的数据, 域名等情况
    char buf[260];

    int num = recv(connect_fd, buf, sizeof(buf), MSG_PEEK);
    // 读取到的数据是错误的
    if(num <= 0){
        LOG(ERROR) << "recv faild";
        return -1;
    }
    // 表示对端已经关闭
    else if(num < 10){
        LOG(WARNING) << "client close";
        return -2;
    }
    // 用于保存ipv4 地址
    char ip4[4];
    // 用于保存端口号
    char port[2];
    // 此时将前四个字段进行获取
    // 因为这四个字段是固定的，然后后面的ip地址是可变的
    num = recv(connect_fd, buf, 4, 0);
    if(num == 0){
        LOG(WARNING) << "client close";
        return -2;
    }
    else if(num != 4){
        LOG(ERROR) << "recv faild";
        return -1;
    }
    Decry(buf, num);

    if(buf[0] != 0x05 || buf[2] != 0x00){
        LOG(ERROR) << "socks5 wrong";
        return -1;
    }
    else{
        // ipv 4
        if(buf[3] == 0x01){
            num = recv(connect_fd, ip4, sizeof(ip4), 0);
            // 表示对端已经关闭
            if(num == 0){
                LOG(WARNING) << "client close";
                return -2;
            }
            else if(num != 4){
                LOG(ERROR) << "recv faild";
                return -1;
            }
            Decry(ip4, num);
            // 获取到了ip地址，获取port
            num = recv(connect_fd, port, 2, 0);
            if(num == 0){
                LOG(WARNING) << "client close";
                return -2;
            }
            else if(num != 2){
                LOG(ERROR) << "recv faild";
                return -1;
            }
            Decry(port, num);
        }
        // dominname
        // 下一个字段是变长，但是第一个字节是域名的长度，
        // 接下的字节是域名
        // 从域名中获取到ip地址
        else if(buf[3] == 0x03){
            // 用于保存域名长度
            char len = 0;
            // 获取域名长度
            num = recv(connect_fd, &len, 1, 0);
            Decry(&len, num);
            if(num == 0){
                LOG(WARNING) << "client close";
                return -2;
            }
            else if(num != 1){
                LOG(ERROR) << "recv faild";
                return -1;
            }
            // 获取域名
            num = recv(connect_fd, buf, len, 0);
            if(num == 0){
                LOG(WARNING) << "client close";
                return -2;
            }
            if(num != len){
                LOG(ERROR) << "recv faild";
                return -1;
            }
            Decry(buf, num);
            buf[num] = '\0';

            // 获取到了ip地址，获取port
            num = recv(connect_fd, port, 2, 0);
            if(num == 0){
                LOG(WARNING) << "client close";
                return -2;
            }
            else if(num != 2){
                LOG(ERROR) << "recv faild";
                return -1;
            }
            Decry(port, num);

            struct hostent* host = gethostbyname(buf);
            // 域名对应的地址和长度
            memcpy(ip4, host->h_addr, host->h_length);
        }
        // ipv 6
        // 此处我们不支持IPv 6
        else if(buf[3] == 0x04){
            LOG(WARNING) << "ipv 6";
            return -1;
        }
        else{
            LOG(FATAL) << "address type wrong";
        }
    } // else
    

    // 进行对真实访问地址的创建连接
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0){
        LOG(WARNING) << "socket faild";
        return -1;
    }

    // printf("ip: %s port: %s\n", ip4, port);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    memcpy(&server.sin_addr.s_addr, ip4, 4);
    server.sin_port = *((uint16_t*)port);
    // server.sin_addr.s_addr = htonl(atoi(ip4));
    // server.sin_port = htons(atoi(port));

    // 对请求的服务进行连接
    if(connect(server_fd, (struct sockaddr*)&server, sizeof(server))){
        LOG(ERROR) << "connect faild";
        close(server_fd);
        return -1;
    }

    LOG(INFO) << "Establish done ...";
    return server_fd;
}
