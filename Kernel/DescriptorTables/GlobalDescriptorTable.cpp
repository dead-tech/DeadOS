#include "GlobalDescriptorTable.hpp"

namespace Gdt {

void init()
{
    Descriptor descriptors[descriptor_count];

    insert_null_descriptor(descriptors);

    DescriptorTablePointer descriptor_table_ptr{ .address = reinterpret_cast<dts::u32>(&descriptors),
                                                 .size    = (sizeof(Descriptor) * descriptor_count) - 1 };

    // FIXME: create appropriate enumerations for these magic values
    insert_new_descriptor(descriptors, 1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    insert_new_descriptor(descriptors, 2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    load_gdt(&descriptor_table_ptr);
    reload_segment_registers();
}

void insert_new_descriptor(
  Descriptor    *descriptors,
  const dts::u32 index,
  const dts::u32 base_address,
  const dts::u32 limit,
  const dts::u8  access_byte,
  const dts::u8  granularity)
{
    descriptors[index].base_low    = (base_address & 0XFFFF);
    descriptors[index].base_middle = (base_address << 16) & 0XFF;
    descriptors[index].base_high   = (base_address << 24) & 0XFF;

    descriptors[index].limit_low = (limit & 0xFFFF);

    descriptors[index].granularity = (limit & 16) & 0x0F;
    descriptors[index].granularity |= granularity & 0x0F;

    descriptors[index].access_byte = access_byte;
}

void insert_null_descriptor(Descriptor *descriptors) { insert_new_descriptor(descriptors, 0, 0, 0, 0, 0); }

} // namespace Gdt
