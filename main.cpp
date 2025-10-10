#include <Arduino.h>

// put function declarations here:
//We want to play around with timer0
//OC0A = PB7, Pin11
//0C0B = PD0, Pin3
//FAST PWM Freq = 1KHz
//50% DC
//Monitoring PWM on B, A is TOP
//I calculate CP = 64, Clock is now 125KHz, Need 125 ticks

void setup() {
  // put your setup code here, to run once:
  DDRB |= (1<<7);
  DDRD |= (1<<0); //Set PortD pin ) to an output  
  OCR0A=255;
  OCR0B = 0;
    OCR0A = 124; //Count up to 125
    TCCR0A = 0b10100011;
    //         0010 - Channel A disconnected, Channel B Normal PWM
    //               xx = WGM 111  \
    //             xx - UNUSED as per datasheet        
    TCCR0B = 0b00000011;
  //               x = WGM 111
  //                011 = 64 prescale


}

void loop() {
  // put your main code here, to run repeatedly:
  OCR0B++;
  if (OCR0B==255)
    OCR0B=0;
  OCR0A--;
  if (OCR0A==0)
    OCR0A=255;

  delay(300);

}
