/*
 IR transmiter with a push button and a Potentiometer for ATTINY85 @8 Mhz
 philteta@gmail.com
 This example sketch works with FourLedsIRTinyRX.ino sketch for the RX part
 Push button on pin 3 (arduino 4) with 10 kohm  pullup
 Potentiometer on pin 2 (arduino 3) 
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
IRsend irsend;


//IR code list
//led status 0 = on , x = off   
#define alloff 0x00FF00FF // xxxx
#define led1x 0x00FF44BB  // 0xxx
#define led12 0x00FF34CB  // 00xx
#define led2x 0x00FF33CC  // x0xx
#define led23 0x00FF23DC  // x00x
#define led3x 0x00FF22DD  // xx0x
#define led34 0x00FF12ED  // xx00
#define led4x 0x00FF11EE  // xxx0
#define allon 0x00FFFF00  // 0000

#define bouton 4
#define sensorPin  3    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean butonstate = false;

void setup(void) 
{
  irsend.enableIROut(38); // Enable phase-correct PWM with a frequency of 38kHz
  pinMode(bouton,INPUT);
}

void loop(void) 
{  
    //read buton state and potentiometer value 
	sensorValue = analogRead(sensorPin);    
	butonstate = digitalRead(bouton);

	if (!butonstate) irsend.sendNEC(allon, 32);  // if buton is pressed then send allon code
	else
	{
		if (sensorValue > 897) irsend.sendNEC(alloff, 32); // send alloff code
		if (sensorValue > 769 && sensorValue <= 896) irsend.sendNEC(led1x, 32); //  send led1x code
		if (sensorValue > 641 && sensorValue <= 768) irsend.sendNEC(led12, 32); //   send led12 code
		if (sensorValue > 513 && sensorValue <= 640) irsend.sendNEC(led2x, 32); //  send led2x code
		if (sensorValue > 385 && sensorValue <= 512) irsend.sendNEC(led23, 32); //  send led23 code
		if (sensorValue > 257 && sensorValue <= 384) irsend.sendNEC(led3x, 32); //  send led3x code
		if (sensorValue > 129 && sensorValue <= 256) irsend.sendNEC(led34, 32); //  send led34 code
		if (sensorValue <= 128) irsend.sendNEC(led4x, 32); //  send led4x code
	}
	delay(100); //delay between two TX
}
