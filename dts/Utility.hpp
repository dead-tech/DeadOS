#pragma once

#include "TypeTraits.hpp"

namespace dts {

template<typename T>
RemoveReferenceT<T> &&move(T &&arg)
{
    return static_cast<RemoveReferenceT<T> &&>(arg);
}

template<typename T>
[[nodiscard]] constexpr T &&forward(RemoveReferenceT<T> &arg)
{
    return static_cast<T &&>(arg);
}

template<typename T>
[[nodiscard]] constexpr T &&forward(RemoveReferenceT<T> &&arg)
{
    return static_cast<T &&>(arg);
}

} // namespace dts
