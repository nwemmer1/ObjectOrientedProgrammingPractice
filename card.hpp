#ifndef CARD_HPP_INCLUDED
#define CARD_HPP_INCLUDED

#pragma once

//Rank and suit for the card class
//use enum like we did in class
//These are the ranks
enum Rank {
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
    King
};
//These are the suits , starting at 0
enum Suit {
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

//This is the card class

class Card {
Card(Rank r, Suit s)    //Default constructor
    : rank(r), suit(s) {}

~Card() {} // destructor


};


#endif // CARD_HPP_INCLUDED
