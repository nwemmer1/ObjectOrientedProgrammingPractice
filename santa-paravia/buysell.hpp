#ifndef ACTIONS_HPP_INCLUDED
#define ACTIONS_HPP_INCLUDED
/*These are all of the functions that have something to do with buying something*/
void BuyCathedral(player *);
void BuyGrain(player *);
void BuyLand(player *);
void BuyMarket(player *);
void BuyMill(player *);
void BuyPalace(player *);
void BuySoldiers(player *);
void BuySellGrain(player *);
/*These are all the functions that have to do with selling or printing out what was sold */
void PrintGrain(player *);
void SellGrain(player *);
void SellLand(player *);
void BuySellGrain(player *Me)
{
    bool Finished = 0;
    std::string option;
    while(Finished == 0)
    {
        std::cout << "\nYear " << Me->Year << "\n";
        std::cout << "\n" << Me->Title << " " << Me->Name << "\n\n";
        std::cout << "Rats ate " << Me->Rats << " of your grain reserves.\n";
        PrintGrain(Me);
        std::cout << "(" << Me->RatsAte << " steres)\n\n";
        std::cout << "Grain\tGrain\tPrice of\tPrice of\tTreasury\n";
        std::cout << "Reserve\tDemand\tGrain\t\tLand\n";
        std::cout << Me->GrainReserve << "\t" << Me->GrainDemand << "\t" << Me->GrainPrice << "\t\t" << Me->LandPrice << "\t\t" << Me->Treasury << " \n";
        std::cout << "steres\tsteres\t1000 st.\thectare\t\tgold florins\n";
        std::cout << "\nYou have " << Me->Land << " hectares of land.\n";
        std::cout << "\n1. Buy grain, 2. Sell grain, 3. Buy land,";
        std::cout << " 4. Sell land\n(Enter q to continue): ";
        std::cin >> option[0];

        if(option[0] == 'q')
            Finished = 1;
        if(option[0] == '1')
            BuyGrain(Me);
        if(option[0] == '2')
            SellGrain(Me);
        if(option[0] == '3')
            BuyLand(Me);
        if(option[0] == '4')
            SellLand(Me);
    }
}
void BuyCathedral(player *Me)
{
    Me->Cathedral += 1;
    Me->Clergy += Random(6);
    Me->Treasury -= 5000;
    Me->PublicWorks += 1.0;
}

void BuyGrain(player *Me)
{

    int HowMuch;
    std::cout << "How much grain do you want to buy (0 to specify a total)? ";
    std::cin >> HowMuch;
    if(HowMuch == 0)
    {
        printf("How much total grain do you wish? ");
        std::cin >> HowMuch;
        HowMuch -= Me->GrainReserve;
        if(HowMuch < 0)
        {
            std::cout << "Invalid total amount.\n\n";
        }
    }
    Me->Treasury -= (HowMuch * Me->GrainPrice / 1000);
    Me->GrainReserve += HowMuch;
}

void BuyLand(player *Me)
{
    int HowMuch;
    std::cout << "How much land do you want to buy? \n";
    std::cin >> HowMuch;
    Me->Land += HowMuch;
    Me->Treasury -= (int)(((float)HowMuch * Me->LandPrice));

}
void BuyMarket(player *Me)
{
    Me->Marketplaces += 1;
    Me->Merchants += 5;
    Me->Treasury -= 1000;
    Me->PublicWorks += 1.0;
}

void BuyMill(player *Me)
{
    Me->Mills += 1;
    Me->Treasury -= 2000;
    Me->PublicWorks += 0.25;
}

void BuyPalace(player *Me)
{
    Me->Palace += 1;
    Me->Nobles += Random(2);
    Me->Treasury -= 3000;
    Me->PublicWorks += 0.5;
}

void BuySoldiers(player *Me)
{
    Me->Soldiers += 20;
    Me->Serfs -= 20;
    Me->Treasury -= 500;
}

void SellGrain(player *Me)
{
    int HowMuch;
    std::cout << "How much grain do you want to sell? ";
    std::cin >> HowMuch;
    if(HowMuch > Me->GrainReserve)
    {
        std::cout << "You don't have it.\n";
    }
    Me->Treasury += (HowMuch * Me->GrainPrice / 1000);
    Me->GrainReserve -= HowMuch;
}

void SellLand(player *Me)
{
    int HowMuch;
    std::cout << "How much land do you want to sell?";
    std::cin >> HowMuch;
    if(HowMuch > (Me->Land - 5000))
    {
        std::cout << "You can't sell that much";
    }
    Me->Land -= HowMuch;
    Me->Treasury += (int)(((float)HowMuch * Me->LandPrice));
}

void PrintGrain(player *Me)
{
    switch(Me->Harvest)
    {
        case 0:
        case 1: std::cout << "Drought. Famine Threatens. "; break;
        case 2: std::cout << "Bad Weather. Poor Harvest. "; break;
        case 3: std::cout << "Normal Weather. Average Harvest. "; break;
        case 4: std::cout << "Good Weather. Fine Harvest. "; break;
        case 5: std::cout << "Excellent Weather. Great Harvest! "; break;
    }
}
#endif // ACTIONS_HPP_INCLUDED
