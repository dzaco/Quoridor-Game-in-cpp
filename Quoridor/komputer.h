#pragma once
#include <cstdlib>
#include <ctime>
#include "gracz.h"
class komputer : public gracz
{
protected:
	void FindComp(); // znajduje pozycje gracza-komputera
	

public:
	string Turn();

	komputer();
};

