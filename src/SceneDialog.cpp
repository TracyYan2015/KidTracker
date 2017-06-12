#include "SceneDialog.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
#include "SceneModeGuidDraw.h"
#include "SceneStickFigureDialog.h"




USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

enum kTag
{
	kTagCanvas = 100,
};

std::vector<std::string> SceneDialog::SCENE_PlIST_PATHS = {"ui/SceneDialog_1/plist_scenes/plist_scenes.plist","an/BlueRing/BlueRing0.plist"};



Scene* SceneDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneDialog::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Util::cleanTextureCacheWithMessage("");
    Util::loadPlists(SCENE_PlIST_PATHS);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/new_added/new_added_plist.plist", "ui/new_added/new_added_plist.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/SceneDialog_1/addedScenes/addedScenes.plist","ui/SceneDialog_1/addedScenes/addedScenes.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/SceneDialog_1/scene8-12/scene8-12.plist","ui/SceneDialog_1/scene8-12/scene8-12.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/SceneDialog_1/scene13-16/scene13-16.plist","ui/SceneDialog_1/scene13-16/scene13-16.pvr.ccz");
    
    SCENES_NUMBER = 15;
    diban_scene1 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene1 = ImageView::create("scene_xx_001_hb.png",Widget::TextureResType::PLIST);
    diban_scene2 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene2 = ImageView::create("scene_xx_002_hb.png",Widget::TextureResType::PLIST);
    diban_scene3 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene3 = ImageView::create("scene_xx_003_hb.png",Widget::TextureResType::PLIST);
    diban_scene4 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene4 = ImageView::create("scene_xx_004_hb.png",Widget::TextureResType::PLIST);
    diban_scene5 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene5 = ImageView::create("scene_xx_005_hb.png",Widget::TextureResType::PLIST);
    diban_scene6 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene6 = ImageView::create("scene_xx_006_hb.png",Widget::TextureResType::PLIST);
    diban_scene7 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene7 = ImageView::create("scene_xx_007_hb.png",Widget::TextureResType::PLIST);
    
    diban_scene8 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene8 = ImageView::create("scene_xx_008_hb.png",Widget::TextureResType::PLIST);
    diban_scene9 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene9 = ImageView::create("scene_xx_009_hb.png",Widget::TextureResType::PLIST);
    diban_scene10 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene10 = ImageView::create("scene_xx_010_hb.png",Widget::TextureResType::PLIST);
    diban_scene11 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene11 = ImageView::create("scene_xx_011_hb.png",Widget::TextureResType::PLIST);
    diban_scene12 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene12 = ImageView::create("scene_xx_012_hb.png",Widget::TextureResType::PLIST);
    diban_scene13 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene13 = ImageView::create("scene_xx_013_hb.png",Widget::TextureResType::PLIST);
    
    diban_scene14 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene14 = ImageView::create("scene_xx_014_hb.png",Widget::TextureResType::PLIST);
    diban_scene15 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene15 = ImageView::create("scene_xx_015_hb.png",Widget::TextureResType::PLIST);
    diban_scene16 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _scene16 = ImageView::create("scene_xx_016_hb.png",Widget::TextureResType::PLIST);
    
    
    generalDibans.pushBack(diban_scene1);
    generalDibans.pushBack(diban_scene2);
    generalDibans.pushBack(diban_scene3);
    generalDibans.pushBack(diban_scene4);
    generalDibans.pushBack(diban_scene5);
    generalDibans.pushBack(diban_scene6);
    generalDibans.pushBack(diban_scene7);
    generalDibans.pushBack(diban_scene8);
    generalDibans.pushBack(diban_scene9);
    generalDibans.pushBack(diban_scene10);
    generalDibans.pushBack(diban_scene11);
    generalDibans.pushBack(diban_scene12);
    generalDibans.pushBack(diban_scene13);
    generalDibans.pushBack(diban_scene14);
    generalDibans.pushBack(diban_scene15);
    generalDibans.pushBack(diban_scene16);
    
    
    generalScenes.pushBack(_scene1);
    generalScenes.pushBack(_scene2);
    generalScenes.pushBack(_scene3);
    generalScenes.pushBack(_scene4);
    generalScenes.pushBack(_scene5);
    generalScenes.pushBack(_scene6);
    generalScenes.pushBack(_scene7);
    generalScenes.pushBack(_scene8);
    generalScenes.pushBack(_scene9);
    generalScenes.pushBack(_scene10);
    generalScenes.pushBack(_scene11);
    generalScenes.pushBack(_scene12);
    generalScenes.pushBack(_scene13);
    generalScenes.pushBack(_scene14);
    generalScenes.pushBack(_scene15);
    generalScenes.pushBack(_scene16);
    
    isDirectEntered = true;
    Vec2 posV = Director::getInstance()->getVisibleOrigin();
    
    init_ui();
    return true;
}




