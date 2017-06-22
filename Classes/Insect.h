//
// Created by ATON on 11/06/2017.
//

#ifndef __INSECT_H__
#define __INSECT_H__

#include "cocos2d.h"

class Insect : public cocos2d::Sprite
{

public:
    Insect();
    ~Insect();
    static Insect* create();

    void initOptions();

    //void addEvents();
   // void touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _p);

    //Savoir si l'insecte a ete marque comme en position de game over ie en bas de l'ecran
    void setIsFinalPosition(bool pIsFinal) {isPositionGameOver=pIsFinal;}
    bool getIsFinalPosition(){ return isPositionGameOver;}

private:

    bool isPositionGameOver= false;

};


#endif //__INSECT_H__
