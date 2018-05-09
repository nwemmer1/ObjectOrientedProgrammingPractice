#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//#include <curses.h>

#include "cityInfo.hpp"
#include "grains.hpp"
#include "player.hpp"
#include "resources.hpp"
using std::cout;
using std::cin;
using std::endl;
/* Declare our player definition. */

int main(void)
{
/* creates an array of players(7 maximum, 1 AI and the rest can be inputted)*/
    player MyPlayers[6];
    int NumOfPlayers, i, level;
    char string[255], name[25];
    bool gender;
/* Initialize the random number generator seed. */
    srand(time(NULL));
/* Start the game. */
    cout << "Santa Paravia and Fiumaccio\n";                                    //printf("Santa Paravia and Fiumaccio\n");

    cout << "\nDo you wish to print the instructions? (Type Y or N)\n";         //printf("\nDo you wish instructions (Y or N)? ");
    fgets(string, 254, stdin);
    if(string[0] == 'y' || string[0] == 'Y')
        PrintInstructions();
        
    cout << "How many people want to play (1 to 6)?\n";                         //printf("How many people want to play (1 to 6)? ");
    fgets(string, 254, stdin);
    NumOfPlayers = (int)atoi(string);
    if(NumOfPlayers < 1 || NumOfPlayers > 6)
    {
/* Ends the game, handles the possible error with not having right amount of players */
        cout << "Thanks for playing.\n";                                        //printf("Thanks for playing.\n");
        return(0);
    }
    cout << "What will be the difficulty of this game: \n1. Apprentice\n";     //printf("What will be the difficulty of this game:\n1. Apprentice\n");
    cout << "2. Journeyman\n3. Master\n4. Grand Master\n\nChoose: ";           //printf("2. Journeyman\n3. Master\n4. Grand Master\n\nChoose: ");
    fgets(string, 254, stdin);
    level = (int)atoi(string);
    if(level < 1)
        level = 1;
    if(level > 4)
        level = 4;
    for(i = 0; i < NumOfPlayers; i++)
    {
        cout << "Who is the ruler of " << CityList[i] << "? ";                   //printf("Who is the ruler of %s? ", CityList[i]);
        fgets(name, 24, stdin);
/* Strip off the trailing \n. */
        name[strlen(name) - 1] = '\0';
        cout << "Is " << name << " a man or a woman (M or F)?";                   //printf("Is %s a man or a woman (M or F)? ", name);
        fgets(string, 3, stdin);
        if(string[0] == 'm' || string[0] == 'M')
            gender = 1; //this is male
        else
            gender = 0; // this is female
/* initialize the players inputted data */
        InitializePlayer(&MyPlayers[i], 1400, i, level, name, gender);
    }
/* Enter the main game loop. */
    PlayGame(MyPlayers, NumOfPlayers);
/* We're finished. */
    return(0);
}