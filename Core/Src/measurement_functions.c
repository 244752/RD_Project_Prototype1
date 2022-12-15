#include "measurement_functions.h"

int size;
char disp_height_buff[10];
uint16_t v_height;
char buffer[10];
char buffer2[10];
float dist;
char tab[10] = {0};
int button_state = 1;

void screen_clean(float dist) {
	if ((int)dist<10){
		SSD1306_GotoXY (10, 15);
		SSD1306_Puts("  ", &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}else if ((int)dist>=10 && (int)dist<100){
		SSD1306_GotoXY (21, 15);
		SSD1306_Puts(" ", &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}
}

char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}

uint16_t meas_init(){
	uint16_t height_buff[100]={0};
	uint16_t filtered_h_buffer[100]={0};
	char progs_buffer[10]={0};
	v_height=0;
	size=0;



	SSD1306_Clear();
	SSD1306_GotoXY (12,0);
	SSD1306_Puts("Initialization", &Font_7x10, 1);
	SSD1306_GotoXY (12,20);
	SSD1306_Puts("Measurement...", &Font_7x10, 1);
	SSD1306_UpdateScreen(); //display

	for (int i=0; i<100; i++){ //measuring
		height_buff[i] = getDistance();
		SSD1306_GotoXY (40,35);
		sprintf(progs_buffer, "%i", i+1);
		SSD1306_Puts(progs_buffer, &Font_7x10, 1);
		SSD1306_GotoXY (60,35);
		SSD1306_Puts("/100", &Font_7x10, 1);
		SSD1306_UpdateScreen(); //display
	}

	for(int i=0; i<100; i++){ //filtering
		if (height_buff[i]<=height_buff[i+1]+6){
			filtered_h_buffer[size]=height_buff[i];
			size++;
		}
	}

	for(int i=0; i<size; i++){ //summing
			v_height = v_height + filtered_h_buffer[i];
	}

	v_height = v_height/size;
	program_step=1;
	SSD1306_Clear();
	return v_height;
}

void display_current_height(uint16_t v_height){
	SSD1306_GotoXY (0,0);
	SSD1306_Puts("Liquid Level:", &Font_7x10, 1);
	SSD1306_GotoXY (32, 15);
	SSD1306_Puts("cm  ", &Font_11x18, 1);

	if (licz_ms>(licz_pom+50)){
		licz_pom=licz_ms;
		dist = v_height - getDistance(); //why +2 ?

		if(dist<0){
			dist=0;
		}else if(dist>v_height){
			dist=v_height;
		}

		dtostrf(dist,2,2,tab);


		sprintf(buffer, "%i", (int)dist);

		SSD1306_GotoXY (0, 15);
		SSD1306_Puts(buffer, &Font_11x18, 1);
		SSD1306_UpdateScreen(); //display
		screen_clean(dist);

		button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
		if(button_state==0){
			program_step=0;

		}

	}

}
void display_vessel_height(uint16_t v_height){

	sprintf(disp_height_buff, "%i", (int)v_height);
	SSD1306_GotoXY (0,33);
	SSD1306_Puts("Vessel height:", &Font_7x10, 1);
	SSD1306_GotoXY (0, 43);
	SSD1306_Puts(disp_height_buff, &Font_11x18, 1);
	SSD1306_GotoXY (32, 43);
	SSD1306_Puts("cm  ", &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
}
