#include "command.h"
#include "common.h"
/* Action for command 'PUT' */
int do_get(const char *src, const char *dst, int sock_fd)
{
    const char ERR_MSG[] = "Open file failed!";
    const char ACK_MSG[] = "ACK";
    const char RDY_MSG[] = "RDY";

    int fd, recv_len;
    char recv_buf[1024] = "";
    char ready_buf[5] = "";
    struct timeval timeout = {1,0};

    src = src;                  /* src is not necessary. */

    send(sock_fd, ACK_MSG, strlen(ACK_MSG), 0);
    recv(sock_fd, ready_buf, sizeof(ready_buf), 0);
    /* Client open file failed. */
    if(strcmp(ready_buf, RDY_MSG) != 0) { return 3; }

    fd = open(dst, O_WRONLY | O_CREAT, 0777);
    if(fd < 0) {
        perror("Open file failed");
        send(sock_fd, ERR_MSG, strlen(ERR_MSG), 0);
        return 1;               /* value '1' is open file failed. */
    }
    send(sock_fd, RDY_MSG, strlen(RDY_MSG), 0);

    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    while((recv_len = recv(sock_fd, recv_buf, sizeof(recv_buf), 0)) > 0) {
        write(fd, recv_buf, recv_len);
    }
    return 0;
}
/* Action for command 'GET' */
/* put file to client */
int do_put(const char *src, const char *dst, int sock_fd)
{
    const char ERR_MSG[] = "Open file failed!";
    const char ACK_MSG[] = "ACK";
    const char RDY_MSG[] = "RDY";

    int fd, recv_len;
    char send_buf[1024] = "";
    char ready_buf[5] = "";

    dst = dst;                  /* It seems that there need not for dst! */

    fd = open(src, O_RDONLY);
    if(fd < 0){
        send(sock_fd, ERR_MSG, strlen(ERR_MSG), 0); /* open failed */
        return 1;         /* return value '1' is "open file failed" */
    }

    send(sock_fd, ACK_MSG, strlen(ACK_MSG), 0);
    recv(sock_fd, ready_buf, sizeof(ready_buf), 0);
    if(strcmp(ready_buf, RDY_MSG) != 0) {
        return 2;     /* return value '2' is "ready message failed" */
    }

    while((recv_len = read(fd, send_buf, sizeof(send_buf))) > 0)  {
        send(sock_fd, send_buf, recv_len, 0);
    }
    return 0;
}
int do_cd(char *path)
{
    return 0;
}
/* Action for command 'LS' */
int do_ls(char *path, int sock_fd)
{
    const char ERR_MSG[] = "Entry dictionary failed!";
    const char ACK_MSG[] = "ACK";
    const char RDY_MSG[] = "RDY";

    int fd, recv_len;
    DIR *dirp;
    struct dirent *direntp;
    char send_buf[1024] = "";
    char ready_buf[5] = "";

    if(path == NULL) { path = "."; }
    /* 1. Check if path is a available path */
    dirp = opendir(path);
    if(dirp == NULL) {
        send(sock_fd, ERR_MSG, sizeof(ERR_MSG), 0);
        return 1;          /* value '1' is path is not a directory. */
    }

    /* 2. List the dictionary's content */
    send(sock_fd, ACK_MSG, sizeof(ACK_MSG), 0);
    recv(sock_fd, ready_buf, sizeof(ready_buf), 0);
    if(strcmp(ready_buf, RDY_MSG) != 0) {
        return 2;        /* value '2' is receive RDY message failed */
    }
    while(1) {
        direntp = readdir(dirp);
        if(direntp == NULL) { break; }
        if(direntp->d_name[0] != '.') { /* ignore hiden file */
            strcpy(send_buf, direntp->d_name);
            strcat(send_buf, "\n\0");
            send(sock_fd, send_buf, strlen(send_buf), 0);
            bzero(send_buf, sizeof(send_buf));
        }
    }

    return 0;
}
