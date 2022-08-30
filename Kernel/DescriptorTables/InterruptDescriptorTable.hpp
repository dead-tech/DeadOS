#pragma once

#include <dts/Types.hpp>

#include "../Io/Io.hpp"
#include "../ProgrammableInterruptController/ProgrammableInterruptController.hpp"
#include "../Screen/Framebuffer.hpp"
#include "ISRGates.hpp"

namespace Idt {

constexpr static dts::u16 interrupts_count = 256;

enum class DescriptorOptions : dts::u8
{
    // G - Gate Type (bits 40 - 43)
    TASK_GATE            = 0x5,
    BIT16_INTERRUPT_GATE = 0x6,
    BIT16_TRAP_GATE      = 0x7,
    BIT32_INTERRUPT_GATE = 0xE,
    BIT32_TRAP_GATE      = 0xF,

    // D - DPL - Descriptor Privilege Level (bits 45 - 46)
    DPL_RING0 = 0,
    DPL_RING1 = 1,
    DPL_RING2 = 2,
    DPL_RING3 = 3,

    // P - Present Bit
    NOT_PRESENT = 0,
    PRESENT     = 1
};

struct [[gnu::packed]] FlagsByte
{
    dts::u8 gate_type : 4;
    dts::u8 : 1;
    dts::u8 descriptor_privilege_level : 2;
    dts::u8 present : 1;
};

struct [[gnu::packed]] DescriptorEntry
{
    dts::u16 base_low : 16;
    dts::u16 segment_selector : 16;
    dts::u8  reserved : 8;
    dts::u8  flags;
    dts::u16 base_high : 16;
};

struct [[gnu::packed]] DescriptorTable
{
    dts::u16 size;
    dts::u32 address;
};

void init();

void insert_new_descriptor(dts::u32 index, dts::u32 base_address, dts::u16 segment_selector, dts::u8 flags);

extern "C" void load_idt(DescriptorTable *descriptor_table_ptr);
} // namespace Idt
