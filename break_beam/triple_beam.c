#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include "triple_beam.h"


int main(int argc, char *argv[]) {

    // Initialize library
    if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialization failed\n");
      return 1;
   }



   beam_init(23, 13);
   beam_read(23, "The first");

   beam_init(16, 13);
   beam_read(16, "The Second");

   beam_init(25, 13);
   beam_read(25, "The Last");




   // pin_1 = receiver pin (non-PWM)
   // pin_2 = LED pin (PWM)
   int beam_init(int pin_1, int pin_2) {
       gpioSetMode(pin_1, PI_INPUT);
       gpioSetMode(pin_2, PI_OUTPUT);
       gpioSetPullUpDown(pin_1, PI_PUD_UP);
       gpioSetPullUpDown(pin_2, PI_PUD_OFF);
       gpioWrite(pin_1, 1);
       gpioWrite(pin_2, 1);
       gpioHardwarePWM(pin_2, 38000, 500000);       
   }


    int beam_read(int pin, char beam[20]) {
    while(1) {
           if(gpioRead(pin) == 0) { 
                printf("%s beam is connected\n", beam);
            } else if(gpioRead(pin) == 1) {
                printf("%s beam is NOT connected\n", beam);
            }
            else{
                printf(" \n");
            }
            usleep(1000000);
       }
    }
}