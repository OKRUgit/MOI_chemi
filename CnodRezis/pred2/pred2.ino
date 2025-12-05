#include <LiquidCrystal_I2C.h>

// Инициализация LCD с адресом 0x27, 16 столбцов, 2 строки
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Константы для измерения ёмкости
const unsigned long CAPACITOR_CHECK_INTERVAL = 100;   // Период опроса в мс
const float REF_VOLTAGE = 644.0;                      // Примерно 65% от 1023 (для 3.3В на 5В)
const long RESISTOR_VALUE = 1000;                     // Сопротивление в Омах

// Переменные для измерений
unsigned long lastTime = 0;
unsigned long chargeTime = 0;
unsigned long dischargeTime = 0;
float capacitance = 0.0;
float zeroOffset = 0.0;

// Флаги состояния
bool measuringMicrofarads = false;  // true — измеряем в мкФ, false — в нФ
bool calibrationDone = false;       // Калибровка нуля выполнена

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Capacitance Test");

  pinMode(A0, INPUT);   // Датчик напряжения
  pinMode(3, OUTPUT);   // Пин для заряда/разряда
  pinMode(13, OUTPUT);  // Дополнительный пин для заряда
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= CAPACITOR_CHECK_INTERVAL) {
    lastTime = currentTime;
    performCapacitanceMeasurement();
  }
}

void performCapacitanceMeasurement() {
  // Шаг 1: Разряд конденсатора
  digitalWrite(3, LOW);
  digitalWrite(13, LOW);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  delay(10); // Короткая задержка для полного разряда

  // Шаг 2: Начало заряда через пин 13
  pinMode(13, OUTPUT);
  pinMode(3, INPUT); // Пин 3 как вход — высокий импеданс
  digitalWrite(13, HIGH);

  unsigned long startTime = micros();

  // Ожидание достижения порога напряжения
  while (analogRead(A0) < REF_VOLTAGE) {
    if (micros() - startTime > 1000000UL) {
      // Долгое время заряда — вероятно, большой конденсатор
      measuringMicrofarads = true;
      break;
    }
  }

  chargeTime = micros() - startTime;

  // Если зарядка заняла менее 1 мс, возможно, конденсатор мал или отсутствует
  if (chargeTime < 1000 && !measuringMicrofarads) {
    measuringMicrofarads = false;
  }

  // Шаг 3: Разряд для проверки времени
  digitalWrite(13, LOW);
  digitalWrite(3, LOW);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  delay(10);

  // Повторный цикл для точности (необязательно, но улучшает стабильность)
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(13, HIGH);
  startTime = micros();

  while (analogRead(A0) < REF_VOLTAGE) {
    if (micros() - startTime > 1000000UL) {
      break;
    }
  }

  dischargeTime = micros() - startTime;

  // Определяем ёмкость по времени заряда
  float timeMs = dischargeTime / 1000.0; // мс
  capacitance = timeMs / (RESISTOR_VALUE * 1.44); // Упрощённая формула RC

  // Компенсация нуля (калибровка при первом запуске)
  if (!calibrationDone && !measuringMicrofarads) {
    zeroOffset = capacitance + 0.02;  // Подстройка
    calibrationDone = true;
  }

  capacitance = abs(capacitance - zeroOffset);

  // Отображение результата на LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("C: ");

  if (dischargeTime >= 1000000UL) {
    lcd.print("BIG uF");
  } else if (capacitance < 0.001) {
    lcd.print("No Cap");
  } else {
    lcd.setCursor(3, 0);
    if (measuringMicrofarads) {
      lcd.print(capacitance, 3);
      lcd.print(" uF");
    } else {
      lcd.print(capacitance * 1000, 2); // в нФ
      lcd.print(" nF");
    }
  }

  // Индикатор активности
  lcd.setCursor(15, 0);
  lcd.print("*");
}