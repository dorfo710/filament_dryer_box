#include <iostream>
#include "time_rtc.h"
using namespace std;

Hora::Hora()
{
}

void Hora::Definir(int ano, int mes, int dia, int hora, int minuto)
{
    rtc.adjust(DateTime(ano, mes, dia, hora, minuto, 0));
}
String Hora::Atual()
{
    DateTime now = rtc.now();
    String Dados = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
    return Dados;
}