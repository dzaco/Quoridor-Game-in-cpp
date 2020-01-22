#pragma once
#include "biblioteki.h"
#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

class plansza
{

	char kwadrat = 219;
	string stan;


public:
	void Draw();							// drukowanie planszy
	void Clear();							// czyszczenie planszy
	void Description( int i );				// opis/informacja dla gracza o zasadach gry i mozliwych ruchach. Jako argument podany numer wiersza.
	void Reset();							// przywracanie poczatkowego stanu gry
	
	
};

