#include "SceneHuaceDialog.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
#include "SceneHuaceDialog.h"
#include "SceneBigHuaceDialog.h"
#include <UserData.h>
#include "SceneHaceDeleteDialog.h"


// init_ui
// onClickUi
//uiRegButtonInScrollView





#define PROTECTED_CAST (CLASS_TYPE ,CLASS_OBJECT_PTR ,MEMBER_TYPE ,MEMBER_NAME ) (C ##MEMBER_NAME ##Accessor <CLASS_TYPE , MEMBER_TYPE >::GetMember (CLASS_OBJECT_PTR ))



USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

enum kTag
{
	kTagCanvas = 100,
};


std::vector<std::string> SceneHuaceDialog::HUACE_PLIST_PATHS = {"ui/huaceDialog_1/haceXX_plist/haceXX_plist.plist","an/hace_fengmian_animation_3/hace_fengmian_animation_30.plist"};




Scene* SceneHuaceDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneHuaceDialog::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneHuaceDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Util::cleanTextureCacheWithMessage("");
    Util::loadPlists(HUACE_PLIST_PATHS);
    isDelete = false;

    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    
    
    //指定触摸的回调函数
    listener->onTouchBegan = CC_CALLBACK_2(SceneHuaceDialog::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(SceneHuaceDialog::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(SceneHuaceDialog::onTouchEnded,this);
    //设置是否吞噬触摸
    listener->setSwallowTouches(false);
    
    //dispatcher->addEventListenerWithFixedPriority(listener,-129); //－129屏蔽模态窗口下层的所有响应。
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    init_ui();
    innerContainerY = huaces->getInnerContainer()->getPosition().y;
    return true;
}


void SceneHuaceDialog::layout()
{
    //直接以三个vector为标准，不牵涉到plist
    float height = huaces->getContentSize().height;//446
    int num = xxdbs.size();
    int add_height;
    if(num > 3)
    {
        add_height = (num - 3)*(154 + 108);
    }
    else
    {
        add_height = 0;
    }
    height = add_height + height;
    huaces->setInnerContainerSize(CCSize(359, height));
    
 
    for(int i = (xxdbs.size() - 1);i >= 0; i--)
    {
        xxdbs.at(i)->setAnchorPoint(Vec2(0,1));
        deleteBtns.at(i)->setAnchorPoint(Vec2(0,1));
        images.at(i)->setAnchorPoint(Vec2(0,1));
        //images.at(i)->setScale(0.191325, 0.191081);//150/784, 120/628
        //images.at(i)->setScale(0.122150, 0.1301229)120;//150/1228, 120/921
        
        
        int j = xxdbs.size() - i - 1;
        
        xxdbs.at(i)->setPosition(Vec2(745, 631 - j*154 + add_height) - huaces->getPosition());
        deleteBtns.at(i)->setPosition(Vec2(540/2, xxdbs.at(i)->getContentSize().height - 40/2));
        images.at(i)->setPosition(Vec2(53.0/2, xxdbs.at(i)->getContentSize().height - 44/2));
    }
}

void SceneHuaceDialog::loadVectorsFromPlist()
//先clear三个vectors，然后从plist中加载图片文件,addchild to 画册
{
    xxdbs.clear();
    images.clear();
    deleteBtns.clear();
    
    UserData* userdata = new UserData();
    __String *fileNum = userdata->sizeStr;
    int iFileNum = fileNum->intValue();
    auto  filesPath =FileUtils::getInstance()->getWritablePath();
    for(int i=0; i<iFileNum; i++)
    {
        __Dictionary* picitem = dynamic_cast<__Dictionary*>(userdata->albumArr->getObjectAtIndex(i));
        __String* pathStr = dynamic_cast<__String*>(picitem->objectForKey("path"));
        const char* cPicPath = pathStr->getCString();
        int id = *cPicPath - '0';
        
        
        //Sprite* xxdbTemp = createWithSpriteFrameName("hace_xx_xxdb.png"));
        ImageView* xxdbTemp = ImageView::create("hace_xx_xxdb.png", Widget::TextureResType::PLIST);
        
        Sprite* del = Sprite::createWithSpriteFrameName("hace_xx_xxsx.png");
        
        CCSize size = CCDirector::getInstance()->getWinSize();
        CCRect rect;
    
        rect.setRect(108.0f*size.width/1024.0f,0,784,628);
        auto  path =FileUtils::getInstance()->getWritablePath()+pathStr->getCString();
        SpriteFrame * pFrame = CCSpriteFrame::create(path,rect);
        Sprite* temp = CCSprite::createWithSpriteFrame(pFrame);
        xxdbTemp->setName(pathStr->getCString());
        
        
        
        
        temp->setScale(75.0f/784.0f, 60.0f/628.0f);
        CCLOG("the contentsize is %f * %f",temp->getContentSize().width, temp->getContentSize().height);
        
        del->setTag(id);
        temp->setTag(id);
        xxdbTemp->setTag(id);
        images.pushBack(temp);
        xxdbs.pushBack(xxdbTemp);
        deleteBtns.pushBack(del);
        
        
        huaces->addChild(xxdbs.at(i),1);
        xxdbs.at(i)->addChild(deleteBtns.at(i));
        xxdbs.at(i)->addChild(images.at(i));
    }//for
    
    
}


bool SceneHuaceDialog::init_ui()
{
    
    
    time_t time;
    struct tm * timeinfo;
    timeinfo = gmtime (&time);
    /*
    CCLOG("%s", asctime(timeinfo));
    CCLOG("year1->%d",timeinfo->tm_year+1900);
    CCLOG("month1->%d",timeinfo->tm_mon+1);
    CCLOG("date1->%d",timeinfo->tm_mday);
    CCLOG("hour1->%d",timeinfo->tm_hour);
    CCLOG("minutes1->%d",timeinfo->tm_min);
    CCLOG("seconds1->%d",timeinfo->tm_sec);
    */
    
	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    
    
    
    
	ui = nullptr;
	{
		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/huaceDialog_1/huaceDialog_1.ExportJson"));
        huaces = (cocos2d::ui::ScrollView*)ui->getChildByName("huaces");
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));
        ui->setBackGroundColor(Color3B(0,0,0));
        ui->setBackGroundColorOpacity(0.4f*255);
        
        
        
		float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
		ui->setPosition(Vec2(gx, gy));
        
		//my comment:
        //uiRegButton的第二个参数就是传入的name
        
        
		uiRegButton(ui, "btn_close", kTagBtnRedClose, zTagDefault);
        //初始化信息区
        loadVectorsFromPlist();
        layout();
        loadDate_Time();
        
        
        
	}
	
    
    
    
	this->addChild(ui, zTagBtnRefresh - 100);
    
    
    
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("an/hace_fengmian_animation_3/hace_fengmian_animation_3.ExportJson");
    auto arm_Test = Armature::create("hace_fengmian_animation_3");
    ui->addChild(arm_Test,100,10);
    arm_Test->setAnchorPoint(Vec2(0.5f,0.5f));
    arm_Test->setPosition(Vec2(1365/2+182,768/2+30));
    arm_Test->getAnimation()->play("Animation1");
    
    
	return true;
}


