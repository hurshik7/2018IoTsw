#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

const int FndSelectPin[6] = {4, 17, 18, 27, 22, 23};
const int FndPin[8] = {6, 12, 13, 16, 19, 20, 26, 21};
const int FndFont[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 
							0x07, 0x7F, 0x67, 0x80};

void Init()
{
		int i;
		if(wiringPiSetupGpio() == -1)
		{
				printf("WiringPiSetupGpio() error\n");
				exit(-1);
		}

		for(i=0; i<6; i++){
				pinMode(FndSelectPin[i], OUTPUT);
				digitalWrite(FndSelectPin[i], HIGH);
		}

		for(i=0; i<8; i++) {
				pinMode(FndPin[i], OUTPUT);
				digitalWrite(FndPin[i], LOW);
		}
}

void FndSelect(int position)
{
		int i;
		for(i=0; i<6; i++)
		{
				if(i==position)
						digitalWrite(FndSelectPin[i], LOW);
				else
						digitalWrite(FndSelectPin[i], HIGH);
		}
}

void FndDisplay(int position, int num)
{
		int i,j;
		int flag = 0;
		int shift = 0x01;

		FndSelect(position);
		for(i=0; i<8; i++)
		{
				flag = (FndFont[num] & shift);
				digitalWrite(FndPin[i], flag);
				shift <<= 1;
		}
}

int main(){
		int t, i, pos;
		int num_00, num_0, num0_, num00_, num000_;
		num_00 = 0 ; num_0 = 0; num0_ = 0; num00_ = 0; num000_ = 0;
		int data[6] = {0, 0, 10, 0, 0, 0};
		//10 = .
		Init();
		while(1)
		{
			data[0] = num_00 % 10;
			data[1] = num_0 % 10;
			data[3] = num0_ % 10;
			data[4] = num00_ % 10;
			data[5] = num000_ % 10;
			
			for(pos=0; pos<6; pos++){
				FndDisplay(pos, data[pos]);
				delay(1);
			}
			num_00++;
			num_0 = num_00/10 ;
			num0_ = num_0/10;
			num00_ = num0_/10;
			num000_ = num00_/10;
		}
		return 0;
}
