#include<reg51.h>
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
 void delay(int i)
 {
    int jaw,k;
	for(k=0;k<i;k++)
	{
	for(jaw=0;jaw<50;jaw++)
	{
	TMOD=0x20; 
    TH1=0xF8;
	TL1=0xCC;
	TR1=1;
	while(TF1==0);
	TF1=0;
	TR1=0;
	}
	}
 }
  void lcd_cmd(char ch)
  {
     P2=ch;
	 RS=0;
	 RW=0;
	 EN=1;
	 delay(1);
	 EN=0;
  }
  void lcd_init()
  {
    lcd_cmd(0x0E);
	lcd_cmd(0x02);
	lcd_cmd(0x01);
  }
  void lcd_data(char k)
  {
     P2=k;
	 RS=1;
	 RW=0;
	 EN=1;
	 delay(1);
	 EN=0;

  }

  void main()
  {
  int a=12345;
     lcd_init();
	 while(1)
	 {
	 //lcd_cmd(0x80);
	 lcd_data((a/10000)+48);
	 delay(1);
	 lcd_cmd(0x01);	
	 lcd_data(((a/1000)%10)+48);
	  delay(2);
	  lcd_cmd(0x01);
	 lcd_data(((a/100)%10)+48);
	  delay(3);
	  lcd_cmd(0x01);
	 lcd_data((a%10)+48);
	  delay(4);
	  lcd_cmd(0x01);
	 lcd_data((a/10)+48);
	  delay(5);
	  lcd_cmd(0x01);
     }
  }
