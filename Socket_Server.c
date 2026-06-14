#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT    8080
#define BACKLOG 5
#define BUFSIZE 1024

int main(void) {
    int server_fd, conn_fd;
    struct sockaddr_in addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    char buf[BUFSIZE];

    /* 1. Create socket file descriptor */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    /* 2. Allow address reuse (avoid EADDRINUSE on restart) */
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /* 3. Bind to port */
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(EXIT_FAILURE);
    }

    /* 4. Listen — kernel now queues incoming connections */
    listen(server_fd, BACKLOG);
    printf("[server] listening on port %d\n", PORT);

    /* 5. Accept loop — handle one client at a time */
    while (1) {
        conn_fd = accept(server_fd,
                         (struct sockaddr *)&client_addr,
                         &addrlen);
        if (conn_fd < 0) { perror("accept"); continue; }

        printf("[server] connected: %s\n",
               inet_ntoa(client_addr.sin_addr));

        /* 6. Read-write loop within connection */
        ssize_t n;
        while ((n = read(conn_fd, buf, sizeof(buf) - 1)) > 0) {
            buf[n] = '\0';
            printf("[server] recv: %s", buf);

            char reply[BUFSIZE + 32];
            int rlen = snprintf(reply, sizeof(reply),
                                 "[echo] %s", buf);
            write(conn_fd, reply, rlen);
        }

        printf("[server] client disconnected\n");
        close(conn_fd);
    }

    close(server_fd);
    return 0;
}

// gcc -Wall -o server Socket_Server.c

// # Terminal 1 — run server first
// ./server