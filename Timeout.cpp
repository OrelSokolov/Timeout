#include "Timeout.h"
#include <avr/interrupt.h>

#define F_CPU 16000000

#define SET(V,bit) V|=(1<<bit)
#define RESET(V,bit) V&=~(1<<bit)

#define interrupts() sei()
#define noInterrupts() cli()

static void (*timeoutCallback)();
static void stub(){}

Timeout Timer1;

ISR(TIMER1_COMPA_vect)
{
  // Calling timeoutCallback can damage
  // some data, because of changing data in
  // status register. So, we need to save SREG
  short SREG_before_interrupt = SREG;
  (*timeoutCallback)();
  if(!Timer1.every_flag){
    Timer1.kill();}
  SREG = SREG_before_interrupt;
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
    short ms = (delay_ms<8000 && delay_ms > 1)? delay_ms : 100;
    every_flag = every_arg;
    prescaler = 1024;
    timeoutCallback = callback;
    noInterrupts();
      // Clear registers to avoid bugs
      TCCR1A = 0;
      TCCR1B = 0;
      TCNT1  = 0;

      SET(TCCR1B, WGM12); // CTC mode
      SET(TIMSK1, OCIE1A); // allow interrupt on compare

      OCR1A = int(ms*F_CPU/prescaler/1000);
    interrupts();
}

void Timeout::setPrescaler(short value){
  switch(value){
    case 1:
      RESET(TCCR1B, CS12);
      RESET(TCCR1B, CS11);
        SET(TCCR1B, CS10);
      break;
    case 8:
      RESET(TCCR1B, CS12);
        SET(TCCR1B, CS11);
      RESET(TCCR1B, CS10);
      break;
    case 64:
      RESET(TCCR1B, CS12);
        SET(TCCR1B, CS11);
        SET(TCCR1B, CS10);
      break;
    case 256:
        SET(TCCR1B, CS12);
      RESET(TCCR1B, CS11);
      RESET(TCCR1B, CS10);
      break;
    case 1024:
        SET(TCCR1B, CS12);
      RESET(TCCR1B, CS11);
        SET(TCCR1B, CS10);
      break;
    default:
      RESET(TCCR1B, CS12);
      RESET(TCCR1B, CS11);
      RESET(TCCR1B, CS10);
      break;
  }
}

void Timeout::start(){
  noInterrupts();
    setPrescaler(prescaler);
  interrupts();
}


void Timeout::kill(){
  setPrescaler(0);
}


#undef interrupts
#undef noInterrupts
