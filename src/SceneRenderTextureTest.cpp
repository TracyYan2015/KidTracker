#include "SceneRenderTextureTest.h"
//#include "SuperAnimNodeV2.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneController.h"
#include "SceneModeGuidDraw.h"
#include "SimpleAudioEngine.h"
#include "ImagePickerImpl.h"
#include "SceneTitle.h"
#include "SceneStickFigureDialog.h"
#include "UserData.h"
#include "Util.h"

//using namespace SuperAnim;
using namespace cocostudio;
USING_NS_CC;

enum kTag
{
	kTagCanvas = 100,
};

//const char* SAM_BASIC = "mh/mouse/test1.sam";
const char* SAM_BASIC = "mh/fish/fish.sam";
const int RELOADPLIST_SIZE = 4;


//grobal constants for plist path definition
const std::string LAOSHU_PATH = "ui/StickFigureDialog_1/laoshuExport/laoshu.plist";
const std::string XIAOTU_PATH = "ui/StickFigureDialog_1/xiaotuExport/xiaotu.plist";
const std::string HB_PATH = "ui/StickFigureDialog_1/hbExport/hbTouXiangs.plist";
const std::string CS_PATH = "ui/StickFigureDialog_1/csExport/csTouXiangs.plist";
const int JBH_SET_NUMBER = 5;
std::vector<std::string> DATU_PATHS;
std::vector<std::string> MH_DATU_PATH;
const std::string LAOSHU_PLIST_PATH = "ui/StickFigureDialog_1/laoshuExport/laoshu.plist";
int modeSoundTmp = 0;

