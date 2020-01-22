#include "stdafx.h"
#include "gra.h"



gra::gra( int nr , bool par )
{

	if ( nr == 1 )
	{
		p1 = new czlowiek(true);
		p2 = new komputer;
		
		p1->IsHuman = true;
		p2->IsHuman = false;
	}
	else if ( nr == 2)
	{
		p1 = new czlowiek(true);
		p2 = new czlowiek(false);

		p1->IsHuman = true;
		p2->IsHuman = true;
	}
	else
	{
		cout << "Blad " << endl;
		exit(0);
	}

	

	wsk = p1;						//wskazuje na gracza1
	wsk->nast = p2;					// nastepnym graczem jest gracz2
	wsk = wsk->nast;				//wskazuje na gracz2
	wsk->nast = p1;					//po graczu 2 jest gracz1
	wsk = wsk->nast;				//wskazuje na gracz1
									//powstala petla kolejnosci ruchow graczy
									// gracz1 -> gracz2 -> gracz1 -> ...


	if (par) get_AllFieldsOfGame();

}

gra::~gra()
{
	delete p1;
	delete p2;
}

int gra::CheckWiner()
{
	if (p1->get_PositionY() == 1) return 1;
	if (p2->get_PositionY() == 17) return 2;

	return 0;
}
void gra::set_AllFieldsOfGame()
{
	std::fstream plik;
	plik.open("parametry.txt", ios::out);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	plik << "1\t";
	for (int i = 0; i < p1->get_SizeOfWallH(); i++)
	{
		plik << p1->get_WallH(i) << "\t";
	}
	plik << endl;

	plik << "2\t";
	for (int i = 0; i < p1->get_SizeOfWallP(); i++)
	{
		plik << p1->get_WallP(i) << "\t";
	}
	plik << endl;

	plik << "3\t";
	for (int i = 0; i < p2->get_SizeOfWallH(); i++)
	{
		plik << p2->get_WallH(i) << "\t";
	}
	plik << endl;

	plik << "4\t";
	for (int i = 0; i < p2->get_SizeOfWallP(); i++)
	{
		plik << p2->get_WallP(i) << "\t";
	}


	plik.close();
}
void gra::get_AllFieldsOfGame()
{
	std::fstream plik;
	plik.open("parametry.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	string stan;
	
	plik >> stan;

	for ( int i = 0; stan != "2"; i++ )
	{
		if (stan == "1") stan = "";
		plik >> stan;
		if (stan == "2") break;
		p1->set_WallH(stan);
		set_WallAll(stan);
	}

	for (int i = 0; stan != "3"; i++)
	{
		if (stan == "2") stan = "";
		plik >> stan;
		if (stan == "3") break;
		p1->set_WallP(stan);
		set_WallAll(stan);
	}

	for (int i = 0; stan != "4"; i++)
	{
		if (stan == "3") stan = "";
		plik >> stan;
		if (stan == "4") break;
		p2->set_WallH(stan);
		set_WallAll(stan);
	}

	for (int i = 0; !plik.eof() ; i++)
	{
		if (stan == "4") stan = "";
		plik >> stan;
		p2->set_WallP(stan);
		set_WallAll(stan);
		stan = "";
	}

//------------------------------------------------------------

	

	plik.close();
}
int gra::get_SizeOfWallAll()
{
	for (int i = 0; i < 20; i++)
	{
		if (WallAll[i] == "\0")
			return i;

	}
}
void gra::set_WallAll(string ruch)
{
	WallAll[get_SizeOfWallAll()] = ruch;
}
string gra::get_WallAll( int i )
{
	return WallAll[i];
}
int gra::get_WallAll(int i, int j)
{
	int pom;

	pom = (int)WallAll[i][j];
	pom -= 48;

	return pom;
}
int gra::CheckMove(string ruch)
{
	//sprawdza wolne pola
	if (ruch == "w")
	{
		if (wsk->get_PositionY() == 1) return 0;
		if (wsk->get_PositionY() - 2 == 1 && wsk->nast->get_PositionY() == 1 && wsk->get_PositionX() == wsk->nast->get_PositionX() ) return 0; // jeden z graczy stoi przy scianie, tarasujac droge drugiemu graczowi
	}
	if (ruch == "a")
	{
		if (wsk->get_PositionX() == 1) return 0;
		if (wsk->get_PositionX() - 2 == 1 && wsk->nast->get_PositionY() == wsk->get_PositionY() && wsk->nast->get_PositionX() == 1 ) return 0; // jeden z graczy stoi przy scianie, tarasujac droge drugiemu graczowi
	}
	if (ruch == "s")
	{
		if (wsk->get_PositionY() == 17) return 0;
		if (wsk->get_PositionY() + 2 == 17 && wsk->nast->get_PositionX() == wsk->get_PositionX() && wsk->nast->get_PositionY() == 17 ) return 0; // jeden z graczy stoi przy scianie, tarasujac droge drugiemu graczowi
	}
	if (ruch == "d")
	{
		if (wsk->get_PositionX() == 17) return 0;
		if (wsk->get_PositionX() + 2 == 17 && wsk->nast->get_PositionY() == wsk->get_PositionY() && wsk->nast->get_PositionX() == 17) return 0; // jeden z graczy stoi przy scianie, tarasujac droge drugiemu graczowi
	}

	//sprawdza czy nie ma sciany
	if (ruch == "w")
	{
		for ( int i = 0; i < get_SizeOfWallAll(); i++ )
		{
			if ( get_WallAll(i)[0] == 'H' ) // sciana
			{
				if ( get_WallAll(i, 2) * 2 + 1 == wsk->get_PositionY() &&
					(get_WallAll(i, 1) * 2 + 1 == wsk->get_PositionX() ||
					 get_WallAll(i, 1) * 2 - 1 == wsk->get_PositionX() ) )
					return 0; // sciana przed graczem

				if (wsk->nast->get_PositionY() == wsk->get_PositionY() - 2 &&
					wsk->nast->get_PositionX() == wsk->get_PositionX() &&
					get_WallAll(i, 2) * 2 + 3 == wsk->get_PositionY() &&
					(get_WallAll(i, 1) * 2 + 1 == wsk->get_PositionX() ||
						get_WallAll(i, 1) * 2 - 1 == wsk->get_PositionX()))
					return 0; // przed graczem jest drugi gracz a za nim sciana
			}

		}
	}
	if (ruch == "s")
	{
		for (int i = 0; i < get_SizeOfWallAll(); i++)
		{
			if (get_WallAll(i)[0] == 'H')
			{
				if (get_WallAll(i, 2) * 2 - 1 == wsk->get_PositionY() &&
					(get_WallAll(i, 1) * 2 + 1 == wsk->get_PositionX() ||
					 get_WallAll(i, 1) * 2 - 1 == wsk->get_PositionX() ) )
					return 0;

				if (wsk->nast->get_PositionY() == wsk->get_PositionY() + 2 &&
					wsk->nast->get_PositionX() == wsk->get_PositionX() &&					
					get_WallAll(i, 2) * 2 - 3 == wsk->get_PositionY() &&
					(get_WallAll(i, 1) * 2 + 1 == wsk->get_PositionX() ||
						get_WallAll(i, 1) * 2 - 1 == wsk->get_PositionX()))
					return 0;


			}
		}
	}
	if (ruch == "a")
	{
		for (int i = 0; i < get_SizeOfWallAll(); i++ )
		{
			if ( WallAll[i][0] == 'P' )
			{
				if ( get_WallAll(i, 1) * 2 + 1 == wsk->get_PositionX() &&
					(get_WallAll(i, 2) * 2 + 1 == wsk->get_PositionY() ||
					 get_WallAll(i, 2) * 2 - 1 == wsk->get_PositionY() ) )
					return 0;

				if (wsk->nast->get_PositionX() == wsk->get_PositionX() - 2 &&
					wsk->nast->get_PositionY() == wsk->get_PositionY() &&
					get_WallAll(i, 1) * 2 + 3 == wsk->get_PositionX() &&
					(get_WallAll(i, 2) * 2 + 1 == wsk->get_PositionY() ||
						get_WallAll(i, 2) * 2 - 1 == wsk->get_PositionY()))
					return 0;

			}
		}
	}
	if (ruch == "d")
	{
		for (int i = 0; i < get_SizeOfWallAll(); i++)
		{
			if (WallAll[i][0] == 'P')
			{
				if (get_WallAll(i, 1) * 2 - 1 == wsk->get_PositionX() &&
					(get_WallAll(i, 2) * 2 + 1 == wsk->get_PositionY() ||
					 get_WallAll(i, 2) * 2 - 1 == wsk->get_PositionY() ) )
					return 0;

				if (wsk->nast->get_PositionX() == wsk->get_PositionX() + 2 &&
					wsk->nast->get_PositionY() == wsk->get_PositionY() &&
					get_WallAll(i, 1) * 2 - 3 == wsk->get_PositionX() &&
					(get_WallAll(i, 2) * 2 + 1 == wsk->get_PositionY() ||
						get_WallAll(i, 2) * 2 - 1 == wsk->get_PositionY()))
					return 0;

			}
		}
	}


	return 1;
}
int gra::CheckWall( string ruch)
{

	if (ruch.length() == 3) // w przeciwnym wypadku chodzilo o ruszenie pionka
	{
		if (p1->get_SizeOfWallH() + p1->get_SizeOfWallP() == 10) return 0; // wykorzystano limit stawiania scian
		if (p2->get_SizeOfWallH() + p2->get_SizeOfWallP() == 10) return 0; // wykorzystano limit stawiania scian

		int xA, yA; // pomocnicze przechowujace pola z sprawdzanego ruchu
		xA = (int)ruch[1] - 48;
		yA = (int)ruch[2] - 48;

		
		for ( int i = 0; i < get_SizeOfWallAll(); i++ )
		{
			if (ruch == WallAll[i]) return 0; // taka sciana juz istnieje

			if ( ruch[0] == 'H' )
			{
				if(yA == get_WallAll(i, 2) &&
					(xA == get_WallAll(i, 1) || xA == get_WallAll(i, 1) + 1 || xA == get_WallAll(i, 1) - 1))
					return 0; 
				if (xA == get_WallAll(i, 1) && yA == get_WallAll(i, 2)) return 0; // sciana krzyzuje sie z istniejaca sciana pionowa
			}
			else
			{
				if(xA == get_WallAll(i, 1) &&
					(yA == get_WallAll(i, 2) || yA == get_WallAll(i, 2) + 1 || yA == get_WallAll(i, 2) - 1))
					return 0;
				if (xA == get_WallAll(i, 1) && yA == get_WallAll(i, 2)) return 0; // sciana krzyzuje sie z istniejaca sciana pionowa
			}

		}

		set_WallAll(ruch);
	}

	
	return 1;
}

void gra::Update()
{

	std::fstream plik;
	plik.open("stan_gry.txt", ios::out);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	for (int w = 1; w < 19; w++)
	{
		for (int k = 1; k < 19; k++ )
		{
			bool flag = false;

			if (w % 2 == 0) // wiersze parzyste
			{
				for (int i = 0; i < get_SizeOfWallAll(); i++)
				{
					if (WallAll[i][0] == 'H') // H
					{
						if (w == get_WallAll(i, 2) * 2)
						{
							if (k == get_WallAll(i, 1) * 2 - 1)
							{
								plik << "-\t";
								flag = true;
								continue;
							}
							else if (k == get_WallAll(i, 1) * 2)
							{
								plik << "-\t";
								flag = true;
								continue;
							}
							else if (k == get_WallAll(i, 1) * 2 + 1)
							{
								plik << "-\t";
								flag = true;
								continue;
							}

						}
					}
					else // P
					{
						if (w == get_WallAll(i, 2) * 2 && k == get_WallAll(i, 1) * 2)
						{
							plik << "|\t";
							flag = true;
							continue;
						}
					}
				}

				if (!flag)
				{
					plik << "s\t";
					continue;
				}
			}
			else // wiersze nieparzyste
			{
				if (k % 2 == 1) // kolumny nieparzyste
				{
					if (w == p1->get_PositionY() && k == p1->get_PositionX())
					{
						plik << "g1\t";
						continue;
					}
					else if (w == p2->get_PositionY() && k == p2->get_PositionX())
					{
						plik << "g2\t";
						continue;
					}
					else
					{
						plik << "p\t";
						continue;
					}

				}
				else // kolumny parzyste
				{
					for (int i = 0; i < get_SizeOfWallAll(); i++)
					{
						if (WallAll[i][0] == 'P') //P
						{
							if (k == get_WallAll(i, 1) * 2)
							{
								if (w == get_WallAll(i, 2) * 2 - 1 || w == get_WallAll(i, 2) * 2 + 1)
								{
									plik << "|\t";
									flag = true;
									continue;
								}
							}
						}
					}

					if (!flag)
					{
						plik << "s\t";
						continue;
					}
				}
			}

		}
		
		plik << '\n';
	}


	plik.close();
}

void gra::Play()
{
	plansza plansza;
	string ruch;

	plansza.Draw();

	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	while ( true )
	{
		//zapisanie i wyswietlenie ruchu
		set_AllFieldsOfGame();
		

		// Wypisanie czyja jest aktualnie tura
		if (wsk->IsFirstPlayer)
		{
			cout << "Tura Gracza 1.";
			SetConsoleTextAttribute(handle, 11); // kolor gracza: blekitny
			cout << "NIEBIESKI\n";
			SetConsoleTextAttribute(handle, 8); // kolor pola: szary
		}
		
		else
		{
			cout << "Tura Gracza 2.";
			SetConsoleTextAttribute(handle, 10); // kolor gracza: zielony
			cout << "ZIELONY\n";
			SetConsoleTextAttribute(handle, 8); // kolor pola: szary
		}

		cout << "\t Pozostale sciany - [" << 10 - (wsk->get_SizeOfWallH() + wsk->get_SizeOfWallP() ) << "]" << endl;
		//wczytanie ruchu gracza
		ruch = wsk->Turn();

		//sprawdzenie czy ciag znakow byl prawidlowy 
		while (ruch == "0" || CheckMove( ruch) == 0 || CheckWall(ruch) == 0 )
		{
			if (wsk->IsHuman)
			{
				plansza.Clear();
				plansza.Draw();
				cout << "Nieprawidlowy ruch" << endl;
			}
			ruch = wsk->Turn();
		}

		//wykonanie ruchu
		if (ruch.length() == 1)
		{
			// ruch pionka np w , a , s , d
			wsk->Move(ruch);
		}
		else if (ruch.length() == 3)
		{
			// sciana np H12
			wsk->Wall(ruch);
		}

		Update();
		plansza.Draw();		


		//nastepny gracz
		wsk = wsk->nast;

		int nr = CheckWiner();
		if ( nr )
		{
			plansza.Clear();
			plansza.Reset();
			if (nr == 1)
			{
				SetConsoleTextAttribute(handle, 11); // kolor gracza: blekitny
				cout << "\n\n\n\n\t\t\t\t";
				cout << "Gracz " << nr << ". NIEBIESKI wygrywa" << endl;
				SetConsoleTextAttribute(handle, 8); // kolor pola: szary
			}
			else if (nr == 2)
			{
				SetConsoleTextAttribute(handle, 10); // kolor gracza: zielony
				cout << "\n\n\n\n\t\t\t\t";
				cout << "Gracz " << nr << ". ZIELONY wygrywa" << endl;
				SetConsoleTextAttribute(handle, 8); // kolor pola: szary
			}
			
			break;
		}
	}



}