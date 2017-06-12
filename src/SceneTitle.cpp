#include "SceneTitle.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
#include "IOSiAP_Bridge.h"
#include "SceneModeGuidDraw.h"
#include "SceneModeGuidStroke.h"//描红模式
#include "SceneModeFreeDraw.h"
#include "SceneDialog.h"
#include "SceneElfDialog.h"
#include "SceneSetupDialog.h"
#include "SceneStickFigureDialog.h"
#include "SceneHuaceDialog.h"
#include "Time.h"
#include "SceneTitleUserData.h"
#include "Util.h"




//#include "C2DXShareSDK.h"
#include "ImagePickerImpl.h"
#include "UserData.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;
using namespace std;


enum kTag
{
	kTagCanvas = 100,
};


enum elfId
{
    elf1 = 1,
    elf2,
    elf3,
    
};

enum sceneId
{
    scene1 = 1,
    scene2,
    scene3,
};


const int JBH_SET_NUMBER = 5;

Scene* SceneTitle::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneTitle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneTitle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    /*
    for(int i = 3;i < 241;i++)
    {
        
        if(i < 10)
        {
            CCLOG("auto dj%d = ImageView::create(\"zyms_dj_bs_00%d.png\",Widget::TextureResType::PLIST);",i,i);
        }
        else if (i < 100)
        {
            CCLOG("auto dj%d = ImageView::create(\"zyms_dj_bs_0%d.png\",Widget::TextureResType::PLIST);",i,i);
        }
        else
        {
            CCLOG("auto dj%d = ImageView::create(\"zyms_dj_bs_%d.png\",Widget::TextureResType::PLIST);",i,i);
        }
        CCLOG("dj%d->setAnchorPoint(Vec2(0.5f, 0.5f));",i);
        CCLOG("dj%d->setTag(kTagBtnFreeDjbk%d);",i,i);
        CCLOG("dj%d->addTouchEventListener(this, toucheventselector(SceneModeFreeDraw::onClickUi_imageView));",i);
        
        CCLOG("daojus.pushBack(dj%d);",i);
        
        CCLOG("dj%d->setScale(1.5f);", i);
        
        
    }
    */
    
    Util::cleanTextureCacheWithMessage("return from setup mode");
   
    
    UserData* data = new UserData();
    localJBHStrings = getCCStringVectorFromUserData(data);

    JBHNames.push_back("laoshu");
    JBHNames.push_back("niu");
    JBHNames.push_back("laohu");
    JBHNames.push_back("tuzi");
    JBHNames.push_back("long");
    JBHNames.push_back("she");
    JBHNames.push_back("ma");
    JBHNames.push_back("yang");
    JBHNames.push_back("hou");
    JBHNames.push_back("ji");
    JBHNames.push_back("gou");
    JBHNames.push_back("zhu");
    JBHNames.push_back("shizi");
    JBHNames.push_back("daxiang");
    JBHNames.push_back("hema");
    JBHNames.push_back("xiniu");
    JBHNames.push_back("eyu");
    JBHNames.push_back("huli");
    JBHNames.push_back("qingwa");
    JBHNames.push_back("shudaixiong");
    //=-------------------------------------20
    JBHNames.push_back("qingting");
    JBHNames.push_back("luotuo");
    JBHNames.push_back("wugui");
    JBHNames.push_back("hudie");
    JBHNames.push_back("haitun");
    JBHNames.push_back("jingyu");
    JBHNames.push_back("lu");
    JBHNames.push_back("xiong");
    JBHNames.push_back("tiane");
    JBHNames.push_back("pangxie");
    JBHNames.push_back("shayu");
    JBHNames.push_back("changjinglu");
    JBHNames.push_back("qie");//企鹅
    JBHNames.push_back("lang");
    JBHNames.push_back("maotouying");
    JBHNames.push_back("mao");
    JBHNames.push_back("kongque");
    JBHNames.push_back("bianselong");
    JBHNames.push_back("daishu");
    JBHNames.push_back("ciwei");
    JBHNames.push_back("songshu");
    //extern std::vector<std::string> JBHNames_Chinese;
    JBHNames_Chinese.push_back("老鼠");
    JBHNames_Chinese.push_back("牛");
    JBHNames_Chinese.push_back("老虎");
    JBHNames_Chinese.push_back("兔子");
    JBHNames_Chinese.push_back("龙");
    JBHNames_Chinese.push_back("蛇");
    JBHNames_Chinese.push_back("马");
    JBHNames_Chinese.push_back("羊");
    JBHNames_Chinese.push_back("猴");
    JBHNames_Chinese.push_back("鸡");
    JBHNames_Chinese.push_back("狗");
    JBHNames_Chinese.push_back("猪");
    JBHNames_Chinese.push_back("狮子");
    JBHNames_Chinese.push_back("大象");
    JBHNames_Chinese.push_back("河马");
    JBHNames_Chinese.push_back("犀牛");
    JBHNames_Chinese.push_back("鳄鱼");
    JBHNames_Chinese.push_back("狐狸");
    JBHNames_Chinese.push_back("青蛙");
    JBHNames_Chinese.push_back("树袋熊");
    JBHNames_Chinese.push_back("蜻蜓");
    JBHNames_Chinese.push_back("骆驼");
    JBHNames_Chinese.push_back("乌龟");
    JBHNames_Chinese.push_back("蝴蝶");
    JBHNames_Chinese.push_back("海豚");
    JBHNames_Chinese.push_back("鲸鱼");
    JBHNames_Chinese.push_back("鹿");
    JBHNames_Chinese.push_back("熊");
    JBHNames_Chinese.push_back("天鹅");
    JBHNames_Chinese.push_back("螃蟹");
    JBHNames_Chinese.push_back("鲨鱼");
    JBHNames_Chinese.push_back("长颈鹿");
    JBHNames_Chinese.push_back("企鹅");
    JBHNames_Chinese.push_back("狼");
    JBHNames_Chinese.push_back("猫头鹰");
    JBHNames_Chinese.push_back("猫");
    JBHNames_Chinese.push_back("孔雀");
    JBHNames_Chinese.push_back("变色龙");
    JBHNames_Chinese.push_back("袋鼠");
    JBHNames_Chinese.push_back("刺猬");
    JBHNames_Chinese.push_back("松鼠");
    
    JBHNames_English.push_back("mouse");
    JBHNames_English.push_back("cow");
    
    
    
    
    
    SceneStickFigureDialog::addBoughtAnimalDatas(1, 1);
 
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm/201-unknown_-_out_of_valley-muji.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/201-unknown_-_out_of_valley-muji.mp3",true);
    
    
    elfsSize = 1;
    stickFigureSize = 1;
    //newBoughtJBHSet = new int[JBH_SET_NUMBER];
    /*
    for(int i = 0;i < JBH_SET_NUMBER;i++)
    {
        *(newBoughtJBHSet + i) = 0;
    }
    */

    Vec2 posV = Director::getInstance()->getVisibleOrigin();
    
  
	init_ui();
    elf_id = 1;
    elfIdTemp =1;
    elf_id_vector = 0;
    elfIdVectorTemp = 0;
    boughtElfId = 4;
    scene_id = 1;
    sceneIdTemp = 1;
    sceneVectorId = 0;
    sceneVectorIdTemp = 0;
    stickFigure_id = 1;
    stickfigureIdTemp = 1;
    stickFigure_id_vector = 0;
    stickFigureIdVectorTemp = 0;
    jbhName = "laoshu_001";
    jbhNameTemp = "laoshu_001";
    
    
   //create massive code
    for (int i = 1; i <= 41; i++) {
        //CCLOG("DIBANS.pushback(diban_figure%d)",i);
    }
    for (int j = 1; j <= 41; j++) {
        //CCLOG("FIGURES.pushback(_figure%d)",j);
    }
    //SceneStickFigureDialog::readJBH_JLFromUserData();
    
    
    /*
    //test for Util::strSplit
    //outcome is test 1 2 3
    //const char* testChar = "test#1#2#3";//output test 1 2 3
    std::string testString = "#1#2#3#";
    std::vector<std::string> wordsout;
    Util::strSplit(testString, "#", wordsout);
    CCLOG("wordsout'size is %d",wordsout.size());
    CCLOG("split words are");
    for(int i = 0;i < wordsout.size();i++){
        CCLOG("%s",wordsout.at(i).c_str());
    }
    */
    
    
    //COVEN
    delete data;
    data = NULL;
    
    return true;
}

