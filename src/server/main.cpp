#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <gsl/gsl>
#include <iostream>

int main(int argc, char *argv[]) {
    const auto PORT{8080};
    const auto BUFFER_SIZE{1024};
    auto server_fd{0};
    auto new_socket{0};
    auto opt{1};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    socklen_t addrlen{sizeof(address)};

    // Bind the socket to the network address and port//
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    if (bind(server_fd, reinterpret_cast<sockaddr *>(&address),
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening..." << std::endl;

    // Accept an incoming connection
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    if ((new_socket = accept(server_fd, reinterpret_cast<sockaddr *>(&address),
                             &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    std::array<char, BUFFER_SIZE> buffer = {0};
    if (read(new_socket, buffer.data(), buffer.size()) < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    std::cout << "Received message: " << buffer.data() << std::endl;

    // CLose the socket when done
    close(server_fd);

    return 0;
}
