#include "common.h"
#include "console.h"

#define DISPLAY_SZ_X	80
#define DISPLAY_SZ_Y	25

#define CURSOR_LOCATION_H_REG	0xE
#define CURSOR_LOCATION_L_REG	0xF


static uint16_t *video_memory = (uint16_t *)0xB8000;

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;


/* 
 * Each character composit by two byte, text byte & color byte.
 * ----------------------------------------------------------------
 * |  Back Color   |  Fore Color   |           Word               |
 * ----------------------------------------------------------------
 * | K | R | G | B | I | R | G | B |         text Byte            |
 * ----------------------------------------------------------------
 * 
 */

// move cursor to current point(x,y)
static void move_cursor()
{
	uint16_t cursorPos = cursor_y*DISPLAY_SZ_X + cursor_x;
	
	//cursor high address
	outb(0x3d4, CURSOR_LOCATION_H_REG);
	outb(0x3d5, cursorPos>>8);
	
	//cursor low address
	outb(0x3d4, CURSOR_LOCATION_L_REG);
	outb(0x3d5, cursorPos);
}

// scroll to next line, if full
static void scroll()
{
	uint16_t color_byte = (rc_black<<4) | (rc_white & 0xf);
	uint16_t blank = (color_byte<<8) | (0x20); //0x20: space
	
	//if cur_y > y_max_25, then scroll diplay: 25->24->23 ->...->1
	if(cursor_y >= DISPLAY_SZ_Y)
	{
		int i,j;
		for(j=0;j<DISPLAY_SZ_Y-1;j++)
		{
			//for(i=0;i<DISPLAY_SZ_X;i++)
			//{
			//	video_memory[i+j*80] = video_memory[i+(j+1)*80];
			//}
			memcpy(&video_memory[(j)*80], &video_memory[(j+1)*80], 80*2);
		}
		
		for(i=0;i<DISPLAY_SZ_X;i++)
		{
			video_memory[(DISPLAY_SZ_Y-1)*DISPLAY_SZ_X+i] = blank;
		}
		
		cursor_y = 24;
	}
}

// clear console
void console_clear()
{
	uint16_t color_byte = (rc_black<<4) | (rc_white & 0xf);
	uint16_t blank = (color_byte<<8) | (0x20); //0x20: space
	int i;
	
	for(i=0;i < DISPLAY_SZ_X*DISPLAY_SZ_Y;i++)
	{
		video_memory[i] = blank;
	}
	
	cursor_x=0;
	cursor_y=0;
	move_cursor();
}


// putc console with text color, bg color
void console_putc_color(char c, real_color_t bg_color, real_color_t fg_color)
{
	if('\n' == c){
		cursor_y++;
		cursor_x=0;
	}else if('\r' == c){
		cursor_x=0;
	}else if(0x9 == c){
		//tab key: 0x9
		cursor_x = (cursor_x+4) & ~(4-1);
	}else if(0x8 == c){
		// backspace key: 0x8
		uint16_t cursorPos = cursor_y*DISPLAY_SZ_X + cursor_x;
		uint16_t color_byte = (rc_black<<4) | (rc_white & 0xf);
		uint16_t blank = (color_byte<<8) | (0x20); //0x20: space
		video_memory[cursorPos] = blank;
		cursor_x--;
	}else if(c >= ' '){	

		uint16_t cursorPos = cursor_y*DISPLAY_SZ_X + cursor_x;
		uint8_t  content_color = (bg_color<<4) | (fg_color & 0xf);
		uint16_t content = (content_color<<8) | c;
		
		//general string
		video_memory[cursorPos] = content;
		cursor_x++;
	}
	

	//if cur_x > x_max_80, then move to next line
	if(cursor_x >= DISPLAY_SZ_X)
	{
		cursor_x = 0;
		cursor_y++;
	}
	
	//update cursor position
	scroll();

	move_cursor();
}

// write string console (with default text color, bg color)
void console_write(char *cstr)
{
	while(*cstr)
	{
		console_putc_color(*cstr++, rc_black, rc_white);
	}
}

// write string with text color, bg color
void console_write_color(char *cstr, real_color_t bg_color, real_color_t fg_color)
{
	while(*cstr)
	{
		console_putc_color(*cstr++, bg_color, fg_color);
	}
}

// put hex with text color, bg color
void console_put_hex_color(uint32_t n, real_color_t bg_color, real_color_t fg_color)
{
	console_write_color("0x", bg_color, fg_color);
	int i=0,b;
	
	uint32_t l = n;
	int tmp;
	int nZero=1;
	
	for(b=(32-4);b>=0;b-=4)
	{
		tmp = (l >> b) & 0xf;
		
		if((0 == tmp) && nZero){
			continue;
		}
		
		nZero = 0;
		if(tmp > 10){
			console_putc_color(tmp-10+'a', bg_color, fg_color);
		}else{
			console_putc_color(tmp+'0', bg_color, fg_color);
		}
	}
	
	//update cursor position
	scroll();
}

// put decimal with text color, bg color
void console_put_dec_color(int32_t n, real_color_t bg_color, real_color_t fg_color)
{
	if(0 == n){
		console_putc_color('0', bg_color, fg_color);
		return;
	}
	
	int32_t l = n;
	char c[32];
	int i=0;
	int max_nz=0;
	
	while(i<32)
	{
		c[i] = '0' + (l % 10);
		l /= 10;
		
		if('0' != c[i]){
			max_nz = i;
		}
		
		i++;
	}
	
	for(i=max_nz;i>=0;i--)
		console_putc_color(c[i], bg_color, fg_color);
	
	//update cursor position
	scroll();
}
