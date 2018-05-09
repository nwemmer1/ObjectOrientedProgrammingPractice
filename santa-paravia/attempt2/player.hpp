#pragma once
#include <string>
#include "cityInfo.hpp"
#include "labels.hpp"
using std::string;
class Player
{
public:
    int Cathedral, Clergy, CustomsDuty, CustomsDutyRevenue, DeadSerfs;			//These
    int Difficulty, FleeingSerfs, GrainDemand, GrainPrice, GrainReserve;		//might
    int Harvest, IncomeTax, IncomeTaxRevenue, RatsAte;					//all
    int Justice, JusticeRevenue, Land, Marketplaces, MarketRevenue;			//be
    int Merchants, MillRevenue, Mills, NewSerfs, Nobles, OldTitle, Palace;		//temporary,
    int Rats, SalesTax, SalesTaxRevenue, Serfs, SoldierPay, Soldiers, TitleNum;		//not
    int TransplantedSerfs, Treasury, WhichPlayer, Year, YearOfDeath;			//sure
    char City[15], Name[25], Title[15];							//yet.
    float PublicWorks, LandPrice;							//Still evaluating my options and how i should go about it.
    bool InvadeMe, IsBankrupt, IsDead, IWon, MaleOrFemale, NewTitle;
	string name;
	Label label;
	Player::Player(string inputN, Label inputL) : name(inputN), label(inputL) {}
private:
};
//maybe this? was fulling around
Player::Player(player *Me, int year, int city, int level, char *name, bool gender)
{
//default constructor? maybe not sure if i got this right yet, haven't researched it enough to know for certain
    Cathedral = 0;
    strcpy(City, CityList[city]);
    Clergy = 5;
    CustomsDuty = 25;
    Difficulty = level;
    GrainPrice = 25;
    GrainReserve = 5000;
    IncomeTax = 5;
    IsBankrupt = 0;
    IsDead = 0;
    IWon = 0;
    Justice = 2;
    Land = 10000;
    LandPrice = 10.0;
    MaleOrFemale = gender;
    Marketplaces = 0;
    Merchants = 25;
    Mills = 0;
    strcpy(Name, name);
    Nobles = 4;
    OldTitle = 1;
    Palace = 0;
    PublicWorks = 1.0;
    SalesTax = 10;
    Serfs = 2000;
    Soldiers = 25;
    TitleNum = 1;
    if(MaleOrFemale == 1)
        strcpy(Title, MaleTitles[0]);
    else
        strcpy(Me->Title, FemaleTitles[0]);
    if(city == 6)
        strcpy(Me->Title, "Baron");
    Treasury = 1000;
    WhichPlayer = city;
    Year = year;
    YearOfDeath = year + 20 + Random(35);


}