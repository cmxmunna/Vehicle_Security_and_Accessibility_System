#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <AM2320.h>

#define RELAY_PIN  5
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

int sensorValue;
int digitalValue;

void setup() {
 //Display Control
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
 //Alcohol
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  // Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
    
  display.setCursor(0,0);
  display.print("====SMART Vehicle====");
  
    display.setCursor(0,15);
    display.print("Alcohol Level = ");
    display.print(sensorValue, DEC); 
    display.println("%"); 


    sensorValue = analogRead(0); // read analog input pin 0
    digitalValue = digitalRead(2);
  if (sensorValue > 400)
  { 
    digitalWrite(RELAY_PIN, HIGH); 
    digitalWrite(13, HIGH);
    display.setCursor(40,25);
    display.println("!WARNING!");
    display.setCursor(0,35);
    display.println("Driver Is Alcoholic!");   
    display.setCursor(0,45);
    display.println("Engine 'OFF'"); 
          
  }
  else
  {
    digitalWrite(13, LOW);
    display.setCursor(0,25);
    display.println("No Alcohol Detected."); 
    display.setCursor(0,35);
    display.println("Engine 'ON'"); 
    //digitalWrite(RELAY_PIN, LOW); 
  }
  
   display.display();
}
