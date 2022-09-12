#pragma once

#include "String.hpp"

namespace dts {

// TODO: Use stringview for fmt
//       Make it work with lvalues too
//       Implement binary and hex formatters
//       Format integer
template<typename... Args>
String format(String &&fmt, Args &&...args)
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
        result += fmt.substr(0, fmt.find_first_of('{'));
        result += value;
        const auto rest =
          fmt.substr(fmt.find_first_of('}') + 1, fmt.size() - 1);
        fmt = rest;
    };

    (format_helper(forward<Args>(args)), ...);
    result += fmt;
    return result;
}

} // namespace dts
