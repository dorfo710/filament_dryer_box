//Bibliotecas
#include <Wire.h>
#include "Nextion.h"

//Funções
#include "time_rtc.h"
#include "Controller.h"
#include "Leitura.h"
#include "Interface.h"

uint32_t ds_var;
Interface Interface;
Hora Hora;

//Nextion
NexButton b0 = NexButton(0, 26, "b14");
NexButton b1 = NexButton(0, 28, "b15");

// Globais
double Temperatura;
double Umidade;
int Resistor;
int Piezo;
int Vento;
int Vento2;

void setup()
{
  nexInit();
  Wire.begin(33, 32);
  pinMode(14, INPUT_PULLUP);
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
}

NexTouch *nex_listen_list[] = {
    &b0,
    &b1,
    NULL // String terminated
};

void loop()
{
  nexLoop(nex_listen_list);
  if (Hora.Timer() == true)
  {
    leitura();
  }
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
  //Interface.NexRtcPrint(String(Leitura.getUmid())+" "+ String(Leitura.getTemp()));
}

void leitura()
{
  Leitura T, U, R, P, V, V2, LSD;
  Temperatura = T.getTemp();
  Umidade = U.getUmid();
  Resistor = R.getResist();
  Piezo = P.getPiezo();
  Vento = V.getVent1();
  Vento2 = V2.getVent2();
  LSD.SdCard();
}

// setup -> inicializa tudo
// loop {
// leitura()
// while !=rtc(5) <
//   Interface() <
//   controller() <
// }

int main
{
  leitura()
}