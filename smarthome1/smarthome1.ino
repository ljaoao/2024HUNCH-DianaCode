#include <Wire.h>


#define LED1 9
#define LED2 2
#define MOTIONSENSOR A0
#define MOISTURESENSOR A1
#define RELAY 7


volatile int motion;


void setup() {
  pinMode(MOISTURESENSOR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(MOTIONSENSOR, INPUT);
  Serial.begin(9600);  
}


void loop() {
  int soilmoisture = analogRead(MOISTURESENSOR);
  Serial.println(soilmoisture);  //checking soil moisture value/debugging
  if (soilmoisture < 300) {
    // x < 300 is dry
    digitalWrite(RELAY, HIGH);
    delay(500);//irrigation delay
  }
  else {
    // x>300 is wet
    digitalWrite(RELAY, LOW);
  }


  motion = analogRead(MOTIONSENSOR);
  if (motion > 0){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(1000);


    if (motion < 0) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
    }
  }
  else {
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
   
  }
}
