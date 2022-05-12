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
NexSlider h1 = NexSlider(0, 19, "h1");
NexDSButton bt0 = NexDSButton(0, 23, "bt0");
NexDSButton bt1 = NexDSButton(0, 24, "bt1");

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

// Globais Controle  //derivativo setar 0
double Kp_t = 1.0, Ki_t = 0.0, Kd_t = 0.0;
// double Kp_h = 1.0, Ki_h = 0.0000001, Kd_h = 0.00000001;

int controll_humitidy_enable = 0;    // toggle to enable or disable the humidity control
int controll_temperature_enable = 0; // toggle to enable or disable the temperature control
// bool advanced_mode = false;

double Desired_temperature = 100.0; // change to set the target temperature
double pin_value_temperature = 0;
double real_temperature = 0; // placeholder for initialization of the sensor dht
double real_temperature_temporary;
double Umidade_temporary;
PID myPID_temperature(&real_temperature, &pin_value_temperature, &Desired_temperature, Kp_t, Ki_t, Kd_t, DIRECT);

double Desired_humidity = 100.0; // change to set the target humidity
const byte hum_gpio = 2;         // gpio of the piezo pin
bool um_state = false;

void b0PopCallback(void *ptr)
{
  H.Ajustar(I.NexRtcDefinirAno(), I.NexRtcDefinirMes(), I.NexRtcDefinirDia(),
            I.NexRtcDefinirHora(), I.NexRtcDefinirMinuto());
  I.NexPrint(H.Atual(), "Hora");
}

void h0PopCallback(void *ptr)
{
  h0.getValue(&valor);
  EEPROM.writeInt(10, valor);
  EEPROM.commit();
  Desired_temperature = valor;
}

void h1PopCallback(void *ptr)
{
  h1.getValue(&valor);
  EEPROM.writeInt(20, valor);
  EEPROM.commit();
  Desired_humidity = valor;
}
NexTouch *nex_listen_list[] = {
    &b0,
    &bt0,
    &bt1,
    &h0,
    &h1,
    NULL // String terminated
};

void setup()
{
  real_temperature = 30;
  Umidade = 30;
  nexInit();
  Wire.begin(33, 32);
  EEPROM.begin(50);
  pinMode(14, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  b0.attachPop(b0PopCallback, &b0);
  h0.attachPop(h0PopCallback);
  h1.attachPop(h1PopCallback);

  nexSerial.print("page0.Barra.val=");
  nexSerial.print(EEPROM.readInt(10));
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.print("page0.BarraUmid.val=");
  nexSerial.print(EEPROM.readInt(20));
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.print("page page0");
  nexSerial.write(0xff);
  nexSerial.write(0xff);
  nexSerial.write(0xff);

  h0.setValue(EEPROM.readInt(10));
  h1.setValue(EEPROM.readInt(20));
  Desired_temperature = EEPROM.readInt(10);
  Desired_humidity = EEPROM.readInt(20);

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
  pinMode(15, OUTPUT);
  // GPIO.func_out_sel_cfg[1].inv_sel = 1;
}

void loop()
{
  nexLoop(nex_listen_list);
  if (H.Timer() == true)
  {
    Temp = L.getTemp();
    Umid = L.getUmid();
    real_temperature = Temp;
    Umidade = Umid;
    I.NexPrint(String(Temp), "Temp");
    I.NexPrint(String(Umid), "Umid");
    I.NexPrint(String(H.Atual()), "Hora");
    L.SdCard(H.Atual(), String(Umid), String(Temp));
  }
  digitalWrite(15, HIGH); // liga a ventuinha
  myPID_temperature.Compute();
  Serial.println(pin_value_temperature);
  ledcWrite(0, pin_value_temperature);
  if (Umidade < Desired_humidity)
  {
    if (um_state == false)
    {
      delay(200);
      digitalWrite(hum_gpio, HIGH);
      delay(1000);
      digitalWrite(hum_gpio, LOW);
      um_state = true;
    }
  }
  else
  {
    if (um_state == true)
    {
      delay(200);
      digitalWrite(hum_gpio, HIGH);
      delay(400);
      digitalWrite(hum_gpio, LOW);
      delay(400);
      digitalWrite(hum_gpio, HIGH);
      delay(400);
      digitalWrite(hum_gpio, LOW);
      delay(200);
      um_state = false;
    }
  }
}
