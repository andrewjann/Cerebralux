/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the receivedInputs RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>

int RECV_PIN = 7;
int BAD_PIN = 8;
int LED_PIN = 9;
int receivedInputs[2] = {0,0};
int numberOfReceivedInputs = sizeof(receivedInputs)/sizeof(int);
int pwm = 255;
float intensity;
int zeroSignal = 777;
int ONtime = 0;
int OFFtime = 10;
int i=0;

String resultsString;
int resultsInt;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(BAD_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
//  digitalWrite(BAD_PIN, HIGH);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    resultsString = String(results.value);
    resultsInt = resultsString.toInt();
    irrecv.resume(); // Receive the next value
    if (resultsInt < 1000) {
      if (i < numberOfReceivedInputs - 1)  {
        if (resultsInt == zeroSignal)  {
          resultsInt = 0;
          receivedInputs[i] = resultsInt;
          i++;
        }
        else  {        
          receivedInputs[i] = resultsInt;
          i++;
        }
      }
      else if (i == numberOfReceivedInputs - 1) {
        if (resultsInt == zeroSignal) {
          resultsInt = 0;
          receivedInputs[i] = resultsInt;
          i++;
        }
        else {
          receivedInputs[i] = resultsInt;
        }
        
        ONtime = receivedInputs[0];
        OFFtime = receivedInputs[1];
        Serial.print("ON time: ");
        Serial.println(ONtime);
        Serial.print("OFF time: ");
        Serial.println(OFFtime);
        i=0;
      }
    }
  else if (resultsInt > 1000) {
    intensity = resultsInt/100;
    intensity = intensity/100;
    pwm = 255 * intensity;
    Serial.print("Intensity: ");
    Serial.println(pwm);
  }
 }
  else  {
    if (receivedInputs[0] == 0 && receivedInputs[1] == 0) {
      analogWrite(LED_PIN, LOW);
      //turn off LED and do nothing
    }
    else if (receivedInputs[0] == 0 && receivedInputs[1] != 0)  {
      analogWrite(LED_PIN, LOW);
      //turn off LED and do nothing
    }
    else if (receivedInputs[0] != 0 && receivedInputs[1] == 0)  {
      analogWrite(LED_PIN, pwm);
    }
    else  {
      analogWrite(LED_PIN, pwm);
      delay(ONtime);
      analogWrite(LED_PIN, LOW);
      delay(OFFtime);
    }
  }

}

