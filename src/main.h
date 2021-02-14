#ifndef MAIN_H 
#define MAIN_H

#include <Arduino.h>
#include <TM1637Display.h>
#include <Servo.h>


void displayClock(TM1637Display display, int seconds);
int convertSecondsToTime(int seconds);
void letUserConfigureTime();

#endif