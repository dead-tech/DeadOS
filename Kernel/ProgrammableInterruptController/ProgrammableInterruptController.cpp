#include "ProgrammableInterruptController.hpp"

namespace Pic {

void send_end_of_interrupt(dts::u8 irq, dts::u8 master_pic_irq_offset)
{
    if (irq >= master_pic_irq_offset + 8) { Io::outb(SLAVE_PIC_COMMAND, END_OF_INTERRUPT); }

    Io::outb(MASTER_PIC_COMMAND, END_OF_INTERRUPT);
}

void remap(dts::u32 master_offset, dts::u32 slave_offset)
{
    Io::outb(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
    Io::outb(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);

    Io::outb(MASTER_PIC_DATA, master_offset);
    Io::outb(SLAVE_PIC_DATA, slave_offset);

    Io::outb(MASTER_PIC_DATA, 4);
    Io::outb(SLAVE_PIC_DATA, 2);

    Io::outb(MASTER_PIC_DATA, ICW4_8086);
    Io::outb(SLAVE_PIC_DATA, ICW4_8086);

    Io::outb(MASTER_PIC_DATA, 0xfc); // Always have the timer and the keyboard interrupt enabled
    Io::outb(SLAVE_PIC_DATA, 0xff);

    debug("PIC remapped!")
}

} // namespace Pic
