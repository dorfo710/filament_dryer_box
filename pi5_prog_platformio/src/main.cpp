// Bibliotecas
#include <Wire.h>
#include <EEPROM.h>
#include "Nextion.h"
// Funções
#include "time_rtc.h"
#include <PID_v1.h>
#include "Leitura.h"
#include "Interface.h"
#include "controller.h"

uint32_t ds_var;
// Objetos
Interface I; // I objeto da classe Interface
Hora H;      // H objeto da classe Hora
Leitura L;   // L objeto da classe Leitura

// Nextion
// P0
NexSlider h0 = NexSlider(0, 3, "h0");
NexSlider h1 = NexSlider(0, 20, "h1");
NexDSButton bt0 = NexDSButton(0, 23, "bt0");
NexDSButton b01 = NexDSButton(0, 24, "bt1");

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
Controller CTRL;

// Globais Controle
double Kp_t = 1, Ki_t = 0.01, Kd_t = 1;
double Kp_h = 1, Ki_h = 0.01, Kd_h = 1;

bool controll_humitidy_enable = true;    // toggle to enable or disable the humidity control
bool controll_temperature_enable = true; // toggle to enable or disable the temperature control
// bool advanced_mode = false;

double Desired_temperature = 100.0; // change to set the target temperature
double pin_value_temperature = 0;
double real_temperature = 0; // placeholder for initialization of the sensor dht
PID myPID_temperature(&real_temperature, &pin_value_temperature, &Desired_temperature, Kp_t, Ki_t, Kd_t, DIRECT);

double Desired_humidity = 100.0; // change to set the target humidity
const byte hum_gpio = 3;         // gpio of the piezo pin

void b0PopCallback(void *ptr)
{
  H.Ajustar(I.NexRtcDefinirAno(), I.NexRtcDefinirMes(), I.NexRtcDefinirDia(),
            I.NexRtcDefinirHora(), I.NexRtcDefinirMinuto());
  I.NexPrint(H.Atual(), "Hora");
}

void h0PopCallback(void *ptr)
{
  h0.getValue(&valor);
  //I.NexPrint((String)valor, "Hora");
  EEPROM.writeInt(1, valor);
  EEPROM.commit();
}

void h1PopCallback(void *ptr)
{
  h1.getValue(&valor);
  //I.NexPrint((String)valor, "Hora");
  EEPROM.writeInt(1, valor);
  EEPROM.commit();
}

void bt0PopCallback(void *ptr)
{
  uint32_t dual_state;
  NexDSButton *btn = (NexDSButton *)ptr;
  bt0.getValue(&dual_state);
  //I.NexPrint(String(dual_state), "Hora");
  controll_humitidy_enable = dual_state;
}

void b01PopCallback(void *ptr)
{
  uint32_t dual_state;
  NexDSButton *btn = (NexDSButton *)ptr;
  b01.getValue(&dual_state);
  //I.NexPrint(String(dual_state), "Hora");
  controll_temperature_enable = dual_state;
}

NexTouch *nex_listen_list[] = {
    &b0,
    &bt0,
    &b01,
    &h0,
    &h1,
    NULL // String terminated
};

void setup()
{
  nexInit();
  Wire.begin(33, 32);
  EEPROM.begin(10);
  pinMode(14, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  b0.attachPop(b0PopCallback, &b0);
  bt0.attachPop(bt0PopCallback, &bt0);
  b01.attachPop(b01PopCallback, &b01);
  h0.attachPop(h0PopCallback);
  h1.attachPop(h1PopCallback);

  h0.setValue(EEPROM.readInt(1));

  Temp = L.getTemp();
  Umid = L.getUmid();
  I.NexPrint(String(Temp), "Temp");
  I.NexPrint(String(Umid), "Umid");
  I.NexPrint(String(H.Atual()), "Hora");
  // control begin setup
  // control pwm setup
  ledcAttachPin(1, 0); // gpio temperatura = 17
  ledcSetup(0, 5000, 8);
  myPID_temperature.SetMode(AUTOMATIC);

  pinMode(hum_gpio, OUTPUT);
}

void loop()
{
  real_temperature = L.getTemp();
  // Serial.print("temp = ");
  // Serial.println(real_temperature);

  Umidade = L.getUmid();
  // Serial.print("humi = ");
  // Serial.println(Umidade);

  if (controll_temperature_enable and !controll_humitidy_enable)
  {
    myPID_temperature.Compute();
    Serial.println(pin_value_temperature);
    ledcWrite(0, pin_value_temperature);
    digitalWrite(hum_gpio, LOW);
  }

  if (controll_humitidy_enable and !controll_temperature_enable)
  {
    if (Umidade < Desired_humidity)
    {
      digitalWrite(hum_gpio, HIGH);
      Desired_temperature = 0;
      myPID_temperature.Compute();
      Serial.println(pin_value_temperature);
      ledcWrite(0, pin_value_temperature);
    }
    else
    {
      digitalWrite(hum_gpio, LOW);
      Desired_temperature = 100;
      myPID_temperature.Compute();
      Serial.println(pin_value_temperature);
      ledcWrite(0, pin_value_temperature);
    }
  }

  if (controll_humitidy_enable and controll_temperature_enable)
  {
    myPID_temperature.Compute();
    Serial.println(pin_value_temperature);
    ledcWrite(0, pin_value_temperature);
    if (Umidade < Desired_humidity)
    {
      digitalWrite(hum_gpio, HIGH);
    }
    else
    {
      digitalWrite(hum_gpio, LOW);
    }
  }

  nexLoop(nex_listen_list);
  if (H.Timer() == true)
  {
    Temp = L.getTemp();
    Umid = L.getUmid();
    I.NexPrint(String(Temp), "Temp");
    I.NexPrint(String(Umid), "Umid");
    I.NexPrint(String(H.Atual()), "Hora");
    L.SdCard(H.Atual(), String(Umid), String(Temp));
  }
}
