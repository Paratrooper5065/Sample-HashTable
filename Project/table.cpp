#include<iostream>
using namespace std;
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "line.h"
#include "table.h"

table::table()
	{
		line* tbox = new line[100];
		crows =0;
	}

void table::tuples(string x,int y)					//get tuples
{	
	int a=0;
	line temp;
	string key;
	stringstream ss(x);
	getline(ss,key, '|');
	if (!dohash1(key,y, x) && !dohash2(key,y,x) && !dohash3(key,y,x))
		{ 
			cout<<"ERROR ADDING TUPLE"<<endl;
		 }
}

bool table::dohash1(string d, int h, string x)   			//hashing for spells
{
        if (h==0)                       //For spells
        {
        int bucket = mul_stringhash(d);                         			//Hash function: Multiplicative String Hash
        int i=0;
	int c1 = 1;
	int c2 = 2;
	int probed =0;				                                

        while (i<100)
        {
                if (tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == d)
                        {      
                                return false;
                        }
                if (tbox[bucket].GetTemp() ==0)
                        {

                                tbox[bucket].SetTemp(1);
                                tbox[bucket].addline(x);
                                crows++;
                                return true;
                        }
                	probed = probed +1;									//Collision: Quadratic Probing
			bucket = (mul_stringhash(d) + (c1 * probed) + (c2 * probed * probed) % 100);
			i = i + 1;
        }
        return false;
        }
}


bool table::dohash2(string d,int h, string x)				//hashing for items
{

	if (h ==1)                 //For items
        {                              					 //Hash function: Mid Square Base 10
        int key = stoi(d);
        int i =0;
        int bucket = midsquare(key);
        while (i<100)
        {                if(tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == d)
                {                     
                        return false;
                }

                if (tbox[bucket].GetTemp() == 0)
                {
                                tbox[bucket].SetTemp(1);
                                tbox[bucket].addline(x);
                                crows++;
                                return true;
                }
                bucket = modulohashing(key)*i;					//Collision: Double hashing
		bucket = bucket + midsquare(key);
		bucket = bucket % 100;
                i= i+1;
        }
                        return false;

	}
}

bool table::dohash3(string d, int h, string x)				//hashing for customers
{

	if (h ==2)                 //For customers
        {
        int key = stoi(d);
        int bucket = modulohashing(key);                          		 //Hash function: Modulo hashing
        int i =0;

        while (i < 100)
        {
                if(tbox[bucket].GetTemp() ==1 && tbox[bucket].getlline(0) ==d)
                {
                        return false;
                }

                if (tbox[bucket].GetTemp() == 0)
                {
                                tbox[bucket].SetTemp(1);
                                tbox[bucket].addline(x);
                                crows++;
                                return true;

                }
                bucket = (bucket+1)%100;                                        //Collision linear probing
                i++;
        }
        return false;
        }
	
}
													//FORMULAS FOR DIFFERENT TYPES OF HASHING
int table::modulohashing(int key)
{
	return key%100;
}

int table::directhash(int key)
{
	return key;
}

int table::midsquare1 (int key)
{
	return key%100;
	int R=1;
	int position = key * key;
	string sposition = to_string(position);
	int temp = floor(sposition.size()/2);
	string final = sposition.substr(temp,R);
	return stoi(final) % 100;
	
}

int table::midsquare (int key)
{
	return key%100;
	int R=2;
	int position = key * key;
	string sposition = to_string(position);
	int temp= floor(sposition.size()/2);
	string final = sposition.substr(temp,R);
	return stoi(final) % 100;
}

int table::mul_stringhash(string key)
{
	int position = 0;
		for (char c : key)
		{
			position = (position*2)+c;
		}
	return position%100;
}

void table::scheme(string s)								//adding the schemes
{
	int a=0;
	string tuple;
	stringstream ss(s);
	while (getline(ss,tuple,','))
	{
		tables.push_back(tuple);
		size.push_back(tuple.length());
		a++;
	}
	Nschemes =a;
}