/*
void SceneTitle::testForSpriteBatchNode(){
    std::string hbPlist = "newPlist12-12/hbTouXiangs.plist";
    std::string csPlist = "newPlist12-12/csTouXiangs.plist";
    std::string hbSheet = "newPlist12-12/hbTouXiangs.pvr.ccz";
    std::string csSheet = "newPlist12-12/csTouXiangs.pvr.ccz";
    
    SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile(hbPlist);
    spriteCache->addSpriteFramesWithFile(csPlist);
    CCSize windowSize = Director::getInstance()->getVisibleSize();
    for(int i = 1;i < 42;i++){
        std::string frameName;
        if(i < 10){
            frameName = "stickfigure_xx_00" + Util::int_to_str(i) + "_hb.png";
        }else{
            frameName = "stickfigure_xx_0" + Util::int_to_str(i) + "_hb.png";
        }
        Sprite* touXiang = Sprite::createWithSpriteFrameName(frameName);
        if(i % 10 == 0){
            touXiang->setPosition(Vec2((i/41.0f) * windowSize.width, windowSize.height / 2));
            this->addChild(touXiang);
        }
    }
    
    
}
 */


void SceneTitle::setLocalPlistValueTo(std::string allHaveBeenBought){
    UserData* data = new UserData();
    __Dictionary* plistDic = data->plistDic;
    __Dictionary* jbhDic = data->jbhDic;
    __Dictionary* elfDic = data->elfDic;
    std::string path = CCFileUtils::getInstance()->getWritablePath();
    std::string _doc1 = path + "test.plist";
    __String* hasBought = __String::create(String::createWithFormat("%s","no")->getCString());
    elfDic->setObject(hasBought, "1");
    elfDic->setObject(hasBought, "2");
    
    jbhDic->setObject(hasBought, "1");
    jbhDic->setObject(hasBought, "2");
    jbhDic->setObject(hasBought, "3");
    jbhDic->setObject(hasBought, "4");
    jbhDic->setObject(hasBought, "5");
    jbhDic->setObject(hasBought, "6");
    jbhDic->setObject(hasBought, "7");
    jbhDic->setObject(hasBought, "8");
    
    plistDic->writeToFile(_doc1.c_str());
}




