#pragma once

#include "types.h"

#define FRAMEBUFFER 0xB8000
#define CRCT_CMD_PORT 0x3D4
#define CRCT_DATA_PORT 0x3D5
#define CURSOR_POS_HIGH_BYTE_CMD 0x0E
#define CURSOR_POS_LOW_BYTE_CMD 0x0F

void write_char_to_frame_buffer(uint8_t letter, uint16_t row, uint16_t col, enum vga_color text_color, enum vga_color bg_color);
void move_cursor(uint16_t pos);
