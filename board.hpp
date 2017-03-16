#ifndef __BOARD_H_
#define __BOARD_H_

#ifdef _WIN32
   //Nothing
#else
  #include <unistd.h>
#endif

#include <vector>
#include "cell.hpp"
#include <iostream>


class Board{
	unsigned n_;	//tamaño n del tablero, 0 - n-1
	unsigned m_;	//tamaño m del tablero, 0 - m-1
	unsigned delay_;

	Cell*** board_;		//Tablero que se muestra al usuario. Puntero de punteros (matriz de punteros) que guarda punteros de tipo Cell

	bool playing_;	//true si está ejecutando, false si no.

	void requestUpdate(void);
	void update(void);

public:
	Board(unsigned n, unsigned m, unsigned delay);//Constructor
	Board(const Board& b);//constructor copia
	~Board();	//Destructor
	void initializeCell(unsigned x, unsigned y, unsigned type);	//La célula xy será puesta como viva al principio de la simulación
	unsigned getN()const;
	unsigned getM()const;
	int getType(unsigned x, unsigned y)const;
	void printBoard(std::ostream& os)const;
	void play(std::ostream& os);
	
};

#endif
