// Bibliotecas
#include <Wire.h>
#include <EEPROM.h>
#include <PID_v1.h>
#include "Nextion.h"
// Funções
#include "time_rtc.h"
#include "Controller.h"
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
uint32_t valor = 0;
Controller CTRL;

// Globais Controle
double Kp_t = 1, Ki_t = 0.01, Kd_t = 1;
double Kp_h = 1, Ki_h = 0.01, Kd_h = 1;

double Desired_temperature = 100.0; // este é o valor pra mudar de acordo com a humidade desejada
double pin_value_temperature = 0;
double real_temperature = 0;
PID myPID_temperature(&real_temperature, &pin_value_temperature, &Desired_temperature, Kp_t, Ki_t, Kd_t, DIRECT);

double Desired_humidity = 100.0;
const byte hum_gpio = 16;

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

void setup()
{
  nexInit();
  /*
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
  */

  // control begin setup
  // control pwm setup
  ledcAttachPin(17, 0); // gpio umidade = 17
  ledcSetup(0, 5000, 8);
  myPID_temperature.SetMode(AUTOMATIC);

  pinMode(hum_gpio, OUTPUT);

  // control end setup
  Serial.begin(9600);
}

void loop()
{
  real_temperature = L.getTemp();
  Serial.print("temp = ");
  Serial.println(real_temperature);

  Umidade = L.getUmid();
  Serial.print("humi = ");
  Serial.println(Umidade);

  if (Umidade < Desired_humidity)
  {
    digitalWrite(hum_gpio, HIGH);
  }
  else
  {
    digitalWrite(hum_gpio, LOW);
  }

  delay(100);

  // int pwm_duty = CTRL.func_PID_TEST(Temperatura, Umidade);
  myPID_temperature.Compute();
  Serial.println(pin_value_temperature);
  ledcWrite(0, pin_value_temperature);
  /*
    nexLoop(nex_listen_list);
    if (H.Timer() == true)
    {

      I.NexPrint(String(Temperatura), "Temp");
      I.NexPrint(String(Umidade), "Umid");
      I.NexPrint(String(H.Atual()), "Hora");
      L.SdCard(H.Atual(), String(Umidade), String(Temperatura));
    }
  */
}