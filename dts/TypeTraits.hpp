#pragma once

namespace dts {

template<typename T>
struct RemoveCV
{
    using type = T;
};

template<typename T>
struct RemoveCV<const T>
{
    using type = T;
};

template<typename T>
struct RemoveCV<volatile T>
{
    using type = T;
};

template<typename T>
struct RemoveCV<const volatile T>
{
    using type = T;
};

template<typename T>
using RemoveCVT = typename RemoveCV<T>::type;

template<typename T, T v>
struct IntegralConstant
{
    constexpr static T value = v;
    using value_type         = T;
    using type               = IntegralConstant<T, v>;
    constexpr            operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template<typename T>
struct IsEnum : public IntegralConstant<bool, __is_enum(T)>
{
};

template<typename T>
using IsEnumV = typename IsEnum<T>::value;

template<typename T>
concept IsEnumC = IsEnum<T>::value;

template<IsEnumC T>
struct UnderlyingType
{
#if defined(__clang__)
    using type = __underlying_type(T);
#elif defined(__GNUC__) || defined(__GNUG__)
    using type = __underlying_type(T);
#elif defined(MSVC_VER)
    UNIMPLEMENTED;
#endif
};

template<typename T>
using UnderlyingTypeT = typename UnderlyingType<T>::type;

template<IsEnumC Enum>
constexpr static auto to_underlying_type(Enum e)
{
    return static_cast<UnderlyingTypeT<Enum>>(e);
}

template<typename T>
struct RemoveReference
{
    using type = T;
};

template<typename T>
using RemoveReferenceT = typename RemoveReference<T>::type;

} // namespace dts
