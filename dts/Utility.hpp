#pragma once

#include "TypeTraits.hpp"

namespace dts {

template<typename T>
RemoveReferenceT<T> &&move(T &&arg)
{
    return static_cast<RemoveReferenceT<T> &&>(arg);
}

} // namespace dts
