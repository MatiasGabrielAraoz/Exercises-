#include "include/types.h"
#include "include/io.h"
#include "include/asm.h"


void write_char_to_frame_buffer(uint8_t letter, uint16_t row, uint16_t col, enum vga_color text_color, enum vga_color bg_color){
	volatile uint16_t *framebuffer = (volatile uint16_t*) FRAMEBUFFER;
	
	uint16_t bg_color_framebuffer = (0x000F & bg_color) << 12;
	uint16_t text_color_framebuffer = (0x000F & text_color) << 8; 
	uint16_t letter_framebuffer = (0x00FF & letter);

	framebuffer[col + row*80] = letter_framebuffer | text_color_framebuffer | bg_color_framebuffer;
}

void move_cursor(uint16_t pos) {
	uint16_t pos_low_byte = pos & 0x00FF;
	uint16_t pos_high_byte = (pos >> 8) & 0xFF;

	outb(CRCT_CMD_PORT, CURSOR_POS_HIGH_BYTE_CMD);
	outb(CRCT_CMD_PORT, pos_high_byte);

	outb(CRCT_CMD_PORT, CURSOR_POS_LOW_BYTE_CMD);
	outb(CRCT_CMD_PORT, pos_low_byte);

}