bool SceneTitle::init_ui()
{
    srand((unsigned)time(nullptr));
    CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
	Layout* ui = nullptr;
	{

		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/SceneTitle/SceneTitle.ExportJson"));
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));

		float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
		ui->setPosition(Vec2(gx, gy));

        
        
        
        
		//my comment:
        //uiRegButton的第二个参数就是传入的name
        //而uiRegButton下的getByName中的name是在ExportJson文件中定义的
        //第三个参数是tag,which is defined in the KTGGlobalDef.h
		uiRegButton(ui, "btn_setup", kTagBtnSetup, zTagDefault);
		uiRegButton(ui, "btn_scene", kTagBtnScene, zTagDefault);
		uiRegButton(ui, "btn_elf", kTagBtnJinglingTuqian, zTagDefault);
		uiRegButton(ui, "btn_stickfigure", kTagBtnJBHTuqian, zTagDefault);
		uiRegButton(ui, "btn_huace", kTagBtnBaoBao, zTagDefault);

		uiRegButton(ui, "btn_mode_yd", kTagBtnModeYd, zTagDefault);
		uiRegButton(ui, "btn_mode_mh", kTagBtnModeMh, zTagDefault);
		uiRegButton(ui, "btn_mode_zy", kTagBtnModeZy, zTagDefault);
        
        setup = (Button*)ui->getChildByName("btn_setup");
        scene = (Button*)ui->getChildByName("btn_scene");
        elf = (Button*)ui->getChildByName("btn_elf");
        stickFigure = (Button*)ui->getChildByName("btn_stickfigure");
        huace = (Button*)ui->getChildByName("btn_huace");
        modeYD = (Button*)ui->getChildByName("btn_mode_yd");
        modeMH = (Button*)ui->getChildByName("btn_mode_mh");
        modeZY = (Button*)ui->getChildByName("btn_mode_zy");
        
        modeMH->setZOrder(2);
        modeYD->setZOrder(2);
        modeZY->setZOrder(2);
        
        
        auto img_title = (ImageView*)ui->getChildByName("img_title");
        if(img_title){
            img_title->loadTexture("ui/SceneTitle/fengmian_dbt-1-6.png");
            img_title->setScale(360.0/719);
        }
        
        
        
        //加载云动画
        ArmatureDataManager::getInstance()->addArmatureFileInfo("an/yun3/yun3.ExportJson");
        auto arm = Armature::create("yun3");
        //this->addChild(arm);
        ui->addChild(arm, 0);
        arm->setGlobalZOrder(0);
        

        
        arm->setAnchorPoint(Vec2(0.5f,0.5f));
        arm->setPosition(400,300);
        arm->getAnimation()->play("Animation1");
    
        
        //test
        //我想知道假如让一个按钮不可见，在那个区域里触摸是否会响应触摸
        //不会
        //btn_huace->setVisible(false);
        
        
        
		//onClickUi(nullptr, TouchEventType::TOUCH_EVENT_CANCELED);
        //my comment:
        //what is the use of the call of the onClickUI here? maybe for test
        
        
		/*
		{
			Widget* wg = ui->getChildByName("tf_input");
			Util::replaceTextFieldToEditBox(wg, kTagEditBoxInputSearchKey, this);
		}
		*/
	}
	//_uiRoot = ui;
	//this->addChild(ui, zTagBtnRefresh - 100);
    
    this->addChild(ui, 0);

    
    
	return true;
}

