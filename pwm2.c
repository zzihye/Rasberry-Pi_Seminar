#include<stdio.h>
#include<wiringPi.h>

#define servo_motor 1

int number=0, flag=0, pwm=34;

void SetPWM(void)
{
	pinMode(servo_motor,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);	//		19.2*10^6/384/1000=50Hz     1000ms/50Hz=20ms/Hz
	pwmSetRange(960);
	pwmWrite(1,pwm);
}
int angle2(void)
	{ 
		while(1)
		{
			if(flag==0)
			{
				pwm++;
				delay(10);
				if(pwm==110)
					flag=1;
			}
			else if(flag==1)
			{
				pwm--;
				delay(10);
				if(pwm==34)
				flag=0;
			}
			if(pwm>=34&&pwm<72)
			{
				printf("^^\n");
				pwmWrite(1,34);
				delay(100);
			}
			if(pwm>=72&&pwm<110)
			{
				pwmWrite(1,72);
				delay(100);
			}
			if(pwm>110)
			{
				pwmWrite(1,110);
				flag=1;
			}
				angle=pwm-34;
				printf("servo_motor_angle= %d\n",angle);
				pwmWrite(1,pwm);
				delay(200);
		}
		
	}
	int main(void)
{
	if(wiringPiSetup()==-1)return 1;
		SetPWM();
		while(1)
	{
		printf("select mode : 1 or 2?\n");
		scanf("%d",&number);
	
		if(number==2)
		{
			angle2();			
		}
	}
	return 0;
}