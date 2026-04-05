#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
using namespace std;

int main() {
    int server_fd, client_socket;
    struct sockaddr_in addr;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 3);

    cout << "Server waiting...\n";

    client_socket = accept(server_fd, NULL, NULL);

    // Receive message
    recv(client_socket, buffer, sizeof(buffer), 0);
    cout << "Client: " << buffer << endl;

    // Send reply
    char reply[] = "Hello from server";
    send(client_socket, reply, strlen(reply), 0);

    close(client_socket);
    close(server_fd);

    return 0;
}