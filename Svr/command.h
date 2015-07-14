#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int do_get(const char *src, const char *dst, int sock_fd);
int do_put(const char *src, const char *dst, int sock_fd);
int do_cd(char *path);
int do_ls(char *path);