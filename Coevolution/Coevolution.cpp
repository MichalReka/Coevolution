#include<iostream>
#include "CoevolutionAlgorithm.h"
int main() {
	srand(time(NULL));
	std::cout << "Hello" << std::endl;
	CoevolutionAlgorithm coev;
	coev.Run();
}