#ifndef __COMMON_H__
#define __COMMON_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <iostream>
#include <unordered_map>

#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/epoll.h>

#include "glog/logging.h"

static inline void XOR(char* buf, int len){
	for (int i = 0; i < len; ++i){
		buf[i] ^= 1;
	}
}

static inline void Decry(char* buf, int len){
	XOR(buf, len);
}

static inline void Encry(char* buf, int len){
	XOR(buf, len);
}

#endif //__COMMON_H__
