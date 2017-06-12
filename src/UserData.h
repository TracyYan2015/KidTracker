//
//  UserData.h
//  KidTracer
//
//  Created by Bian Wu on 19/8/14.
//
//

#ifndef __KidTracer__UserData__
#define __KidTracer__UserData__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

class UserData
{
   

    __String* fileStr;
    __String* nameStr;
    __String* ageStr;
    

public:
    UserData();
    
    //void init();
    
    void showData();
    
    void setUser(__String* name, __String* age);
    
    Vector<__String*>* getUserInfo();
    
    int addPicItem();
    
    void delPicItem(int index);
    
    __Array* albumArr;
    
    __String* sizeStr;
    
    __Dictionary* plistDic;
    __Dictionary* jbhDic;
    __Dictionary* elfDic;
    __Dictionary* sceneDic;
    __String* isLiBaoBought;
};

#endif /* defined(__KidTracer__UserData__) */