void SceneHuaceDialog::refreshXXQ()
{
    
}






void SceneHuaceDialog::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
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

void SceneHuaceDialog::onClickUi(Ref* sender, TouchEventType type)
{
    
    //cocos2d::ui::ScrollView* listView = (ScrollView*)ui->getChildByName("figures");
    
    //cocos2d::ui::ScrollView* listView = (cocos2d::ui::ScrollView*)ui->getChildByName("Figures");
    
    //ImageView *_di_ban = (ImageView*)ui->getChildByName("di_ban");
    
    
    int id = -1;
	Button* btn = dynamic_cast<Button*>(sender);
	if (btn != nullptr)
	{
		id = btn->getTag();
	}
    
	if (type != TOUCH_EVENT_ENDED)
		return;
    
	CCLOG("onClick!!! in SceneHuaceDialog id=%d", id);
    
	
	if (id == kTagBtnRedClose)
	{
        //画册对话框的关闭按钮
        auto action1 = ScaleTo::create(0.2f, 0.9f);
        auto action2 = ScaleTo::create(0.2f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneHuaceDialog::closeCallback, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,call
                                          , NULL));
	}
    
    
    
}



void SceneHuaceDialog::closeCallback()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
    this->removeAllChildrenWithCleanup(true);
    //coven0202
    this->release();
    SceneTitle::clearCache();
}
/*
void SceneHuaceDialog::onExit(){
    Layer::onExit();
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    
    Util::cleanTextureCacheWithMessage("exit title");
    
}
*/

