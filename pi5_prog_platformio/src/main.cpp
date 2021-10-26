#include <Arduino.h>
#include <SdFat.h>
 
SdFat sdCard;
SdFile meuArquivo;

#include <DHT.h>; //INCLUSÃO DE BIBLIOTECA
 
#define DHTPIN 7 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
 
DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
 
// Pino ligado ao CS do modulo
const int chipSelect = 4;
 
void setup()
{
  Serial.begin(9600); //INICIALIZA A SERIAL
  dht.begin(); //INICIALIZA A FUNÇÃO
  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
  
  // Inicializa o modulo SD
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
  // Abre o arquivo LER_POT.TXT
  if (!meuArquivo.open("ler_pot.txt", O_RDWR | O_CREAT | O_AT_END))
  {
    sdCard.errorHalt("Erro na abertura do arquivo LER_POT.TXT!");
  }
}
 
void loop()
{
  //leitura de umidade e temperatura
  int umidade = (dht.readHumidity());
  int temperatura = (dht.readTemperature(), 0);
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(umidade); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //IMPRIME O TEXTO NA SERIAL 
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(temperatura); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDOS * NÃO DIMINUIR ESSE VALOR
  
 
  // Grava dados do sensor em LER_POT.TXT
  meuArquivo.print("Umidade: "); 
  meuArquivo.print(umidade);
  meuArquivo.print(" / Temperatura: ");
  meuArquivo.print(temperatura); 
 /* if (valor <= 5)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("Processo de gravacao interrompido. Retire o SD!");
    meuArquivo.close();
    while (1) {}
  }
  delay(2000);*/
}