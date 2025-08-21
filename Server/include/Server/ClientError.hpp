#pragma once

#include <exception>

namespace Server::ClientError {
    struct ClientDisconnectedError : std::exception {
        const char* what() const noexcept override {
            return "Client disconnected";
        }
    };
    struct AuthFailedError : std::exception {
        const char* what() const noexcept override {
            return "Auth failed";
        }
    };
}

