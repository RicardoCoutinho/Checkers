//
//  Appearances.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Appearances.h"

Appearances::Appearances()
{
    appearanceMap.clear();
}
Appearances::~Appearances()
{
    map<string,Appearance*>::iterator it,ite;
    it = appearanceMap.begin();
    ite = appearanceMap.end();
    
    for (; it != ite; it++)
    {
        delete it->second;
    }
}


Appearance* Appearances::getAppearance(string ids)
{
    if (appearanceMap.count(ids))
    {
        return appearanceMap[ids];
    }
        
    return NULL;
}
bool Appearances::addAppearance(Appearance* appearance)
{
    if (this->appearanceMap.find(appearance->getIds()) == this->appearanceMap.end())
    {
        this->appearanceMap.insert(pair<string,Appearance*>(appearance->getIds(),appearance));
        return true;
    }
    
    return false;
}

void Appearances::print()
{
    map<string,Appearance*>::iterator it,ite;
    it = appearanceMap.begin();
    ite = appearanceMap.end();
    
    cout << "--- Appearances ---" << endl;
    for (; it != ite; it++)
    {
        it->second->print();
        cout << endl;
    }
}