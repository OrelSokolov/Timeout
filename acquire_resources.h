
#if(BOARD_TIMER1==1)
  #error ==> Timer library coul'd not acquire TIMER0 resource
#else
  #define BOARD_TIMER1 1
#endif

