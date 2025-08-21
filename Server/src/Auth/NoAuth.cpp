#include <cstring>

#include "../../include/Auth/Auth.hpp"
#include "../../include/Server/ClientError.hpp"
#include "../../include/IOStream/IOStreamConcept.hpp"

namespace Auth {
    template<template <typename> class DatabaseType, IOStream::IOStreamConcept IOStreamType> requires Database::DatabaseConcept<DatabaseType<NoAuthData>, NoAuthData>
    void NoAuth<DatabaseType, IOStreamType>::start(IOStreamType* stream, DatabaseType<Data>& database) {
        std::string str(8, 0);

        *reinterpret_cast<uint64_t*>(str.data()) = database.addUser(Data());

        stream->writeMessage(str);
    }

    template<template <typename> class DatabaseType, IOStream::IOStreamConcept IOStreamType> requires Database::DatabaseConcept<DatabaseType<NoAuthData>, NoAuthData>
    uint64_t NoAuth<DatabaseType, IOStreamType>::authenticate(IOStreamType* stream, DatabaseType<Data>& database) {
        std::string* str = stream->readMessage(8);

        if (str->length() != 8) throw Server::ClientError::AuthFailedError();

        uint64_t id = *reinterpret_cast<uint64_t*>(str->data());
        if (!database.isUserExists(id)) throw Server::ClientError::AuthFailedError();

        delete str;
        return id;
    }
}
