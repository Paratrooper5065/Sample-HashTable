#ifndef COLLECTION_H
#define COLLECTION_H

class collection
{
private:
vector <table> vdatabase;
int count;


public:

collection();
void readdata(string x);
void letsdothis(string y);
void printdata();
void letsinsert(string x,string y);
void letsupdate(string x,string y);
void letsdelete(string x, string y);
void letsselect(string x, string y);
void letsproject(string x);
void writedata();

};

#endif
