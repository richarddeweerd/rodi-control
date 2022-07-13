#include <Arduino.h>
#include "config.h"
#include "TFT_Gui.h"

TFT_eSPI tft;
GUI_Screen screen(&tft);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting...");

  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_RED);
}

void loop()
{
  // put your main code here, to run repeatedly:
}