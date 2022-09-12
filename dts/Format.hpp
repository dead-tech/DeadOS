#pragma once

#include "String.hpp"

namespace dts {

template<typename Type>
struct Formatter
{
};

// TODO: Use stringview for fmt
//       Make it work with lvalues too
//       Implement binary and hex formatters
//       Format integer
template<typename... Args>
String format(String fmt, Args &&...args)
{
    assert(
      dts::count(fmt, '{') == sizeof...(args),
      "[ERROR] dts::format(): Mismatch of opening '{' and number of "
      "provided arguments."
    );

    assert(
      dts::count(fmt, '}') == sizeof...(args),
      "[ERROR] dts::format(): Mismatch of opening '{' and number of "
      "provided arguments."
    );

    String result;

    const auto format_helper = [&](const auto &value) {
        const auto open_curly  = fmt.find_first_of('{');
        const auto close_curly = fmt.find_first_of('}');

        assert(
          open_curly != dts::String::npos && close_curly != dts::String::npos,
          "[ERROR] dts::format(): Could not find matching '{' or '}'."
        );

        result += fmt.substr(0, open_curly);
        result += Formatter<DecayT<decltype(value)>>::format(value);

        if (close_curly + 1 < fmt.size()) {
            const auto rest = fmt.substr(close_curly + 1, fmt.size() - 1);
            fmt             = rest;
        } else {
            fmt.clear();
        }
    };

    (format_helper(forward<Args>(args)), ...);
    result += fmt;
    return result;
}

template<typename... Args>
void print(String fmt, Args &&...args)
{
    if constexpr (sizeof...(args) > 0) {
        const auto to_print = format(fmt, args...);
        asm volatile("int $0x80" : : "a"(2), "b"(to_print.c_str()));
    } else {
        asm volatile("int $0x80" : : "a"(2), "b"(fmt.c_str()));
    }
}

} // namespace dts
