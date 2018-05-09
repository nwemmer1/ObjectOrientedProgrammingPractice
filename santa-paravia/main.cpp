
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//#include <curses.h>

#include "player.hpp"
#include "paravia-functions.h"
#include "buysell.hpp"
#include "treasury.hpp"
#include "questions.hpp"
#

using std::cout;
using std::cin;
using std::endl;
/* Declare our player definition. */
void InitializePlayer(player*, int, int, int, std::string, bool);

int main()
{
/* Initialize the random number generator seed. */
    srand(time(NULL));
/* Start the game, instructions, input user data. */
    cout << "Santa Paravia and Fiumaccio\n";
    instructions();
    userdata();
/* We're finished. */
    return(0);
}

