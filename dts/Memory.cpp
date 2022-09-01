#include "Memory.hpp"

namespace dts {

void *memset(void *address, const int constant, const dts::u32 num)
{
    dts::u8 *ptr = reinterpret_cast<dts::u8 *>(address);
    for (dts::u32 i = 0; i < num; ++i) { ptr[i] = static_cast<dts::u8>(constant); }

    return ptr;
}

} // namespace dts
