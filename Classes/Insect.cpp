//
// Created by ATON on 11/06/2017.
//

#include "Insect.h"
#include "cocos2d.h"

using namespace cocos2d;

Insect::Insect() {}

Insect::~Insect() {}

Insect* Insect::create()
{
    Insect* pSprite = new Insect();

    if (pSprite && pSprite->initWithFile("insect01.png"))
    {
        pSprite->autorelease();

        pSprite->initOptions();

        //pSprite->addEvents();

        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Insect::initOptions()
{
    // do things here like setTag(), setPosition(), any custom logic.
}


/*
void Insect::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();

        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();

        Insect::touchEvent(touch,p);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Insect::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _point)
{
    CCLOG("touched Insect");
}

*/