#include <Servo.h>
#include <Wire.h>
#include <DS3231.h>
#include <LCD_I2C.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define thermistorPin A0
#define photoSensor A1
#define waterSensor A2
#define fanPin 5
#define trigPin 13
#define echoPin 12
#define servoGaragePin 10
#define pirSensorA 7
#define pirSensorB 6
#define motionLedB 8

// instance
RTSlib myRTC
LCD_I2C lcd(0x27, 16, 2);
Servo garageDoorServo;

unsigned long previousMillis = 0;
const long interval = 5000;
bool displayTemperature = false;

int valueA = 0;
int valueB= 0;

void setup() {
  Serial.begin(9600);
  Serial.println("READY :>");

  pinMode(fanPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motionLedA, OUTPUT);
  pinMode(motionLedB, OUTPUT);
  pinMode(pirSenorA, INPUT_PULLUP);
  pinMode(pirSenorB, INPUT_PULLUP);
  garageDoorServo.attach(servoGaragePin);

  Wire.begin();
  lcd.begin();
  lcd.backlight();
}

void loop() {
  unsigned long currentMillis = millis();

  // ------- Temp and Fan contols ---------
  float temp_value = analogRead(thermistorPin) + 200;
  if(temp_value >= 800) {
    digitalWrite(fanPin, HIGH);
    Serial.println("Fan ON");
  }
  else {
    digitalWrite(fanPin, LOW);
    serial.println("Fan OFF")
  }

  long period;
  int distance;
  digitalWrite(trinPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  period = pulseIn(echoPin, HIGH);
  distance = period * 0.034 / 2;

  // --------- Garage door servo ----------
  if (distance <= 100) {
    for(int angle=0; angle <= 100; angle += 1) {
      garageDoorServo(angle);
      delay(15);
      Serial.println("Garage door opening");
      break;

    }
    else {
      garageDoorServo.write(90);
    }
  }

  int photoSensorValue = analogRead(photoSensor);
  int proximityA = digitalRead(pirSensorA);
  int proximityB = digitalread(pirSensorB);

  if (proximityA == HIGH && photoSensorValue <= 500) {
    digitalWrite(motionLedB, HIGH);
    Serial.print("motion detected in roomB")
    if (valueA == LOW) {
      valueA = HIGH;
    }
    else {
      digialWrite(motionLedA, LOW);
      if (valueA == HIGH) {
        valueA = LOW;
      }
    }
  }

  if (proximityB == HIGH && photoSensorValue <= 500) {
    digitalWrite(motionLedB, HIGH);
    Serial.print("motion detected in roomB")
    if (valueB == LOW) {
      valueB = HIGH;
    }
    else {
      digialWrite(motionLedB, LOW);
      if (valueB == HIGH) {
        valueB = LOW;
      }
    }
  }

  DateTime now = myRTC.now();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DATE: ");
  lcd.print(now.month(), DEC)
  lcd.print('/');
  lcd.print(now.day(), DEC)
  lcd.print('/');
  lcd.print(now.year(), DEC)

  lcd.setCursor(0,1);
  lcd.print("");
  lcd.print(now.hour(), DEC)
  lcd.print(':');
  lcd.print(now.minute(), DEC)
  lcd.print(':');
  lcd.print(now.second(), DEC)

  //every five second display temperature
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("temp: ");
    lcd.print(temperature(temp_value));
    lcd.print(" C / ");
    lcd.setCursor(1,3);
    lcd.print(temperatureInF(Temperature(temp_value)));
    lcd.print(" F");
  }

  int level = analogRead(waterSensor)
;
  if (level > 250) {
    serial.println("excess water");
  }
  if (level > 100) {
    serial.println("excess water");
  }
  else {
    Serial.println("water ok");
  }
  delay(1000);

  Serial.print("Temperature: ");
  Serial.print(temp_value);
  Serial.print("| LightSensor: ");
  Serial.print(temp_value);
  Serial.print("| Distance Sensor: ");
  Serial.print(distance);

  Serial.print("| Water Sensor");
  Serial.print(level);
  Serial.print("| Proximity A:")
  Serial.print(proximityA);
  Serial.print("| Proximity B:")
  Serial.print(proximityB);
  Serial.print("| Distance:")
  Serial.print(distance);

}