/*
void SceneTitle::menuCloseCallback(Ref* pSender)
{


// 	std::vector<Point> points = {
// 		Point(1, 1),
// 		Point(10, 10),
// 		Point(20, 20),
// 		Point(30, 40),
// 		Point(30, 50),
// 		Point(30, 60)
// 	};


	Node* canvas = this->getChildByTag(kTagCanvas);

	std::vector<Point> points = {
		Point(498, 463),
		Point(503, 461),
		Point(508, 460),
		Point(513, 459),
		Point(518, 458),
		Point(523, 458),
		Point(528, 458),
		Point(533, 459),
		Point(538, 460),
		Point(543, 461),
		Point(548, 463),
		Point(553, 466),
		Point(558, 468),
		Point(563, 472),
		Point(568, 476),
		Point(573, 481),
		Point(578, 487),
		Point(583, 496),
		Point(585, 501),
		Point(587, 506),
		Point(588, 511),
		Point(589, 516),
		Point(589, 521),
		Point(590, 526),
		Point(590, 531),
		Point(589, 536),
		Point(588, 541),
		Point(587, 546),
		Point(585, 551),
		Point(583, 556),
		Point(580, 561),
		Point(577, 566),
		Point(573, 571),
		Point(568, 575),
		Point(563, 580),
		Point(558, 583),
		Point(553, 586),
		Point(548, 588),
		Point(543, 590),
		Point(538, 591),
		Point(533, 592),
		Point(528, 593),
		Point(523, 593),
		Point(518, 593),
		Point(513, 593),
		Point(508, 592),
		Point(503, 591),
		Point(498, 589),
		Point(493, 586),
		Point(488, 584),
		Point(483, 580),
		Point(478, 576),
		Point(473, 571),
		Point(468, 566),
		Point(465, 561),
		Point(462, 556),
		Point(460, 551),
		Point(458, 546),
		Point(456, 541),
		Point(456, 536),
		Point(455, 531),
		Point(455, 526),
		Point(455, 516),
		Point(456, 511)
	};

	Sprite* sp = Sprite::create("tracer.png");
	sp->setScale(0.5f);
	sp->setPosition(points[0]);
	canvas->addChild(sp);

	playActionPointPath(sp, points, 0);

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
 */



void SceneTitle::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
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


