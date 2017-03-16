#include "cell.hpp"
#include "board.hpp"

Cell::Cell(){
	type_ = dead;
	next_state_ = UNASSIGNED;
	neighbors_ = UNASSIGNED;

	#ifdef _WIN32
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif

	
}

Cell::Cell(const Cell& c){
	type_ = c.type_;
	next_state_ = c.next_state_;
	neighbors_ = c.neighbors_;
}

void Cell::lookUpArround(const Board& board, unsigned n, unsigned m){	//Posiciones 0 - n-1 CAMBIAR

	neighbors_ = 0;
	n++;
	m++;

	for (int i = n-1 ; i <= n+1 ; i++) {
		for (int j = m-1 ; j <= m+1 ; j++) {
			if ( !(i-1 < 0 || j-1 < 0 || i-1 >= board.getN() || j-1 >= board.getM() ) && board.getType(i-1,j-1) != dead ) {	//Si está dentro de los límites de su vecindad y está viva, es un vecino.
				neighbors_++;
			}
		}
	}
	
	if (type_ != dead) {	//Si type_=1,2,3 estonces está viva y se contó a si misma.
		neighbors_--;
	}
}

void Cell::prepareNextState(const Board& board, unsigned x, unsigned y) {

	lookUpArround(board, x, y);

    if (neighbors_ == 3)
        next_state_ = typeA;
    else if(neighbors_ == 4)
        next_state_ = typeB;
    else if(neighbors_ == 6)
        next_state_ = typeC;
    else
        next_state_ = dead;
    
}


int Cell::update(){
	return next_state_;
}


int Cell::getType()const {
	return type_;
}

std::ostream& Cell::printCell(std::ostream& os) const {
	os << ' ';
	return os;
}


Cell* Cell::createCell(unsigned n) {
	//delete c;
	//c = nullptr;
	Cell* c = nullptr;
	switch (n) {
	case 0: { c = new Cell;  break; }
	case 1: { c = new CellA;  break; }
	case 2: { c = new CellB;  break; }
	case 3: { c = new CellC;  break; }
	default:
		std::cerr << "Bad parameter in createCell\n";
	
	}
	return c;
}

// CELL A

CellA::CellA(){
	type_ = typeA;
	next_state_ = UNASSIGNED;
	neighbors_ = UNASSIGNED;
}

CellA::CellA(const CellA& c){
	type_ = c.type_;
	next_state_ = c.next_state_;
	neighbors_ = c.neighbors_;
}

void CellA::prepareNextState(const Board& board, unsigned x, unsigned y) {
	lookUpArround(board, x, y);

	if (neighbors_ == 2 || neighbors_ == 3)
		next_state_ = typeA;
	else
		next_state_ = dead;
}

std::ostream& CellA::printCell(std::ostream& os) const {

	#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, 10);	//ponemos el color
		os << 'A';
		SetConsoleTextAttribute(hConsole, 15);	//se lo quitamos
	#else
		os << FGRN("A");
	#endif

	
	return os;
}

// CELL B

CellB::CellB(){
	type_ = typeB;
	next_state_ = UNASSIGNED;
	neighbors_ = UNASSIGNED;
}

CellB::CellB(const CellB& c){
	type_ = c.type_;
	next_state_ = c.next_state_;
	neighbors_ = c.neighbors_;
}

std::ostream& CellB::printCell(std::ostream& os) const {

	#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, 11);//ponemos el color
		os << 'B';
		SetConsoleTextAttribute(hConsole, 15);//se lo quitamos
	#else
		os << FBLU("B");
	#endif

	
	return os;
}

void CellB::prepareNextState(const Board& board, unsigned x, unsigned y) {
	lookUpArround(board, x, y);

	if (neighbors_ == 3 || neighbors_ == 4)
		next_state_ = typeB;
	else
		next_state_ = dead;
}

// CELL C

CellC::CellC(){
	type_ = typeC;
	next_state_ = UNASSIGNED;
	neighbors_ = UNASSIGNED;
}

CellC::CellC(const CellC& c){
	type_ = c.type_;
	next_state_ = c.next_state_;
	neighbors_ = c.neighbors_;
}

std::ostream& CellC::printCell(std::ostream& os) const {

	#ifdef _WIN32
		SetConsoleTextAttribute(hConsole, 12);//ponemos el color
		os << 'C';
		SetConsoleTextAttribute(hConsole, 15);//se lo quitamos
	#else
		os << FRED("C");
	#endif


	
	return os;
}

void CellC::prepareNextState(const Board& board, unsigned x, unsigned y) {
	lookUpArround(board, x, y);

	if (neighbors_ == 1 || neighbors_ == 5)
		next_state_ = typeC;
	else
		next_state_ = dead;
}
