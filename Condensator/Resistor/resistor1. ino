//https://microkontroller.ru/arduino-projects/ommetr-na-arduino-uno/#:~:text=%D0%94%D0%BB%D1%8F%20%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F%20%D1%81%D0%BE%D0%BF%D1%80%D0%BE%D1%82%D0%B8%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F%20%D1%80%D0%B5%D0%B7%D0%B8%D1%81%D1%82%D0%BE%D1%80%D0%BE%D0%B2%20%D0%B8%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D1%83%D0%B5%D1%82%D1%81%D1%8F%20%D1%81%D0%BB%D0%B5%D0%B4%D1%83%D1%8E%D1%89%D0%B0%D1%8F%20%D1%84%D0%BE%D1%80%D0%BC%D1%83%D0%BB%D0%B0:,Vout%20*%20R1%20/%20(Vin%20%E2%80%93%20Vout)

#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);   //rs,e,d4,d5,d6,d7
int Vin=5;        //напряжение на контакте 5V платы arduino
float Vout=0;     //напряжение на контакте A0 платы arduino
float R1=3300;    //значение сопротивления известного резистора
float R2=0;         // значение сопротивления неизвестного резистора
int a2d_data=0;    
float buffer=0;            
void setup() 
{
 lcd.begin(16,2);
}
void loop()
{
  a2d_data=analogRead(A0);
  if(a2d_data)
  {
    buffer=a2d_data*Vin;
    Vout=(buffer)/1024.0;
    buffer=Vout/(Vin-Vout); 
    R2=R1*buffer;
    lcd.setCursor(4,0);
    lcd.print("ohm meter");
    lcd.setCursor(0,1);
    lcd.print("R (ohm) = ");
    lcd.print(R2);
    
    delay(1000);
  }
}