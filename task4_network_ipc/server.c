#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd < 0) {
        printf("Socket creation failed.\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 1);

    printf("Server is waiting for connection...\n");

    client_fd = accept(server_fd, NULL, NULL);

    read(client_fd, buffer, sizeof(buffer));

    printf("Message from client: %s\n", buffer);

    char reply[] = "Hello from server";
    send(client_fd, reply, strlen(reply), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
