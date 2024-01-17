#include <Wire.h>               //библиотека для i2c
#include <LiquidCrystal_I2C.h>  //библиотека для дисплея

LiquidCrystal_I2C lcd(0x27,16,2);   //инициализация дисплея

uint32_t timer1,timer2,timer3;      //таймеры для выполения функций

int realy1 = 3;              //пин реле 3
int realy2 = 4;              //пин реле 4


void setup()
{
//    Serial.begin(9600);             //инциализация монитора com-порта для отладки
    pinMode(realy1,OUTPIT);
    pinMode(realy2,OUTPIT);
}
void loop()
{

}

void relay_time(){                      //функция управления лампами

}

void relay_temp(){                      //функция управления полдогревом

}

void lcd_out(){                         //функция вывода на экран

}
