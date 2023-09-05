#include <DFPlayerMini_Fast.h>
DFPlayerMini_Fast myDFPlayer;

int button1 = 11;
int trigPin1 = 8;
int echoPin1 = 9;
int trigPin2 = 6;
int echoPin2 = 7;
int trigPin3 = 4;
int echoPin3 = 5;
int rungPin = 13;

int voltPin = A0;
float correctionfactor = .3;
float voltage = 0;
float vout = 0;
float R1=33000.0;
float R2=7500.0;

void setup() {
  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  
  pinMode(voltPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(rungPin, OUTPUT);  

  myDFPlayer.begin(Serial);
  myDFPlayer.volume(30);  // set volume 30%
  myDFPlayer.play(1);    // play default song "1.mp3"
  delay(5500);
}

void loop() {
  long duration1, distance1, duration2, distance2, duration3, distance3;
  // Đo khoảng cách từ cảm biến 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

// Đo khoảng cách từ cảm biến 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  //Đo khoảng cách từ cảm biến 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;
  
  // In ra màn hình khoảng cách từ từng cảm biến  
  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm");
  Serial.print(" | Distance2: ");
  Serial.print(distance2);
  Serial.print(" cm");
  Serial.print(" | Distance3: ");
  Serial.print(distance3);
  Serial.println(" cm");

  if (distance1 < 50 || distance2 < 50 ) {
    digitalWrite(rungPin, HIGH);
    myDFPlayer.play(2);
    delay(2000);  // debounce delay
    
  }
  else{
    digitalWrite(rungPin, LOW);
    
  }
  if ( distance3 > 15) {
    digitalWrite(rungPin, HIGH);
    myDFPlayer.play(3);
    delay(2000);  // debounce delay
    
    
  }
  else{
    digitalWrite(rungPin, LOW);
    
  }

  //pin
  int volt = analogRead(voltPin);
  float vout = (volt * 5.0 ) / 1024.0 ;
  float voltage = vout / ( R2/(R1 + R2)) ;
  voltage = voltage + correctionfactor;
  int percentage = 0;

  if (voltage < 6) {
    percentage = 0;
  } else {
    percentage = ((voltage - 6) / (8.4 - 6)) * 100;
  } 
  if (digitalRead(button1) == LOW) {
    delay(1500);
    switch (percentage) {
    case 0 ... 20:
      myDFPlayer.play(4);
      delay(1500);
      break;
    case 21 ... 50:
      myDFPlayer.play(5);
      delay(1500);
      break;
    case 51 ... 90:
      myDFPlayer.play(6);
      delay(1500);
      break;
    case 91 ... 100:
      myDFPlayer.play(7);
      delay(1500);
      break;
  }
  }
// báo pin khi hết pin
  if(percentage == 20 ){
        digitalWrite(rungPin, HIGH);
        myDFPlayer.play(4);delay(1500);  
        myDFPlayer.play(4);delay(1500);  
        myDFPlayer.play(4);delay(1500);
  }
  else{
        digitalWrite(rungPin, LOW);
      }
}

