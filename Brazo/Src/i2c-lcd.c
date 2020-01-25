
/** Put this in the src folder **/

#include "i2c-lcd.h"
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD  0x4E //0x7E//0x7e //0x4E//0x3f// 0x27 // cambiar

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}


void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_init (void)
{
	uint8_t i=0;
	HAL_Delay(100);
	for(i=0;i<3;i++)//sending 3 times: select 4-bit mode
	{
		lcd_send_cmd(0x03);
		HAL_Delay(45);
	}
	lcd_send_cmd (0x02);
	HAL_Delay(100);
	lcd_send_cmd (0x28);
	HAL_Delay(1);
	lcd_send_cmd (0x0c);
	HAL_Delay(1);
	lcd_send_cmd (0x80);
	HAL_Delay(1);
}

void lcd_send_number (uint8_t line , uint8_t row, uint32_t value)
{ //enviar variable
	if (line == 0 ){
		uint8_t line_x_y = 0x80 + row ;
		lcd_send_cmd(line_x_y);
		char lcdvalor[4];
		sprintf(lcdvalor, "%d", value);
		lcd_send_string(lcdvalor);
	}
	else if (line == 1 )
		{
			uint8_t line_x_y = 0x80 |( 0x40 + row) ;
			lcd_send_cmd(line_x_y);
			char lcdvalor[4];
			sprintf(lcdvalor, "%d", value);
			lcd_send_string(lcdvalor);
		}
	else if (line == 2 )
			{
				uint8_t line_x_y = 0x80 |( 0x14 + row) ;
				lcd_send_cmd(line_x_y);
				char lcdvalor[4];
				sprintf(lcdvalor, "%d", value);
				lcd_send_string(lcdvalor);
			}
	else if (line == 3 )
			{
				uint8_t line_x_y = 0x80 |( 0x54 + row) ;
				lcd_send_cmd(line_x_y);
				char lcdvalor[4];
				sprintf(lcdvalor, "%d", value);
				lcd_send_string(lcdvalor);
			}
}
void lcd_print_x_y(uint8_t line , uint8_t row, char *str )
{
	if (line == 0 ){
		uint8_t line_x_y = 0x80 + row ;
		lcd_send_cmd(line_x_y);
		while (*str) lcd_send_data (*str++);
	}
	else if (line == 1 )
		{
			uint8_t line_x_y = 0x80 |( 0x40 + row) ;
			lcd_send_cmd(line_x_y);
			while (*str) lcd_send_data (*str++);
		}
	else if (line == 2 )
			{
				uint8_t line_x_y = 0x80 |( 0x14 + row) ;
				lcd_send_cmd(line_x_y);
				while (*str) lcd_send_data (*str++);
			}
	else if (line == 3 )
			{
				uint8_t line_x_y = 0x80 |( 0x54 + row) ;
				lcd_send_cmd(line_x_y);
				while (*str) lcd_send_data (*str++);
			}

}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear (void)
{
  HAL_Delay(3);
	lcd_send_cmd (0x01);
	HAL_Delay(3);
}


void lcd_go_home (void)
{
	
}
void lcd_shift_left ( uint16_t delay)
{
	for(int i=1;i<16;i++)
	{
   	lcd_send_cmd(0x18);
		HAL_Delay(delay);
	}
	
}

void lcd_shift_right (uint16_t delay)
{
	for(int i=1;i<16;i++)
	{
		lcd_send_cmd(0x1C);
		HAL_Delay(delay);
	}
	
}
	
