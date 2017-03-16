
#include "board.hpp"
#include <iostream>
#include <stdlib.h>     /*srand, rand */
#include <time.h>       /* time */
int main (void){
  
	unsigned x = 5, y = 5;

	std::cout << "Introduce el tamaño del campo de juego (Por defecto 5x5): \n";
	std::cout << "X:";
	std::cin >> x;
	std::cout << "Y:";
	std::cin >> y;

	unsigned delay = 0;
	
	std::cout << "Delay entre actualizaciones (ms): ";
	std::cin >> delay;


	std::cout << "Se generarán células vivas de forma aleatoria por el campo de juego.\n";
	Board B(x, y, delay);


	srand(time(NULL));

	for(unsigned i = 0; i < x ; i++){
		for(unsigned j = 0; j < y; j++){
			if(rand() % 2)
				B.initializeCell(i,j, rand()%3 + 1);
		}
	}

	B.play(std::cout);

	return 0;
}
