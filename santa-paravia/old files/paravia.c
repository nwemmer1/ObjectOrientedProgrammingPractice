//**************************************
// Name: paravia.c
// Description:This is a port of the original TRS-80 BASIC code for Santa Paravia and Fiumaccio, (C) 1979 George Blank (used with permission).
// By: Thomas Knox
//
// Inputs:N/A
//
// Returns:N/A
//
// Assumes:Should compile and run on any system with an ANSI-C compiler.
//
// Side Effects:N/A
//
//This code is copyrighted and has
// limited warranties.Please see http://www.Planet-Source-Code.com/vb/scripts/ShowCode.asp?txtCodeId=7183&lngWId=3
//for details.
//**************************************

/******************************************************************************
 ** **
 ** Santa Paravia & Fiumaccio. Translated from the original TRS-80 BASIC **
 ** source code into C by Thomas Knox <tknox@mac.com>.**
 ** **
 ** Original program (C) 1979 by George Blank**
 ** <gwblank@postoffice.worldnet.att.net>**
 ** **
 ******************************************************************************/
/*
Copyright (C) 2000 Thomas Knox
Portions Copyright (C) 1979 by George Blank, used with permission.
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
Thomas Knox
tknox@mac.com
*/
/* Declare our standard C headers. */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//#include <curses.h>

#include "paravia-functions.h"
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

