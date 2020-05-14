#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "line.h"
#include "table.h"
#include "collection.h"



collection::collection()
{
	count =0;
}

void collection::readdata(string a)
{	
	ifstream inFile;					
	table thistable;
	string filename0;
	string tablename;
	string keyname;
	stringstream ss(a);
	getline(ss,filename0,' ');					//getline for keyname and the table name
	getline(ss,tablename,' ');
	thistable.SetName(tablename);
	inFile.open(filename0.c_str());
	getline(inFile,keyname);
	thistable.SetKey(keyname);
	getline(inFile,keyname);
	thistable.scheme(keyname);
	while(getline(inFile,keyname))
	{
									//loop to figure out which table to go to
		if (tablename == "spells")
		{
			thistable.tuples(keyname,0);

		}
		if (tablename == "items")
		{
			thistable.tuples(keyname,1);
		}
		if (tablename == "customers")
		{
			thistable.tuples(keyname,2);
		}
	}
	vdatabase.push_back(thistable);
	count++;
}

void collection::letsdothis(string b)					//display for milestone and final
{
	stringstream aa(b);
	stringstream ss(b);
	string line;
	string option; 
	string needtable;
	string chunk;	
 	string empty;
	string Ftable;
	string forproject;
	string bonus;

	getline(aa,forproject,'(');					//Project the specified data
		if (forproject == "PROJECT")
			{
				getline(aa,bonus,'\n');
				letsproject(bonus);
				return;
			}


	if (b == ("DISPLAY()"))							//Display the data
	{
		printdata();
		return;
	}
 	if (b == ("WRITE()"))						//Write in new file
	{
		writedata();
		return;
	}

		getline(ss,option,'(');						//Getting rid of the extra '('
		while(2){												
			getline(ss,chunk, ',');
			empty = empty+chunk;
			getline(ss,needtable,')');
			if (needtable =="spells" || needtable == "items" || needtable == "customers")			//pulls out tablename first
			{
				empty.pop_back();
				if (option== "INSERT")
				{
					letsinsert(empty,needtable);
					return;
				}
			
				else if (option =="UPDATE")
				{
					letsupdate(empty,needtable);
					return;
				}
				
				else if (option == "SELECT")
				{
					letsselect(empty,needtable);
					return;
				}
				
				else if (option == "DELETE")
				{
					letsdelete(empty,needtable);
					return;
				}
			
				else
				{	
					return;
				}
			}
				
			empty = empty + ",";
			empty = empty + needtable;
			empty = empty + ")";
		}
	return;
}

void collection::printdata()									//print the tables
{

	for (int i=0; i < vdatabase.size();i++)
	{
		vdatabase[i].printtable();
		cout <<  endl;
	}
}

void collection::letsinsert(string x, string y)							//insert data 
{
	for (int i =0; i < vdatabase.size(); i++)
	{
		if (y == "spells" && vdatabase[i].GetName()== "spells")
		{
			vdatabase[i].insert(x,0);
		}
		
		if(y == "items" && vdatabase[i].GetName()=="items")
		{
			vdatabase[i].insert(x,1);
		}
		
		if(y == "customers" && vdatabase[i].GetName() == "customers")
		{
			vdatabase[i].insert(x,2);
		}
	}
}

void collection::letsupdate(string x, string y)							//Update data
{
	for (int i=0; i < vdatabase.size(); i++)
	{	
		if (y == "spells" && vdatabase[i].GetName()== "spells")
                {
                        vdatabase[i].update(x,0);
                }

                if(y == "items" && vdatabase[i].GetName()=="items")
                {
                        vdatabase[i].update(x,1);
                }

                if(y == "customers" && vdatabase[i].GetName() == "customers")
                {
                        vdatabase[i].update(x,2);
                }
        }
}

void collection::letsdelete(string x, string y)							//Delete data
{
	for (int a=0; a < vdatabase.size(); a++)
	{	

		if (y == vdatabase[a].GetName())
		{
			vdatabase[a].deleteit(x,y);
			return;
		}
	}
}

void collection::letsselect(string x, string y)							//Select data
{
        for (int a=0; a < vdatabase.size(); a++)
        {

                if (y == vdatabase[a].GetName())
                {
                        vdatabase[a].selectit(x,y);
                        return;
                }
        }
}

void collection::writedata()									//Write data
{
	for (int i=0; i < vdatabase.size();i++)
	{
		vdatabase[i].writeit();
	}
}

void collection::letsproject(string x)								//Project data
{
		stringstream ss(x);
		string empty;
		string chunk;
		string needtable;
		string removebrackets;
		getline(ss,removebrackets,'(');							//Remove brackets
		getline(ss,removebrackets,'(');
		
	
		while (2)
	{
		getline(ss,needtable,',');
		empty = empty + needtable;
		getline(ss,needtable,')');
	
		if (needtable == "spells" || needtable == "customers" || needtable == "items")		//Checking if table name is found
		{	
			getline(ss,chunk,')');
			break;
		}
	
		empty = empty + ",";
		empty = empty + needtable;
		empty = empty + ")";
	}
		chunk.erase(0,1);								//Erasing the comma
		empty.pop_back();								//erasing the close bracket
		
		for (int i =0; i<vdatabase.size();i++)
		{		
		if ((needtable =="spells" && vdatabase[i].GetName() == "spells") || (needtable =="items" && vdatabase[i].GetName() == "items") || (needtable =="customers" && vdatabase[i].GetName() == "customers"))
			{
				vdatabase[i].projectit(empty,chunk);				//Heads to projectit if the above condition is met
			}
		}
}
