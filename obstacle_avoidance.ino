#include "Ultrasonic.h"

#include <Servo.h>

Servo ser_pin;
Ultrasonic ultra(0,1);
Ultrasonic ultra2(2,8);

const int left_en=3;
const int right_en=11;
const int m1=6;
const int m2=7;
const int m3=4;
const int m4=5;

const int blink_right=A0;
const int blink_left=A1;
int right_turn=0;
int left_turn=0;

int turnL=0;
int turnR=0;

int dist;
int dist1;
float time_take=0.0;
int z=0;

void setup()
{

ser_pin.attach(9);
pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m4,OUTPUT);
pinMode(blink_left,OUTPUT);
pinMode(blink_right,OUTPUT);

}

void led_left()
{
digitalWrite(blink_left,HIGH);
delay(80);

digitalWrite(blink_left,LOW);
delay(80);
}

void led_right()
{
digitalWrite(blink_right,HIGH);

delay(80);

digitalWrite(blink_right,LOW);
delay(80);
}

void go_front()
{

digitalWrite(m1,HIGH);
digitalWrite(m2,LOW);

 
analogWrite(left_en,80);
digitalWrite(m3,LOW);

digitalWrite(m4,HIGH);

analogWrite(right_en,80);
}

void go_left()
{
digitalWrite(m1,LOW);

digitalWrite(m2,HIGH);
analogWrite(left_en,80);
digitalWrite(m3,LOW);
digitalWrite(m4,HIGH);
analogWrite(right_en,200);

led_left();
}

void go_right()
{
digitalWrite(m1,HIGH);
digitalWrite(m2,LOW);
analogWrite(left_en,200);

digitalWrite(m3,HIGH);
digitalWrite(m4,LOW);
analogWrite(right_en,80);
led_right();

}

void go_stop()
{
digitalWrite(m1,LOW);
digitalWrite(m2,LOW);
digitalWrite(m3,LOW);
digitalWrite(m4,LOW);
}

void go_back()

{
digitalWrite(m1,LOW);
digitalWrite(m2,HIGH);
analogWrite(left_en,100);
digitalWrite(m3,HIGH);
digitalWrite(m4,LOW);

analogWrite(right_en,100);
led_left();
led_right();
}

void loop()

{  ser_pin.write(90);

dist = ultra.Ranging(CM); dist1 = ultra2.Ranging(CM); delay(10);

if ((dist1<=6)&&(dist>10))
{
go_front();

}

 
else if ((dist1<=6)&&(dist<10))
{

go_stop();

delay(10);
go_back();
delay(10);
go_stop();
delay(10);
for(int i=90; i>25; i--)

{
ser_pin.write(i);
delay(10);
}
turnL = ultra.Ranging(CM);

delay(10);
for(int i=25; i<155; i++)

{
ser_pin.write(i);
delay(10);
}
turnR= ultra.Ranging(CM);
delay(10);

if (turnL > turnR)
{
go_left();

delay(600);
}
else

{
go_right();
delay(600);
}
}
else
{

go_back();

delay(200);
}

}
