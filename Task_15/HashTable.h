#pragma once

#include <string>
#include <vector>
#include <memory>

typedef unsigned int uint;

const int SHA1_HASH_SIZE = 5;
const uint INIT_ARRAY_SIZE = 8;
const double MULTIPLICATE_CONST = 0.6180339887;

const double PERCENTAGE_OF_PAIR_REMOVED = .10;

typedef uint SHA1_Hash[SHA1_HASH_SIZE];

enum class ePairStatus
{
    unused,
    engaged,
    deleted
};

struct Pair
{
    Pair() : _status(ePairStatus::unused), _password_hash(new uint[SHA1_HASH_SIZE], std::default_delete<uint[]>()) 
    {
        _login.clear();
    }

    Pair(const std::string& login, std::shared_ptr<uint> sha1_hash_ptr) : _login(login), _status(ePairStatus::engaged)
    {
        std::shared_ptr<uint> new_ptr(new uint[SHA1_HASH_SIZE], std::default_delete<uint[]>());

        for (auto i{0}; i < SHA1_HASH_SIZE; ++i)
            new_ptr.get()[i] = sha1_hash_ptr.get()[i];

        _password_hash = new_ptr;

    }

    Pair(const Pair& other)
    {
        _login = other._login;
        _status = other._status;
        std::shared_ptr<uint> new_ptr(new uint[SHA1_HASH_SIZE], std::default_delete<uint[]>());

        for (auto i{0}; i < SHA1_HASH_SIZE; ++i)
            new_ptr.get()[i] = other._password_hash.get()[i];

        _password_hash = new_ptr;

    }

    ~Pair() {}

    Pair& operator=(const Pair& other)
    {
        _login = other._login;
        _status = other._status;
        std::shared_ptr<uint> new_ptr(new uint[SHA1_HASH_SIZE], std::default_delete<uint[]>());

        for (auto i{0}; i < SHA1_HASH_SIZE; ++i)
            new_ptr.get()[i] = other._password_hash.get()[i];

        _password_hash = new_ptr;

        return *this;
    }

    std::string _login;
    std::shared_ptr<uint> _password_hash;
    ePairStatus _status{ePairStatus::unused};
};

class HashTable
{
public:
    HashTable();
    //~HashTable();

    auto add(const std::string& login, std::shared_ptr<uint>& password) -> void;
    auto remove(const std::string& login) -> void;
    auto find(const std::string& login) const -> const std::shared_ptr<uint>&;

private:
    std::vector<Pair> _pair_array;
    uint _current_size{INIT_ARRAY_SIZE};
    uint _count{0};
    uint _deleted_count{0};

    auto hash_func(const std::string& message, uint offset) const -> uint;
    auto resize() -> void;
    auto repair() -> void;
};
