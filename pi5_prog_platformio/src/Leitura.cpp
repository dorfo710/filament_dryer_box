//Só exemplos para começar :)

#include <iostream>
#include "Leitura.h"
using namespace std;

#define Resistencia_Port 17
#define Piezo_Port 25
#define Vent1_port 26
#define Vent2_port 27

//Construtor padrão não recebe nenhum parâmetro
//Este construtor sempre está presente mesmo que não tenha sido Declarado
Leitura::Leitura()
{
    Temp = 0;
    Umid = 0;
    Resist = 0;
    Piezo = 0;
    Vent = 0;
    cout << "Construindo(1) um objeto da classe Leitura!" << endl;
}
//Construtor Sobrecarregado - Recebe o raio do circulo
Leitura::Leitura(double T, int R)
{
    Temp = T;
    Umid = 0;
    Resist = R;
    Piezo = 0;
    Vent = 0;
    cout << "Construindo(2) um objeto da classe Circle!" << endl;
}
//Construtor Sobrecarregado - Recebe o raio do circulo, assim como as
//coordenadas X e Y do Centro Respectivamente
Leitura::Leitura(double T, double U, int R, int P, int V)
{
    Temp = T;
    Umid = U;
    Resist = R;
    Piezo = P;
    Vent = V;
    cout << "Construindo(3) um objeto da classe Circle!" << endl;
}
//Destrutor
Leitura::~Leitura()
{
    Temp = 0;
    Umid = 0;
    Resist = 0;
    Piezo = 0;
    Vent = 0;
    //Imprime o texto indicado que o objeto está sendo destruido
    cout << "Destruindo o objeto da classe Ci l rc e!" << endl;
}
#pragma region Definição dos Estados
/*
//Métodos Modificadores
void Leitura::setTemp(double T){ //Ajusta o raio do círculo
    Temp = T;
}
void Leitura::setUmid(double U){//Ajusta a coordenada X do Centro
    Umid = U;
}
void Leitura::setResist(int R){ ////Ajusta a coordenada Y do Centro
    Resist = R;
}
void Leitura::setPiezo(int P){
    Piezo = P;
}
void Leitura::setVent(int V){
    Vent = V;
}
*/
#pragma endregion

//Métodos Acessores
double Leitura::getTemp()
{ //Recupera temperatura media
    int temperatura1 = dht1.readTemperature();
    int temperatura2 = dht2.readTemperature();
    Temp = (temperatura1 + temperatura2) / 2;
    return Temp;
}
double Leitura::getUmid()
{ //Recupera umidade media
    int umidade1 = dht1.readHumidity();
    int umidade2 = dht2.readHumidity();
    Umid = (umidade1 + umidade2) / 2;
    return Umid;
}
int Leitura::getResist()
{ //Recupera o estado da Resistência
    Resist = digitalRead(Resistencia_Port);
    return Resist;
}
int Leitura::getPiezo()
{ //Recupera o valor do Piezo
    Piezo = digitalRead(Piezo_Port);
    return Piezo;
}
int Leitura::getVent1()
{ //Recupera o valor da ventoinha 1
    Vent = digitalRead(Vent1_port);
    return Vent;
}
int Leitura::getVent2()
{ //Recupera o valor da ventoinha 2
    Vent = digitalRead(Vent2_port);
    return Vent;
}
void Leitura::SdCard()
{
    if (!sdCard.begin(chipSelect, SPI_HALF_SPEED))
        sdCard.initErrorHalt();
    // Abre o arquivo LER_POT.TXT
    if (!meuArquivo.open("dados.csv", O_RDWR | O_CREAT | O_AT_END))
    {
        sdCard.errorHalt("(┛◉Д◉)┛彡┻━┻ Erro na abertura do arquivo LER_POT.TXT! (×_×)");
    }

    // Grava Cartão
    DateTime now = rtc.now();
    Dados = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + ";" + String(Umid) + ";" + String(Temp) + ";";
    meuArquivo.println(Dados);

    //Encerra Cartão
    Serial.println("(˘͜ʖ˘) Processo de gravacao interrompido. Retire o SD! ٩(^ᴗ^)۶");
    meuArquivo.close();
}

// falta fazer parte do main.cpp