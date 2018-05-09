#ifndef QUESTIONS_HPP_INCLUDED
#define QUESTIONS_HPP_INCLUDED
void PrintInstructions();
void instructions()
{
    char input;
    cout << "\nDo you wish to print the instructions? (Type Y or N)\n";
    std::cin >> input;
    //i kept this, i liked how it worked by only taking the first character typed in
    if(input == 'y' || input == 'Y')
        PrintInstructions();
}

void PrintInstructions(void)
{
    cout << "Santa Paravia and Fiumaccio\n\n"
         << "You are the ruler of a 15th century Italian city state.\n"
         << "If you rule well, you will receive higher titles. The\n"
         << "first player to become king or queen wins. Life expectancy\n"
         << "then was brief, so you may not live long enough to win.\n"
         << "The computer will draw a map of your state. The size\n"
         << "of the area in the wall grows as you buy more land. The\n"
         << "size of the guard tower in the upper left corner shows\n"
         << "the adequacy of your defenses. If it shrinks, equip more\n"
         << "soldiers! If the horse and plowman is touching the top of the wall,\n"
         << "all your land is in production. Otherwise you need more\n"
         << "serfs, who will migrate to your state if you distribute\n"
         << "more grain than the minimum demand. If you distribute less\n"
         << "grain, some of your people will starve, and you will have\n"
         << "a high death rate. High taxes raise money, but slow down\n"
         << "economic growth. (Press ENTER to begin game)\n";
    std::cin.ignore();
}
int userdata()
{
    player MyPlayers[6];
    paraviamap PlayersMaps[6];

    int NumOfPlayers, i, level;
    bool gender;
    std::string name, input;//input for gender and name
    cout << "How many people want to play (1 to 6)?\n";
    std::cin >> NumOfPlayers;
    if(NumOfPlayers < 1 || NumOfPlayers > 6)
    {
/* Ends the game, handles the possible error with not having right amount of players */
        cout << "Thanks for playing.\n";
        return 0;
    }
    cout << "What will be the difficulty of this game: \n1. Apprentice\n"
         << "2. Journeyman\n3. Master\n4. Grand Master\n\nChoose: ";
    std::cin >> level;
    if(level < 1)
        level = 1;
    if(level > 4)
        level = 4;
    for(i = 0; i < NumOfPlayers; i++)
    {
        cout << "Who is the ruler of " << CityList[i] << "? ";
        std::cin >> name; //i like this too how they did it
/* Strip off the trailing \n. */
        cout << "Is " << name << " a man or a woman (M or F)?";
        std::cin >> input;
        if(input[0] == 'm' || input[0] == 'M')
            gender = 1; //this is male
        else
            gender = 0; // this is female
/* initialize the players inputted data */
        InitializePlayer(&MyPlayers[i], 1400, i, level, name, gender);
    }
    /* creates an array of players(7 maximum, 1 AI and the rest can be inputted)*/
        PlayGame(MyPlayers, NumOfPlayers,PlayersMaps);
    return 1;
}
#endif // QUESTIONS_HPP_INCLUDED
