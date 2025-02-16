//https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

double ax_tuning = 0;
double ay_tuning = 0;
double az_tuning = 0;
sensors_event_t a, g, temp;
double max_val = 0;

void setup(void) {
  pinMode(18, INPUT);
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);

  delay(100);
}

void loop() {  
  /* Get new sensor events with the readings */
  getData();
  /* Print out the values */
//Jab = 0
  if(a.acceleration.x < -25)
  {
    double starttime = millis();
    double endtime = starttime;
    while ((endtime-starttime) <= 200)
    {
      getData();
      double temp_val = sqrt(pow(a.acceleration.x, 2)+pow(a.acceleration.y, 2)+pow(a.acceleration.z, 2));
      if (temp_val > max_val) { max_val = temp_val; }
      endtime = millis();
      delay(5);
    } 
    Serial.print("0");
    Serial.print(", ");
    Serial.println(max_val);
    delay(800);
    max_val = 0;
  }

//Hook = 1
  if(a.acceleration.x > 25)
  {
    double starttime = millis();
    double endtime = starttime;
    while ((endtime-starttime) <= 200)
    {
      getData();
      double temp_val = sqrt(pow(a.acceleration.x, 2)+pow(a.acceleration.y, 2)+pow(a.acceleration.z, 2));
      if (temp_val > max_val) { max_val = temp_val; }
      endtime = millis();
      delay(5);
    } 
    Serial.print("1");
    Serial.print(", ");
    Serial.println(max_val);
    delay(800); 
    max_val = 0;
  }

  if (digitalRead(18) == HIGH) 
  { 
    ax_tuning = ax_tuning + a.acceleration.x;
    ay_tuning = ay_tuning + a.acceleration.y;
    az_tuning = az_tuning + a.acceleration.z;
  }

  delay(5);
}

void getData()
{
  mpu.getEvent(&a, &g, &temp);
  a.acceleration.x = a.acceleration.x - ax_tuning;
  a.acceleration.y = a.acceleration.y - ay_tuning;
  a.acceleration.z = a.acceleration.z - az_tuning;
}