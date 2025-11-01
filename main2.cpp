#include <Arduino.h>

// put function declarations here:
//We want to play around with timer0
//OC0A = PB7, Pin11
//0C0B = PD0, Pin3
//FAST PWM Freq = 1KHz
//Monitoring PWM on B, A is TOP
//I calculate CP = 64, Clock is now 125KHz, Need 125 ticks


void setup() {
// put your setup code here, to run once:
Serial.begin(9600);

DDRD |= (1<<0); // PD0 output

OCR0A=255;
OCR0B = 0;
OCR0A = 124;

   //00 = Channel A pin disconnected
        //10 = Channel B pin connected, clear on compare match, set at Top
             //xx
                 //11 = WGM 111, [1:0] = 11, Fast PWM, OCR0A TOP

  TCCR0A = 0b00100011;

  //00
        //xx
            //1 = WGM 011, [2] = 1, Fast PWM, OCR0A TOP
                 //011 = Prescaler = clk/64
  
  TCCR0B = 0b00001011;


  //01 = AVcc refrence, REFS0 = 1
        //0 = Right adjust
             //xxxxx channel selection
   ADMUX = 0b01000001; 

   //1 = ADC enabled
      //1 = start conversion
            //1 = no auto trigger
                //00 = no interrupt
                    //111 = division factor (ADC clock prescaler) = 128
   ADCSRA = 0b11100111; // 
   

   //0 = no high speed
      //x ACME
            //0 = no MUX5 
                //x
                    //0000 = free running
   
   ADCSRB = 0b00100000;


DIDR2 |= (1<<1);


}


void loop() {
  // put your main code here, to run repeatedly:
float aval;
long x;
x = millis();
aval =abs(3 * sin(2 * 3.141592654 * x / 1000));
delay(20);

OCR0B = aval*(OCR0A/3);

unsigned short *ADCData;
unsigned short ADCVal;
ADCData = (unsigned short *)0x78;
ADCVal = (*ADCData & 0x3FF);

float fADCVal;
fADCVal = ((float)ADCVal)/1023 * 3;

Serial.println(abs(aval));
Serial.print("");
Serial.println(fADCVal);

}
