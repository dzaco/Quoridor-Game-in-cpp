#pragma once
#include "gracz.h"

#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

class czlowiek : public gracz
{
protected:
	void FindPlayer(); // znajduje pozycje gracza

public:
	czlowiek(bool);
	string Turn();
	
};

