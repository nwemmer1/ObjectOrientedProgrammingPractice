#ifndef TREASURY_HPP_INCLUDED
#define TREASURY_HPP_INCLUDED

void GenerateIncome(player *);
void SeizeAssets(player *);
void AddRevenue(player *);


void AddRevenue(player *Me)
{
    Me->Treasury += (Me->JusticeRevenue + Me->CustomsDutyRevenue);
    Me->Treasury += (Me->IncomeTaxRevenue + Me->SalesTaxRevenue);
/* Penalize deficit spending. */
    if(Me->Treasury < 0)
        Me->Treasury = (int)((float)Me->Treasury * 1.5);
/* Will a title make the creditors happy (for now)? */
    if(Me->Treasury < (-10000 * Me->TitleNum))
    Me->IsBankrupt = 1;
}


void NewLandAndGrainPrices(player *Me)
{
    float x, y, MyRandom;
    int h;
/* Generate an offset for use in later int->float conversions. */
    MyRandom = (float)((float)rand() / (float)RAND_MAX);
/* If you think this C code is ugly, you should see the original BASIC. */
    x = (float)Me->Land;
    y = (((float)Me->Serfs - (float)Me->Mills) * 100.0) * 5.0;
    if(y < 0.0)
        y = 0.0;
    if(y < x)
        x = y;
    y = (float)Me->GrainReserve * 2.0;
    if(y < x)
        x = y;
    y = (float)Me->Harvest + (MyRandom - 0.5);
    h = (int)(x * y);
    Me->GrainReserve += h;
    Me->GrainDemand = (Me->Nobles * 100) + (Me->Cathedral * 40) + (Me->Merchants * 30);
    Me->GrainDemand += ((Me->Soldiers * 10) + (Me->Serfs * 5));
    Me->LandPrice = (3.0 * (float)Me->Harvest + (float)Random(6) + 10.0) / 10.0;
    if(h < 0)
        h *= -1;
    if(h < 1)
    y = 2.0;
    else
    {
        y = (float)((float)Me->GrainDemand / (float)h);
        if(y > 2.0)
            y = 2.0;
    }
    if(y < 0.8)
        y = 0.8;
    Me->LandPrice *= y;
    if(Me->LandPrice < 1.0) Me->LandPrice = 1.0;
        Me->GrainPrice = (int)(((6.0 - (float)Me->Harvest) * 3.0 + (float)Random(5) + (float)Random(5)) * 4.0 * y);
    Me->RatsAte = h;
}


void GenerateIncome(player *Me)
{
    float y;
    int revenues = 0;
    char string[256];
    Me->JusticeRevenue = (Me->Justice * 300 - 500) * Me->TitleNum;
    switch(Me->Justice)
    {
        case 1: strcpy(string, "Very Fair"); break;
        case 2: strcpy(string, "Moderate"); break;
        case 3: strcpy(string, "Harsh"); break;
        case 4: strcpy(string, "Outrageous");
    }
    y = 150.0 - (float)Me->SalesTax - (float)Me->CustomsDuty - (float)Me->IncomeTax;
    if(y < 1.0)
        y = 1.0;
    y /= 100.0;
    Me->CustomsDutyRevenue = Me->Nobles * 180 + Me->Clergy * 75 + Me->Merchants * 20 * y;
    Me->CustomsDutyRevenue += (int)(Me->PublicWorks * 100.0);
    Me->CustomsDutyRevenue = (int)((float)Me->CustomsDuty / 100.0 * (float)Me->CustomsDutyRevenue);
    Me->SalesTaxRevenue = Me->Nobles * 50 + Me->Merchants * 25 + (int)(Me->PublicWorks * 10.0);
    Me->SalesTaxRevenue *= (y * (5 - Me->Justice) * Me->SalesTax);
    Me->SalesTaxRevenue /= 200;
    Me->IncomeTaxRevenue = Me->Nobles * 250 + (int)(Me->PublicWorks * 20.0);
    Me->IncomeTaxRevenue += (10 * Me->Justice * Me->Nobles * y);
    Me->IncomeTaxRevenue *= Me->IncomeTax;
    Me->IncomeTaxRevenue /= 100;
    revenues = Me->CustomsDutyRevenue + Me->SalesTaxRevenue +
    Me->IncomeTaxRevenue + Me->JusticeRevenue;
    std::cout << "State revenues " << revenues << " gold florins.\n";
    std::cout << "Customs Duty\tSales Tax\tIncome Tax\tJustice\n";
    std::cout << Me->CustomsDutyRevenue << "\t\t" << Me->SalesTaxRevenue << "\t\t" << Me->IncomeTaxRevenue << "\t\t" << Me->JusticeRevenue << string << "\n";
}

