//VERSION 3

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED1 0//always on
#define LED2 1//always on
#define LED3 2//only flashes when something is wrong, white light
#define BUZZER1 3//Greenhouse buzzer
#define BUZZER2 4//Smart Home 1 buzzer
#define BUZZER3 5//Smart Home 2 buzzer
#define FAN 6

DHT11 dht11(A1);

int tonepin = 3; //for buzzer
int buzzer = 0;
int lights = 0;
int fan = 0;
int temperature = 0;
int humidity = 0;


void setup() {
  Serial.begin (9600); // Set the serial port baud rate to 9600
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  pinMode(BUZZER3, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  lcd.init ();
  lcd.backlight (); // Light up the backlight
  lcd.setCursor (3,0);
}

void loop() {
   int result = dht11.readTemperatureHumidity(temperature, humidity);
   if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } 
    else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }

  digitalWrite(LED1, HIGH); //always on
  digitalWrite(LED2, HIGH); //always on
  lcd.setCursor(0,0);
  lcd.print("Temperature: "); // LED prints temp
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity); // LED prints humidity
  lcd.print(" %");

  if (temperature >= 29) { // greater than or equal to 29
    buzzer = 1;
    fan = 1;
    lights = 1;
  }
  else if (temperature > 24) { // between 24 and 29, not including 24
    buzzer = 0;
    fan = 1;
    lights = 1;
  }
  else if (temperature > 18) { // in between but not including 18 and 24
    buzzer = 0;
    fan = 0;
    lights = 0;
  }
  else if (temperature > 13) { // in between but not including 13 and 18
    buzzer = 0;
    fan = 0;
    lights = 1;
  }
  else { // below 13
    buzzer = 1;
    fan = 0;
    lights = 1;
  }
 
  if (lights == 1) {
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