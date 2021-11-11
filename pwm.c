#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

#define led1 23
#define led2 24
#define led3 25
#define servo_motor 1

int duty =0, number=0, flag=0, pwm=7;
double angle;

void SetPWM(void)
{
	pinMode(servo_motor,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(1920);	//		19.2*10^6/384/1000=50Hz     1000ms/50Hz=20ms/Hz
	pwmSetRange(200);
	pwmWrite(1,pwm);
}

int angle2(void)
	{
		while(1)
		{
			pwm=pwm+1;
			angle=pwm-7;
			printf("servo_motor_angle : %d\n",angle);
			delay(200);		
		}
	}

int LED(void)
	{
		while(1)
		{
			if(flag==0)
			{
				duty++;
			}
			else if(flag==1)
			{
				duty--;
				if(duty==0)
					flag=0;
			}
			if(duty>=7)
			{
				digitalWrite(led1,0);
				digitalWrite(led2,1);
				digitalWrite(led3,1);
				softPwmWrite(1,7);
				}
			if(duty>=15)
			{
				digitalWrite(led2,0);
				digitalWrite(led3,1);
				softPwmWrite(1,15);
			}
			if(duty>=23)
			{
				digitalWrite(led3,0);
				softPwmWrite(1,23);
				flag=1;
			}
				printf("%d\n",duty);
				delay(500);
		}
		
	}	
int main(void)
{
	if(wiringPiSetup()==-1)return 1;
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	SetPWM();
	digitalWrite(led1,1);
	digitalWrite(led2,1);
	digitalWrite(led3,1);
	softPwmCreate(servo_motor,0,100);
	while(1)
	{
	printf("select mode : 1 or 2?\n");
	scanf("%d",&number);
	if(number==1)
		{
			LED();
		}
	else if(number==2)
		{
			angle2();
		}
	}

}