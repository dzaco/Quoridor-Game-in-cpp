// Quoridor.cpp : Jacek Giedronowicz
#include "stdafx.h"
#include "menu.h"


int main()
{		
	menu Menu;
	int nr = Menu.Start();
	bool par = Menu.get_DownloadParam();

	gra Game( nr , par );
	


	Game.Play();
	
	



	cout << endl;
    return 0;
}

