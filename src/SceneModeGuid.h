#ifndef __SCENE_MODE_GUID_H__
#define __SCENE_MODE_GUID_H__

#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "PictureData.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

// class StrokeData
// {
// public:
// 	std::vector<Point> pos;
// 	bool isWait;
// };
// 
// class PictureData
// {
// public:
// 
// 	std::vector<StrokeData*> strokes;
// };

class SceneModeGuid : public cocos2d::Layer
{
public:

	SceneModeGuid();

	virtual ~SceneModeGuid();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	bool init_ui();
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneModeGuid);

	//void loadStrokeData();

	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);

	void playActionPointWait(Node* node, float delay);

	void onPointPathEnd(Node* node);

	bool playStroke(int strokeIndex);


	virtual void onClickUi(Ref* sender, TouchEventType type);

	void uiRegButton(Widget* parent, const std::string& name, int k, int z);

	// 给节点注册事件
	void registerTouchEvent(Node* node);

	virtual bool onTouchBegan(Touch * touch, Event * pEvent) override;
	virtual void onTouchMoved(Touch * touch, Event * pEvent) override;
	virtual void onTouchEnded(Touch * touch, Event * pEvent) override;
    
    
    void initElf();

private:


	Widget* _ui;
	PictureData* _pictureData;
	Armature* _guider;

	int _strokeIndex;
	int _nextStrokeIndex;
};

#endif // __SCENE_MODE_GUID_H__
