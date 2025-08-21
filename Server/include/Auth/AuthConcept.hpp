#pragma once

#include <concepts>
#include "../Database/DatabaseConcept.hpp"
#include "../IOStream/IOStreamConcept.hpp"

namespace Auth {
    template<typename T, template <typename> class DatabaseType, typename IOStreamType>
    concept AuthConcept = Database::DatabaseConcept<DatabaseType<typename T::Data>, typename T::Data> &&
                          IOStream::IOStreamConcept<IOStreamType> && requires(T obj, typename T::Data data,
                          IOStreamType* stream, DatabaseType<typename T::Data>& database) {
        { T::start(stream, database) } -> std::same_as<void>;
        { T::authenticate(stream, database) } -> std::same_as<uint64_t>;
        { T::number } -> std::same_as<const uint8_t&>;
    };
}