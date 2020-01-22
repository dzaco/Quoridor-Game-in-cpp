#pragma once
#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

class gracz
{
protected:

	int PositionX;								// pozycja gracza (nr kolumny)
	int PositionY;								// pozycja gracza (nr wiersza)

	string WallH[10];							// pozycja postawionych scian poziomych
	string WallP[10];							// pozycja postawionych scian pionowych

public:

	bool IsFirstPlayer;							// flaga, pierwszy gracz ma kolor niebieski , drugi ma kolor zielony
	bool IsHuman;
	gracz *nast;								// gracz wskazuje na swojego rywala
	void Move(string);							// poruszenie pionka przez gracza
	void Wall(string);							// postawienie sciany przez gracza
	

	virtual string Turn() = 0;					// gracz wczytuje swoj ruch , wywoluje odpowiednie metody Move() lub Wall()
	
	int get_PositionX() { return PositionX; }	// get'ery prywatne 
	int get_PositionY() { return PositionY; }	// wartosci PositionX i PositionY
	int get_WallH(int i, int j);				// zwraca wartosc i-tej sciany , j-te wspolrzedne
	int get_WallP(int i, int j);				// zwraca wartosc i-tej sciany , j-te wspolrzedne
	string get_WallH(int i);					// zwraca wartosc i-tej sciany
	string get_WallP(int i);					// zwraca wartosc i-tej sciany
	void set_WallH(string ruch);
	void set_WallP(string ruch);
	int get_SizeOfWallH();						//sprawdza ile scian jest zapisanych
	int get_SizeOfWallP();						//sprawdza ile scian jest zapisanych

};

