#include <stdio.h>
#include "fonts.h"
#include "ssd1306.h"

extern SSD1306_COLOR_t color;
extern FontDef_t Font_11x18;
extern void SSD1306_GotoXY(uint16_t x, uint16_t y);
extern char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);
extern int licz_ms, licz_wys, licz_pom;
extern uint16_t getDistance(void);
extern int program_step;

char *dtostrf (double val, signed char width, unsigned char prec, char *sout);
void screen_clean(float dist);
uint16_t meas_init();
void display_current_height(uint16_t v_height);
void display_vessel_height(uint16_t v_height);

