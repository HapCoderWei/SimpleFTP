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

    fd = open(dst, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fd < 0) {
        perror("Open file failed");
        send(sock_fd, ERR_MSG, strlen(ERR_MSG), 0);
        return 1;               /* value '1' is open file failed. */
    }

    send(sock_fd, ACK_MSG, strlen(ACK_MSG), 0);
    recv(sock_fd, ready_buf, sizeof(ready_buf), 0);
    /* value '2' is receive ready message message failed. */
    if(strcmp(ready_buf, RDY_MSG) != 0) { return 2; }

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
int do_ls(char *path)
{
    return 0;
}
