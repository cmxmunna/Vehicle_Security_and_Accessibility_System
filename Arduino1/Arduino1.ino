#include <Adafruit_Fingerprint.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <AM2320.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
#define RELAY_PIN  5
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
AM2320 car_temp;

int motor1pin = 6;

void setup() {
  //set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) 
  {
  } 
  else 
  {
    while (1) { delay(1); }
  }
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 
  
 //Display Control
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
 //Temp Control
  car_temp.begin();
}

void loop() {
  // Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
    
  display.setCursor(0,0);
  display.print("====SMART Vehicle====");
  
  //Car Temparature
  if (car_temp.measure()) {
    display.setCursor(0,15);
    display.print("T=");
    display.print(temp('C'));
    display.print(" *C, H=");
    display.print(car_temp.getHumidity());
    display.println("%");
  }
  else {  // error has occurred
    int errorCode = car_temp.getErrorCode();
    switch (errorCode) {
      case 1: display.println("ERR:Sensor is offline"); break;
      case 2: display.println("ERR:CRC validation failed."); break;
    }    
  }
  //delay(50);

  /*Fan control by temperature*/

  display.setCursor(0,25);
  if(temp('C')<=29)
   {
    display.print("Air Conditioner OFF");
    digitalWrite(motor1pin, HIGH);
   }
  if(temp('C')>29)
    {
     display.print("Air Conditioner ON");
     digitalWrite(motor1pin, LOW);
    }

   //Fingerprint Scan
     if ( getFingerPrint() != -1)
  {
    digitalWrite(RELAY_PIN, LOW);
  }  
  if ( getFingerPrint() != -1)
  {
    digitalWrite(RELAY_PIN, HIGH);  
  } 
  if (RELAY_PIN != LOW)
  {
    display.setCursor(0,35);
    display.print("Waiting for Finger!");
    display.setCursor(0,45);
    display.print("Main Engine 'OFF'");
   } 
  else if (RELAY_PIN != HIGH)
  {
    display.setCursor(0,35);
    display.print("->Authorized<-");
    display.print("Main Engine 'ON'");
   }
  
   display.display();
}
int getFingerPrint() 
{
  int p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

 // found a match!
  return finger.fingerID;
}

float temp(char T)
{
  if (car_temp.measure()) 
  {
    if(T =='F')
    {
      return car_temp.getTemperature()* 1.8 + 32;
    }
    else
    {
      return car_temp.getTemperature();// return CELSIUS
    }
  }
}
