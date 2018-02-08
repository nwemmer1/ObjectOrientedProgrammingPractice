
#include "card.hpp"

#include <iostream>

//things in the class
//  -cards(values between 1 and 13, suits)
//  -deck
//  -players (hands?)
//  -sacrifice pile
//      -compare cards
//      -equal.. redo and flip over another 2
//      -winner gets all cards

int
main()
{
    std::cout << "The game of war";
    std::cout << "hello world\n";

    Rank r1 = King;
    Rank r2 = Queen;

    std::cout << (r1 == r2) << '\n';
    std::cout << (r1 < r2) << '\n';
//below this are notes for me

    //narrowing conversion
    //rank r3 = 4; You cant convert int to rank
    //invalid type conversion

    //Doesn't work. not in range
    //Rank r4 = -1;

    //We can cast int to rank
    //potential error, obliged to verify that
    //Ace <= n0 && n0 <= King
    int n0;
    Rank r5 = static_cast<Rank>(n0);

    //This is a widening conversion and guaranteed
    //top work (most likely).

    int n = King;

}

