#pragma once

#include <dts/Types.hpp>

namespace Gdt {

constexpr static dts::u8 descriptor_count = 3;

struct [[gnu::packed]] DescriptorTablePointer
{
    dts::u32 address;
    dts::u16 size;
};

struct [[gnu::packed]] Descriptor
{
    dts::u16 limit_low;
    dts::u16 base_low;
    dts::u8  base_middle;
    dts::u8  access_byte;
    dts::u8  granularity;
    dts::u8  base_high;
};

void init();

void insert_new_descriptor(
  Descriptor    *descriptors,
  const dts::u32 index,
  const dts::u32 base_address,
  const dts::u32 limit,
  const dts::u8  access_byte,
  const dts::u8  granularity);

void insert_null_descriptor(Descriptor *descriptors);

extern "C" void load_gdt(DescriptorTablePointer *descriptor_table_ptr);
extern "C" void reload_segment_registers();

} // namespace Gdt
