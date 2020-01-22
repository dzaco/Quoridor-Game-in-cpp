#include "stdafx.h"
#include "komputer.h"


komputer::komputer()
{
	nast = NULL;
	FindComp();
}

void komputer::FindComp()
{
	std::fstream plik;
	plik.open("stan_gry.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	string stan;
	for (int w = 1; w <= 18; w++)
	{
		for (int k = 1; k <= 18; k++)
		{
			plik >> stan;
			if (stan == "g2")
			{
				PositionX = k;
				PositionY = w;
			}
		}
	}


	plik.close();
}

string komputer::Turn()
{
	int typ_ruchu;
	string ruch;
	srand( time(NULL) );
	typ_ruchu = rand() % 3 + 1;

	if ( typ_ruchu == 1 || typ_ruchu == 2 )
	{
		int pom;
		pom = rand() % 10 + 1;

		switch ( pom )
		{
		case 1:				// z prawdopodobienstwem 
		case 2:				//   5/10 komputer poruszy sie "s"
		case 3:
		case 4:
		case 5:
			ruch = "s";
			break;
		case 6:				// z prawdopodobienstwem 
		case 7:				//   2/10 komputer poruszy sie "a"
			ruch = "a";
			break;
		case 8:				// z prawdopodobienstwem
							//   1/10 komputer poruszy sie "w"
			ruch = "w";
			break;
		case 9:				// z prawdopodobienstwem 
		case 10:			//   2/10 komputer poruszy sie "d"
			ruch = "d";
			break;
		default:
			break;
		}

	}
	else if (typ_ruchu == 3)
	{
		int pom;
		pom = rand() % 2 + 1;

		switch (pom)
		{
		case 1:
			ruch = "P";
			break;
		case 2:
			ruch = "H";
			break;
		default:
			break;
		}


		pom = rand() % 8 + 1;
		ruch += (char)pom + 48;
		pom = rand() % 8 + 1;
		ruch += (char)pom + 48;

	}	

	return ruch;
}
