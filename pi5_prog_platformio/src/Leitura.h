//Só exemplos para começar :)

#ifndef _Leitura_H_
#define _Leitura_H_

#include <Arduino.h>

class Leitura
{
private: // As variáveis membro são privadas (encapsulamento)
    double Temp, Umid;
    int Resist, Piezo, Vent, Vent2;
    String Dados;

public:        // Os métodos sao públicos
    Leitura(); //Construtores (sobrecarregado)
    //Leitura(double, int);
    //Leitura(double, double, int, int, int, int);
    ~Leitura();           // Método Destrutor
    double getTemp(); //Métodos Acessores getXXX
    double getUmid();
    int getResist();
    int getPiezo();
    int getVent1();
    int getVent2();
    void SdCard(String, String, String);
};
#endif