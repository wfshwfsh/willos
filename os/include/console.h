#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "types.h"



typedef enum real_color {
	
	rc_black=0,
	rc_blue,
	rc_green,
	rc_cyan,
	rc_red, 
	rc_magenta,
	rc_brown,
	rc_white, //7
	
	rc_dark_gray,
	rc_light_blue,
	rc_light_green,
	rc_light_cyan,
	rc_light_red, 
	rc_light_magenta,
	rc_light_brown,
	rc_light_white,
	
} real_color_t;


// clear console
void console_clear();

// putc console with text color, bg color
void console_putc_color(char c, real_color_t bg_color, real_color_t fg_color);

// write string console (with default text color, bg color)
void console_write(char *cstr);

// write string with text color, bg color
void console_write_color(char *cstr, real_color_t bg_color, real_color_t fg_color);

// put hex with text color, bg color
void console_put_hex_color(uint32_t n, real_color_t bg_color, real_color_t fg_color);

// put decimal with text color, bg color
void console_put_dec_color(int32_t n, real_color_t bg_color, real_color_t fg_color);




#endif