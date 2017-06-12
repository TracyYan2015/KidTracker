#include "SceneBigHuaceDialog.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
#include <UserData.h>



USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;
using namespace std;



enum kTag
{
	kTagCanvas = 100,
};

Scene* SceneBigHuaceDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneBigHuaceDialog::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneBigHuaceDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CCSize sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();
    
    
	init_ui();
    
    
    CCRect rect;
    rect.setRect(100,0,784,628);
    auto  path =FileUtils::getInstance()->getWritablePath();
    CCSpriteFrame * pFrame = CCSpriteFrame::create(path+fileName,rect);//screenshot.png 改为选择要分享的图片文件名
    CCSprite * pSprite3 = CCSprite::createWithSpriteFrame(pFrame);
    pSprite3->setPosition(0,0);
    pSprite3->setAnchorPoint(Vec2(0,0));
    this->addChild(pSprite3,zTagDefault+10);
    
    CCRenderTexture* texture1 = CCRenderTexture::create(784, 628);
    //设置位置
    //开始获取
    texture1->begin();
    //遍历场景节点对象，填充纹理到texure中
    pSprite3->visit();
    //结束获取
    texture1->end();
    //保存为PNG图，Win32/Debug目录下
    texture1->saveToFile("tt1.png", kCCImageFormatPNG); //tt1.png是用于社交分享的图片
    
    this->removeChild(pSprite3);
    
    return true;
}

void SceneBigHuaceDialog::getPictureFromScreenShot()
{
    CCRect rect;
    rect.setRect(100,0,784,628);
    auto  path =FileUtils::getInstance()->getWritablePath();
    CCSpriteFrame * pFrame = CCSpriteFrame::create(path+fileName,rect);//screenshot.png 改为选择要分享的图片文件名
    CCSprite * pSprite3 = CCSprite::createWithSpriteFrame(pFrame);
    pSprite3->setPosition(0,0);
    pSprite3->setAnchorPoint(Vec2(0,0));
    this->addChild(pSprite3,zTagDefault+10);
    
    CCRenderTexture* texture1 = CCRenderTexture::create(784, 628);
    //设置位置
    //开始获取
    texture1->begin();
    //遍历场景节点对象，填充纹理到texure中
    pSprite3->visit();
    //结束获取
    texture1->end();
    //保存为PNG图，Win32/Debug目录下
    std::string sub = std::string(".png");
    fileName.replace(fileName.find(sub), sub.size(), "t.png");
    cout<<fileName;
    
    
    
    
    
    texture1->saveToFile(fileName, kCCImageFormatPNG); //tt1.png是用于社交分享的图片
    
    this->removeChild(pSprite3);
}

bool SceneBigHuaceDialog::init_ui()
{
    //cache = SpriteFrameCache::getInstance();
    //cache->addSpriteFramesWithFile("ui/Elfdialog_1/plist_elfs/plist_elfs.plist", "ui/Elfdialog_1/plist_elfs/plist_elfs.png");
    
    
	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    
	ui = nullptr;
	{
		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/huace_big_1/huace_big_1.ExportJson"));
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));
        ui->setBackGroundColor(Color3B(0,0,0));
        ui->setBackGroundColorOpacity(0.4f*255);
        
        
        
        
		float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
		ui->setPosition(Vec2(gx, gy));
        
        
       
        
		
		uiRegButton(ui, "btn_close", kTagBtnRedClose, zTagDefault);
        uiRegButton(ui, "qqz", kTagBtnQQZ, zTagDefault);
        uiRegButton(ui, "xl", kTagBtnXL, zTagDefault);
        uiRegButton(ui, "wx", kTagBtnWX, zTagDefault);
        uiRegButton(ui, "txwb", kTagBtnTXWB, zTagDefault);
        
	}
	//_uiRoot = ui;
	this->addChild(ui, zTagBtnRefresh - 100);
    
    
	return true;
}





void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            CCLog("分享失败: %d : %s", ((CCInteger *)error -> objectForKey("error_code")) -> getValue(), ((CCString *)error -> objectForKey("error_msg")) -> getCString() );
            break;
        default:
            break;
    }
}

Sprite* SceneBigHuaceDialog::returnSprite()
{
    return added;
}

