#ifndef __SCENE_HACE_DELETE_DIALOG_H__
#define __SCENE_HACE_DELETE_DIALOG_H__


#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneHuaceDialog.h"


using namespace cocos2d;
using namespace ui;
using namespace std;


class SceneHaceDeleteDialog : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	bool init_ui();
    
    //void onExit();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneHaceDeleteDialog);
	//void playActionPointPath(Node* node, const std::vector<Point>& points, int index);
    
	virtual void onClickUi(Ref* sender, TouchEventType type);
    
	void uiRegButton_imageview(Widget* parent, const std::string& name, int k, int z);
    
    //void uiRegButtonInScrollView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    
    Layout *ui;
    //Layout *ui_big;
    
    //SpriteFrameCache *cache;
    
    //void layout();
    
    
    void setBtnPosition(Vec2 position);
    bool isDelete;
    SceneHuaceDialog* huace;
    int idx;
private:
    /*
    enum selected_huace_idx
    {
        huace1 = 1,
        huace2,
        huace3,
        
        
        
    };
    
    int selected_huace_id = -1;
     */
    
    
    void SetBtnPosition(Vec2 position);//改变“是否删除”图片的位置，根据xxdb的位置
    
    ImageView* btn;
    
    EventListenerTouchOneByOne* listener;
    
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    void onTouchMoved(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    
    
    //Rect getBoundingBox_worldspace(Sprite*);
    
  
};



#endif // __SCENE_TITLE_H__
