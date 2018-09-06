#include "Epoll.h"

void EpollServer::Start(){
    LOG(INFO) << "Start begin ...";

    signal(SIGPIPE, SIG_IGN);

    listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_GE(listen_fd_, 0) << "Start, socket faild";

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port_);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    CHECK_EQ(bind(listen_fd_, (struct sockaddr*)&server, sizeof(server)), 0) << "Start, bind faild";
    CHECK_EQ(listen(listen_fd_, 100000), 0) << "Start, listen faild";

    events_fd_ = epoll_create(100000);
    CHECK(events_fd_ >= 0) << "Start, call epoll_create faild";

    LOG(INFO) << "Start done , then EpollLoop begin ...";

    EpollLoop();
}

void EpollServer::EpollLoop(){
    LOG(INFO) << "EpollLoop begin ...";
    SetNonBlock(listen_fd_);
    OpCtl(listen_fd_, EPOLL_CTL_ADD, EPOLLIN);

    struct epoll_event events[100000];

    while(1){
        int num = epoll_wait(events_fd_, events, 100000, 0);
        LOG_IF(WARNING, num < 0) << "epoll_wait return < 0";
        for(int i = 0; i < num; ++ i){
            //表示有新的连接到来
            //进行accept
            if(events[i].data.fd == listen_fd_){
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                int new_fd = accept(listen_fd_,(struct sockaddr*)&client, &len);
                LOG_IF(WARNING, new_fd < 0) << "accept return < 0";
                // printf("get new connect [ip]:%s [port]:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                ConnectEventHandler(new_fd);
            }//if
            else if(events[i].events & (EPOLLIN | EPOLLPRI)){
                ReadEventHandler(events[i].data.fd);
            }
            else if(events[i].events & EPOLLOUT){
                WriteEventHandler(events[i].data.fd);
            }
            else{
                LOG(FATAL) << "can't find fd in epoll";
            }
        }//for
    }//while
}

void EpollServer::SetNonBlock(int fd){
    int sfd = fcntl(fd, F_GETFL, 0);
    LOG_IF(FATAL, sfd < 0) << "SetNonBlock, fcntl 1";

    LOG_IF(FATAL, fcntl(fd, F_SETFL, sfd | O_NONBLOCK) < 0) << "SetNonBlock, fcntl 2";
}

void EpollServer::OpCtl(int fd, int op, int how){
    struct epoll_event event;
    event.events = how;
    event.data.fd = fd;

    LOG_IF(ERROR, epoll_ctl(events_fd_, op, fd, &event) < 0) << "OpCtl";
}

void EpollServer::ConnectRemove(int fd){
    OpCtl(fd, EPOLL_CTL_DEL, 0);
    std::unordered_map<int, Connect*>::iterator it = connect_map_.find(fd);
    if(it != connect_map_.end()){
        Connect* con = it->second;
        if(-- con->ref_ == 0){
            delete con;
            connect_map_.erase(it);
        }
    }
    else{
        LOG(FATAL) << "ConnectRemove";
    }
}

void EpollServer::Forwarding(Channel* ClientChannel, Channel* ServerChannel, bool sendencry, bool recvdecrypt){
    LOG(INFO) << "Forwarding begin ...";

    char buf[4096];
    int num = recv(ClientChannel->fd_, buf, sizeof(buf), 0);
    if(num < 0){
        LOG(ERROR) << "recv faild";
    }
    else if(num == 0){
        // 关闭fd
        shutdown(ServerChannel->fd_, SHUT_WR);
        ConnectRemove(ClientChannel->fd_);
        LOG(WARNING) << "client close";
    }
    else{
        if(recvdecrypt){
            Decry(buf, num);
        }
        if(sendencry){
            Encry(buf, num);
        }
        buf[num] = '\0';
        SendInLoop(ServerChannel->fd_, buf, num);
    }
    LOG(INFO) << "Forwarding done ...";
}

void EpollServer::SendInLoop(int fd, const char* buf, int len){
    int slen = send(fd, buf, len, 0);
    if(slen < 0){
        LOG(ERROR) << "SendInLoop, send";
    }
    else if(slen < len){
        std::unordered_map<int, Connect*>::iterator it = connect_map_.find(fd);
        if(it != connect_map_.end()){
            Connect* con = it->second;
            Channel* channel = &con->client_channel;
            if(fd == con->server_channel.fd_){
                channel = &con->server_channel;
            }
            int flags = EPOLLOUT | EPOLLIN | EPOLLONESHOT;
            OpCtl(fd, EPOLL_CTL_MOD, flags);
            channel->buff_.append(buf+slen);
        }
        else{
            LOG(FATAL) << "SendInLoop, can't find in map";
        }
    }
}

void EpollServer::WriteEventHandler(int fd){
    LOG(INFO) << "WriteEventHandler begin ...";

    std::unordered_map<int, Connect*>::iterator it = connect_map_.find(fd);
    if(it == connect_map_.end()){
        LOG(FATAL) << "can not find fd in map";
    }
    Connect* con = it->second;
    Channel* channel = &(con->client_channel);

    if(fd == con->server_channel.fd_){
        channel = &con->server_channel;
    }
    std::string buff;
    buff.swap(channel->buff_);
    SendInLoop(fd, buff.c_str(), buff.size());

    LOG(INFO) << "WriteEventHandler done ...";
}
