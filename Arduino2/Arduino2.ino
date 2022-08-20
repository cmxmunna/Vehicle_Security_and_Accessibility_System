#include <SoftwareSerial.h>

//Alarm reciever's phone number with country code
const String PHONE_1 = "+8801627124780";
const String PHONE_2 = ""; //optional
const String PHONE_3 = ""; //optional

#define rxPin 2
#define txPin 3
SoftwareSerial sim800L(rxPin,txPin);

#define flame_sensor_pin 5
//fire_flag = 0 means no fire detected
boolean fire_flag = 0;



void setup()
{

  
  //Begin serial communication: SIM800L
  sim800L.begin(9600);
  
  pinMode(flame_sensor_pin, INPUT);
  
  
  Serial.println("Initializing...");
  //Once the handshake test is successful, it will back to OK
  sim800L.println("AT");
  delay(1000);
  sim800L.println("AT+CMGF=1");
  delay(1000);

}

void loop()
{
  while(sim800L.available()){
  Serial.println(sim800L.readString());
  }
  
  int flame_value = digitalRead(flame_sensor_pin);
  
  //The fire is detected, trigger Alarm and send sms
  if(flame_value == HIGH)
  {
    if(fire_flag == 0)
    {
      Serial.println("Bodddaaa Agun to Lagi gese!!.");
      fire_flag == 1;
      send_multi_sms();
     //make_multi_call();
    }

  }
  //No fire is detected, turn OFF Alarm
  else
  {
    fire_flag = 0;
  }
}

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    send_sms("Women Harassment Alert! Vehicle Reg. No: Dhaka Metro GHA- XX-XXXX. Take Action Immediately.", PHONE_1);
  }
  if(PHONE_2 != ""){
    Serial.print("Phone 2: ");
    send_sms("This is 1st fire alert sms for our Smart Vehicle System.", PHONE_2);
  }
  if(PHONE_3 != ""){
    Serial.print("Phone 3: ");
    send_sms("This is 1st fire alert sms for our Smart Vehicle System.", PHONE_3);
  }
}
void send_sms(String text, String phone)
{
    Serial.println("sending sms....");
    delay(50);
    sim800L.print("AT+CMGF=1\r");
    delay(1000);
    sim800L.print("AT+CMGS=\""+phone+"\"\r");
    delay(1000);
    sim800L.print(text);
    delay(100);
    sim800L.write(0x1A); //ascii code for ctrl-26 //Serial2.println((char)26); //ascii code for ctrl-26
    delay(5000);
}
//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

//NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
/*void make_call(String phone)
{
    Serial.println("calling....");
    sim800L.println("ATD"+phone+";");
    delay(20000); //20 sec delay
    sim800L.println("ATH");
    delay(1000); //1 sec delay
}*/
