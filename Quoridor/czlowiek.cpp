#include "stdafx.h"
#include "czlowiek.h"


czlowiek::czlowiek( bool fp )
{
	IsFirstPlayer = fp;
	nast = NULL;
	FindPlayer();
}

void czlowiek::FindPlayer()
{
	std::fstream plik;
	plik.open("stan_gry.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	string szukana;
	if (IsFirstPlayer) szukana = "g1";
	else szukana = "g2";

	string stan;
	for (int w = 1; w <= 18; w++)
	{
		for (int k = 1; k <= 18; k++)
		{
			plik >> stan;
			if (stan == szukana)
			{
				PositionX = k;
				PositionY = w;
			}
		}
	}


	plik.close();
}

string czlowiek::Turn()
{
	cout << "Twoj ruch:" << endl;
	string ruch;
	cin >> ruch;

	if (ruch.length() != 1 && ruch.length() != 3)
	{
		ruch = "0";
		return ruch;
	}
	if ( ruch.length() == 1 )
	{
		if (ruch != "w" && ruch != "a" && ruch != "s" && ruch != "d")
		{
			ruch = "0";
			return ruch;
		}
	}
	else if ( ruch.length() == 3 )
	{
		if ( ruch[0] != 'P' && ruch[0] != 'p' && ruch[0] != 'H' && ruch[0] != 'h' )
		{
			ruch = "0";
			return ruch;
		}
		if ( ruch[1] < '1' || ruch[1] > '8' )
		{
			ruch = "0";
			return ruch;
		}
		if (ruch[2] < '1' || ruch[2] > '8')
		{
			ruch = "0";
			return ruch;
		}

		if (ruch[0] == 'h') ruch[0] = 'H';
		if (ruch[0] == 'p') ruch[0] = 'P';
	}


	return ruch;
}