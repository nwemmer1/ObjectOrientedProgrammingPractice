//========================================
//
//  Bitfield header file
//  Nathan Wemmer
//  nww8@zips.uakron.edu
//  2-14-2018
//
//========================================

#pragma once

#include <iostream>
#include <bitset>
#include <ctime>
#include <cassert>

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

enum Color
{
	Black,
	Red,
};

class SCard {
public:
	SCard() = default;
	SCard(Rank r, Suit s) : rank(r), suit(s) { }

	Rank get_rank() { return rank; }
	Suit get_suit() { return suit; }
private:
	Rank rank;
	Suit suit;

class Joker
{
public:
	Joker(Color c) : color(c) {}

	Color get_color() { return color; }
	
	Color color;
};


class Card
{
private:
union value {
	value(SCard c) : s(c) { }
	value(Joker j) : j(c) { }
	
	SCard s;
	Joker j;

public:
	enum type{
		Standard,
		Joker,
		};
	Card(SCard s) : type(Standard), std(s) { }
	bool isStandard() { return type == Standard;}
	Card(Joker j) : type(Joker), std(j) { }
	bool isJoker() {return type == Joker;}

Card* clone() {
	if (isStandard())
		return new Card(std.s);
	else
		return new Card(std.j);
}

SCard getSCard()
{
	assert(isStandard());
	return std.s;
}

Joker getJoker()
{
	assert(isJoker());
	return std.j;
}

Suit get_suit() { return getSCard().get_suit(); }

Rank get_rank() { return getSCard().get_rank(); }

Color get_color() { return getJoker().get_color(); }



 
};
