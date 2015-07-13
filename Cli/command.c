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
        return -1;
    }

    return 0;
}
