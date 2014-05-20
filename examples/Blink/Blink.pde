#include <Timeout.h>

#define toggle(pin) digitalWrite(pin, !digitalRead(pin))

void toggleLed(){
  toggle(13);
}

int main(void)
{
    Serial.begin(9600);
    Timer1.every(1000, toggleLed).start();
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    Serial.println("Start");

    while(1)
    {
    }
}
