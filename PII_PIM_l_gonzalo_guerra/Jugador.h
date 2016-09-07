#pragma once
ref class Jugador
{

private:
	int puntos;
	bool jugando;
	int num_jug;

public:
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