void SceneDialog::scenes_layout(Vector<Sprite*> dibans, Vector<ImageView*> scenes)
{
    cocos2d::ui::ScrollView* scrollview = (cocos2d::ui::ScrollView*)ui->getChildByName("Scenes");
    for(int i=0; i<dibans.size(); i++)
    {
        if(dibans.at(i) != nullptr){
            scrollview->addChild(dibans.at(i),0);
            dibans.at(i)->ignoreAnchorPointForPosition(false);
            dibans.at(i)->setAnchorPoint(Vec2(0.5f,0.5f));
            dibans.at(i)->setPosition(Vec2(120+i*236,150));
        }
    }
    
    for (int i = 0;i < scenes.size();i++) {
        if(scenes.at(i) != nullptr){
            scrollview->addChild(scenes.at(i),0);
            scenes.at(i)->ignoreAnchorPointForPosition(false);
            scenes.at(i)->setAnchorPoint(Vec2(0.5f,0.5f));
            scenes.at(i)->setPosition(Vec2(120+i*236,150));
        }
        
    }
}

void SceneDialog::createScene(int sceneId){
    
}



void SceneDialog::initScenes(){
    scenes.pushBack(_scene1);
    dibans.pushBack(diban_scene1);
    _scene1->setTag(kTagBtnScene1);
    _scene1->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi_ImageView));
    
    __String* scene1Name = __String::createWithFormat("%s","scene_xx_001_hb.png");
    scenesHBFileNames.pushBack(scene1Name);
    
    
    UserData* data = new UserData();
    data->showData();
    __Dictionary* sceneDic = data->sceneDic;
    __Array* keys = sceneDic->allKeys();
    
    Util::sortCCStringArray(keys);
    
    for (int i = 1; i < keys->count() + 1; i++) {
        __String* tmp = dynamic_cast<__String*>(keys->getObjectAtIndex(i - 1));
        std::string key = tmp->getCString();
        CCLOG("%s",key.c_str());
        __String* hasBought = dynamic_cast<__String*>(sceneDic->objectForKey(key));
        if (hasBought->length() == 3) {
            //give the scenes
            CCLOG("%d", 3 * i - 2);
            CCLOG("%d", 3 * i - 1);
            CCLOG("%d", 3 * i - 0);
            scenes.pushBack(generalScenes.at(3 * i - 2));
            scenes.pushBack(generalScenes.at(3 * i - 1));
            scenes.pushBack(generalScenes.at(3 * i - 0));
            dibans.pushBack(generalDibans.at(3 * i - 2));
            dibans.pushBack(generalDibans.at(3 * i - 1));
            dibans.pushBack(generalDibans.at(3 * i - 0));
            
            
            int id1 = 3 * i - 1;
            int id2 = 3 * i - 0;
            int id3 = 3 * i + 1;
            std::ostringstream oss1;
            oss1<<id1;
            std::string sId1 = oss1.str();
            std::ostringstream oss2;
            oss2<<id2;
            std::string sId2 = oss2.str();
            std::ostringstream oss3;
            oss3<<id3;
            std::string sId3 = oss3.str();
            
            std::string tmp1 = "scene_xx_00" + sId1 + "_hb.png";
            __String* name1 = __String::create(tmp1);
            std::string tmp2 = "scene_xx_00" + sId2 + "_hb.png";
            __String* name2 = __String::create(tmp2);
            std::string tmp3 = "scene_xx_00" + sId3 + "_hb.png";
            __String* name3 = __String::create(tmp3);
            
            
            scenesHBFileNames.pushBack(name1);
            scenesHBFileNames.pushBack(name2);
            scenesHBFileNames.pushBack(name3);
        
            generalScenes.at(3 * i - 2)->setTag(kTagBtnScene1 + 3 * i - 2);
            generalScenes.at(3 * i - 2)->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi_ImageView));
            generalScenes.at(3 * i - 2)->setZOrder(zTagDefault);
            
            generalScenes.at(3 * i - 1)->setTag(kTagBtnScene1 + 3 * i - 1);
            generalScenes.at(3 * i - 1)->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi_ImageView));
            generalScenes.at(3 * i - 1)->setZOrder(zTagDefault);
            
            generalScenes.at(3 * i - 0)->setTag(kTagBtnScene1 + 3 * i - 0);
            generalScenes.at(3 * i - 0)->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi_ImageView));
            generalScenes.at(3 * i - 0)->setZOrder(zTagDefault);
        }
    }
}



