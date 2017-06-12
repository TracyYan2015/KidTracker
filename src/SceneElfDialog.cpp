#include "SceneElfDialog.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
#include "SceneElfDialog.h"
#include "UserData.h"
#include "SceneStickFigureDialog.h"



USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

enum kTag
{
	kTagCanvas = 100,
};


std::vector<std::string> SceneElfDialog::ELF_PLIST_PATHS = {"an/BlueRing/BlueRing0.plist","plist_elfs/plist_elfs.plist","ui/new_added/new_added_plist.plist","an/Elf1_in_dialog/Elf1_in_dialog0.plist","an/Elf2_in_dialog/Elf2_in_dialog0.plist","an/Elf3_in_dialog/Elf3_in_dialog0.plist","ui/ElfDialog_1/elf-in-dialog4-6/elf-in-dialog4-6.plist","an/elfAni4-6-in-elfDialog/elf_xx_004_wait/elf_xx_004_wait0.plist","an/elfAni4-6-in-elfDialog/elf_xx_005_wait/elf_xx_005_wait0.plist","an/elfAni4-6-in-elfDialog/elf_xx_006_wait/elf_xx_006_wait0.plist"};

Scene* SceneElfDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneElfDialog::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneElfDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Util::cleanTextureCacheWithMessage("");
    Util::loadPlists(ELF_PLIST_PATHS);
    
    isJLGouMai = new bool[3];
    *isJLGouMai = true;
    *(isJLGouMai + 1) = false;
    *(isJLGouMai + 2) = false;
    //selected_elf_id = 1;
    //selected_id_vector = 0;
    //selected_elf_id_inside = 1;
    //selected_id_vector_inside = -1;
    elfsSize = 1;//包含加号
    
    diban_elf1 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _elf1 = ImageView::create("elf_xx_001_hb.png",Widget::TextureResType::PLIST);
    diban_elf2 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _elf2 = ImageView::create("elf_xx_002_hb.png",Widget::TextureResType::PLIST);
    diban_elf3 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _elf3 = ImageView::create("elf_xx_003_hb.png",Widget::TextureResType::PLIST);
    diban_elf4 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _elf4 = ImageView::create("elf_xx_004_hb.png",Widget::TextureResType::PLIST);
    diban_elf5 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _elf5 = ImageView::create("elf_xx_005_hb.png",Widget::TextureResType::PLIST);
    diban_elf6 = Sprite::createWithSpriteFrameName("fengmian_lb_bjb.png");
    _elf6 = ImageView::create("elf_xx_006_hb.png",Widget::TextureResType::PLIST);
    
    
    generalDibans.pushBack(diban_elf1);
    generalDibans.pushBack(diban_elf2);
    generalDibans.pushBack(diban_elf3);
    generalDibans.pushBack(diban_elf4);
    generalDibans.pushBack(diban_elf5);
    generalDibans.pushBack(diban_elf6);
    
    
    
    generalElfs.pushBack(_elf1);
    generalElfs.pushBack(_elf2);
    generalElfs.pushBack(_elf3);
    generalElfs.pushBack(_elf4);
    generalElfs.pushBack(_elf5);
    generalElfs.pushBack(_elf6);
    
    
    isDirectEntered = true;
    CCSize sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();
	init_ui();
    return true;
}
/*
void SceneElfDialog::onExit(){
    Layer::onExit();
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    
    Util::cleanTextureCacheWithMessage("exit title");
    
}
*/



void SceneElfDialog::elfs_layout()
{
    cocos2d::ui::ScrollView* scrollview = (cocos2d::ui::ScrollView*)ui->getChildByName("Elfs");
    
    for(int i=0; i<dibans.size(); i++)
    {
        scrollview->addChild(dibans.at(i),0);
        dibans.at(i)->ignoreAnchorPointForPosition(false);
        dibans.at(i)->setAnchorPoint(Vec2(0.5f,0.5f));
        dibans.at(i)->setPosition(Vec2(120+i*236,150));
    }
    for(int i=0; i<elfs.size(); i++)
    {
        scrollview->addChild(elfs.at(i),0);
        elfs.at(i)->ignoreAnchorPointForPosition(false);
        elfs.at(i)->setAnchorPoint(Vec2(0.5f,0.5f));
        elfs.at(i)->setPosition(Vec2(120+i*236,150));
    }
}


