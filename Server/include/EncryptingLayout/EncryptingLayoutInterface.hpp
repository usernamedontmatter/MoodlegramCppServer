#pragma once

#include <string>

#include "../IOStream/IOStreamConcept.hpp"

namespace EncryptingLayout {
    template<IOStream::IOStreamConcept IOStreamType>
    class EncryptingLayoutInterface {
    protected:
        IOStreamType* iostream;
    public:
        explicit EncryptingLayoutInterface(IOStreamType* iostream) : iostream(iostream) {}
        virtual ~EncryptingLayoutInterface() = default;

        virtual void openStream() {
            this->iostream->openStream();
        }
        virtual void closeStream() {
            this->iostream->closeStream();
        }
        virtual void writeMessage(const std::string& message) {
            this->iostream->writeMessage(message);
        }
        virtual std::string* readMessage(unsigned long long length) {
            return this->iostream->readMessage(length);
        }
    };
}