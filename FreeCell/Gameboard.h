#include "stdafx.h"
#pragma once

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cmath>
#include <string>
#include "Exception.h"
#include "Stack.h"
#include "StackLL.h"
#include "Deck.h"
using namespace std;

const int NUM_FREECELLS = 4;
const int NUM_HOMECELLS = 4;
const int NUM_PLAYCARDCELLS = 8;

class Gameboard
{
public:
	Gameboard();
	~Gameboard();
	Gameboard(const Gameboard & originalToCopy);
	Gameboard & operator=(const Gameboard & inRhs);
public:
	void initializeBoard();
	void displayGameboard();
	void displayWhenEmpty();
	bool checkWin();
public:
	void MakeMovePlayToPlay(int originCol, int destCol);
	void MakeMovePlayToFree(int originCol, int destCol);
	void MakeMovePlayToHome(int originCol, int destCol);
	void MakeMoveFreeToPlay(int originCol, int destCol);
	void MakeMoveFreeToHome(int originCol, int destCol);

private:
	bool m_freeIsEmpty[NUM_FREECELLS];
	Array<Card> m_freeCell;
	Array<Stack<Card>> m_homeCell;
	Array<StackLL<Card>> m_playCell;		
};

inline Gameboard::Gameboard()
{
	initializeBoard();
	//set default to empty
	for (int i = 0; i < NUM_FREECELLS; i++) {
		m_freeIsEmpty[i] = true;
	}
}

inline Gameboard::~Gameboard()
{
	m_freeCell.setLength(0);
	m_homeCell.setLength(0);
	m_playCell.setLength(0);
	//set the cells in freecell to empty
	for (int i = 0; i < NUM_FREECELLS; i++) {
		m_freeIsEmpty[i] = true;
	}
}

inline Gameboard::Gameboard(const Gameboard & originalToCopy)
{
	m_freeCell = originalToCopy.m_freeCell;
	m_homeCell = originalToCopy.m_homeCell;
	m_playCell = originalToCopy.m_playCell;
}

inline Gameboard & Gameboard::operator=(const Gameboard & inRhs)
{
	if (! &inRhs) {
		m_freeCell = inRhs.m_freeCell;
		m_homeCell = inRhs.m_homeCell;
		m_playCell = inRhs.m_playCell;
	}
	return *this;
}

inline void Gameboard::initializeBoard()
{
	m_freeCell = Array<Card>(NUM_FREECELLS);
	m_homeCell = Array<Stack<Card>>(NUM_HOMECELLS);
	m_playCell = Array<StackLL<Card>>(NUM_PLAYCARDCELLS);
	
	//Creating a stack of 13 cards
	for (int hom = 0; hom < NUM_HOMECELLS; hom++)	{
		m_homeCell[hom] = Stack<Card>(NUM_RANK);
	}

	//Create deck and shuffle
	Deck tempDeck;
	tempDeck.Shuffle();

	//Populating Playcards Cells
	for (int dec = 0; dec < NUM_CARDS_ONDECK;)	{
		for (int pla = 0; pla < NUM_PLAYCARDCELLS && dec < NUM_CARDS_ONDECK; pla++)		{
			m_playCell[pla].Push(tempDeck.Deal());
			dec++;	
		}
	}
}

