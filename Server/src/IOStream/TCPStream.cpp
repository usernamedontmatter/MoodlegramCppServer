#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../include/IOStreamCreator/TCPStreamCreator.hpp"

namespace IOStream {
    void TCPStream::openStream() {
        if (is_open) throw TCPStreamError::StreamAlreadyOpenedError();
        is_open = true;
    }
    void TCPStream::closeStream() {
        if (!is_open) throw TCPStreamError::StreamAlreadyOpenedError();
        close(socket_fd);
        is_open = false;
    }
    void TCPStream::writeMessage(const std::string& message) {
        if (write(socket_fd, message.c_str(), message.length()) != message.length()) throw TCPStreamError::DisconnectionError();
    }
    std::string* TCPStream::readMessage(unsigned long long length) {
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