#ifndef SOCKET_H
#define SOCKET_H

#include <string>

namespace mux {

struct SockAddr {
    std::string hostname;
    int port;
};
typedef struct SockAddr SockAddr;

void tcp_client(const SockAddr sockaddr, const std::string message);
void tcp_server(const SockAddr sockaddr);
}  // namespace mux

#endif  // SOCKET_H
