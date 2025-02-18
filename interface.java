import processing.serial.*;
import processing.sound.*;
SoundFile sound;

Serial serialPort;
PImage photo1;
PImage photo2;
int type = -1;
float intensity = -1;
float max_intensity = -1;
PFont knockdown;

void setup() {
  //printArray(Serial.list());  // lists all the available serial ports
  serialPort = new Serial(this, Serial.list()[9], 115200);  // opens the serial port
  windowResize(displayWidth, displayHeight);
  background(237, 232, 208);
  photo1 = loadImage("boxing_gloves.jpeg");
  photo2 = loadImage("cat.jpeg");
  textSize(100);
  knockdown = createFont("knockdown.ttf", 100);
  textFont(knockdown);
  sound = new SoundFile(this, "punch.mp3");
}

void draw() {
  background(237, 232, 208);
  image(photo1, 30, 30, 300, 200);
  image(photo2, 1170, 30, 200, 200);
  if (type == 0) {
    fill(204, 17, 0);
    text("Jab!", 650, 200);
  }
  else if (type == 1) {
    fill(204, 17, 0);
    text("Hook!", 650, 200);
  }
  if (intensity != -1) {
    text("Intensity: " + intensity, 475, 375);
    text("Intensity to beat: " + max_intensity, 325, 475);
  }
  String[] encouragement = {"Nice work!", "Keep going!", "You got this!"};
  if (type != -1) {
    text(encouragement[type], 550, 650);
  }
  
  while (serialPort.available() > 0) {
    String inBuffer = serialPort.readString();   
    if (inBuffer != null) {
      println(inBuffer);
      
      float[] tokens = float(split(inBuffer, ", "));
      //for (int i = 0; i < tokens.length; i++) {
      //  println("  " + tokens[i]);
      //}
      //println(tokens.length);
      
      sound.play();
      
      if (tokens[0] == 0) {
        println("jab");
        type = 0;
      }
      else if (tokens[0] == 1) {
        println("hook");
        type = 1;
      }
      else {
        //println("continuing");
        continue;
      }
      
      println("intensity: " + tokens[1]);
      intensity = tokens[1];
      if (intensity > max_intensity) {
        max_intensity = intensity;
      }
    }
  }
}