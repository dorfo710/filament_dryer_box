//Bibliotecas
#include <Wire.h>
#include "Nextion.h"

//Funções
#include "time_rtc.h"
#include "Controller.h"
#include "Leitura.h"
//#include "Interface.h"

uint32_t ds_var;
//Interface Interface;
//Hora Hora;

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
bool auxiliar = false;

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
  if (Hora.Timer() == true && auxiliar == true)
  {
    leitura();
    auxiliar = false;
  }
  auxiliar = Hora.TimerVerifica();
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
// int Temp_PWM_FREQUENCY, int Temp_PWM_CHANNEL, int Temp_PWM_RESOLUTION, int humidity_PWM_FREQUENCY, int humidity_PWM_CHANNEL, int humidity_PWM_RESOLUTION
Controller(5000, 0, 8, 5000, 8, 0);
//Controller.Set_hum_pwm_config();    // int GPIO_pin, int Frequency, int Channel, int Resolution
//Controller.Set_temp_pwm_config();   // int GPIO_pin, int Frequency, int Channel, int Resolution

int main
{
  leitura();

  Controller.Set_desired_temperature(17, 5000, 0, 8); // this function recives the Temperature value from the interface and stores inside the class controller
  Controller.Set_desired_humidity(25, 5000, 0, 8);    // this function recives the Humidity value from the interface and stores inside the class controller
  //Controller.Control_humidity(Umidade); // this function controlls the pwm signal based on the read Humidity
  //Controller.Control_temp(Temperatura); // this function controlls the pwm signal based on the read Temperature
  controller.PID_CONTROLL(Temperatura, Umidade);


}