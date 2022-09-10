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

using TrueType  = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;

template<typename T>
struct IsEnum : public IntegralConstant<bool, __is_enum(T)>
{
};

template<typename T>
struct IsIntegralHelper : public FalseType
{
};

template<>
struct IsIntegralHelper<bool> : public TrueType
{
};

template<>
struct IsIntegralHelper<char> : public TrueType
{
};

template<>
struct IsIntegralHelper<signed char> : public TrueType
{
};

template<>
struct IsIntegralHelper<unsigned char> : public TrueType
{
};

template<>
struct IsIntegralHelper<short> : public TrueType
{
};

template<>
struct IsIntegralHelper<unsigned short> : public TrueType
{
};

template<>
struct IsIntegralHelper<int> : public TrueType
{
};


template<>
struct IsIntegralHelper<unsigned int> : public TrueType
{
};

template<>
struct IsIntegralHelper<long> : public TrueType
{
};

template<>
struct IsIntegralHelper<unsigned long> : public TrueType
{
};

template<>
struct IsIntegralHelper<long long> : public TrueType
{
};

template<>
struct IsIntegralHelper<unsigned long long> : public TrueType
{
};

template<typename T>
struct IsIntegral : public IsIntegralHelper<RemoveCVT<T>>
{
};

template<typename T>
using IsIntegralV = typename IsIntegral<T>::value;

template<typename T>
concept IsIntegralC = IsIntegral<T>::value;

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

template<typename T>
struct IsLValueReference : public FalseType
{
};

template<typename T>
struct IsLValueReference<T &> : public TrueType
{
};

template<typename T>
using IsLValueReferenceV = typename IsLValueReference<T>::value;

template<typename T>
using IsLValueReferenceT = typename IsLValueReference<T>::type;

template<typename T, typename U>
struct IsSame : public FalseType
{
};

template<typename T>
struct IsSame<T, T> : public TrueType
{
};

template<typename T, typename U>
inline constexpr bool IsSameV = false;

template<typename T>
inline constexpr bool IsSameV<T, T> = true;

} // namespace dts
