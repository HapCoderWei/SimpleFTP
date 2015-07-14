#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>

int do_connect(char *ip, int *sock_fd);
int do_get(const char *src, const char *dst, int sock_fd);
int do_put(const char *src, const char *dst, int sock_fd);
int do_cd(char *path);
int do_ls(char *path);
int do_serv_cd(char *path, int sock_fd);
int do_serv_ls(char *path, int sock_fd);
int bye(int sock_fd);
int quit();
