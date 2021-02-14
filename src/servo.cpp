#include <Arduino.h>
#include <Servo.h>

// Servo 
#define SERVO D5 // yellow wire
Servo servo;
int pos = 0;

enum SERVO_POS {
    open = 180,
    closed = 90
};

void setup()
{
    servo.attach(SERVO);
    servo.write(pos);
}

void loop()
{
    while(pos <= open) {
      servo.write(pos);
      delay(15);
      LED.write(67) // blue
      pos++;
    }

    while(pos >= closed) {
      servo.write(pos);
      delay(15);
      pos--;
    }
}
