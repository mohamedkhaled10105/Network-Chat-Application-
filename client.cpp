#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
using namespace std;

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Send message
    char msg[] = "Hello from client";
    send(sock, msg, strlen(msg), 0);

    // Receive reply
    recv(sock, buffer, sizeof(buffer), 0);
    cout << "Server: " << buffer << endl;

    close(sock);
    return 0;
}