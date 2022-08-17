int sensorValue;
int digitalValue;
#define RELAY_PIN  3
void setup()
{
  Serial.begin(9600); // sets the serial port to 9600
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); 
}

void loop()
{
  sensorValue = analogRead(0); // read analog input pin 0
  digitalValue = digitalRead(2);
  if (sensorValue > 400)
  {
    digitalWrite(RELAY_PIN, LOW); 
    digitalWrite(13, HIGH);
  }
  else
    digitalWrite(13, LOW);
    digitalWrite(RELAY_PIN, HIGH); 
  Serial.println(sensorValue, DEC); // prints the value read
  Serial.println(digitalValue, DEC);
  delay(1000); // wait 100ms for next reading
}
