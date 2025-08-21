#pragma once

#include <fstream>
#include <string>

#include "../Auth/Auth.hpp"
#include "../../include/IOStream/IOStream.hpp"

namespace Server {
    template<template <typename> class DatabaseType, template <template <typename> class, typename> class AuthType,
        IOStream::IOStreamCreatorConcept IOStreamCreatorType> requires Auth::AuthConcept<AuthType<DatabaseType,
        typename IOStreamCreatorType::Stream>, DatabaseType, typename IOStreamCreatorType::Stream>
    class Server {
    private:
        DatabaseType<typename AuthType<DatabaseType, typename IOStreamCreatorType::Stream>::Data>& database;
        IOStreamCreatorType& iostream;

        int socket_fd = 0;
        bool is_running = false;

        template<IOStream::IOStreamConcept IOStreamType>
        static void send_error(IOStreamType*, uint8_t status, const std::string& error_message);

        void process_command(typename IOStreamCreatorType::Stream*);

        void run();

    public:
        explicit Server(DatabaseType<typename AuthType<DatabaseType,
            typename IOStreamCreatorType::Stream>::Data>& database, IOStreamCreatorType& iostream) : database(database),
            iostream(iostream){}
        ~Server() {
            this->stop();
        }

        void start();
        void stop();
    };
}
