#pragma once
#include "biblioteki.h"

class gra
{
	gracz *p1;
	gracz *p2;
	gracz *wsk;
	string WallAll[20];
	void Update();


	void set_WallAll(string ruch);
	int get_SizeOfWallAll();
	string get_WallAll(int i);
	int get_WallAll(int i, int j);
	void get_AllFieldsOfGame();
	void set_AllFieldsOfGame();
	int CheckMove(string ruch);					// sprawdza poprawnosc ruchu gracza
	int CheckWall(string ruch);					// sprawdza poprawnosc stawianej sciany
	int CheckWiner();

public:
	gra() : p1(NULL), p2(NULL) , wsk(NULL) {} ;
	gra( int , bool );
	~gra();

	void Play(); // glowna petla gry
};

