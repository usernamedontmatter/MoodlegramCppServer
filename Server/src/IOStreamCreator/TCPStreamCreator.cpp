#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../include/IOStreamCreator/TCPStreamCreator.hpp"

namespace IOStream {
    TCPStreamCreator::TCPStreamCreator(const std::string& address, const int port) : address(address), port(port) {
        socket_fd = socket(AF_INET , SOCK_STREAM, 0);
        if(socket_fd == 0) throw TCPStreamError::SocketCreationError();

        sockaddr_in socket_address{};
        socket_address.sin_family = AF_INET;
        socket_address.sin_addr.s_addr = inet_addr(address.data());
        socket_address.sin_port = htons(port);

        size_t socket_address_len = sizeof(socket_address);
        if (bind(socket_fd, reinterpret_cast<sockaddr*>(&socket_address), socket_address_len) < 0) throw TCPStreamError::BindingError();
        if (listen(socket_fd, 3) < 0) throw TCPStreamError::ListeningError();
    }
    TCPStreamCreator::~TCPStreamCreator() {
        close(socket_fd);
    }
}