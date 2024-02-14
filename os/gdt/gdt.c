
#include "gdt.h"

#define GDT_LENGTH 5
gdt_entry_t gdt_entries[GDT_LENGTH];

gdt_ptr_t gdt_ptr;


static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	int idx=num;
	gdt_entries[idx].limit_low = limit & 0xffff;
	gdt_entries[idx].base_low = base & 0xffff;
	gdt_entries[idx].base_middle = (base & 0xff0000) >> 16;
	gdt_entries[idx].access = access;
	gdt_entries[idx].granularity = (limit >> 16) & 0xf;
        gdt_entries[idx].granularity |= gran;
	gdt_entries[idx].base_high = (base & 0xff000000) >> 24;
}


void init_gdt()
{
	// 1. Set GDT
	// 1.1 set gdt.base
	// 1.2 set gdt.limit
	gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base  = (uint32_t)&gdt_entries;
	
	//set gdt entries
	gdt_set_gate(0, 0, 0, 0, 0);
	//set kernel
	gdt_set_gate(1, 0, 0xffffffff, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xCF);
	//set user seg.
	//gdt_set_gate(3, 0, 0xffffffff, 0xFA, 0xCF);
	//gdt_set_gate(4, 0, 0xffffffff, 0xF2, 0xCF);
	
	//set gdtr
	gdt_flush((uint32_t)&gdt_ptr);
}

