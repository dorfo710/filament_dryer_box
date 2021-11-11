//Só exemplos para começar :)

#include <iostream>
#include "Leitura.h"
using namespace std;
//Construtor padrão não recebe nenhum parâmetro
//Este construtor sempre está presente mesmo que não tenha sido Declarado
Leitura::Leitura(){
    Temp = 0; Umid = 0; Resist = 0; Piezo = 0; Vent = 0;
    cout << "Construindo(1) um objeto da classe Leitura!" << endl;
}
//Construtor Sobrecarregado - Recebe o raio do circulo
Leitura::Leitura(double T, int R){
    Temp = T; Umid = 0; Resist = R; Piezo = 0; Vent = 0;
    cout << "Construindo(2) um objeto da classe Circle!" << endl;
}
//Construtor Sobrecarregado - Recebe o raio do circulo, assim como as
//coordenadas X e Y do Centro Respectivamente
Leitura::Leitura(double T, double U, int R, int P, int V){
    Temp = T; Umid = U; Resist = R; Piezo = P; Vent = V;
    cout << "Construindo(3) um objeto da classe Circle!" << endl;
}
//Destrutor
Leitura::~Leitura(){
    Temp = 0; Umid = 0; Resist = 0; Piezo = 0; Vent = 0;
    //Imprime o texto indicado que o objeto está sendo destruido
    cout << "Destruindo o objeto da classe Ci l rc e!" << endl;
}
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
//Métodos Acessores
double Leitura::getTemp(){//Recupera o raio o Círculo
    return Temp;
}
double Leitura::getUmid(){//Recupera o raio o Círculo
    return Umid;
}
int Leitura::getResist(){//Recupera o raio o Círculo
    return Resist;
}
int Leitura::getPiezo(){//Recupera o raio o Círculo
    return Piezo;
}
int Leitura::getVent(){//Recupera o raio o Círculo
    return Vent;
}
// falta fazer parte do main.cpp