#include "stdafx.h"
#pragma once

#ifndef FREECELL_H
#define FREECELL_H

#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>
#include <thread>
#include "Gameboard.h"
using namespace std;

class Freecell
{
public:
	Freecell();
	~Freecell();
public:
	Freecell(const Freecell & originalToCopy);
	Freecell & operator=(const Freecell & inRhs);
public:
	void startGame();
	void userActionsList();

private:
	Gameboard m_gameboard;
	bool m_validGame;
};

inline Freecell::Freecell()
{
	m_validGame = true;
}

inline Freecell::~Freecell()
{
	m_validGame = false;
}

inline Freecell::Freecell(const Freecell & originalToCopy)
{
	*this = originalToCopy;
}

inline Freecell & Freecell::operator=(const Freecell & inRhs)
{
	if (this != &inRhs) {
		m_gameboard = inRhs.m_gameboard;
		m_validGame = inRhs. m_validGame;
	}
	return *this;
}

inline void Freecell::startGame()
{
	m_gameboard.displayGameboard();
	userActionsList();
}

inline void Freecell::userActionsList()
{
	while (m_validGame == true)
	{
		int userOriginCol = 0;
		int userDestCol = 0;
		char userOps;

		cout << endl << endl << endl;
		cout << "[1] Move Play to Play." << endl;
		cout << "[2] Move Play to Free." << endl;
		cout << "[3] Move Play to Home." << endl;
		cout << "[4] Move Free to Home." << endl;
		cout << "[5] Move Free to Play." << endl;
		cout << "[r] Reset game." << endl;
		cout << "[x] Exit." << endl;
		cout << ":: Operator: ";
		cin >> userOps;

switch (userOps) {
		case '1':
			cout << ":: Choose Playcard origin column: ";
			cin >> userOriginCol;
			cout << ":: Choose Playcard destination column: ";
			cin >> userDestCol;
			try {
				m_gameboard.MakeMovePlayToPlay(userOriginCol - 1, userDestCol - 1);
			}
			catch (Exception e) {
				cout << "[!]  " << e.getMessage();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
			m_gameboard.displayGameboard();
			break;
		case '2':
			cout << ":: Choose Playcard origin column: ";
			cin >> userOriginCol;
			cout << ":: Choose Freecell destination column: ";
			cin >> userDestCol;
			try {
				m_gameboard.MakeMovePlayToFree(userOriginCol - 1, userDestCol - 1);
			}
			catch (Exception e) {
				cout << "[!]  " << e.getMessage();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
			m_gameboard.displayGameboard();
			break;
		case '3':
			cout << ":: Choose Playcard origin column: ";
			cin >> userOriginCol;
			cout << ":: Choose Home destination column: ";
			cin >> userDestCol;
			try {
				m_gameboard.MakeMovePlayToHome(userOriginCol - 1, userDestCol - 1);
			}
			catch (Exception e) {
				cout << "[!]  " << e.getMessage();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
			m_gameboard.displayGameboard();
			break;
		case '4':
			cout << ":: Choose Freecell origin column: ";
			cin >> userOriginCol;
			cout << ":: Choose Home destination column: ";
			cin >> userDestCol;
			try {
				m_gameboard.MakeMoveFreeToHome(userOriginCol - 1, userDestCol - 1);
			}
			catch (Exception e) {
				cout << "[!]  " << e.getMessage();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
			m_gameboard.displayGameboard();
			break;
		case '5':
			cout << ":: Choose Freecell origin column: ";
			cin >> userOriginCol;
			cout << ":: Choose Playcard destination column: ";
			cin >> userDestCol;
			try {
				m_gameboard.MakeMoveFreeToPlay(userOriginCol - 1, userDestCol - 1);
			}
			catch (Exception e) {
				cout << "[!]  " << e.getMessage();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
			m_gameboard.displayGameboard();
			break;
		case 'r':
			m_gameboard.initializeBoard();
			break;
		case 'x':
			exit(EXIT_SUCCESS);
			break;
		}
	}
}

#endif 
