#pragma once

#include <netinet/in.h>
#include <string>

#include "../IOStream/TCPStream.hpp"

#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 8000

namespace IOStream {

    namespace TCPStreamError {
        struct TCPStreamError : std::exception {};

        struct StreamAlreadyOpenedError : TCPStreamError {
            const char* what() const noexcept override {
                return "Stream already opened";
            }
        };
        struct StreamAlreadyClosedError : TCPStreamError {
            const char* what() const noexcept override {
                return "Stream already closed";
            }
        };
        struct SocketCreationError : TCPStreamError {
            const char* what() const noexcept override {
                return "Socket creation error";
            }
        };
        struct BindingError : TCPStreamError {
            const char* what() const noexcept override {
                return "Binding error";
            }
        };
        struct ListeningError : TCPStreamError {
            const char* what() const noexcept override {
                return "Listening error";
            }
        };
        struct DisconnectionError : TCPStreamError {
            const char* what() const noexcept override {
                return "Disconnection error";
            }
        };
    }

    class TCPStreamCreator {
    private:
        const std::string address;
        const int port;

        int socket_fd;
        sockaddr_in socket_address{};

    public:
        using Stream = TCPStream;

        explicit TCPStreamCreator(const std::string& address = DEFAULT_ADDRESS, const int port = DEFAULT_PORT);
        ~TCPStreamCreator();

        Stream* getStream();
    };
}