void SceneTitle::setupKeJian()
{
    SceneTitleUserData* data = SceneTitleUserData::getInstance(this);
    SceneController::getInstance()->data = data;
    CCLOG("when the data is uploaded---------------------");
    data->printData();
    
    Util::cleanTextureCacheWithMessage("exit title");
    
    SceneStickFigureDialog::readJBH_JLFromUserData();
    SceneSetupDialog* setupScene = SceneSetupDialog::create();
    setupScene->sceneTitle = this;
    
    auto scene = Scene::create();
    scene->addChild(setupScene);
    Director::getInstance()->replaceScene(scene);
}



void SceneTitle::loadYunPlists(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("an/yun3/yun30.plist");
}


void SceneTitle::sceneKeJian()
{
    SceneStickFigureDialog::readJBH_JLFromUserData();
    SceneDialog* scene = SceneDialog::create();//init() is called
    //thus, initScenes() is called before initBlueRing_Word();
    scene->sceneTitle = this;
    scene->sceneId = scene_id;
    scene->initBlueRing_Word();
    this->addChild(scene,1);
    scene->isDirectEntered = true;
    
}

void SceneTitle::elfKeJian()
{
    SceneStickFigureDialog::readJBH_JLFromUserData();
    SceneElfDialog* scene = SceneElfDialog::create();
    scene->sceneTitle = this;
    this->addChild(scene,1);
    scene->initData(elf_id, elf_id_vector, boughtElfId);
    scene->initBlueRing_Word();
    scene->isDirectEntered = true;
}

void SceneTitle::elfKeJian_YD()
{
    SceneStickFigureDialog::readJBH_JLFromUserData();
    SceneElfDialog* scene = SceneElfDialog::create();
    scene->sceneTitle = this;
    int xx = scene->elfsSize;
    int added_size = xx - elfsSize;
    elfsSize = scene->elfsSize;
    
    this->addChild(scene,1);
    if(elf_id_vector == 0)
    {
        scene->elfId = elf_id;
        scene->elfIdVector = elf_id_vector;
        scene->initBlueRing_Word();
    }
    else
    {
        scene->elfId = elf_id;
        scene->elfIdVector = elf_id_vector + added_size;
        scene->initBlueRing_Word();
    }
    scene->isDirectEntered = false;
    scene->make_a_change();//从引导模式进入时需要做的一系列变化
}


void SceneTitle::confirmUserChoices()
{
    scene_id = sceneIdTemp;
    sceneVectorId = sceneVectorIdTemp;
    elf_id = elfIdTemp;
    elf_id_vector = elfIdVectorTemp;
    jbhName = jbhNameTemp;
    stickFigure_id = stickfigureIdTemp;
    stickFigure_id_vector = stickFigureIdVectorTemp;
    squareBlueRingId = squareBlueRingIdTemp;
    
    CCLOG("when the data is confirmed--------------");
    CCLOG("JBH id is %d", stickFigure_id);
}

void SceneTitle::playMHEffect1()
{
    SimpleAudioEngine::getInstance()->playEffect("描红模式.wav");
}
void SceneTitle::playMHEffect2()
{
    SimpleAudioEngine::getInstance()->playEffect("描红模式使用提示.wav");
}
void SceneTitle::playZYEffect1()
{
    SimpleAudioEngine::getInstance()->playEffect("自由模式.wav");
}
void SceneTitle::playZYEffect2()
{
    SimpleAudioEngine::getInstance()->playEffect("自由模式使用提示.wav");
}


