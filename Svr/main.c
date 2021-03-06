#include "common.h"

void *th_func(void *arg);
int main(int argc, char *argv[])
{
    struct sockaddr_in s_addr, c_addr;
    int socket_fd, client_fd;
    int s_addr_len;

    pthread_t pt;
    int res;
    /* create a socket */
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    s_addr_len = sizeof(s_addr);
    bzero(&s_addr, s_addr_len);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socket_fd, (struct sockaddr *)&s_addr, s_addr_len) < 0) {
        perror("Bind error");
        exit(1);
    }
    listen(socket_fd, 10);          /* max request counts is 10 */

    for(;;) {
        client_fd = accept(socket_fd,
            (struct sockaddr *)&c_addr,
            &s_addr_len);
        if(client_fd < 0) {
            perror("Accept error");
            continue;
        }
        printf("Accept connection from %s: %d\n",
            inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));

        /* Create a thread to do the request */
        res = pthread_create(&pt, NULL, th_func, (void *)client_fd);
        if(res != 0) {
            perror("Error in create thread");
            close(client_fd);
            continue;
        }
    }
    /* close(socket_fd); */
    return 0;
}
void *th_func(void *arg)
{
    int client_fd = (int)arg;
    int ret, recv_len;
    char *command_arg = NULL;
    char command_buf[MAX_LENGTH] = "";

    pthread_detach(pthread_self()); /* as pthread_join() */
    for(;;) {
        recv_len = recv(client_fd, command_buf, sizeof(command_buf), 0);
        command_buf[recv_len] = '\0';

        if(strncmp(command_buf, "GET", 3) == 0) {
            command_arg = command_buf + 3;
            ret = do_put(command_arg, NULL, client_fd);
            switch(ret) {
                case 0: printf("GET finished.\n"); break;
                case 1: printf("GET: open file failed.\n"); break;
                case 2: printf("GET: ready message failed.\n"); break;
                default: break;
            }
        }
        else if(strncmp(command_buf, "PUT", 3) == 0) {
            command_arg = command_buf + 3;
            ret = do_get(NULL, command_arg, client_fd);
            switch(ret) {
                case 0: printf("PUT finished.\n"); break;
                case 1: printf("PUT: Open file failed.\n"); break;
                case 2: printf("PUT: Receive READY message failed.\n"); break;
                case 3: printf("Client open file failed.\n"); break;
                default: break;
            }
        }
        else if(strncmp(command_buf, "CD", 2) == 0) {
            command_arg = command_buf + 2;
            ret = do_cd(command_arg, client_fd);
            switch(ret) {
                case 0: printf("CD finished.\n");
                case 1: printf("CD: Change Directory failed.\n");
            }
        }
        else if(strncmp(command_buf, "LS", 2) == 0) {
            command_arg = command_buf + 2;
            ret = do_ls(command_arg, client_fd);
            switch(ret) {
                case 0: printf("LS finished.\n"); break;
                case 1: printf("LS: PATH is not a dictionary.\n"); break;
                case 2: printf("LS: Receive READY message failed.\n"); break;
                default: break;
            }
        }
        else if(strncmp(command_buf, "BYE", 3) == 0) {
            /* BYE BYE */
            send(client_fd, "OK", 2, 0);
            close(client_fd);
            printf("Connection disconnect.\n");
            pthread_exit(NULL);
        }
        bzero(command_buf,  sizeof(command_buf));
    }
}