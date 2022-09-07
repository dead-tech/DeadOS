#include "ISRGates.hpp"
namespace Isr {

void init_gates()
{
    // IRQ
    Idt::insert_new_descriptor(
      32, reinterpret_cast<dts::u32>(irq0), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      33, reinterpret_cast<dts::u32>(irq1), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      34, reinterpret_cast<dts::u32>(irq2), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      35, reinterpret_cast<dts::u32>(irq3), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      36, reinterpret_cast<dts::u32>(irq4), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      37, reinterpret_cast<dts::u32>(irq5), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      38, reinterpret_cast<dts::u32>(irq6), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      39, reinterpret_cast<dts::u32>(irq7), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      40, reinterpret_cast<dts::u32>(irq8), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      41, reinterpret_cast<dts::u32>(irq9), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      42, reinterpret_cast<dts::u32>(irq10), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      43, reinterpret_cast<dts::u32>(irq11), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      44, reinterpret_cast<dts::u32>(irq12), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      45, reinterpret_cast<dts::u32>(irq13), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      46, reinterpret_cast<dts::u32>(irq14), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      47, reinterpret_cast<dts::u32>(irq15), 0x08, 0x8E
    );

    // ISR
    Idt::insert_new_descriptor(0, reinterpret_cast<dts::u32>(isr0), 0x08, 0x8E);
    Idt::insert_new_descriptor(1, reinterpret_cast<dts::u32>(isr1), 0x08, 0x8E);
    Idt::insert_new_descriptor(2, reinterpret_cast<dts::u32>(isr2), 0x08, 0x8E);
    Idt::insert_new_descriptor(3, reinterpret_cast<dts::u32>(isr3), 0x08, 0x8E);
    Idt::insert_new_descriptor(4, reinterpret_cast<dts::u32>(isr4), 0x08, 0x8E);
    Idt::insert_new_descriptor(5, reinterpret_cast<dts::u32>(isr5), 0x08, 0x8E);
    Idt::insert_new_descriptor(6, reinterpret_cast<dts::u32>(isr6), 0x08, 0x8E);
    Idt::insert_new_descriptor(7, reinterpret_cast<dts::u32>(isr7), 0x08, 0x8E);
    Idt::insert_new_descriptor(8, reinterpret_cast<dts::u32>(isr8), 0x08, 0x8E);
    Idt::insert_new_descriptor(9, reinterpret_cast<dts::u32>(isr9), 0x08, 0x8E);
    Idt::insert_new_descriptor(
      10, reinterpret_cast<dts::u32>(isr10), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      11, reinterpret_cast<dts::u32>(isr11), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      12, reinterpret_cast<dts::u32>(isr12), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      13, reinterpret_cast<dts::u32>(isr13), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      14, reinterpret_cast<dts::u32>(isr14), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      15, reinterpret_cast<dts::u32>(isr15), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      16, reinterpret_cast<dts::u32>(isr16), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      17, reinterpret_cast<dts::u32>(isr17), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      18, reinterpret_cast<dts::u32>(isr18), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      19, reinterpret_cast<dts::u32>(isr19), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      20, reinterpret_cast<dts::u32>(isr20), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      21, reinterpret_cast<dts::u32>(isr21), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      22, reinterpret_cast<dts::u32>(isr22), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      23, reinterpret_cast<dts::u32>(isr23), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      24, reinterpret_cast<dts::u32>(isr24), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      25, reinterpret_cast<dts::u32>(isr25), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      26, reinterpret_cast<dts::u32>(isr26), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      27, reinterpret_cast<dts::u32>(isr27), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      28, reinterpret_cast<dts::u32>(isr28), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      29, reinterpret_cast<dts::u32>(isr29), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      30, reinterpret_cast<dts::u32>(isr30), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      31, reinterpret_cast<dts::u32>(isr31), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      48, reinterpret_cast<dts::u32>(isr48), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      49, reinterpret_cast<dts::u32>(isr49), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      50, reinterpret_cast<dts::u32>(isr50), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      51, reinterpret_cast<dts::u32>(isr51), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      52, reinterpret_cast<dts::u32>(isr52), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      53, reinterpret_cast<dts::u32>(isr53), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      54, reinterpret_cast<dts::u32>(isr54), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      55, reinterpret_cast<dts::u32>(isr55), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      56, reinterpret_cast<dts::u32>(isr56), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      57, reinterpret_cast<dts::u32>(isr57), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      58, reinterpret_cast<dts::u32>(isr58), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      59, reinterpret_cast<dts::u32>(isr59), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      60, reinterpret_cast<dts::u32>(isr60), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      61, reinterpret_cast<dts::u32>(isr61), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      62, reinterpret_cast<dts::u32>(isr62), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      63, reinterpret_cast<dts::u32>(isr63), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      64, reinterpret_cast<dts::u32>(isr64), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      65, reinterpret_cast<dts::u32>(isr65), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      66, reinterpret_cast<dts::u32>(isr66), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      67, reinterpret_cast<dts::u32>(isr67), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      68, reinterpret_cast<dts::u32>(isr68), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      69, reinterpret_cast<dts::u32>(isr69), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      70, reinterpret_cast<dts::u32>(isr70), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      71, reinterpret_cast<dts::u32>(isr71), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      72, reinterpret_cast<dts::u32>(isr72), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      73, reinterpret_cast<dts::u32>(isr73), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      74, reinterpret_cast<dts::u32>(isr74), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      75, reinterpret_cast<dts::u32>(isr75), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      76, reinterpret_cast<dts::u32>(isr76), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      77, reinterpret_cast<dts::u32>(isr77), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      78, reinterpret_cast<dts::u32>(isr78), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      79, reinterpret_cast<dts::u32>(isr79), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      80, reinterpret_cast<dts::u32>(isr80), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      81, reinterpret_cast<dts::u32>(isr81), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      82, reinterpret_cast<dts::u32>(isr82), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      83, reinterpret_cast<dts::u32>(isr83), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      84, reinterpret_cast<dts::u32>(isr84), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      85, reinterpret_cast<dts::u32>(isr85), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      86, reinterpret_cast<dts::u32>(isr86), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      87, reinterpret_cast<dts::u32>(isr87), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      88, reinterpret_cast<dts::u32>(isr88), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      89, reinterpret_cast<dts::u32>(isr89), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      90, reinterpret_cast<dts::u32>(isr90), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      91, reinterpret_cast<dts::u32>(isr91), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      92, reinterpret_cast<dts::u32>(isr92), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      93, reinterpret_cast<dts::u32>(isr93), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      94, reinterpret_cast<dts::u32>(isr94), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      95, reinterpret_cast<dts::u32>(isr95), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      96, reinterpret_cast<dts::u32>(isr96), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      97, reinterpret_cast<dts::u32>(isr97), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      98, reinterpret_cast<dts::u32>(isr98), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      99, reinterpret_cast<dts::u32>(isr99), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      100, reinterpret_cast<dts::u32>(isr100), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      101, reinterpret_cast<dts::u32>(isr101), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      102, reinterpret_cast<dts::u32>(isr102), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      103, reinterpret_cast<dts::u32>(isr103), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      104, reinterpret_cast<dts::u32>(isr104), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      105, reinterpret_cast<dts::u32>(isr105), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      106, reinterpret_cast<dts::u32>(isr106), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      107, reinterpret_cast<dts::u32>(isr107), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      108, reinterpret_cast<dts::u32>(isr108), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      109, reinterpret_cast<dts::u32>(isr109), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      110, reinterpret_cast<dts::u32>(isr110), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      111, reinterpret_cast<dts::u32>(isr111), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      112, reinterpret_cast<dts::u32>(isr112), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      113, reinterpret_cast<dts::u32>(isr113), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      114, reinterpret_cast<dts::u32>(isr114), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      115, reinterpret_cast<dts::u32>(isr115), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      116, reinterpret_cast<dts::u32>(isr116), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      117, reinterpret_cast<dts::u32>(isr117), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      118, reinterpret_cast<dts::u32>(isr118), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      119, reinterpret_cast<dts::u32>(isr119), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      120, reinterpret_cast<dts::u32>(isr120), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      121, reinterpret_cast<dts::u32>(isr121), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      122, reinterpret_cast<dts::u32>(isr122), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      123, reinterpret_cast<dts::u32>(isr123), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      124, reinterpret_cast<dts::u32>(isr124), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      125, reinterpret_cast<dts::u32>(isr125), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      126, reinterpret_cast<dts::u32>(isr126), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      127, reinterpret_cast<dts::u32>(isr127), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      128, reinterpret_cast<dts::u32>(syscall_common_handler), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      129, reinterpret_cast<dts::u32>(isr129), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      130, reinterpret_cast<dts::u32>(isr130), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      131, reinterpret_cast<dts::u32>(isr131), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      132, reinterpret_cast<dts::u32>(isr132), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      133, reinterpret_cast<dts::u32>(isr133), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      134, reinterpret_cast<dts::u32>(isr134), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      135, reinterpret_cast<dts::u32>(isr135), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      136, reinterpret_cast<dts::u32>(isr136), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      137, reinterpret_cast<dts::u32>(isr137), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      138, reinterpret_cast<dts::u32>(isr138), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      139, reinterpret_cast<dts::u32>(isr139), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      140, reinterpret_cast<dts::u32>(isr140), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      141, reinterpret_cast<dts::u32>(isr141), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      142, reinterpret_cast<dts::u32>(isr142), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      143, reinterpret_cast<dts::u32>(isr143), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      144, reinterpret_cast<dts::u32>(isr144), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      145, reinterpret_cast<dts::u32>(isr145), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      146, reinterpret_cast<dts::u32>(isr146), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      147, reinterpret_cast<dts::u32>(isr147), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      148, reinterpret_cast<dts::u32>(isr148), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      149, reinterpret_cast<dts::u32>(isr149), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      150, reinterpret_cast<dts::u32>(isr150), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      151, reinterpret_cast<dts::u32>(isr151), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      152, reinterpret_cast<dts::u32>(isr152), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      153, reinterpret_cast<dts::u32>(isr153), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      154, reinterpret_cast<dts::u32>(isr154), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      155, reinterpret_cast<dts::u32>(isr155), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      156, reinterpret_cast<dts::u32>(isr156), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      157, reinterpret_cast<dts::u32>(isr157), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      158, reinterpret_cast<dts::u32>(isr158), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      159, reinterpret_cast<dts::u32>(isr159), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      160, reinterpret_cast<dts::u32>(isr160), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      161, reinterpret_cast<dts::u32>(isr161), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      162, reinterpret_cast<dts::u32>(isr162), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      163, reinterpret_cast<dts::u32>(isr163), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      164, reinterpret_cast<dts::u32>(isr164), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      165, reinterpret_cast<dts::u32>(isr165), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      166, reinterpret_cast<dts::u32>(isr166), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      167, reinterpret_cast<dts::u32>(isr167), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      168, reinterpret_cast<dts::u32>(isr168), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      169, reinterpret_cast<dts::u32>(isr169), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      170, reinterpret_cast<dts::u32>(isr170), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      171, reinterpret_cast<dts::u32>(isr171), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      172, reinterpret_cast<dts::u32>(isr172), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      173, reinterpret_cast<dts::u32>(isr173), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      174, reinterpret_cast<dts::u32>(isr174), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      175, reinterpret_cast<dts::u32>(isr175), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      176, reinterpret_cast<dts::u32>(isr176), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      177, reinterpret_cast<dts::u32>(isr177), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      178, reinterpret_cast<dts::u32>(isr178), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      179, reinterpret_cast<dts::u32>(isr179), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      180, reinterpret_cast<dts::u32>(isr180), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      181, reinterpret_cast<dts::u32>(isr181), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      182, reinterpret_cast<dts::u32>(isr182), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      183, reinterpret_cast<dts::u32>(isr183), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      184, reinterpret_cast<dts::u32>(isr184), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      185, reinterpret_cast<dts::u32>(isr185), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      186, reinterpret_cast<dts::u32>(isr186), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      187, reinterpret_cast<dts::u32>(isr187), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      188, reinterpret_cast<dts::u32>(isr188), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      189, reinterpret_cast<dts::u32>(isr189), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      190, reinterpret_cast<dts::u32>(isr190), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      191, reinterpret_cast<dts::u32>(isr191), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      192, reinterpret_cast<dts::u32>(isr192), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      193, reinterpret_cast<dts::u32>(isr193), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      194, reinterpret_cast<dts::u32>(isr194), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      195, reinterpret_cast<dts::u32>(isr195), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      196, reinterpret_cast<dts::u32>(isr196), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      197, reinterpret_cast<dts::u32>(isr197), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      198, reinterpret_cast<dts::u32>(isr198), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      199, reinterpret_cast<dts::u32>(isr199), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      200, reinterpret_cast<dts::u32>(isr200), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      201, reinterpret_cast<dts::u32>(isr201), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      202, reinterpret_cast<dts::u32>(isr202), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      203, reinterpret_cast<dts::u32>(isr203), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      204, reinterpret_cast<dts::u32>(isr204), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      205, reinterpret_cast<dts::u32>(isr205), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      206, reinterpret_cast<dts::u32>(isr206), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      207, reinterpret_cast<dts::u32>(isr207), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      208, reinterpret_cast<dts::u32>(isr208), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      209, reinterpret_cast<dts::u32>(isr209), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      210, reinterpret_cast<dts::u32>(isr210), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      211, reinterpret_cast<dts::u32>(isr211), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      212, reinterpret_cast<dts::u32>(isr212), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      213, reinterpret_cast<dts::u32>(isr213), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      214, reinterpret_cast<dts::u32>(isr214), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      215, reinterpret_cast<dts::u32>(isr215), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      216, reinterpret_cast<dts::u32>(isr216), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      217, reinterpret_cast<dts::u32>(isr217), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      218, reinterpret_cast<dts::u32>(isr218), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      219, reinterpret_cast<dts::u32>(isr219), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      220, reinterpret_cast<dts::u32>(isr220), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      221, reinterpret_cast<dts::u32>(isr221), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      222, reinterpret_cast<dts::u32>(isr222), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      223, reinterpret_cast<dts::u32>(isr223), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      224, reinterpret_cast<dts::u32>(isr224), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      225, reinterpret_cast<dts::u32>(isr225), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      226, reinterpret_cast<dts::u32>(isr226), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      227, reinterpret_cast<dts::u32>(isr227), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      228, reinterpret_cast<dts::u32>(isr228), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      229, reinterpret_cast<dts::u32>(isr229), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      230, reinterpret_cast<dts::u32>(isr230), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      231, reinterpret_cast<dts::u32>(isr231), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      232, reinterpret_cast<dts::u32>(isr232), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      233, reinterpret_cast<dts::u32>(isr233), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      234, reinterpret_cast<dts::u32>(isr234), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      235, reinterpret_cast<dts::u32>(isr235), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      236, reinterpret_cast<dts::u32>(isr236), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      237, reinterpret_cast<dts::u32>(isr237), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      238, reinterpret_cast<dts::u32>(isr238), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      239, reinterpret_cast<dts::u32>(isr239), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      240, reinterpret_cast<dts::u32>(isr240), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      241, reinterpret_cast<dts::u32>(isr241), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      242, reinterpret_cast<dts::u32>(isr242), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      243, reinterpret_cast<dts::u32>(isr243), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      244, reinterpret_cast<dts::u32>(isr244), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      245, reinterpret_cast<dts::u32>(isr245), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      246, reinterpret_cast<dts::u32>(isr246), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      247, reinterpret_cast<dts::u32>(isr247), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      248, reinterpret_cast<dts::u32>(isr248), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      249, reinterpret_cast<dts::u32>(isr249), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      250, reinterpret_cast<dts::u32>(isr250), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      251, reinterpret_cast<dts::u32>(isr251), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      252, reinterpret_cast<dts::u32>(isr252), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      253, reinterpret_cast<dts::u32>(isr253), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      254, reinterpret_cast<dts::u32>(isr254), 0x08, 0x8E
    );
    Idt::insert_new_descriptor(
      255, reinterpret_cast<dts::u32>(isr255), 0x08, 0x8E
    );

    debug("Loaded 15 IRQs and 241 ISRs")
}

} // namespace Isr
