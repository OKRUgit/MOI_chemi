#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
}
// переменые
unsigned long timeMill = 0;
const long condesator = 100; //  для конденсатора
const long resistor = 1000;  //  для resistor
                             // condesator
unsigned long time0,time1,time2; 
float c=0;
float yvs0=0;
byte kn=0;
byte mk=0;
byte i=0;                    //  condesator


void loop() 
{
  unsigned long inerval = millis();
 if (inerval-timeMill>=condesator)
   {                          
    timeMill=inerval;         // Сохранить время последнего обновления
                              // далее полный код из проверки конденсатора
     
    // Ваш код, который должен выполняться каждую секунду
    // Например, мигание светодиода
    // digitalWrite(ledPin, !digitalRead(ledPin));
   }

  // Здесь может быть другой код, который будет выполняться без остановки
}