#include "interrupt.h"
#include "debug.h"
#include "common.h"

void init_int8295a()
{
	/* icw1 */
	outb( 0x20, 0x11 ); /* master port A */
	outb( 0xA0, 0x11 ); /* slave port A */

	/* icw2 */
	outb( 0x21, 0x20 ); /* master offset of 0x20 in the IDT */
	outb( 0xA1, 0x28 ); /* slave offset of 0x28 in the IDT */

	/* icw3 */
	outb( 0x21, 0x04 ); /* slaves attached to IR line 2 */
	outb( 0xA1, 0x02 ); /* this slave in IR line 2 of master */

	/* icw4 */
	outb( 0x21, 0x01 ); /* set as master */
	outb( 0xA1, 0x01 ); /*set as slave */

}

void int8295a_send_eoi(int nr)
{
	/* Send EOI to both master and slave */
	if(nr >= 40){
		outb( 0xA0, 0x20 ); /* slave PIC */
	}
	
	outb( 0x20, 0x20 ); /* master PIC */
}