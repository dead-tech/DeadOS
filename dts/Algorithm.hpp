#pragma once

namespace dts {

template<typename T>
void swap(T &a, T &b)
{
    const T &temp = a;
    a             = b;
    b             = temp;
}

} // namespace dts