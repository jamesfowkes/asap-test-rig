#ifndef _LCD_H_
#define _LCD_H_

char * lcd_get_test_number_line();

void lcd_write(const char * line1, const char * line2, const char * line3, const char * line4);
void lcd_write_P(const char * line1, const char * line2, const char * line3, const char * line4);

void lcd_write_line(const char * fmt, ...);
void lcd_write_line_P(const char * line);

#endif