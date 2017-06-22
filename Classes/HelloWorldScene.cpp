#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include <string>

#include "Insect.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    __String *myText = __String::createWithFormat("Score: %d", m_Score);
    m_ScoreLabel = Label::createWithTTF(myText->getCString(), "fonts/Marker Felt.ttf", 48);
    m_ScoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - m_ScoreLabel->getContentSize().height));
    this->addChild(m_ScoreLabel, 5);


    //
    __String *myTextLife = __String::createWithFormat("Vie: %d", m_NbLife);

    m_LifeLabel = Label::createWithTTF(myTextLife->getCString(), "fonts/Marker Felt.ttf", 48);
    m_LifeLabel->setPosition(Vec2(origin.x + visibleSize.width-200,origin.y + visibleSize.height - m_LifeLabel->getContentSize().height));
    this->addChild(m_LifeLabel, 5);



/*
    //Label text "Total"
    __String *myText = __String::createWithFormat("%s", "Total");
    cocos2d::Label *myLabel = Label::createWithTTF(myText->getCString(), "fonts/tarzananarrow.ttf", 36);  //visibleSize.height * 0.03);
    myLabel->setColor(Color3B::WHITE);
    myLabel->setPosition(Point(50, visibleSize.height - 25));
    this->addChild(myLabel, 10);
 */


    // Ajout fond
    auto sprite = Sprite::create("bg01.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

  //Trait de séparation pour game over
    auto draw = DrawNode::create();
    draw->drawLine(Point(0, m_TraitSeparationY), Point(visibleSize.width + origin.x, m_TraitSeparationY), Color4F::RED);
    addChild(draw,5);

    //
    //Evenement sur le touché
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
/*    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    //Game loop
    this->scheduleUpdate();

    //
    this->schedule(schedule_selector(HelloWorld::speedInsect), m_IntervalSpeedInsect);


/*

    auto draw = DrawNode::create();
    addChild(draw, 10);

    auto s = Director::getInstance()->getWinSize();
    draw->drawQuadBezier(Vec2(0, s.height), Vec2(s.width/2, s.height/2), Vec2(s.width, s.height), 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    draw->drawCubicBezier(VisibleRect::center(), Vec2(VisibleRect::center().x+30,VisibleRect::center().y+50), Vec2(VisibleRect::center().x+60,VisibleRect::center().y-50),VisibleRect::right(),100, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

*/

    return true;
}

void HelloWorld::speedInsect(float pTime)
{
    if(m_InsectSpeed<0.25f) {
        m_InsectSpeed=0.25f;
        return;
    }

    this->unschedule(schedule_selector(HelloWorld::setInsect));

    m_InsectSpeed=m_InsectSpeed-0.10f;
    this->schedule(schedule_selector(HelloWorld::setInsect), m_InsectSpeed);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::setInsect(float pTime)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // add "HelloWorld" splash screen"
    Insect* sprite = Insect::create();

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y +sprite->getContentSize().height));
    sprite->setPosition(HelloWorld::getPointByRandom(0));


    m_ListeInsecte.push_back(sprite);

    // add the sprite as a child to this layer
    this->addChild(sprite, 3);


    ccBezierConfig bezier;
    bezier.controlPoint_1=HelloWorld::getPointByRandom(1);
    bezier.controlPoint_2=HelloWorld::getPointByRandom(1);
    bezier.endPosition=HelloWorld::getPointByRandom(2);
    auto actionBezier = BezierTo::create(3,bezier);
    //
    auto ActionMoveTo = MoveTo::create(0.5f, HelloWorld::getPointByRandom(3));

    auto attenteSec = DelayTime::create(1.0f);

    auto seq = Sequence::create(actionBezier, attenteSec, ActionMoveTo, nullptr);

    //auto seq = Spawn::createWithTwoActions(actionBezier, ActionMoveTo);

    sprite->runAction(seq);


    //rotation du sprite
/*    Point vector = m_LastPosition -sprite->getPosition() ;
    sprite->setRotation(atan2(vector.x, vector.y) * 180 / M_PI);
    m_LastPosition = sprite->getPosition();
*/
}



/*
 * 0 = Haut
 * 1=nimporte ou
 * 2=bas
 */
