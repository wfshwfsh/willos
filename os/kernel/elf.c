
#include "common.h"
#include "string.h"
#include "debug.h"
#include "elf.h"


elf_t elf_from_multiboot(multiboot_t *mb)
{
	elf_t elf;
	int i;
	
	elf_section_header_t *sh = (elf_section_header_t*)mb->addr;
	printk("mb->flags = %x\n", mb->flags);
	printk("mb->num = %d\n", mb->num);
	printk("mb->size = %u\n", mb->size);
	printk("mb->addr = 0x%x\n", mb->addr);
	printk("mb->shndx = %u\n", mb->shndx);
	
	uint32_t shstrtab = sh[mb->shndx].addr;
	
	for(i=0;i<mb->num;i++)
	{
		const char *name = (const char*)(shstrtab + sh[i].name);
		if(strcmp(".strtab", name) == 0){
			elf.strtab = (const char*)sh[i].addr;
			elf.strtabsz = sh[i].size;
		}
		if(strcmp(".symtab", name) == 0){
			elf.symtab = (elf_symbol_t*)sh[i].addr;
			elf.symtabsz = sh[i].size;
		}
	}
	
	printk("elf.symtab = 0x%x\n", elf.symtab);
	printk("elf.symtabsz = %d\n", elf.symtabsz);
	printk("elf.strtab = 0x%x\n", elf.strtab);
	printk("elf.strtabsz = %d\n", elf.strtabsz);
	return elf;
}

const char *elf_lookup_symbol(uint32_t addr, elf_t *elf)
{
	int i;
	
	for(i=0;i < (elf->symtabsz/sizeof(elf_symbol_t));i++)
	{
		if(ELF32_ST_TYPE(elf->symtab[i].info) != 0x02/*SYM_WEAK*/)
		{
			continue;
		}
		
		if ( (addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size)) ) {
			return (const char *)((uint32_t)elf->strtab + elf->symtab[i].name);
		}
	}
	
	return NULL;
}