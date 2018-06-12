#include "display.h"

void initDisplay(uint8_t *buffer){
    memset(buffer, 0x00, 512); // Sets eah eleen of the buffer to 0xAA
    lcd_push_buffer(buffer);
}

 void LCD_Printer(uint8_t level, uint8_t lives, uint8_t points, uint8_t* buffer){
    uint16_t val1 = level+1, val2 = lives, val3 = points;
    char str1[30], str2[30], str3[30];
    sprintf(str1, "Level   = %4d", val1);
    sprintf(str2, "Lives   = %4d", val2);
    sprintf(str3, "Points  = %4d", val3);
    lcd_write_string(buffer, str1, 1, 0);
    lcd_write_string(buffer, str2, 1, 1);
    lcd_write_string(buffer, str3, 1, 2);
}

void lcd_write_string(uint8_t *buffer, char *text, uint8_t slice, uint8_t line){ //Antager slice [0,128] og line[0,3]
    uint8_t textlenght = strlens(text);
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

void lcd_updateline(uint8_t *buffer, uint8_t line){
    uint16_t n = line * 128;
    if (get_flag()){
        memmove(buffer + n, buffer + 1 + n, 127);
        buffer[127+n] = buffer[0 + n];
        lcd_push_buffer(buffer);
    }
}

void lcd_update(uint8_t *buffer){
    int8_t i = 0;
    uint16_t n;
    if (get_flag()){
        for (i = 0; i < 4; ++i) {
            n = i * 128;
            memmove(buffer + n, buffer + 1 + n, 127);
            buffer[127+n] = buffer[0 + n];
        }
        lcd_push_buffer(buffer);

    }
}
