#include "stdafx.h"
#pragma once

#include <iostream>
#include "Freecell.h"
using namespace std;

int main()
{
	Freecell game;
	char reset;

	do {
		game.startGame();

		cout << "Play again [y/n]? ";
		cin >> reset;
	} while (reset == 'y' || reset == 'Y');

	system("pause");
	return 0;
}