#include "HelloWorldScene.h"
#include "SceneTitle.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
USING_NS_CC;

enum kTag
{
	kTagBtn0 = 1000,
	kTagBtnExit,
	kTagSpCapture,
};

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


void HelloWorld::turnToSceneTitle(const char* event)
{
    //CCLOG("the event is %s",event);
    //if(strcmp(event, "\370\'r") == 0){
    //SceneController::getInstance()->addScene(this, eSceneIdSceneTitle);
        auto scene = SceneTitle::createScene();
        Director::getInstance()->replaceScene(scene);
    //}
    //\370r
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto closeItem = MenuItemImage::create( "CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::onClickMenu, this));
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 , origin.y + closeItem->getContentSize().height/2));

	
/*
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
*/

	// -------------------------------------------------------------------------------------------------------------------
	/*
    {
		MenuItemImage* btn = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::onClickMenu, this));
		btn->setPosition(Vec2(100.0f, 100.0f));
		btn->setTag(kTagBtn0);
		menu->addChild(btn, 1);
	}
     */
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("an/LOGO/LOGO.ExportJson");
    Armature *arm = Armature::create("LOGO");
    //ui->addChild(arm,1,1000);
    //arm->setPosition(diban_elf1->getPosition()+listView->getPosition());
    this->addChild(arm,1,1000);
    arm->setAnchorPoint(Vec2(0,0));
    arm->setPosition(Vec2(0,0));

    arm->getAnimation()->play("Animation1");
    arm->getAnimation()->setFrameEventCallFunc(this,frameEvent_selector(HelloWorld::turnToSceneTitle));
    
    /*
    Sprite* temp = Sprite::create("HelloWorld.png");
    CallFunc* call1  = CallFunc::create(CC_CALLBACK_0(HelloWorld::turnToSceneTitle, this));
    FiniteTimeAction* seq = Sequence::create(DelayTime::create(9.28f), call1, NULL);
    temp->runAction(seq);
    
    //SceneController::getInstance()->replaceScane(eSceneIdSceneTitle);
    
    //SceneController::getInstance()->addScene(this, eSceneIdSceneTitle);
    */
    return true;
}


void HelloWorld::onClickMenu(Ref* pSender)
{
	MenuItem* mi = (MenuItem*)pSender;
	int id = mi->getTag();

	if (id == kTagBtn0)
	{
		utils::captureScreen(CC_CALLBACK_2(HelloWorld::onCaptureScreen, this), "abc.png");
	}
	else if (id == kTagBtnExit)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
#endif
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}

}

void HelloWorld::onCaptureScreen(bool succeed, const std::string& outputFile)
{
	if (succeed)
	{
		int childTag = 5555;
		auto sp = Sprite::create(outputFile);
		addChild(sp, 0, childTag);
		CCSize s = Director::getInstance()->getWinSize();
		sp->setPosition(s.width / 2, s.height / 2);
		sp->setScale(0.25);
		//_filename = outputFile;
		log("Capture screen failed. %s", outputFile.c_str());
	}
	else
	{
		log("Capture screen failed.");
	}
}
