#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <IRremote.h> 
// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin
 
// Constants
 
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
IRsend irsend; 
void setup() {
 
  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);
 
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
 
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);
 
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
 
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}
 
void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
}
 
void interruptRoutine() {
  isr_flag = 1;
}
 
void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        irsend.sendNECRaw(0x3EC1FD01, 32);
        Serial.println("UP");
        break;
      case DIR_DOWN:
      irsend.sendNECRaw(0x6699FD01, 32);
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
      irsend.sendNECRaw(0x35CAFD01, 32);
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
      irsend.sendNECRaw(0x2DD2FD01, 32);
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
      irsend.sendNECRaw(0x708FFD01, 32);
        Serial.println("NEAR");
        break;
      case DIR_FAR:
      irsend.sendNECRaw(0x37C8FD01, 32);
        Serial.println("FAR");
        break;
      //default:
        //Serial.println("NONE");
    }
  }
}
