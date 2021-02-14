#include "main.h"

// Module connection pins (Digital Pins)
// Buttons
#define START_COUNTDOWN_BUTTON D0   // white wire
#define SET_TIME_BUTTON D1          // orange wire
// Display
#define CLK D2                      // blue wire
#define DIO D3                      // green wire
// Servo 
#define SERVO D5                    // yellow wire


// TM1637Display
TM1637Display display(CLK, DIO);
#define SHOW_COLON 0x40             //shows colon between numbers (for HH:MM format)

// TIMER
int time_in_seconds;
boolean is_time_set;
const int MAX_TIME_SHORT_PRESS = 500; // max time for short_press in ms (above is long)

int time_button_last_state;
int time_button_pressed;
int counter_during_long_press;

//SERVO
enum SERVO_POS {
    open = 180,
    locked = 90
};
Servo servo;
int servo_pos;


void setup()
{
  // Display
  display.setBrightness(0x09);

  //Servo
  servo.attach(SERVO);
  servo_pos = SERVO_POS::open;
  servo.write(servo_pos);

  //Buttons
  pinMode(SET_TIME_BUTTON, INPUT);
  pinMode(START_COUNTDOWN_BUTTON, INPUT);
  time_button_last_state = HIGH; //Button not pressed at beginning

  //Time
  time_in_seconds = 0;
  is_time_set = false;
}

void loop()
{
  // Set time
  if (!is_time_set)
  {
    int countdown_button = digitalRead(START_COUNTDOWN_BUTTON);
    if (countdown_button == LOW)
    {
      is_time_set = true;
      //TODO check if box is closed
      servo.write(SERVO_POS::locked);
    }
    else
    {
      letUserConfigureTime();
    }
  }
  // Count down time to 0
  else
  {
    if (time_in_seconds > 0)
    {
      delay(1000);
      time_in_seconds--;
    }
    else
    {
      servo.write(SERVO_POS::open);
      is_time_set = false;
    }
  }

  displayClock(display, time_in_seconds);
}

// Shows time on TM1637Display
// e.g. 5672s -> 01:34 (HH:MM)
void displayClock(TM1637Display display, int seconds)
{
  int time = convertSecondsToTime(seconds);
  display.showNumberDecEx(time, SHOW_COLON, true);
}

// Converts seconds to clock decimal format
// e.g. 3660s -> 301 (for clock 03:01)
int convertSecondsToTime(int seconds)
{
  int hours = seconds / 3600;
  seconds -= hours * 3600;
  int minutes = seconds / 60;

  int time = minutes;  //xx:MM
  time += hours * 100; //HH:xx

  return time;
}

void letUserConfigureTime()
{
  int button_state = digitalRead(SET_TIME_BUTTON);

  // Button state changed?
  if (time_button_last_state != button_state)
  {
    if (button_state == LOW)
    {
      // Button pressed
      time_in_seconds += 60;
      time_button_pressed = millis();
    }
    else
    {
      // Button released
      time_button_pressed = 0;
    }
    time_button_last_state = button_state;
  }

  // Button hold?
  int time_diff = millis() - time_button_pressed;
  if (time_button_pressed > 0 && time_diff > MAX_TIME_SHORT_PRESS && button_state == LOW)
  {
    time_in_seconds += (60 * 5);
    delay(500);
  }
}