#include "domeniu.h"
#include "teste.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


int main() {
	testAll();
	/*
	OfertaRepo rep;
	OfertaValidator valid;
	OfertaService serv{ rep, valid };
	UI ui{ serv };
	ui.start();
	*/
	if (_CrtDumpMemoryLeaks())
		printf("\nMEMORY LEAKS\n");
	return 0;
}