#pragma once
#include <string>

#include "HashTable.h"

class Chat
{
public:
    Chat() = default;
    auto reg(const std::string& login, const std::string& password) -> void;
    auto login(const std::string& login, const std::string& password) const -> bool;
    auto remove(const std::string& login) ->void;
private:

    HashTable _hash_table;
};
