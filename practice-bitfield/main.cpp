#include <iostream>
#include <cassert> // assert
#include <algorithm> // testing use of an algorithm
#include <ctime>//time
#include <cstdlib>//sudo rand

#include "bitfield.hpp"

using std::cout;
using std::endl;


int main()
{
    //default card created here
    Card cardD;
    //random card generator that i found online (template)
    std::srand(std::time(NULL));
    int ranS = std::rand() % 4;
    int ranR = std::rand() % 13;
    Suit s=(Suit)ranS;
    Rank r=(Rank)ranR;

    Card card1 {r,s};//norm const
    Card card2=card1;//copy const

    assert(card1.getRank() == r);
    assert(card1.getSuit() == s);
    assert(card2 == card1);

    card2 = cardD;

    assert(card2 !=card1);
    // making sure this works

    card1 = {Rank::Ace, Suit::Spades};
    card2 = {Rank::Queen, Suit::Clubs};

    //making sure these work
    assert(card2 > card1);
    assert(card1 < card2);
    assert(card1 <= card2);
    assert(card2 >= card1);

    card2 = card1;
    card2 = cardD;

    assert(card1 <= card2);
    assert(card1 >= card2);

    //these should be the same
    cout << "Card 1's bitfield:" << card1 << endl;
    cout << "Card 2's bitfield:" << card2 << endl;

    return 0;

}
