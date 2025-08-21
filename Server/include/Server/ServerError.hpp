#pragma once

namespace Server::ServerError {
    struct ServerError : std::exception {};

    struct ServerAlreadyStartedError : ServerError {
        const char* what() const noexcept override {
            return "Server already started";
        }
    };
}