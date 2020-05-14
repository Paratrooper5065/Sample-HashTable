#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "line.h"


line:: line()
{
	temporary=0;
}

void line::addline(string x)					//Add a line
	{	
		string t;
		stringstream ss(x);
		while(getline (ss,t,'|'))
				{ 
					lline.push_back(t);
				}
	}

string line::getlline(int g)					//Return the line
	{
		return lline[g];
	}

void line::SetTemp(int t)					//Set some temporary variable
	{
		temporary = t;
	}

int line::GetTemp()						//Return the temporary variable
	{
		return temporary;
	}

void line::removeline()						//Remove the entire line
	{
	lline.clear();
	}
