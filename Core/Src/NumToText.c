/*
 * NumToText.c
 *
 *  Created on: 11 cze 2022
 *      Author: Marcin
 */
#include "NumToText.h"

void Num_To_Text(uint8_t num, char *numStr, uint8_t *digits)
{
	uint8_t cnt = 0;
	uint8_t tmp = num;
	while(num != 0)
	{
		if(num % 10 == 0)
		{
			numStr[2-cnt] = '0';
		}
		else if(num % 10 == 1)
		{
			numStr[2-cnt] = '1';
		}
		else if(num % 10 == 2)
		{
			numStr[2-cnt] = '2';
		}
		else if(num % 10 == 3)
		{
			numStr[2-cnt] = '3';
		}
		else if(num % 10 == 4)
		{
			numStr[2-cnt] = '4';
		}
		else if(num % 10 == 5)
		{
			numStr[2-cnt] = '5';
		}
		else if(num % 10 == 6)
		{
			numStr[2-cnt] = '6';
		}
		else if(num % 10 == 7)
		{
			numStr[2-cnt] = '7';
		}
		else if(num % 10 == 8)
		{
			numStr[2-cnt] = '8';
		}
		else if(num % 10 == 9)
		{
			numStr[2-cnt] = '9';
		}
		cnt++;
		num /= 10;
	}
	numStr[3] = '\r';
	numStr[4] = '\n';
	if(tmp > 0 && tmp <= 9)
	{
		for(uint8_t i = 0; i < 3; i++)
		{
			numStr[i] = numStr[i+2];
		}
	}
	else if(tmp >= 10 && tmp <= 99)
	{
		for(uint8_t i = 0; i < 4; i++)
		{
			numStr[i] = numStr[i+1];
		}
	}
	if(tmp == 0)
	{
		numStr[0] = '0';
		numStr[1] = '\r';
		numStr[2] = '\n';
		*digits = 1;
	}
	else
	{
		*digits = cnt;
	}
}
