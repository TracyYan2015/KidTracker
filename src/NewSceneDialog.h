//
//  NewSceneDialog.h
//  KidTracer
//
//  Created by user on 14-10-14.
//
//

#ifndef __KidTracer__NewSceneDialog__
#define __KidTracer__NewSceneDialog__

#include <iostream>

#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneTitle.h"

using namespace cocos2d;
using namespace ui;

class NewSceneDialog : public cocos2d::Layer
{
    
};






class SceneDialog : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	bool init_ui();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneDialog);
    
    
	void playActionPointPath(Node* node, const std::vector<Point>& points, int index);
    
	virtual void onClickUi(Ref* sender, TouchEventType type);
    
    virtual void onClickUi_ImageView(Ref* sender, TouchEventType type);
    
	void uiRegButton(Widget* parent, const std::string& name, int k, int z);
    
    void uiRegButtonInListView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    int selected_scene_id;
    void addScene2VectorWithSceneId(int id);
    void scenes_layout(Vector<Sprite*> dibans, Vector<ImageView*>  scenes);
    
    SceneTitle* sceneTitle;
    
    void initBlueRing_Word();//一进入场景图鉴，用这个方法进行初始化
    
    bool isDirectEntered;//如果是从主界面直接进入此对话框则置为true
    
    void make_a_change();
    
    
    
    //接受来自简笔画模块的数据
    int stickFigure_id;
    int stickFigure_id_vector;
    int elf_id;
    int elf_id_vector;
    
    
    
    
    
private:
    enum selected_scene_idx
    {
        scene1 = 1,
        scene2,
        scene3,
        
        
    };
    
    
    
    
    Layout *ui;
    SpriteFrameCache *cache;
    Sprite* diban_scene1;
    Sprite* diban_scene2;
    Sprite* diban_scene3;
    ImageView* _scene1;
    ImageView* _scene2;
    ImageView* _scene3;
    Sprite* _jiahao;
    
    
    
    Vector<Sprite*> dibans;
    Vector<ImageView*> scenes;
    
    
    
    
    
    ImageView* back;   //上一步
    ImageView* start;   //开始
    void backFunc();
    void startFunc();
    
    
};

#endif // __SCENE_TITLE_H__
