#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define GPS_TX 10
#define GPS_RX 11
#define GSM_TX 7
#define GSM_RX 8
#define BUZZER_PIN 2
#define LED_PIN 3
#define ULTRASONIC_TRIG_PIN 4
#define ULTRASONIC_ECHO_PIN 5
#define GAS_SENSOR_PIN A0
#define ACCELEROMETER_X A1
#define ACCELEROMETER_Y A2
#define ACCELEROMETER_Z A3

LiquidCrystal_I2C lcd(0x27, 16, 2);
TinyGPSPlus gps;
SoftwareSerial gpsSerial(GPS_TX, GPS_RX);
SoftwareSerial gsmSerial(GSM_TX, GSM_RX);

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();
      updateLCD("Lat: " + String(latitude, 6), "Lon: " + String(longitude, 6));
      if (isAccident()) {
        sendEmergencyAlert(latitude, longitude);
        activateAlarm();
        blinkLights();
      }
    }
  }
}

void updateLCD(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void sendEmergencyAlert(float lat, float lon) {}

void activateAlarm() {
  digitalWrite(BUZZER_PIN, HIGH);
}

void blinkLights() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}

bool isAccident() {
  return false;
}
