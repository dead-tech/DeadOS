#pragma once

#include "Types.hpp"
#include "TypeTraits.hpp"

namespace dts {

template<typename T>
[[nodiscard]] constexpr RemoveReferenceT<T> &&move(T &&arg)
{
    return static_cast<RemoveReferenceT<T> &&>(arg);
}

template<typename T>
[[nodiscard]] constexpr T &&forward(RemoveReferenceT<T> &arg)
{
    return static_cast<T &&>(arg);
}

template<dts::u32... Integers>
struct IndexSequence
{
    using type       = IndexSequence;
    using value_type = dts::u32;
    static constexpr dts::u32 size() noexcept { return sizeof...(Integers); }
};

namespace impl {

template<typename FirstSequence, typename SecondSequence>
struct MergeAndRenumber;

template<dts::u32... FirstIntegers, dts::u32... SecondIntegers>
struct MergeAndRenumber<
  IndexSequence<FirstIntegers...>,
  IndexSequence<SecondIntegers...>>
  : IndexSequence<
      FirstIntegers...,
      (sizeof...(FirstIntegers) + SecondIntegers)...>
{
};

} // namespace impl

template<dts::u32 Size>
struct MakeIndexSequence
  : impl::MergeAndRenumber<
      typename MakeIndexSequence<Size / 2>::type,
      typename MakeIndexSequence<Size - Size / 2>::type>
{
};

template<>
struct MakeIndexSequence<0> : IndexSequence<>
{
};

template<>
struct MakeIndexSequence<1> : IndexSequence<0>
{
};

} // namespace dts
