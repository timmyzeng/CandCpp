#include "Tranfer.h"

int main(int argc, char* argv[]){
    // if(argc != 4){
    //     printf("Usage: %s [tranfer port] [socks5 ip] [socks5 port]\n", argv[0]);
    //     exit(-1);
    // }

    // 使用glog进行日志记录
    google::InitGoogleLogging(argv[0]);
    fLS::FLAGS_log_dir = "../log";

    // TranferServer tranfer_server(atoi(argv[1]), argv[2], atoi(argv[3]));
    TranferServer tranfer_server(8889, "159.65.106.211", 8888);
    // TranferServer tranfer_server(8889, "47.94.223.85", 8888);
    printf("tranfer start in 8889\n");
    tranfer_server.Start();
}
