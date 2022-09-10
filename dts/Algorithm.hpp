#pragma once

#include "Concepts.hpp"
#include "Types.hpp"

namespace dts {

template<typename T>
constexpr void swap(T &a, T &b)
{
    const T &temp = a;
    a             = b;
    b             = temp;
}

template<IterableContainerC Container, typename Item>
dts::u32 count(const Container &container, const Item &item)
{
    dts::u32 count = 0;
    for (const auto &elem : container) {
        if (elem == item) { ++count; }
    }

    return count;
}

} // namespace dts
