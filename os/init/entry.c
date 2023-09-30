
#include "types.h"
#include "console.h"
#include "common.h"

extern uint16_t *video_memory;

int kern_entry()
{
	console_clear();	
	console_write("Hello World Test\n");


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

	
	for(int i=0;i<100;i++)
	{
		console_put_dec_color(i, rc_black, rc_white);
		if(i%16 != 0)
			console_write("\t");
		else
			console_write("\n");
	}

	return 0;
}