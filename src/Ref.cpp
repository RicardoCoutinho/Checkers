#include "Ref.h"

Ref::Ref(int ID, string ids)
{
    setID(ID);
	setIds(ids);
}


int Ref::getID()
{
	return ID;
}
string Ref::getIds()
{
	return ids;
}

void Ref::setID(int ID)
{
	this->ID = ID;
}
void Ref::setIds(string ids)
{
	this->ids = ids;
}

void Ref::print()
{
	cout << "Ref :: ";
    
    cout << "ID: " << getID() << endl;
	cout << "ids: " << getIds() << endl;
}