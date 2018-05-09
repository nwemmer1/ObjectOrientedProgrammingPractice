
#ifndef PARAVIA-FUNCTIONS_HPP_INCLUDED
#define PARAVIA-FUNCTIONS_HPP_INCLUDED
#include "buysell.hpp"
/*
======================================================================================
====My reasoning for this poorly named and used file is to start to get more of   ====
====and idea of how I am going to break up everything later. I have int main      ====
====in its own file and all the functions in one header file. Eventually, this    ====
====will be broken up into several files/classes.                                 ====
====                                                                              ====
====                                                                              ====
======================================================================================
*/

/* Declare an enum to emulate a Boolean. */
//this was taken out completely, and changed to use a bool type, not a
//makeshift boolean emulation. Less code/less confusion/current/faster?
using std::cout;
/* Our prototypes. */
int Random(int);
void InitializePlayer(player*, int, int, int, char*, bool);
void AddRevenue(player *);
int AttackNeighbor(player *, player *);
int limit10(int, int);
bool CheckNewTitle(player *);
void GenerateHarvest(player *);
void GenerateIncome(player *);
void ChangeTitle(player *);
void NewLandAndGrainPrices(player *);
int ReleaseGrain(player *);
void SeizeAssets(player *);
void SerfsDecomposing(player *, float);
void SerfsProcreating(player *, float);
void PrintInstructions(void);
void PlayGame(player [], int);
void NewTurn(player *, int, player [], player *);
void AdjustTax(player *);
void DrawMap(player *);
void StatePurchases(player *, int, player []);
void ShowStats(player [], int);
void ImDead(player *);
//******************************************************************************

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

int AttackNeighbor(player *Me, player *Him)
{
    int LandTaken;
    int deadsoldiers = 0;
    if(Me->WhichPlayer == 7)
        LandTaken = Random(9000) + 1000;
    else
        LandTaken = (Me->Soldiers * 1000) - (Me->Land / 3);
    if(LandTaken > (Him->Land - 5000))
        LandTaken = (Him->Land - 5000) / 2;
    Me->Land += LandTaken;
    Him->Land -= LandTaken;
    printf("\a\n%s %s of %s invades and seizes %d hectares of land!\n",
    Me->Title, Me->Name, Me->City, LandTaken);
    deadsoldiers = Random(40);
    if(deadsoldiers > (Him->Soldiers - 15))
        deadsoldiers = Him->Soldiers - 15;
    Him->Soldiers -= deadsoldiers;
    std::cout << Him->Title << " " << Him->Name << " loses " << deadsoldiers << " soldiers in battle.\n";
    return(LandTaken);
}


int limit10(int num, int denom)
{
    register int val;
    val = num / denom;
    return(val > 10 ? 10 : val);
}

bool CheckNewTitle(player *Me)
{
    int Total;
/* Tally up our success so far . . . . */
    Total = limit10(Me->Marketplaces, 1);
    Total += limit10(Me->Palace, 1);
    Total += limit10(Me->Cathedral, 1);
    Total += limit10(Me->Mills, 1);
    Total += limit10(Me->Treasury, 5000);
    Total += limit10(Me->Land, 6000);
    Total += limit10(Me->Merchants, 50);
    Total += limit10(Me->Nobles, 5);
    Total += limit10(Me->Soldiers, 50);
    Total += limit10(Me->Clergy, 10);
    Total += limit10(Me->Serfs, 2000);
    Total += limit10((int)(Me->PublicWorks * 100.0), 500);
    Me->TitleNum = (Total / Me->Difficulty) - Me->Justice;
    if(Me->TitleNum > 7)
        Me->TitleNum = 7;
    if(Me->TitleNum < 0)
        Me->TitleNum = 0;
/* Did we change (could be backwards or forwards)? */
    if(Me->TitleNum > Me->OldTitle)
    {
        Me->OldTitle = Me->TitleNum;
        ChangeTitle(Me);
        std::cout << "\aGood news! " << Me->Name << " has achieved the rank of " << Me->Title << "\n\n";
        return(1);
    }
    Me->TitleNum = Me->OldTitle;
    return(0);
}

void GenerateHarvest(player *Me)
{
    Me->Harvest = (Random(5) + Random(6)) / 2;
    Me->Rats = Random(50);
    Me->GrainReserve = ((Me->GrainReserve * 100) - (Me->GrainReserve * Me->Rats)) / 100;
}