inline void Gameboard::displayGameboard()
{
	system("cls");
	cout << "\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	cout << "\t\t FreeCell Game ASCII style!!" << endl;
	cout << "\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl << endl;

	cout << "      Free Cells	            Home Cells" << endl;
	/*-----------------Free Indexes Display-------------------*/
	for (int fre = 1; fre <= NUM_FREECELLS; fre++) {
		cout << "   " << fre << "  ";
	}
	cout << "     ";
	/*----------------Home Indexes Display-------------------*/
	for (int hom = 1; hom <= NUM_HOMECELLS; hom++) {
		cout << "   " << hom << "  ";
	}

	/*---------------Free Cell CARD Display------------------*/
	cout << endl;
	for (int fre = 0; fre < NUM_FREECELLS; fre++) {
		if (m_freeCell[fre].getRank() != JOKER) {	//Cell is not empty
			cout << " ";
			m_freeCell[fre].displayCard();
		}
		else { //Cell is empty
			cout << " ";
			displayWhenEmpty();
		}
	}
	cout << "     "; //10sp

	 /*------------------Home Cell Display-----------------*/
	for (int hom = 0; hom < NUM_HOMECELLS; hom++) {
		if (m_homeCell[hom].Peek().getRank() == JOKER) {
			cout << " ";
			displayWhenEmpty();
		}
		else {
			cout << " ";
			m_homeCell[hom].Peek().displayCard();
			cout << " ";
		}
	}
	cout << "\n\n"; //2lines down


	/*----------------Play Index Display-------------------*/
	cout << endl;
	cout << "                  Play Card\n";
	for (int pla = 1; pla < NUM_PLAYCARDCELLS+1; pla++) {
		cout << "   " << pla << "  ";
	}
		
	/*--------------Playcard Cells Display---------------*/
	//Displaying cards onto PlayCard Cells
	cout << endl;
	for (int pla = 0; pla < NUM_PLAYCARDCELLS; pla++) {
		if (m_playCell[pla].isEmpty()) {
			cout << " ";
			displayWhenEmpty();
		}
		else {
			cout << " ";
			m_playCell[pla].Peek().displayCard();
			cout << " ";
		}
	}
}

inline void Gameboard::displayWhenEmpty()
{
	SetConsoleTextAttribute(handle, GREY);
	cout << "  X  ";
	SetConsoleTextAttribute(handle, BLACK);
}

inline bool Gameboard::checkWin()
{
	bool winning = false;
	int numCompletedHomeCell = 0;	

	for (int hom = 0; hom < NUM_HOMECELLS; hom++)	{
		if (m_homeCell[hom].isFull()) {
			numCompletedHomeCell++;
			}
	}

	if (numCompletedHomeCell == NUM_HOMECELLS) {
		winning = true;
	}
	return winning;
}

inline void Gameboard::MakeMovePlayToPlay(int originCol, int destCol)
{
	StackLL<Card> fromCard;		
	
	if (m_playCell[originCol].Peek().getRank() != JOKER) {	//moving from non-empty stack
		fromCard.Push(m_playCell[originCol].Pop());

		if (m_playCell[destCol].Peek().getRank() != JOKER) {	//moving to a NON-empty cell 
			if (m_playCell[destCol].Peek().getRank() - fromCard.Peek().getRank() == 1) {	//if rank is inorder
				if (fromCard.Peek().getSuit() + 1 == m_playCell[destCol].Peek().getSuit() ||
					fromCard.Peek().getSuit() - 1 == m_playCell[destCol].Peek().getSuit() ||
					fromCard.Peek().getSuit() + 3 == m_playCell[destCol].Peek().getSuit() ||
					fromCard.Peek().getSuit() - 3 == m_playCell[destCol].Peek().getSuit())	//If suit colors are opposite
				{

					m_playCell[destCol].Push(fromCard.Pop());
					m_playCell[originCol].Pop();
				}
				else {
					m_playCell[originCol].Push(fromCard.Pop());
					throw Exception("Invalid Move: Wrong color combination. Try again.");
				}
			}
			else {
				m_playCell[originCol].Push(fromCard.Pop());
				throw Exception("Invalid Move: Rank is not inorder. Try again.");
			}
		}
		else if (m_playCell[destCol].Peek().getRank() == JOKER) {	//moving a card to an empty cell 
			fromCard.Push(m_playCell[originCol].Pop());
			m_playCell[destCol].Push(fromCard.Pop());
		}
	}
	else {
		throw Exception("Invalid Move: Origin stack is empty. Try again.");
	}
}

inline void Gameboard::MakeMovePlayToFree(int originCol, int destCol)
{
	if (m_playCell[originCol].Peek().getRank() != JOKER) { 
		if (m_freeCell[destCol].getRank() == JOKER) {	//if destination is empty
			m_freeCell[destCol] = m_playCell[originCol].Pop();
			m_freeIsEmpty[destCol] = false;
		}
		else {
			throw Exception("Invalid Move: Cell is not available. Try again.");
		}
	}
	else {
		throw Exception("Invalid Move: Origin stack is empty. Try again.");
	}
}

