//
//  Appearances.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Appearances__
#define __CGFLib_1__Appearances__

#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "Appearance.h"

using namespace std;

class Appearances {
private:
    map<string,Appearance*> appearanceMap;
    
public:
    Appearances();
    ~Appearances();
    
    Appearance* getAppearance(string);
    bool addAppearance(Appearance*);
    
    void print();
};


#endif /* defined(__CGFLib_1__Appearances__) */