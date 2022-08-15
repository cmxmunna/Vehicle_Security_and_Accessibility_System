#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <AM2320.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
AM2320 car_temp;

int motor1pin = 2;

void setup() {
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
  delay(500);

  /*Fan control by temperature*/

  display.setCursor(0,25);
  if(temp('C')<=29)
   {
    display.print("Air Conditioner OFF");
    digitalWrite(motor1pin, LOW);
   }
  if(temp('C')>29)
    {
     display.print("Air Conditioner ON");
     digitalWrite(motor1pin, HIGH);
    }
   display.display();
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
