#include "Tranfer.h"

// 多态实现的虚函数
void TranferServer::ConnectEventHandler(int fd){	
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_GE(server_fd, 0) << "ConnectEventHandle, socket";
    CHECK_GE(connect(server_fd, (struct sockaddr*)&socks5_addr_, sizeof(socks5_addr_)), 0)
        << "ConnectEventHandle, connect";

	// 设置成非阻塞，并且添加到epoll
	SetNonBlock(fd);
	OpCtl(fd, EPOLL_CTL_ADD, EPOLLIN);

	SetNonBlock(server_fd);
	OpCtl(server_fd, EPOLL_CTL_ADD, EPOLLIN);

	Connect* con = new Connect();
	con->state_ = FORWARDING;

	con->client_channel.fd_ = fd;
	con->ref_ ++;
	connect_map_[fd] = con;

	con->server_channel.fd_ = server_fd;
	con->ref_ ++;
	connect_map_[server_fd] = con;
}

void TranferServer::ReadEventHandler(int fd){
    std::unordered_map<int, Connect*>::iterator it = connect_map_.find(fd);
	if (it != connect_map_.end()){
		Connect* con = it->second;
		Channel* ClientChannel = &con->client_channel;
		Channel* ServerChannel = &con->server_channel;
        bool sendencry = true, recvdecrypt = false;
		if (fd == con->server_channel.fd_){
            std::swap(ClientChannel, ServerChannel);
            std::swap(sendencry, recvdecrypt);
		}
		
        Forwarding(ClientChannel, ServerChannel, sendencry, recvdecrypt);
	}
	else{
        LOG(FATAL) << "ReadEventHandle fail";
	}
}
