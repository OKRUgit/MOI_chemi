// взято отсюда ..http://rcl-radio.ru/?p=43106

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();           // инициализация
 // lcd.backlight();      // включить подсветку
}
unsigned long time0, time1, time2; //time0, time1, time2: 
                                   // Это имена отдельных объявляемых переменных. 
                                   // Каждая из них будет unsigned long типом.
float c, null0;                    // Объявляет переменную c типа float
byte kn, mk, i;float               // null0 так обьявлять нельза она и так нУль
  lcd.setCursor(15, 0);
  lcd.print("*");
  if (mk == 0) {
    pinMode(13, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(13, HIGH);
  }

  if (mk == 1) {
    pinMode(3, OUTPUT);
    pinMode(13, INPUT);
    digitalWrite(3, HIGH);
  }

  time0 = micros();
  while (analogRead(A0) < 644) {
    time2 = micros() - time0;
    if (time2 >= 1000000 && mk == 0) {
      mk = 1;
      time0 = 100000000;
      break;
    }
  }

  time1 = micros() - time0;

  while (analogRead(A0) > 0) {
    pinMode(3, OUTPUT);
    pinMode(13, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(13, LOW);
  }

  if (mk == 1 && time1 < 1000) {
    mk = 0;
  }

  lcd.setCursor(1, 0);
  c = time1;
  c = c / 1000 - null0;
  c = abs(c);

  if (time1 >= 10000000) {
    lcd.setCursor(1, 0);
    lcd.print(" TEST uF   ");
  } else {                  // Вывод на LCD
    lcd.print(c);

    if (mk == 0) {
      lcd.print(" nF       ");
    }
    if (mk == 1) {
      lcd.print(" uF       ");
    }
  }
  if (i == 0) {              // калибровка нуля
    i++;
    null0 = c + 0.02;
  }
  delay(100);
}