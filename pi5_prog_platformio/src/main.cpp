//Bibliotecas
#include <Wire.h>
#include "Nextion.h"

//Funções
#include "time_rtc.h"
//#include "controler.cpp"
#include "Leitura.h"
#include "Interface.h"

uint32_t ds_var;
Interface Interface;
Hora Hora;

//Nextion
NexButton b0 = NexButton(0, 26, "b14");
NexButton b1 = NexButton(0, 28, "b15");

int HORA, MINUTO, DIA, MES, ANO;
void setup()
{
  nexInit();
  Wire.begin(33, 32);
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
}

NexTouch *nex_listen_list[] =
{
  &b0,
  &b1,
  NULL  // String terminated
};


void loop()
{
  nexLoop(nex_listen_list);

}

void b0PopCallback(void *ptr)
{
  Hora.Ajustar(Interface.NexRtcDefinirAno(), Interface.NexRtcDefinirMes(), Interface.NexRtcDefinirDia(),
               Interface.NexRtcDefinirHora(), Interface.NexRtcDefinirMinuto());
  Interface.NexRtcPrint(Hora.Atual());
}

void b1PopCallback(void *ptr)
{
  Interface.NexRtcPrint(Hora.Atual());
}