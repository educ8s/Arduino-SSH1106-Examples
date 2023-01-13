#include <GyverOLED.h>
#include "DHT.h"

#define DHTPIN 15    // Pin the DHT22 is connected to
#define DHTTYPE DHT22   // DHT22 sensor

GyverOLED<SSH1106_128x64> oled;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  delay(1000);
  initDisplay();
  printUI();
  oled.setScale(2);  
}

void loop()
 {  
  oled.setCursorXY(28, 28);
  oled.print(String(readTemperature(),1));
  oled.update();
  delay(2000);
}

float readTemperature() {
  float temperature = dht.readTemperature();
  return temperature;
}

void initDisplay()
{
  oled.init();  
  oled.clear();   
  oled.update(); 
}

void printUI()
{
  oled.home();   
  oled.rect(0,0,127,63,OLED_STROKE);
  oled.setCursorXY(30, 8);
  oled.setScale(1);
  oled.print("Temperature");
  oled.setScale(1);
  oled.setCursorXY(85, 25);
  oled.print("o");
  oled.setScale(2);
  oled.setCursorXY(92, 28);
  oled.print("C");
  oled.update();
}