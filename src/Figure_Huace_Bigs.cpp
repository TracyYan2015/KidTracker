//
//  DialogLayer.cpp
//  ModalDialogDemo
//
//  Created by Tom on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

//场景视图

#include "Figure_Huace_Bigs.h"

Figure_Huace_Bigs::Figure_Huace_Bigs()
{
}

Figure_Huace_Bigs::~Figure_Huace_Bigs()
{
}

void Figure_Huace_Bigs::setSprite(cocos2d::Sprite *s)
{
    _stickfigure_laoshu_big = s;
}

bool Figure_Huace_Bigs::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!LayerColor::initWithColor(Color4B(0, 0, 0, 125)));
        //125应该是不透明度，，，前面的三个0分别代表了RGB
        //125 is the opacity
        this->initDialog();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void Figure_Huace_Bigs::initDialog()
{
    //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //CCLabelTTF *label = CCLabelTTF::initWithString("Are u sure exit?", "", 64);
    //label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    //this->addChild(label);
    
    //CCMenuItemFont *okMenuItem = SizeFromString("OK", this, menu_selector(DialogLayer::okMenuItemCallback));
    //okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));
    
    //CCMenuItemFont *cancelMenuItem = CCMenuItemFont::itemFromString("Cancel", this, menu_selector(DialogLayer::cancelMenuItemCallback));
    //cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));
    
    //m_pMenu = CCMenu::menuWithItems(okMenuItem, cancelMenuItem, NULL);
    //m_pMenu->setPosition(CCPointZero);
    //this->addChild(m_pMenu);
    CCSize visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*
    auto _fengmian_bjb = Sprite::create("fengmian_dhk_bjb.png");
    //_fengmian_dhk->ignoreAnchorPointForPosition(false);
    _fengmian_bjb->setAnchorPoint(Vec2(0,1));
    _fengmian_bjb->setPosition(Vec2(Xdim*1446/2048, visibleSize.height));
    this->addChild(_fengmian_bjb, 51);
    */
    _button_guanbi_red = Sprite::create("button_guanbi_red.png");
    //_fengmian_dhk->ignoreAnchorPointForPosition(false);
    _button_guanbi_red->setAnchorPoint(Vec2(0,1));
    _button_guanbi_red->setPosition(Vec2(Xdim*1446/2048, visibleSize.height-Ydim*990/1536));
    this->addChild(_button_guanbi_red, 1);
    
    //_stickfigure_laoshu_big = Sprite::create(“stickFigureName”);
    //_stickfigure_laoshu_big = Sprite::create(stickFigureName);
    //_stickfigure_laoshu_big ＝ Sprite::create();
    
    //_fengmian_dhk->ignoreAnchorPointForPosition(false);
    //_stickfigure_laoshu_big->setAnchorPoint(Vec2(0,1));
    //_stickfigure_laoshu_big->setPosition(Vec2(Xdim*400/2048, visibleSize.height-Ydim*150/1536));
    //this->addChild(_stickfigure_laoshu_big, 0);
    
    
    
}

void Figure_Huace_Bigs::onEnter()
{
    //在当片层显示的时候调用此函数
    //所以一般会在这个方法下面进行一些初始化工作，例如精灵的布局等
    CCLayerColor::onEnter();
     CCSize visibleSize = Director::getInstance()->getVisibleSize();
    _stickfigure_laoshu_big->setAnchorPoint(Vec2(0,1));
    Node* parent = this->getParent();
    
    _stickfigure_laoshu_big->setPosition(Vec2(Xdim*400/2048, visibleSize.height-Ydim*150/1536));
    this->addChild(_stickfigure_laoshu_big, 0);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    
    listener = EventListenerTouchOneByOne::create();
    
    
    //指定触摸的回调函数
    listener->onTouchBegan = CC_CALLBACK_2(Figure_Huace_Bigs::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(Figure_Huace_Bigs::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(Figure_Huace_Bigs::onTouchEnded,this);
    //设置是否吞噬触摸
    listener->setSwallowTouches(true);//设置禁止向下传递触摸
    
    
    //addWEventListrnerWithGraghPriority(listener,background)
    dispatcher->addEventListenerWithFixedPriority(listener,-129); //－129屏蔽模态窗口下层的所有响应。
    
}
/*
void Figure_Huace_Bigs::onExit()
{
    if(listener)
    {
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->removeEventListener(listener);
        listener = NULL;
    }
    
    CCLayerColor::onExit();
    
}
*/

bool Figure_Huace_Bigs::onTouchBegan(Touch * touch,Event * pEvent)
{
    //CCLOG("Figure_Huace_Bigs began");
    //m_bTouchedMenu = this->ccTouchBegan(touch, pEvent);
    
    Vec2 touchPoint=convertTouchToNodeSpace(touch);
    //a Point is just a Vec2
    //which returns a Vec2
    if(_button_guanbi_red->boundingBox().containsPoint(touchPoint))
    {
        //CCLOG("red button is working");
        auto actionTo1 = ScaleTo::create(0.2f, 0.9f);
        auto actionTo2 = ScaleTo::create(0.2f, 1.0f);
        CallFunc* call  = CallFunc::create(CC_CALLBACK_0(Figure_Huace_Bigs::closeCallback, this));
        _button_guanbi_red->runAction(CCSequence::create(actionTo1, actionTo2, call, NULL));
    }
    
    
    
    return true;
}

void Figure_Huace_Bigs::onTouchMoved(Touch * touch,Event * pEvent)
{
    
    //CCLOG("moved");
}

void Figure_Huace_Bigs::onTouchEnded(Touch * touch,Event * pEvent)
{
    
    //CCLOG("ended");
    //m_bTouchedMenu = false;
}

/*
 
 void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
 {
 // 点击确定就退出（拷贝的原有方法）
 CCDirector::sharedDirector()->end();
 
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
 exit(0);
 #endif
 }
 */

void Figure_Huace_Bigs::closeCallback()
{
    //coven0202
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    
    this->retain();
    this->removeFromParentAndCleanup(true);
    this->release();
    
}
