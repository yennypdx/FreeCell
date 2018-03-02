#include "stdafx.h"
#pragma once

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "Exception.h"
using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int RED = 12;
const int YELLOW = 14;
const int GREY = 31;
const int BLACK = 7;

const int NUM_RANK = 13;
const int NUM_SUIT = 4;

enum Rank{ ACE = 1, TWO, THREE, FOUR, 
	FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, JOKER };
enum Suit { HEART = 1, CLUB, DIAMOND, SPADE, FLOWER };

class Card
{
public:
	Card();
	Card(Rank inRank, Suit inSuit);
	~Card();
public:
	Card & operator=(const Card & inRhs);
	bool operator!=(Card & inRhs);
public:
	void setRank(Rank inRank);
	void setSuit(Suit inSuit);
	Rank getRank() { return m_rank; }
	Suit getSuit() { return m_suit; }
public:
	string rankToString();
	string suitToString();
	void displayCard();

private:
	Rank m_rank;
	Suit m_suit;
};

inline Card::Card()
{
	m_rank = JOKER;
	m_suit = FLOWER;
}

inline Card::Card(Rank inRank, Suit inSuit)
{
	setRank(inRank);
	setSuit(inSuit);
}

inline Card::~Card() {}

inline Card & Card::operator=(const Card &inRhs)
{
	if (this != &inRhs) {
		m_rank = inRhs.m_rank;
		m_suit = inRhs.m_suit;
	}
	return *this;
}

inline bool Card::operator!=(Card & inRhs)
{
	bool outResult = false;
	if (m_rank != inRhs.m_rank || m_suit != inRhs.m_suit) {
		outResult = true;
	}
	return outResult;
}

inline void Card::setRank(Rank inRank)
{
	m_rank = inRank;
}

inline void Card::setSuit(Suit inSuit)
{
	m_suit = inSuit;
}

inline string Card::rankToString()
{
	string assignRank;

	if (m_rank == KING) {
		assignRank = "K";
	}
	else if (m_rank == QUEEN) {
		assignRank = "Q";
	}
	else if (m_rank == JACK) {
		assignRank = "J";
	}
	else if (m_rank == TEN) {
		assignRank = "10";
	}
	else if (m_rank == ACE) {
		assignRank = "1";
	}
	else {
		assignRank = char(m_rank + 48);
	}
	return assignRank;
}

inline string Card::suitToString()
{
	string assignSuit;

	if (m_suit == HEART) {
		assignSuit = "H";
	}
	else if (m_suit == CLUB) {
		assignSuit = "C";
	}
	else if (m_suit == DIAMOND) {
		assignSuit = "D";
	}
	else if (m_suit == SPADE) {
		assignSuit = "S";
	}
	else {
		assignSuit = "F";
	}
	return assignSuit;
}

inline void Card::displayCard()
{
	string outRank = rankToString();
	string outSuit = suitToString();

	//for RED cards
	if (m_suit == HEART || m_suit == DIAMOND) {
		SetConsoleTextAttribute(handle, RED);
		cout << setw(2) << outRank << "|" << outSuit;
		SetConsoleTextAttribute(handle, BLACK);
	}
	else if (m_suit == CLUB || m_suit == SPADE) {
		SetConsoleTextAttribute(handle, YELLOW);
		cout << setw(2) << outRank << "|" << outSuit;
		SetConsoleTextAttribute(handle, BLACK);
	}
	else {
		SetConsoleTextAttribute(handle, GREY);
		cout << "  X  ";
		SetConsoleTextAttribute(handle, BLACK);
	}
}

#endif