Vector<__String*> SceneTitle::getCCStringVectorFromUserData(UserData *data)
{
    __Dictionary* oldJBH = data->jbhDic;
    __String* oldJBH1 = dynamic_cast<__String*>(oldJBH->objectForKey("1"));
    __String* oldJBH2 = dynamic_cast<__String*>(oldJBH->objectForKey("2"));
    __String* oldJBH3 = dynamic_cast<__String*>(oldJBH->objectForKey("3"));
    __String* oldJBH4 = dynamic_cast<__String*>(oldJBH->objectForKey("4"));
    __String* oldJBH5 = dynamic_cast<__String*>(oldJBH->objectForKey("5"));
    /*
    __String* oldJBH6 = dynamic_cast<__String*>(oldJBH->objectForKey("6"));
    __String* oldJBH7 = dynamic_cast<__String*>(oldJBH->objectForKey("7"));
    __String* oldJBH8 = dynamic_cast<__String*>(oldJBH->objectForKey("8"));
    */
    
    Vector<__String*> oldJBHs;
    oldJBHs.pushBack(oldJBH1);
    oldJBHs.pushBack(oldJBH2);
    oldJBHs.pushBack(oldJBH3);
    oldJBHs.pushBack(oldJBH4);
    oldJBHs.pushBack(oldJBH5);
    //oldJBHs.pushBack(oldJBH6);
   // oldJBHs.pushBack(oldJBH7);
    //oldJBHs.pushBack(oldJBH8);
    
    return oldJBHs;
}


int* SceneTitle::getNewBoughtSet(Vector<__String*> oldJBHDic, Vector<__String*> newJBHDic)
{
    int* newBoughtSet = new int[JBH_SET_NUMBER];
    for (int i = 0; i < JBH_SET_NUMBER; i++) {
        *(newBoughtSet + i) = 0;
    }
    int i = 0;
    for (int ii = 0; ii < oldJBHDic.size(); ii++) {
        //ii = 0-7
        int oldLength = oldJBHDic.at(ii)->length();
        int newLength = newJBHDic.at(ii)->length();
        if(oldLength == 2 && newLength == 3)
        {
            *(newBoughtSet + i) = ii + 1;
            i++;
        }
    }
    return newBoughtSet;
}

int SceneTitle::getNewBoughtSetNum(Vector<cocos2d::__String *> oldJBHDic, Vector<cocos2d::__String *> newJBHDic)
{
    int result = 0;
    for (int ii = 0; ii < oldJBHDic.size(); ii++) {
        //ii = 0-7
        int oldLength = oldJBHDic.at(ii)->length();
        int newLength = newJBHDic.at(ii)->length();
        if(oldLength == 2 && newLength == 3)
        {
            result++;
        }
    }
    return result;
}




void SceneTitle::stickFigureKeJian()
{
    //setup->setVisible(true);
    SceneStickFigureDialog::readJBH_JLFromUserData();
    
    //创建简笔画实例
    SceneStickFigureDialog* scene = SceneStickFigureDialog::create();
    scene->sceneTitle = this;
    this->addChild(scene,1);
    
    
    //从新老userData获取newBoughtSet(int*)
    //and newBoughtSetNum(int)
    UserData* newUserData = new UserData();
    Vector<__String*> newLocalJBHStrings = getCCStringVectorFromUserData(newUserData);
    for (int i = 0; i < newLocalJBHStrings.size(); i++) {
        CCLOG("new String %d %s",i,newLocalJBHStrings.at(i)->getCString());
        CCLOG("old String %d %s",i,localJBHStrings.at(i)->getCString());
    }
    int* newBoughtSet = getNewBoughtSet(localJBHStrings, newLocalJBHStrings);
    int newBoughtSetNum = getNewBoughtSetNum(localJBHStrings, newLocalJBHStrings);
    //get newIdVector
    int newIdVector = scene->initUserData(stickFigure_id, stickFigure_id_vector, newBoughtSet, newBoughtSetNum);
    //update stickFigure_id_vector in sceneTitle and localJBHStrings
    stickFigure_id_vector = newIdVector;
    localJBHStrings = newLocalJBHStrings;
   
    
    
    
    //初始化简笔画彩色部分与蓝环
    scene->initBlueRing_Word();
    //虽然在每次选择简笔画的时候
    //selected_stickfigure_id会更新，但是每次进入简笔画图鉴的时候
    //selected_stickfigure_id会被初始化为1
    
    CCLOG("boughtSetNum is %d", newBoughtJBHSetNumber);
    for (int i = 0; i < newBoughtJBHSetNumber; i++) {
        CCLOG("the bought setId is %d",*(newBoughtJBHSet + i));
    }
    
    
    scene->squareBlueRing_id = squareBlueRingId;
    scene->initSquareBlueRing();
    
    scene->isDirectEntered = true;
    
    
}
void SceneTitle::huaceKeJian()
{
    SceneHuaceDialog* scene = SceneHuaceDialog::create();
    this->addChild(scene,1);
}

