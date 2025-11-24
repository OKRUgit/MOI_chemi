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
     timeMill=inerval;        // Сохранить время последнего обновления
                              // далее полный код из проверки конденсатора
     
     lcd.setCursor(15,0); 
     lcd.print("*");
     if(mk==0){               // подбор номинала
     pinMode(13,OUTPUT);
     pinMode(3,INPUT);
     digitalWrite(13,HIGH);
   }

    if(mk==1)
    {      // подбор номинала 
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
  c=c/1000-yvs0;
  c=abs(c);

  if(time1>=10000000){
    lcd.setCursor(1,0);
    lcd.print(" TEST uF   "); 
  }
  else{
    lcd.print(c); 

    if(mk==0){
      lcd.print(" NoF    ");
    }
    if(mk==1){
      lcd.print(" MkF       ");
    }
  }
  if(i==0){// калибровка нуля
    i++;
    yvs0=c+0,02;
  }
    // digitalWrite(ledPin, !digitalRead(ledPin));
   }

  // Здесь может быть другой код, который будет выполняться без остановки
}