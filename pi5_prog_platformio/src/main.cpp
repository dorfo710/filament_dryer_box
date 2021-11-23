#include "SdFat.h"
#include <EEPROM.h>
#include <Wire.h>
#include "RTClib.h"

#include "time_rtc.h"
#include "controler.cpp"
#include "Leitura.h"

SdFat sdCard;
SdFile meuArquivo;
RTC_DS3231 rtc;


//#comentario laura
#include <DHT.h> //INCLUSÃO DE BIBLIOTECA

#define DHTPIN 15 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)

#define DHTPIN2 14 

DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
DHT dht2(DHTPIN2, DHTTYPE);

// Pino ligado ao CS do modulo
const int chipSelect = 5;
void setup()
{

}

void loop()
{
  if (analogRead(13) > 600)
  {
    while (1) {}
  }
  }
}