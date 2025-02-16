//https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/

#include <Adafruit_MPU6050.h>
#include "BluetoothSerial.h"
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
BluetoothSerial SerialBT;

double ax_tuning = 0;
double ay_tuning = 0;
double az_tuning = 0;
double gx_tuning = 0;
double gy_tuning = 0;
double gz_tuning = 0;
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
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  delay(100);
}

void loop() {  
  /* Get new sensor events with the readings */
  mpu.getEvent(&a, &g, &temp);
  a.acceleration.x = a.acceleration.x - ax_tuning;
  a.acceleration.y = a.acceleration.y - ay_tuning;
  a.acceleration.z = a.acceleration.z - az_tuning;
  g.gyro.x = g.gyro.x - gx_tuning;
  g.gyro.y = g.gyro.y - gy_tuning;
  g.gyro.z = g.gyro.z - gz_tuning;
  /* Print out the values */
  Serial.print("X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.print(" ");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println("");
/*
//Punch type identification
  if(a.acceleration.x < 10 && a.acceleration.y < 10 && a.acceleration.z > 50)
  {
     Serial.println("Uppercut punch identified");
     delay(1000);
  }

  if(a.acceleration.x > 50 && a.acceleration.y > 50 && a.acceleration.z < 10)
  {
     Serial.println("Hook punch identified");
     delay(1000);
  }

  if(a.acceleration.x < 10 && a.acceleration.y > 50 && a.acceleration.z < 10)
  {
     Serial.println("Jab punch identified");
     delay(1000);
  }
*/
  if (digitalRead(18) == HIGH) 
  { 
    ax_tuning = ax_tuning + a.acceleration.x;
    ay_tuning = ay_tuning + a.acceleration.y;
    az_tuning = az_tuning + a.acceleration.z;
    gx_tuning = gx_tuning + g.gyro.x;
    gy_tuning = gy_tuning + g.gyro.y;
    gz_tuning = gz_tuning + g.gyro.z;
    digitalWrite(19, HIGH); 
  }
  else { digitalWrite(19, LOW); } 

  delay(100);
}