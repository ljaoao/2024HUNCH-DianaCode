//VERSION 3

#include <Wire.h>
#include <DHT11.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED1 5
#define LED2 3
#define MOTIONSENSOR A0
DHT11 dht11(A1);

int motion = 0;
int temperature = 0;
int humidity = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MOTIONSENSOR, INPUT);
  lcd.init ();
  lcd.backlight ();
  lcd.setCursor (3,0);  
  Serial.begin(9600);  
}

void loop() {
  dht11.readTemperatureHumidity(temperature, humidity);
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  motion = digitalRead(MOTIONSENSOR);
  Serial.print("Motion: ");
  Serial.println(motion);
  if (motion > 0){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW); //special LED
    delay(1000);
  }
  else {
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH); //special LED
  }
}