#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"

void isr_timer()
{
	static uint32_t tick=0;
	printk_color(rc_black, rc_red, "Tick: %d\n", tick++);
}

void init_timer(uint32_t frequency)
{
	int divisor=0;
	if(!frequency){
		divisor=(1193180/100);
	}else{
		divisor=(1193180/frequency);
	}
	
	// 1. register timer isr
	register_interrupt_handler(IRQ0, isr_timer);
	
	// 2. setup timer 
	// 2.1 set timer work mode (0x43,0x36)
	outb( 0x43, 0x36 );
	
	// 2.2 set timer freq low and high
	uint8_t	low  = (uint8_t)(divisor & 0xff);
	uint8_t	high = (uint8_t)((divisor >> 8)&0xff);
	
	outb( 0x43, low );
	outb( 0x43, high );
}


