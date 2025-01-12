#include "TinyDHT.h"
#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306
display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire, -1);
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(115200);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
Serial.println(F("SSD1306 allocation failed"))

Serial.begin(9600);
dht.begin();
delay(2000);
}


void loop() {
display.clearDisplay();

display.setTextSize(1);
display.setTextColour(WHITE);
display.setCursor(0,10);
display.println("hello world")
display.display();
delay(2000);
float hum = dht.readHumidity();
float tempc = dht.readTemperature();
float tempf = dht.readTemperature(true);
Serial.println(hum);
Serial.println(tempc);
Serial.println(tempf);


}
