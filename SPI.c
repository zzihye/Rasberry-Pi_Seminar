#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include<wiringSerial.h>
#include <wiringPiSPI.h>

#define CS_MCP3208 6
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 //1MHz

unsigned char adcChannel;
char qwe[100];
int fd, abc;
int adcValue = 0;

void setSPI(void)
{
	pinMode(CS_MCP3208, OUTPUT);
	digitalWrite(CS_MCP3208, 1);  // HIGH : CS Inactive
}

int read_mcp3208_adc(unsigned char adcChannel) 
{
    unsigned char buff[3];    
    buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
    buff[1] = ((adcChannel & 0x07) << 6);
    buff[2] = 0x00;
    
    digitalWrite(CS_MCP3208, 0);
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

    buff[1] = 0x0f & buff[1];
    adcValue = (buff[1] << 8 ) | buff[2];
    
    digitalWrite(CS_MCP3208, 1);
    
    return adcValue;
}

int main()
{	
	if (wiringPiSetup () == -1)
		return 1;
	
	if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)  
    {
        fprintf(stdout, "wiringPiSPISetup Failed :%s\n", strerror(errno));
        return 1;
    }
	if((fd=serialOpen("/dev/ttyS0",9600))<0)				//serial 에러 검사
	{
		fprintf(stderr,"Unable to open serial device:%s\n",strerror(errno));
		return 1;
	}
	serialPuts(fd,"ADC \r");
	setSPI();
	adcValue = read_mcp3208_adc(adcChannel);
	
	while(1)
	{
		abc = read_mcp3208_adc(adcChannel);
		sprintf(qwe,"SPI : %d %d",adcChannel,abc);
		serialPuts(fd,qwe);
		serialPuts(fd,"\r");       // 줄바꿈
		fflush(stdout);            // 출력버퍼를 비움                      
		delay(500);
	}
}