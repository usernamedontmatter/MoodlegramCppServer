#pragma once

#include <map>
#include <queue>
#include <stack>

#include "DatabaseConcept.hpp"

namespace Database {
    template<typename AuthDataType>
    class TempDatabase {
    public:
        class User{
        private:
            AuthDataType auth_data;
            std::queue<Message> messages;

        public:
            explicit User(AuthDataType auth_data) : auth_data(auth_data) {}

            AuthDataType getAuthData() const;
            unsigned long long getQueueLength() const;
            Message popMessage();
            void pushMessage(const Message &message);
        };

        void makeMessage(uint64_t sender_id, uint64_t receiver_id, const std::string& message);

        bool isUserExists(uint64_t id) const;

        User* getUser(uint64_t id) const;
        uint64_t addUser(AuthDataType auth_data);
        void deleteUser(uint64_t id);
        void changeUserAuthData(uint64_t id, AuthDataType new_user);
    protected:

        std::stack<uint64_t> free_space_list;
        uint64_t new_user_index = 1;
        std::map<uint64_t, User*> users;
    };
}