// Bibliotecas
#include <Wire.h>
#include <EEPROM.h>
#include "Nextion.h"
// Funções
#include "time_rtc.h"
//#include "Controller.h"
#include "Leitura.h"
#include "Interface.h"

uint32_t ds_var;
// Objetos
Interface I; // I objeto da classe Interface
Hora H;      // H objeto da classe Hora
Leitura L;   // L objeto da classe Leitura

// Nextion
// P0
NexSlider h0 = NexSlider(0, 4, "h0");
NexCheckbox c0 = NexCheckbox(0, 12, "c0");
NexCheckbox c1 = NexCheckbox(0, 13, "c1");
NexCheckbox c2 = NexCheckbox(0, 14, "c2");

// P3
NexButton b0 = NexButton(3, 26, "b14");

// Globais
double Temperatura;
double Umidade;
int Resistor;
int Piezo;
int Vento;
int Vento2;
bool auxiliar = true;
uint32_t valor = 0;
int Temp, Umid;
//Controller CTRL;

void b0PopCallback(void *ptr)
{
  H.Ajustar(I.NexRtcDefinirAno(), I.NexRtcDefinirMes(), I.NexRtcDefinirDia(),
            I.NexRtcDefinirHora(), I.NexRtcDefinirMinuto());
  I.NexPrint(H.Atual(), "Hora");
}

void h0PopCallback(void *ptr)
{
  h0.getValue(&valor);
  EEPROM.writeInt(1, valor);
  EEPROM.commit();
}
void c0PopCallback(void *ptr)
{
  c0.getValue(&valor);
  EEPROM.writeInt(2, valor);
  EEPROM.commit();
}
void c1PopCallback(void *ptr)
{
  c1.getValue(&valor);
  EEPROM.writeInt(3, valor);
  EEPROM.commit();
}
void c2PopCallback(void *ptr)
{
  c2.getValue(&valor);
  EEPROM.writeInt(4, valor);
  EEPROM.commit();
}
NexTouch *nex_listen_list[] = {
  &b0,
  &h0,
  &c0,
  &c1,
  &c2,
  NULL // String terminated
};

void leitura()
{
  Leitura T, U, R, P, V, V2, LSD;
  Temperatura = T.getTemp();
  Umidade = U.getUmid();
  Resistor = R.getResist();
  Piezo = P.getPiezo();
  Vento = V.getVent1();
  Vento2 = V2.getVent2();
}

void Controle_init()
{
  //  CTRL.Set_hum_pwm_config(25, 5000, 0, 8);
  // CTRL.Set_temp_pwm_config(17, 5000, 0, 8);
}

void setup()
{
  nexInit();
  Wire.begin(33, 32);
  EEPROM.begin(10);
  pinMode(14, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  b0.attachPop(b0PopCallback, &b0);
  h0.attachPop(h0PopCallback);
  c0.attachPop(c0PopCallback);
  c1.attachPop(c1PopCallback);
  c2.attachPop(c2PopCallback);

  h0.setValue(EEPROM.readInt(1));
  c0.setValue(EEPROM.readInt(2));
  c1.setValue(EEPROM.readInt(3));
  c2.setValue(EEPROM.readInt(4));

  Controle_init();
}

void loop()
{
  nexLoop(nex_listen_list);

  //if (H.Timer() == true) {
  
  Temp = L.getTemp();
  Umid = L.getUmid();
  I.NexPrint(String(Temp), "Temp");
  I.NexPrint(String(Umid), "Umid");
  I.NexPrint(String(H.Atual()), "Hora");
  L.SdCard(H.Atual(), String(Umid), String(Temp));
  I.NexPrint("10:11 08/12/2021", "Hora");
  // }

  delay(10000);

}
