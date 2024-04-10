#include <Wire.h>
#include <DHT11.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED1 3
#define LED2 5
#define MOTIONSENSOR A0

DHT11 dht11(A1);

int motion = 0;
int temperature = 0;
int humidity = 0;

void setup() {
  Serial.begin (9600); // Set the serial port baud rate to 9600
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MOTIONSENSOR, INPUT);
  lcd.init ();
  lcd.backlight ();
  lcd.setCursor (3,0);
Serial.begin(9600);
}

void loop() {
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  motion = analogRead(MOTIONSENSOR);
  if (motion > 0)
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(1000);

    if (motion < 0) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
    }
  }

  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}