#include "stdafx.h"
#include "gracz.h"
#include <string>
using namespace std;

void gracz::Move(string ruch)
{

	if (ruch == "w")
	{
		if (this->get_PositionX() == this->nast->get_PositionX() && this->get_PositionY() == this->nast->get_PositionY()+2 )
		{
			PositionY -= 4;
		}
		else PositionY -= 2;
	}
	else if (ruch == "a")
	{
		if (this->get_PositionY() == this->nast->get_PositionY() && this->get_PositionX() == this->nast->get_PositionX() + 2)
		{
			PositionX -= 4;
		}
		else PositionX -= 2;
	}
	else if (ruch == "s")
	{
		if (this->get_PositionX() == this->nast->get_PositionX() && this->get_PositionY() == this->nast->get_PositionY() -2 )
		{
			PositionY += 4;
		}
		else PositionY += 2;
	}
	else if (ruch == "d")
	{
		if (this->get_PositionY() == this->nast->get_PositionY() && this->get_PositionX() == this->nast->get_PositionX() - 2)
		{
			PositionX += 4;
		}
		else PositionX += 2;
	}

}

void gracz::Wall(string ruch)
{
	int size;

	if (ruch[0] == 'H' || ruch[0] == 'h' )
	{
		size = get_SizeOfWallH();
		WallH[size] = ruch;
	}
	else
	{
		size = get_SizeOfWallP();
		WallP[size] = ruch;
	}
}

int gracz::get_SizeOfWallH()
{
	for (int i = 0; i < 10; i++)
	{
		if (WallH[i] == "\0")
			return i;

	}
}

int gracz::get_SizeOfWallP()
{
	for (int i = 0; i < 10; i++)
	{
		if (WallP[i] == "\0")
			return i;

	}
}

int gracz::get_WallH(int i, int j)
{
	int pom;

	pom = (int)WallH[i][j];
	pom -= 48;

	return pom;
}

int gracz::get_WallP(int i, int j)
{
	int pom;

	pom = (int)WallP[i][j];
	pom -= 48;

	return pom;
}

string gracz::get_WallH(int i)
{
	return WallH[i];
}

string gracz::get_WallP(int i)
{
	return WallP[i];
}

void gracz::set_WallH(string ruch)
{
	WallH[get_SizeOfWallH()] = ruch;
}

void gracz::set_WallP(string ruch)
{
	WallP[get_SizeOfWallP()] = ruch;
}
