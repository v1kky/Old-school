#include<reg51.h>
sfr stepper=0xA0;
void delay(unsigned int count)
{ 
	inti;
	for(i=0;i<count;i++);
}
void main()
{
	while(1)
	{
		stepper=0x01;
		delay(300);
		stepper=0x03;
		delay(300);
		stepper=0x02;
		delay(300);
		stepper=0x06;
		delay(300);
		stepper=0x04;
		delay(300);
		stepper=0x0C;
		delay(300);
		stepper=0x08;
		delay(300);
		stepper=0x09;
		delay(300);
	}
}