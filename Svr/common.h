#if 0
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#endif
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "command.h"

#define SIZE         1024
#define MAX_LINE     1024
#define PORT         8000
#define COMMAND_LINE 256
#define MAX_LENGTH   64