Scene* SceneRenderTextureTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneRenderTextureTest::create();
    
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneRenderTextureTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
 //   Util::modeSoundTmp = 0;
    //bought all stuffs
    UserData* data = new UserData();
    __Dictionary* plistDic = data->plistDic;
    __Dictionary* jbhDic = data->jbhDic;
    __Dictionary* sceneDic = data->sceneDic;
    __Dictionary* elfDic = data->elfDic;
    std::string path = CCFileUtils::getInstance()->getWritablePath();
    std::string _doc1 = path + "test.plist";
    __String* yes = __String::createWithFormat("%s","yes");
    __String* no = __String::createWithFormat("%s","no");
    
    jbhDic->setObject(yes, "1");
    jbhDic->setObject(yes, "2");
    jbhDic->setObject(yes, "3");
    jbhDic->setObject(yes, "4");
    jbhDic->setObject(yes, "5");
   

    elfDic->setObject(yes, "1");
    elfDic->setObject(yes, "2");
    elfDic->setObject(yes, "3");
    elfDic->setObject(yes, "4");
    elfDic->setObject(yes, "5");

    sceneDic->setObject(yes, "1");
    sceneDic->setObject(yes, "2");
    sceneDic->setObject(yes, "3");
    sceneDic->setObject(yes, "4");
    sceneDic->setObject(yes, "5");
    
    
    plistDic->setObject(yes, "isLiBaoBought");
    
    
    plistDic->writeToFile(_doc1.c_str());
    
    
    
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set1_01.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set1_02.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set2_01.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set2_02.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set3_01.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set3_02.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set4_01.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set4_02.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set5_01.plist");
    DATU_PATHS.push_back("ui/StickFigureDialog_1/datuExport/set5_02.plist");
    
    
    
    MH_DATU_PATH.push_back("mhDatuExport/mhSet1_1.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet1_2.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet2_1.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet2_2.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet3_1.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet3_2.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet4_1.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet4_2.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet5_1.plist");
    MH_DATU_PATH.push_back("mhDatuExport/mhSet5_2.plist");
    
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3",true);//("bgm/201-unknown_-_out_of_valley-muji.mp3");
    
    
    //Size sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SceneRenderTextureTest::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(posV.x + Director::getInstance()->getVisibleSize().width - closeItem->getContentSize().width/2 ,
                                posV.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    //Size vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    Vec2 posWCenter = Vec2(vOrigin.x + Director::getInstance()->getVisibleSize().width / 2, vOrigin.y + Director::getInstance()->getVisibleSize().height / 2);
    
    
    
    
 	ArmatureDataManager::getInstance()->addArmatureFileInfo("an/title/title.ExportJson");
    logo = Armature::create("title");
    
    
    logo->setTag(kTagElfHappy);
    logo->setPosition(vOrigin);
    this->addChild(logo, 1);
    logo->getAnimation()->setFrameEventCallFunc(this,frameEvent_selector (SceneRenderTextureTest::onFrameEvent));//转主界面
    logo->getAnimation()->play("Animation2");
    
    
    
    
    //extern int curReloadPlistNum;
    //curReloadPlistNum = 0;
    //reloadPlists = new std::string[4];
    /*
    *(reloadPlists + 0) = "ui/StickFigureDialog_1/plist_figures/plist_figures";
    *(reloadPlists + 1) = "ui/StickFigureDialog_1/plist_figures_2/plist_figures_2";
    *(reloadPlists + 2) = "ui/StickFigureDialog_1/plist_figures_3/plist_figures_3";
    *(reloadPlists + 3) = "ui/StickFigureDialog_1/plist_figures_4/plist_figures_4";
    *(reloadPlists + 4) = "ui/StickFigureDialog_1/plist_figures_5/plist_figures_5";
    *(reloadPlists + 5) = "ui/StickFigureDialog_1/plist_figures_6/plist_figures_6";
    *(reloadPlists + 6) = "ui/StickFigureDialog_1/plist_figures_7/plist_figures_7";
    *(reloadPlists + 7) = "ui/StickFigureDialog_1/plist_figures_8/plist_figures_8";
    *(reloadPlists + 8) = "ui/StickFigureDialog_1/plist_figures_9/plist_figures_9";
    *(reloadPlists + 9) = "ui/StickFigureDialog_1/plist_figures_10/plist_figures_10";
    *(reloadPlists + 10) = "ui/StickFigureDialog_1/plist_figures_11/plist_figures_11";
    *(reloadPlists + 11) = "ui/StickFigureDialog_1/plist_figures_12/plist_figures_12";
    *(reloadPlists + 12) = "ui/StickFigureDialog_1/plist_figures_13/plist_figures_13";
    *(reloadPlists + 13) = "ui/StickFigureDialog_1/plist_figures_14/plist_figures_14";
    
    //加载道具plist
    *(reloadPlists + 14) = "ui/NewSetupDialog_1_11_20/daoju_small_plist";
    *(reloadPlists + 15) = "ui/NewSetupDialog_1_11_20/daoju_big_plist1";
    *(reloadPlists + 16) = "ui/NewSetupDialog_1_11_20/daoju_big_plist2";
    *(reloadPlists + 17) = "ui/NewSetupDialog_1_11_20/daoju_big_plist3";
    *(reloadPlists + 18) = "ui/NewSetupDialog_1_11_20/daoju_big_plist4";
     */
    /*
    *(reloadPlists + 0) = LAOSHU_PLIST_PATH;
    *(reloadPlists + 1) = XIAOTU_PATH;
    *(reloadPlists + 2) = HB_PATH;
    *(reloadPlists + 3) = CS_PATH;
    */
    
    
    
    //addImageAsync not support .pvr.ccz
    
    //异步加载
    //extern int curReloadPlistNum;
    /*
    Director::getInstance()->getTextureCache()->addImageAsync(reloadPlists[curReloadPlistNum]+".plist",
                                                                  CC_CALLBACK_1(SceneRenderTextureTest::plistImageAsyncCallback, this));
    */
    std::string DATU_PLIST_ROOT = "ui/StickFigureDialog_1/datuExport/set";
    //COVEN
    delete data;
    data = NULL;
    
    return true;
}


void SceneRenderTextureTest::addLaoshuPVR(){
    std::string laoshuPlistPath = "ui/StickFigureDialog_1/laoshuExport/laoshu.plist";
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(laoshuPlistPath);
}


