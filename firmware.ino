#include  <iarduino_RTC.h>      //библиотека часов
#include <DHT.h>                //библиотека для датчика DHT
#include <DHT_U.h>              //библиотека для датчика DHT
#include <Wire.h>               //библиотека для i2c
#include <LiquidCrystal_I2C.h>  //библиотека для дисплея 
#define DHTPIN1 3                   // пин датчика DTH11 d5
#define DHTPIN2 2                   // пин датчика DTH11 d2
LiquidCrystal_I2C lcd(0x27,16,2);   //инициализация дисплея
iarduino_RTC watch(RTC_DS3231);     //инициализация часов 
uint32_t timer1,timer2,timer3;      //таймеры для выполения функций
int realy1 = 5;              //пин реле d3
int realy2 = 4;              //пин реле d4

void setup()
{
//    Serial.begin(9600);             //инциализация монитора com-порта для отладки
    pinMode(realy1,OUTPIT);
    pinMode(realy2,OUTPIT);
     watch.begin();
    //watch.settime(__TIMESTAMP__);     //Установка времени в модуль, в таком описании равен времени компиляции кода, т.е +- вермя на ПК. После первой прошивки закоммпентировать!
    lcd.init();                     
    lcd.backlight();
}
void loop()
{
    if (millis() - timer1 >= 10000)
    {
       timer1 = millis();
       relay_time();
    }
    
    if (millis() - timer2 >= 5000)
    {
        timer2 = millis();
        relay_temp();
    }

    if (millis() - timer3 > 1000)
    {
        timer3 = millis();
        lcd_out();
    }
}
void relay_time(){                      //функция управления лампами
  watch.gettime();
  String time1 = watch.gettime("H:i:s");
  String start = "22:04:00"; //включение ламп
  String stop =  "22:08:00"; //выключение ламп
  Serial.println(time1);
  if (time1 == start){
    digitalWrite(relay1, LOW);
    
  }
  if (time1 == stop){
    digitalWrite(relay1, HIGH);
    
  }
}
void relay_temp(){                      //функция управления полдогревом
  float temp1 = dht1.readTemperature(DHTPIN1);      //данные с датчика 1
  float temp2 = dht2.readTemperature(DHTPIN2);      //данные с датчика 2
  float up_lemit  = 26.0;                           //верхний порог температуры
  float down_lemit = 22.0;                          //нижний порог температуры
 // Serial.println(temp1);                          //выхлоп в монитор порта для отладки
 // Serial.println(temp2);                          //выхлоп в монитор порта для отладки
 if (temp1 || temp2 >= up_lemit)
 {
    dititalWrite(realy2,HIGH);
 }
 if (temp1 || temp2 <= down_lemit)
 {
    digitalWrite(realy2,LOW);
 }
}
void lcd_out(){                         //функция вывода на экран
  float temp1 = dht1.readTemperature(DHTPIN1);      
  float temp2 = dht2.readTemperature(DHTPIN2);
  lcd.setCursor(0,0);                     // Устанавливаем курсор на первую строку и нулевой символ.
  lcd.print(watch.gettime("H:i:s"));
  lcd.setCursor(0, 1);
  lcd.print(temp1);
  lcd.setCursor(5, 1);
  lcd.print(temp2);
}
