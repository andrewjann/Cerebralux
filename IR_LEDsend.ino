/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;

//GUI variables
int mydata;
int input[3];
int zeroSignal = 777;
int numberOfInputs = sizeof(input)/sizeof(int);
int i=0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  if (Serial.available()>0)  {  // when data is received through the Serial port, read data
    mydata = Serial.parseInt();  // reads integers until a non-integer, non-negative sign
    if (mydata > 0)  {
      if (i < numberOfInputs - 1)  {
          input[i] = mydata;
          i++;
        }
      else if (i == numberOfInputs - 1) {
        input[i] = mydata;
        for(i=0;i<numberOfInputs;i++) {
          Serial.println(input[i]);
          irsend.sendSony(input[i], 16); //inputs floats, number of bits
          delay(150);
        }
        i=0;
      }
      else {
        Serial.println("It's a trap");
      }
    }
  }
}

//  thisString = String(i, HEX);
//  Serial.println(thisString);
//	for (int i = 0; i < 1; i++) {
//		irsend.sendSony(1000, 12);
//		delay(40);
//	}
//	delay(2000); //2 second delay between each signal burst
//  for (int i = 0; i < 1; i++) {
//    irsend.sendSony(0xa90, 12);
//    delay(40);
//  }
//  delay(2000); //5 second delay between each signal burst
//}
