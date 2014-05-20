#include "Timeout.h"
#include <avr/interrupt.h>

#define F_CPU 16000000

void (*timeoutCallback)();
void stub(){}

Timeout Timer1;

ISR(TIMER1_COMPA_vect)
{
  TCNT1=0; // reset Timer
  (*timeoutCallback)();
  if(!Timer1.every_flag){
    Timer1.kill();}
}

Timeout::Timeout(){
  configure(1000, stub);
}

Timeout Timeout::delay(short delay_ms, void (*callback)()){
  configure(delay_ms, callback, false);
  return Timer1;
}

Timeout Timeout::every(short delay_ms, void (*callback)()){
  configure(delay_ms, callback, true);
  return Timer1;
}

void Timeout::configure(short delay_ms, void (*callback)(), bool every_arg){
    every_flag = every_arg;
    short prescaler = 1024;
    setPrescaler(prescaler);

    OCR1A= int(delay_ms*F_CPU/prescaler/1000); // 1000 ms in 1 second
    timeoutCallback = callback;
}

void Timeout::setPrescaler(short value){
  switch(value){
    case 1:
      TCCR1B |= (0 << CS12)|(0 << CS11)|(1 << CS10);
      break;
    case 8:
      TCCR1B |= (0 << CS12)|(1 << CS11)|(0 << CS10);
      break;
    case 64:
      TCCR1B |= (0 << CS12)|(1 << CS11)|(1 << CS10);
      break;
    case 256:
      TCCR1B |= (1 << CS12)|(0 << CS11)|(0 << CS10);
      break;
    case 1024:
      TCCR1B |= (1 << CS12)|(0 << CS11)|(1 << CS10);
      break;
    default:
      TCCR1B |= (0 << CS12)|(0 << CS11)|(0 << CS10);
      break;
  }

}

void Timeout::start(){
    TCNT1 = 0; // reset
    TIMSK1 = (1<< OCIE1A); // allow interrupt on compare
    sei();
}


void Timeout::kill(){
  TIMSK1 = (0<< OCIE1A); //disable interrupts on compare
  cli();
}