Point HelloWorld::getPointByRandom(int pPosition)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Point poinDeRetour;

    //Haut
    if(pPosition==0) {
        int min = 0;
        int max = visibleSize.width+origin.x;
        int randomX = rand() % (max - min) + min;
        poinDeRetour =Point(randomX,visibleSize.height+origin.x);
    }

    //N'importe ou
    if(pPosition==1)
        poinDeRetour =Point(rand()%((int)(visibleSize.width+origin.x)),rand()%((int)(visibleSize.height+origin.y)));

    //Bas
    if(pPosition==2) {
        int min = 0;
        int max = visibleSize.width+origin.x;
        int randomX = rand() % (max - min) + min;
        poinDeRetour =Point(randomX,100);
    }

    //Sortir de l'ecran
    if(pPosition==3) {
        int min = 0;
        int max = visibleSize.width+origin.x;
        int randomX = rand() % (max - min) + min;
        poinDeRetour =Point(randomX,-200);
    }

    return poinDeRetour;
}

void HelloWorld::update(float )
{

    //Test si on est en situation de GAMEOVER pour
    for(Insect* sprite : m_ListeInsecte) {
        if (sprite->getPositionY() < m_TraitSeparationY)
        {
            //On decompte une sprite une seulle fois
            if (!sprite->getIsFinalPosition()) {

                //Marque l'insecte comme arrive en bas
                sprite->setIsFinalPosition(true);


                if (m_NbLife > 0) {
                    m_NbLife--;
                    //Affichage des vies
                    __String *myText = __String::createWithFormat("Vie: %d", m_NbLife);
                    m_LifeLabel->setString(myText->getCString());


                } else {
                    //Game over
                    gameOver();
                    return;
                }
            } else{
                //A priori on ne fait rien??!!
            }
        }
    }


/*    for(int i=0;i<m_ListeInsecte.size()-1;i++)
    {
        m_ListeInsecte.at(i) = m_ListeInsecte.at(i+1);

        m_ListeInsecte.at(i)->setPosition(m_ListeInsecte.at(i+1)->getPosition());

    }
*/
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{

    Vec2 location=touch->getLocation();

    std::vector<Insect*> toDel;

    bool myTouche=false;
    for(Insect* sprite : m_ListeInsecte)
    {

            if(!myTouche && sprite->getBoundingBox().containsPoint(location))
            {
            toDel.push_back(sprite);

            myTouche=true;

            //Ajoute tache
            auto spriteTache = Sprite::create("tache01.png");
            // position the sprite on the center of the screen
            spriteTache->setPosition(sprite->getPosition());
            // add the sprite as a child to this layer
            this->addChild(spriteTache, 2);

            m_ListeTache.push_back(spriteTache);


            //Augmentation du score
            m_Score++;
            __String *myText = __String::createWithFormat("Score: %d", m_Score);
            m_ScoreLabel->setString(myText->getCString()); //

        }

        //Les insects sorti de l'écran
        if(sprite->getPositionY()<0)
        {
            toDel.push_back(sprite);

            //break;
        }


        //rotation du sprite
 /*       Point vector = m_LastPosition -sprite->getPosition() ;
        sprite->setRotation(atan2(vector.x, vector.y) * 180 / M_PI);
        m_LastPosition = sprite->getPosition();
*/


    }

    //Delete Insects
    for(Insect* sprite : toDel)
    {
        auto removeSelf = RemoveSelf::create();
        auto wait = DelayTime::create(0.35f);
        auto waitFadeout = DelayTime::create(1.0f);
        auto fadeOut = FadeOut::create(2.0f);
        auto TintByAction=TintBy::create(0.5f,-100,-100,-100);
        sprite->stopAllActions();
        sprite->runAction(Sequence::create(TintByAction,waitFadeout,fadeOut,wait, removeSelf, NULL));

        //sprite->removeFromParentAndCleanup(true);

        m_ListeInsecte.erase(std::remove(m_ListeInsecte.begin(), m_ListeInsecte.end(), sprite ), m_ListeInsecte.end());
    }

    //Delete Taches
    for(Sprite* sprite : m_ListeTache)
    {

        auto removeSelf = RemoveSelf::create();
        auto wait = DelayTime::create(0.35f);
        auto fadeOut = FadeOut::create(2.0f);
        sprite->runAction(Sequence::create(fadeOut,wait, removeSelf, NULL));


        //sprite->removeFromParentAndCleanup(true);
        m_ListeTache.erase(std::remove(m_ListeTache.begin(), m_ListeTache.end(), sprite ), m_ListeTache.end());
    }
}

void HelloWorld::gameOver()
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

//55555555555555555DDDDDDDDDDDDDDDDDDDDssssssssssssssssssssssssss