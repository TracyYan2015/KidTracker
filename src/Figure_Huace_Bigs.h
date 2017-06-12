//
//  DialogLayer.h
//  ModalDialogDemo
//
//  Created by Tom on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef ModalDialogDemo_Figure_Huace_Bigs_h
#define ModalDialogDemo_Figure_Huace_Bigs_h

#include "cocos2d.h"

USING_NS_CC;

class Figure_Huace_Bigs: public cocos2d::LayerColor
//LayerColor
//a sub class of Layer
//which add opacity and the RGB color
{
    // 模态对话框菜单
    //CCMenu *m_pMenu;
    // 记录菜单点击
    //bool m_bTouchedMenu;
    
    cocos2d::Sprite* _button_guanbi;
    EventListenerTouchOneByOne* listener;
    
    const int Xdim = 1024;//2048;
    const int Ydim = 768;//1536;
    //const int Xdim = 2048;
    //const int Ydim = 1536;
    cocos2d::Sprite *_button_guanbi_red;
    cocos2d::Sprite *_stickfigure_laoshu_big;//要显示的大号老鼠的精灵
    //String stickFigureName;
public:
    Figure_Huace_Bigs();
    ~Figure_Huace_Bigs();
    
    virtual bool init();
    // 初始化对话框内容
    void initDialog();
    void setSprite(Sprite *s);
    CREATE_FUNC(Figure_Huace_Bigs);
    //传入一个类名，创建这个类的一个create函数，，，
    //create函数会自动调用这个类的init函数
    void onEnter();
    //void onExit();
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    void onTouchMoved(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    
    //void okMenuItemCallback(CCObject *pSender);
    void closeCallback();
};

#endif
