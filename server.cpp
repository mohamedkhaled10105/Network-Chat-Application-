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
    char buffer[1024];

    // Create socket (TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Setup server address
    addr.sin_family = AF_INET;            
    addr.sin_port = htons(PORT);          
    addr.sin_addr.s_addr = INADDR_ANY;    

    // Bind socket to port
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));

    // Start listening for clients
    listen(server_fd, 3);
    cout << "Server waiting...\n";

    // Accept a client connection
    client_socket = accept(server_fd, NULL, NULL);
    cout << "Client connected!\n";

    // Chat loop (continuous communication)
    while (true) {
        memset(buffer, 0, sizeof(buffer));   

        // Receive message from client
        int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;               

        cout << "Client: " << buffer << endl;

        // Send reply to client
        cout << "You: ";
        cin.getline(buffer, sizeof(buffer));
        send(client_socket, buffer, strlen(buffer), 0);
    }

    // Close sockets
    close(client_socket);
    close(server_fd);

    return 0;
}