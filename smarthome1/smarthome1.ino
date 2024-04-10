//VERSION 3

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED1 10
#define LED2 6
#define MOTIONSENSOR A0
#define MOISTURESENSOR A1
#define RELAY 5
DHT11 dht11(A2);

int motion = 0;
int temperature = 0;
int humidity = 0;

void setup() {
  pinMode(MOISTURESENSOR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(RELAY, OUTPUT);
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

  int soilmoisture = analogRead(MOISTURESENSOR);
  Serial.print("Soil Moisture: ");
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

  motion = digitalRead(MOTIONSENSOR);
  Serial.print("Motion: ");
  Serial.println(motion);
  if (motion > 0){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(1000);
  }
  else {
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}