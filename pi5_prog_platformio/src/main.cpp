#include <SdFat.h>
#include <EEPROM.h>
#include <Wire.h>
#include "RTClib.h"

SdFat sdCard;
SdFile meuArquivo;
RTC_DS3231 rtc;


//#comentario laura
#include "DHT.h" //INCLUSÃO DE BIBLIOTECA

#define DHTPIN 15 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)

#define DHTPIN2 16
#define DHTTYPE DHT22

#define Resit 17
#define Piezo 25
#define Vent1 26
#define Vent2 27

DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
//-
// Pino ligado ao CS do modulo
const int chipSelect = 5;
String Dados;
int tempoDelay = 6000;
char tempo[7];
unsigned int atual = 0;
char VetorTempo[17];


int ano = 0;
int mes = 0;
int dia = 0, AuxDia = 0;
int hora = 0;
int minuto = 0;

void setup()
{
  Serial.begin(115200); //INICIALIZA A SERIAL
  EEPROM.begin(10);
  Wire.begin(33, 32);
  if (! rtc.begin()) {
    Serial.println("Não foi possível encontrar RTC");
    while (1);
  }
  dht.begin(); //INICIALIZA A FUNÇÃO
  delay(500);
  Serial.println("\n \n \n");
  Serial.println("(▀̿Ĺ̯▀̿) Instrunção ✍(◔◡◔)");
  Serial.println("Para gravar outros valores de ciclo,\ndigite na caixa serial 'T' e o tempo desejado em milisegundos.");
  Serial.println("Exemplo, T1000 para 1000 milisegundos, 1 segundo (>‿◠)✌");
  Serial.println("Tempo maximo pode ser ajustado até 2 horas e 46 minutos ♪┏(°.°)┛┗(°.°)┓┗(°.°)┛┏(°.°)┓ ♪");
  delay(10000);
  if (EEPROM.readInt(2) < 6000) {
    tempoDelay = EEPROM.readInt(2);
  }

  Serial.println((String)"Ciclo: " + tempoDelay);

  // Inicializa o modulo SD
  if (!sdCard.begin(chipSelect, SPI_HALF_SPEED))sdCard.initErrorHalt();
  // Abre o arquivo LER_POT.TXT
  if (!meuArquivo.open("dados.csv", O_RDWR | O_CREAT | O_AT_END))
  {
    sdCard.errorHalt("(┛◉Д◉)┛彡┻━┻ Erro na abertura do arquivo LER_POT.TXT! (×_×)");
  }
}

void loop()
{


  if (analogRead(13) > 600)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("(˘͜ʖ˘) Processo de gravacao interrompido. Retire o SD! ٩(^ᴗ^)۶");
    meuArquivo.close();
    while (1) {}
  }
  if (Serial.available() > 0) {
    /*
      if (Serial.read() == 'D') {
      delay(10);
      VetorTempo[0] = Serial.read();
      VetorTempo[1] = Serial.read();
      VetorTempo[2] = Serial.read();
      VetorTempo[3] = Serial.read();
      VetorTempo[4] = Serial.read();
      VetorTempo[5] = Serial.read();
      VetorTempo[6] = Serial.read();
      VetorTempo[7] = Serial.read();
      VetorTempo[8] = Serial.read();
      VetorTempo[9] = Serial.read();
      VetorTempo[10] = Serial.read();
      VetorTempo[11] = Serial.read();
      VetorTempo[12] = Serial.read();
      VetorTempo[13] = Serial.read();
      VetorTempo[14] = Serial.read();
      VetorTempo[15] = Serial.read();

      ano = mes = dia = hora = minuto = 0;
      hora = hora + (VetorTempo[0] - '0') * 10;
      hora = hora + (VetorTempo[1] - '0');

      minuto = minuto + (VetorTempo[3] - '0') * 10;
      minuto = minuto + (VetorTempo[4] - '0');

      dia = dia + (VetorTempo[6] - '0') * 10;
      dia = dia + (VetorTempo[7] - '0');

      mes = mes + (VetorTempo[9] - '0') * 10;
      mes = mes + (VetorTempo[10] - '0');

      ano = ano + (VetorTempo[12] - '0') * 1000;
      ano = ano + (VetorTempo[13] - '0') * 100;
      ano = ano + (VetorTempo[14] - '0') * 10;
      ano = ano + (VetorTempo[15] - '0');

      Serial.println((String)"Ano " + ano + " Mes " + mes + " Dia " + dia + " Hora " + hora + " Minuto " + minuto);
      rtc.adjust(DateTime(ano, mes, dia, hora, minuto, 0));
      Serial.println();
      }*/
    if (Serial.read() == 'T') {
      delay(10);
      tempo[0] = Serial.read();
      tempo[1] = Serial.read();
      tempo[2] = Serial.read();
      tempo[3] = Serial.read();
      tempo[4] = Serial.read();
      tempo[5] = Serial.read();
      tempo[6] = Serial.read();
      sscanf(tempo, "%d", &tempoDelay);
      EEPROM.writeInt(2, tempoDelay);
      EEPROM.commit();
      Serial.print((String)"Ciclo: " + tempoDelay + " milisegundos;" + "  Segundos: " + (float)tempoDelay / 1000.0 + ";  Minutos: " + (float)tempoDelay / (1000.0 * 60.0));
      if ((tempoDelay - 3600000) / (60000) >= 0) {
        Serial.println((String)"; Hora: " + tempoDelay / (1000 * 3600) + "." + (tempoDelay - 3600000) / (60000));
      } else Serial.println("");
      Serial.println();
    }

  }

  //leitura de umidade e temperatura
  if (millis() - atual > tempoDelay) {
    int umidade = (dht.readHumidity());
    int temperatura = (dht.readTemperature());

    Serial.print((String)"Umidade: " + umidade + "%"); //IMPRIME O TEXTO NA SERIAL
    Serial.println((String)" Temperatura: " + temperatura + "ºC"); //IMPRIME O TEXTO NA SERIAL
    DateTime now = rtc.now();
    Serial.print(now.day(), DEC);
    Serial.print("/");
    Serial.print(now.month(), DEC);
    Serial.print("/");
    Serial.print(now.year(), DEC);
    Serial.print("----");
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.println(now.second(), DEC);

    Dados = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + ";" + String(umidade) + ";" + String(temperatura) + ";" ;
    meuArquivo.println(Dados);


    atual = millis();
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
  }
}