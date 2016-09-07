/*
	PII_PIM_l_gonzalo_guerra.cpp: archivo de proyecto principal.
*/ 

#include "stdafx.h"
#include "stdlib.h"
#include "vector"
#include "PII_PIM_l_gonzalo_guerra.h"

using namespace System;
using namespace std;

class Jugador
{

private:
	int puntos;
	bool jugando;
	int num_jug;
public:

	Jugador() {};

	Jugador(int nj) {
		num_jug = nj;
		puntos = 0;
		jugando = false;
	}

	int getNombre() {
		return num_jug;
	}

	void setPuntos(int p) {
		puntos += p;
	}

	int getPuntos() {
		return puntos;
	}

	void setJugando(bool j) {
		jugando = j;
	}

	bool isJugando() {
		return jugando;
	}

};

int tirarDado() {
	int valor;
	valor = rand() % 6 + 1;
	return valor;
}

int revisarJugada(vector<int> dados) {
	int uno, dos, tres, cuatro, cinco, seis = 0;
	int jugada = 0;
	for (int i = 0; i < dados.size(); i++) {
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

void imprimirTirada(vector<int> dados) {
	Console::Clear();
	Console::WriteLine("	{0,10}", "Dados");
	int posicion = 1;
	for each (int dado in dados)
	{
		Console::WriteLine("    +-+");
		Console::WriteLine(" " + posicion + ") |" + dado + "|");
		Console::WriteLine("    +-+");
		posicion++;
	}
};

void imprimirTabla(vector<Jugador> jugadores) {
	Console::WriteLine("\n");
	Console::WriteLine("{0,10}", "Puntajes");
	String^ cabecera = "";
	for (unsigned int i=0; i < jugadores.size(); i++) {
		cabecera += ((jugadores[i].isJugando())?"*":" ")+"   Jugador" + (jugadores[i].getNombre()) + " | "+ jugadores[i].getPuntos()+"\n";
	}
	Console::WriteLine(cabecera);
}

void imprimirMenu(int estado) {
	Console::WriteLine("\n");
	Console::WriteLine((estado == 0) ? "	Lo siento no podrá guardar": "	0 para guardar");
	Console::WriteLine("	1 a 5 para volver a tirar dado");
	Console::WriteLine("	t para tirar nuevamente");
	Console::WriteLine("	n para todo nuevamente, si todos los dados poseen valor");

}

void main()
{
	int cant_dados, puntos, cant_jug,volver;
	String^ seleccion;
	vector<int> dados;
	bool fin_juego, fin_turno, guardar;
	fin_juego = false;
	fin_turno = false;
	guardar = false;
	volver = 0;
	unsigned int i_jugador = 0;
	Jugador player;
	
	do {
		Console::Clear();
		Console::WriteLine("	Bienvenido al 10000" +"\n"
		 "	El fin de este juego es juntar 10000 puntos tirando dados"+"\n"
		 "	Cada As vale 100 y cada 5 vale 50, sin embargo, si hay"+"\n"
		 "	tres números cualesquiera repetidos, el jugador sumará" +"\n"
		 "	ese número multiplicado por 100, aunque si fuese el As"+"\n"
		 "	sumará 1000, la escalera servida, vale 500 puntos y si al"+"\n"
		 "	tirar los dados no sumase bajo ninguna combinación, perderá""\n"
		 "	el turno y no podrá anotar lo que hubiese conseguido al momento");
		
		Console::WriteLine("	Cuantos jugadores van a  jugar (2 a 4):");
		cant_jug = cant_jug.Parse(Console::ReadLine());
	} while (cant_jug < 2 || cant_jug > 4);

	vector<Jugador> jugadores;

	for (int i = 0; i < cant_jug; i++) {
		jugadores.push_back(Jugador(i+1));
	}

	do 
	{

		player = jugadores[i_jugador];
		player.setJugando(true);
		
		Console::Clear();
		Console::WriteLine("\n\n");
		Console::WriteLine("	Es el turno del jugador #" + player.getNombre()+", presione una tecla para lanzar los dados");
		Console::ReadKey();
		Console::Clear();
		puntos = 0;
		cant_dados = 5;
		int actual = 0;

		do{ 
			dados.clear();
			//Tirar dados
			for (int i = 0; i < cant_dados; i++) {
				dados.push_back(tirarDado());
			}
			do { 
				//Elegir jugada
				imprimirTirada(dados);
				puntos = actual + revisarJugada(dados);
				Console::WriteLine("	Puntos -> " + puntos);
				imprimirMenu(puntos);
				imprimirTabla(jugadores);
				seleccion = Console::ReadLine();

				if (puntos == 0) {
					guardar = true;
					fin_turno = true;
					continue;
				}

				if (seleccion->Length == 0) {
					Console::WriteLine("	Por favor seleccione una opción válida antes de continuar");
				} else if (seleccion->Length==1){
					if (seleccion=="t") {
						//player.setPuntos(puntos);
						guardar = true;
						continue;
					} 

					if (seleccion == "n") {
						volver = 5;
						guardar = true;
						continue;
					}
					
					int dado = dado.Parse(seleccion);
					if (dado > 0 && dado < 6) {
						dados.erase(dados.begin() + dado-1);

						volver++;
					} else if (dado==0){
						player.setPuntos(puntos);
						player.setJugando(false);
						guardar = true;
						fin_turno = true;
					} else {
						Console::WriteLine("	Lo siento, no comprendo esa orden");
						puntos = 0;
					}
					
				}
				else {
					Console::WriteLine("	Lo siento, no comprendo esa orden");
				}
			} while (!guardar);
			actual = puntos;
			puntos = 0;
			cant_dados = volver;
		} while (!fin_turno);

		player.setJugando(false);
		// actualizo los datos del jugador
		jugadores[i_jugador] = player;

		// Cambio de jugador
		i_jugador++;
		// Vuelve a empezar la ronda
		if (i_jugador > (jugadores.size()-1)){
			i_jugador = 0;
		}

		// Chequeo puntajes para ver si terminó el juego, si algún jugador supera 10000 gana y se termina el mismo
		for each (Jugador jug in jugadores)
		{
			if (jug.getPuntos() > 10000) {
				fin_juego = true;
			}
			player = jug;
		}


	} while (!fin_juego);
	
	Console::Clear();
	Console::WriteLine("Felicitaciones jugador #" + player.getNombre() + " ha ganado la partida");
	Console::ReadLine();
}