void table::printtable()								//set width and print it
{
	for (int t=0; t < Nschemes; t++)
	{
		int temp=longest(t);
		cout << setw(temp+5) << tables[t];
	}
	cout << endl;
	
	for (int i=0; i<100;i++)
	{
		if(tbox[i].GetTemp() ==1)
		{
		for (int j=0; j<Nschemes;j++)
		{
			int temp = longest(j);
			cout << setw(temp+5) << tbox[i].getlline(j);	
		}
		cout << endl;
		}
	}
}

int table::longest(int a)						//find the longest length in column
{
	int updated =0;
	for (int i =0;i<100;i++)
	{
		if(tbox[i].GetTemp()==1)
		{
	int len = tbox[i].getlline(a).length();
	if (len > updated)
		{
			 updated = len;
		}
		}
	}
	return updated;
}

void table::insert(string x, int y)
{
int position;
x.erase(0,1);									//Removing the first bracket
stringstream ss(x);
string key;
string tuple;

getline(ss,key,'|');										
if (y==0)										//inserting in spells table
{
	if (!dohash1(key,0,x))
	{
		cout << "Failed to insert (" << x << ") into " << name << endl;
		return;
	}

	else 
	{
		cout << "Inserted (" << x << ") into " << name << endl;
	}
}

if (y==1)										//inserting in items table
{	
        if (!dohash2(key,1,x))
        {
                cout << "Failed to insert (" << x << ") into " << name << endl;
                return;
        }

	else
	{
		cout << "Inserted (" << x << ") into " << name << endl;
	}	
}

if (y==2)										//inserting in customers table
{	
        if (!dohash3(key,2,x))
        {
                cout << "Failed to insert (" << x << ") into " << name << endl;
                return;
        }


	else

	{
		cout << "Inserted (" << x << ") into " << name << endl;
	}
}

}

void table::update(string x, int y)
{
int position;
x.erase(0,1);                                                                   //Removing the first bracket
stringstream ss(x);
string key;
string tuple;

getline(ss,key,'|');
if (y==0)                                                                               //updating in spells table
{
        if (!forupdate1(key,0,x))
        {
                cout << "Failed to update (" << x << ") in " << name << endl;
                return;
        }

        else
        {
    
	       cout << "Updated (" << x << ") in " << name << endl;
        }
}

if (y==1)                                                                               //Updating in items table
{
        if (!forupdate2(key,1,x))
        {
                cout << "Failed to update (" << x << ") in " << name << endl;
                return;
        }

        else
        {
                cout << "Updated (" << x << ") in " << name << endl;
        }
}

if (y==2)                                                                               //Updating in customers table
{
        if (!forupdate3(key,2,x))
        {
                cout << "Failed to update (" << x << ") in " << name << endl;
                return;
        }


        else

        {
                cout << "Updated (" << x << ") in " << name << endl;
        }
}
}

bool table::forupdate1(string x,int y, string z)
{
if (y==0) 		                      //For spells
        {
        int bucket = mul_stringhash(x);                        
        int i=0;
        int c1 = 1;
        int c2 = 2;
        int probed =0;                                                         

        while (i<100)
        {
                if (tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == x)
                        {
			tbox[bucket].removeline();									//Removing the old data
			tbox[bucket].addline(z);									//Updating with new one
                              return true;
                        }
               
                        probed = probed +1;
                        bucket = (mul_stringhash(x) + (c1 * probed) + (c2 * probed * probed) % 100);
                        i = i + 1;
        }
        return false;
        }
}

bool table::forupdate2(string x,int y,string z)
{
if (y ==1) 								                //For items
        {                            
	int key = stoi(x);                                   
        int i =0;
        int bucket = midsquare(key);

        while (i<100)
        {
                if(tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == x)
                {
			tbox[bucket].removeline();									//Removing the old data
			tbox[bucket].addline(z);									//Updating with new one
                        return true;
                }
                bucket = modulohashing(key)*i;
                bucket = bucket + midsquare(key);
                bucket = bucket % 100;
                i= i+1;
       }
                        return false;

        }
}

