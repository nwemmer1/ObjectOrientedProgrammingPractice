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

class Card
{
private:
    unsigned char bitfield;

public:
    //constructors/destructor
    Card();//default const
    Card(const Card&);//copy const
    Card(Rank,Suit);

    ~Card();
    //friending the << operator to use bitfields
    friend std::ostream&operator<< (std::ostream &out, const Card&);
    //getter and setters
    Rank getRank() const;
    Suit getSuit() const;
    //overloading
    bool operator==(Card) const;
    bool operator<(Card) const;
    bool operator>(Card) const;
    bool operator>=(Card) const;
    bool operator<=(Card) const;
    bool operator!=(Card) const;

};
