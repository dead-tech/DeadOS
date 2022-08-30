#include "GlobalDescriptorTable.hpp"

namespace Gdt {

static DescriptorEntry descriptors[descriptor_count];

void init()
{
    insert_null_descriptor(descriptors);
    DescriptorTable descriptor_table{ .size    = sizeof(DescriptorEntry) * descriptor_count - 1,
                                      .address = reinterpret_cast<dts::u32>(descriptors) };

    // This starts at 1 since we have alreacy inserted the null descriptor
    dts::u32 current_descriptor_index = 1;

    // Kernel Code Segment
    insert_new_descriptor(
      descriptors,
      current_descriptor_index++,
      0,
      0xFFFFFFFF,
      {
        .access                     = dts::to_underlying_type(AccessByteOptions::ACCESS),
        .readable_or_writeable      = dts::to_underlying_type(AccessByteOptions::READABLE_OR_WRITABLE),
        .conforming                 = dts::to_underlying_type(AccessByteOptions::NON_CONFORMING),
        .executable                 = dts::to_underlying_type(AccessByteOptions::EXECUTABLE_CODE_SEGMENT),
        .descriptor_type            = dts::to_underlying_type(AccessByteOptions::DATA_OR_CODE_SEGMENT),
        .descriptor_privilege_level = dts::to_underlying_type(AccessByteOptions::DPL_RING0),
        .present                    = dts::to_underlying_type(AccessByteOptions::PRESENT),
      },
      BIT32_OPERAND_SIZE_4KB_GRANULARITY);

    // Kenrel Data Segment
    insert_new_descriptor(
      descriptors,
      current_descriptor_index++,
      0,
      0xFFFFFFFF,
      {
        .access                     = dts::to_underlying_type(AccessByteOptions::ACCESS),
        .readable_or_writeable      = dts::to_underlying_type(AccessByteOptions::READABLE_OR_WRITABLE),
        .conforming                 = dts::to_underlying_type(AccessByteOptions::NON_CONFORMING),
        .executable                 = dts::to_underlying_type(AccessByteOptions::NON_EXECUTABLE_DATA_SEGMENT),
        .descriptor_type            = dts::to_underlying_type(AccessByteOptions::DATA_OR_CODE_SEGMENT),
        .descriptor_privilege_level = dts::to_underlying_type(AccessByteOptions::DPL_RING0),
        .present                    = dts::to_underlying_type(AccessByteOptions::PRESENT),
      },
      BIT32_OPERAND_SIZE_4KB_GRANULARITY);

    load_gdt(&descriptor_table);

    debug("GDT loaded!");
}

void insert_new_descriptor(
  DescriptorEntry *descriptors,
  const dts::u32   index,
  const dts::u32   base_address,
  const dts::u32   limit,
  const AccessByte access,
  const dts::u8    flags)
{
    descriptors[index] = DescriptorEntry{ .limit_low   = static_cast<dts::u16>(limit & 0xffff),
                                          .base_low    = static_cast<dts::u16>(base_address & 0xffffff),
                                          .access      = access,
                                          .limit_high  = static_cast<dts::u8>((limit >> 16) & 0xf),
                                          .a           = 0, // This is reserved for the system (must be zero)
                                          .long_mode   = 0, // This is always zero in 32bit protected mode
                                          .size        = static_cast<dts::u8>((flags & 0x3) & 0x1),
                                          .granularity = static_cast<dts::u8>(((flags & 0x3) & 0x2) >> 1),
                                          .base_high   = static_cast<dts::u8>((base_address >> 24) & 0xffff) };
}

void insert_null_descriptor(DescriptorEntry *descriptors)
{
    insert_new_descriptor(descriptors, 0, 0, 0, { 0, 0, 0, 0, 0, 0, 0 }, BIT32_OPERAND_SIZE_4KB_GRANULARITY);
}

} // namespace Gdt