void SceneElfDialog::initElfs(){
    dibans.pushBack(diban_elf1);
    elfs.pushBack(_elf1);
    _elf1->setAnchorPoint(Vec2(0,0));
    _elf1->setTag(kTagBtnElf1);
    _elf1->addTouchEventListener(this, toucheventselector(SceneElfDialog::onClickUi_ImageView));
    
    __String* name1 = __String::createWithFormat("%s","elf_xx_001_hb.png");
    elfsHBFileNames.pushBack(name1);
    
    
    UserData* data = new UserData();
    __Dictionary* elfDic = data->elfDic;
    __Array* keys = elfDic->allKeys();
    
    Util::sortCCStringArray(keys);
    for(int i = 1;i < keys->count() + 1;i++){
        __String* tmp = dynamic_cast<__String*>(keys->getObjectAtIndex(i - 1));
        std::string key = tmp->getCString();
        CCLOG("%s",key.c_str());
        __String* hasBought = dynamic_cast<__String*>(elfDic->objectForKey(key));
        if (hasBought->length() == 3) {
            elfs.pushBack(generalElfs.at(i));
            dibans.pushBack(generalDibans.at(i));
            CCLOG("elf %d", i + 1);
            
            generalElfs.at(i)->setTag(kTagBtnElf1 + i);
            generalElfs.at(i)->addTouchEventListener(this, toucheventselector(SceneElfDialog::onClickUi_ImageView));
            generalElfs.at(i)->setZOrder(zTagDefault);
            
            std::ostringstream oss;
            oss<<i + 1;
            std::string sId1 = oss.str();
            
            std::string tmp = "elf_xx_00" + sId1 + "_hb.png";
            __String* name = __String::create(tmp);
            elfsHBFileNames.pushBack(name);
            
        }
    }
}


bool SceneElfDialog::init_ui()
{
    UserData* data = new UserData();
    //data->showData();
    
    
    
    
	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
	ui = nullptr;
	{
		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/ElfDialog_1/ElfDialog_1.ExportJson"));
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));
        ui->setBackGroundColor(Color3B(0,0,0));
        ui->setBackGroundColorOpacity(0.4f*255);
        
        
        
        
		float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
		ui->setPosition(Vec2(gx, gy));
        
        
        initElfs();
        _jiahao = Sprite::createWithSpriteFrameName("fengmian_lb_bjb_xx.png");
        dibans.pushBack(_jiahao);
        elfsSize = elfs.size();
        elfs_layout();
        
        
        cocos2d::ui::ScrollView* Elfs = (cocos2d::ui::ScrollView*)ui->getChildByName("Elfs");
        int num_elfs = dibans.size();//4
        int add_width = (num_elfs - 3)*708/3;
        //CCLOG("figures.size is %d",num_figures);
        Elfs->setInnerContainerSize(CCSize(708+add_width,292));
        
		
		uiRegButton(ui, "btn_close", kTagBtnRedClose, zTagDefault);
        next = ImageView::create("button_xz_next.png",Widget::TextureResType::PLIST);
        
        if(!isDirectEntered)
        {
            
        }
        
        
        
        
        
	}
	//_uiRoot = ui;
	this->addChild(ui, zTagBtnRefresh - 100);
	return true;
}


void SceneElfDialog::make_a_change()
{
    //修改标题图片关闭图片以及添加下一步图片
    ImageView* bian_kuang = (ImageView*)ui->getChildByName("bian_kuang");
    ImageView* biao_ti = (ImageView*)bian_kuang->getChildByName("biao_ti");
    biao_ti->loadTexture("elf_xz_bt.png",Widget::TextureResType::PLIST);
    
    Button* btn_close = (Button*)ui->getChildByName("btn_close");
    btn_close->loadTextureNormal("button_home_1.png",Widget::TextureResType::PLIST);
    
    //添加下一步按钮
    
    next->setAnchorPoint(Vec2(0, 1));
    this->addChild(next);
    //next->setScale(0.5f);
    next->setPosition(Vec2(1420/2, 768 - 1344/2));
    
    //注册next
    next->setTag(kTagBtnNext_elf);
    next->addTouchEventListener(this, toucheventselector(SceneElfDialog::onClickUi_ImageView));
    next->setZOrder(20);//20应该够大了吧
}


