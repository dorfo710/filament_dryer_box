#include <Arduino.h>
#include <SdFat.h>
 
SdFat sdCard;
SdFile meuArquivo;


#include "DHT.h" //INCLUSÃO DE BIBLIOTECA
 
#define DHTPIN 15 //PINO DIGITAL UTILIZADO PELO DHT22
#define DHTTYPE DHT22 //DEFINE O MODELO DO SENSOR (DHT22 / AM2302)
 
DHT dht(DHTPIN, DHTTYPE); //PASSA OS PARÂMETROS PARA A FUNÇÃO
 
// Pino ligado ao CS do modulo
const int chipSelect = 5;
String Dados;
int tempoDelay = 2000;
char tempo[7];
unsigned int atual=0;
 
void setup()
{
  Serial.begin(115200); //INICIALIZA A SERIAL
  dht.begin(); //INICIALIZA A FUNÇÃO
  delay(500);
  Serial.println("\n \n \n");
  Serial.println("(▀̿Ĺ̯▀̿) Instrunção ✍(◔◡◔)");
  Serial.println("Para gravar outros valores de ciclo,\ndigite na caixa serial 'T' e o tempo desejado em milisegundos.");
  Serial.println("Exemplo, T1000 para 1000 milisegundos, 1 segundo (>‿◠)✌");
  Serial.println("Tempo maximo pode ser ajustado até 2 horas e 46 minutos ♪┏(°.°)┛┗(°.°)┓┗(°.°)┛┏(°.°)┓ ♪");
  delay(10000);
  Serial.println((String)"Ciclo: "+tempoDelay);

  // Inicializa o modulo SD
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
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

  if(Serial.read() == 'T'){
    delay(10);
    tempo[0] = Serial.read();
    tempo[1] = Serial.read();
    tempo[2] = Serial.read();
    tempo[3] = Serial.read(); 
    tempo[4] = Serial.read();
    tempo[5] = Serial.read();
    tempo[6] = Serial.read(); 
    sscanf(tempo, "%d", &tempoDelay);
    Serial.print((String)"Ciclo: "+tempoDelay +" milisegundos;" + "  Segundos: "+ (float)tempoDelay/1000.0 + ";  Minutos: "+ (float)tempoDelay/(1000.0*60.0));
    if((tempoDelay-3600000)/(60000) > 0){
        Serial.println((String)"; Hora: "+ tempoDelay/(1000*3600)+"."+(tempoDelay-3600000)/(60000));
      }else Serial.println("");
    
    }
  
  //leitura de umidade e temperatura
  if(millis()-atual>tempoDelay){
    int umidade = (dht.readHumidity());
    int temperatura = (dht.readTemperature());

    Serial.print((String)"Umidade: " + umidade + "%"); //IMPRIME O TEXTO NA SERIAL
    Serial.println((String)" Temperatura: "+ temperatura +"ºC"); //IMPRIME O TEXTO NA SERIAL
  
    Dados = String(millis()) +";"+ String(umidade) + ";" + String(temperatura)+ ";" ;
    meuArquivo.println(Dados);
    atual = millis();
    }
    
}