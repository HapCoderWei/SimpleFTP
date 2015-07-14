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
    int ret;
    char *command_arg = NULL;
    char command_buf[MAX_LENGTH] = "";

    pthread_detach(pthread_self()); /* as pthread_join() */
    for(;;) {
        recv(client_fd, command_buf, sizeof(command_buf), 0);
        command_buf[strlen(command_buf)] = '\0';

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
            do_get(command_arg, NULL, client_fd);
        }
        else if(strncmp(command_buf, "CD", 2) == 0) {
            command_arg = command_buf + 2;
            do_cd(command_arg);
        }
        else if(strncmp(command_buf, "LS", 2) == 0) {
            command_arg = command_buf + 2;
            do_ls(command_arg);
        }
        else if(strncmp(command_buf, "BYE", 3) == 0) {
            /* BYE BYE */
            close(client_fd);
            pthread_exit(NULL);
        }
        bzero(command_buf,  sizeof(command_buf ));
    }
}