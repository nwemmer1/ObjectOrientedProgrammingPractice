#include <iostream>
#include <cassert> // assert
#include <algorithm> // testing use of an algorithm
#include <ctime>//time
#include <cstdlib>//sudo rand
#include "deck-of-cards.hpp"


using std::cout;
using std::endl;


int main()
{

Deck theDeck{
    SCard(Ace, Spades),
    SCard(Two, Spades),
    SCard(Three, Spades),
    SCard(Four, Spades),
    SCard(Five, Spades),
    SCard(Six, Spades),
    SCard(Seven, Spades),
    SCard(Eight, Spades),
    SCard(Nine, Spades),
    SCard(Ten, Spades),
    SCard(Jack, Spades),
    SCard(Queen, Spades),
    SCard(King, Spades),

    SCard(Ace, Clubs),
    SCard(Two, Clubs),
    SCard(Three, Clubs),
    SCard(Four, Clubs),
    SCard(Five, Clubs),
    SCard(Six, Clubs),
    SCard(Seven, Clubs),
    SCard(Eight, Clubs),
    SCard(Nine, Clubs),
    SCard(Ten, Clubs),
    SCard(Jack, Clubs),
    SCard(Queen, Clubs),
    SCard(King, Clubs),

    SCard(Ace, Diamonds),
    SCard(Two, Diamonds),
    SCard(Three, Diamonds),
    SCard(Four, Diamonds),
    SCard(Five, Diamonds),
    SCard(Six, Diamonds),
    SCard(Seven, Diamonds),
    SCard(Eight, Diamonds),
    SCard(Nine, Diamonds),
    SCard(Ten, Diamonds),
    SCard(Jack, Diamonds),
    SCard(Queen, Diamonds),
    SCard(King, Diamonds),

    SCard(Ace, Hearts),
    SCard(Two, Hearts),
    SCard(Three, Hearts),
    SCard(Four, Hearts),
    SCard(Five, Hearts),
    SCard(Six, Hearts),
    SCard(Seven, Hearts),
    SCard(Eight, Hearts),
    SCard(Nine, Hearts),
    SCard(Ten, Hearts),
    SCard(Jack, Hearts),
    SCard(Queen, Hearts),
    SCard(King, Hearts),

    Joker(Black),
    Joker(Red),
  };
    cout << theDeck << '\n';
    return 0;

}
