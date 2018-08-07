#include<stdio.h>
 char str[10];
 unsigned int i,PWM_value=0,duty_cycle=0,count=1,throttle_position=0;
int adc(void)
{
  int b=0;
  ADMUX=0x00;//selected ADC0 channel
  ADMUX|=(1<<REFS0);//giving AVcc reference voltage
  ADCSRA=(1<<ADEN)|(1<<0)|(1<<1)|(1<<2);//Enabling the ADC and giving 128 devider to set frequency
  ADCSRA|=(1<<ADSC);//we are starting convertion analog to digital by enabling this bit
  while((ADCSRA&(1<<ADSC))==0);//we are waiting for the complition of covertion 
  //ADCL=0XFF;
  b=ADCL|(ADCH<<8);
  return b;
}
void PWM_init()
{
  TCCR0A=0x83;
  TCCR0B =(1<<CS12);
  DDRD=0xff;  
}
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  PWM_init();
  pinMode(5,INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int adc_val=adc();
  OCR0A=(adc_val*0.249);    /* 8 bit pwm max value 255 and 10 bit adc max value 1023 for adjusting 1023 to 255 (255*adc_value)/1023 (or), 0.249*adc_value,  255/1023=0.249 */
  PWM_value = pulseIn(5, HIGH);  /* pulseIn function gives ON time of the pulse in micro seconds*/
  
 if(PWM_value<=405)   /* for first 10% of pulseIn value 405, 90% of pulseIn value 4050-405=3645 */
 {
  duty_cycle=10;
 }
 else if(PWM_value>405 && PWM_value<=3645)
 {
     duty_cycle =(0.02469*PWM_value);   /* pulseIn function gives max 4050 micro seconds, deviding that to %, (80*pwm_value)/4050 (or) 0.01975*pwm_value 100/4050=0.02469 */
 }
 else
 {
  duty_cycle=90;
 }
throttle_position=((duty_cycle-10)*1.25);
Serial.print("duty cycle : ");
Serial.println(duty_cycle);
Serial.print("throttle position : ");
Serial.println(throttle_position);
  
  delay(500);
}
