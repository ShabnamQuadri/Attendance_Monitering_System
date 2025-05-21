#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  oled.begin();
  oled.clearBuffer();
  oled.setFont(u8g2_font_5x7_tr);
  oled.drawStr(1, 10, "OLED Test");
  oled.sendBuffer();
}

void loop() {
}
