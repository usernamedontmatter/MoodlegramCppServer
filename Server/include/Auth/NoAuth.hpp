#pragma once

#include "../Database/DatabaseConcept.hpp"
#include "../IOStream/IOStreamConcept.hpp"

namespace Auth {
    template<template <typename> class DatabaseType, IOStream::IOStreamConcept IOStreamType>
        requires Database::DatabaseConcept<DatabaseType<NoAuthData>, NoAuthData>
    struct NoAuth {
        using Data = NoAuthData;

        const static uint8_t number = 1;

        static void start(IOStreamType* stream, DatabaseType<Data>& database);

        static uint64_t authenticate(IOStreamType* stream, DatabaseType<Data>& database);
    };


}