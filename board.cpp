#include "board.hpp"

Board::Board(unsigned n = 5, unsigned m = 5, unsigned delay = 100) {
	n_ = n;
	m_ = m;

	board_ = new Cell**[n_];	//Filas	
	for (unsigned i = 0; i < n; i++) {
		board_[i] = new Cell*[m_];	//Columnas
		for (unsigned j = 0; j < m; j++)
			board_[i][j] = new Cell;	//Células en si
	}

	delay_ = delay;

}
Board::Board(const Board& b) {
	n_ = b.n_;
	m_ = b.m_;
	board_ = b.board_;
	delay_ = b.delay_;
}

Board::~Board() {
	for (unsigned i = 0; i < n_; i++)
			delete board_[i];
	delete board_;
	board_ = nullptr;
}

void Board::initializeCell(unsigned x, unsigned y, unsigned type) {
	
	if (!board_[x][y]->getType() != dead) {	//Si la célula xy está muerta, ponerla como viva
		delete board_[x][y];
		board_[x][y] = Cell::createCell(type);
	}
}

unsigned Board::getN()const {
	return n_;
}
unsigned Board::getM()const {
	return m_;
}

int Board::getType(unsigned x, unsigned y)const {
	return board_[x][y]->getType();
}

void Board::requestUpdate(void){


	for (unsigned i = 0; i < n_; i++) {
		for (unsigned j = 0; j < m_; j++) {
			board_[i][j]->prepareNextState(*this, i, j);	//Calculamos el estado nuevo de cada célula, y que lo guarden.
		}
	}
}

void Board::update(void){
	for (unsigned i = 0; i < n_; i++) {
		for (unsigned j = 0; j < m_; j++) {
			unsigned nextType = board_[i][j]->update();
			if (nextType != board_[i][j]->getType()) {	//Si el estado siguiente es diferente del actual, eliminamos la célula actual y creamos otra
				delete board_[i][j];
				board_[i][j] = Cell::createCell(nextType);
			}
		}
	}
}

void Board::printBoard(std::ostream& os)const {
	for (unsigned i = 0; i < n_; i++) {
		os << "|";
		for (unsigned j = 0; j < m_; j++) {
			board_[i][j]->printCell(os) << '|';
		}
		os << '\n';
	}
	os << '\n';
}

void Board::play(std::ostream& os) {

	playing_ = true;
	while (playing_) {
		printBoard(os);
		requestUpdate();
		update();
		
		#ifdef _WIN32	//Si estamos en windows, que compile _sleep(), sino que lo haga con usleep();
		   _sleep(delay_);
		#else
		  usleep(delay_*1000);
		#endif
	}
}
