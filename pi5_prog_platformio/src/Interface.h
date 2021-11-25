#ifndef _Interface_H_
#define _Interface_H_

#include <Arduino.h>

class Interface
{

private:
public:
  int HORA, MINUTO, DIA, MES, ANO;
  Interface();
  int NexRtcDefinirMinuto();
  int NexRtcDefinirHora();
  int NexRtcDefinirDia();
  int NexRtcDefinirMes();
  int NexRtcDefinirAno();
  void NexRtcPrint(String);
};
#endif