bool table::forupdate3(string x, int y, string z)
{
if (y ==2)                							 //For customers
        {
        int key = stoi(x);
        int bucket = modulohashing(key);                                    
        int i =0;
   
        while (i < 100)
        {
                if(tbox[bucket].GetTemp() ==1 && tbox[bucket].getlline(0) ==x)
                {
			tbox[bucket].removeline();									//Removing the old data
			tbox[bucket].addline(z);									//Updating with the new one
                        return true;
                }
    
                bucket = (bucket+1)%100;                                       
                i++;
        }
        return false;
        }

}

void table::deleteit(string x,string y)
{
	x.erase(0,1);
	stringstream ss(x);
	int position;
	string key;
	string rest;
	line templine;
	getline(ss,key,'|');
	templine.addline(key);				//To see if we have "*"
	
	if (key == "*")												//If key is not specified
	{
		
			if ( y == "spells")
			{
				if (!stardelete1(key,0,x))
				{
					cout << "Failed to delete (" << x << ")  " << endl;
					return;
				}
			else
				{
					return;
				}
					return;
			}
		

			 if ( y == "items")
                        {
                                if (!stardelete2(key,1,x))
                                {
                                        cout << "Failed to delete (" << x << ") " << endl;
                                        return;
                                }
                        else
          			{
                                        return;
                                }
                                        return;
                        }

			 if ( y == "customers")
                        {
                                if (!stardelete3(key,2,x))
                                {
                                        cout << "Failed to delete (" << x << ") " << endl;
                                        return;
                                }
                        else
                                {                                     
                                        return;
                                }
                                        return;
                        }
			

	}
													//Search for key directly if it is given	
	if(y == "spells")
	{
		   if (!fordelete1(key,0,x))
        		{
                		cout << "Failed to delete (" << x << ") " << endl;
                		return;
       			 }

        	  else
        		{
                	cout << "Deleted (" << x << ") from " << name << endl;
			return;
       			 }
	}
	
	if (y=="items")
	{	
		if(!fordelete2(key,1,x))
			{
				cout << "Failed to delete (" << x << ") " << endl;
				return;
			}
			
		else
			{
				cout << "Deleted (" << x << ") from " << name << endl;
				return;
			}
	}
	
	if (y=="customers")
        {       
                if(!fordelete3(key,2,x))
                        {
                                cout << "Failed to delete (" << x << ") "<< endl;
                                return;
                        }

                else
                        {       
                                cout << "Deleted (" << x << ") from " << name << endl;
                                return;
                        }
        }

}

