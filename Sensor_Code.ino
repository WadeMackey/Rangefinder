/**
 * @author Wade Mackey
 * 
 * This file uses the sonar sensor to detect the distance from the forward object and outputs the range to the display in centimeters.
 * If the range is less than 10cm a warning message will be displayed, and the LED on the arduino will flash.
 */
#define trigPin 9
#define echoPin 10

//Flashing LED on Arduino board
#define LEDPin 13

//LCD
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal.h>

  
#define BACKLIGHT_PIN   3
#define En_pin  8
#define Rw_pin  1
#define Rs_pin  12
#define D4_pin  5
#define D5_pin  4
#define D6_pin  3
#define D7_pin  2

int n = 1;

LiquidCrystal  lcd(Rs_pin,En_pin,D4_pin,D5_pin,D6_pin,D7_pin);


void setup ()
{
  analogWrite(6,75);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  //The transmit pin of the ultrasonic sensor
  pinMode(echoPin, INPUT);   //The receive pin of the ultrasonic sensor
  pinMode(LEDPin, OUTPUT);   //The LED of the Arduino

  lcd.begin (16,4);  //Size of LCD
 
// Switch on the backlight
//  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
//  lcd.setBacklight(HIGH);
  lcd.home ();                // go home

}

void loop()
{
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance =(duration/2) / 29.1;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance To Obj");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print("cm");
  if (distance >=10)
  {
    lcd.setCursor(0,4);
    lcd.print("Safe Zone :)");
    digitalWrite(LEDPin,HIGH);
      delay(500);
      digitalWrite(LEDPin,LOW);
      delay(500);
   
  }
    else
  {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Object Too Close!");
      lcd.setCursor(0,1);
      lcd.print("Object Too close!");
      lcd.setCursor(0,2);
      lcd.print("Object too close!");
      lcd.setCursor(0,3);
      lcd.print("Object too close!");

      for(int i = 1; i < 10; i++)
      {
        digitalWrite(LEDPin,HIGH);
        delay(50);
        digitalWrite(LEDPin,LOW);
        delay(50);
      }
  }

}
