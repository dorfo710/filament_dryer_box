#include <Nextion.h> // Biblioteca lcd
#include <Interface.h> // Biblioteca dos macro da interface
#include <Leitura.h> // Biblioteca de leitura

// === Declaração de Objetos ===


Nexsettemp h0 = Nexsettemp(0, 5, "h0"); // Setup das funções do LCD
Nex30umid c0 = Nex30umid(0, 13, "c0");
Nex50umid c1 = Nex50umid(0, 14, "c1");
Nex70umid c2 = Nex70umid(0, 15, "c2");
Nextempautal t1 = Nextempautal(0, 3, "t1");
NexUmidatual t4 = NexUmidatual(0, 8, "t4");