void SceneHuaceDialog::uiRegButton(Widget* parent, const std::string& name, int k, int z)
{
	Button* btn = (Button*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneHuaceDialog::onClickUi));
		btn->setZOrder(z);
	}
}




CCRect SceneHuaceDialog::getBoundingBox_worldspace(Sprite* sprite)
{
    CCRect rect = sprite->getBoundingBox();
    Vec2 point_ws = sprite->convertToWorldSpace(rect.origin);
    CCRect rect_WorldSpace = CCRect(point_ws.x, point_ws.y, rect.size.width, rect.size.height);
    return rect_WorldSpace;
}



bool SceneHuaceDialog::onTouchBegan(Touch * touch,Event * pEvent)
{
    //m_bTouchedMenu = this->ccTouchBegan(touch, pEvent);
    this->setLocalZOrder(11); //设置层级反转，原来HuaceLayer中的grossini层级（4）在HuaceSelectorLayer（3）之上
    //grossini是一个播放封面动画的一个精灵
    
    
    
    Vec2 touchPoint=convertTouchToNodeSpace(touch);
    //touchPoint = touchPoint - huaces->getPosition();
    
    
    CCLOG("THE TOUCHPOINT IS (%f, %f)",touchPoint.x, touchPoint.y);
    
    for(int i=0; i<xxdbs.size(); i++)
    {
 
        CCRect _rect = xxdbs.at(i)->getBoundingBox();
      
 
        if(this->getBoundingBox_worldspace(images.at(i)).containsPoint(touchPoint))
        {
            int scene_id = eSceneIdSceneBigHuaceDialog;
            SceneBigHuaceDialog* big = (SceneBigHuaceDialog*)SceneController::getInstance()->getSceneById(scene_id);
            
            std::string fileName = xxdbs.at(i)->getName();
            big->setFileName(fileName);
            
            big->addSprite(Sprite::createWithSpriteFrame(images.at(i)->getSpriteFrame()));
            
            big->getPictureFromScreenShot();
            this->addChild(big);
            break;
        }
        CCRect rectDel = getBoundingBox_worldspace(deleteBtns.at(i));
        float delW = (rectDel.getMaxX() - rectDel.getMinX());
        float delH = (rectDel.getMaxY() - rectDel.getMinY());
        Vec2 originDel = rectDel.origin;
        float newX = originDel.x;
        newX = newX - 87 - 172;
        CCLOG("the newX is %f the width is %f", newX, delW);
        CCLOG("the origin.y is %f, the height is %f", originDel.y, delH);
        
        if(CCRect(newX, originDel.y-14, delW, delH).containsPoint(touchPoint))
        {
            SceneHaceDeleteDialog* layer = SceneHaceDeleteDialog::create();
            layer->huace = this;
            layer->idx = i;
            this->addChild(layer);
            Layout* container = huaces->getInnerContainer();
            Vec2 posCon = container->getPosition();
            
            
    
            Vec2 xxdbPosWS = xxdbs.at(i)->getPosition() + huaces->getPosition();
        
            int num = xxdbs.size();
            int add_height;
            if(num > 3)
            {
                add_height = (num - 3)*(154 + 108);
            }
            else
            {
                add_height = 0;
            }
            float x = xxdbPosWS.x + 74;
            float y = xxdbPosWS.y - 9 - add_height + posCon.y - innerContainerY;
            
            
            layer->setBtnPosition(Vec2(x,y));
            break;
        }
    }// for
    
    return true;
}


