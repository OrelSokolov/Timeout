
#if(BOARD_TIMER1==1)
  #error ==> Timeout library coul'd not acquire TIMER1 resource
#else
  #define BOARD_TIMER1 1
#endif

