#include "stdafx.h"
#include "plansza.h"


void plansza::Draw()
{
	Clear();

	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::fstream plik;
	plik.open("stan_gry.txt" , ios::in );
	
	if ( plik.good() == false )
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}	
	
	cout << "\t";
	for (int i = 0; i < 18; i++)
	{
		if( i % 2 == 0 ) cout << " " << (i/2)+1;
		else cout << "  ";
	}
	cout << endl;

	for (int w = 0; w < 18; w++)
	{
		if (w % 2 == 0)		cout << "\t" << (w/2)+1;
		else				cout << "\t ";

		for (int k = 0; k < 18; k++)
		{
			plik >> stan;
			if ( stan == "p")
			{
				SetConsoleTextAttribute(handle, 8); // kolor pola: szary
				cout << kwadrat << kwadrat;
			}
			if ( stan == "s" )
			{
				cout << "  ";
			}
			if ( stan == "g1" )
			{
				SetConsoleTextAttribute(handle, 11); // kolor gracza: niebieski
				cout << " @";
			}
			if ( stan == "g2" )
			{
				SetConsoleTextAttribute(handle, 10); // kolor gracza: zielony
				cout << " @";
			}
			if ( stan == "|")
			{
				SetConsoleTextAttribute(handle, 12); // kolor sciany: czerwony
				cout << " |";
			}
			if ( stan == "-")
			{
				SetConsoleTextAttribute(handle, 12); // kolor sciany: czerwony
				cout << "--";
			}

			SetConsoleTextAttribute(handle, 8); // kolor pola: szary
		}
		
		Description(w);

		cout << endl;
	}

	plik.close();
}

void plansza::Clear()
{
	system("cls");
}

void plansza::Description( int w )
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "\t";
	SetConsoleTextAttribute(handle, 26); 
	if (w == 0) cout << "\t\t\t---< QUORIDOR >---";
	SetConsoleTextAttribute(handle, 8); 
	if (w == 1) cout << "\t\tAutor : Jacek Giedronowicz";
	if (w == 2) cout << "Poruszanie sie pionkiem:" << "\t" << "Wstawianie scian:";
	if (w == 3) cout << "\tw - do gory" << "\t\t" << "\tP - pionowe sciany (perpendicularly)";
	if (w == 4) cout << "\ts - do dolu" << "\t\t" << "\tH - poziome sciany (horizontally)";
	if (w == 5) cout << "\ta - w lewo" << "\t\t" << "oraz okreslic miedzy jakimi polami wstawic";
	if (w == 6) cout << "\td - w prawo" << "\t\t" << "np. H12 - pozioma sciana, kolumna 1 , wiersz 2";
	
	if (w == 8) cout << "\tSciana H12";
	if (w == 9) cout << "\t 1" << "   " << "2" << "   " << "3";
	if (w == 10) cout << "\t1" << kwadrat << kwadrat << "  " << kwadrat << kwadrat << "  " << kwadrat << kwadrat;
	
	if (w == 12) cout << "\t2" << kwadrat << kwadrat << "  " << kwadrat << kwadrat << "  " << kwadrat << kwadrat;
	if (w == 13)
	{
		SetConsoleTextAttribute(handle, 12); // kolor sciany: czerwony
		cout << "\t " << "------";
		SetConsoleTextAttribute(handle, 8); // kolor pola: szary
	}
	if (w == 14) cout << "\t3" << kwadrat << kwadrat << "  " << kwadrat << kwadrat << "  " << kwadrat << kwadrat;


	if (w == 8) cout << "\t\tSciana P12";
	if (w == 9) cout << "\t\t 1" << "   " << "2" << "   " << "3";
	if (w == 10) cout << "\t\t1" << kwadrat << kwadrat << "  " << kwadrat << kwadrat << "  " << kwadrat << kwadrat;

	if (w == 12)
	{
		cout << "\t\t2" << kwadrat << kwadrat;
		SetConsoleTextAttribute(handle, 12); // kolor sciany: czerwony
		cout << " |";
		SetConsoleTextAttribute(handle, 8); // kolor pola: szary
		cout << kwadrat << kwadrat << "  " << kwadrat << kwadrat;
	}
	if (w == 13)
	{
		SetConsoleTextAttribute(handle, 12); // kolor sciany: czerwony
		cout << "\t\t\t    " << "|";
		SetConsoleTextAttribute(handle, 8); // kolor pola: szary
	}
	if (w == 14)
	{
		cout << "\t\t3" << kwadrat << kwadrat;
		SetConsoleTextAttribute(handle, 12); // kolor sciany: czerwony
		cout << " |";
		SetConsoleTextAttribute(handle, 8); // kolor pola: szary
		cout << kwadrat << kwadrat << "  " << kwadrat << kwadrat;
	}



	if (w == 17) cout << "-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-";
}

void plansza::Reset()
{
	std::fstream plik;
	plik.open("stan_gry.txt", ios::out);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	for (int w = 0; w < 18; w++)
	{
		for (int k = 0; k < 9; k++)
		{

			if ( k == 4 && (w==0 || w==16) )
			{
				if (w == 0)
				{
					plik << "g2\ts\t";
				}
				if (w == 16)
				{
					plik << "g1\ts\t";
				}
			}
			else
			{
				if (w % 2 == 1)
				{
					plik << "s\ts\t";
				}
				else
				{
					plik << "p\ts\t";
				}
			}		
		}
		plik << "\n";
	}

	plik.close();
}
