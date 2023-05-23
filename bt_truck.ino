char t;
#include<Servo.h>
Servo ser;
#define trigPin 7
#define echoPin 6
#define motor1 10
#define motor2 11
#define hrn 8
int duration;
int distance;
int safetyDistance = 6;
int check;
void setup()
{
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(motor1,OUTPUT);
pinMode(motor2,OUTPUT);
Serial.begin(9600);
ser.attach(9);
ser.write(90);
pinMode(hrn,OUTPUT);
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
}
void loop()
{
while(!Serial.available())
{
//do nothing
}
t = Serial.read();
Serial.println(t);
check = checkSafety();
if(check)
{
switch (t)
{
case 'F' :
forward();
break;
case 'B' :
reverse();
break;
case 'I' :
forwardRight();
break;
case 'G' :
forwardLeft();
break;
case 'H' :
reverseLeft();
break;
case 'J' :
reverseRight();
break;
case 'R' :
right();
break;
case 'L' :
left();
break;
case 'V' :
horn();
break;
case 'S' :
stop1();
break;
}
}
else
{
stop1();
digitalWrite(hrn,HIGH);
delay(200);
digitalWrite(hrn,LOW);
if(t=='B')
{
reverse();
delay(300);
}
}
}
void forward()
{
ser.write(90);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
}
void reverse()
{
ser.write(90);
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
}
void left()
{
ser.write(135);
}
void right()
{
ser.write(135);
}
void forwardLeft()
{
ser.write(135);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
}
void forwardRight()
{
ser.write(45);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
}
void reverseRight()
{
ser.write(45);
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
}
void reverseLeft()
{
ser.write(135);
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
}
void horn()
{
digitalWrite(hrn,HIGH);
delay(1000);
digitalWrite(hrn,LOW);
}
void stop1()
{
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
}
int checkSafety()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
Serial.println(distance);
if(safetyDistance>=distance)
{
return 0;
}
else
{
return 1;
}
}
