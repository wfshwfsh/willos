#include <multiboot.h>
#include <debug.h>
#include <elf.h>

static void print_stack_trace();
static elf_t kernel_elf;

// init Debug
void init_debug()
{
	kernel_elf = elf_from_multiboot(glb_mboot_ptr);
}

// print system register
void print_cur_status()
{
	
	
	
	
}

// Print function call stack
void print_stack_trace()
{
	uint32_t *ebp, *eip;
	
	while(ebp)
	{
		eip = ebp + 1;
		printk("    [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
		ebp = (uint32_t*) *ebp;
	}
	
}

// panic, print system info
void panic(const char *msg)
{
	printk("*** System panic: %s\n", msg);
	
	//print function call stack
	print_stack_trace();
	
	printk("***\n");
}



