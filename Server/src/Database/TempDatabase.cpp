#include <stdexcept>

#include "../../include/Database/TempDatabase.hpp"

namespace Database {
    template<typename AuthDataType>
    AuthDataType TempDatabase<AuthDataType>::User::getAuthData () const {
        return auth_data;
    }
    template<typename AuthDataType>
    unsigned long long TempDatabase<AuthDataType>::User::getQueueLength () const {
        return messages.size();
    }
    template<typename AuthDataType>
    Message TempDatabase<AuthDataType>::User::popMessage () {
        Message copy = std::move(messages.back());
        messages.pop();
        return copy;
    }
    template<typename AuthDataType>
    void TempDatabase<AuthDataType>::User::pushMessage (const Message &message) {
        messages.push(message);
    }

    template<typename AuthDataType>
    void TempDatabase<AuthDataType>::makeMessage(uint64_t sender_id, uint64_t receiver_id, const std::string& message) {
        users[receiver_id]->pushMessage(Message(sender_id, message));
    }

    template<typename AuthDataType>
    bool TempDatabase<AuthDataType>::isUserExists(uint64_t id) const {
        return users.contains(id);
    }
    template<typename AuthDataType>
    typename TempDatabase<AuthDataType>::User* TempDatabase<AuthDataType>::getUser(uint64_t id) const {
        if (users.contains(id)) {
            return users.at(id);
        }
        else {
            throw std::invalid_argument("User does not exist");
        }
    }

    template<typename AuthDataType>
    uint64_t TempDatabase<AuthDataType>::addUser(AuthDataType auth_data) {
        if (free_space_list.empty()) {
            users[new_user_index] = new User(auth_data);

            return new_user_index++;
        }
        else {
            uint64_t id = free_space_list.top();
            users[id] = new User(auth_data);
            free_space_list.pop();
            return id;
        }
    }
    template<typename AuthDataType>
    void TempDatabase<AuthDataType>::deleteUser(uint64_t id) {
        if (users.contains(id)) {
            delete users[id];
            users.erase(id);
            if (id == new_user_index - 1) {
                --new_user_index;
            }
            else {
                free_space_list.push(id);
            }
        }
        else {
            throw std::invalid_argument("User does not exist");
        }
    }
    template<typename AuthDataType>
    void TempDatabase<AuthDataType>::changeUserAuthData(uint64_t id, AuthDataType auth_data) {
        if (users.contains(id)) {
            users[id]->auth_data = auth_data;
        }
        else {
            throw std::invalid_argument("User does not exist");
        }
    }
}