#if !defined(BOARD)
  #error ===> Arduino board is not defined. Definig Arduino UNO board looks like "#define BOARD UNO"
#endif

#ifndef BOARD_RESOURCES_INITIALIZED
  #if(BOARD==UNO || BOARD==NANO)
    #define BOARD_PIN1  0
    #define BOARD_PIN2  0
    #define BOARD_PIN3  0
    #define BOARD_PIN4  0
    #define BOARD_PIN5  0
    #define BOARD_PIN6  0
    #define BOARD_PIN8  0
    #define BOARD_PIN9  0
    #define BOARD_PIN10 0
    #define BOARD_PIN11 0
    #define BOARD_PIN12 0
    #define BOARD_PIN13 0

    #define BOARD_TIMER0 0
    #define BOARD_TIMER1 0
    #define BOARD_TIMER2 0

    #define BOARD_INTERRUPT_0 0
    #define BOARD_INTERRUPT_1 0
  #endif

  #define BOARD_RESOURCES_INITIALIZED
#endif