bool table::stardelete1(string x, int y, string z)								//Checking in spells table when * is given
{
if (y == 0)
{
        line templine;
        stringstream ss(z);
        string key;
        getline(ss,key,'|');
        templine.addline(key);
        bool full= false;
        int position;
        bool starornot;
        int s =0;
	int check =0;
	int count =0;
        while (getline(ss,key,'|'))
        {
                templine.addline(key);
        }

        for (int i=0;i < 100;i++)
        {
		
                starornot =false;
                if (tbox[i].GetTemp() == 1)
                {
                        s=0;
                        do
                        {		
                                if (templine.getlline(s) == "*" || (tbox[i].getlline(s)==templine.getlline(s)))			//Lets * pass through
                                {
                                        starornot = true;
                                }

                                else
                                {
                                        starornot = false;
                                }
                                s++;
			
                        }
                        while (starornot == true && s < Nschemes);
                }
	
        if (starornot == true)
                {    
			check++;
			if (count == 0)
			{
				cout << "Deleted ";
				count++;
			}
			cout <<"(";
			for (int k =0; k< Nschemes; k++)
			{
				cout << tbox[i].getlline(k) << '|'; 
			}
			cout <<"\b";
			cout <<  ") " << endl;
			tbox[i].removeline();											//Deleting the matched line
			tbox[i].SetTemp(0);											//Setting to 0, indicating as empty
			crows--;												//Reduce rows after deleting
			                
                }
	}
	
	if (check >1)
		{	
			return true;
		}

	if (check ==0)
		{
	
		        return false;
		}
	

}
}
bool table::stardelete2(string x, int y, string z)										//Checking in items table when * is given
{
if (y == 1)
{
        line templine;
        stringstream ss(z);
        string key;
        getline(ss,key,'|');
        templine.addline(key);
        bool full= false;
        int position;
        bool starornot;
        int s =0;
	int check =0;
	int count = 0;
        while (getline(ss,key,'|'))
        {
                templine.addline(key);
        }

        for (int i=0;i < 100;i++)
        {
		
                starornot =false;
                if (tbox[i].GetTemp() == 1)
                {
                        s=0;
                        do
                        {		
                                if (templine.getlline(s) == "*" || (tbox[i].getlline(s)==templine.getlline(s)))				//Lets * pass through
                                {
                                        starornot = true;
                                }

                                else
                                {
                                        starornot = false;
                                }
                                s++;
			
                        }
                        while (starornot == true && s < Nschemes);
                }
	
        if (starornot == true)
                {    
			check++;
			if (count ==0)
			{
				cout << "Deleted ";
				count++;
			}
			cout << "(";
			for (int k =0; k< Nschemes; k++)
			{
				cout  << tbox[i].getlline(k) << '|'; 
			}
			cout <<"\b" ;
			cout <<  ") "  << endl;
			tbox[i].removeline();												//Deleting the matched line
			tbox[i].SetTemp(0);												//Setting value to 0, indicating empty
			crows--;													//Reducing number of rows after deleting
			                
                }
	}
	
	if (check >1)
		{	
			return true;
		}

	if (check ==0)
		{
		
		        return false;
		}
	

}
}



bool table::stardelete3(string x, int y, string z)								//Checking in customerss table when * is given
{
if (y == 2)
{
        line templine;
        stringstream ss(z);
        string key;
        getline(ss,key,'|');
        templine.addline(key);
        bool full= false;
        int position;
        bool starornot;
        int s =0;
	int check =0;
	int  count = 0;
        while (getline(ss,key,'|'))
        {
                templine.addline(key);
        }

        for (int i=0;i < 100;i++)
        {
		
                starornot =false;
                if (tbox[i].GetTemp() == 1)
                {
                        s=0;
                        do
                        {		
                                if (templine.getlline(s) == "*" || (tbox[i].getlline(s)==templine.getlline(s)))			//Lets * pass through
                                {
                                        starornot = true;
                                }

                                else
                                {
                                        starornot = false;
                                }
                                s++;
			
                        }
                        while (starornot == true && s < Nschemes);
                }
	
        if (starornot == true)
                {    
			check++;
			if (count ==0)
				{
					cout << "Deleted ";
					count++;
				}
			cout << "(";
			for (int k =0; k< Nschemes; k++)
			{
				cout  << tbox[i].getlline(k) << '|'; 
			}
			cout <<"\b";
			cout <<  ") " << endl;
			
			tbox[i].removeline();											//Deleting the matched line
			tbox[i].SetTemp(0);											//Setting value to 0, indicating it is empty
			crows--;												//Reducing number of rows after deleting
			                
                }
	}
	
	if (check >1)
		{	
			return true;
		}

	if (check ==0)
		{
			
		        return false;
		}
	

}
}

bool table::fordelete1(string x,int y, string z)
{
if (y==0)                                     //For spells
        {
        long bucket = mul_stringhash(x);
        int i=0;
        int c1 = 1;
        int c2 = 2;
        int probed =0;

        while (i<100)										
        {
                if (tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == x)
                        {
                        tbox[bucket].removeline();								//Remove line when found
			tbox[bucket].SetTemp(0);
                        return true;
                        }

                        probed = probed +1;									//If not, search in another bucket
                        bucket = (mul_stringhash(x) + (c1 * probed) + (c2 * probed * probed) % 100);
                        i = i + 1;
			
        }
	
       		 return false;
        }
}

