#include "command.h"
#include "common.h"

int do_connect(char *ip, int *sock_fd){
    if(ip == NULL || sock_fd == NULL){
        return -1;
    }

    struct sockaddr_in addr;
    int len;
    int result;

    len = sizeof(addr);
    bzero(&addr, len);

    *sock_fd = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    result = connect(*sock_fd, (struct sockaddr *)&addr, len);

    if(result == -1){
        perror("connect: ");
        *sock_fd = -1;
        return -1;
    }

    return 0;
}

int do_get(const char *src, const char *dst, int sock_fd){

    return 0;
}

int do_put(const char *src, const char *dst, int sock_fd){

    return 0;
}

int do_cd(char *path){

    return 0;
}

int do_ls(char *path){

    return 0;
}

int do_serv_cd(char *path, int sock_fd){

    return 0;
}

int do_serv_ls(char *path, int sock_fd){

    return 0;
}

int bye(int sock_fd){

    exit(1);
    return 0;
}