void SceneElfDialog::nextFunc()
{
    //点击下一步时进入简笔画选择图鉴
    //closeCallback();
    
    SceneStickFigureDialog* scene = SceneStickFigureDialog::create();
    scene->sceneTitle = sceneTitle;
    sceneTitle->addChild(scene,1);
    
    
    
    sceneTitle->stickFigureSize = scene->stickFigureSize;
    
    
    if(sceneTitle->stickFigure_id_vector != 0)
    {
        //从新老userData获取newBoughtSet(int*) and newBoughtSetNum(int)
        UserData* newUserData = new UserData();
        Vector<__String*> newLocalJBHStrings = sceneTitle->getCCStringVectorFromUserData(newUserData);
        
        for (int i = 0; i < newLocalJBHStrings.size(); i++) {
            CCLOG("new String %d %s",i,newLocalJBHStrings.at(i)->getCString());
            CCLOG("old String %d %s",i,sceneTitle->localJBHStrings.at(i)->getCString());
        }
        
        
        int* newBoughtSet = sceneTitle->getNewBoughtSet(sceneTitle->localJBHStrings, newLocalJBHStrings);
        int newBoughtSetNum = sceneTitle->getNewBoughtSetNum(sceneTitle->localJBHStrings, newLocalJBHStrings);
        //get newIdVector
        int newIdVector = scene->initUserData(sceneTitle->stickFigure_id, sceneTitle->stickFigure_id_vector, newBoughtSet, newBoughtSetNum);
        //更新localJBHStrings & stickFigure_id_vector
        sceneTitle->localJBHStrings = newLocalJBHStrings;
        sceneTitle->stickFigure_id_vector = newIdVector;
        /*
         下面这段通过added_size调节idVector的代码是有问题的
         不能确定每一组新购买的都是在被选中的简笔画的前面
        int id = sceneTitle->stickFigure_id;
        int id_vector = sceneTitle->stickFigure_id_vector;
        scene->JBHId = sceneTitle->stickfigureIdTemp;
        scene->JBHIdVector = sceneTitle->stickFigureIdVectorTemp + added_size;
         */
        
        scene->initBlueRing_Word();
        
        
    }else{
        int id = sceneTitle->stickFigure_id;
        int id_vector = sceneTitle->stickFigure_id_vector;
        scene->JBHId = sceneTitle->stickfigureIdTemp;
        scene->JBHIdVector = sceneTitle->stickFigureIdVectorTemp;
        scene->initBlueRing_Word();
    }
    
    
    
    
    
    
    
    scene->isDirectEntered = false;
    scene->make_a_change();
    scene->squareBlueRing_id = sceneTitle->squareBlueRingId;
    scene->initSquareBlueRing();
    sceneTitle->elfs = elfs;
    
    closeCallback();
    
    //this->retain();
    //this->removeFromParentAndCleanup(true);
}


void SceneElfDialog::testFunc()
{
    CCLOG("testFunc successful");
}


void SceneElfDialog::initData(int id, int id_vector, int boughtId)
{
    //id 1-3
    //id_vector 0-2
    //bought_id 2,3
    this->elfId = id;
    if (id > boughtId) {
        this->elfIdVector = id_vector + 1;
    }
    else
    {
        //id <= boughtId
        this->elfIdVector = id_vector;
    }
}



void SceneElfDialog::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
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