bool table::fordelete2(string x,int y, string z)
{
if (y ==1)                                                                              //For items
        {

        int key = stoi(x);
        int i =0;
        int bucket = midsquare(key);

        while (i<100)
        {
                if(tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == x)
                {
                        tbox[bucket].removeline();								//Remove line when found
                        tbox[bucket].SetTemp(0);								
                        return true;
                }												//If not, search in another bucket
                bucket = modulohashing(key)*i;
                bucket = bucket + midsquare(key);
                bucket = bucket % 100;
                i= i+1;
       }
                        return false;

        }
}

bool table::fordelete3(string x, int y, string z)
{
if (y ==2)                                                                       //For customers
        {
        int key = stoi(x);
        int bucket = modulohashing(key);
        int i =0;
        
        while (i < 100)
        {
                if(tbox[bucket].GetTemp() ==1 && tbox[bucket].getlline(0) ==x)
                {
                        tbox[bucket].removeline();								//Remove line when found
                        tbox[bucket].SetTemp(0);								
                        return true;
                }

                bucket = (bucket+1)%100;									//If not, search in another bucket
                i++;
        }
        return false;
        }

}

//SELECT

void table::selectit(string x,string y)
{
    x.erase(0,1);
    stringstream ss(x);
    int position;
    string key;
    string rest;
    line templine;
    getline(ss,key,'|');
    templine.addline(key);                //To see if we have "*"
    
    if (key == "*")                                                //If key is not specified
    {
        
        if ( y == "spells")
        {
            if (!starselect1(key,0,x))
            {
                cout << "No entries match query (" << x << ")" << endl;
                return;
            }
            else
            {
                
                return;
            }
            return;
        }
        
        
        if ( y == "items")
        {
            if (!starselect2(key,1,x))
            {
                cout << "No entries match query (" << x << ")"  << endl;
                return;
            }
            else
            {
               
                return;
            }
            return;
        }
        
        if ( y == "customers")
        {
            if (!starselect3(key,2,x))
            {
                cout << "No entries match query (" << x << ")" << endl;
                return;
            }
            else
            {
                return;
            }
            return;
        }
        
    }
    //Search for key directly if it is given
    if(y == "spells")
    {
        if (!forselect1(key,0,x))
        {
            cout << "No entires match query (" << x << ")" << endl;
            return;
        }
        
        else
        {
            cout << "Found (" << x << ")" << endl;
            return;
        }
    }
    
    if (y=="items")
    {
        if(!forselect2(key,1,x))
        {
            cout << "No entries match query (" << x << ")"  << endl;
            return;
        }
        
        else
        {
            cout << "Found (" << x << ")"  << endl;
            return;
        }
    }
    
    if (y=="customers")
    {
        if(!forselect3(key,2,x))
        {
            cout << "No entries match query (" << x << ")" << endl;
	cout << "TESTING ! " << endl;
            return;
        }
        
        else
        {
            cout << "Found (" << x << ")"<< endl;
            return;
        }
    }
    
}

