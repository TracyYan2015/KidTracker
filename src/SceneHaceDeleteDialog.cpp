#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneController.h"
#include "SceneHaceDeleteDialog.h"
#include <UserData.h>
#include "Util.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

/*
enum kTag
{
	kTagCanvas = 100,
};
*/

/*
 //类外定义静态成员变量
 Layout* SceneHaceDeleteDialog::ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/huaceDialog_1/huaceDialog_1.ExportJson"));
 
 SpriteFrameCache* SceneHaceDeleteDialog::cache = SpriteFrameCache::getInstance();
 */

Scene* SceneHaceDeleteDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneHaceDeleteDialog::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
/*
void SceneHaceDeleteDialog::onExit(){
    Layer::onExit();
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    
    Util::cleanTextureCacheWithMessage("exit title");
    
}
*/

// on "init" you need to initialize your instance
bool SceneHaceDeleteDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //std::string  currTime = getcurrTime()
    //CCLOG("current time is %s", currTime.c_str());
    //Size sizeV = Director::getInstance()->getVisibleSize();
    //Vec2 posV = Director::getInstance()->getVisibleOrigin();
	/*
     auto sp = Sprite::create("bg.png");
     sp->setScale(1.0f);
     sp->setAnchorPoint(Point::ZERO);
     sp->setPosition(posV + Point(0.0f, 0.0f));
     this->addChild(sp, 0);
     Node* canvas = Node::create();
     canvas->setTag(kTagCanvas);
     canvas->setAnchorPoint(Point::ZERO);
     canvas->setPosition( Point(118.0f, 150.0f) );
     this->addChild(canvas, 0);
     */
	init_ui();
    //可以改变位置
    
    btn = (ImageView*)ui->getChildByName("deletaImageView");//bad typing!!!
    btn->setAnchorPoint(Vec2(0,1));
    uiRegButton_imageview(btn, "gou", kTagBtnDelete, zTagDefault);
    uiRegButton_imageview(btn, "cha", kTagBtnCancel, zTagDefault);
    
    
    
    
    
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    listener = EventListenerTouchOneByOne::create();
    
    
    //指定触摸的回调函数
    listener->onTouchBegan = CC_CALLBACK_2(SceneHaceDeleteDialog::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(SceneHaceDeleteDialog::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(SceneHaceDeleteDialog::onTouchEnded,this);
    //设置是否吞噬触摸
    listener->setSwallowTouches(false);
    
    //dispatcher->addEventListenerWithFixedPriority(listener,-129); //－129屏蔽模态窗口下层的所有响应。
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

void SceneHaceDeleteDialog::uiRegButton_imageview(Widget* parent, const std::string& name, int k, int z)
{
    ImageView* btn = (ImageView*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneHaceDeleteDialog::onClickUi));
		btn->setZOrder(z);
		//parent->addChild(btn, z);
	}
    
}

void SceneHaceDeleteDialog::onClickUi(Ref* sender, TouchEventType type)
{
    int id = -1;
	ImageView* btn = dynamic_cast<ImageView*>(sender);
	if (btn != nullptr)
	{
		id = btn->getTag();
	}
    
	if (type != TOUCH_EVENT_ENDED)
		return;
	CCLOG("onClick!!! in SceneHuaceDialog id=%d", id);
    
    if(id == kTagBtnDelete)
    {
        CCLOG("delete is clicked");
        closeCallback();
        huace->deleteItemFromHace(idx);
        
    }
    else if(id == kTagBtnCancel)
    {
        CCLOG("cancel is clicked");
        closeCallback();
    }
}








void SceneHaceDeleteDialog::setBtnPosition(Vec2 position)
{
    //根据传入的信息地板的位置改变图片的位置
    //传入的应该是信息地板的世界坐标
    btn->setAnchorPoint(Vec2(0,1));
    btn->setPosition(position);
}

bool SceneHaceDeleteDialog::init_ui()
{
    CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    
	ui = nullptr;
	{
		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/HaceDeleteDialog_1/HaceDeleteDialog_1.ExportJson"));
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));
        ui->setBackGroundColor(Color3B(0,0,0));
        ui->setBackGroundColorOpacity(0.4f*255);
		float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
		ui->setPosition(Vec2(gx, gy));
	}
	this->addChild(ui, zTagBtnRefresh - 100);
    
   
    

	return true;
}







void SceneHaceDeleteDialog::closeCallback()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
}





bool SceneHaceDeleteDialog::onTouchBegan(Touch * touch,Event * pEvent)
{
    Vec2 touchPoint=convertTouchToNodeSpace(touch);
    //touchPoint = touchPoint - huaces->getPosition();
    //CCLOG("THE TOUCHPOINT IS (%f, %f)",touchPoint.x, touchPoint.y);
    
    
    return true;
}

void SceneHaceDeleteDialog::onTouchMoved(Touch * touch,Event * pEvent)
{
    //CCLOG("drag moved");
}

void SceneHaceDeleteDialog::onTouchEnded(Touch * touch,Event * pEvent)
{
    //CCLOG("drag ended");
    
    
}