void  SceneElfDialog::initBlueRing_Word()
{
    //elf_idx 1~3
    //idx_vector 0~2
    //selected_elf_id = elf_idx;
    //selected_id_vector = idx_vector;
    //selected_elf_id_inside = elf_idx;
    //selected_id_vector_inside = idx_vector;
    //将选中的精灵置为彩色
    std::ostringstream oss;
    oss<<elfId;
    std::string sElf_idx = oss.str();
    std::string tmp = "elf_xx_00" + sElf_idx + "_hb.png";
    std::string csName = "elf_xx_00" + sElf_idx + "_cs.png";
    __String* hbFileName = __String::create(tmp);
    int foundElfVectorId = Util::findVectorIdByCCString(elfsHBFileNames,hbFileName);
    elfs.at(foundElfVectorId)->loadTexture(csName,Widget::TextureResType::PLIST);
  
    //添加BlueRing动画
    ArmatureDataManager::getInstance()->addArmatureFileInfo("an/BlueRing/BlueRing.ExportJson");
    Armature* arm = Armature::create("BlueRing");
    elfs.at(foundElfVectorId)->addChild(arm,1,1000);
    this->elfIdVector = foundElfVectorId;
    arm->setAnchorPoint(Vec2(0.5f,0.5f));
    arm->setPosition(Vec2(100,100));
    arm->getAnimation()->play("Animation1");
    //添加文字
    ImageView* di_ban = (ImageView*)ui->getChildByName("di_ban");
    Vec2 position = di_ban->getPosition();
    position.x = position.x- 230;//凑的
    std::string str3 = "_word.png";
    Sprite *_elf_xx_word = Sprite::createWithSpriteFrameName("elf_xx_00" + sElf_idx + str3);
    _elf_xx_word->setAnchorPoint(Vec2(0.5f,0.5f));
    di_ban->addChild(_elf_xx_word,1,elfId + 1314);//the third parameter is the tag
    position.x = position.x - 165;
    _elf_xx_word->setPosition(position);
    //添加精灵动画
    std::string str4 = "an/Elf";
    std::string str5 = "_in_dialog/Elf";
    std::string str6 = "_in_dialog.ExportJson";
    std::string fileNameAni;
    if(elfId <= 3){
        fileNameAni = str4 + sElf_idx + str5 + sElf_idx + str6;
        ArmatureDataManager::getInstance()->addArmatureFileInfo(fileNameAni);
        std::string str7 = "Elf";
        std::string str8 = "_in_dialog";
        arm = Armature::create(str7 + sElf_idx + str8);
    }else if (elfId <= 6){
        fileNameAni = "an/elfAni4-6-in-elfDialog/elf_xx_00" + sElf_idx + "_wait/elf_xx_00" + sElf_idx
        + "_wait.ExportJson";
        ArmatureDataManager::getInstance()->addArmatureFileInfo(fileNameAni);
        arm = Armature::create("elf_xx_00" + sElf_idx
                               + "_wait");
    }
    
    di_ban->addChild(arm,1,elfId + 1314);
    arm->setPosition(Vec2(680,138));
    arm->getAnimation()->play("Animation1");
}



void SceneElfDialog::elfChangedCallback(int id, int idVector, ImageView* btn)
{
    std::ostringstream oss;
    oss<<id;
    std::string sId = oss.str();
    std::ostringstream oss1;
    oss1<<elfId;
    std::string sPreviousId = oss1.str();
    std::string newFileName = "elf_xx_00" + sId + "_cs.png";
    std::string previousFileName = "elf_xx_00" + sPreviousId + "_hb.png";
    std::string wordFileName = "elf_xx_00" + sId + "_word.png";
    std::string animationPath;
    if(id <= 3){
        animationPath = "an/Elf" + sId + "_in_dialog/Elf" + sId
        + "_in_dialog.ExportJson";
    }else if(id <= 6){
        animationPath = "an/elfAni4-6-in-elfDialog/elf_xx_00" + sId + "_wait/elf_xx_00" + sId
        + "_wait.ExportJson";
    }
    
    
    
    elfs.at(elfIdVector)->loadTexture(previousFileName,Widget::TextureResType::PLIST);
    btn->loadTexture(newFileName,Widget::TextureResType::PLIST);
    
    
    ImageView* di_ban = (ImageView*)ui->getChildByName("di_ban");
    //去除精灵动画和文字
    di_ban->removeChildByTag(elfId + 1314);
    di_ban->removeChildByTag(elfId + 1314);
    Vec2 position = di_ban->getPosition();
    position.x = position.x- 230;//凑的
    
    //添加文字
    Sprite *word = Sprite::createWithSpriteFrameName(wordFileName);
    word->setAnchorPoint(Vec2(0.5f,0.5f));
    di_ban->addChild(word,1,id + 1314);//the third parameter is the tag
    position.x = position.x - 165;
    word->setPosition(position);
    
    //添加精灵动画
    ArmatureDataManager::getInstance()->addArmatureFileInfo(animationPath);
    Armature* arm;
    if(id <= 3){
         arm = Armature::create("Elf" + sId + "_in_dialog");
    }else if (id <= 6){
        arm = Armature::create("elf_xx_00" + sId + "_wait");
    }
    
    di_ban->addChild(arm,1,id + 1314);
    arm->setPosition(Vec2(680,138));
    arm->getAnimation()->play("Animation1");
    
    //去除蓝环
    elfs.at(elfIdVector)->removeChildByTag(1000);
    //添加BlueRing动画
    ArmatureDataManager::getInstance()->addArmatureFileInfo("an/BlueRing/BlueRing.ExportJson");
    arm = Armature::create("BlueRing");
    elfs.at(idVector)->addChild(arm,1,1000);
    arm->setAnchorPoint(Vec2(0.5f,0.5f));
    arm->setPosition(Vec2(100,100));
    arm->getAnimation()->play("Animation1");
    
}

