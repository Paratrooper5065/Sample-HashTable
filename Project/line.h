#ifndef LINE_H
#define LINE_H

class line
{

private:
int temporary;
vector <string> lline;

public:
line();
void addline(string x);
string getlline(int a);
void SetTemp(int t);
int GetTemp();
void removeline();
};

#endif
