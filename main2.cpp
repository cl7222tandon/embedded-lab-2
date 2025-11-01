#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);

DDRD |= (1<<0); 

OCR0A=255;
OCR0B = 0;
OCR0A = 124;
  TCCR0A = 0b00100011;
  TCCR0B = 0b00001011;

ADMUX = 0b01000001;
ADCSRA = 0b11100111;
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
