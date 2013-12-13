Modified Version of the IRTinyRX library found at http://tetalab.org/blog/librairie-ir-nec-pour-attiny85
The device I wanted to control with my Digispark, which uses the Attiny85, uses RC5 instead
 of NEC so I added the sendRC5() function. It works just like the sendNEC function but with RC5.
 I thought I should share this to maybe save somebody some time. All credit for the original library to
 its original authors.
 
 Issues I encountered:
 
 PROBLEM: The atTiny flashes the IR led but the device won't respond
 SOLUTION: My atTiny wasn't at 8Mhz so the timing was off
 
 PROBLEM: The IR led has very short range
 SOLUTION: Make sure that you don't have it plugged into the default led pin (varies on version of board)