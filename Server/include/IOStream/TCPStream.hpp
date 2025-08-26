#pragma once

namespace IOStream {
    class TCPStream {
    protected:
        bool is_open = false;
        int socket_fd;
    public:
        void openStream();
        void closeStream();
        void writeMessage(const std::string& message);
        std::string* readMessage(unsigned long long length);

        explicit TCPStream(int socket_fd) : socket_fd(socket_fd) {}
    };
}