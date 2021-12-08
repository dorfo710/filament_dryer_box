#include <Nextion.h>   // Biblioteca lcd
#include "Interface.h" // Biblioteca dos macro da interface
#include <iostream>

using namespace std;
char buffer[25];

// === Declaração de Objetos ===
//Page0
NexText TempP0 = NexText(0, 2, "t1");
NexText UmidP0 = NexText(0, 7, "t4");
NexText MostradorP0 = NexText(0, 18, "t10");
//Page1
NexText MostradorP1 = NexText(1, 4, "t10");

//Page2
NexText TempP2 = NexText(2, 4, "t2");
NexText UmidP2 = NexText(2, 5, "t3");
NexText MostradorP2 = NexText(2, 3, "t10");

//Page3
NexText v1 = NexText(0, 1, "t0");
NexText v2 = NexText(0, 6, "t6");
NexText v3 = NexText(0, 7, "t7");
NexText v4 = NexText(0, 8, "t8");
NexText v5 = NexText(0, 9, "t9");
NexText MostradorP3 = NexText(0, 27, "t10"); 

Interface::Interface()
{
}
int Interface::NexRtcDefinirDia()
{
  memset(buffer, 0, sizeof(buffer));
  v3.getText(buffer, sizeof(buffer));
  DIA = atoi(buffer);
  return DIA;
}

int Interface::NexRtcDefinirMes()
{

  memset(buffer, 0, sizeof(buffer));
  v4.getText(buffer, sizeof(buffer));
  MES = atoi(buffer);
  return MES;
}

int Interface::NexRtcDefinirAno()
{

  memset(buffer, 0, sizeof(buffer));
  v5.getText(buffer, sizeof(buffer));
  ANO = atoi(buffer);
  return ANO;
}

int Interface::NexRtcDefinirHora()
{
  memset(buffer, 0, sizeof(buffer));
  v1.getText(buffer, sizeof(buffer));
  HORA = atoi(buffer);

  return HORA;
}
int Interface::NexRtcDefinirMinuto()
{

  memset(buffer, 0, sizeof(buffer));
  v2.getText(buffer, sizeof(buffer));
  MINUTO = atoi(buffer);
  return MINUTO;
}

void Interface::NexPrint(String Valor, String Local)
{
  char conversao_S_C[30];
  Valor.toCharArray(conversao_S_C, 30);

  if (Local == "Aviso")
  {
    MostradorP0.setText(conversao_S_C);
    MostradorP1.setText(conversao_S_C);
    MostradorP2.setText(conversao_S_C);
    MostradorP3.setText(conversao_S_C);
  }
  if (Local == "Hora")
  {
    MostradorP0.setText(conversao_S_C);
    MostradorP1.setText(conversao_S_C);
    MostradorP2.setText(conversao_S_C);
    MostradorP3.setText(conversao_S_C);
  }
  if (Local == "Temp")
  {
    TempP0.setText(conversao_S_C);
    TempP2.setText(conversao_S_C);
  }
  if (Local == "Umid")
  {
    UmidP0.setText(conversao_S_C);
    UmidP2.setText(conversao_S_C);
  }





}



void Interface::Nexsettemp()
{
}
void Interface::Nextempautal()
{
}
void Interface::NexUmidatual()
{
}
void Interface::Nex30umid()
{
}
void Interface::Nex50umid()
{
}
void Interface::Nex70umid()
{
}