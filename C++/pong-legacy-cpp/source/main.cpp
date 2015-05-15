#include <iostream>
#include "../include/game.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	game * g = new game();

	g->run();

	delete g;
	return 0;
	
}