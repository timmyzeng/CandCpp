#ifndef __SOCKS5_H__
#define __SOCKS5_H__

#include "Epoll.h"

class Socks5Server : public EpollServer{
public:
    Socks5Server(int port)
        :EpollServer(port)
    {}

    virtual void ConnectEventHandler(int fd);
    virtual void ReadEventHandler(int fd);

protected:
    // 以下函数内部使用
    int Approve(int connect_fd);
    int Establish(int connect_fd);
};

#endif //__SOCKS5_H__
