#pragma once

#include <dts/Types.hpp>
#include <dts/TypeTraits.hpp>

#include "../Io/SerialPort.hpp"

namespace Gdt {

constexpr static dts::u8 descriptor_count = 3;

enum class AccessByteOptions : dts::u8
{
    // P - DPL - S - E - DC - RW - A

    // P - present bit
    NOT_PRESENT = 0,
    PRESENT     = 1,

    // DPL - Descriptor Privilege Level
    DPL_RING0 = 0,
    DPL_RING1 = 1,
    DPL_RING2 = 2,
    DPL_RING3 = 3,

    // S - Descriptor Type Bit
    SYSTEM_SEGMENT       = 0,
    DATA_OR_CODE_SEGMENT = 1,

    // E - Executable Bit
    NON_EXECUTABLE_DATA_SEGMENT = 0,
    EXECUTABLE_CODE_SEGMENT     = 1,

    // D - Direction Bit
    DIRECTION_GROW_UP   = 0,
    DIRECTION_GROW_DOWN = 1,

    // C - Conforming Bit
    NON_CONFORMING = 0,
    CONFORMING     = 1,

    // RW - Readable or writable (depending on the segment)
    NON_READABLE_OR_WRITABLE = 0,
    READABLE_OR_WRITABLE     = 1,

    // A - Access Bit (left to the CPU)
    ACCESS = 0
};

enum class FlagsOptions : dts::u8
{
    // G - DB - L - Reserved

    // G - Granularity Bit
    GRANULARITY_BYTE = 0,
    GRANULARITY_4KB  = 1,

    // DB - Size flag
    BIT16_PROTECTED_MODE_SEGMENT = 0,
    BIT32_PROTECTED_MODE_SEGMENT = 1,

    // L - Long Mode
    NO_LONG_MODE = 0,
    LONG_MODE    = 1
};

struct [[gnu::packed]] AccessByte
{
    dts::u8 access : 1;
    dts::u8 readable_or_writeable : 1;
    dts::u8 conforming : 1;
    dts::u8 executable : 1;
    dts::u8 descriptor_type : 1;
    dts::u8 descriptor_privilege_level : 2;
    dts::u8 present : 1;
};

struct [[gnu::packed]] DescriptorEntry
{
    dts::u16   limit_low : 16;
    dts::u32   base_low : 24;
    AccessByte access;
    dts::u8    limit_high : 4;
    dts::u8    a : 1;
    dts::u8    long_mode : 1;
    dts::u8    size : 1;
    dts::u8    granularity : 1;
    dts::u8    base_high : 8;
};

struct [[gnu::packed]] DescriptorTable
{
    dts::u16 size;
    dts::u32 address;
};

static constexpr auto BIT32_OPERAND_SIZE_4KB_GRANULARITY = 0x3;

void init();

void insert_new_descriptor(
  DescriptorEntry *descriptors,
  const dts::u32   index,
  const dts::u32   base_address,
  const dts::u32   limit,
  const AccessByte access,
  const dts::u8    flags);

void insert_null_descriptor(DescriptorEntry *descriptors);

extern "C" void load_gdt(DescriptorTable *descriptor_table_ptr);

} // namespace Gdt
