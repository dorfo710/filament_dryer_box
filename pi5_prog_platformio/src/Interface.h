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
  void NexPrint(String, String);
  
  void NexUmidatual();
  void Nextempautal();
  void Nexsettemp();
  void Nex30umid();
  void Nex50umid();
  void Nex70umid();
  // casa
};
#endif