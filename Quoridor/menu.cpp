#include "stdafx.h"
#include "menu.h"



bool menu::IsNewGame()
{
	std::fstream plik;
	plik.open("stan_gry.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia pliku" << endl;
		exit(1);
	}

	// sprawdzam czy plik jest domyslny czy z modyfikacjami  (czy juz gra sie odbywala czy jest nowa)
	string stan;
	bool CzyNowa = true;
	for (int w = 0; w < 18; w++)
	{
		for (int k = 0; k < 18; k++)
		{
			plik >> stan;
			if (k == 8 && (w == 0 || w == 16))
			{
				if (w == 0 && stan != "g2") { CzyNowa = false; }
				if (w == 16 && stan != "g1") { CzyNowa = false; }
			}
			else
			{
				if (w % 2 == 1 && stan != "s") { CzyNowa = false; }
				if (w % 2 == 0)
				{
					if (k % 2 == 0 && stan != "p") { CzyNowa = false; }
					if (k % 2 == 1 && stan != "s") { CzyNowa = false; }
				}
			}

			if (CzyNowa == false)
			{
				plik.close();
				return CzyNowa;
			}

		}
	}


	plik.close();

	return CzyNowa;
}

menu::menu() : plansza(NULL)
{
	DownloadParam = false;
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!IsNewGame())
	{

		cout << "\n\n\n\n\n\n" << endl;
		SetConsoleTextAttribute(handle, 15);
		cout << "\t\t\t\t\t\t--- < Quoridor > ---" << endl;
		SetConsoleTextAttribute(handle, 12); 
		cout << "\t\t\t\t\t" << "---------------------------------" << endl;
		SetConsoleTextAttribute(handle, 8);
		cout << "\t\t\t\t\t" << "|\t" "1. Nowa gra" "\t\t|" << endl;
		SetConsoleTextAttribute(handle, 12);
		cout << "\t\t\t\t\t" << "---------------------------------" << endl;
		SetConsoleTextAttribute(handle, 8);
		cout << "\t\t\t\t\t" << "|\t" << "2. Kontynuuj gre" << "\t|" << endl;
		SetConsoleTextAttribute(handle, 12);
		cout << "\t\t\t\t\t" << "---------------------------------" << endl;
		SetConsoleTextAttribute(handle, 8);
		cout << "\t\t\t\t\t";

		char pyt;
		cin >> pyt;

		while (pyt != '1' && pyt != '2')
		{
			plansza->Clear();

			cout << "\n\n\n\n\n\n" << endl;
			SetConsoleTextAttribute(handle, 15);
			cout << "\t\t\t\t\t\t--- < Quoridor > ---" << endl;
			SetConsoleTextAttribute(handle, 12);
			cout << "\t\t\t\t\t" << "---------------------------------" << endl;
			SetConsoleTextAttribute(handle, 8);
			cout << "\t\t\t\t\t" << "|\t" "1. Nowa gra" "\t\t|" << endl;
			SetConsoleTextAttribute(handle, 12);
			cout << "\t\t\t\t\t" << "---------------------------------" << endl;
			SetConsoleTextAttribute(handle, 8);
			cout << "\t\t\t\t\t" << "|\t" << "2. Kontynuuj gre" << "\t|" << endl;
			SetConsoleTextAttribute(handle, 12);
			cout << "\t\t\t\t\t" << "---------------------------------" << endl;
			SetConsoleTextAttribute(handle, 8);
			cout << "\t\t\t\t\t";

			cin.clear();
			cin >> pyt;
		}

		if (pyt == '1')
		{
			plansza->Reset();
			plansza->Clear();
			DownloadParam = false;
		}
		else
		{
			plansza->Clear();
			DownloadParam = true;
		}

	}
}

int menu::Start()
{

	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "\n\n\n\n\n\n" << endl;
	SetConsoleTextAttribute(handle, 15);
	cout << "\t\t\t\t\t\t--- < Quoridor > ---" << endl;
	SetConsoleTextAttribute(handle, 12);
	cout << "\t\t\t\t\t" << "----------------------------------" << endl;
	SetConsoleTextAttribute(handle, 8);
	cout << "\t\t\t\t\t" << "|    \t" << "1. Tryb OnePlayer" << "\t |" << endl;
	SetConsoleTextAttribute(handle, 12);
	cout << "\t\t\t\t\t" << "----------------------------------" << endl;
	SetConsoleTextAttribute(handle, 8);
	cout << "\t\t\t\t\t" << "|    \t" << "2. Tryb MultiPlayer" << "\t |" << endl;
	SetConsoleTextAttribute(handle, 12);
	cout << "\t\t\t\t\t" << "----------------------------------" << endl;
	SetConsoleTextAttribute(handle, 8);
	cout << "\t\t\t\t\t";

	char tryb;
	cin >> tryb;

	while (tryb != '1' && tryb != '2')
	{
		plansza->Clear();

		cout << "\n\n\n\n\n\n" << endl;
		SetConsoleTextAttribute(handle, 15);
		cout << "\t\t\t\t\t\t--- < Quoridor > ---" << endl;
		SetConsoleTextAttribute(handle, 12);
		cout << "\t\t\t\t\t" << "----------------------------------" << endl;
		SetConsoleTextAttribute(handle, 8);
		cout << "\t\t\t\t\t" << "|    \t" << "1. Tryb OnePlayer" << "\t |" << endl;
		SetConsoleTextAttribute(handle, 12);
		cout << "\t\t\t\t\t" << "----------------------------------" << endl;
		SetConsoleTextAttribute(handle, 8);
		cout << "\t\t\t\t\t" << "|    \t" << "2. Tryb MultiPlayer" << "\t |" << endl;
		SetConsoleTextAttribute(handle, 12);
		cout << "\t\t\t\t\t" << "----------------------------------" << endl;
		SetConsoleTextAttribute(handle, 8);
		cout << "\t\t\t\t\t";

		cin.clear();
		cin >> tryb;
	}

	int nr = (int)tryb - 48;

	return nr;
}

menu::~menu()
{
	delete plansza;
}