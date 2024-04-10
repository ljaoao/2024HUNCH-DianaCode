#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

LiquidCrystal_I2C lcd1(0x27, 16, 2);

#define LED1 0//always on
#define LED2 1//always on
#define LED3 2//only flashes when something is wrong
#define BUZZER1 3//Greenhouse buzzer
#define BUZZER2 4//Smart Home 1 buzzer
#define BUZZER3 5//Smart Home 2 buzzer
#define FAN 6

DHT11 dht11(A1);

int temperature = 0;
int humidity = 0;
int lightsflash = 0;
int buzzer = 0;
int fan = 0;
int tonepin = 3; //for buzzer

void setup() {
  Serial.begin (9600); // Set the serial port baud rate to 9600
  //pinMode(HUMIDITYSENSOR, INPUT);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  pinMode(BUZZER3, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  lcd1.init ();
  lcd1.backlight (); // Light up the backlight
  lcd1.setCursor (0,0);
}

void loop() {
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  digitalWrite(LED1, HIGH); //always on
  digitalWrite(LED2, HIGH); //always on
  lcd1.setCursor (0,0);
  lcd1.print("Temperature:"); // LED prints temp
  lcd1.print(temperature);
  lcd1.print("C");
  lcd1.setCursor(0,1);
  lcd1.print("Humidity:");
  lcd1.print(humidity);
  lcd1.print("%");

  if (temperature >= 29) { // greater than or equal to 29
    buzzer = 1;
    fan = 1;
    lightsflash = 1;
  }

  else if (temperature > 24) { // between 24 and 29, not including 24
    buzzer = 0;
    fan = 1;
    lightsflash = 1;
  }

  else if (temperature > 18) { // in between but not including 18 and 24
    buzzer = 0;
    fan = 0;
    lightsflash = 0;
  }

  else if (temperature > 13) { // in between but not including 13 and 18
    buzzer = 0;
    fan = 0;
    lightsflash = 1;
  }

  else { // below 13
    buzzer = 1;
    fan = 0;
    lightsflash = 1;
  }

  if (lightsflash == 1) {
    digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED3, LOW);
    delay(500);
    digitalWrite(LED3, HIGH);
    delay(500);
    digitalWrite(LED3, LOW);
    delay(500);
  }

  if (buzzer == 1) {
    tone(BUZZER1, 532);
    tone(BUZZER2, 532);
    tone(BUZZER3, 532);
    delay(50);
    tone(BUZZER1, 659);
    tone(BUZZER2, 659);
    tone(BUZZER3, 659);
    delay(100);
    noTone(BUZZER1);
    noTone(BUZZER2);
    noTone(BUZZER3);
  }

  if (fan == 1) {
    digitalWrite(FAN, HIGH);
  }

  else {
    digitalWrite(FAN, LOW);
  }
}