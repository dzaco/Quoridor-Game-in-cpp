#pragma once
#include "biblioteki.h"

class menu
{
	friend class gra;

	plansza * plansza;

	bool IsNewGame(); // sprawdza czy byla juz rozpoczeta gra
	bool DownloadParam;

public:
	menu();
	~menu();
	int Start();
	bool get_DownloadParam() { return DownloadParam; }

};

