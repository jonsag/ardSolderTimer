#include "Arduino.h"

#include "configuration.h" // sets all variables
#include "buttons.h" // handles the button presses
#include "run.h" // handles the timer function


void setup() {

  /*******************************
    Start serial
  *******************************/
  
  Serial.begin(9600);

  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.print(author);
  Serial.println(email);
  Serial.println();

  /*******************************
    Define in- and outputs
  *******************************/
  Serial.println("Starting in- and outputs...");
  Serial.println();

  pinMode(startButtonPin, INPUT);
  pinMode(setButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, relayState);   // set initial output states

  /*******************************
    Read time value from eeprom
  *******************************/
  Serial.println("Reading last time from eeprom ...");

  f = 0.00f;
  EEPROM.get(eeAddr, f); // read time from eeprom
  Serial.print("Found time: ");
  Serial.print(f);
  Serial.print(" seconds");
  Serial.println();

  if (isnan(f)) { // check if there is a value stored in eeprom
    Serial.println("No value found in eeprom");
    Serial.print("Storing value: ");
    Serial.println(dur);
    Serial.println();
    EEPROM.put(eeAddr, dur); // if not, store the predefined time
  }
  else {
    Serial.println("Using it for timer");
    Serial.println();
    dur = f; // else use it as set point
  }

  /*******************************
      Build custom characters
    *******************************/
  Serial.println("Building characters ...");
  Serial.println();

}

void loop() {
  /*******************************
    Read buttons
  *******************************/
  readButtons();

  if (relayState == HIGH) { // timer is running
    countDown();
  }
  else if (setMode == HIGH) { // in set mode
    //setTime();
  }
  else {
  }
}
