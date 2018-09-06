#ifndef __TRANFER_H__
#define __TRANFER_H__

#include "Epoll.h"

class TranferServer : public EpollServer
{
public:
	TranferServer(int selfport, const char* socks5ip, int socks5port)
		:EpollServer(selfport){
		memset(&socks5_addr_, 0, sizeof(struct sockaddr_in));
		socks5_addr_.sin_family = AF_INET;
		socks5_addr_.sin_port = htons(socks5port);
		socks5_addr_.sin_addr.s_addr = inet_addr(socks5ip);
	}

	// 多态实现的虚函数
    virtual void ConnectEventHandler(int fd);
    virtual void ReadEventHandler(int fd);

protected:
	struct sockaddr_in socks5_addr_;
};

#endif //__TRANFER_H__
