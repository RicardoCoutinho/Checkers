//
//  Animations.h
//  CGFLib-1
//

#ifndef __CGFLib_1__Animations__
#define __CGFLib_1__Animations__

#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "Animation.h"

using namespace std;

class Animations {
private:
    map<string,Animation*> AnimationMap;
    
public:
    Animations();
    ~Animations();
    
	map<string,Animation*> getAnimations();
    Animation* getAnimation(string);
    bool addAnimation(Animation*);
    
    void print();
};

#endif /* defined(__CGFLib_1__Animations__) */
