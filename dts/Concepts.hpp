#pragma once

#include "TypeTraits.hpp"

namespace dts {

template<typename Container>
concept IterableContainerC = requires(const Container &container)
{
    {
        container.cbegin()
        } -> SameAs<typename Container::ConstIterator>;
    {
        container.cend()
        } -> SameAs<typename Container::ConstIterator>;
    {
        container.begin()
        } -> SameAs<typename Container::Iterator>;
    {
        container.end()
        } -> SameAs<typename Container::Iterator>;
};

} // namespace dts
