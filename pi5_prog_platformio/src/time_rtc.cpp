#include <iostream>
#include "time_rtc.h"

#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

using namespace std;

Hora::Hora()
{
}

void Hora::Ajustar(int ano, int mes, int dia, int hora, int minuto)
{
    rtc.adjust(DateTime(ano, mes, dia, hora, minuto, 0));
}
String Hora::Atual()
{
    DateTime now = rtc.now();
    String Dados = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute());
    return Dados;
}

bool Hora::Timer()
{
    DateTime now = rtc.now();
    if (now.second() == 0 || now.second() == 20 || now.second() == 40)
    {
        return true;
    }
    return false;
}
bool Hora::TimerVerifica(){
    DateTime now = rtc.now();
    if (now.second() == 1 || now.second() == 21 || now.second() == 41)
    {
        return true;
    }
    return false;
}
//vcc = 3.3v
//gnd = gnd
//sda = d33
//scl = d32