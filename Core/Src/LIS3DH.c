/*
 * LIS3DH.c
 *
 *  Created on: Jun 30, 2021
 *      Author: Marcin
 */

#include "LIS3DH.h"


uint8_t getI2Caddr()
{
	return (0b0011000 | SAD0);
}

uint8_t setup()
{
	uint8_t reg1, reg2, reg3, reg4, reg5;
	//set low power mode 1 Hz, XYZ detection
	reg1 = CTRL_REG1_ODR1 | CTRL_REG1_LPEN | CTRL_REG1_ZEN | CTRL_REG1_YEN | CTRL_REG1_XEN;
	//high pass filter, leave it as it is (no filtering)
	//reg2 =
	//reg3 =
	writeregister8(REG_CTRL_REG1, reg1);
}

void writeData(uint8_t addr, const uint8_t *buf, size_t numBytes)
{
	if(numBytes > 1)
	{
		addr |= 0x80;	//wysyl kilku bajtow pod rzad - MSB = 1
	}
	HAL_I2C_Mem_Write(&hi2c1, (getI2Caddr()<<1), addr, 1, buf, numBytes, 100);
	//HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, Timeout);
}

void writeregister8(uint8_t addr, uint8_t val)
{
	writeData(addr,&val,sizeof(val));
}

void writeregister16(uint8_t addr, uint16_t val)
{
	uint8_t req[2];
	req[0] = val & 0xff;
	req[1] = val >> 8;

	writeData(addr, req, sizeof(req));
}

void readData(uint8_t addr, uint8_t *buf, size_t numBytes)
{
	if(numBytes > 1)
	{
			addr |= 0x80;	//wysyl kilku bajtow pod rzad - MSB = 1
	}
	HAL_I2C_Mem_Read(&hi2c1, (getI2Caddr()<<1), addr, 1, buf, numBytes, 100);
}

uint8_t readregister8(uint8_t addr)
{
	uint8_t read_val[1];
	readData(addr, read_val, sizeof(read_val));

	return read_val[0];
}

uint16_t readregister16(uint8_t addr)
{
	uint8_t read_val[2];
	readData(addr, read_val, sizeof(read_val));

	return read_val[0] | (((uint16_t)read_val[1]) << 8);
}

void get_Acc(uint8_t *x, uint8_t *y, uint8_t *z)
{
	uint8_t res[6];
	readData(REG_OUT_X_L,res,sizeof(res));

	*x = res[1];
	*y = res[3];
	*z = res[5];

	//because of 8-bit mode
	//*x |= 0x00FF;
	//*y |= 0x00FF;
	//*z |= 0x00FF;
}

float convertToG(int8_t val)
{
	//float unitDegree = 1.47;		//increase val by 1 -> increase degree by 1.5
	float angleDeviation = 0.0;
	const uint8_t Gvalue = 64;
	if(val <= 122)		//The G vector is zero or is negative
	{
		val = val*(-1);
	}
	else		//The G vector is positive
	{
		val = abs(256-val);
	}
	if(val >= -64 && val < 64)
	{
		angleDeviation = asin((float)val/Gvalue);
	}
	else
	{
		angleDeviation = asin(val/(2*Gvalue));
	}
	angleDeviation = angleDeviation*180/M_PI;

	return angleDeviation;
}

void convertToG2(float *Xval, float *Yval)
{
	const uint8_t Gvalue = 64;
	if(*Xval <= 122)		//The G vector is zero or is negative
	{
		*Xval *= (-1);
	}
	else		//The G vector is positive
	{
		*Xval = (int)abs(256-(*Xval));
	}
	if(*Xval >= -64 && *Xval < 64)
	{
		*Xval = asin(*Xval/Gvalue);
	}
	else
	{
		*Xval = asin(*Xval/(2*Gvalue));
	}

	if(*Yval <= 122)		//The G vector is zero or is negative
	{
		*Yval *= (-1);
	}
	else		//The G vector is positive
	{
		*Yval = (int)abs(256-(*Yval));
	}
	if(*Yval >= -64 && *Yval < 64)
	{
		*Yval = asin(*Yval/Gvalue);
	}
	else
	{
		*Yval = asin(*Yval/(2*Gvalue));
	}

	*Xval *= 180/M_PI;
	*Yval *= 180/M_PI;
}

