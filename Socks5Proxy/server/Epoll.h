#ifndef __EPOLL_H__
#define __EPOLL_H__

#include "../common/common.h"
#include "glog/logging.h"

// 当前连接fd的状态
enum State{
    APPROVE,    //认证
    ESTABLISH,  //建立连接
    FORWARDING  //转发
};

// 渠道
struct Channel{
    int fd_;
    std::string buff_;

    Channel()
        :fd_(-1)
    {}
};

// 连接fd的结构体
struct Connect{
    State state_;               // 连接fd处于的状态
    Channel client_channel;     // 发送数据的一端
    Channel server_channel;     // 接收数据的一端
    int ref_;                   // 引用计数，用于关闭连接

    Connect()
        :state_(APPROVE)
         ,ref_(0)
    {}
};

class EpollServer{
public:
    EpollServer(int port)
        :port_(port)
         ,listen_fd_(-1)
         ,events_fd_(-1)
    {}

    virtual ~EpollServer(){
        if(listen_fd_ != -1){
            close(listen_fd_);
        }
    }

    void Start();

protected:
    // 端口号
    int port_;
    // 监听套接字fd
    int listen_fd_;
    // epoll_create 返回的 fd
    int events_fd_;

    // 用来保存所有的fd
    std::unordered_map<int, struct Connect*> connect_map_;

    // 以下函数内部使用
    virtual void ConnectEventHandler(int fd) = 0;
    virtual void ReadEventHandler(int fd) = 0;
    virtual void WriteEventHandler(int fd);
    // epoll事件循环
    void EpollLoop();
    // 设置fd为非阻塞状态
    void SetNonBlock(int fd);
    // epoll_ctl函数的封装，用来进行添加、删除、修改操作
    void OpCtl(int fd, int op, int how);
    // 将连接从map中移除
    void ConnectRemove(int fd);
    // 转发函数
    // void Forwarding(int connect_fd);
    void Forwarding(Channel* client_channel, Channel* server_channel, bool sendencry, bool recvdecrypt);
    // 循环发送
    void SendInLoop(int fd, const char* buf, int len);
};

#endif //__EPOLL_H__
