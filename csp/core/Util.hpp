#ifndef _UTIL_HPP_
#define _UTIL_HPP_ 1

#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-result"

#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

std::vector<std::string> &explode(char delim, const std::string &s, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }

    return elems;
}

std::vector<std::string> explode(char delim, const std::string &s)
{
    std::vector<std::string> elems;
    explode(delim, s, elems);
    return elems;
}

std::string trim(std::string s)
{
    return s.erase(s.find_last_not_of(" \n\r\t") + 1);
}

std::string get_cookie(char *cookies, const char *name)
{
    std::string result = "";

    char *key, *val, *lasts = 0;
    for (;;)
    {
        key = strtok_r(cookies, "= ", &lasts);
        val = strtok_r(0, ";,", &lasts);

        if (!val) break; //no more cookies

        if (!strcmp(key, name))
        {
            result = val;
            break;
        }

        cookies = 0;
    }

    return result;
}

std::string get_param(std::string &paramString, const char *name)
{
    std::vector<std::string> pair, params = explode('&', paramString);

    for (int i = params.size(); i--;)
    {
        pair = explode('=', trim(params[i]));

        if (pair[0] == name)
        {
            return pair[1];
        }
    }

    return "";
}

std::string random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);

    return str;
}

std::string str_replace(const std::string& from, const std::string& to, std::string str)
{
    size_t start_pos = 0;

    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

    return str;
}

#endif
