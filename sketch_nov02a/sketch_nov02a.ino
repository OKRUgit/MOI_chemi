#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // адрес, столбцов, строк

void setup() {
  lcd.init();           // инициализация
  lcd.backlight();      // включить подсветку

  lcd.setCursor(1, 0);  // столбец 1 строка 0
  lcd.print("Hello,yvsik.ru!");

  lcd.setCursor(4, 1);  // столбец 4 строка 1
  lcd.print("GyverKIT");
}

void loop() {
}
