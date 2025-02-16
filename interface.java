// Used in the Processing library/environment

import processing.serial.*;

Serial serialPort;

void setup() {
  //printArray(Serial.list());  // lists all the available serial ports
  serialPort = new Serial(this, Serial.list()[9], 115200);  // opens the serial port
}

void draw() {
  windowResize(displayWidth, displayHeight);
  background(51);
  // other initial designs
  
  while (serialPort.available() > 0) {
    String inBuffer = serialPort.readString();   
    if (inBuffer != null) {
      println(inBuffer);
      
      float[] tokens = float(split(inBuffer, ", "));
      //for (int i = 0; i < tokens.length; i++) {
      //  println("  " + tokens[i]);
      //}
      //println(tokens.length);
      
      if (tokens[0] == 0) {
        println("jab");
      }
      else if (tokens[0] == 1) {
        println("hook");
      }
      else {
        //println("continuing");
        continue;
      }
      
      float intensity = sqrt(pow(tokens[1], 2) + pow(tokens[2], 2) + pow(tokens[3], 2));
      println("intensity: " + intensity);
      // change to rating
      
      // encouragement
      
      //println();
    }
  }
}
