#pragma once

#include "Assert.hpp"
#include "Types.hpp"
#include "Utility.hpp"

namespace dts {

template<typename T, dts::u32 Size>
struct Array
{
    using Iterator      = T *;
    using ConstIterator = const T *;

    [[nodiscard]] constexpr const T &at(const dts::u32 index) const;
    [[nodiscard]] constexpr T       &at(const dts::u32 index);
    [[nodiscard]] constexpr const T &operator[](const dts::u32 index) const;
    [[nodiscard]] constexpr T       &operator[](const dts::u32 index);
    [[nodiscard]] constexpr const T &front() const;
    [[nodiscard]] constexpr T       &front();
    [[nodiscard]] constexpr const T &back() const;
    [[nodiscard]] constexpr T       &back();
    [[nodiscard]] constexpr const T *data() const;
    [[nodiscard]] constexpr T       *data();

    [[nodiscard]] constexpr T       *begin();
    [[nodiscard]] constexpr const T *begin() const;
    [[nodiscard]] constexpr T       *end();
    [[nodiscard]] constexpr const T *end() const;

    [[nodiscard]] constexpr bool     empty() const;
    [[nodiscard]] constexpr dts::u32 size() const;

    [[nodiscard]] constexpr bool operator==(const Array &rhs) const;

    constexpr void fill(const T &value);

    T m_data[Size];
};

template<typename T, dts::u32 Size>
constexpr const T &Array<T, Size>::at(const dts::u32 index) const
{
    assert(
      index < Size, "[ERROR] dts::Array::at(): index was greater than size."
    );
    return m_data[index];
}

template<typename T, dts::u32 Size>
constexpr T &Array<T, Size>::at(const dts::u32 index)
{
    assert(
      index < Size, "[ERROR] dts::Array::at(): index was greater than size."
    );
    return m_data[index];
}

template<typename T, dts::u32 Size>
constexpr const T &Array<T, Size>::operator[](const dts::u32 index) const
{
    return m_data[index];
}

template<typename T, dts::u32 Size>
constexpr T &Array<T, Size>::operator[](const dts::u32 index)
{
    return m_data[index];
}

template<typename T, dts::u32 Size>
constexpr const T &Array<T, Size>::front() const
{
    return m_data[0];
}

template<typename T, dts::u32 Size>
constexpr T &Array<T, Size>::front()
{
    return m_data[0];
}

template<typename T, dts::u32 Size>
constexpr const T &Array<T, Size>::back() const
{
    return *(m_data + Size);
}

template<typename T, dts::u32 Size>
constexpr T &Array<T, Size>::back()
{
    return *(m_data + Size);
}

template<typename T, dts::u32 Size>
constexpr const T *Array<T, Size>::data() const
{
    return m_data;
}

template<typename T, dts::u32 Size>
constexpr T *Array<T, Size>::data()
{
    return m_data;
}

template<typename T, dts::u32 Size>
constexpr T *Array<T, Size>::begin()
{
    return m_data;
}

template<typename T, dts::u32 Size>
constexpr const T *Array<T, Size>::begin() const
{
    return m_data;
}

template<typename T, dts::u32 Size>
constexpr T *Array<T, Size>::end()
{
    return m_data + Size;
}

template<typename T, dts::u32 Size>
constexpr const T *Array<T, Size>::end() const
{
    return m_data + Size;
}

template<typename T, dts::u32 Size>
constexpr bool Array<T, Size>::empty() const
{
    return !(Size > 0);
}

template<typename T, dts::u32 Size>
constexpr dts::u32 Array<T, Size>::size() const
{
    return Size;
}

template<typename T, dts::u32 Size>
[[nodiscard]] constexpr bool Array<T, Size>::operator==(const Array &rhs) const
{
    if (Size != rhs.size()) { return false; }

    for (dts::u32 i = 0; i < rhs.size(); ++i) {
        if (m_data[i] != rhs[i]) { return false; }
    }

    return true;
}

template<typename T, dts::u32 Size>
constexpr void Array<T, Size>::fill(const T &value)
{
    for (auto &elem : *this) { elem = value; }
}

namespace impl {

template<typename T, dts::u32 Size, dts::u32... Indices>
[[nodiscard]] constexpr static Array<RemoveCVT<T>, Size> to_array_impl(
  T (&array)[Size],
  [[maybe_unused]] IndexSequence<Indices...> sequence
)
{
    return { { array[Indices]... } };
}

} // namespace impl

template<typename T, dts::u32 Size>
[[nodiscard]] constexpr static Array<RemoveCVT<T>, Size> to_array(T (&array
)[Size])
{
    return impl::to_array_impl(array, MakeIndexSequence<Size>{});
}

} // namespace dts
