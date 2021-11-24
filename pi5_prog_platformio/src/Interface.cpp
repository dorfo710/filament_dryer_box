#include <Nextion.h>   // Biblioteca lcd
#include "Interface.h" // Biblioteca dos macro da interface
#include "Leitura.h"   // Biblioteca de leitura
#include "time_rtc.h"
#include <iostream>

using namespace std;
char buffer[25];
int hora, minuto, dia, mes, ano;

Hora Hora;

// === Declaração de Objetos ===
Nexsettemp h0 = Nexsettemp(0, 5, "h0"); // Setup das funções do LCD
Nex30umid c0 = Nex30umid(0, 13, "c0");
Nex50umid c1 = Nex50umid(0, 14, "c1");
Nex70umid c2 = Nex70umid(0, 15, "c2");
Nextempautal t1 = Nextempautal(0, 3, "t1");
NexUmidatual t4 = NexUmidatual(0, 8, "t4");

// RTC Ajuste @@@Definir pagina@@@
NexText v1 = NexText(0, 1, "t0");
NexText v2 = NexText(0, 6, "t6");
NexText v3 = NexText(0, 7, "t7");
NexText v4 = NexText(0, 8, "t8");
NexText v5 = NexText(0, 9, "t9");

//NexText v6   = NexText(0, 28, "t10"); // Ajustar

Interface::Interface()
{
}
void Interface::NexRtcDefinir()
{
    memset(buffer, 0, sizeof(buffer));
    v1.getText(buffer, sizeof(buffer));
    hora = atoi(buffer);

    memset(buffer, 0, sizeof(buffer));
    v2.getText(buffer, sizeof(buffer));
    minuto = atoi(buffer);

    memset(buffer, 0, sizeof(buffer));
    v3.getText(buffer, sizeof(buffer));
    dia = atoi(buffer);

    memset(buffer, 0, sizeof(buffer));
    v4.getText(buffer, sizeof(buffer));
    mes = atoi(buffer);

    memset(buffer, 0, sizeof(buffer));
    v5.getText(buffer, sizeof(buffer));
    ano = atoi(buffer);

    Hora.Definir(ano, mes, dia, hora, minuto);
}

void Interface::NexRtcPrint()
{
    String HoraEnvio = Hora.Atual();
    char conversao_S_C[20];
    HoraEnvio.toCharArray(conversao_S_C, 20);
   // v6.setText(conversao_S_C);
}
