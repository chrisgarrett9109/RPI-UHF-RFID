/*
test_buzz.c
2020-11-28
Chris Garrett

Tests buzzer sounds for valid + invalid tickets
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include "buzzer.h"

int main(int argc, char *argv[]) 
{

    // Initialize library
    if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialization failed\n");
      return 1;
   }

   init_buzzer(26);
}


/*******************************************
                buzzer_init
*******************************************/
int init_buzzer(int buzz_pin)
{
    gpioSetMode(buzz_pin, PI_OUTPUT);
    gpioSetPullUpDown(buzz_pin, PI_PUD_DOWN);
    gpioWrite(buzz_pin, 0);
    return(1);
}

/********************************************
                forward_buzz
- single buzz that lasts 2 seconds
- will indicate valid ticket
********************************************/
int forward_buzz(int buzz_pin)
{
    gpioWrite(buzz_pin, 1);
    sleep(2);
    gpioWrite(buzz_pin, 0);
    return(1);
}


/*******************************************
                reverse_buzz
- activates buzzer for 8 short pulses
- will indicate invalid ticket OR no ticket scanned
*******************************************/
int reverse_buzz(int buzz_pin) 
{
    int pulse_buzz() 
    {
        gpioWrite(buzz_pin, 1);
        usleep(800000);
        gpioWrite(buzz_pin, 0);
        usleep(800000);
        return(1);
    }

    for(int i = 0; i < 8; i++) 
     {
         pulse_buzz();
     }
     return(1);
}