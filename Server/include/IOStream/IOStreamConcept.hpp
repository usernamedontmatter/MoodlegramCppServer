#pragma once

#include <string>

namespace IOStream {
    template <typename T>
    concept IOStreamConcept = requires(T obj, const std::string& message, unsigned long long length) {
        { obj.openStream() } -> std::same_as<void>;
        { obj.closeStream() } -> std::same_as<void>;
        { obj.writeMessage(message) } -> std::same_as<void>;
        { obj.readMessage(length) } -> std::same_as<std::string*>;
    };
}