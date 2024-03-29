#ifndef KERNEL_ARCH_x86_MMU_H
#define KERNEL_ARCH_x86_MMU_H

#include <kernel/stdint.h>
#include <kernel/arch/x86/isr.h>

#define PAGE_SIZE 1024
#define FRAME_SIZE 0x1000
#define RAM_SIZE 0x10000000

typedef struct page
{
    uint32_t present	: 1;	/* Page present in memory */
    uint32_t rw		: 1;	/* Read-only if clear, readwrite if set */
    uint32_t user	: 1;	/* Supervisor level only if clear */
    uint32_t accessed	: 1;	/* Has the page been accessed since last refresh? */
    uint32_t dirty	: 1;	/* Has the page been written to since last refresh? */
    uint32_t unused	: 7;	/* Amalgamation of unused and reserved bits */
    uint32_t frame	: 20;	/* Frame address (shifted right 12 bits) */
} page_t;

typedef struct page_table
{
    page_t pages[PAGE_SIZE];
} page_table_t;

typedef struct page_directory
{
    /* Array of pointers to pagetables. */
    page_table_t *tables[PAGE_SIZE];
    /* Array of pointers to the pagetables above, but
    *  gives their *physical* location, for loading
    *  into the CR3 register. */
    uint32_t tablesPhysical[PAGE_SIZE];
    /* The physical address of tablesPhysical. This comes
    *  into play when we get our kernel heap allocated
    *  and the directory may be in a different location in
    *  virtual memory. */
    uint32_t physicalAddr;
} page_directory_t;

/* Sets up the environment, page directories etc and
*  enables paging. */
void mmu_init(void);

/* Causes the specified page directory to be loaded into the
*  CR3 register. */
void switch_page_directory(page_directory_t *new);

/* Retrieves a pointer to the page required.
*  If make == 1, if the page-table in which this page
*  should reside isn't created, create it! */
page_t *get_page(uint32_t address, int32_t make, page_directory_t *dir);

/* Handler for page faults */
void page_fault(registers_t *regs);

/* Manage frames */
void alloc_frame(page_t *page, int32_t is_kernel, int32_t is_writeable);
void free_frame(page_t *page);

/* Makes a copy of a page directory */
page_directory_t *clone_directory(page_directory_t *src);

/* Physically copy the data across. This function is in process.s */
extern void copy_page_physical(uint32_t, uint32_t);

#endif