void ChangeTitle(player *Me)
{
    if(Me->MaleOrFemale == 1)
        Me->Title = MaleTitles[Me->TitleNum];
    else
        Me->Title = FemaleTitles[Me->TitleNum];
    if(Me->TitleNum == 7)
    {
        Me->IWon = 1;
    }
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



int ReleaseGrain(player *Me)
{
    double xp, zp;
    float x, z;
    char string[256];
    int HowMuch, Maximum, Minimum;
    bool IsOK;
    IsOK = 0;
    Minimum = Me->GrainReserve / 5;
    Maximum = (Me->GrainReserve - Minimum);
    while(IsOK == 0)
    {
        std::cout << "How much grain will you release for consumption?\n";
        std::cout << "1 = Minimum (" << Minimum << "), 2 = Maximum(" << Maximum << "), or enter a value: ";
        std::cin >> HowMuch;
        if(HowMuch == 1)
            HowMuch = Minimum;
        if(HowMuch == 2)
            HowMuch = Maximum;
/* Are we being a Scrooge? */
        if(HowMuch < Minimum)
            std::cout << "You must release at least 20%% of your reserves.\n";
/* Whoa. Slow down there son. */
        else if(HowMuch > Maximum)
            std::cout << "You must keep at least 20%%.\n";
        else
            IsOK = 1;
    }


    Me->SoldierPay = Me->MarketRevenue = Me->NewSerfs = Me->DeadSerfs = 0;
    Me->TransplantedSerfs = Me->FleeingSerfs = 0;
    Me->InvadeMe = 0;
    Me->GrainReserve -= HowMuch;
    z = (float)HowMuch / (float)Me->GrainDemand - 1.0;
    if(z > 0.0)
        z /= 2.0;
    if(z > 0.25)
        z = z / 10.0 + 0.25;
    zp = 50.0 - (double)Me->CustomsDuty - (double)Me->SalesTax - (double)Me->IncomeTax;
    if(zp < 0.0)
        zp *= (double)Me->Justice;
    zp /= 10.0;
    if(zp > 0.0)
        zp += (3.0 - (double)Me->Justice);
    z += ((float)zp / 10.0);
    if(z > 0.5)
        z = 0.5;
    if(HowMuch < (Me->GrainDemand - 1))
    {
        x = ((float)Me->GrainDemand - (float)HowMuch) / (float)Me->GrainDemand * 100.0 - 9.0;
        xp = (double)x;
        if(x > 65.0)
            x = 65.0;
        if(x < 0.0)
        {
            xp = 0.0;
            x = 0.0;
        }
        SerfsProcreating(Me, 3.0);
        SerfsDecomposing(Me, xp + 8.0);
    }

    else
    {
        SerfsProcreating(Me, 7.0);
        SerfsDecomposing(Me, 3.0);


        if((Me->CustomsDuty + Me->SalesTax) < 35)
        {
            Me->Merchants += Random(4);
        }

        if(Me->IncomeTax < Random(28))
        {
            Me->Nobles += Random(2);
            Me->Clergy += Random(3);
        }

        if(HowMuch > (int)((float)Me->GrainDemand * 1.3))
        {
            zp = (double)Me->Serfs / 1000.0;
            z = ((float)HowMuch - (float)(Me->GrainDemand)) / (float)Me->GrainDemand * 10.0;
            z *= ((float)zp * (float)Random(25));
            z += (float)Random(40);
            Me->TransplantedSerfs = (int)z;
            Me->Serfs += Me->TransplantedSerfs;
            std::cout << Me->TransplantedSerfs << " serfs move to the city\n";
            zp = (double)z;
            z = ((float)zp * (float)rand()) / (float)RAND_MAX;
            if(z > 50.0)
                z = 50.0;
    Me->Merchants += (int)z;
    Me->Nobles++;
    Me->Clergy += 2;
        }
    }
    if(Me->Justice > 2)
    {
        Me->JusticeRevenue = Me->Serfs / 100 * (Me->Justice - 2) * (Me->Justice - 2);
        Me->JusticeRevenue = Random(Me->JusticeRevenue);
        Me->Serfs -= Me->JusticeRevenue;
        Me->FleeingSerfs = Me->JusticeRevenue;
        std::cout << Me->FleeingSerfs << " serfs flee harsh justice\n";
    }
    Me->MarketRevenue = Me->Marketplaces * 75;
    if(Me->MarketRevenue > 0)
    {
        Me->Treasury += Me->MarketRevenue;
        std::cout << "Your market earned " << Me->MarketRevenue << " florins.\n";
    }
    Me->MillRevenue = Me->Mills * (55 + Random(250));
    if(Me->MillRevenue > 0)
    {
        Me->Treasury += Me->MillRevenue;
        std::cout << "Your woolen mill earned " << Me->MillRevenue << " florins.\n";
    }
    Me->SoldierPay = Me->Soldiers * 3;
    Me->Treasury -= Me->SoldierPay;
    std::cout << "You paid your soldiers " << Me->SoldierPay << " florins.\n";
    std::cout << "You have " << Me->Serfs << " serfs in your city.\n";
    std::cout << "(Press ENTER): ";
    fgets(string, 255, stdin);
    if((Me->Land / 1000) > Me->Soldiers)
    {
        Me->InvadeMe = 1;
        return(3);
    }
    if((Me->Land / 500) > Me->Soldiers)
    {
        Me->InvadeMe = 1;
        return(3);
    }
    return(0);
}


void SerfsDecomposing(player *Me, float MyScale)
{
    int absc =(int)MyScale;
    float ord = MyScale - (float)absc;

    Me->DeadSerfs = (int)((((float)Random(absc) + ord) * (float)Me->Serfs) / 100.0);
    Me->Serfs -= Me->DeadSerfs;
    std::cout << Me->DeadSerfs << " serfs die this year.\n";
}

void SerfsProcreating(player *Me, float MyScale)
{
    int absc;
    float ord;
    absc = (int)MyScale;
    ord = MyScale - (float)absc;
    Me->NewSerfs = (int)((((float)Random(absc) + ord) * (float)Me->Serfs) / 100.0);
    Me->Serfs += Me->NewSerfs;
    std::cout << Me->NewSerfs << " serfs born this year.\n";

}

void PlayGame(player MyPlayers[6], int NumOfPlayers)
{
    void InitializePlayer(player*, int, int, int, std::string, bool);
    bool AllDead, Winner;
    int i;
    int WinningPlayer = 0;
    player Baron;
    AllDead = 0;
    Winner = 0;
    InitializePlayer(&Baron, 1400, 6, 4, "Peppone", 1);
    while(AllDead == 0 && Winner == 0)
    {
        for(i = 0; i < NumOfPlayers; i++)
            if(MyPlayers[i].IsDead == 0)
                NewTurn(&MyPlayers[i], NumOfPlayers, MyPlayers,&Baron);
        AllDead = 1;
        for(i = 0; i < NumOfPlayers; i++)
            if(AllDead == 1 && MyPlayers[i].IsDead == 0)
                AllDead = 0;
        for(i = 0; i < NumOfPlayers; i++)
            if(MyPlayers[i].IWon == 1)
            {
                Winner = 1;
                WinningPlayer = i;
            }
    }
    if(AllDead == 1)
    {
        std::cout << "The game has ended.\n";
    }
    std::cout << "Game Over. " << MyPlayers[WinningPlayer].Title << MyPlayers[WinningPlayer].Name << " wins.\n";
}

void NewTurn(player *Me, int HowMany, player MyPlayers[6], player *Baron)
{
    int i;
    GenerateHarvest(Me);
    NewLandAndGrainPrices(Me);
    BuySellGrain(Me);
    ReleaseGrain(Me);
    if(Me->InvadeMe == 1)
    {
        for(i = 0; i < HowMany; i++)
            if(i != Me->WhichPlayer)
                if(MyPlayers[i].Soldiers > (Me->Soldiers * 2.4))
                {
                    AttackNeighbor(&MyPlayers[i], Me);
                    i = 9;
                }
        if(i != 9)
            AttackNeighbor(Baron, Me);
    }
    AdjustTax(Me);
    //DrawMap(Me);
    StatePurchases(Me, HowMany, MyPlayers);
    CheckNewTitle(Me);

    Me->Year++;
    if(Me->Year == Me->YearOfDeath)
    {
        Me->ImDead();
    }
    if(Me->TitleNum >= 7)
        Me->IWon = 1;
}


void ShowStats(player MyPlayers[6], int HowMany)
{
    int i = 0;
    char string[256];
    std::cout << "Nobles\tSoldiers\tClergy\tMerchants\tSerfs\tLand\tTreasury\n";
    for(; i < HowMany; i++)
        printf("\n%s %s\n%d\t%d\t\t%d\t%d\t\t%d\t%d\t%d\n",
                MyPlayers[i].Title, MyPlayers[i].Name,
                MyPlayers[i].Nobles, MyPlayers[i].Soldiers,
                MyPlayers[i].Clergy, MyPlayers[i].Merchants,
                MyPlayers[i].Serfs, MyPlayers[i].Land,
                MyPlayers[i].Treasury);
    std::cout << "\n(Press ENTER): ";
    fgets(string, 255, stdin);
}

/*void ImDead(player *Me)
{
    int why;

    std::cout << "\n\nVery sad news.\n" << Me->Title << " " << Me->Name << " has just died\n";
    if(Me->Year > 1450)
        std::cout << " of old age after a long reign.\n";
    else
    {
        why = Random(8);
        switch(why)
        {
            case 0:
            case 1:
            case 2:
            case 3: printf("of pneumonia after a cold winter in a drafty castle.\n"); break;
            case 4: printf("of typhoid after drinking contaminated water.\n"); break;
            case 5: printf("in a smallpox epidemic.\n"); break;
            case 6: printf("after being attacked by robbers while travelling.\n"); break;
            case 7:
            case 8: printf("of food poisoning.\n"); break;
        }
    }
    Me->IsDead = 1;
    std::cout << "\n(Press ENTER): ";
    std::cin.ignore();
}
*/
#endif
