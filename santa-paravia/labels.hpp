#pragma once
#include <string>
using std::string;


/* Declare the name of the cities */
char CityList[7][15] = {"Santa Paravia", "Fiumaccio", "Torricella", "Molinetto",
"Fontanile", "Romanga", "Monterana"};

/* Declare our male titles. */
char MaleTitles[8][15] = {"Sir", "Baron", "Count", "Marquis", "Duke",
 "Grand Duke", "Prince", "* H.R.H. King"};

/* Declare our female titles. */
char FemaleTitles[8][15] = {"Lady", "Baroness", "Countess", "Marquise",
"Duchess", "Grand Duchess", "Princess",
            "* H.R.H. Queen"};

class Labels
{
public:
	string name;
	int label; //this will be different depending on if you are a male or female 
};
	