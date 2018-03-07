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


#pragma once		

#include <cassert>
#include <iosfwd>
#include <iostream>
#include <vector>

class RatNum
{
private:
	int numerator;
	int denominatior;
	void simplifyFraction();
	std::vector<int> multiply(RatNum x);
public:
//constructors
	RatNum();
	RatNum(int num);
	RatNum(int num, int denom);
//overoading so i can compare the numbers
	bool operator==(RatNum x);
	bool operator<(RatNum x);
	bool operator>(RatNum x);
	bool operator!=(RatNum x);
	bool operator>=(RatNum x);
	bool operator<=(RatNum x);
//overloading for the actual comparison between two class objects i created
	RatNum operator+(RatNum x);
	RatNum operator-(RatNum x);
	RatNum operator/(RatNum x);
	RatNum operator*(RatNum x);

	friend std::istream& operator>>(std::istream &inFile, RatNum &x);
	friend std::ostream& operator<<(std::ostream &output, const RatNum &x);

};

//I put all of the functions from the class in the same header file(this one) for easier
//and more convienent reading/access.

std::vector<int> RatNum::multiply(RatNum x)
{
	int Side1 = numerator * x.denominator;
	int Side2 = x.numerator * denominator;
	return std::vector<int> {Side1, Side2};
	
}


void RatNum::simplifyFraction()
{
	int Gcd = std::gcd(numerator,denominator);
	numerator = numerator/Gcd;
	denominator = denominator/Gcd;

//found something online, generic if statement that helps show
//the number if there is a sign before the call, makes sure its the right number

	if((numerator > 0 && denominator < 0) || (numerator < 0 && denominator < 0))
	{
		numerator=-numerator;
		denominator=-denominator;
	}
}

RatNum::RatNum(int num)
{
	numerator = num;
	denominator = 1;
}

RatNum::RatNum(int num, int denom)
{
	if(denom == 0)
	{
       `	throw;
	}

	numerator=num;
	denominator=denom;
	simplifyFraction();
}


bool RatNum::operator==(RatNum x)
{	
	return numerator == x.numerator && denominator == x.denominator;
}

bool RatNum::operator!=(RatNum x)
{
	return !(*this == x);
}

bool RatNum::operator>(RatNum x)
{
	std::vector<int> product = multiply(x);
	return product[0] > product[1];
}

bool RatNum::operator<(RatNum x)
{
	std::vector<int> product = multiply(x);
	return product[0] < product[1];
}

bool RatNum::operator<=(RatNum x)
{
	return *this < x || *this == x;
}

bool RatNum::operator>=(RatNum x)
{
	return *this > x || *this == x;
}

RatNum RatNum::operator-(RatNum x)
{
	std::vector<int> product = multiply(x);
	int resultNum = product[0] - product[1];
	int resultDenom = denominator * x.denominator;
	return RatNum(resultNum, resultDenom);
}

RatNum RatNum::operator+(RatNum x)
{
	std::vector<int> product = multiply(x);
	int resultNum = product[0] + product[1];
	int resultDenom = denominator * x.denominator;
	return RatNum(resultNum, resultDenom);
}

RatNum RatNum::operator/(RatNum x)
{
	RatNum flippedx = RatNum(x.denominator,x.numerator);
	int resultNum = numerator * flippedx.numerator;
	int resultDenom = denominator*flippedx.denominator;
	return RatNum(resultNum, resultDenom);
}

RatNum RatNum::operator*(RatNum x)
{
	int resultNum= numerator * x.numerator;
	int resultDenom= denominator *x.denominator;
	return RatNum(resultNum,resultDenom);
}

std::ostream& operator<<(std::ostream &output, const RatNum &x)
{

	if(x.numerator==0)
		output << 0;
	else if(x.denominator == 1)
		output << x.numerator;
	else
		output << x.numerator << "/" << x.denominator;

	return output;
}

RatNum RatNum::operator-()
{
	return RatNum(-numerator,denominator);
}

std::istream& operator>>(std::istream &inputFile, RatNum &x)
{
	inputFile >> x.numerator >> x.denominator;
	x.simplifyFraction();
	return inputFile;
}