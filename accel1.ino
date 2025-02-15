// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/
//https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/

#include <Adafruit_MPU6050.h>
#include "BluetoothSerial.h"
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
BluetoothSerial SerialBT;

double x_tuning = 0;
double y_tuning = 0;
double z_tuning = 0;
sensors_event_t a, g, temp;

void setup(void) {
  pinMode(19, OUTPUT);
  pinMode(18, INPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
  while (!Serial)
    delay(10);
  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  delay(100);
}

void loop() {  
  /* Get new sensor events with the readings */
  mpu.getEvent(&a, &g, &temp);
  a.acceleration.x = a.acceleration.x - x_tuning;
  a.acceleration.y = a.acceleration.y - y_tuning;
  a.acceleration.z = a.acceleration.z - z_tuning;
  /* Print out the values */
  Serial.print("X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println("");

  if (digitalRead(18) == HIGH) 
  { 
    x_tuning = x_tuning + a.acceleration.x;
    y_tuning = y_tuning + a.acceleration.y;
    z_tuning = z_tuning + a.acceleration.z;
    digitalWrite(19, HIGH); 
  }
  else { digitalWrite(19, LOW); } 

  delay(100);
}