#include <common.h>

void cp_file(const char *src, const char *dst, mode_t mode);
void cp_dir(const char *src , const char *dst);

int main( int argc, char *argv[] )
{
        if ( argc != 3 ) {
                fprintf(stderr, "usage: %s src dst\n", argv[0]);
                exit(1);
        }

        struct stat sbuf;
        if ( stat(argv[1], &sbuf) == -1 ) ERR_EXIT("stat src");
        if ( S_ISREG(sbuf.st_mode) ) {// 原是文件
                struct stat dbuf;
                if ( stat(argv[2], &dbuf) == -1 ) { // 目标不存在
                        cp_file(argv[1], argv[2], sbuf.st_mode);
                } else if ( S_ISDIR(dbuf.st_mode) ) { // 目标是目录
                        char tmp[1024] = {};
                        sprintf(tmp, "%s/%s", argv[2], argv[1]);
                        cp_file(argv[1], tmp, sbuf.st_mode);
                } else if ( S_ISREG(dbuf.st_mode) ) { // 目标是已经存在的文件
                        printf("是否覆盖%s文件? ", argv[2]);
                        char ask = 'n';
                        scanf(" %c", &ask);
                        if ( ask=='y' || ask=='Y' ) {
                                truncate(argv[2], 0); // 清空目标文件
                                cp_file(argv[1], argv[2], sbuf.st_mode);
                        }
                }
        }else if (S_ISDIR(sbuf.st_mode) ) { // 原文件是目录
                struct stat dbuf;
                if ( stat(argv[2], &dbuf) == -1 ) { // 目标目录不存在
                        mkdir(argv[2], sbuf.st_mode); // 创建目标目录
                        cp_dir(argv[1], argv[2]);
                } else if ( S_ISDIR(dbuf.st_mode) ) { // 目标是目录，作为子目录
                        char tmp[1024] = {};
                        sprintf(tmp, "%s/%s", argv[2], argv[1]);
                        mkdir(tmp, sbuf.st_mode);
                } else { // 非法
                        printf("瞎搞,目录不能拷贝到文件中\n");
                        exit(0);
                }
        } 
}

void cp_file(const char *src, const char *dst, mode_t mode)
{
        int fd_src = open(src, O_RDONLY);
        if (fd_src == -1 ) ERR_EXIT("open src");
        int fd_dst = open(dst, O_WRONLY|O_CREAT, mode);
        if (fd_dst == -1 ) ERR_EXIT("open dst");

        char buf[1024];
        memset(buf, 0x00, sizeof(buf));

        int r;
        while ( (r=read(fd_src, buf, 1024)) > 0 )  {
                write(fd_dst, buf, r);
                memset(buf, 0x00, sizeof(buf));
        }

        close(fd_src);
        close(fd_dst);
}

void cp_dir(const char *src , const char *dst)
{
        DIR *pdir = opendir(src);
        if ( pdir == NULL ) ERR_EXIT("opendir");

        struct dirent *pd = NULL;

        while ( (pd=readdir(pd)) != NULL ) {
                if ( strcmp(pd->d_name,".")==0 || strcmp(pd->d_name, "..")==0)
                        continue;
                struct stat sbuf;
                stat(pd->d_name, &sbuf);
        }
}
