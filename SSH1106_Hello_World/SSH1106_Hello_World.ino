#include <GyverOLED.h>

GyverOLED<SSH1106_128x64> oled;

void setup() {
  oled.init();  
  
  oled.clear();   
  oled.update(); 

  oled.setCursorXY(28, 26);   
  oled.print("Hello World!");
  oled.rect(0,0,127,63,OLED_STROKE);
  oled.update();
}

void loop() {    
}
