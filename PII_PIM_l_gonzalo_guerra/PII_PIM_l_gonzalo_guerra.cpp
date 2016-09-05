/*


	PII_PIM_l_gonzalo_guerra.cpp: archivo de proyecto principal.

*/ 

#include "stdafx.h"
#include "stdlib.h"

int cant_dados = 5;

using namespace System;

int tirarDado() {
	int valor;
	valor = rand() % 6 + 1;
	return valor;
}

int revisarJugada(int* dados) {
	int uno, dos, tres, cuatro, cinco, seis = 0;
	int jugada = 0;
	for (int i = 0; i <= sizeof(dados); i++) {
		switch (dados[i]) {
		case 1:
			uno++;
			break;
		case 2:
			dos++;
			break;
		case 3:
			tres++;
			break;
		case 4:
			cuatro++;
			break;
		case 5:
			cinco++;
			break;
		case 6:
			seis++;
			break;
		default:
			break;
		}
	}

		// Contamos los UNOS

		switch (uno) {
		case 5:
			jugada += 10000;
			break;
		case 4:
			jugada += 1100;
			break;
		case 3:
			jugada += 1000;
			break;
		case 2:
			jugada += 200;
			break;
		case 1:
			jugada += 100;
			break;
		}

		
		// Contamos los CINCOS

		if (cinco >= 3) {
			jugada += 500 + (cinco - 3 * 50);
		}
		else {
			jugada += cinco * 50;
		}


		// Contamos el RESTO


		if (dos == 3) {
			jugada += 200;
		}

		if (tres == 3) {
			jugada += 300;
		}

		if (cuatro == 3) {
			jugada += 400;
		}

		if (seis == 3) {
			jugada += 600;
		}

		// Si es escalera vale 500 

		if (uno == 1 && dos == 1 && tres == 1 && cuatro == 1 && cinco == 1) {
			jugada += 500;
		}
		else if (seis == 1 && dos == 1 && tres == 1 && cuatro == 1 && cinco == 1) {
			jugada += 500;
		}

		return jugada;
	
}

void main()
{
	String^ salida;
	String^ seleccion;
	int* dados;
	dados = new int[5];
	
	do
	{

		for (int i = 0; i < cant_dados; i++) {
			int aux = tirarDado();
			int dado = i+1;
			Console::WriteLine(L"Dado " + dado +" -> "+aux);
			dados[i] = aux;
		}
				
		Console::WriteLine("-----------------");
		
		Console::WriteLine(L"Puntos -> " + revisarJugada(dados));
		Console::WriteLine(L"Por favor seleccione los dados que va a usar");
		Console::WriteLine(L"coloque los números separados por comas");
		Console::WriteLine(L"t para todos");
		Console::WriteLine(L"x para salir :");
		seleccion = Console::ReadLine();
				
		if (String::Compare(seleccion,"x")==0) {
			break;
		} else if (String::Compare(seleccion, "t") == 0) {
			
		} 
		
		int dado = dado.Parse(seleccion);

		if (dado >0 && dado<6){ 
			for (int i = 0; i < cant_dados; i++) {
				if (i == (dado-1)) {
					dados[i] = 0;
				}
			}
		}
		Console::WriteLine("-----------------");

		Console::WriteLine(L"Puntos -> " + revisarJugada(dados));
		seleccion = Console::ReadLine();

	} while (true);
}