void SceneHuaceDialog::deleteItemFromHace(int idx)
{
    UserData* userdata = new UserData();
    userdata->delPicItem(idx);
    huaces->cocos2d::Node::removeAllChildren();
    loadVectorsFromPlist();
    layout();
    loadDate_Time();
    innerContainerY = innerContainerY + 262;
}



void SceneHuaceDialog::onTouchMoved(Touch * touch,Event * pEvent)
{
    //CCLOG("drag moved");
}

void SceneHuaceDialog::onTouchEnded(Touch * touch,Event * pEvent)
{
    //CCLOG("drag ended");
}


void SceneHuaceDialog::loadDate_Time()
{
    UserData* userdata = new UserData();
    int numAlbum = userdata->sizeStr->intValue();
    int** date = new int*[numAlbum];
    for (int i = 0; i < numAlbum; i++) {
        *(date + i) = new int[8];
    }
    for (int i = 0; i< numAlbum; i++) {
        __Dictionary* picitem = dynamic_cast<__Dictionary*>(userdata->albumArr->getObjectAtIndex(i));
        __String* yrStr = dynamic_cast<__String*>(picitem->objectForKey("yr"));
        __String* moStr = dynamic_cast<__String*>(picitem->objectForKey("mo"));
        __String* daStr = dynamic_cast<__String*>(picitem->objectForKey("da"));
        int yr = yrStr->intValue();
        int mo = moStr->intValue();
        int da = daStr->intValue();
        
        int yrGe = yr % 10;
        yr = yr / 10;
        int yrShi = yr % 10;
        int yrBai = 0;
        int yrQian = 2;
        *(*(date + i) + 0) = yrQian;
        *(*(date + i) + 1) = yrBai;
        *(*(date + i) + 2) = yrShi;
        *(*(date + i) + 3) = yrGe;
        
        mo++;// mo = 0-11
        int moGe = mo % 10;
        int moShi = mo / 10;
        *(*(date + i) + 4) = moShi;
        *(*(date + i) + 5) = moGe;
        
        int daGe = da % 10;
        int daShi = da / 10;
        
        *(*(date + i) + 6) = daShi;
        *(*(date + i) + 7) = daGe;
        
        Vector<Sprite*> myDate;
        
        std::ostringstream oss;
        oss<<yrQian;
        std::string sYrQian = oss.str();
        std::string rqTemp1 = "hace_xx_rq_";
        std::string rqTemp2 = ".png";
        std::string sQian = rqTemp1 + sYrQian + rqTemp2;
        Sprite* yrQianSprite = Sprite::createWithSpriteFrameName(sQian);
        
        
        oss.str("");
        oss<<yrBai;
        std::string sYrBai = oss.str();
        std::string sBai = rqTemp1 + sYrBai + rqTemp2;
        Sprite* yrBaiSprite = Sprite::createWithSpriteFrameName(sBai);
        
        
        oss.str("");
        oss.clear();
        oss<<yrShi;
        std::string sYrShi = oss.str();
        std::string sShi = rqTemp1 + sYrShi + rqTemp2;
        Sprite* yrShiSprite = Sprite::createWithSpriteFrameName(sShi);
        
        
        oss.str("");
        oss.str("");
        oss.clear();
        oss<<yrGe;
        std::string sYrGe = oss.str();
        std::string sGe = rqTemp1 + sYrGe + rqTemp2;
        Sprite* yrGeSprite = Sprite::createWithSpriteFrameName(sGe);
        
        
        oss.str("");
        oss.clear();
        oss<<moShi;
        std::string sMoShi = oss.str();
        std::string sMo = rqTemp1 + sMoShi + rqTemp2;
        Sprite* moShiSprite = Sprite::createWithSpriteFrameName(sMo);
        
        
        oss.str("");
        oss.clear();
        oss<<moGe;
        std::string sMoGe = oss.str();
        std::string sMo2 = rqTemp1 + sMoGe + rqTemp2;
        Sprite* moGeSprite = Sprite::createWithSpriteFrameName(sMo2);
        
        oss.str("");
        oss.clear();
        oss<<daShi;
        std::string sDaShi = oss.str();
        std::string sDa = rqTemp1 + sDaShi + rqTemp2;
        Sprite* daShiSprite = Sprite::createWithSpriteFrameName(sDa);
        
        oss.str("");
        oss.clear();
        oss<<daGe;
        std::string sDaGe = oss.str();
        std::string sDa2 = rqTemp1 + sDaGe + rqTemp2;
        Sprite* daGeSprite = Sprite::createWithSpriteFrameName(sDa2);
        
        myDate.pushBack(yrQianSprite);
        myDate.pushBack(yrBaiSprite);
        myDate.pushBack(yrShiSprite);
        myDate.pushBack(yrGeSprite);
        myDate.pushBack(moShiSprite);
        myDate.pushBack(moGeSprite);
        myDate.pushBack(daShiSprite);
        myDate.pushBack(daGeSprite);
        
        myDateLayout(myDate,i);
        
        
        __String* hrStr = dynamic_cast<__String*>(picitem->objectForKey("hr"));
        __String* miStr = dynamic_cast<__String*>(picitem->objectForKey("mi"));
        
        int hrInt = hrStr->intValue();
        
        
        int miInt = miStr->intValue();
        int miShi = miInt/10;
        int miGe = miInt%10;
        
        Vector<Sprite*> myTime;
        if(hrInt > 12)
        {
            hrInt = hrInt - 12;
            int hrShi = hrInt/10;
            int hrGe = hrInt%10;
            
            oss.str("");
            oss.clear();
            oss<<hrShi;
            std::string sHrshi = oss.str();
            std::string sHr1 = rqTemp1 + sHrshi + rqTemp2;
            Sprite* hrShiSprite = Sprite::createWithSpriteFrameName(sHr1);
            
            oss.str("");
            oss.clear();
            oss<<hrGe;
            std::string sHrGe = oss.str();
            std::string sHr2 = rqTemp1 + sHrGe + rqTemp2;
            Sprite* hrGeSprite =Sprite::createWithSpriteFrameName(sHr2);
            
            
            Sprite* pm = Sprite::createWithSpriteFrameName("hace_xx_rq_pm.png");
            
            myTime.pushBack(pm);
            myTime.pushBack(hrShiSprite);
            myTime.pushBack(hrGeSprite);
         
            
            
        }else{
            int hrShi = hrInt/10;
            int hrGe = hrInt%10;
            
            oss.str("");
            oss.clear();
            oss<<hrShi;
            std::string sHrshi = oss.str();
            std::string sHr1 = rqTemp1 + sHrshi + rqTemp2;
            Sprite* hrShiSprite = Sprite::createWithSpriteFrameName(sHr1);
            
            oss.str("");
            oss.clear();
            oss<<hrGe;
            std::string sHrGe = oss.str();
            std::string sHr2 = rqTemp1 + sHrGe + rqTemp2;
            Sprite* hrGeSprite = Sprite::createWithSpriteFrameName(sHr2);
            
            Sprite* am = Sprite::createWithSpriteFrameName("hace_xx_rq_am.png");
            
            myTime.pushBack(am);
            myTime.pushBack(hrShiSprite);
            myTime.pushBack(hrGeSprite);
        }
        
        oss.str("");
        oss.clear();
        oss<<miShi;
        std::string sMishi = oss.str();
        std::string sMi1 = rqTemp1 + sMishi + rqTemp2;
        Sprite* miShiSprite = Sprite::createWithSpriteFrameName(sMi1);
        
        oss.str("");
        oss.clear();
        oss<<miGe;
        std::string sMiGe = oss.str();
        std::string sMi2 = rqTemp1 + sMiGe + rqTemp2;
        Sprite* miGeSprite = Sprite::createWithSpriteFrameName(sMi2);
        
        
        myTime.pushBack(miShiSprite);
        myTime.pushBack(miGeSprite);
        
        
        myTimeLayout(myTime, i);
        
    }
   
    //coven
    
    for (int i = 0; i < numAlbum; ++i)
    {
        delete date[i];
        
    }
    delete[] date;
    delete userdata;
    
}

