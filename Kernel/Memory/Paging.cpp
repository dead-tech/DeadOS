#include "Paging.hpp"

namespace Mem {

[[noreturn]] static void
  page_fault_handler([[maybe_unused]] Isr::CpuRegisters regs)
{
    debug("[ERROR]: Page fault!");

    [[maybe_unused]] dts::u32 faulting_address = 0;
    asm volatile("mov %%cr2, %0" : "=r"(faulting_address));

    const bool present    = (regs.error_code & 0x1) == 0U;
    const bool read_write = (regs.error_code & 0x2) != 0U;
    const bool user       = (regs.error_code & 0x4) != 0U;
    const bool reserved   = (regs.error_code & 0x8) != 0U;

    if (present) { debug("\tpresent,"); }
    if (read_write) { debug("\tread_write,"); }
    if (user) { debug("\tuser,"); }
    if (reserved) { debug("\treserved,"); }

    panic();
}

static PageDirectory *current_page_directory = nullptr;

PageEntry *
  get_page_in_table(PageTable *page_table, const virtual_address address)
{
    if (page_table != nullptr) {
        return &page_table->entries[page_table_index(address)];
    } else {
        return nullptr;
    }
}

TableEntry *get_page_table_in_directory(
  PageDirectory        *page_directory,
  const virtual_address address
)
{
    if (page_directory != nullptr) {
        return &page_directory->tables[page_table_index(address)];
    } else {
        return nullptr;
    }
}

PageEntry *get_page(const virtual_address address)
{
    PageDirectory *page_directory = current_page_directory;

    TableEntry *entry = &page_directory->tables[page_directory_index(address)];
    auto       *table = reinterpret_cast<PageTable *>(get_frame(entry));
    PageEntry  *page  = &table->entries[page_table_index(address)];

    return page;
}

void *allocate_page(PageEntry *page)
{
    void *block = Mem::kmalloc_aligned(PAGE_SIZE);
    if (block != nullptr) {
        set_frame(page, reinterpret_cast<physical_address>(block));
        set_flag(page, dts::to_underlying_type(PageFlags::PRESENT));
    }

    debug("[MEM]: Page allocation!")

      return block;
}

void free_page(PageEntry *page)
{
    [[maybe_unused]] void *address = reinterpret_cast<void *>(get_frame(page));
    // if (address) { // implement free }
    clear_flag(page, dts::to_underlying_type(PageFlags::PRESENT));
}

bool set_paging_directory(PageDirectory *page_directory)
{
    if (page_directory == nullptr) { return false; }

    current_page_directory = page_directory;

    asm volatile("mov %0, %%cr3" : : "a"(current_page_directory));

    debug("[MEM]: Switched page directory!") return true;
}

void flush_tlb_entry(const virtual_address address)
{
    asm volatile("cli");
    asm volatile("invlpg (%0)" : : "r"(address));
    asm volatile("sti");
}

bool map_page(void *phys_address, void *virt_address)
{
    PageDirectory *page_directory = current_page_directory;

    TableEntry *entry =
      &page_directory
         ->tables[page_directory_index(reinterpret_cast<dts::u32>(virt_address)
         )];

    if ((*entry & dts::to_underlying_type(PageFlags::PRESENT)) != dts::to_underlying_type(PageFlags::PRESENT)) {
        auto *table = reinterpret_cast<PageTable *>(kmalloc_aligned(PAGE_SIZE));
        if (table == nullptr) { return false; } // EFAULT

        dts::memset(table, 0, sizeof(PageTable));

        TableEntry *new_entry = &page_directory->tables[page_directory_index(
          reinterpret_cast<dts::u32>(virt_address)
        )];

        set_flag(new_entry, dts::to_underlying_type(TableFlags::PRESENT));
        set_flag(new_entry, dts::to_underlying_type(TableFlags::READ_WRITE));
        set_frame(new_entry, reinterpret_cast<physical_address>(table));
    }

    auto *table = reinterpret_cast<PageTable *>(get_frame(entry));

    PageEntry *page =
      &table
         ->entries[page_table_index(reinterpret_cast<dts::u32>(virt_address))];

    set_flag(page, dts::to_underlying_type(PageFlags::PRESENT));
    set_frame(page, reinterpret_cast<dts::u32>(phys_address));

    debug("[MEM]: Mapped a page!") return true;
}

void unmap_page(void *virt_address)
{
    PageEntry *page = get_page(reinterpret_cast<dts::u32>(virt_address));

    set_frame(page, 0);
    set_flag(page, dts::to_underlying_type(PageFlags::PRESENT));

    debug("[MEM]: Un-Mapped a page!")
}

bool init_paging()
{
    auto *default_directory =
      reinterpret_cast<PageDirectory *>(kmalloc_aligned(PAGE_SIZE));
    if (default_directory == nullptr) { return false; } // EFAULT

    dts::memset(default_directory, 0, sizeof(PageDirectory));

    for (dts::u32 i = 0; i < 1024; ++i) { // NOLINT
        default_directory->tables[i] =
          0x02; // Supervisor, read/write, not present
    }

    // Page table for 0-4 MB
    auto *table = reinterpret_cast<PageTable *>(kmalloc_aligned(PAGE_SIZE));
    if (table == nullptr) { return false; } // EFAULT

    // Page table for 3GB+ higher half kernel
    auto *table3G = reinterpret_cast<PageTable *>(kmalloc_aligned(PAGE_SIZE));
    if (table3G == nullptr) { return false; } // EFAULT

    dts::memset(table, 0, sizeof(PageTable));
    dts::memset(table3G, 0, sizeof(PageTable));

    // Identity map first 4MB of memory
    for (dts::u32 i = 0, frame = 0x0, virt = 0x0; i < 1024;
         ++i, frame += PAGE_SIZE, virt += PAGE_SIZE) {
        PageEntry page = 0;
        set_flag(&page, dts::to_underlying_type(PageFlags::PRESENT));
        set_flag(&page, dts::to_underlying_type(PageFlags::READ_WRITE));
        set_frame(&page, frame);

        table3G->entries[page_table_index(virt)] = page;
    }

    // Map the kernel to address space 3GB+
    for (dts::u32 i = 0, frame = KERNEL_ADDRESS, virt = 0xC0000000; i < 1024;
         ++i, frame += PAGE_SIZE, virt += PAGE_SIZE) {
        PageEntry page = 0;
        set_flag(&page, dts::to_underlying_type(PageFlags::PRESENT));
        set_flag(&page, dts::to_underlying_type(PageFlags::READ_WRITE));
        set_frame(&page, frame);

        table->entries[page_table_index(virt)] = page;
    }

    TableEntry *entry =
      &default_directory->tables[page_directory_index(0xC0000000)];
    set_flag(entry, dts::to_underlying_type(TableFlags::PRESENT));
    set_flag(entry, dts::to_underlying_type(TableFlags::READ_WRITE));
    set_frame(entry, reinterpret_cast<physical_address>(table));

    TableEntry *entry3G =
      &default_directory->tables[page_directory_index(0x00000000)];
    set_flag(entry3G, dts::to_underlying_type(TableFlags::PRESENT));
    set_flag(entry3G, dts::to_underlying_type(TableFlags::READ_WRITE));
    set_frame(entry3G, reinterpret_cast<physical_address>(table3G));

    set_paging_directory(default_directory);

    // Set page fault handler
    Isr::register_interrupt_handler(14, &page_fault_handler);

    dts::u32 cr0 = 0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" ::"r"(cr0));

    debug("[MEM]: Paging enabled!") return true;
}

} // namespace Mem
