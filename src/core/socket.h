#ifndef SOCKET_H
#define SOCKET_H

#include <string>

namespace mux {
void tcp_client(const std::string hostname, const std::string port,
                const std::string message);
void tcp_server(const std::string port);
}  // namespace mux

#endif  // SOCKET_H
