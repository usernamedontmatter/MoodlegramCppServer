#include <fstream>
#include <string>
#include <thread>
#include <filesystem>
#include <iostream>

#include "../../include/Server/Server.hpp"
#include "../../include/EncryptingLayout/EncryptingLayout.hpp"
#include "../../include/Server/ServerError.hpp"

#define DEFAULT_BUFFER_SIZE 1024

namespace Server {
    template<template <typename> class DatabaseType, template <template <typename> class, typename> class AuthType,
        IOStream::IOStreamCreatorConcept IOStreamCreatorType> requires Auth::AuthConcept<AuthType<DatabaseType,
        typename IOStreamCreatorType::Stream>, DatabaseType, typename IOStreamCreatorType::Stream>
    template<IOStream::IOStreamConcept IOStreamType>
    void Server<DatabaseType, AuthType, IOStreamCreatorType>::send_error(IOStreamType* iostream, uint8_t status,
                                                                  const std::string &error_message) {
        std::string str;
        str.push_back(static_cast<char>(status));
        iostream->writeMessage(str);
        iostream->writeMessage(error_message);
    }
    template<template <typename> class DatabaseType, template <template <typename> class, typename> class AuthType,
        IOStream::IOStreamCreatorConcept IOStreamCreatorType> requires Auth::AuthConcept<AuthType<DatabaseType,
        typename IOStreamCreatorType::Stream>, DatabaseType, typename IOStreamCreatorType::Stream>
    void Server<DatabaseType, AuthType, IOStreamCreatorType>::process_command(typename IOStreamCreatorType::Stream* iostream) {
        try {
            iostream->openStream();

            std::string* buffer;
            std::string* command = iostream->readMessage(4);
            // Version
            if (command->at(0) == 1) {
                EncryptingLayout::EncryptingLayoutInterface<typename IOStreamCreatorType::Stream>* encrypted_iostream = nullptr;

                // Encrypting
                if (command->at(1) == 1 && command->at(2) == 0) {
                    encrypted_iostream = new EncryptingLayout::NoEncryptingLayout<typename IOStreamCreatorType::Stream>(iostream);
                }
                else {
                    send_error(iostream, 1, "Unsupported encrypting type");
                }

                if (encrypted_iostream != nullptr) {
                    encrypted_iostream->openStream();

                    // Command
                    if (command->at(3) == 1) { // Registration
                        std::string answer;
                        answer.push_back(0);
                        answer.push_back(AuthType<DatabaseType, typename IOStreamCreatorType::Stream>::number);

                        encrypted_iostream->writeMessage(answer);

                        AuthType<DatabaseType, EncryptingLayout::EncryptingLayoutInterface<
                            typename IOStreamCreatorType::Stream>>::start(encrypted_iostream, database);
                    }
                    else if (command->at(3) == 2) { // Send message
                        uint64_t sender_id = AuthType<DatabaseType, EncryptingLayout::EncryptingLayoutInterface<
                            typename IOStreamCreatorType::Stream>>::authenticate(encrypted_iostream, database);

                        buffer = iostream->readMessage(8);
                        uint64_t receiver_id = *reinterpret_cast<uint64_t*>(buffer->data());
                        delete buffer;

                        if (database.isUserExists(receiver_id)) {
                            buffer = iostream->readMessage(8);
                            unsigned long long length = *reinterpret_cast<uint64_t*>(buffer->data());
                            delete buffer;

                            buffer = iostream->readMessage(length);
                            database.makeMessage(sender_id, receiver_id, *buffer);
                            delete buffer;

                            buffer = new std::string();
                            buffer->push_back(0);
                            iostream->writeMessage(*buffer);
                            delete buffer;
                        }
                        else {
                            send_error(encrypted_iostream, 3, "Received with this id doesn't exists");
                        }
                    }
                    else if (command->at(3) == 3) { // Get messages
                        uint64_t id = AuthType<DatabaseType, typename IOStreamCreatorType::Stream>::authenticate(iostream, database);

                        auto user = database.getUser(id);
                        uint64_t message_count = user->getQueueLength();

                        buffer = new std::string(1, 0);
                        iostream->writeMessage(*buffer);

                        buffer->resize(8);
                        *reinterpret_cast<uint64_t*>(buffer->data()) = message_count;
                        iostream->writeMessage(*buffer);

                        for (uint64_t i = 0; i < message_count; ++i) {
                            auto message = user->popMessage();
                            *reinterpret_cast<uint64_t*>(buffer->data()) = static_cast<uint64_t>(message.message.length());
                            iostream->writeMessage(*buffer);
                            iostream->writeMessage(message.message);
                        }

                        delete user;
                        delete buffer;
                    }
                    else {
                        send_error(iostream, 1, "Unsupported command");
                    }

                    encrypted_iostream->closeStream();
                    delete encrypted_iostream;
                }
            }
            else {
                send_error(iostream, 1, "Unsupported version");
            }

            iostream->closeStream();
            delete command;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        delete iostream;
    }
    template<template <typename> class DatabaseType, template <template <typename> class, typename> class AuthType,
        IOStream::IOStreamCreatorConcept IOStreamCreatorType> requires Auth::AuthConcept<AuthType<DatabaseType,
        typename IOStreamCreatorType::Stream>, DatabaseType, typename IOStreamCreatorType::Stream>
    void Server<DatabaseType, AuthType, IOStreamCreatorType>::run() {
        while (is_running) {
            typename IOStreamCreatorType::Stream* stream = iostream.getStream();

            std::thread(&Server::process_command, this, stream).detach();
        }
    }

    template<template <typename> class DatabaseType, template <template <typename> class, typename> class AuthType,
        IOStream::IOStreamCreatorConcept IOStreamCreatorType> requires Auth::AuthConcept<AuthType<DatabaseType,
        typename IOStreamCreatorType::Stream>, DatabaseType, typename IOStreamCreatorType::Stream>
    void Server<DatabaseType, AuthType, IOStreamCreatorType>::start() {
        if (is_running) throw ServerError::ServerAlreadyStartedError();

        is_running = true;
        std::thread(&Server::run, this).detach();
    }

    template<template <typename> class DatabaseType, template <template <typename> class, typename> class AuthType,
        IOStream::IOStreamCreatorConcept IOStreamCreatorType> requires Auth::AuthConcept<AuthType<DatabaseType,
        typename IOStreamCreatorType::Stream>, DatabaseType, typename IOStreamCreatorType::Stream>
    void Server<DatabaseType, AuthType, IOStreamCreatorType>::stop() {
        if (is_running) is_running = false;
    }
}

#undef DEFAULT_BUFFER_SIZE