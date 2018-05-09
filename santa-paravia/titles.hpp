#ifndef TITLES_HPP_INCLUDED
#define TITLES_HPP_INCLUDED

bool CheckNewTitle(player *);
void ChangeTitle(player *);

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


#endif // TITLES_HPP_INCLUDED
