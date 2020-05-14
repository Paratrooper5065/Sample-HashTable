#ifndef TABLE_H
#define TABLE_H

class table
{
private:
	vector <string> tables;
	vector <int> size;
	string name;
	string key;
	line tbox[100];						//Setting 100 buckets
	int pos;
	int Nschemes;
	int crows;

public:
table();
 
//Mutators and accessors
void SetName(string n)
	{
		name = n;
	}

string GetName()
	{
		return name;
	}

void SetKey(string k)
	{
		key = k;
	}

string GetKey()
	{
		return key;
	}

void tuples(string x, int y);
void scheme(string s);
bool dohash1(string,int,string);
bool dohash2(string,int,string);
bool dohash3(string,int,string);
int modulohashing(int key);
int directhash(int key);
int midsquare1(int key);
int midsquare(int key);
int mul_stringhash(string key);
void printtable();
int getsize(int s)
	{
		return size[s];
	}
int longest(int a);
void insert(string x,int y);
void update(string x, int y);
bool forupdate1(string x, int y, string z);
bool forupdate2(string x, int y, string z);
bool forupdate3(string x, int y, string z);
void deleteit(string x,string y);
bool fordelete1(string x, int y, string z);
bool fordelete2(string x,int y, string z);
bool fordelete3(string x,int y, string z);
bool stardelete1(string x,int y, string z);
bool stardelete2(string x,int y, string z);
bool stardelete3(string x,int y, string z);
void writeit();
void selectit(string x,string y);
bool forselect1(string x, int y, string z);
bool forselect2(string x, int y, string z);
bool forselect3(string x, int y, string z);
bool starselect1(string x,int y, string z);
bool starselect2(string x,int y, string z);
bool starselect3(string x,int y, string z);
void projectit(string x,string z);
};
#endif
