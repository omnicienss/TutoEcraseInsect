#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Insect.h"

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void update(float) override;


    //TOUCH screen
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
/*    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
*/

private:
    void setInsect(float pTime );
    void gameOver();
    cocos2d::Point getPointByRandom(int pPosition);

    void speedInsect(float pTime);

private:

    std::vector<Insect*>  m_ListeInsecte;
    std::vector<cocos2d::Sprite*>  m_ListeTache;
    cocos2d::Vec2 m_LastPosition = cocos2d::Vec2(0,0);

    int m_Score=0;
    cocos2d::Label *m_ScoreLabel;
    cocos2d::Label *m_LifeLabel;

    int m_TraitSeparationY=200;
    int m_NbLife=10;

    float m_InsectSpeed=1.0f;
    float m_IntervalSpeedInsect=5.0f;


};

#endif // __HELLOWORLD_SCENE_H__
