#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();           // инициализация
  lcd.backlight();      // включить подсветку

  // строки для вывода
  char s1[] = "YVSIK-yvsik.ru";
  char s2[] = "OK pabotaet056";

  lcd.setCursor(1, 0);
  for (int i = 0; i < strlen(s1); i++) {
    lcd.print(s1[i]);
    delay(100);
  }

  lcd.setCursor(0, 1);
  for (int i = 0; i < strlen(s2); i++) {
    lcd.print(s2[i]);
    delay(100);
  }
}
void loop() {
}