bool SceneDialog::init_ui()
{
	//Size vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    
	ui = nullptr;
	{
        
		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/SceneDialog_1/SceneDialog_1.ExportJson"));
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));
        ui->setBackGroundColor(Color3B(0,0,0));
        ui->setBackGroundColorOpacity(0.4f*255);
        
        
        
        
		float gx = vOrigin.x - (ui->getContentSize().width - Director::getInstance()->getVisibleSize().width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - Director::getInstance()->getVisibleSize().height) / 2;
		ui->setPosition(Vec2(gx, gy));
        
        
        UserData* data = new UserData();
        __Dictionary* jbhDic = data->jbhDic;
        
        initScenes();
        
        
        _jiahao = Sprite::createWithSpriteFrameName("fengmian_lb_bjb_xx.png");
        dibans.pushBack(_jiahao);
        scenes_layout(dibans, scenes);
        uiRegButton(ui, "btn_close", kTagBtnRedClose, zTagDefault);
        
        
        cocos2d::ui::ScrollView* Scenes = (cocos2d::ui::ScrollView*)ui->getChildByName("Scenes");
        int num_scenes = dibans.size();
        int add_width = (num_scenes - 3)*716/3;
        
        Scenes->setInnerContainerSize(CCSize(716+add_width,297));
        

        back = ImageView::create("button_xz_back.png",Widget::TextureResType::PLIST);
        start = ImageView::create("button_xz_start.png",Widget::TextureResType::PLIST);
	}

	this->addChild(ui, zTagBtnRefresh - 100);
    
    
	return true;
}




void SceneDialog::initBlueRing_Word()
{
    //add cs picture, word and blue ring
    std::ostringstream oss;
    oss<<sceneId;
    std::string sScene_idx = oss.str();
    //添加BlueRing动画
    ArmatureDataManager::getInstance()->addArmatureFileInfo("an/BlueRing/BlueRing.ExportJson");
    auto arm = Armature::create("BlueRing");
    
    //needs 2 parameters, one is Vector<__String>,
    //another is __String*
    std::string tmp = "scene_xx_00" + sScene_idx + "_hb.png";
    __String* hbFileName = __String::create(tmp);
    int foundSceneVectorId = Util::findVectorIdByCCString(scenesHBFileNames,hbFileName);
    
    this->sceneVectorId = foundSceneVectorId;
    
    //seems not useful
    cocos2d::ui::ScrollView* scrollview = (cocos2d::ui::ScrollView*)ui->getChildByName("Scenes");
    float percent = (float)foundSceneVectorId/(scenes.size() +1);
    scrollview->jumpToPercentHorizontal(percent);
    
    
    
    
    scenes.at(foundSceneVectorId)->addChild(arm,1,1000);
    arm->setAnchorPoint(Vec2(0.5f,0.5f));
    arm->setPosition(Vec2(100,100));
    arm->getAnimation()->play("Animation1");
    //添加文字
    ImageView* di_ban = (ImageView*)ui->getChildByName("diban");
    Vec2 position = di_ban->getPosition();
    position.x = position.x-230;//凑的
    position.y = position.y-30;
    std::string str1 = "scene_xx_00";
    std::string str2 = "_word.png";
    std::string str4 = "scene_xx_0";
    std::string wordFileName;
    if(sceneId < 10){
        wordFileName = str1 + sScene_idx + str2;
    }else{
        wordFileName = str4 + sScene_idx + str2;
    }

    
    Sprite *_scene_xx_word = Sprite::createWithSpriteFrameName(wordFileName);
    _scene_xx_word->setAnchorPoint(Vec2(0.5f,0.5f));
    di_ban->addChild(_scene_xx_word,1,sceneId);//the third parameter is the tag
    _scene_xx_word->setPosition(position);
    //添加彩色图片
    std::string str3 = "_cs.png";
    std::string fileName;
    if(sceneId < 10){
        fileName = str1 + sScene_idx + str3;
    }else{
        fileName = str4 + sScene_idx + str3;
    }
    
    CCLOG("sceneVectorId is %d", sceneTitle->sceneVectorId);
    scenes.at(foundSceneVectorId)->loadTexture(fileName, Widget::TextureResType::PLIST);
    
    
}


void SceneDialog::updateUserData(int sceneId,int sceneVectorId)
{
    this->sceneId = sceneId;
    sceneTitle->sceneIdTemp = sceneId;
    sceneTitle->sceneVectorIdTemp = sceneVectorId;
}


