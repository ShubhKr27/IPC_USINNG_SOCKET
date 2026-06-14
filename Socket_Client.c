#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT    8080
#define SERVER  "127.0.0.1"
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buf[BUFSIZE];

    /* 1. Create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    /* 2. Fill server address struct */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(PORT);

    if (inet_pton(AF_INET, SERVER, &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "invalid address\n");
        exit(EXIT_FAILURE);
    }

    /* 3. Connect (triggers TCP 3-way handshake) */
    if (connect(sockfd,
                (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect"); exit(EXIT_FAILURE);
    }
    printf("[client] connected to %s:%d\n", SERVER, PORT);

    /* 4. Interactive send/recv loop */
    while (1) {
        printf("msg> ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;

        /* Strip newline, send to server */
        size_t len = strlen(buf);
        if (buf[len - 1] == '\n') buf[--len] = '\0';
        if (strcmp(buf, "quit") == 0) break;

        write(sockfd, buf, len);

        /* Read server echo */
        ssize_t n = read(sockfd, buf, sizeof(buf) - 1);
        if (n <= 0) { puts("[client] server closed"); break; }
        buf[n] = '\0';
        printf("[client] recv: %s\n", buf);
    }

    printf("[client] closing\n");
    close(sockfd);
    return 0;
}

// gcc -Wall -o client Socket_Client.c

// # Terminal 2 (click + in terminal panel) — then run client
// ./client