void SeizeAssets(player *Me)
{
    std::string x; //used for pressing enter
    Me->Marketplaces = 0;
    Me->Palace = 0;
    Me->Cathedral = 0;
    Me->Mills = 0;
    Me->Land = 6000;
    Me->PublicWorks = 1.0;
    Me->Treasury = 100;
    Me->IsBankrupt = 0;
    std::cout << "\n\n" << Me->Title << Me->Name << "is bankrupt.\n";
    std::cout << "\nCreditors have seized much of your assets.\n";
    std::cout << "\n(Press ENTER): ";
    std::cin >> x;
    std::cin.ignore();

}

void AdjustTax(player *Me)
{
    char string[256];
    int val = 1, duty = 0;
    string[0] = '\0';
    while(val != 0 || string[0] != 'q')
    {
        std::cout << "\n" << Me->Title<< "\n\n" << Me->Name << "\n\n";
        GenerateIncome(Me);
        std::cout << "(" << Me->CustomsDuty << ")\t\t(" << Me->SalesTax << ")\t\t(" << Me->IncomeTax << ")"
                  << "\n1. Customs Duty, 2. Sales Tax, 3. Wealth Tax, "
                  << "4. Justice\n"
                  << "Enter tax number for changes, q to continue: ";
        std::cin >> val;
        switch(val)
        {
            case 1:
                std::cout << "New customs duty (0 to 100): ";
                std::cin >> duty;
                if(duty > 100) duty = 100;
                if(duty < 0) duty = 0;
                Me->CustomsDuty = duty;
                break;
            case 2:
                std::cout << "New sales tax (0 to 50): ";
                std::cin >> duty;
                if(duty > 50) duty = 50;
                if(duty < 0) duty = 0;
                Me->SalesTax = duty;
                break;
            case 3:
                std::cout<< "New wealth tax (0 to 25): ";
                std::cin >> duty;
                if(duty > 25)
                    duty = 25;
                if(duty < 0)
                    duty = 0;
                Me->IncomeTax = duty;
                break;
            case 4:
                std::cout << "Justice: 1. Very fair, 2. Moderate"
                          << " 3. Harsh, 4. Outrageous: ";
                std::cin  >> duty;
                if(duty > 4) duty = 4;
                if(duty < 1) duty = 1;
                Me->Justice = duty;
                break;
        }

    }
    AddRevenue(Me);
    if(Me->IsBankrupt == 1)
        SeizeAssets(Me);
}

void StatePurchases(player *Me, int HowMany, player MyPlayers[6], paraviamap *mpmap)
{
    char string[256];
    int val = 1;
    string[0] = '\0';
    while(val != 0 || string[0] != 'q')
    {
    std::cout << "\n\n" << Me->Title << Me->Name <<  "\nState purchases.\n";
        std::cout << "\n1. Marketplace (" << Me->Marketplaces << ")\t\t\t\t1000 florins\n";
        std::cout << "2. Woolen mill (" << Me->Mills << ")\t\t\t\t2000 florins\n";
        std::cout << "3. Palace (partial) (" << Me-> Cathedral << ")\t\t\t\t3000 florins\n";
        std::cout << "4. Cathedral (partial) (" << Me->Cathedral << ")\t\t\t5000 florins\n";
        std::cout << "5. Equip one platoon of serfs as soldiers\t500 florins\n";
        std::cout << "\nYou have " << Me->Treasury << " gold florins.\n";
        std::cout << "\nTo continue, enter q. To compare standings, enter 6\n";
        std::cout << "Your choice: ";
        std::cin >> val;
        switch(val)
        {
            case 1: BuyMarket(Me, mpmap); break;
            case 2: BuyMill(Me, mpmap); break;
            case 3: BuyPalace(Me, mpmap); break;
            case 4: BuyCathedral(Me, mpmap); break;
            case 5: BuySoldiers(Me); break;
            case 6: ShowStats(MyPlayers, HowMany);
        }
    }
    return;
}

#endif // TREASURY_HPP_INCLUDED
