#include "InterruptDescriptorTable.hpp"

namespace Idt {

DescriptorEntry descriptors[interrupts_count];


void init()
{
    DescriptorTable descriptor_table = { .size    = (sizeof(DescriptorEntry) * interrupts_count) - 1,
                                         .address = reinterpret_cast<dts::u32>(&descriptors) };

    Isr::init_gates();
    Pic::remap(0x20, 0x28);

    load_idt(&descriptor_table);
}

void insert_new_descriptor(dts::u32 index, dts::u32 base_address, dts::u16 segment_selector, dts::u8 flags)
{
    descriptors[index] = DescriptorEntry{ .base_low         = static_cast<dts::u16>((base_address & 0x0000FFFF)),
                                          .segment_selector = segment_selector,
                                          .reserved         = 0,
                                          .flags            = flags,
                                          .base_high = static_cast<dts::u16>((base_address & 0xFFFF0000) >> 16) };
}

} // namespace  Idt
