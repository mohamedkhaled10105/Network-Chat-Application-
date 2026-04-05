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
    char buffer[1024];

    // Create socket (TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Setup server address
    serv_addr.sin_family = AF_INET;        
    serv_addr.sin_port = htons(PORT);      
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); 

    // 3. Connect to server
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    cout << "Connected to server!\n";

    // Chat loop
    while (true) {
        // Send message
        cout << "You: ";
        cin.getline(buffer, sizeof(buffer));
        send(sock, buffer, strlen(buffer), 0);

        // Receive reply
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;             

        cout << "Server: " << buffer << endl;
    }

    // Close socket
    close(sock);

    return 0;
}