void SceneDialog::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
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


void SceneDialog::initData(int id)
{
    this->sceneId = id;
}

void SceneDialog::sceneChangedCallback(int newId, ImageView* btn){
    CCLOG("scene %d is touched",newId);
    std::ostringstream oss;
    oss<<sceneId;
    std::string sPreviousId = oss.str();
    std::ostringstream oss1;
    oss1<<newId;
    std::string sNewId = oss1.str();
    std::string previousFileName;
    std::string newFileName;
    std::string wordFileName;
    if(sceneId < 10){
        previousFileName = "scene_xx_00" +sPreviousId + "_hb.png";
    }else{
        previousFileName = "scene_xx_0" +sPreviousId + "_hb.png";
    }
    
    if(newId < 10){
        newFileName = "scene_xx_00" +sNewId + "_cs.png";
        wordFileName = "scene_xx_00" + sNewId + "_word.png";
    }else{
        newFileName = "scene_xx_0" +sNewId + "_cs.png";
        wordFileName = "scene_xx_0" + sNewId + "_word.png";
    }
    
   
    //load hb scene
    scenes.at(sceneVectorId)->loadTexture(previousFileName,Widget::TextureResType::PLIST);
    //load cs scene
    btn->loadTexture(newFileName,Widget::TextureResType::PLIST);
    
    //change the blue ring's position
    scenes.at(sceneVectorId)->removeChildByTag(1000);
    ArmatureDataManager::getInstance()->addArmatureFileInfo("an/BlueRing/BlueRing.ExportJson");
    auto arm = Armature::create("BlueRing");
    btn->addChild(arm,1,1000);
    arm->setAnchorPoint(Vec2(0.5f,0.5f));
    arm->setPosition(Vec2(100,100));
    arm->getAnimation()->play("Animation1");
    
    //change the words description below
    ImageView* di_ban = (ImageView*)ui->getChildByName("diban");
    di_ban->removeChildByTag(sceneId);
    Sprite *word = Sprite::createWithSpriteFrameName(wordFileName);
    word->setAnchorPoint(Vec2(0.5f,0.5f));
    di_ban->addChild(word,1,newId);//the third parameter is the tag
    Vec2 position = di_ban->getPosition();
    position.x = position.x-230;
    position.y = position.y-30;
    word->setPosition(position);
}


void SceneDialog::onClickUi_ImageView(Ref* sender, TouchEventType type){
    cocos2d::ui::ScrollView* listView = (cocos2d::ui::ScrollView*)ui->getChildByName("Scenes");
    int id = -1;
	ImageView* btn_imageview = dynamic_cast<ImageView*>(sender);
	if (btn_imageview != nullptr)
	{
		id = btn_imageview->getTag();
	}
	if (type != TOUCH_EVENT_ENDED)
		return;
    
    
    
    if(id >= kTagBtnScene1 && id <= kTagBtnScene16){
        int newVectorId = (btn_imageview->getPosition().x - 120) / 236;
        sceneChangedCallback(id - kTagBtnScene1 + 1,btn_imageview);
        if(id == kTagBtnScene1){
            updateUserData(1,0);
        }else{
            updateUserData(id - kTagBtnScene1 + 1,newVectorId);
        }
        
        
        sceneVectorId = newVectorId;
    }
    else if(id == kTagBtnStart_scene)
    {
        //开始
        //进入引导模式
        
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneDialog::startFunc, this));
        btn_imageview->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
    }
    else if (id == kTagBtnBack_scene)
    {
        //返回到简笔画对话框
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneDialog::backFunc, this));
        btn_imageview->runAction(CCSequence::create(action1
                                                    ,action2
                                                    ,action3
                                                    ,action4
                                                    ,action5
                                                    ,action6
                                                    ,call
                                                    ,NULL));
    
    }
    
}


