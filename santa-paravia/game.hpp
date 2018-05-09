#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

int AttackNeighbor(player *, player *);
void NewTurn(player *, int, player [], player *, paraviamap *);
void ShowStats(player [], int);
void PlayGame(player [], int);

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

void PlayGame(player MyPlayers[6], int NumOfPlayers, paraviamap PlayersMaps[6])
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
                NewTurn(&MyPlayers[i], NumOfPlayers, MyPlayers,&Baron,&PlayersMaps[i]);
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


void NewTurn(player *Me, int HowMany, player MyPlayers[6], player *Baron, paraviamap *mpmap)
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
    mpmap->DrawMap();

    StatePurchases(Me, HowMany, MyPlayers, mpmap);
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

#endif // GAME_HPP_INCLUDED
