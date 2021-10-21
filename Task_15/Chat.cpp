#include "Chat.h"

#include "SHA1.h"
#include "HashTable.h"

auto Chat::reg(const std::string& login, const std::string& password) -> void 
{
    std::shared_ptr<uint> pass_ptr = sha1(password);

    _hash_table.add(login, pass_ptr);
}

auto Chat::login(const std::string& login, const std::string& password) const -> bool
{
    std::shared_ptr<uint> pass_ptr = sha1(password);
    std::shared_ptr<uint> result_ptr = _hash_table.find(login);

    if (!result_ptr) return false;
    auto i{0u};
    for (; i < SHA1HASHLENGTHUINTS; ++i)
    {
        if (pass_ptr.get()[i] != result_ptr.get()[i]) return false;
    }
    return true;
}

auto Chat::remove(const std::string& login) -> void 
{
    _hash_table.remove(login);
}