void SceneTitle::clearCache(){
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    SceneTitle::loadYunPlists();
}
void SceneTitle::modeZYKeJian()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    
    SceneTitleUserData* data = SceneTitleUserData::getInstance(this);
    SceneController::getInstance()->data = data;
    
    CCLOG("when the data is uploaded---------------------");
    data->printData();
    
    SceneStickFigureDialog::readJBH_JLFromUserData();
    
    
    this->retain();
    this->removeAllChildrenWithCleanup(true);
    Util::cleanTextureCacheWithMessage("exit title");
    
    SceneController::getInstance()->replaceScane(eSceneIdSceneModeFreeDraw);
    CCLOG("in free");
    CCLOG("%s",Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

/*
void SceneTitle::onExit(){
    Layer::onExit();
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    
    
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    
    Util::cleanTextureCacheWithMessage("exit title");
    
}
*/


void SceneTitle::modeMHKeJian()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    
    //从本地读取用户购买数据，并填充全局变量boughtAnimalDatas
    //memory leak issue
    SceneStickFigureDialog::readJBH_JLFromUserData();
    
    
    
    SceneTitleUserData* data = SceneTitleUserData::getInstance(this);
    SceneController::getInstance()->data = data;
    CCLOG("when the data is uploaded---------------------");
    data->printData();
    
    
    this->retain();
    this->removeAllChildrenWithCleanup(true);
    this->release();
    Util::cleanTextureCacheWithMessage("exit title to mh");
    
    auto mhScene = SceneModeGuidStroke::create();
    auto scene = Scene::create();
    scene->addChild(mhScene);
    Director::getInstance()->replaceScene(scene);
    
    
}


void SceneTitle::getDataFromSceneController()
{
    SceneTitleUserData* data = SceneController::getInstance()->data;
    
    
    scene_id= data->scene_id;  //1～3
    sceneIdTemp= data->sceneIdTemp;
    sceneVectorId = data->sceneVectorId;
    sceneVectorIdTemp = data->sceneVectorIdTemp;
    
    
    
    elf_id= data->elf_id;// 1~3
    elfIdTemp= data->elfIdTemp;
    elf_id_vector= data->elf_id_vector; //0~2
    elfIdVectorTemp= data->elfIdVectorTemp;
    elfs= data->elfs;
    elfsSize= data->elfsSize;
    selected_elf_id= data->selected_elf_id;//传递给引导模式，用于随机精灵
    
    
    stickFigure_id= data->stickFigure_id;
    stickfigureIdTemp= data->stickfigureIdTemp;
    stickFigure_id_vector= data->stickFigure_id_vector;//0 ~ 40
    stickFigureIdVectorTemp= data->stickFigureIdVectorTemp;
    squareBlueRingId= data->squareBlueRingId;//1~3
    squareBlueRingIdTemp= data->squareBlueRingIdTemp;
    jbhName= data->jbhName;//从简笔画的下面三幅图得到的文件名
    jbhNameTemp= data->jbhNameTemp;
    stickFigureSize= data->stickFigureSize;
    localJBHStrings = data->getLocalJBHData();
    
    delete data;
}

