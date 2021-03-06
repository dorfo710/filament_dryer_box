// Só exemplos para começar :)

#include <iostream>
#include "Leitura.h"
#include "time_rtc.h"

#include <SdFat.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Nextion.h>

using namespace std;

#define Resistencia_Port 17
#define Piezo_Port 25
#define Vent1_port 26
#define Vent2_port 27

#define DHTPIN 12 // PINO DIGITAL UTILIZADO PELO DHT22
#define DHTPIN2 13
#define DHTTYPE DHT22 // DEFINE O MODELO DO SENSOR (DHT22 / AM2302)

DHT dht1(DHTPIN, DHTTYPE); // PASSA OS PARÂMETROS PARA A FUNÇÃO
DHT dht2(DHTPIN2, DHTTYPE);

SdFat sdCard;
SdFile meuArquivo;
const int chipSelect = 5;

// Construtor padrão não recebe nenhum parâmetro
// Este construtor sempre está presente mesmo que não tenha sido Declarado
Leitura::Leitura()
{
  Temp = 0;
  Umid = 0;
  Resist = 0;
  Piezo = 0;
  Vent = 0;
  Vent2 = 0;
  Dados;
  cout << "Construindo(1) um objeto da classe Leitura!" << endl;
}

// Destrutor
Leitura::~Leitura()
{
  Temp = 0;
  Umid = 0;
  Resist = 0;
  Piezo = 0;
  Vent = 0;
  // Imprime o texto indicado que o objeto está sendo destruido
  cout << "Destruindo o objeto da classe Ci l rc e!" << endl;
}

// Métodos Acessores
double Leitura::getTemp()
{ // Recupera temperatura media
  int temperatura1 = dht1.readTemperature();
  int temperatura2 = dht2.readTemperature();
  Temp = (temperatura1 + temperatura2) / 2;
  return temperatura2;
}
double Leitura::getUmid()
{ // Recupera umidade media
  int umidade1 = dht1.readHumidity();
  int umidade2 = dht2.readHumidity();
  Umid = (umidade1 + umidade2) / 2;
  return umidade2;
}
int Leitura::getResist()
{ // Recupera o estado da Resistência
  Resist = digitalRead(Resistencia_Port);
  return Resist;
}
int Leitura::getPiezo()
{ // Recupera o valor do Piezo
  Piezo = digitalRead(Piezo_Port);
  return Piezo;
}
int Leitura::getVent1()
{ // Recupera o valor da ventoinha 1
  Vent = digitalRead(Vent1_port);
  return Vent;
}
int Leitura::getVent2()
{ // Recupera o valor da ventoinha 2
  Vent2 = digitalRead(Vent2_port);
  return Vent2;
}
void Leitura::SdCard(String Hora, String UmiD, String TemP)
{
  sdCard.begin(chipSelect, SPI_HALF_SPEED);
  // Abre o arquivo LER_POT.TXT
  if (!meuArquivo.open("dados.csv", O_RDWR | O_CREAT | O_AT_END))
  {
    meuArquivo.close();
    // break;
  }

  // Grava Cartão
  Dados = String(Hora + ";" + UmiD + ";" + TemP + ";");
  meuArquivo.println(Dados);

  // Encerra Cartão
  meuArquivo.close();
}