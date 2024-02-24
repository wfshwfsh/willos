#include "idt.h"
#include "timer.h"
#include "types.h"
#include "console.h"
#include "common.h"
#include "debug.h"

#define INT_TIMER 1

void isr3_handler(pt_regs *regs)
{
	printk_color(rc_black, rc_green, "isr3_handler\n");
}

int kern_entry()
{
	console_clear();
	init_debug();
	init_gdt();
	init_int8295a();//init 8259A
	init_idt();
	init_timer(200);
	

	//panic("test");

#if IDT
	register_interrupt_handler(3, isr3_handler);
	
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
#endif

#if INT_TIMER
	console_write("Hello World Test\n");
	//enable interrupt
	asm volatile ("sti");
#endif

	return 0;
}
