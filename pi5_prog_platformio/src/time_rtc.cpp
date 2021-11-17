#include <iostream>
#include "time_rtc.h"
using namespace std;

int DiaSemana, Porta, TempoAcao, H0, H1 , H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12, H13, H14, H15, H16, H17, H18, H19, H20, H21, H22, H23, tempo;
bool Auxiliar = false, auxiliar2 = false, Aux2 =  true;

Hora::Hora(){	
  
}

void Hora::Definir(int hora, int minuto, int dia, int mes, int ano) {    
    rtc.adjust(DateTime(ano, mes, dia, hora, minuto, 0));

}
char Hora::Atual(){
    DateTime now = rtc.now();
    String Dados = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":"
    + String(now.minute()) + ":" + String(now.second());
    return Dados;
}