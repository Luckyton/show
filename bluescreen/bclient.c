#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFF_SIZE  1024
#define DEFAULT_PORT 12345

struct sockaddr_in target_addr;
char message[BUFF_SIZE];

static void printHelp()
{
    printf("\nUsage : bclient -ip 目的IP地址 -port 目的端口号 -m 内容\n\n");
}

static void nextAddr(const char * addr)
{
    if(addr == NULL) 
        perror("IP address can not be NULL");

    // printf("ip : %s\n", addr);

    target_addr.sin_addr.s_addr = inet_addr(addr);
}

static void nextPort(const char * port)
{
    // printf("port : %s\n", port);

    target_addr.sin_port = htons(atoi(port));
}

static void nextMsg(const char * msg)
{
    if(msg == NULL) {
        perror("Message can not be NULL");
    } else if(strlen(msg) > BUFF_SIZE) {
        perror("The message is too long");
    } else {
        strncpy(message, msg, strlen(msg));
    }
}

static int parse(char **argv)
{
    char ** p_argv;

    memset(&target_addr, 0, sizeof(struct sockaddr_in));

    p_argv = argv;
    while(*p_argv)
    {
        if(strcmp(*p_argv, "-ip") == 0) {
            nextAddr(*(++p_argv));
        } else if(strcmp(*p_argv, "-port") == 0) {
            nextPort(*(++p_argv));
        } else if(strcmp(*p_argv, "-m") == 0) {
            nextMsg(*(++p_argv));
        } else {
            return -1;
        }
        ++p_argv;
    }
    return 0;
}

static void work()
{
    int sockfd;

    target_addr.sin_family = AF_INET;
    if(target_addr.sin_port == 0) {
        target_addr.sin_port = htonl(12345);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr_in)) == -1) {
        perror("Server is closed");
    }
    
    while (send(sockfd, message, strlen(message), 0) <= 0);

    close(sockfd);
}

int main(int argc, char *argv[])
{
    if(parse(argv + 1) < 0) {
        perror("format error");
        printHelp();
    } else {
        work();
    }

    return 0;
}