bool table::starselect1(string x, int y, string z)
{
    if (y == 0)
    {
        line templine;
        stringstream ss(z);
        string key;
        getline(ss,key,'|');
        templine.addline(key);
        bool full= false;
        int position;
        bool starornot;
        int s =0;
        int check =0;
	int count =0;
        while (getline(ss,key,'|'))
        {
            templine.addline(key);
        }
        
        for (int i=0;i < 100;i++)
        {
            
            starornot =false;
            if (tbox[i].GetTemp() == 1)
            {
                s=0;
                do
                {
                    if (templine.getlline(s) == "*" || (tbox[i].getlline(s)==templine.getlline(s)))			//Lets * pass through
                    {
                        starornot = true;
                    }
                    
                    else
                    {
                        starornot = false;
                    }
                    s++;
                    
                }
                while (starornot == true && s < Nschemes);
            }
            
            if (starornot == true)
            {
                check++;
		if (count ==0)
		{
               	 cout << "Found ";
		 count++;
                }
		for (int k =0; k< Nschemes; k++)
                {
                    cout<<"(" << tbox[i].getlline(k) << '|';							//Prints out when found
                }
                cout <<  ")"  << endl;           
            }
        }
        
        if (check >1)
        {
            return true;
        }
        
        if (check ==0)
        {
            
            return false;
        }
        
        
    }
}
bool table::starselect2(string x, int y, string z)
{
    if (y == 1)
    {
        line templine;
        stringstream ss(z);
        string key;
        getline(ss,key,'|');
        templine.addline(key);
        bool full= false;
        int position;
        bool starornot;
        int s =0;
        int check =0;
	int count =0;
        while (getline(ss,key,'|'))
        {
            templine.addline(key);
        }
        
        for (int i=0;i < 100;i++)
        {
            
            starornot =false;
            if (tbox[i].GetTemp() == 1)
            {
                s=0;
                do
                {
                    if (templine.getlline(s) == "*" || (tbox[i].getlline(s)==templine.getlline(s)))			//Lets * pass through
                    {
                        starornot = true;
                    }
                    
                    else
                    {
                        starornot = false;
                    }
                    s++;
                    
                }
                while (starornot == true && s < Nschemes);
            }
            
            if (starornot == true)
            {
                check++;
		if (count ==0)
			{
	                cout << "Found ";
			count++;
			}
		cout <<"(";
                for (int k =0; k< Nschemes; k++)
                {
                    cout  << tbox[i].getlline(k) << '|';								//Prints out when found
                }
		cout <<"\b";
                cout <<  ")" << endl;
            }
        }
        
        if (check >1)
        {
            return true;
        }
        
        if (check ==0)
        {
            
            return false;
        }
        
        
    }
}



bool table::starselect3(string x, int y, string z)
{
    if (y == 2)
    {
        line templine;
        stringstream ss(z);
        string key;
        getline(ss,key,'|');
        templine.addline(key);
        bool full= false;
        int position;
        bool starornot;
        int s =0;
        int check =0;
	int count = 0;
        while (getline(ss,key,'|'))
        {
            templine.addline(key);
        }
        
        for (int i=0;i < 100;i++)
        {
            
            starornot =false;
            if (tbox[i].GetTemp() == 1)
            {
                s=0;
                do
                {
                    if (templine.getlline(s) == "*" || (tbox[i].getlline(s)==templine.getlline(s)))			//Lets * pass through
                    {
                        starornot = true;
                    }
                    
                    else
                    {
                        starornot = false;
                    }
                    s++;
                    
                }
                while (starornot == true && s < Nschemes);
            }
            
            if (starornot == true)
            {
                check++;
		if (count ==0)
		{
        	        cout << "Found ";
			count++;
		}
		cout << "(";
                for (int k =0; k< Nschemes; k++)
                {
                    cout<< tbox[i].getlline(k) << '|';									//Prints out when found
                }
		cout << "\b";
                cout <<  ")" << endl;      
            }
        }
        
        if (check >1)
        {
            return true;
        }
        
        if (check ==0)
        {
            
            return false;
        }
        
        
    }
}

bool table::forselect1(string x,int y, string z)
{
    if (y==0)                                     //For spells
    {
        long bucket = mul_stringhash(x);
        int i=0;
        int c1 = 1;
        int c2 = 2;
        int probed =0;
        
        while (i<100)                                       
        {
            if (tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == x)
            {	
		   return true;											//Returns true and prints out when found
            }
            
            probed = probed +1;											//Will check another bucket if not found
            bucket = (mul_stringhash(x) + (c1 * probed) + (c2 * probed * probed) % 100);
            i = i + 1;
            
        }
        
        return false;
    }
}

