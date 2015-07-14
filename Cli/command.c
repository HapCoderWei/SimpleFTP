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
        perror("Connect");
        *sock_fd = -1;
        return -1;
    }

    return 0;
}

int do_get(const char *src, const char *dst, int sock_fd){

    if(src == NULL || dst == NULL){
        return -1;
    }

    struct stat dst_path_stat;
    char filename[MAX_LENGTH];
    int dest_fd;

    int request_length = strlen(src) + 3 + 1;
    char *request_buffer = (char *)malloc(request_length);

    char recive_buffer[MAX_LENGTH];

    memset(recive_buffer, 0, MAX_LENGTH);

    strcpy(request_buffer, "GET");
    strcat(request_buffer, src);

    send(sock_fd, request_buffer, request_length, 0);
    recv(sock_fd, recive_buffer, MAX_LENGTH, 0);
    if(strcmp(recive_buffer, "ACK") == 0){
        get_dst_filename(src, dst, filename);

        dest_fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
        if(dest_fd == -1){
            perror("Open");
            return -1;
        }
        send(sock_fd, "RDY", 3, 0);
        int result;
        while((result = recv(sock_fd, recive_buffer, MAX_LENGTH, 0)) > 0){
            if(write(dest_fd, recive_buffer, result) < 0){
                return -1;
            }
            if(result < MAX_LENGTH){
                break;
            }
            memset(recive_buffer, 0, MAX_LENGTH);
        }

    }else{

    }
    close(dest_fd);

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
