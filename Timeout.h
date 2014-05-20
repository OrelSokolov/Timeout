#ifndef timeout_h
#define timeout_h

#include "acquire_resources.h"

class Timeout{
  public:
    bool every_flag;

    Timeout();
    Timeout delay(short delay_ms, void (*callback)());
    Timeout every(short delay_ms, void (*callback)());
    void start();
    void kill();
  private:
    void setPrescaler(short value);
    void configure(short delay_ms, void (*callback)(), bool every = false);
};

extern Timeout Timer1;

#endif
