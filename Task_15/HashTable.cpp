
#include "HashTable.h"
#include <math.h>

HashTable::HashTable()
{
    for (auto i{0}; i < INIT_ARRAY_SIZE; ++i)
    {
        _pair_array.push_back(Pair());
    }
}

auto HashTable::add(const std::string& login, std::shared_ptr<uint>& password) -> void
{
    if (find(login)) return;

    auto index{0u};
    auto i{0u};
    for (; i < _current_size; ++i)
    {
        index = hash_func(login, i);
        if (_pair_array[index]._status == ePairStatus::unused) break;
    }

    if (i == _current_size)
    {
        resize();
        add(login, password);
        return;
    }

    _pair_array[index]._login = login;
    _pair_array[index]._password_hash = password;
    _pair_array[index]._status = ePairStatus::engaged;
    ++_count;
}

auto HashTable::remove(const std::string& login) -> void
{
    auto index{0u};
    for (auto i{0u}; i < _current_size; ++i)
    {
        index = hash_func(login, i);
        if (_pair_array[index]._status == ePairStatus::unused) return;
        if (_pair_array[index]._status == ePairStatus::deleted) continue;
        if (_pair_array[index]._login == login)
        {
            --_count;
            ++_deleted_count;
            _pair_array[index]._status = ePairStatus::deleted;

            if (static_cast<double>(_deleted_count) / _current_size > PERCENTAGE_OF_PAIR_REMOVED)
            {
                repair();
            }

            return;
        }
    }
}

auto HashTable::find(const std::string& login) const -> const std::shared_ptr<uint>&
{
    auto index{0u};
    for (auto i{0u}; i < _current_size; ++i)
    {
        index = hash_func(login, i);
        if (_pair_array[index]._status == ePairStatus::unused) return nullptr;
        if (_pair_array[index]._status == ePairStatus::deleted) continue;
        if (_pair_array[index]._login == login) return _pair_array[index]._password_hash;
    }
    return nullptr;
}

auto HashTable::hash_func(const std::string& message, uint offset) const -> uint
{
    uint sum{0};
    for (auto i{0u}; i < message.size(); ++i)
    {
        sum += static_cast<uint>(message[i]);
    }

    double int_part{0};
    auto fractional_part{modf(static_cast<double>(sum) * MULTIPLICATE_CONST, &int_part)};

    return static_cast<uint>(_current_size * fractional_part + offset * offset) % _current_size;
}

auto HashTable::resize() -> void
{
    auto prev_vect = _pair_array;
    _pair_array.resize(prev_vect.size() * 2);
    for (auto i{0u}; i < _current_size; ++i)
    {
        _pair_array[i]._status = ePairStatus::unused;
    }

    auto prev_curr_size{_current_size};
    _current_size <<= 1;  // Mult 2

    for (auto i{0u}; i < prev_curr_size; ++i)
    {
        if (prev_vect[i]._status == ePairStatus::engaged) add(prev_vect[i]._login, prev_vect[i]._password_hash);
    }
    _deleted_count = 0;
}

auto HashTable::repair() -> void
{
    auto prev_vect = _pair_array;
    for (auto i{0u}; i < _current_size; ++i)
    {
        _pair_array[i]._status = ePairStatus::unused;
    }

    for (auto i{0u}; i < _current_size; ++i)
    {
        if (prev_vect[i]._status == ePairStatus::engaged) add(prev_vect[i]._login, prev_vect[i]._password_hash);
    }
    _deleted_count = 0;
}
