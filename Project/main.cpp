#include<iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <sstream>
#include "line.h"
#include "table.h"
#include "collection.h"

int main()
{
collection data;
string line;
ifstream inFile;
ifstream fin;
string filename;
string filename0;
string table;
string printhere;
string a;
cout << "Please enter filename: "; //Ask user to enter filename
getline (cin,filename);
inFile.open(filename.c_str());
if(inFile.fail())
{
		cout << filename << " does not exist." << endl;				//Error message if the filename is not found
}

else
{
	while(getline(inFile,line))
	{
		if (line =="")
		{	
			break;
		}
	data.readdata(line);								//Taking in data
	}
	
	while (getline(inFile,line))
	{	
		data.letsdothis(line);							//Taking instructions
	}
	
}

return 0;
}
