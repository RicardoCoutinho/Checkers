#ifndef __CGFLib_1__Ref__
#define __CGFLib_1__Ref__

#include <iostream>
#include <string>

using namespace std;

class Ref{
private:
    int ID;
	string ids;
public:
	Ref(int ID, string ids);
	
    int getID();
	string getIds();
	
    void setID(int);
	void setIds(string);
	
	virtual void print();
};

#endif /* defined(__CGFLib_1__Ref__) */