bool table::forselect2(string x,int y, string z)
{
    if (y ==1)                                                                              //For items
    {
        
        int key = stoi(x);
        int i =0;
        int bucket = midsquare(key);
        
        while (i<100)
        {
            cout << key << endl;
            if(tbox[bucket].GetTemp()==1 && tbox[bucket].getlline(0) == x)
            {
                return true;											//Returns true and prints out when found
            }
            bucket = modulohashing(key)*i;									//Will check another bucket if not found
            bucket = bucket + midsquare(key);
            bucket = bucket % 100;											
            i= i+1;
        }
        return false;
        
    }
}

bool table::forselect3(string x, int y, string z)
{
    if (y ==2)                                                                       //For customers
    {
        int key = stoi(x);
        int bucket = directhash(key);
        int i =0;
       
        while (i < 100)
        {
            if(tbox[bucket].GetTemp() ==1 && tbox[bucket].getlline(0) ==x)
            {
                return true;											//Returns true and prints out when found
            }
            
            bucket = (bucket+1)%100;										//Will check another bucket if not found
            i++;
        }
        return false;
    }
    
}


void table::writeit()
{	
	ifstream Infile;												//Write in a new file
	ofstream Newfile;	
	if (name == "spells")
		{
			Newfile.open("spellswritefile.txt");
		}
	
	if (name == "items")
		{
			Newfile.open("itemswritefile.txt");
		}
	
	if (name == "customers")
		{
			Newfile.open("customerswritefile.txt");
		}

	Newfile << key << endl;					//Printing just the key

	for ( int a = 0; a < Nschemes;a++)
	{
		Newfile << tables[a] << ',';			//Printing the tuples
	}
	Newfile << '\b'; 					//Using \b to eliminate the last comma(,) 
	Newfile << " ";
	Newfile << endl;

	for ( int b = 0; b < 100; b++)
	{
		if (tbox[b].GetTemp() == 1)
		{
			for (int c=0; c < Nschemes; c++)
			{
			Newfile << tbox[b].getlline(c) << '|';			
			}
			Newfile << '\b';				//Removing the '|' after the last element
			Newfile << " ";	
			Newfile << endl;
		}
	}
	Newfile.close();
}

void table::projectit(string x, string z)						//BONUS: PROJET((
{
	line templine;
	int counter=0;
	bool TF = false;	
	bool check;
	string key;
	stringstream aa(z);
	stringstream ss(x);
	vector <int> projectout;							//Temporary vector mostly use for comparision
	
	while (getline(ss,key,'|'))
	{
		templine.addline(key);
		
	}

	while(getline(aa,key,'|'))
	{
		for (int i=0; i<Nschemes; i++)
		{	
			if (key==tables[i])
			{
				projectout.push_back(i);
			}
		}
	}

	for (int j=0;j<100;j++)
	{
		check = false;
		if (tbox[j].GetTemp() == 1)
		{
			int b=0;
			do{
			if ((tbox[j].getlline(b) == templine.getlline(b)) ||templine.getlline(b)=="*")			//Comparision section
			{
				check = true;
			}
		
			else 
			{	
				check = false;
			}
			b++;
		}while (check == true && b < Nschemes);
		
		}
	
	if (check == true)
	{	
		TF =true;
		if (counter==0)
		{	
				
			for (int e=0;e < projectout.size();e++)								//Prints the headings
			{
				int only = projectout[e];
				int l = longest(only);									//Width is set for the longest integer	
				cout << setw(l+5) << tables[only];						
			}
				cout << endl;
		counter++;
		}

		  for (int c=0;c < projectout.size(); c++)
                        {
				int sonly = projectout[c];
                                int m=longest(sonly);
                                cout << setw(m+5) << tbox[j].getlline(sonly) ;
                        }
		cout << endl;
	}
		
	}
		cout << endl;
}
		
	
