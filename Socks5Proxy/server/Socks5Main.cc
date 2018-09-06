#include "Socks5.h"
// #include "glog/logging.h"

int main(int argc, char* argv[]){
    // if(argc != 2){
    //     printf("Usage: %s [port]\n", argv[0]);
    //     exit(-1);
    // }

    // 使用glog进行日志记录
    google::InitGoogleLogging(argv[0]);
    fLS::FLAGS_log_dir = "../log";

    // Socks5Server server(atoi(argv[1]));
    Socks5Server server(8888);
    printf("Socks5 start in 8888\n");
    server.Start();

    return 0;
}
