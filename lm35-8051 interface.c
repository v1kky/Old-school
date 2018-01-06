#include<at89x51.h>
#define port P3
#define adc_input P1
#define dataport P0
#define sec 100
sbitrs = port^0;
sbitrw = port^1;
sbit e = port^2;
sbitwr= port^3;
sbitrd= port^4;
sbitintr= port^5;
int test_intermediate3=0, test_final=0,test_intermediate1[10],test_intermediate2[3]={0,0,0};
void delay(unsigned intmsec )
{
inti ,j ;
for(i=0;i&lt;msec;i++)
for(j=0; j&lt;1275; j++);
}
voidlcd_cmd(unsigned char item)  //Function to send command to LCD
{
dataport = item;
rs= 0;
rw=0;
e=1;
delay(1);
e=0;
return;
}
voidlcd_data(unsigned char item) //Function to send data to LCD
{
dataport = item;
rs= 1;
rw=0;
e=1;
delay(1);
e=0;
//delay(100);
return;
}
voidlcd_data_string(unsigned char *str)  // Function to send string to LCD
{
inti=0;
while(str[i]!='\0')
{
lcd_data(str[i]);
i++;
delay(10);
}
return;
}
void shape()     // Function to create the shape of degree
{
lcd_cmd(64);
lcd_data(2);
lcd_data(5);
lcd_data(2);
lcd_data(0);
lcd_data(0);
lcd_data(0);
lcd_data(0);
lcd_data(0);
} 
void convert()    // Function to convert the values of ADC into numeric value to be sent to LCD
{
int s;
test_final=test_intermediate3;
lcd_cmd(0xc1); 
delay(2);
lcd_data_string(&quot;TEMP:&quot;);
s=test_final/100;
test_final=test_final%100;
lcd_cmd(0xc8);
if(s!=0)
lcd_data(s+48);
else
lcd_cmd(0x06);
s=test_final/10;
test_final=test_final%10;
lcd_data(s+48);
lcd_data(test_final+48);
lcd_data(0);
lcd_data('c');
lcd_data(' ');
delay(2);
}
void main()
{
inti,j;
adc_input=0xff;
lcd_cmd(0x38); 
lcd_cmd(0x0c);  //Display On, Cursor  Blinking
delay(2);
lcd_cmd(0x01);  // Clear Screen
delay(2);
while(1)
{
for(j=0;j&lt;3;j++)
  {
for(i=0;i&lt;10;i++)
   {
delay(1);
rd=1;
wr=0;
delay(1);
wr=1;
while(intr==1);
rd=0;
lcd_cmd(0x88);
    test_intermediate1[i]=adc_input/10;
delay(1);
intr=1;
   }
for(i=0;i&lt;10;i++)
   test_intermediate2[j]=test_intermediate1[i]+test_intermediate2[j];
  }
test_intermediate2[0]=test_intermediate2[0]/3;
test_intermediate2[1]=test_intermediate2[1]/3;
test_intermediate2[2]=test_intermediate2[2]/3;
test_intermediate3=test_intermediate2[0]+test_intermediate2[1]+test_intermediate2[2];
shape();
convert();
}
}