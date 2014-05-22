#include <Timeout.h>

#define toggle(pin) digitalWrite(pin, !digitalRead(pin))

volatile short counter = 0;

void toggleLed(){
  toggle(13);
  if(counter>18){
    Timer1.kill();
  }
  counter++;
}

void setup()
{
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Serial.println("Start");
    Timer1.every(500, toggleLed).start();
}


void loop(){
  // Imitate some stuff
  delay(10000);
  Serial.println("100000ms left");
}
