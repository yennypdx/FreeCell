#include "stdafx.h"
#pragma once

#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <cstdlib>
#include  "Card.h"
using namespace std;

const int NUM_CARDS_ONDECK = 52;

class Deck
{
public:
	Deck();
	~Deck();
public:
	Deck(const Deck & originalToCopy);
	Deck & operator=(const Deck & inRhs);
public:
	void Shuffle();
	Card Deal();
	Card GetTopCard();

private:
	int m_topOfDeck = 0;
	Array<Card> m_deck;
};

Deck::Deck()
{
	//building deck
	m_topOfDeck = 0;
	int counter = 0;
	m_deck = Array<Card>(NUM_CARDS_ONDECK);

	for (int r = 1; r <= NUM_RANK; r++) {
		for (int s = 1; s <= NUM_SUIT; s++) {
			m_deck[counter].setRank(static_cast<Rank>(r));
			m_deck[counter].setSuit(static_cast<Suit>(s));
			counter++;
		}
	}
}

inline Deck::~Deck()
{
	m_topOfDeck = 0;
}

inline Deck::Deck(const Deck & originalToCopy)
{
	*this = originalToCopy;
}

inline Deck & Deck::operator=(const Deck & inRhs)
{
	if (this != &inRhs) {
		m_topOfDeck = inRhs.m_topOfDeck;
		m_deck = inRhs.m_deck;
	}
	return *this;
}

void Deck::Shuffle()
{
	srand((unsigned int)time(NULL));
	int numOfSwap = 100;

	for (int i = 0; i < numOfSwap; i++) {
		int cardOne = rand() % NUM_CARDS_ONDECK;
		int cardTwo = rand() % NUM_CARDS_ONDECK;
		swap(m_deck[cardOne], m_deck[cardTwo]);
	}
}

Card Deck::GetTopCard()
{
	return m_deck[m_topOfDeck];
}

Card Deck::Deal()
{
	return m_deck[m_topOfDeck++];
}

#endif