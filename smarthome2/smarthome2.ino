#include <Wire.h>


#define LED1 5
#define LED2 3
#define MOTIONSENSOR A0


volatile int motion;


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MOTIONSENSOR, INPUT);
  Serial.begin(9600);  
}


void loop() {
  motion = digitalRead(MOTIONSENSOR);
  Serial.print("Motion: ");
  Serial.println(motion);
  if (motion > 0){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW); //special LED
    delay(1000);
    if (motion < 0) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH); //special LED
    }
  }
  else {
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH); //special LED
  }
}