void SceneHuaceDialog::myTimeLayout(Vector<Sprite*> myTime, int idx_xxdb)
{
    ImageView* xxdb = xxdbs.at(idx_xxdb);
    int height = xxdb->getContentSize().height;
 
    xxdb->addChild(myTime.at(0));
    myTime.at(0)->setAnchorPoint(Vec2(0,1));
    myTime.at(0)->setPosition(Vec2(278/2, height - 120/2));
    
    xxdb->addChild(myTime.at(1));
    myTime.at(1)->setAnchorPoint(Vec2(0,1));
    myTime.at(1)->setPosition(Vec2(344/2, height - 116/2));
    
    
    xxdb->addChild(myTime.at(2));
    myTime.at(2)->setAnchorPoint(Vec2(0,1));
    myTime.at(2)->setPosition(Vec2(362/2, height - 120/2));
 
    
    //冒号
    Sprite* maohao = Sprite::createWithSpriteFrameName("hace_xx_rq_mh.png");
    xxdb->addChild(maohao);
    maohao->setAnchorPoint(Vec2(0,1));
    maohao->setPosition(Vec2(390/2, height - 116/2));
    
    xxdb->addChild(myTime.at(3));
    myTime.at(3)->setAnchorPoint(Vec2(0,1));
    myTime.at(3)->setPosition(Vec2(418/2, height - 116/2));
    
    
    xxdb->addChild(myTime.at(4));
    myTime.at(4)->setAnchorPoint(Vec2(0,1));
    myTime.at(4)->setPosition(Vec2(446/2, height - 120/2));
    
    
}


