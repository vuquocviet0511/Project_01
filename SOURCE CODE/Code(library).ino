#include <HardwareSerial.h>
#include <DFPlayerMini_Fast.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "distanceSensor.h"
#include "battery.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
DFPlayerMini_Fast myDFPlayer;


const int button1 = 2;
int trigPin1 = 8;
int echoPin1 = 9;
int trigPin2 = 6;
int echoPin2 = 7;
int trigPin3 = 4;
int echoPin3 = 5;
int rungPin = 13;
int percentage = 0;
int voltPin = A0;

float voltage = 0;
int duration1, distance1, duration2, distance2, duration3, distance3;




void setup() {
  Serial.begin(9600);
  
  pinMode(voltPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(rungPin, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  
  myDFPlayer.begin(Serial);
  myDFPlayer.volume(30);  // set volume 
  myDFPlayer.play(1);    // play default song "1.mp3"
  delay(6000);
  
}
void loop() {
  // Đo khoảng cách từ các cảm biến và lưu vào biến distance1, distance2, distance3
  int distance1, distance2, distance3;
  measureDistance(trigPin1, echoPin1, trigPin2, echoPin2, trigPin3, echoPin3, distance1, distance2, distance3);
  if (distance1 < 50 || distance2 < 50) {
      digitalWrite(rungPin, HIGH);
      myDFPlayer.play(2);
      delay(2000);  // debounce delay
    }
    else{
      digitalWrite(rungPin, LOW);
    }
    if (distance3 > 15) {
      digitalWrite(rungPin, HIGH);
      myDFPlayer.play(3);
      delay(2000);  // debounce delay
    }
    else{
      digitalWrite(rungPin, LOW);
    }
  // Đọc giá trị từ cảm biến ADC
  int volt = analogRead(voltPin);
  int percentage = calculateBatteryPercentage(voltPin);
  if (digitalRead(button1) == LOW) {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("pin: ");
    lcd.print(percentage);
    lcd.print("%");
    switch (percentage) {
      case 0 ... 20:
        myDFPlayer.play(4);
        delay(2000);
        break;
      case 21 ... 50:
        myDFPlayer.play(5);
        delay(2000);
        break;
      case 51 ... 90:
        myDFPlayer.play(6);
        delay(2000);
        break;
      default:
        myDFPlayer.play(7);
        delay(2000);
        break;
    }
    delay(1000);
    
  }
  if(percentage == 20 ){
        digitalWrite(rungPin, HIGH);
        myDFPlayer.play(4);delay(2000);  
        myDFPlayer.play(4);delay(2000);  
        myDFPlayer.play(4);delay(2000);
      }
      else{
        digitalWrite(rungPin, LOW);
      }
}


