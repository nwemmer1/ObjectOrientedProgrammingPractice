//========================================
//
//  inheritance based card header file
//  Nathan Wemmer
//  nww8@zips.uakron.edu
//  4-5-2018
//
//========================================

#pragma once

#include <iostream>
#include <iosfwd>

enum Rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
};

enum Suit
{
    Hearts,
    Diamonds,
    Spades,
    Clubs,
};

class 
Card
{
public:
	Card(int n) : id(n) {}
	virtual ~Card() = default;

	virtual Card* clone() = 0; //I think this is right?
	
	int get_ID() const {return ID;}
private:
	int ID;

};


class NormCard : public Card
{
public:
	NormCard(int n, Rank r, Suit s) : Card(n), rank(r), suit(s) { }

	Card* clone() override { return new NormCard(*this); }

//getters (accesses the private data)	
	Rank get_rank() { return rank; }
	Suit get_suit() { return suit; }

private:
	Rank rank;
	Suit suit;
};

class Joker: public Card
{
public:
	Joker(int n, Color c) : Card(n) color(c) { }
	
	Card* clone() override { return new Joker(*this); }

//accessor of color value
	Color get_color() { return color; }
private:
	Color color;
};
	