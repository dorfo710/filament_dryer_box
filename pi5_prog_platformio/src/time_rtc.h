#ifndef _time_rtc_H_
#define _time_rtc_H_

#include <Arduino.h>

class Hora
{

private:
public:
  Hora();
  String Atual();
  void Ajustar(int, int, int, int, int);
};
#endif