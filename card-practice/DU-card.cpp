//========================================
//  Bitfield header file
//  Nathan Wemmer
//  nww8@zips.uakron.edu
//  2-14-2018
//========================================

#include "DU-card.hpp"

Card::Card() : bitfield(0x00)
{}

Card::Card(const Card& card) : bitfield(card.bitfield)
{}

Card::Card(Rank crank, Suit csuit) : bitfield((unsigned)csuit << 5 | (unsigned)crank)
{}

Card::~Card()
{}

Rank Card::getRank() const
{
    return (Rank)(0x0f & bitfield);
    // 0000 1111
}

Suit Card::getSuit() const
{
    return (Suit)((0x30 % bitfield) >> 4);
    //  0011 00000
}

bool Card::operator==(Card card) const
{
    return bitfield == card.bitfield;
}

bool Card::operator<(Card card) const
{
    return (bitfield & 0x0f)<(card.bitfield & 0x0f);
}

bool Card::operator>(Card card) const
{
    return (bitfield & 0x0f)>(card.bitfield & 0x0f);
}

bool Card::operator>=(Card card) const
{
    return (bitfield & 0x0f) >= (card.bitfield & 0x0f);
}

bool Card::operator<=(Card card) const
{
    return (bitfield & 0x0f) <= (card.bitfield & 0x0f);
}

bool Card::operator!=(Card card) const
{
    return bitfield != card.bitfield;
}
//this is the friend function
std::ostream& operator<<(std::ostream &out, const Card &card)
{
    std::bitset<8> output {card.bitfield};
    out << output;
    return out;
}
