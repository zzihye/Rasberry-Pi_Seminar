#include<stdio.h>
#include<string.h>	//문자열을 다룰 수 있는 함수 포함
#include<errno.h>	//오류 검사
#include<wiringPi.h>
#include<wiringSerial.h> // 시리얼

int a=0;
int b=0;
int z=0;
int fd;
int main()
{
    if(wiringPiSetup()==-1)
        return 1;
	int mode = 0;
	char str[100];
	char qwe[4];
	char asd[5];
	char das[4];
	char qwe2[4];
	
	if ((fd = serialOpen ("/dev/ttyS0", 9600)) < 0)
	{
		fprintf(stderr,"Unable to open serial device:%s\n",strerror(errno));
		return 1;
	}
	serialPuts(fd,"set password \r");

	while(1)
    {      
        if(mode == 0)
        {
            printf("*****************************************\n");
            printf(" mode 1 : set password \n");
            printf(" mode 2 : write your password \n");
            mode=getchar();      //문자 입력함수
            getchar();
        }
		else if(mode =='1')
        {
			
            if(serialDataAvail(fd) > 0)
            {   
                qwe[1]=serialGetchar(fd);  
				fflush(stdin);
                if(qwe[1]!='\r')
                {   
                     for(a = 1 ; a<4 ; a++)
                    {   
                        asd[0] = qwe[1];
                        asd[a] = serialGetchar(fd);
                    }
                printf("****",asd[0], asd[1], asd[2], asd[3]);
                fflush(stdout);
                printf("\n");
                }
                else if(qwe[1]=='\r')
                {
                    mode = 0;
                }

            }
        }
		else if(mode =='2')
		{
			if((serialDataAvail(fd) > 0))
			{
				
				qwe2[1]=serialGetchar(fd);
				 if(qwe2[1]!='\r')
					{   
						for(z = 1 ; z<4 ; z++)
						{   
							das[0] = qwe2[1];
							das[z] = serialGetchar(fd);
							
						}
						if((das[0]==asd[0])&&(das[1]==asd[1])&&(das[2]==asd[2])&&(das[3]==asd[3]))
							{
								printf("password is correct!\n");
							} 
							else
							{
								printf("password is worng!\n");
							}
					}
			else if(qwe2[1]=='\r')
				{
					mode = 0;
				}
			}
		}
	}
	return 0;
}