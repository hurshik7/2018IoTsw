#include<wiringPi.h>
#include<softPwm.h>

#define LED_2 	17
#define LED_1	4


int main(void)
{
		if(wiringPiSetupGpio() == -1)
				return 1;

		pinMode(LED_1, OUTPUT);
		int i;

		softPwmCreate(LED_1, 0, 128);
		softPwmCreate(LED_2, 0, 128);

		while(1)
		{
				for(i=0; i<128; i++){
					softPwmWrite(LED_1, i);
					delay(10);
				}
				for(i; i>0; i--){
					softPwmWrite(LED_1, i);
					delay(10);
				}
		}
		return 0;
}
