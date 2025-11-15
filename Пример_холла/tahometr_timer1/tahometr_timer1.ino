#include <TimerOne.h>
#include <LiquidCrystal.h>
LiquidCrystal  lcd(9, 8, 7, 6, 5, 4);
const int RPM_PIN=3;
volatile int rpm                = 0;
volatile int rpm_tik            = 0;   // иИмпульсы тахометра
volatile boolean kontrol;
volatile int rpm_array[3] = {0,0,0};   // массив для усреднения
volatile int rpm_result         = 0;   // частота вращения
void rpm_count(){
  rpm_tik++;
}
void SensorData(){
  rpm = rpm_tik;
  rpm_tik = 0;
  digitalWrite(10, HIGH);
  delayMicroseconds(500);
  digitalWrite(10, LOW);
}
void setup(){
  lcd.begin(16, 2); 
   pinMode(RPM_PIN,INPUT);
   attachInterrupt(digitalPinToInterrupt(RPM_PIN),  rpm_count,  RISING);
   Timer1.attachInterrupt(SensorData);
   Timer1.initialize(1000000);
   pinMode(10, OUTPUT);
}
void loop(){
    rpm_result = 0;
    for (int i=0; i<=1; i++)    {
      rpm_array[i]=rpm_array[i+1];
    }    
    rpm_array[2] = 60*rpm/2;
    for (int i=0; i<=2; i++)    {
      rpm_result = rpm_result+rpm_array[i]; 
    } 
    rpm_result = rpm_result/3;
    lcd.setCursor(0, 0);
    lcd.print("                ");   
    lcd.setCursor(0, 0);
    lcd.print("N(ob/min): ");lcd.print(rpm_result);
    lcd.setCursor(0, 1);
    lcd.print("                ");   
    lcd.setCursor(0, 1);
    lcd.print("V(m/min):  "); 
    lcd.print(rpm_result*3.14*3/1000); // пересчёт частоты вращения в скорость резания при диаметре фрезы 3 мм
    delay(500);
}
