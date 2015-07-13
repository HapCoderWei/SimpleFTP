#include "command.h"
/* Action for command 'PUT' */
int do_get(const char *src, const char *dst, int sock_fd)
{
}
/* Action for command 'GET' */
int do_put(const char *src, const char *dst, int sock_fd)
{
    FILE * fd;
    char err[] = "Open file failed!";
    char send_buf[1024] = "";
    dst = dst;                  /* It seems that there need not for dst! */
    fd = fopen(src, "r");
    if(fd == NULL) {
        send(sock_fd, err, strlen(err), 0); /* open failed */
        return 1;         /* return value '1' is "open file failed" */
    }
    while(fread(send_buf, sizeof(send_buf[0]), sizeof(send_buf), fd) > 0)  {
        send(sock_fd, send_buf, strlen(send_buf), 0);
    }
    return 0;
}
int do_cd(char *path)
{
}
int do_ls(char *path)
{
}