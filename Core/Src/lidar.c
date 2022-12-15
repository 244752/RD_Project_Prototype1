#include "lidar.h"

extern UART_HandleTypeDef huart1;

uint16_t getDistance(void) {
	unsigned char data[8] = {0};

	while(1)
	{
		unsigned char sign;
		HAL_UART_Receive(&huart1, &sign, 1, 10);
		if(sign == 0x59)
		{
			HAL_UART_Receive(&huart1, &sign, 1, 10);
			if(sign == 0x59)
			{
				data[0] = 0x59;
				data[1] = 0x59;
				for(int i = 2; i < 8; i++)
					 HAL_UART_Receive(&huart1, &data[i], 1, 10);
				return (data[3] << 8) | data[2];
			}
		}
	}
}
