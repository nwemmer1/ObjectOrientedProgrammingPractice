//========================================
//
//  my attempt at the deck of cards (header file)
//  Nathan Wemmer
//  nww8@zips.uakron.edu
//  4-5-2018
//
//========================================

#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>

using std::vector;
using std::initializer_list;
using std::ostream;
#include "DU-card.hpp"

class 
CardDeck : public vector<Card*>
{
public:
//defualt initializer list
	CardDeck(initializer_list<Card*> list) : vector<Card*>(list) { }
//im actually completely lost here im not really sure what to do		
//same idea as the destructor i think 
	CardDeck(const CardDeck& deck)
	{ 
		for (Card* card : deck)	
		{
			push_back(card->clone());
		}
	}
//i think this is right
	~CardDeck() 
	{
		for(Card* card : *this)
			delete card;
	}
};

ostream& operator<<(ostream& out, Card card)
{
	if (card.isStandard())
		return out << card.get_rank() << card.get_suit;
	else
		return out << card.get_color();
}

ostream& operator<<(ostream& out, const Deck& deck)
{
	for(int i=0; i < deck.size(); ++i)
	{
		if (deck[i]->isStandard()) {
			out << deck[i]->get_rank() << '\t' << deck[i]->get_suit() << '\n';
		}
	
	else if (deck[i]->isJoker()){
		out << deck[i]->get_color() << '\n';
}
}
return out;
}