void SceneTitle::onClickUi(Ref* sender, TouchEventType type)
{
	int id = -1;
	Button* btn = dynamic_cast<Button*>(sender);
	if (btn != nullptr)
	{
		id = btn->getTag();
	}

	if (type != TOUCH_EVENT_ENDED)
		return;

	CCLOG("onClick!!! id=%d", id);

	// SimpleAudioEngine::getInstance()->playEffect(SND4_BTN1);


	if (id == kTagBtnSetup)
	{
        //CCLOG("setup button is activated!");
        //添加按钮动画
        /*
        ArmatureDataManager::getInstance()->addArmatureFileInfo("an/btn_setup/btn_setup.ExportJson");
        auto arm = Armature::create("btn_setup");

        this->addChild(arm,1,1000);
        arm->setAnchorPoint(Vec2(0.5f,0.5f));
        Vec2 point = btn->getPosition();
        point.x = point.x - 180;
        arm->setPosition(point);
        arm->getAnimation()->play("Animation1");
        */
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::setupKeJian, this));
        setup->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
        
        
	}
    
    
	else if (id == kTagBtnScene)
	{
        //int scene_id = eSceneIdSceneDialog;
        //SceneController::getInstance()->replaceScane(scene_id);
        //SceneController::getInstance()->addScene(this, scene_id);
        /*
        SceneDialog* scene = SceneDialog::create();
        scene->sceneTitle = this;
        scene->initBlueRing_Word(scene_id);
        this->addChild(scene);
        */
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        SimpleAudioEngine::getInstance()->playEffect("场景图鉴.wav");
        //SimpleAudioEngine::getInstance()->unloadEffect("场景图鉴.wav");
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::sceneKeJian, this));
        scene->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
        
	}
	else if (id == kTagBtnJinglingTuqian)
	{
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::elfKeJian, this));
        SimpleAudioEngine::getInstance()->playEffect("精灵图鉴.wav");
        elf->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
	}
	else if (id == kTagBtnJBHTuqian)
	{
        //简笔画对话框
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::stickFigureKeJian, this));
        SimpleAudioEngine::getInstance()->playEffect("简笔画图鉴.wav");
        //plist添加测试
        //测试效果不好，大概是延时3-4s
        //SpriteFrameCache* cache = SpriteFrameCache::getInstance();
        //cache->addSpriteFramesWithFile("ui/StickFigureDialog_1/plist_figures/plist_figures.plist", "ui/StickFigureDialog_1/plist_figures/plist_figures.png");
        /*
        SpriteFrameCache* cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("ui/StickFigureDialog_1/plist_figures/plist_figures.plist", "ui/StickFigureDialog_1/plist_figures/plist_figures.png");
        cache->addSpriteFramesWithFile("ui/StickFigureDialog_1/plist_figures_2/plist_figures_2.plist", "ui/StickFigureDialog_1/plist_figures_2/plist_figures_2.png");
        cache->addSpriteFramesWithFile("ui/StickFigureDialog_1/plist_figures_3/plist_figures_3.plist", "ui/StickFigureDialog_1/plist_figures_3/plist_figures_3.png");
        */
        
        
        stickFigure->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
        
        
	}
	else if (id == kTagBtnBaoBao)
	{
        //宝宝画册
        //int scene_id = eSceneIdSceneHuaceDialog;
        //SceneController::getInstance()->addScene(this, scene_id);
        
        
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::huaceKeJian, this));
        SimpleAudioEngine::getInstance()->playEffect("宝宝画册.wav");
        huace->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
	}
	else if (id == kTagBtnModeYd)
    {
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        SimpleAudioEngine::getInstance()->playEffect("引导模式.wav");
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::elfKeJian_YD, this));
        modeYD->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
	}
	else if (id == kTagBtnModeMh)
	{
		//int scene_id = eSceneIdSceneHaceDeleteDialog;
		//SceneController::getInstance()->addScene(this, scene_id);
        //SceneController::getInstance()->replaceScane(eSceneIdSceneModeGuidStroke);
        
        
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
    
        
        SimpleAudioEngine::getInstance()->playEffect("描红模式.wav");
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::modeMHKeJian, this));
        DelayTime* delay = DelayTime::create(0.1f);
        modeMH->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            //,delay
                                            ,call
                                            ,NULL));
	}
	else if (id == kTagBtnModeZy)
	{
        //int scene_id = eSceneIdSceneModeFreeDraw;
		//SceneController::getInstance()->replaceScane(scene_id);
        //按钮动画
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        
        SimpleAudioEngine::getInstance()->playEffect("自由模式.wav");
        CallFunc* call = CallFunc::create(CC_CALLBACK_0(SceneTitle::modeZYKeJian, this));
        modeZY->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
	}
}

void SceneTitle::uiRegButton(Widget* parent, const std::string& name, int k, int z)
{
    Button* btn = (Button*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneTitle::onClickUi));
		btn->setZOrder(z);
	}

}



