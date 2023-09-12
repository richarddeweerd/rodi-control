#include <Arduino.h>
#include "config.h"
#include "TFT_Gui.h"

float test = 12.2;

TFT_eSPI tft;
GUI_Screen screen(&tft);
GUI_Page page_1(TFT_BLUE);
GUI_Page page_2(TFT_RED);
GUI_Form form_1(GUI_Viewport(10, 10, 300, 220), TFT_GREEN, TFT_WHITE);
GUI_Label label_1(GUI_Viewport(10, 10, 50, 30), TFT_BLACK, FF17, TL_DATUM, "Top Left");
GUI_Label label_2(GUI_Viewport(120, 10, 50, 30), TFT_BLACK, FF17, TC_DATUM, "Top Center");
GUI_Label label_3(GUI_Viewport(230, 10, 50, 30), TFT_BLACK, FF17, TR_DATUM, "Top Right");

GUI_Label label_4(GUI_Viewport(10, 90, 50, 30), TFT_BLACK, FF17, CL_DATUM, "Cent Left");
GUI_Label label_5(GUI_Viewport(120, 90, 50, 30), TFT_BLACK, FF17, CC_DATUM, "Cent Center");
GUI_Label label_6(GUI_Viewport(230, 90, 50, 30), TFT_BLACK, FF17, CR_DATUM, "Cent Right");

GUI_Label label_7(GUI_Viewport(10, 170, 50, 30), TFT_BLACK, FF17, BL_DATUM, "Bot Left");
GUI_Label label_8(GUI_Viewport(120, 170, 50, 30), TFT_BLACK, FF17, BC_DATUM, "Bot Center");
GUI_Label label_9(GUI_Viewport(230, 170, 50, 30), TFT_BLACK, FF17, BR_DATUM, String(test, 2));

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting...");

  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);

  tft.begin();
  tft.setRotation(1);        // landscape mode
  tft.fillScreen(TFT_BLACK); // Clear screen
  screen.init();
  page_1.addChild(&form_1);
  form_1.addChild(&label_1);
  form_1.addChild(&label_2);
  form_1.addChild(&label_3);
  form_1.addChild(&label_4);
  form_1.addChild(&label_5);
  form_1.addChild(&label_6);
  form_1.addChild(&label_7);
  form_1.addChild(&label_8);
  form_1.addChild(&label_9);
  screen.addPage(&page_1);
  screen.addPage(&page_2);
  screen.setActivePage(0);
}

void loop()
{
  // put your main code here, to run repeatedly:
}