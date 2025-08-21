#pragma once

#include <cstdint>
#include <string>

namespace Database {
    struct Message {
        uint64_t sender_id;
        std::string message;
    };

    template<typename T, typename AuthDataType>
    concept DatabaseConcept =  requires (T obj, T const const_obj, const typename T::User const_user, typename T::User user, uint64_t sender_id,
            uint64_t receiver_id, const std::string& message, uint64_t id, AuthDataType auth_data, const Message& msg) {
        requires std::is_constructible_v<typename T::User, AuthDataType>;

        { const_user.getAuthData() } -> std::same_as<AuthDataType>;
        { const_user.getQueueLength() } -> std::same_as<unsigned long long>;
        { user.popMessage() } -> std::same_as<Message>;
        { user.pushMessage(msg) } -> std::same_as<void>;

        { obj.makeMessage(sender_id, receiver_id, message) } -> std::same_as<void>;
        { const_obj.isUserExists(id) } -> std::same_as<bool>;
        { const_obj.getUser(id) } -> std::same_as<typename T::User*>;
        { obj.addUser(auth_data) } -> std::same_as<uint64_t>;
        { obj.deleteUser(id) } -> std::same_as<void>;
        { obj.changeUserAuthData(id, auth_data) } -> std::same_as<void>;
    };
}
