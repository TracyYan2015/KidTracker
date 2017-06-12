//
//  ArmatureTest.h
//  KidTracer
//
//  Created by user on 14-9-13.
//
//

#ifndef __KidTracer__ArmatureTest__
#define __KidTracer__ArmatureTest__

#include <iostream>
#include "cocostudio/CCArmature.h"

#endif /* defined(__KidTracer__ArmatureTest__) */


class ArmatureTest : public cocostudio::CCArmature
{
public:
    virtual void update(float delta);
    ArmatureTest(std::string animationName);
    void playAnimation(std::string animationName);
private:
    Armature* arm;
    int curReloadPlistNum;
    std::string* reloadPlists;
    void plistImageAsyncCallback(cocos2d::Texture2D* texture);
};