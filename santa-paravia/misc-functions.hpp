#ifndef MISC-FUNCTIONS_HPP_INCLUDED
#define MISC-FUNCTIONS_HPP_INCLUDED

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
int limit10(int, int);
void GenerateHarvest(player *);
void NewLandAndGrainPrices(player *);
int ReleaseGrain(player *);
void SerfsDecomposing(player *, float);
void SerfsProcreating(player *, float);
void AdjustTax(player *);
void StatePurchases(player *, int, player [], paraviamap *);
//******************************************************************************


int limit10(int num, int denom)
{
    register int val;
    val = num / denom;
    return(val > 10 ? 10 : val);
}


void GenerateHarvest(player *Me)
{
    Me->Harvest = (Random(5) + Random(6)) / 2;
    Me->Rats = Random(50);
    Me->GrainReserve = ((Me->GrainReserve * 100) - (Me->GrainReserve * Me->Rats)) / 100;
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


#endif // MISC-FUNCTIONS_HPP_INCLUDED
