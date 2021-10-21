#include <iostream>

#include "Chat.h"

auto main() -> int
{
    Chat chat;

    std::string string[]{
        "abcd",
        "abcf",
        "abce",
        "abcde",
        "abcfe",
        "abcee",
        "abcdf",
        "abcff",
        "abcef",
        "abcdg",
        "abcfg",
        "abceg",
        "abcdh",
        "abcfh",
        "abceh",
        "abcdi",
        "abcfi",
        "abcei",
        "abcdj",
        "abcfj",
        "abcej",
        "abcdk",
        "abcfk",
        "abcek",
        "abcdl",
        "abcfl",
        "abcel",
        "abcdm",
        "abcfm",
        "abcem",
        "abcdn",
        "abcfn",
        "abcen",
        "abcdo",
        "abcfo",
        "abceo",
    };

    for (auto i{0}; i < 26; ++i)
    {
        chat.reg(string[i], string[i]);
    }
    for (auto i{0}; i < 26; ++i)
    {
        auto result{chat.login(string[i], string[i])};

        std::cout << i << " - " << result << std::endl;
    }

    for (auto i{0}; i < 26; ++i)
    {
        // auto result{chat.login(string[i], string[i])};
        if (i % 2) chat.remove(string[i]);
    }

    for (auto i{0}; i < 26; ++i)
    {
        auto result{chat.login(string[i], string[i])};

        std::cout << i << " - " << result << std::endl;
    }

    auto result{chat.login(string[0], string[0])};

    std::cout << "Hello World!\n";

    return 0;
}
