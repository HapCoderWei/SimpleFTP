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

    char filename[MAX_LENGTH];
    int dest_fd;

    int request_length;
    char *request_buffer;

    char recive_buffer[MAX_LENGTH];
    int recive_length;
    struct timeval timeout = {1,0};

    request_length = strlen(src) + 3 + 1;
    request_buffer = (char *)malloc(request_length);
    strcpy(request_buffer, "GET");//Create request_buffer
    strcat(request_buffer, src);
    send(sock_fd, request_buffer, request_length, 0); //Send GET + Path, then free request_buffer
    free(request_buffer);

    memset(recive_buffer, 0, MAX_LENGTH);
    recv(sock_fd, recive_buffer, MAX_LENGTH, 0);

    if(strcmp(recive_buffer, "ACK") == 0){
        memset(recive_buffer, 0, MAX_LENGTH);
        get_dst_filename(src, dst, filename);

        dest_fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
        if(dest_fd == -1){
            perror("Open");
            return -1;
        }
        setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        send(sock_fd, "RDY", 3, 0);


        while((recive_length = recv(sock_fd, recive_buffer, MAX_LENGTH, 0)) > 0){
            if(write(dest_fd, recive_buffer, recive_length) < 0){
                return -1;
            }
            memset(recive_buffer, 0, MAX_LENGTH);
        }

        close(dest_fd);
    }else{
        printf("No such file on server\n");
    }

    return 0;
}

int do_put(const char *src, const char *dst, int sock_fd){
    int request_length;
    char *request_buffer;

    char send_buffer[MAX_LENGTH];
    char recive_buffer[MAX_LENGTH];

    int file_to_put_fd = -1;
    int send_length;

    request_length = strlen(dst) + 3 + 1;
    request_buffer = (char *)malloc(request_length);
    strcpy(request_buffer, "PUT");//Create request_buffer
    strcat(request_buffer, dst);
    send(sock_fd, request_buffer, request_length, 0); //Send GET + Path, then free request_buffer
    free(request_buffer);

    memset(recive_buffer, 0, MAX_LENGTH);
    memset(send_buffer, 0, MAX_LENGTH);
    recv(sock_fd, recive_buffer, MAX_LENGTH, 0);

    if(strcmp(recive_buffer, "ACK") == 0){
        file_to_put_fd = open(src, O_RDONLY);
        if(file_to_put_fd < 0){
            perror("Open");
            send(sock_fd, "ERR", 5, 0);
            return -1;
        }

        send(sock_fd, "RDY", 3, 0);

        memset(recive_buffer, 0, MAX_LENGTH);
        recv(sock_fd, recive_buffer, MAX_LENGTH, 0);

        if(strcmp(recive_buffer, "RDY") == 0){
            while((send_length = read(file_to_put_fd, send_buffer, sizeof(recive_buffer))) > 0){
                send(sock_fd, send_buffer, send_length, 0);
            }
        }else{
            printf("Create file failure on server\n");
        }

    }else{
        printf("Send message failure\n");
    }

    close(file_to_put_fd);
    return 0;
}

int do_cd(char *path){
    return 0;
}

int do_ls(char *path){
    DIR *dir;
    struct dirent *ptr;

    if(path == NULL){
        char path_tmp[2] = ".";
        path = (char *)malloc(2);
        strcpy(path, path_tmp);
    }

    if(is_dir(path)){
        dir = opendir(path);
        while((ptr = readdir(dir)) != NULL){
            printf("%s\n", ptr->d_name);
        }
        closedir(dir);
    }else{
        printf("No such directory.\n");
        return -1;
    }


    return 0;
}

void do_show(){
    char current_dir[MAX_LENGTH];
    getcwd(current_dir, MAX_LENGTH);
    printf("%s \n", current_dir);
}

int do_serv_cd(char *path, int sock_fd){

    return 0;
}

int do_serv_ls(char *path, int sock_fd){

    return 0;
}

int bye(int sock_fd){
    send(sock_fd, "BYE", 3, 0);
    close(sock_fd);
    return 0;
}

int quit(){
    exit(1);
    return 0;
}
