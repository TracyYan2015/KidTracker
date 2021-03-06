#ifndef __SCENE_TEST1_H__
#define __SCENE_TEST1_H__

#include "KTGlobalDef.h"

#include "cocos2d.h"

using namespace cocos2d;


class SceneTest1 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneTest1);


	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);
};

#endif // __SCENE_TEST1_H__
