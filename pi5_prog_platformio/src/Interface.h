#ifndef _Interface_H_
#define _Interface_H_

#include <Arduino.h>

class Interface
{

private:
public:
  int HORA, MINUTO, DIA, MES, ANO;
  int SETTEMP, TEMP, UMID;
  Interface();
  int NexRtcDefinirMinuto();
  int NexRtcDefinirHora();
  int NexRtcDefinirDia();
  int NexRtcDefinirMes();
  int NexRtcDefinirAno();
  void NexRtcPrint(String, String);
  int NexUmidatual();
  int Nextempautal();
  int Nexsettemp();
  int Nex30umid();
  int Nex50umid();
  int Nex70umid();
  // casa
};
#endif