
#include "types.h"
#include "console.h"
#include "common.h"
#include "debug.h"

interrupt_handler_t isr3_handler(pt_regs *regs)
{
	printk_color(rc_black, rc_green, "isr3_handler\n");
}

int kern_entry()
{
	console_clear();
	init_debug();
	init_gdt();
	init_idt();
	
	console_write("Hello World Test\n");
	//panic("test");
	
	register_interrupt_handler(3, isr3_handler);
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

#if 0
	for(int i=0;i<100;i++)
	{
		console_put_dec_color(i, rc_black, rc_white);
		console_write("\n");
	}
	console_put_dec_color(101, rc_black, rc_white);
	console_write("Hello World Test\n");
#endif
#if 0
	console_put_dec_color(432105678, rc_black, rc_white);
	console_write("\n");
	
	console_put_dec_color(50607080, rc_black, rc_white);
	console_write("\n");
#endif

#if 0	
	for(int i=0;i<100;i++)
	{
		console_put_dec_color(i, rc_black, rc_white);
		if(i%16 != 0)
			console_write("\t");
		else
			console_write("\n");
	}
#endif

	return 0;
}