inline void Gameboard::MakeMovePlayToHome(int originCol, int destCol)
{
	//If not moving from an empty play area column
	if (m_playCell[originCol].Peek().getRank() != JOKER)	{ //if origin in avail
		if (m_homeCell[destCol].Peek().getRank() == JOKER) { //if dest is empty
			if (m_playCell[originCol].Peek().getRank() == ACE) {	
				m_homeCell[destCol].Push(m_playCell[originCol].Pop());
			}
			else {
				throw Exception("Invalid move: First card rank must be 1 (ACE). Try again.");
			}
		}
		else {	//if dest already have card(s)
			if (m_playCell[originCol].Peek().getRank() - m_homeCell[destCol].Peek().getRank() == 1) {
				if (m_playCell[originCol].Peek().getSuit() == m_homeCell[destCol].Peek().getSuit()) {
					m_homeCell[destCol].Push(m_playCell[originCol].Pop());
				}
				else
					throw Exception("Invalid move: Wrong color combination. Try again.");
			}
			else {
				throw Exception("Invalid move: Rank is not inorder. Try again.");
			}
		}
	}
	else {
		throw Exception("Invalid Move: Stack is empty. Try again.");
	}
}

inline void Gameboard::MakeMoveFreeToPlay(int originCol, int destCol)
{
	if (m_freeCell[originCol].getRank() != JOKER) {
		if (m_playCell[destCol].Peek().getRank() == JOKER) {	//if destination is empty stack
			m_playCell[destCol].Push(m_freeCell[originCol]);
			m_freeCell[originCol].setRank(JOKER);
			m_freeCell[originCol].setSuit(FLOWER);
		}
		else	{ 
			if (m_playCell[destCol].Peek().getRank() - m_freeCell[originCol].getRank() == 1)	{ //if rank inorder
				if (m_freeCell[originCol].getSuit() + 1 == m_playCell[destCol].Peek().getSuit() ||
					m_freeCell[originCol].getSuit()  - 1 == m_playCell[destCol].Peek().getSuit() ||
					m_freeCell[originCol].getSuit()  + 3 == m_playCell[destCol].Peek().getSuit() ||
					m_freeCell[originCol].getSuit() - 3 == m_playCell[destCol].Peek().getSuit())	//if suits opposite
				{
					m_playCell[destCol].Push(m_freeCell[originCol]);
					m_freeCell[originCol].setRank(JOKER);
					m_freeCell[originCol].setSuit(FLOWER);
				}
				else {
					throw Exception("Invalid move: Wrong combination. Try again.");
				}
			}
			else {
				throw Exception("Invalid move: Rank is not inorder. Try again.");
			}
		}
	}
	else {
		throw Exception("Invalid Move: No card to move. Try again.");
	}
}

inline void Gameboard::MakeMoveFreeToHome(int originCol, int destCol)
{
	if (m_freeCell[originCol].getRank() != JOKER)	{
		if (m_homeCell[destCol].Peek().getRank() == JOKER) {
			if (m_freeCell[originCol].getRank() == ACE) {
				m_homeCell[destCol].Push(m_freeCell[originCol]);
				m_freeCell[originCol].setRank(JOKER);
				m_freeCell[originCol].setSuit(FLOWER);
			}
			else {
				throw Exception("Invalid move: First card rank must be 1 (ACE). Try again.");
			}
		}
		else { //if homecell (dest) already has card
			if (m_freeCell[originCol].getRank() - m_homeCell[destCol].Peek().getRank() == 1) {
				if (m_freeCell[originCol].getSuit() == m_homeCell[destCol].Peek().getSuit())	{
					m_homeCell[destCol].Push(m_freeCell[originCol]);
					m_freeCell[originCol].setRank(JOKER);
					m_freeCell[originCol].setSuit(FLOWER);
				}
				else {
					throw Exception("Invalid move : Wrong color combination. Try again.");
				}
			}
			else {
				throw Exception("Invalid move : Rank is not inorder. Try again.");
			}
		}
	}
	else {
		throw Exception("Invalid Move : No card to move. Try again.");
	}
}

#endif