void SceneElfDialog::updateUserData(int id, int idVector)
{
    this->elfId = id;
    this->elfIdVector = idVector;
}

void SceneElfDialog::onClickUi_ImageView(Ref* sender, TouchEventType type)
{
    cocos2d::ui::ScrollView* listView = (cocos2d::ui::ScrollView*)ui->getChildByName("Elfs");
    int id = -1;
	ImageView* btn = dynamic_cast<ImageView*>(sender);
	if (btn != nullptr)
	{
		id = btn->getTag();
	}
	if (type != TOUCH_EVENT_ENDED)
		return;
    
    if (id >= kTagBtnElf1 && id <= kTagBtnElf6) {
        int elfId = id - kTagBtnElf1 + 1;
        int elfVectorId = (btn->getPosition().x - 120) / 236;
        
        elfChangedCallback(elfId, elfVectorId, btn);
        updateUserData(elfId, elfVectorId);
        sceneTitle->elfIdTemp = elfId;
        sceneTitle->elfIdVectorTemp = elfVectorId;
    }
    /*
    if (id == kTagBtnElf1)
	{
        
        
        elfChangedCallback(1, 0, btn);
        updateUserData(1, 0);
        sceneTitle->elfIdTemp = 1;
        sceneTitle->elfIdVectorTemp = 0;
        
        
    }
	else if (id == kTagBtnElf2)
	{
        
       
        
        elfChangedCallback(2, 1, btn);
        updateUserData(2, 1);
        sceneTitle->elfIdTemp = 2;
        sceneTitle->elfIdVectorTemp = 1;
        
	}
    
    
    else if (id == kTagBtnElf3)
	{
        
        
        
        int x = btn->getPosition().x;
        int xx = _elf1->getPosition().x;//120
        elfChangedCallback(3, (x - xx)/ 236, btn);
        updateUserData(3, (x - xx)/ 236);
        sceneTitle->elfIdTemp = 3;
        sceneTitle->elfIdVectorTemp = (x - xx)/ 236;
	}
     */
    
    
    else if (id == kTagBtnNext_elf)
    {
        CCLOG("elf next is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneElfDialog::nextFunc, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
    }
}

void SceneElfDialog::onClickUi(Ref* sender, TouchEventType type)
{
    //cocos2d::ui::ScrollView* listView = (ScrollView*)ui->getChildByName("Elfs");
    
    cocos2d::ui::ScrollView* listView = (cocos2d::ui::ScrollView*)ui->getChildByName("Elfs");
    
    
    
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
        //精灵对话框的关闭按钮
        sceneTitle->elfs = elfs;
        
        auto action1 = ScaleTo::create(0.2f, 0.9f);
        auto action2 = ScaleTo::create(0.2f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneElfDialog::closeCallback, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,call
                                          , NULL));
        
	}
}

void SceneElfDialog::closeCallback()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
    this->removeAllChildrenWithCleanup(true);
    //coven0202
    this->release();
    
    Util::unloadPlists(ELF_PLIST_PATHS);
    //coven0202
    //Util::cleanTextureCacheWithMessage("return from elf");
}

void SceneElfDialog::uiRegButton(Widget* parent, const std::string& name, int k, int z)
{
	Button* btn = (Button*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneElfDialog::onClickUi));
		btn->setZOrder(z);
		//parent->addChild(btn, z);
	}
    
    
}


