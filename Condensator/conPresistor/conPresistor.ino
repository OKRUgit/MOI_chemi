
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();               // инициализация
  lcd.backlight();          // включить подсветку
  pinMode(A0,INPUT);        // для проверки Конденсаторов
  
}
unsigned long time0,time1,time2; 
float c,null0;
byte kn,mk,i;
/* добавление переменных  resistor1*/
int Vin=5;        // напряжение на контакте 5V платы arduino
float Vout=0;     // напряжение на контакте A1 платы arduino
float R1=3300;    // значение сопротивления известного резистора
float R2=0;       // значение сопротивления неизвестного резистора
int a2d_data=0;   // Переменная  Резистров
float buffer=0;   // значение Резисторов

/* добавление переменных  resistor1*/
void loop(){ 
  lcd.setCursor(15,0); 
  lcd.print("*");
  if(mk==0){
    pinMode(13,OUTPUT);
    pinMode(3,INPUT);
    digitalWrite(13,HIGH);
  }

  if(mk==1){
    pinMode(3,OUTPUT);
    pinMode(13,INPUT);
    digitalWrite(3,HIGH);
  }

  time0=micros();
  while(analogRead(A0)<644){
    time2=micros()-time0;
    if(time2>=1000000 && mk==0){
      mk=1;
      time0=100000000;
      break;
    }
  }

  time1=micros()-time0; 

  while(analogRead(A0)>0){ 
    pinMode(3,OUTPUT); 
    pinMode(13,OUTPUT); 
    digitalWrite(3,LOW); 
    digitalWrite(13,LOW);
  }

  if(mk==1&&time1<1000){
    mk=0;
  }

  lcd.setCursor(1,0);
  c=time1;
  c=c/1000-null0;
  c=abs(c);

  if(time1>=10000000){
    lcd.setCursor(1,0);
    lcd.print(" TEST uF   "); 
  }
  else{
    lcd.print(c); 

    if(mk==0){
      lcd.print(" nF       ");
    }
    if(mk==1){
      lcd.print(" uF       ");
    }
  }
  if(i==0){// калибровка нуля
    i++;
    null0=c+0.02;
  }
 a2d_data=analogRead(A1);  // для проверки Резисторов
  if(a2d_data)
  {
    buffer=a2d_data*Vin;
    Vout=(buffer)/1024.0;
    buffer=Vout/(Vin-Vout); 
    R2=R1*buffer;
    lcd.setCursor(0,1);
    lcd.print("R=");
    lcd.print(R2);
    lcd.setCursor(14,1); 
    lcd.print("oM");
  }

  delay(100);
}
