//
//  ArmatureTest.cpp
//  KidTracer
//
//  Created by user on 14-9-13.
//
//

#include "ArmatureTest.h"
#include "CCDirector.h"
#include "cocos2d.h"


void ArmatureTest::update(float delta)
{
    cocos2d::Director::getInstance()->getTextureCache()->addImageAsync(reloadPlists[curReloadPlistNum]+"png",
                                                              CC_CALLBACK_1(ArmatureTest::plistImageAsyncCallback, this));
}

ArmatureTest::ArmatureTest(std::string animationName)
{
    cocostudio::Armature::create(animationName);
    
    reloadPlists= new std::string[14];
    curReloadPlistNum = 0;

    *(reloadPlists + 0) = "ui/StickFigureDialog_1/plist_figures/plist_figures";
    *(reloadPlists + 1) = "ui/StickFigureDialog_1/plist_figures_2/plist_figures_2";
    *(reloadPlists + 2) = "ui/StickFigureDialog_1/plist_figures_3/plist_figures_3";
    *(reloadPlists + 3) = "ui/StickFigureDialog_1/plist_figures_4/plist_figures_4";
    *(reloadPlists + 4) = "ui/StickFigureDialog_1/plist_figures_5/plist_figures_5";
    *(reloadPlists + 5) = "ui/StickFigureDialog_1/plist_figures_6/plist_figures_6";
    *(reloadPlists + 6) = "ui/StickFigureDialog_1/plist_figures_7/plist_figures_7";
    *(reloadPlists + 7) = "ui/StickFigureDialog_1/plist_figures_8/plist_figures_8";
    *(reloadPlists + 8) = "ui/StickFigureDialog_1/plist_figures_9/plist_figures_9";
    *(reloadPlists + 9) = "ui/StickFigureDialog_1/plist_figures_10/plist_figures_10";
    *(reloadPlists + 10) = "ui/StickFigureDialog_1/plist_figures_10/plist_figures_11";
    *(reloadPlists + 11) = "ui/StickFigureDialog_1/plist_figures_12/plist_figures_12";
    *(reloadPlists + 12) = "ui/StickFigureDialog_1/plist_figures_13/plist_figures_13";
    *(reloadPlists + 13) = "ui/StickFigureDialog_1/plist_figures_14/plist_figures_14";
}


void ArmatureTest::plistImageAsyncCallback(cocos2d::Texture2D* texture)
{
    if(curReloadPlistNum <= 13)
    {
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(reloadPlists[curReloadPlistNum].append("plist"), texture);
        curReloadPlistNum++;
        //CCLOG("curReloadPlistNum is %d",curReloadPlistNum);
    }
}


void ArmatureTest::playAnimation(std::string animationName)
{
    arm->getAnimation()->play(animationName);
}


