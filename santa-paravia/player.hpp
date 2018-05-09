#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

/* Declare our list of cities. */
std::string CityList[7] = {"Santa Paravia", "Fiumaccio", "Torricella", "Molinetto",
"Fontanile", "Romanga", "Monterana"};
/* Declare our male titles. */
std::string MaleTitles[8] = {"Sir", "Baron", "Count", "Marquis", "Duke",
 "Grand Duke", "Prince", "* H.R.H. King"};
/* Declare our female titles. */
std::string FemaleTitles[8] = {"Lady", "Baroness", "Countess", "Marquise",
"Duchess", "Grand Duchess", "Princess",
            "* H.R.H. Queen"};

struct Player
{
public:
    int Cathedral, Clergy, CustomsDuty, CustomsDutyRevenue, DeadSerfs;
    int Difficulty, FleeingSerfs, GrainDemand, GrainPrice, GrainReserve;
    int Harvest, IncomeTax, IncomeTaxRevenue, RatsAte;
    int Justice, JusticeRevenue, Land, Marketplaces, MarketRevenue;
    int Merchants, MillRevenue, Mills, NewSerfs, Nobles, OldTitle, Palace;
    int Rats, SalesTax, SalesTaxRevenue, Serfs, SoldierPay, Soldiers, TitleNum;
    int TransplantedSerfs, Treasury, WhichPlayer, Year, YearOfDeath;
    std::string City, Name, Title;
    float PublicWorks, LandPrice;
    bool InvadeMe, IsBankrupt, IsDead, IWon, MaleOrFemale, NewTitle;
    void ImDead();
};
typedef struct Player player;
/******************************************************************************
 ** This function will take a parameter Hi and return a random integer**
 ** between 0 and Hi.**
 ******************************************************************************/
int Random(int Hi)  //shortened and simplified the random number generation function
{
    int RanNum=rand() % Hi +1;
    return(RanNum);
}


//initializing function
void InitializePlayer(player *Me, int year, int city, int level, std::string name, bool gender)
{
/* This is pretty straightforward. */
    Me->Cathedral = 0;
    Me->City = CityList[city];
    Me->Clergy = 5;
    Me->CustomsDuty = 25;
    Me->Difficulty = level;
    Me->GrainPrice = 25;
    Me->GrainReserve = 5000;
    Me->IncomeTax = 5;
    Me->IsBankrupt = 0;
    Me->IsDead = 0;
    Me->IWon = 0;
    Me->Justice = 2;
    Me->Land = 10000;
    Me->LandPrice = 10.0;
    Me->MaleOrFemale = gender;
    Me->Marketplaces = 0;
    Me->Merchants = 25;
    Me->Mills = 0;
    Me->Name = name;
    Me->Nobles = 4;
    Me->OldTitle = 1;
    Me->Palace = 0;
    Me->PublicWorks = 1.0;
    Me->SalesTax = 10;
    Me->Serfs = 2000;
    Me->Soldiers = 25;
    Me->TitleNum = 1;
    if(Me->MaleOrFemale == 1)
        Me->Title = MaleTitles[0];
    else
        Me->Title = FemaleTitles[0];
    if(city == 6)
        Me->Title = "Baron";
    Me->Treasury = 1000;
    Me->WhichPlayer = city;
    Me->Year = year;
    Me->YearOfDeath = year + 20 + Random(35);

}
void Player::ImDead()
{
    int why;
    std::cout << "\n\nVery sad news.\n" << Title << " " << Name << " has just died\n";
    if(Year > 1450)
        std::cout << " of old age after a long reign.\n";
    else
    {
        why = Random(8);
        switch(why)
        {
            case 0:
            case 1:
            case 2:
            case 3: std::cout << "of pneumonia after a cold winter in a drafty castle.\n"; break;
            case 4: std::cout << "of typhoid after drinking contaminated water.\n"; break;
            case 5: std::cout << "in a smallpox epidemic.\n"; break;
            case 6: std::cout << "after being attacked by robbers while travelling.\n"; break;
            case 7:
            case 8: std::cout << "of food poisoning.\n"; break;
        }
    }
    IsDead = 1;
    std::cout << "\n(Press ENTER): ";
    std::cin.ignore();





}
class paraviamap : public Player
{
private:

public:
    void DrawMap();
};
void paraviamap::DrawMap()
{
    if(Cathedral==1)
        std::cout << "Cathedral is owned";
        std::cout << "----Cathedral-----";
    if(Mills==1)
        std::cout << "Mill is owned";
        std::cout << "-------Mill-------";
    if(Marketplaces==1)
        std::cout << "Market is owned.";
        std::cout << "-------Market-----";
    if(Palace==1)
        std::cout << "Palace is owned.";
        std::cout << "-------Palace-----";
}
#endif // PLAYER_HPP_INCLUDED
