#include <Arduino.h>
#include "paj7620.h"
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <IRremote.h>
#define GES_REACTION_TIME    800
#define GES_QUIT_TIME     1000
// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables

int isr_flag = 0;
IRsend irsend;
void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
void setup() {
  Wire.begin();
  TCA9548A(2);    // select I2C bus 7 for the BMP180
uint8_t error = 0;

  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 15 gestures.");

  error = paj7620Init();      // initialize Paj7620 registers
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:");
    Wire.begin();
 TCA9548A(7); 
 


  //Serial.begin(9600);
 // Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 15 gestures.");

  error = paj7620Init();      // initialize Paj7620 registers
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:");
}

void loop() {
    TCA9548A(2); // select I2C bus 0 for the OLED
  uint8_t data = 0, data1 = 0, error; 

  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_LEFT_FLAG) 
 {
          Serial.println("Right-Left");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x35CAFD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Right");
           irsend.sendNECRaw(0x6D92FD01, 2);
        }          
        break;
      case GES_LEFT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_RIGHT_FLAG) 
        {
          Serial.println("Left-Right");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x35CAFD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Left");
           irsend.sendNECRaw(0x6C93FD01, 2);
        }          
        break;
        break;
      case GES_UP_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_DOWN_FLAG) 
        {
          Serial.println("Up-Down");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x35CAFD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Up");
          irsend.sendNECRaw(0x718EFD01, 2);
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_UP_FLAG) 
        {
          Serial.println("Down-Up");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x35CAFD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Down");
          irsend.sendNECRaw(0x33CCFD01, 2);
        }
        break;
      case GES_FORWARD_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Forward-Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x35CAFD01, 2);
          delay(GES_QUIT_TIME);
        }
        break;
      case GES_BACKWARD_FLAG:     
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Backward-Forward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Backward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        irsend.sendNECRaw(0x3EC1FD01, 2);
        
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        irsend.sendNECRaw(0x6699FD01, 2);
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("wave");
        }
        break;
    }
   TCA9548A(7); 
  uint8_t data = 0, data1 = 0, error; 

  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) 
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_LEFT_FLAG) 
        {
          Serial.println("Right-Left");
          irsend.sendNECRaw(0x3AC5FD01, 2);
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
          irsend.sendNECRaw(0x23DCFD01, 2);
        }
        else
        {
          Serial.println("Right");
          irsend.sendNECRaw(0x708FFD01, 2);
        }          
        break;
      case GES_LEFT_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_RIGHT_FLAG) 
        {
          Serial.println("Left-Right");
          irsend.sendNECRaw(0x639CFD01, 2);
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
         irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
          irsend.sendNECRaw(0x23DCFD01, 2);
        }
        else
        {
          Serial.println("Left");
          irsend.sendNECRaw(0x37C8FD01, 2);
        }          
        break;
        break;
      case GES_UP_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_DOWN_FLAG) 
        {
          Serial.println("Up-Down");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
         irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
          irsend.sendNECRaw(0x23DCFD01, 2);
        }
        else
        {
          Serial.println("Up");
          irsend.sendNECRaw(0x748BFD01, 2);
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_UP_FLAG) 
        {
          Serial.println("Down-Up");
        }
        else if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Forward");
         irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
          irsend.sendNECRaw(0x23DCFD01, 2);
        }
        else
        {
          Serial.println("Down");
          irsend.sendNECRaw(0x758AFD01, 2);
        }
        break;
      case GES_FORWARD_FLAG:
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_BACKWARD_FLAG) 
        {
          Serial.println("Forward-Backward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Forward");
          irsend.sendNECRaw(0x2DD2FD01, 2);
          delay(GES_QUIT_TIME);
          
        }
        break;
      case GES_BACKWARD_FLAG:     
        delay(GES_REACTION_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          Serial.println("Backward-Forward");
          delay(GES_QUIT_TIME);
        }
        else
        {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
          irsend.sendNECRaw(0x23DCFD01, 2);
        }
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        irsend.sendNECRaw(0x6A95FD01, 2);
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        irsend.sendNECRaw(0x7D82FD01, 2);
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("wave");
        }
      break;
      }
  }}}
