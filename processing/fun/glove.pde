import processing.serial.*;

Serial serialPort;  // The serial port
PImage cow_photo, steak_1, steak_2;
PFont f;

double start = 0;
double end = 0;
double scene = 0;
float intensity = 0;

void setup() {
  // List all the available serial ports:
  //printArray(Serial.list());
  // Open the port you are using at the rate you want:
  serialPort = new Serial(this, Serial.list()[2], 115200);
  
  fullScreen();
  background(0);
  
  cow_photo = loadImage("cow_test.jpg");
  cow_photo.resize(displayWidth, displayHeight); 
  steak_1 = loadImage("steak_1.jpg");
  steak_1.resize(600, 600);
  steak_2 = loadImage("steak_2.jpg");
  steak_2.resize(600, 600);
  
  f = createFont("Nirmala Text Bold",40,true);
  textFont(f,60);
  fill(0);
}

void draw() {
  background(0);
  image(cow_photo, 0, 0);
  text(intensity, 650, 450);
  end = millis();
  if (end - start >= 1000) { scene = 0; }
  if (scene == 1) { image(steak_1, 450, 150); }
  if (scene == 2) { image(steak_2, 450, 150); }
  
  while (serialPort.available() > 0) {
    String inBuffer = serialPort.readString();  
    if (inBuffer != null) {
      println(inBuffer);
      
      float[] tokens = float(split(inBuffer, ", "));
      if (tokens.length <= 1) { continue; }
      
      if (tokens[0] == 0) {
        start = millis();
        scene = 1;
        println("jab");
      }
      else if (tokens[0] == 1) {
        start = millis();
        scene = 2;
        println("hook");
      }
      else {
        continue;
      }
      
      intensity = tokens[1];
      println("intensity: " + intensity);
      // change to rating
      
      // encouragement
    }
  }
}
