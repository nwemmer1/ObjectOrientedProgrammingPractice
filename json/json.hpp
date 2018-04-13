#pragma once


#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>


using std::cout;
using std::cin;
using std::endl;
using std::string;
// TODO: Write your JSON class hierarchy here.


struct value
{
public:
	value () { } //default constructor
	virtual void print() const = 0;
	virtual ~value() = 0;
};

struct null : public value 
{
	void print() const override 
	{
		cout << "{}";
	}
};

struct numeral : public value
{
	numeral(double n) : val(n) { }
	double val;
	void print() const override
	{
		cout << val;
	}
};

struct string : public value 
{
	string(string s) : val(s) { }
	string val;
	void print() const override
	{
		cout << val;
	}
};

struct array : public value, vector<value*>
{
	void InsertIt(value* v)
	{
		this->push_back(v);
	}
	void print() const override
	{
		cout << "[";
		for vector<value*>::const iterator it = this->begin(); it!=this->end(); ++it
		{
			(*it)->print();
			cout << " ,";
		}
		cout << "]"<<endl;
	}
};

struct stdObj : public value
{
	std::map<string*, value*> data;
	void InsertIt(string* p, value* v)
	{
		data.insert(std::pair<string*, value*>(p,v) );
	}
	void print() const override
	{
		cout << "{}" << endl;
		for(std::map<string*, value*>::const_iterator it=values.begin(); it!= data.end(); ++it)
		{
			cout << \t";
			it->first->print();
			cout << ": ";
			it->second->print();
			cout << "," << endl;
		}
		cout << "}" << endl;
	}
};
	
	value* parse(const string&);