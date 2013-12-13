/*
 IR transmiter with a push button and a Potentiometer for ATTINY85 @8 Mhz
 philteta@gmail.com
 This example sketch works with SimpleIRTinyRX.ino sketch for the RX part
 Push button on pin 3 (arduino 4) with 10 kohm  pullup
 IR led on pin 6 (arduino 1)
 The IR output MUST be on pin 6 (OC0B).
 *---------------*
 |DIL 8 | Arduino|
 |------|--------|
 |  1   |        | reset 
 |  2   |   3    | Analog in / digial in or out
 |  3   |   4    | Analog in / digial in or out
 |  4   |        | GND
 |  5   |   0    | PWM / digial in or out
 |  6   |   1    | PWM / digial in or out
 |  7   |   2    | Analog in / digial in or out
 |  8   |        | VCC
 *---------------*
 For futur reference the IR library use some stuff (timer I think) and dosen't permit to use PWN hardware function
*/


#include "IRTinyTX.h" //short version on IR library with only TX function for NEC protocol



//IR code list
#define alloff 0x00FF00FF 
#define allon 0x00FFFF00  
#define bouton 4
boolean butonstate = true;
IRsend irsend;

void setup(void) 
{
  irsend.enableIROut(38); // Enable phase-correct PWM with a frequency of 38kHz
  pinMode(bouton,INPUT);
}

void loop(void) 
{  
  //read buton state 
  butonstate = digitalRead(bouton);
  if (!butonstate) irsend.sendNEC(allon, 32);  // if buton is pressed then send allon code
  else irsend.sendNEC(alloff, 32); // send alloff code
  delay(100); //delay between two TX
}
