/*
	Nathan Wemmer
	Object-Oriented Programming
	Rational Number practice
Implement a rational number class. The class must:

Only allow the creation of valid rational numbers
	-Support equality (==, !=)
	-Support ordering (<, >, <=, >=)
	-Support basic arithmetic operators (+, - , * /)
	-Support input and output using istream (>>) and ostream (<<)
	-The input and output format form rational numbers should be of the form "n / d".
*/

#include <fstream>
#include <iostream>
#include <cassert>
#include "rational-number.hpp"
using std::cout;
using std::endl;
int
main(int arg1, char const *arg2[]) 
{
// creating 2 rational numers with the Ratnum class
	RatNum num1 = RatNum(8,2);
	RatNum num2 = RatNum(4,1);
//These 2 are the same, true 4==4
	assert(num1==num2);

//created another rational number that isnt the same
	RatNum num3 = RatNum(7,2);
//these arent the same, true 4 != 3.5 
	assert(num1 != num3);
	assert(num2 != num3);

//these are comparing using greater and less than
//should be true always 4>3.5
	assert(num2 > num3);
	assert(num3 < num2);

//these are comparing using greater or equal to, and less than or equal to
	assert(num1 >= num3);
	assert(num3 <= num1);
	assert(num1 >= num2);

//These are the addition tests, created num4 for testing 
//should be true, 4+4=8 and 8==8
	RatNum num4 = num1 + num2;
	assert(num4 == RatNum(8)); //i think i compared these right?
	
//These are the subtraction tests, created num5 for testing
//should be true 8-1/2=15/2
	RatNum num5 = num4 - RatNum(1,2);
	assert(num5 == RatNum(15,2));

//These are the division tests, created num6-8 for testing
	RatNum num6 = RatNum(10,2);
	Ratnum num7 = RatNum(4);
 	RatNum num8 = num6 / num7;

//These are the multiplication tests, created num9 for testing
//should be true -4*3.5=-14 and -14==-14
	RatNum num9 = -num1 * num3;
	assert(num9 == RatNum(-14));

//This is the input stream test 
	std::ifstream inFile;
	inFile.open("inputFile");
	RatNum num10;
	inFile >> num10;

//this should be true because the input file has just 7/4 in it and 7/4==7/4
	assert(num10 == RatNum(7,4));

//This is all the output shown to the user on screen
//This is an example that i am going to use to study/for myself
	cout << "RatNum(2) is shown as " << RatNum(2) << endl;
	cout << "-RatNum(1,2) is shown as " << -RatNum(1,2) << endl;
	cout << "RatNum(0,9) is shown as " << RatNum(0,9) << endl;
	cout << "RatNum(10,2) is shown as " << RatNum(10,2) << endl;
	cout << "RatNum(-2,7) is shown as " << RatNum(-2,7) << endl;
	cout << "RatNum(-4,-6) is shown as " << RatNum(-4,-6) << endl;
	cout << "-RatNum(-1,-5) is shown as " << -RatNum(-1,-5) << endl;
	
	return 0;
}