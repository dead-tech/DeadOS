#pragma once

#include <dts/Types.hpp>

#include "../Io/Io.hpp"

namespace Pic {

constexpr static auto MASTER_PIC         = 0x20;
constexpr static auto MASTER_PIC_COMMAND = MASTER_PIC;
constexpr static auto MASTER_PIC_DATA    = MASTER_PIC + 1;

constexpr static auto SLAVE_PIC         = 0xA0;
constexpr static auto SLAVE_PIC_COMMAND = SLAVE_PIC;
constexpr static auto SLAVE_PIC_DATA    = SLAVE_PIC + 1;

constexpr static auto END_OF_INTERRUPT = 0x20;

constexpr static auto ICW1_ICW4           = 0x01;
constexpr static auto ICW1_SINGLE         = 0x02;
constexpr static auto ICW1_CALL_INTERVAL4 = 0x04;
constexpr static auto ICW1_LEVEL          = 0x08;
constexpr static auto ICW1_INIT           = 0x010;

constexpr static auto ICW4_8086                 = 0x01;
constexpr static auto ICW4_AUTO                 = 0x02;
constexpr static auto ICW4_BUFFERED_SLAVE       = 0x08;
constexpr static auto ICW4_BUFFERED_MASTER      = 0x0C;
constexpr static auto ICW4_SPECIAL_FULLY_NESTED = 0x10;

void send_end_of_interrupt(dts::u8 irq, dts::u8 master_pic_irq_offset);
void remap(dts::u32 master_offset, dts::u32 slave_offset);

} // namespace Pic
