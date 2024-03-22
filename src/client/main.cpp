#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <gsl/gsl>
#include <iostream>

int main(int argc, char *argv[]) {
    const auto PORT{8080};
    auto sock{0};
    auto hello{"Hello from client"};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in srv_addr {};
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    srv_addr.sin_port = htons(PORT);

    // Check if IP address is valid
    if (srv_addr.sin_addr.s_addr == INADDR_NONE) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    if (connect(sock, reinterpret_cast<sockaddr *>(&srv_addr),
                sizeof(srv_addr)) < 0) {
        perror("connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Send message to server
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;

    // Close the socket
    close(sock);
    return 0;
}
