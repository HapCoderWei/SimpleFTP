#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <pthread.h>

#include "command.h"

#define SIZE 1024