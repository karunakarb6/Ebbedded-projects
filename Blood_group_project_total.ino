#include<Arduino.h>
#include<EEPROM.h>
#include<stdio.h>
char blood_group[5],p_name[15],mobile_number[10];
int i=0,j=0,n=0;
int addr = 0;//addr variable for write the address into EEPROM
byte data,o;//data variable to store the charecters 
int ad=0,l,k=0,index=0;
char da,string[15];

void usart_init(int b)
  {
  UBRR0H=(unsigned char)(b>>8);//used to load the higher byte of the baud rate 
  UBRR0L=(unsigned char)(b);//used to load the lower byte of the baud rate
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);//enabling RXEN0 bit to recieve the data(receive enable). enabling TXEN0 bit to transmit the data(transmitter enable)  
  //UCSR0C = (1<<USBS0)|(3<<UCSZ00);
  //UCSR0C = (1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);//enablig UBS0 to set the stop bits 2. enabling UCSZ00 and UCSZ01 to set the mode to send 8 bit of data(mode 11).  
  UCSR0C =(1<<UCSZ00)|(1<<UCSZ01);//enabling UCSZ00 and UCSZ01 to set the mode to send 8 bit of data(mode 11). 
  }

void usart_tx(unsigned char ch)
  {
  //putting the data in URD0 register to send 8 bit of data.
  while(!(UCSR0A&(1<<UDRE0)));//waiting for transmission is complited,if it will be high, then we know transmission is done.
  UDR0=ch;
  }
char usart_rx()
  {
  char k;
  while(!(UCSR0A&(1<<RXC0)));//waiting for receiving, if it is high the data is received succesfully
  k=UDR0;//storing that received data in one variable.
  return k;//returnig that data to use in another function
  }
  
void usart_string(char *p)
{
  while(*p!='\0')
  {
     usart_tx(*p++); 
  }
}

int EEPROM_index_read()
{
  data = EEPROM.read(0);
  return data;   
}

void string_write_function()
{
  char *p;
  k=EEPROM_index_read();
  //Serial.print("0th address");
  //Serial.println(k);
   while(usart_rx()!='#');
   while((blood_group[i++]=usart_rx())!=',');
   blood_group[--i]='\0';
   i=0;
   while((p_name[i++]=usart_rx())!=',');  
   p_name[--i]='\0';
   i=0;
   while((mobile_number[j++]=usart_rx())!='@');
   mobile_number[--j]='\0';
   j=0;

   p=blood_group;
    addr=(30*k)+1;
   while(*p!='\0')
  {
    //Serial.println(*p);
    EEPROM.write(addr, *p++);//sending charecter by charecter. incrementing the address of string
    addr = addr + 1;//incrementing the address of EEPROM
  }
  EEPROM.write(addr, '\0');
  
 p=p_name;
  addr=(30*k)+5;
   while(*p!='\0')
  {
    EEPROM.write(addr, *p++);//sending charecter by charecter. incrementing the address of string
    addr = addr + 1;//incrementing the address of EEPROM
  }
  EEPROM.write(addr, '\0');

  addr=(30*k)+19;
  p=mobile_number;
   while(*p!='\0')
  {
    EEPROM.write(addr, *p++);//sending charecter by charecter. incrementing the address of string
    addr = addr + 1;//incrementing the address of EEPROM
  }
  EEPROM.write(addr, '\0');
  
  index_write_function();
}

void index_write_function()
{
  index=EEPROM_index_read();
  index++;
  EEPROM.write(0,index);
  //Serial.print("index :");
  //Serial.println(index);
}

void calling_read_write_function()
{
  char a;
  a=usart_rx();
  if(a=='#')
  {
    string_write_function(); 
  }
  else if(a=='$')
 {
   EEPROM_read_function();
 } 
 else if(a=='*')
 {
  blood_group_search();
 }
}

void blood_group_search()
{
  int a=0;
  char ch[5];
  while((ch[a++]=usart_rx())!='@');
  ch[--a]='\0';
   for(k=0;k<EEPROM.read(0);k++)
    { 
    addr=(30*k)+1;
   while(EEPROM.read(addr)!='\0')
   {
    da=EEPROM.read(addr++); 
    //Serial.print(da);
    string[n++]=da;
   }
   string[n]='\0';
   n=0;
   if((strcmp(ch,string))==0)
   {
      addr=(30*k)+5;  
      while(EEPROM.read(addr)!='\0')
      {
       da=EEPROM.read(addr++); 
       Serial.print(da);
      }
     Serial.println();
     addr=(30*k)+19;
     while(EEPROM.read(addr)!='\0')
      {
       da=EEPROM.read(addr++); 
       Serial.print(da);
      }
      Serial.println(); 
   } 
  }
}

void EEPROM_read_function()
{
  int w=0;
  w=EEPROM.read(0);
  for(k=0;k<w;k++)
  {
   addr=(30*k)+1;
   while(EEPROM.read(addr)!='\0')
   {
    da=EEPROM.read(addr++); 
    Serial.print(da);
   }
  Serial.println(); 
  
  addr=(30*k)+5;  
  while(EEPROM.read(addr)!='\0')
   {
    da=EEPROM.read(addr++); 
    Serial.print(da);
   }
   Serial.println(); 
   
  addr=(30*k)+19;
  while(EEPROM.read(addr)!='\0')
   {
    da=EEPROM.read(addr++); 
    Serial.print(da);
  }
  Serial.println();
 }
}


void setup() 
   {
//    for(int i=0;i<1024;i++)
//    {
//      EEPROM.write(i,0);
//    }
    usart_init(103);//giving 103 means we are setting the baud rate is 9600
   }

void loop() 
  {
   calling_read_write_function(); 
   //string_write_function();
   //EEPROM_read_function();
  //delay(1000);
  }


