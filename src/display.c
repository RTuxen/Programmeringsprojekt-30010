#include "display.h"

void initDisplay(uint8_t *buffer){
    memset(buffer, 0x00, 512); // Sets each element of the buffer to 0xAA
    lcd_push_buffer(buffer);
}

void LCD_Printer(struct game_state_t* gs){ // Prints game information on LCD
    uint16_t val1 = gs->currentlevel, val2 = gs->lives, val3 = gs->points;
    char str1[30], str2[30], str3[30];
    sprintf(str1, "Level   = %4d", val1);
    sprintf(str2, "Lives   = %4d", val2);
    sprintf(str3, "Points  = %4d", val3);
    lcd_write_string(gs->buffer, str2, 1, 1);
    lcd_write_string(gs->buffer, str3, 1, 2);
    lcd_write_string(gs->buffer, str1, 1, 0);
}

void lcd_write_string(uint8_t *buffer, char *text, uint8_t slice, uint8_t line){ //Writes string on LCD. Slice [0,128] and Line[0,3]
    uint8_t textlenght = strlen(text);
    int8_t i,j;
    int16_t k =slice+line*128-1;


    for (i = 0; i< textlenght; i++){
            for (j=0; j <= 4; j++){
                if (7*i+k+j >= 128*line+128) {
                    break;
                }
                buffer[7*i+k+j]= character_data[text[i]-0x20][j];
            }
    }
    lcd_push_buffer(buffer);
}
