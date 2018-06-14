#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <string.h>
#include "struct.h"
#include "charset.h"
#include "ansi.h"
#include "timer.h"
#include "graphics.h"

void initDisplay(uint8_t *buffer);
void LCD_Printer(struct game_state_t* gs);
void lcd_write_string(uint8_t *buffer, char *text, uint8_t slice, uint8_t line);
void lcd_updateline(uint8_t *buffer, uint8_t line);
void lcd_update(uint8_t *buffer);

#endif /*_DISPLAY_H_*/
