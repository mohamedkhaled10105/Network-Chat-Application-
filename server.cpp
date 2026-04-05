#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
using namespace std;

int main() {
    int server_fd;
    struct sockaddr_in addr;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Setup address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind and listen
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 3);

    cout << "Server waiting on port 8080...\n";

    // Accept client
    int client_socket = accept(server_fd, NULL, NULL);
    cout << "Client connected!\n";

    close(client_socket);
    close(server_fd);

    return 0;
}