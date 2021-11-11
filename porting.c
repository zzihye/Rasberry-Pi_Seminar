#include <stdio.h>
#include <wiringPi.h>

#define led1 21
#define led2 22
#define led3 23
#define led4 24
#define led5 27
#define led6 25
#define led7 28
#define sw1 3
#define sw2 1
#define sw3 2
#define sw4 4

unsigned char led[]={led1, led2, led3, led4, led5, led6, led7};
unsigned char sw[]={sw1, sw2, sw3, sw4};

void setting(void)
{
	for(int i=0; i<7; i++)
	{
		pinMode(led[i],OUTPUT);
		digitalWrite(led[i],1);
	}
	for(int k=0; k<4; k++)
	{
		pinMode(sw[k],INPUT);
	}
}	

int main (void)
{
	if(wiringPiSetup()==-1) return 1;
	setting();
	int i=0, k=0, t=100, button=0;
	while(1)
	{
		if (digitalRead(sw1)==0)
		{
			for(i=0;i<7;i++)
			{
				digitalWrite(led[i],0);
				delay(100);
				digitalWrite(led[i],1);
			}
		}
		else if (digitalRead(sw2)==0)
		{
			while((digitalRead(sw2)==0))
			{
			for(int z=0;z<7;z++)
			{
				digitalWrite(led[z],0);
				delay(t);
				t++;
			}
			}
		}
		else if (digitalRead(sw3)==0)
		{
			delay(100);
			button++;
			
			if(button%2==1)
				{
					for(i=0;i<7;i=i+2)
					{
						digitalWrite(led[i],0);										
					}
				}
				else if(button%2==0)
				{
					for(i=1;i<7;i=i+2)
					{
						digitalWrite(led[i],1);
						delay(100);
						digitalWrite(led[i],0);
					}
				}
		}
		else if (digitalRead(sw4)==0)
		{
			for(i=0;i<7;i++)
			{
				digitalWrite(led[i],0);
				delay(t);
				t--;
				digitalWrite(led[i],1);
			}
		}
	}
	return 0;
}