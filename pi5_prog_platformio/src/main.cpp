//Bibliotecas
#include "SdFat.h"
#include <EEPROM.h>
#include <Wire.h>
#include "RTClib.h"
#include <DHT.h>

//Funções
#include "time_rtc.h"
#include "controler.cpp"
#include "Leitura.h"

SdFat sdCard;
SdFile meuArquivo;
RTC_DS3231 rtc;



#define DHTPIN 15 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)

#define DHTPIN2 14 

DHT dht1(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
DHT dht2(DHTPIN2, DHTTYPE);

// Pino ligado ao CS do modulo
const int chipSelect = 5;
void setup()
{
  Serial.begin(115200); //INICIALIZA A SERIAL
  EEPROM.begin(10);
  Wire.begin(33, 32);
  if (! rtc.begin()) {
    Serial.println("Não foi possível encontrar RTC");
    while (1);
  }
  dht1.begin();
  dht2.begin();
}

void loop()
{
  
}