void SceneHuaceDialog::myDateLayout(Vector<Sprite*> myDate, int idx_xxdb)
{
    ImageView* xxdb = xxdbs.at(idx_xxdb);
    int height = xxdb->getContentSize().height;
    
    xxdb->addChild(myDate.at(0));
    myDate.at(0)->setAnchorPoint(Vec2(0,1));
    myDate.at(0)->setPosition(Vec2(243/2, height - 45/2));
    
    xxdb->addChild(myDate.at(1));
    myDate.at(1)->setAnchorPoint(Vec2(0,1));
    myDate.at(1)->setPosition(Vec2(271/2, height - 45/2));
    
    xxdb->addChild(myDate.at(2));
    myDate.at(2)->setAnchorPoint(Vec2(0,1));
    myDate.at(2)->setPosition(Vec2(299/2, height - 45/2));
    
    xxdb->addChild(myDate.at(3));
    myDate.at(3)->setAnchorPoint(Vec2(0,1));
    myDate.at(3)->setPosition(Vec2(327/2, height - 45/2));
    
    Sprite* xieGang = Sprite::createWithSpriteFrameName("hace_xx_rq_xg.png");
    xxdb->addChild(xieGang);
    xieGang->setAnchorPoint(Vec2(0,1));
    xieGang->setPosition(Vec2(355/2, height - 45/2));
    
    xxdb->addChild(myDate.at(4));
    myDate.at(4)->setAnchorPoint(Vec2(0,1));
    myDate.at(4)->setPosition(Vec2(383/2, height - 45/2));
    
    xxdb->addChild(myDate.at(5));
    myDate.at(5)->setAnchorPoint(Vec2(0,1));
    myDate.at(5)->setPosition(Vec2(411/2, height - 45/2));
    
    Sprite* xieGang2 = Sprite::createWithSpriteFrameName("hace_xx_rq_xg.png");
    xxdb->addChild(xieGang2);
    xieGang2->setAnchorPoint(Vec2(0,1));
    xieGang2->setPosition(Vec2(439/2, height - 45/2));
    
    xxdb->addChild(myDate.at(6));
    myDate.at(6)->setAnchorPoint(Vec2(0,1));
    myDate.at(6)->setPosition(Vec2(467/2, height - 45/2));
    
    xxdb->addChild(myDate.at(7));
    myDate.at(7)->setAnchorPoint(Vec2(0,1));
    myDate.at(7)->setPosition(Vec2(495/2, height - 45/2));
}



