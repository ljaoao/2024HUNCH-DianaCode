#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED1 10
#define LED2 6
#define MOTIONSENSOR A0
#define HUMIDITYSENSOR A1
#define RELAY 5

DHT11 dht11(A2);

volatile int motion;
int temperature = 0;
int humidity = 0;

//int button;
//int tomepin = 3;

void setup() {
  //pinMode(HUMIDITYSENSOR, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  //pinMode(FAN, OUTPUT)
  //pinMode(BUTTON, INPUT);
  //pinMode(BUZZER, OUTPUT)
  pinMode(MOTIONSENSOR, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(HUMIDITYSENSOR, INPUT);
  lcd.init ();
  lcd.backlight ();
  lcd.setCursor (3,0);
  Serial.begin(9600);
}

void loop() {
  int soilhumidity = analogRead(HUMIDITYSENSOR);
  int result = dht11.readTemperatureHumidity(temperature, humidity);
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  if (soilhumidity < 300) {
    digitalWrite(RELAY, HIGH);
    delay(500);//irrigation delay
  }

  else {
    digitalWrite(RELAY, LOW);
  }

  //button = digitalRead(BUTTON, INPUT)
  //if (button == LOW) {
    //for(pos = 0; pos < 180; pos += 1)
    //{

//myservo.write (pos); // The servo angle is pos
//delay (15); // Delay 15ms
  //}

    // angle from 0 to 180 degrees
    //delay(1000000)
    //for(pos = 0; pos > 180; pos -= 1)// angle from 180 to 0 degrees
//{

//myservo.write (pos); // The servo angle is pos
//delay (15); // Delay 15ms
  //}

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