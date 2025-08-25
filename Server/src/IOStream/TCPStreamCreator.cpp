#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../include/IOStream/TCPStreamCreator.hpp"

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

    void TCPStreamCreator::Stream::openStream() {
        if (is_open) throw TCPStreamError::StreamAlreadyOpenedError();
        is_open = true;
    }
    void TCPStreamCreator::Stream::closeStream() {
        if (!is_open) throw TCPStreamError::StreamAlreadyOpenedError();
        close(socket_fd);
        is_open = false;
    }
    void TCPStreamCreator::Stream::writeMessage(const std::string& message) {
        if (write(socket_fd, message.c_str(), message.length()) != message.length()) throw TCPStreamError::DisconnectionError();
    }
    std::string* TCPStreamCreator::Stream::readMessage(unsigned long long length) {
        auto message = new std::string(length, 0);
        unsigned long long bytes_read = 0;

        while (bytes_read != length) {
            unsigned long long diff = read(socket_fd, message->data() + bytes_read, length);
            if (diff == -1) throw TCPStreamError::DisconnectionError();
            bytes_read += diff;
        }

        return message;
    }

    TCPStreamCreator::Stream* TCPStreamCreator::getStream() {
        socklen_t socket_address_len = sizeof(socket_address);
        int new_socket = accept(socket_fd, reinterpret_cast<sockaddr*>(&socket_address), &socket_address_len);

        return new Stream(new_socket);
    }

}