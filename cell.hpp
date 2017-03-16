#ifndef __CELL_H_
#define __CELL_H_

#ifdef _WIN32
	#include <windows.h>   // WinApi header
#else
	#define RST  "\x1B[0m"
	#define KRED  "\x1B[31m"
	#define KGRN  "\x1B[32m"
	#define KBLU  "\x1B[34m"

	#define FRED(x) KRED x RST
	#define FGRN(x) KGRN x RST
	#define FBLU(x) KBLU x RST
#endif

#include <iostream>

const unsigned UNASSIGNED = 65535;
const unsigned dead = 0;
const unsigned typeA = 1;
const unsigned typeB = 2;
const unsigned typeC = 3;



class Board;

class Cell{	

protected:
	int next_state_;	//Siguiente estado, que será de utilidad para el tablero. 0,1,2,3
	unsigned neighbors_;	//Número de vecinos en su proximidad.
	void lookUpArround(const Board& board, unsigned n, unsigned m);	//Calcula el número de vecinos de cada célula
	int type_;	

	#ifdef _WIN32
		HANDLE  hConsole;
	#endif
	

public:
	Cell();		//Constructor
	Cell(const Cell& c);		//Constructor copia
	virtual void prepareNextState(const Board& board, unsigned x, unsigned y);	//Actualiza su estado y lo guarda en next_state_
	int update();		//Actualiza su estado actual por el siguiente, y lo retorna
	int getType()const;	//return el tipo de célula
	virtual std::ostream& printCell(std::ostream& os) const;

	static Cell* createCell(unsigned n);	//Crea una célula según el índice 0->Normal 1->A 2->B 3->C
};

class CellA : public Cell{

public:
	CellA();//Constructor
	CellA(const CellA& c);//Constructor copia
	virtual void prepareNextState(const Board& board, unsigned x, unsigned y);	//Actualiza su estado y lo guarda en next_state_
	virtual std::ostream& printCell(std::ostream& os) const;
};

class CellB : public Cell{

public:
	CellB();//Constructor
	CellB(const CellB& c);//Constructor copia
	virtual void prepareNextState(const Board& board, unsigned x, unsigned y);	//Actualiza su estado
	virtual std::ostream& printCell(std::ostream& os) const;
};

class CellC : public Cell{

public:
	CellC();//Constructor
	CellC(const CellC& c);//Constructor copia
	virtual void prepareNextState(const Board& board, unsigned x, unsigned y);	//Actualiza su estado
	virtual std::ostream& printCell(std::ostream& os) const;
};

#endif