void SceneDialog::make_a_change()
{
    //修改标题图片
    ImageView* bian_kuang = (ImageView*)ui->getChildByName("bian_kuang");
    ImageView* biaoti = (ImageView*)bian_kuang->getChildByName("biao_ti");
    biaoti->loadTexture("scenc_xz_bt.png",Widget::TextureResType::PLIST);
    
    //修改关闭按钮图片
    Button* btn_close = (Button*)ui->getChildByName("btn_close");
    btn_close->loadTextureNormal("button_home_1.png",Widget::TextureResType::PLIST);
    
    //增加上一步和开始按钮
    back->setAnchorPoint(Vec2(0, 1));
    this->addChild(back);
    back->setPosition(Vec2(960/2, 768 - 1344/2));
    
    
    start->setAnchorPoint(Vec2(0, 1));
    this->addChild(start);
    start->setPosition(Vec2(1420/2, 768 - 1344/2));
    
    //注册back
    back->setTag(kTagBtnBack_scene);
    back->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi_ImageView));
    back->setZOrder(20);
    
    //注册开始
    start->setTag(kTagBtnStart_scene);
    start->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi_ImageView));
    start->setZOrder(20);
    
    
}
/*
void SceneDialog::onExit(){
    Layer::onExit();
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    
    Util::cleanTextureCacheWithMessage("exit title");
    
}
 */


void SceneDialog::startFunc()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    
    sceneTitle->confirmUserChoices();
    
    Util::cleanTextureCacheWithMessage("exit scene dialog to enter YD mode");
    
    SceneModeGuidDraw* ydScene = SceneModeGuidDraw::create();
    ydScene->sceneTitle = sceneTitle;
    ydScene->elfsSize = sceneTitle->elfsSize;
    ydScene->selectedElfId = sceneTitle->elf_id;
    ydScene->elfs = sceneTitle->elfs;
    
    
    //set the txt file name with jbhName in the sceneTitle
    std::string pictureDataFileName = sceneTitle->jbhName + ".txt";
    CCLOG("pictureDataFileName is %s", pictureDataFileName.c_str());
   
    
    
    ydScene->initPictureData(pictureDataFileName);
    ydScene->initElf();
    ydScene->sceneid = sceneTitle->scene_id;
    ydScene->initBackground(sceneTitle->scene_id);
    
    SceneTitleUserData* data = SceneTitleUserData::getInstance(sceneTitle);

    
    SceneController::getInstance()->data = data;
    CCLOG("when the data is uploaded---------------------");
    data->printData();
    
    auto scene = Scene::create();
    scene->addChild(ydScene);
    Director::getInstance()->replaceScene(scene);
    
    
    CCLOG("in YD");
    CCLOG("%s",Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    
    closeCallback();
    //this->retain();
    //this->removeFromParentAndCleanup(true);
}

void SceneDialog::backFunc()
{
    //点击上一步时进入简笔画选择图鉴
    Util::unloadPlists(SCENE_PlIST_PATHS);
    
    
    SceneStickFigureDialog* scene = SceneStickFigureDialog::create();
    scene->sceneTitle = sceneTitle;
    sceneTitle->addChild(scene,1);
    
    
    //从主界面中得数据，具体是从temp里还是不是temp里得数据
    scene->JBHIdVector = sceneTitle->stickFigureIdVectorTemp;
    scene->JBHId = sceneTitle->stickfigureIdTemp;
    scene->initBlueRing_Word();
    scene->squareBlueRing_id = sceneTitle->squareBlueRingIdTemp;
    scene->initSquareBlueRing();
    
    scene->isDirectEntered = false;
    scene->make_a_change();
    
    
    closeCallback1();
    
}

void SceneDialog::onClickUi(Ref* sender, TouchEventType type)
{
	
    cocos2d::ui::ScrollView* listView = (cocos2d::ui::ScrollView*)ui->getChildByName("Scenes");
    int id = -1;
	Button* btn = dynamic_cast<Button*>(sender);
	if (btn != nullptr)
	{
		id = btn->getTag();
	}
    
	if (type != TOUCH_EVENT_ENDED)
		return;
    
	CCLOG("onClick!!! id=%d", id);
    
	
    
    
	
	if (id == kTagBtnRedClose)
	{
        auto action1 = ScaleTo::create(0.2f, 0.9f);
        auto action2 = ScaleTo::create(0.2f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneDialog::closeCallback, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,call
                                          , NULL));
	}
}

void SceneDialog::closeCallback()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
    this->removeAllChildrenWithCleanup(true);
    //coven0202
    this->release();
    
    Util::unloadPlists(SCENE_PlIST_PATHS);
    Util::cleanTextureCacheWithMessage("return from scene");
    
    
   
}
//coven0202
void SceneDialog::closeCallback1()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
    this->removeAllChildrenWithCleanup(true);
    //coven0202
    this->release();
    
    Util::unloadPlists(SCENE_PlIST_PATHS);
    
    
    
}

void SceneDialog::uiRegButton(Widget* parent, const std::string& name, int k, int z)
{
	Button* btn = (Button*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneDialog::onClickUi));
		btn->setZOrder(z);
		//parent->addChild(btn, z);
	}
    
    
    
    
    
    
}




    
    
    

