#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include<wiringSerial.h>
#include <wiringPiI2C.h>

unsigned int fd;
int ADC_DATA;

void i2cSetMode()
{
	wiringPiI2CWriteReg8 (fd, 0x00, 0x01);			//레지스터 초기화
	wiringPiI2CWriteReg8 (fd, 0x00, 0x1E);			//cycle start, power up (start, analog circuit, digital circuit)
	wiringPiI2CWriteReg8 (fd, 0x01, 0x20);			//VLDO 100 (3.3V)
	wiringPiI2CWriteReg8 (fd, 0x15, 0x30);			//ADC 레지스터 부분, 클럭을 꺼짐('1')상태 설정
	wiringPiI2CWriteReg8 (fd, 0x1c, 0x80);			//파워 컨트롤 레지스터
}

int ADC()
{
    unsigned int DATA_H, DATA_M, DATA_L;	
	int st =0;
	
	do 
	{
		st = wiringPiI2CReadReg8(fd,0x00);
	}
	while(st & 0x20 == 0x00);   					//reg00  cycle ready check 
	
	DATA_H = wiringPiI2CReadReg8(fd,0x12);			//24bit를 8bit씩 나눠서 저장
	DATA_M = wiringPiI2CReadReg8(fd,0x13);
	DATA_L = wiringPiI2CReadReg8(fd,0x14);

	ADC_DATA = (DATA_H<<16)|(DATA_M<<8)|(DATA_L);	//합
	return (ADC_DATA>>15)
	; 							//8bit 맞춰줌
}
int main(void)
{
	unsigned adc_value=0;

	if(wiringPiSetup() == -1)
	{
		fprintf (stdout, "Unable to start wiringPi : %s\n", strerror(errno));
		return 1;
	}
	if((fd=serialOpen("/dev/ttyS0",9600))<0)				//serial 에러 검사
	{
		fprintf(stderr,"Unable to open serial device:%s\n",strerror(errno));
		return 1;
	}

	fd = wiringPiI2CSetup(0x2a);  //NAU7802KGI    ID
	
	if (fd<0)
	{
		printf(" Unable to initialise I2C: \n");
		return -1;
	}
	i2cSetMode();
	serialPuts(fd,"ADC \r");

	while(1)
	{
		adc_value = ADC();
		printf("I2C = %d", adc_value);
		printf("\n");
	}
}