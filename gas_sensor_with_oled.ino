#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int gas;
const int ledg=6;
const int ledr=8;
const int buzz=2;
void setup()
{Serial.begin(9600);
  pinMode(A1,INPUT);
  pinMode(ledg,OUTPUT);
  pinMode(ledr,OUTPUT);
  pinMode(buzz,OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
 }
  
}

void loop()
{
  gas=analogRead(A1);
  if (gas<=100)
  {
    noTone(buzz);
    digitalWrite(ledg,HIGH);
    digitalWrite(ledr,LOW);
    delay(2000);
    display.clearDisplay();
  
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("NORMAL");
    display.setCursor(0,30);
    display.println(gas);
    display.display(); 
  }
  else
  {
    tone(buzz,1000);
    delay(5000);
    noTone(buzz);
    delay(1000);
    digitalWrite(ledg,LOW);
    digitalWrite(ledr,HIGH);
    
    delay(2000);
    display.clearDisplay();
  
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Dangerous");
    display.setCursor(0,30);
    display.println(gas);
    display.display(); 
  }
  
}