void SceneBigHuaceDialog::onClickUi_ImageView(Ref* sender, TouchEventType type)
{
    //cocos2d::ui::ScrollView* listView = (ScrollView*)ui->getChildByName("Elfs");
    int id = -1;
	ImageView* btn = dynamic_cast<ImageView*>(sender);
    
	if (btn != nullptr)
	{
		id = btn->getTag();
	}
    
	if (type != TOUCH_EVENT_ENDED)
		return;
    
	//CCLOG("onClick!!! id=%d", id);
    if (id == kTagBtnQQZ)
	{
        
        CCLOG("!!!!QQZ IS TOUCHED!!!!");
        
        auto  path =FileUtils::getInstance()->getWritablePath();
        __Dictionary *content = __Dictionary::create();
        content -> setObject(__String::create("这是我在ELf&Draw中的作品"), "content");
        content -> setObject(__String::create(path+fileName), "image");//传入一个png路径
        content -> setObject(__String::create("测试标题"), "title");
        content -> setObject(__String::create("测试描述"), "description");
        content -> setObject(__String::create("http://sharesdk.cn"), "url");
        content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeNews), "type");
        C2DXShareSDK::shareContent(C2DXPlatTypeQZone, content, shareResultHandler);
        
     
        
    }
	else if (id == kTagBtnXL)
	{
        CCLOG("!!!!XL IS TOUCHED!!!!");
        auto  path =FileUtils::getInstance()->getWritablePath();
        __Dictionary *content = __Dictionary::create();
        content -> setObject(__String::create("这是我在ELf&Draw中的作品"), "content");
        content -> setObject(__String::create(path+fileName), "image");//传入一个png路径
        content -> setObject(__String::create("测试标题"), "title");
        content -> setObject(__String::create("测试描述"), "description");
        content -> setObject(__String::create("http://sharesdk.cn"), "url");
        content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeNews), "type");
        C2DXShareSDK::shareContent(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
	}
    else if (id == kTagBtnWX)
	{
        CCLOG("!!!!WX IS TOUCHED!!!!");
        
        auto  path =FileUtils::getInstance()->getWritablePath();
        __Dictionary *content = __Dictionary::create();
        content -> setObject(__String::create("这是我在ELf&Draw中的作品"), "content");
        content -> setObject(__String::create(path+fileName), "image");//传入一个png路径
        content -> setObject(__String::create("测试标题"), "title");
        content -> setObject(__String::create("测试描述"), "description");
        content -> setObject(__String::create("http://sharesdk.cn"), "url");
        content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeNews), "type");
        C2DXShareSDK::shareContent(C2DXPlatTypeWeixiTimeline, content, shareResultHandler);
        //C2DXShareSDK::shareContent(cn::sharesdk::C2DXPlatType platType, content, shareResultHandler);
        
        
	}
    else if(id == kTagBtnTXWB)
    {
        CCLOG("!!!!TXWB IS TOUCHED!!!!");
        auto  path =FileUtils::getInstance()->getWritablePath();
        __Dictionary *content = __Dictionary::create();
        content -> setObject(__String::create("这是我在ELf&Draw中的作品"), "content");
        content -> setObject(__String::create(path+fileName), "image");//传入一个png路径
        content -> setObject(__String::create("测试标题"), "title");
        content -> setObject(__String::create("测试描述"), "description");
        content -> setObject(__String::create("http://sharesdk.cn"), "url");
        content -> setObject(__String::createWithFormat("%d", cn::sharesdk::C2DXContentTypeNews), "type");
        C2DXShareSDK::shareContent(C2DXPlatTypeTencentWeibo, content, shareResultHandler);
        
        
    }
    else if(id == kTagBtnRedClose)
	{
        //精灵对话框的关闭按钮
        
        auto action1 = ScaleTo::create(0.2f, 0.9f);
        auto action2 = ScaleTo::create(0.2f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneBigHuaceDialog::closeCallback, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,call
                                          , NULL));
        
	}
}

void SceneBigHuaceDialog::setFileName(std::string filename)
{
    this->fileName = filename;
}
/*
void SceneBigHuaceDialog::onExit(){
    Layer::onExit();
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    Util::cleanTextureCacheWithMessage("exit title");
}
*/

void SceneBigHuaceDialog::addBigPicByID(int idx)
{
    UserData* data = new UserData();
    __Dictionary* picitem = dynamic_cast<__Dictionary*>(data->albumArr->getObjectAtIndex(idx));
    __String* pathStr = dynamic_cast<__String*>(picitem->objectForKey("path"));
    //const char* cPicPath = pathStr->getCString();
    //int id = *cPicPath - '0';
    
    
    
    
    CCSize size = CCDirector::getInstance()->getWinSize();
    CCRect rect;
    rect.setRect(108.0f*size.width/1024.0f,0,784,628);
    auto  path =FileUtils::getInstance()->getWritablePath()+pathStr->getCString();
    SpriteFrame * pFrame = CCSpriteFrame::create(path,rect);
    Sprite* big = CCSprite::createWithSpriteFrame(pFrame);
    
    
    ImageView* diban_big = (ImageView*)ui->getChildByName("diban_big");
    diban_big->addChild(big);
    big->setAnchorPoint(Vec2(0,1));
    big->setScale(487.0f/784.0f, 390.0f/628.0f);
    big->setPosition(Vec2(52,455));
    
}

void SceneBigHuaceDialog::closeCallback()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
    //coven0202
    this->release();
    
}

void SceneBigHuaceDialog::uiRegButton(Widget* parent, const std::string& name, int k, int z)
{
	ImageView* btn = (ImageView*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneBigHuaceDialog::onClickUi_ImageView));
		btn->setZOrder(z);
		//parent->addChild(btn, z);
	}
}


void SceneBigHuaceDialog::addSprite(Sprite* added)
{
    this->added = added;
    ImageView* diban_big = (ImageView*)ui->getChildByName("diban_big");
    diban_big->addChild(added);
    added->setAnchorPoint(Vec2(0,1));
    added->setScale(487.0f/784.0f,390.0f/628.0f);
    
    added->setPosition(Vec2(52,455));
}