//int curReloadPlistNum= 0;
/*
void SceneRenderTextureTest::plistImageAsyncCallback(cocos2d::Texture2D* texture)
{
    extern int curReloadPlistNum;
    if(curReloadPlistNum <= RELOADPLIST_SIZE - 2)
    {
        CCLOG("curReloadPlistNum is %d",curReloadPlistNum);
        //extern SpriteFrameCache* cache_jbh;
        cache_jbh = SpriteFrameCache::getInstance();
        int ii = curReloadPlistNum;
        cache_jbh->addSpriteFramesWithFile(reloadPlists[curReloadPlistNum] + ".plist", texture);
        
       
        curReloadPlistNum++;
        Director::getInstance()->getTextureCache()->addImageAsync(reloadPlists[curReloadPlistNum]+".pvr.ccz",CC_CALLBACK_1(SceneRenderTextureTest::plistImageAsyncCallback, this));
    }
    else if(curReloadPlistNum == RELOADPLIST_SIZE - 1)
    {
        //plist加载完毕
        CCLOG("curReloadPlistNum is %d",curReloadPlistNum);
        cache_jbh = SpriteFrameCache::getInstance();
        int ii = curReloadPlistNum;
        cache_jbh->addSpriteFramesWithFile(reloadPlists[curReloadPlistNum] + ".plist", texture);
        auto scene = SceneTitle::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    
    
}
*/




bool SceneRenderTextureTest::onTouchBegan(Touch * touch, Event * pEvent)
{
	Vec2 posW = touch->getLocation();
    
    
    auto start = touch->getPreviousLocation();
    startP = posW;
    volumFlag=0;
	return true;
}

void SceneRenderTextureTest::onTouchMoved(Touch * touch, Event * pEvent)
{
	
    
}


void SceneRenderTextureTest::update(float delta)
{
    
}

void SceneRenderTextureTest ::onFrameEvent( CCZone * bone , const char * evt, int originFrameIndex, int currentFrameIndex )
{
    //if(strcmp(evt,"\btest") == 0) //COCOS STUDIO中设置帧事件 if equal, return 0
        //\b好像是正则表达式里面的，和字符匹配有关
    {
        SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
        
        auto scene = SceneTitle::createScene();
        Director::getInstance()->replaceScene(scene);
        /*
        std::string  cachedInfo = Director::getInstance()->getTextureCache()->getCachedTextureInfo();
        CCLOG("cached info");
        CCLOG("%s",cachedInfo.c_str());
         */
    }
}

void SceneRenderTextureTest::menuCloseCallback(Ref* pSender)
{
	exit(0);
	
    
	return;
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void SceneRenderTextureTest::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
{
    
	Vec2 posStart = node->getPosition();
	Vec2 posEnd = points[index];
	float dis = posStart.distance(posEnd);
	float v = 100 / 1.0f;
	float t = dis / v;
    
	auto act_m = MoveTo::create(t, points[index]);
	auto act_cb = CallFunc::create([=]{
        
		int nextIndex = (index + 1);
		if (nextIndex < points.size())
			playActionPointPath(node, points, nextIndex);
		else
		{
			// end
		}
        
	});
	auto seq = Sequence::create(act_m, act_cb, nullptr);
    
	node->runAction(seq);
}

void SceneRenderTextureTest::drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd)
{
	float distance = posStart.distance(posEnd);
	float difx = posEnd.x - posStart.x;
	float dify = posEnd.y - posStart.y;
    
	_brushs.clear();
    
	for (int i = 0; i < distance; i++)
	{
		Sprite* br = Sprite::create("brush1.png");
		_brushs.pushBack(br);
	}
	
	canvas->begin();
	for (int i = 0; i < distance; i++)//
	{
		float delta = (float)i / distance;
		Vec2 pos = ccp(posStart.x + (difx * delta), posStart.y + (dify * delta));
		// CCLOG("[%d] - (%d,%d)", i, (int)pos.x, (int)pos.y );
        
		Sprite* br = _brushs.at(i);
		br->setPosition(pos);
		br->visit();
	}
	canvas->end();
    
}

Sprite* SceneRenderTextureTest::getBrush()
{
	Sprite* brush = Sprite::create("brush1.png");
    
    
	return brush;
}

void SceneRenderTextureTest::playActionDelay(float delay, const std::function<void()> &func)
{
	auto a_dt = DelayTime::create(delay);
	auto a_cb = CallFunc::create(func);
	auto a_seq = Sequence::create(a_dt, a_cb, nullptr);
	this->runAction(a_seq);
}

void SceneRenderTextureTest::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	auto touch = touches[0];
	auto start = touch->getPreviousLocation();
	auto end = touch->getLocation();
    
	start = _rt->convertToNodeSpace(start) + _canvasSize / 2;
	end = _rt->convertToNodeSpace(end) + _canvasSize / 2;
    
    
	drawLine(_rt, _brush, start, end);
}
