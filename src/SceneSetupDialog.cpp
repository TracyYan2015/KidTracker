#include "SceneSetupDialog.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"
#include "SceneElfDialog.h"
#include "UserData.h"//为测试UserData的添加用户信息而先include进来
#include "IOSiAP.h"
#include "IOSiAP_Bridge.h"
#include "SceneStickFigureDialog.h"



#define MUSIC_FILE  "bgm/201-unknown_-_out_of_valley-muji.mp3"
#define EFFECT_FILE ""



USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

const int JBH_SET_NUMBER = 5;
const std::string SETUP_DIALOG_UI_PATH = "ui/NewSetupDialog_1_11_20";

const int WEI_SHANG_XIAN_SETS[3] = {2, 3, 4};
const int WEI_SHANG_XIAN_NUMBER = 3;


enum kTag
{
	kTagCanvas = 100,
};

IOSiAP_Bridge* iap;

Scene* SceneSetupDialog::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneSetupDialog::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



//because there is no posotion change after the user bought jbh,
//this method is then useless.
/*
void SceneSetupDialog::JBHBoughtCallback(int boughtId)
{
    //boughtId = 1 to JBH_SET_NUMBER
    for (int i = 0; i < JBH_SET_NUMBER; i++) {
        if((i + 1) < boughtId)
        {
            int newJBH_Y = jianBiHuas.at(i)->getPosition().y - 266;
            jianBiHuas.at(i)->setPosition(Vec2(jianBiHuas.at(i)->getPosition().x, newJBH_Y));
            newJBH_Y = JBHGouMais.at(i)->getPosition().y - 266;
            JBHGouMais.at(i)->setPosition(Vec2(JBHGouMais.at(i)->getPosition().x, newJBH_Y));
        }
    }
}
*/



void SceneSetupDialog::refreshJBH(int decreaseHeight, int id, int numJBHGoumai)
{
    //id是选择的简笔画的id  = 1 - jianBiHuas.size()
    //更新简笔画的位置
    //when you get in the view for the first time, the id is 9
    for (int i = 0; i < jianBiHuas.size() ; i++) {
        CCLOG("第 %d 个元素上移的距离是 %d", i, *(upMoveDistances +i));
    }
    
    for (int i = 0; i < jianBiHuas.size(); i++) {
        if(*(isJianbihuaGoumai + i))
        {
            CCLOG("the deleted JBH is %d",i + 1);
            //将购买按钮换成已购买按钮，并且设为unable
            JBHGouMais.at(i)->loadTexture("ui/NewSetupDialog_1_11_20/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(i)->setEnabled(false);
            
        }
        /*
        else
        {
            if((i + 1) > id)
            {
                //no position changed
            }
            else if((i + 1) < id)
            {
                //position changed
                int posY = jianBiHuas.at(i)->getPosition().y;
                int posX = jianBiHuas.at(i)->getPosition().x;
                int posY_GM = JBHGouMais.at(i)->getPosition().y;
                int posX_GM = JBHGouMais.at(i)->getPosition().x;
                posY = posY + (*(upMoveDistances + i)) * 266 - decreaseHeight;
                posY_GM = posY_GM + (*(upMoveDistances + i)) * 266 - decreaseHeight;
                CCLOG("posY %d posY_GM %d",posY, posY_GM);
                CCLOG("decreaseHeight is %d",decreaseHeight);
                CCLOG("upMoveDistances is %d",*(upMoveDistances + i));
                jianBiHuas.at(i)->setPosition(Vec2(posX, posY));
                JBHGouMais.at(i)->setPosition(Vec2(posX_GM,posY_GM));
            }
        }
         */
        
        
        
    }
    
    
}




// on "init" you need to initialize your instance
bool SceneSetupDialog::init()
{
    //////////////////////////////
    //extern SpriteFrameCache* cache_jbh;
    Util::cleanTextureCacheWithMessage("");

    
    //Layout* layout = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/MainScene.json"));
    
    
    //newJLScrollview = dynamic_cast<ui::ScrollView*>(getChildFromMyUI(layout, "ScrollView_1"));
    
    
    
    mJieShaoScrollView = nullptr;
    jieshaoUI = nullptr;
    cache_jbh = SpriteFrameCache::getInstance();
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    newBoughtJBHSet = new int[JBH_SET_NUMBER];
    for(int i = 0;i < JBH_SET_NUMBER;i++)
    {
        *(newBoughtJBHSet + i) = 0;
    }
    cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(SETUP_DIALOG_UI_PATH + "/setup_plist.plist", SETUP_DIALOG_UI_PATH + "/setup_plist.png");//四张设置界面按钮高亮图
    //音量调节图
    cache->addSpriteFramesWithFile(SETUP_DIALOG_UI_PATH + "/yinliang_plist.plist", SETUP_DIALOG_UI_PATH + "/yinliang_plist.png");
    upMoveDistances = new int[JBH_SET_NUMBER];
    isJianbihuaGoumai = new bool[JBH_SET_NUMBER];
    for (int i =0; i < JBH_SET_NUMBER; i++) {
        *(isJianbihuaGoumai + i) = false;
        *(upMoveDistances + i ) = 0;
    }
    num_jbh_goumai = 0;//记录当前用户已经购买的简笔画的数量,一进入这个类的时候被初始化为0之后唯一的一次更新是在countUpMoveDistances()里面
    added = nullptr;
    
    
    
    //Size sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();
    CCSize vSize = Director::getInstance()->getVisibleSize();
    Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile((SETUP_DIALOG_UI_PATH + "/SetupDialog_1.ExportJson").c_str()));
    
    
    xinxi = ImageView::create("xinxi.png");
    ui->addChild(xinxi);
    xinxi->setVisible(false);
    jieshaoUI = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/jieshao_UI/NewOne_1/NewOne_1.json"));
    
    jieshaoUI->setVisible(false);
    
    
    float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
    float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
    ui->setPosition(Vec2(gx, gy));
    this->addChild(ui, zTagBtnRefresh - 100);
    this->addChild(jieshaoUI, zTagBtnRefresh - 100);
    
    
    ui->setTouchEnabled(true);
    ui->setEnabled(true);
    ui->setAnchorPoint(Vec2(0.0f, 0.0f));
    ui->setBackGroundColor(Color3B(0,0,0));
    ui->setBackGroundColorOpacity(0.4f*255);
    ui_shangdian = (ImageView*)ui->getChildByName("ui_shangdian");
    ui_JBSheZhi = (ImageView*)ui->getChildByName("ui_JBSheZhi");
    shangdian = (ImageView*)ui->getChildByName("shangdian");
    home = (ImageView*)ui->getChildByName("home");
    gsxinxi = (ImageView*)ui->getChildByName("gsxinxi");
    xuanchuan = (ImageView*)ui->getChildByName("xuanchuan");
    jbshezhi = (ImageView*)ui->getChildByName("jbshezhi");
    bgmusic=(ImageView*)ui_JBSheZhi->getChildByName("bgmVolumn");
    volume=(ImageView*)ui_JBSheZhi->getChildByName("voiceVolumn");
    pTextField1=(TextField*)ui->getChildByName("tfName");
    pTextField2=(TextField*)ui->getChildByName("tfAge");
    
    
    if(scrollView_jianbihua == nullptr){
        scrollView_jianbihua = (cocos2d::ui::ScrollView*)getChildFromMyUI((ImageView*)ui->getChildByName("ui_shangdian"), "ScrollView_jianbihua");
    }
    jianbihua_1 = (ImageView*)scrollView_jianbihua->getChildByName("jianbihua1");
    jianbihua_2 = (ImageView*)scrollView_jianbihua->getChildByName("jianbihua2");
    jianbihua_3 = (ImageView*)scrollView_jianbihua->getChildByName("jianbihua3");
    jianbihua_4 = (ImageView*)scrollView_jianbihua->getChildByName("jianbihua4");
    jianbihua_5 = (ImageView*)scrollView_jianbihua->getChildByName("jianbihua5");
    jianBiHuas.pushBack(jianbihua_1);
    jianBiHuas.pushBack(jianbihua_2);
    jianBiHuas.pushBack(jianbihua_3);
    jianBiHuas.pushBack(jianbihua_4);
    jianBiHuas.pushBack(jianbihua_5);
    jbh_goumai_1 = (ImageView*)scrollView_jianbihua->getChildByName("JBHGoumai1");
    jbh_goumai_2 = (ImageView*)scrollView_jianbihua->getChildByName("JBHGoumai2");
    jbh_goumai_3 = (ImageView*)scrollView_jianbihua->getChildByName("JBHGoumai3");
    jbh_goumai_4 = (ImageView*)scrollView_jianbihua->getChildByName("JBHGoumai4");
    jbh_goumai_5 = (ImageView*)scrollView_jianbihua->getChildByName("JBHGoumai5");
    JBHGouMais.pushBack(jbh_goumai_1);
    JBHGouMais.pushBack(jbh_goumai_2);
    JBHGouMais.pushBack(jbh_goumai_3);
    JBHGouMais.pushBack(jbh_goumai_4);
    JBHGouMais.pushBack(jbh_goumai_5);
    
    //修改3 4 5简笔画为未上线
    /*
    for (int i = 0; i < WEI_SHANG_XIAN_NUMBER; i++) {
        JBHGouMais.at(WEI_SHANG_XIAN_SETS[i])->loadTexture("ui/NewSetupDialog_1_11_20/boughtStateChange/jbh/button_jbh_goumai_3.png",Widget::TextureResType::LOCAL);
    }
    */
    if(scrollView_jingling == NULL){
        scrollView_jingling = (cocos2d::ui::ScrollView*)getChildFromMyUI((ImageView*)ui->getChildByName("ui_shangdian"), "ScrollView_jingling");
    }
    /*
    newJLScrollview->setAnchorPoint(scrollView_jingling->getAnchorPoint());
    scrollView_jingling->getParent()->addChild(newJLScrollview);
    newJLScrollview->setLocalZOrder(scrollView_jingling->getLocalZOrder() + 1);
    newJLScrollview->setPosition(scrollView_jingling->getPosition());
    */
    
    
    jingling1 = (ImageView*)scrollView_jingling->getChildByName("jingling1");
    jingling2 = (ImageView*)scrollView_jingling->getChildByName("jingling2");
    jingling3 = ImageView::create("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/jl_gm_xx_3.png",Widget::TextureResType::LOCAL);
    jingling4 = ImageView::create("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/jl_gm_xx_4.png",Widget::TextureResType::LOCAL);
    jingling5 = ImageView::create("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/jl_gm_xx_6.png",Widget::TextureResType::LOCAL);
    
    JLGoumai1 = (ImageView*)scrollView_jingling->getChildByName("goumai_1");
    JLGoumai2 = (ImageView*)scrollView_jingling->getChildByName("goumai_2");
    JLGoumai3 = ImageView::create("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/button_jl_goumai_1.png",Widget::TextureResType::LOCAL);
    JLGoumai4 = ImageView::create("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/button_jl_goumai_1.png",Widget::TextureResType::LOCAL);
    JLGoumai5 = ImageView::create("ui/NewSetupDialog_1_11_20/ElfScrollView2-6/button_jl_goumai_1.png",Widget::TextureResType::LOCAL);
    //resize the scrollView_jingling's innerContainerSize and
    //add elf 3,4,5
    float newHeight = scrollView_jingling->getInnerContainerSize().height * 2.5f;
    float width = scrollView_jingling->getInnerContainerSize().width;
    scrollView_jingling->setInnerContainerSize(CCSize(width,newHeight));
    
    float addedHeight = (float)newHeight * 3.0f /5.0f;
    
    
    //reposition elf1 and elf2
    Vec2 newPos1 = Vec2(jingling1->getPosition().x, jingling1->getPosition().y + addedHeight);
    Vec2 newPos2 = Vec2(jingling2->getPosition().x, jingling2->getPosition().y + addedHeight);
    jingling1->setPosition(newPos1);
    jingling2->setPosition(newPos2);
    
    Vec2 newButtonPos1 = Vec2(JLGoumai1->getPosition().x, JLGoumai1->getPosition().y + addedHeight);
    Vec2 newButtonPos2 = Vec2(JLGoumai2->getPosition().x, JLGoumai2->getPosition().y + addedHeight);
    JLGoumai1->setPosition(newButtonPos1);
    JLGoumai2->setPosition(newButtonPos2);
    
    //add elf3,4,5
    jingling3->setAnchorPoint(jingling1->getAnchorPoint());
    scrollView_jingling->cocos2d::Node::addChild(jingling3, jingling1->getLocalZOrder());
    Vec2 newPos3 = Vec2(jingling2->getPosition().x, jingling2->getPosition().y - 267);
    jingling3->setPosition(newPos3);
    
    jingling4->setAnchorPoint(jingling1->getAnchorPoint());
    scrollView_jingling->cocos2d::Node::addChild(jingling4, jingling1->getLocalZOrder());
    Vec2 newPos4 = Vec2(jingling3->getPosition().x, jingling3->getPosition().y - 267);
    jingling4->setPosition(newPos4);
    
    jingling5->setAnchorPoint(jingling1->getAnchorPoint());
    scrollView_jingling->cocos2d::Node::addChild(jingling5, jingling1->getLocalZOrder());
    Vec2 newPos5 = Vec2(jingling4->getPosition().x, jingling4->getPosition().y - 267);
    jingling5->setPosition(newPos5);
    
    //add button 3, 4, 5
    JLGoumai3->setAnchorPoint(JLGoumai1->getAnchorPoint());
    scrollView_jingling->cocos2d::Node::addChild(JLGoumai3, JLGoumai1->getLocalZOrder());
    Vec2 newButtonPos3 = Vec2(JLGoumai2->getPosition().x, JLGoumai2->getPosition().y - 267);
    JLGoumai3->setPosition(newButtonPos3);
    
    JLGoumai4->setAnchorPoint(JLGoumai1->getAnchorPoint());
    scrollView_jingling->cocos2d::Node::addChild(JLGoumai4, JLGoumai1->getLocalZOrder());
    Vec2 newButtonPos4 = Vec2(JLGoumai3->getPosition().x, JLGoumai3->getPosition().y - 267);
    JLGoumai4->setPosition(newButtonPos4);
    
    JLGoumai5->setAnchorPoint(JLGoumai1->getAnchorPoint());
    scrollView_jingling->cocos2d::Node::addChild(JLGoumai5, JLGoumai1->getLocalZOrder());
    Vec2 newButtonPos5 = Vec2(JLGoumai4->getPosition().x, JLGoumai4->getPosition().y - 267);
    JLGoumai5->setPosition(newButtonPos5);
    
    
    if(scrollView_libao == NULL){
         scrollView_libao = (cocos2d::ui::ScrollView*)getChildFromMyUI((ImageView*)ui->getChildByName("ui_shangdian"), "ScrollView_libao");
    }
    scrollView_fuwu = (cocos2d::ui::ScrollView*)getChildFromMyUI((ImageView*)ui->getChildByName("ui_shangdian"), "ScrollView_fuwu");
    
    
    libao = (ImageView*)scrollView_libao->getChildByName("libao1");
    lb_goumai_btn = (ImageView*)scrollView_libao->getChildByName("goumai");
    
    
    
    if(ui_JBSheZhi == NULL)
    {
        ui_JBSheZhi = (ImageView*)ui->getChildByName("ui_JBSheZhi");
    }
    huiFuGouMai = (ImageView*)ui_JBSheZhi->getChildByName("huiFuGouMai");
    huiFuGouMai->setEnabled(true);
    
    libao_btn = (ImageView*)ui_shangdian->getChildByName("libao");
    
    //一开始让礼包按钮高亮
    added_Shangdian = Sprite::createWithSpriteFrameName("shangdian_libao_biaoqian_1.png");
    ui_shangdian->addChild(added_Shangdian,10,103);
    added_Shangdian->setAnchorPoint(Vec2(0, 1));
    added_Shangdian->setPosition(libao_btn->getPosition());
    SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FILE);
    
    
	init_ui();
    
    
    
    
    
    
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    listener = EventListenerTouchOneByOne::create();
    
    
    //指定触摸的回调函数
    listener->onTouchBegan = CC_CALLBACK_2(SceneSetupDialog::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(SceneSetupDialog::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(SceneSetupDialog::onTouchEnded,this);
    //设置是否吞噬触摸
    listener->setSwallowTouches(false);
    
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    //iap = new IOSiAP_Bridge();
    
    
    return true;
}




Widget* SceneSetupDialog::getChildFromMyUI(Widget* parent, const std::string& name)
{
    Widget* child = nullptr;
    if(parent != nullptr)
    {
        child = parent->getChildByName(name);
    }
    return child;
}

bool SceneSetupDialog::init_ui()
{
    cache = SpriteFrameCache::getInstance();
	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    
	
	
        //((ImageView*)ui_JBSheZhi->getChildByName("huiFuGouMai"))->setEnabled(false);
        //注册设置下的按钮
		uiRegButton_imageview(ui, "home", kTagBtnHome, zTagDefault);
        uiRegButton_imageview(ui, "gsxinxi", kTagBtnGSXinXi, zTagDefault);
        uiRegButton_imageview(ui, "jbshezhi", kTagBtnJBSheZhi, zTagDefault);
        uiRegButton_imageview(ui, "shangdian", kTagBtnShangDian, zTagDefault);
        uiRegButton_imageview(ui, "xuanchuan", kTagBtnXuanChuan, zTagDefault);
        //设置界面初始化为商店
        added = Sprite::createWithSpriteFrameName("button_shangdian_1.png");
        added->setAnchorPoint(Vec2(0,1));
        ui->addChild(added, 10, 2000);
        added->setPosition(shangdian->getPosition());
        ui_JBSheZhi->setVisible(false);
        ui_shangdian->setVisible(true);
        //注册商店里的按钮
        uiRegButton_imageview((ImageView*)ui->getChildByName("ui_shangdian"), "libao", kTagBtnLiBao, zTagDefault);
        uiRegButton_imageview((ImageView*)ui->getChildByName("ui_shangdian"), "jianbihua", kTagBtnJianBiHua, zTagDefault);
        uiRegButton_imageview((ImageView*)ui->getChildByName("ui_shangdian"), "jingling", kTagBtnJingling, zTagDefault);
        uiRegButton_imageview((ImageView*)ui->getChildByName("ui_shangdian"), "fuwu", kTagBtnFuWu, zTagDefault);
        //注册简笔画模块下的8个购买按钮和一个总价按钮
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai1", kTagBtnJBHGoumai_1, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai2", kTagBtnJBHGoumai_2, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai3", kTagBtnJBHGoumai_3, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai4", kTagBtnJBHGoumai_4, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai5", kTagBtnJBHGoumai_5, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai6", kTagBtnJBHGoumai_6, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai7", kTagBtnJBHGoumai_7, zTagDefault);
        uiRegButton_imageview(scrollView_jianbihua, "JBHGoumai8", kTagBtnJBHGoumai_8, zTagDefault);
        //注册礼包下的购买按钮
        uiRegButton_imageview(scrollView_libao, "goumai", kTagBtnLiBaoGoumai, zTagDefault);
        //注册精灵下的购买按钮
        uiRegButton_imageview(scrollView_jingling, "goumai_1", kTagBtnJLGoumai_1, zTagDefault);
        uiRegButton_imageview(scrollView_jingling, "goumai_2", kTagBtnJLGoumai_2, zTagDefault);
    
    
        JLGoumai3->setTag(kTagBtnJLGoumai_3);
        JLGoumai3->addTouchEventListener(this, toucheventselector(SceneSetupDialog::onClickUi_ImageView));
        JLGoumai4->setTag(kTagBtnJLGoumai_4);
        JLGoumai4->addTouchEventListener(this, toucheventselector(SceneSetupDialog::onClickUi_ImageView));
        JLGoumai5->setTag(kTagBtnJLGoumai_5);
        JLGoumai5->addTouchEventListener(this, toucheventselector(SceneSetupDialog::onClickUi_ImageView));
    
    
    
    
    
    //注册恢复购买
        uiRegButton_imageview(ui_JBSheZhi, "huiFuGouMai",kTagBtnHuiFuGouMai , zTagDefault);
        pTextField1->setVisible(false);
        pTextField2->setVisible(false);
        pTextField1->setEnabled(false);
        pTextField2->setEnabled(false);                                                                                                     
    
        //改变精灵的购买价格
        ImageView* goumai1 = (ImageView*)scrollView_jingling->getChildByName("goumai_1");
        ImageView* goumai2 = (ImageView*)scrollView_jingling->getChildByName("goumai_2");
        goumai1->loadTexture(SETUP_DIALOG_UI_PATH + "/button_jl_goumai_1.png",Widget::TextureResType::LOCAL);
        goumai2->loadTexture(SETUP_DIALOG_UI_PATH + "/button_jl_goumai_1.png",Widget::TextureResType::LOCAL);
    
    
        //change the libao tab view UI
    if (scrollView_libao != nullptr) {
        ImageView* libao = (ImageView*)scrollView_libao->getChildByName("libao1");
        ImageView* lb_goumai = (ImageView*)scrollView_libao->getChildByName("goumai");
        lb_goumai->loadTexture("ui/NewSetupDialog_1_11_20/button_lb_goumai_1.png",Widget::TextureResType::LOCAL);
        libao->loadTexture(SETUP_DIALOG_UI_PATH + "/lb_gm_xx_1.png",Widget::TextureResType::LOCAL);
    }
    
    
    //change the ui of the jianbihua scrollview
    if(scrollView_jianbihua != nullptr){
        
    }
    
        
        
        //计算简笔画界面的一些参数
        UserData* data = new UserData();
        __Dictionary* jbhDic = data->jbhDic;
        __String* jbh1 = dynamic_cast<__String*>(jbhDic->objectForKey("1"));
        __String* jbh2 = dynamic_cast<__String*>(jbhDic->objectForKey("2"));
        __String* jbh3 = dynamic_cast<__String*>(jbhDic->objectForKey("3"));
        __String* jbh4 = dynamic_cast<__String*>(jbhDic->objectForKey("4"));
        __String* jbh5 = dynamic_cast<__String*>(jbhDic->objectForKey("5"));
    
    
        
        
        int length1 = jbh1->length();
        int length2 = jbh2->length();
        int length3 = jbh3->length();
        int length4 = jbh4->length();
        int length5 = jbh5->length();
    
    
        
        
        int* lengths = new int[JBH_SET_NUMBER];
        *(lengths + 0) = length1;
        *(lengths + 1) = length2;
        *(lengths + 2) = length3;
        *(lengths + 3) = length4;
        *(lengths + 4) = length5;
    
    
    
    
        
        for(int i = 0;i < jianBiHuas.size();i++)
        {
            if(*(lengths + i) == 3)
            {
                *(isJianbihuaGoumai + i) = true;
            }
        }
        countUpMoveDistances();//得到 num_jbh_goumai
        //另外这个函数还得到upMoveDistances(int* )
    /*
        int width = scrollView_jianbihua->getInnerContainerSize().width;
        int height = scrollView_jianbihua->getInnerContainerSize().height;
        CCLOG("when you get a new scrollview, the height is %d", height);
        decreaseHeight =num_jbh_goumai*266;
        scrollView_jianbihua->setInnerContainerSize(Size(width, height - decreaseHeight));
        int newHeight = scrollView_jianbihua->getInnerContainerSize().height;
        CCLOG("you get in, and you change the height of the scrollview, and you get %d",newHeight);
        */
    
    
        //check how many jbhs has been bought
        refreshJBH(0, jianBiHuas.size() + 1, num_jbh_goumai);
        //check if the user has bought the liBao
        UserData* myData = new UserData();
        __String* isLiBaoBought = (__String*)myData->isLiBaoBought;
        int length = isLiBaoBought->length();
        if(length == 3){
            ImageView* liBaoBought = (ImageView*)scrollView_libao->getChildByName("goumai");
            liBaoBought->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/libao/button_lb_goumai_2.png");
            liBaoBought->setEnabled(false);
    }
    
    
    //COVEN
    delete myData;
    myData = NULL;
    delete data;
    data = NULL;
    delete lengths;
    lengths = NULL;
    
    
	return true;
}



void SceneSetupDialog::lb_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product_libao";
    iap->gouMaiJBHSetID = 11;
    iap->requestProducts();
}

void SceneSetupDialog::jl1_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.elfproduct1";
    iap->gouMaiJBHSetID = 9;
    iap->requestProducts();
}
void SceneSetupDialog::jl2_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.elfproduct2";
    iap->gouMaiJBHSetID = 10;
    iap->requestProducts();
}


//精灵3， 4，5的购买product identity刚好用简笔画6 7 8的
void SceneSetupDialog::jl3_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product6";
    iap->gouMaiJBHSetID = 6;
    iap->requestProducts();
}
void SceneSetupDialog::jl4_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product7";
    iap->gouMaiJBHSetID = 7;
    iap->requestProducts();
}
void SceneSetupDialog::jl5_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product8";
    iap->gouMaiJBHSetID = 8;
    iap->requestProducts();
}


void SceneSetupDialog::jbh1_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product1";
    iap->gouMaiJBHSetID = 1;
    iap->requestProducts();
    
    
}
void SceneSetupDialog::jbh2_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product2";
    iap->gouMaiJBHSetID = 2;
    iap->requestProducts();
}
void SceneSetupDialog::jbh3_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product3";
    iap->gouMaiJBHSetID = 3;
    iap->requestProducts();
    
    
}
void SceneSetupDialog::jbh4_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product4";
    iap->gouMaiJBHSetID = 4;
    iap->requestProducts();
    
}
void SceneSetupDialog::jbh5_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product5";
    iap->gouMaiJBHSetID = 5;
    iap->requestProducts();
    
}
void SceneSetupDialog::jbh6_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product6";
    iap->gouMaiJBHSetID = 6;
    iap->requestProducts();
    
    
}
void SceneSetupDialog::jbh7_goumai()
{
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product7";
    iap->gouMaiJBHSetID = 7;
    iap->requestProducts();
    
}
void SceneSetupDialog::jbh8_goumai(){
    iap->_setup = this;
    iap->productIdentifier = "com.elf.iaptest.product8";
    iap->gouMaiJBHSetID = 8;
    iap->requestProducts();
    
    
}


void SceneSetupDialog::jbshezhiKeJian()
{
    jbshezhi->setVisible(true);
    ui_shangdian->setVisible(false);
    ui_JBSheZhi->setVisible(true);
}

void SceneSetupDialog::gsxinxiKeJian()
{
    gsxinxi->setVisible(true);
}

void SceneSetupDialog::shangdianKeJian()
{
    shangdian->setVisible(true);
    ui_JBSheZhi->setVisible(false);
    ui_shangdian->setVisible(true);
}

void SceneSetupDialog::xuanchuanKeJian()
{
    xuanchuan->setVisible(true);
}








void SceneSetupDialog::onClickUi_ImageView(Ref* sender, TouchEventType type)
{
    int id = -1;
	ImageView* btn = dynamic_cast<ImageView*>(sender);
	if (btn != nullptr)
	{
        
		id = btn->getTag();
	}
	if (type != TOUCH_EVENT_ENDED)
		return;
	CCLOG("onClick!!! id=%d", id);
    
    
    
    
    //－－－－－－－－－－－－－－－－－－－－设置主界面按钮－－－－－－－－－－－－－－－－－－－－－－－
        if (id == kTagBtnHome)
        {
            //save the user's personal infos
            int nameLength = pTextField1->getStringLength();
            int ageLength = pTextField2->getStringLength();
            
            if(nameLength > 0 && ageLength > 0)
            {
                __String* name = __String::create(pTextField1->getStringValue());
                __String* age = __String::create(pTextField2->getStringValue());
                UserData* data = new UserData();
                data->setUser(name, age);
                //for test
                //data->showData();
            }
            
            this->retain();
            this->removeFromParentAndCleanup(true);
            this->removeAllChildrenWithCleanup(true);
            //coven0202
            this->release();
            
            //return back to the sceneTitle
            sceneTitle->newBoughtJBHSet = newBoughtJBHSet;
            sceneTitle->newBoughtJBHSetNumber = newBoughtJBHNumber;
            SceneTitle* sceneTitle = SceneTitle::create();
            auto scene = Scene::create();
            scene->addChild(sceneTitle);
            sceneTitle->getDataFromSceneController();
            //CCLOG("when the data is downloaded from the Controller");
            //SceneController::getInstance()->data->printData();
            Director::getInstance()->replaceScene(scene);

            
            
            
            SceneTitle::clearCache();
        }
        else if (id == kTagBtnGSXinXi)//宣传
        {
            ui_shangdian->setVisible(false);
            ui_JBSheZhi->setVisible(false);
            jieshaoUI->setVisible(false);
           
            if(added !=nullptr)
            {
                ui->removeChildByTag(2000);
                ui->removeChildByTag(2000);
            }
            added = Sprite::createWithSpriteFrameName("button_gsxinxi_1.png");
            added->setAnchorPoint(Vec2(0.5f,0.5f));
            ui->addChild(added, 10, 2000);
            Vec2 pos = btn->getPosition();
            pos.x = pos.x + 75;
            pos.y = pos.y - 75;
            added->setPosition(pos);
            
            pTextField1->setEnabled(false);
            pTextField2->setEnabled(false);
            pTextField1->setVisible(false);
            pTextField2->setVisible(false);
            pTextField1->setZOrder(0);
            pTextField2->setZOrder(0);
            
            

            xinxi->setAnchorPoint(Vec2(0,0));
            xinxi->setPosition(Vec2(220,260));
            xinxi->setScale(0.5f);
            xinxi->setVisible(true);
            
        }
        else if (id == kTagBtnJBSheZhi)
        {
            ui_shangdian->setVisible(false);
            xinxi->setVisible(false);
            jieshaoUI->setVisible(false);
            ui_JBSheZhi->setVisible(true);
            
            float bgmVolumn = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
            float effectColumn = SimpleAudioEngine::getInstance()->getEffectsVolume();
            CCLOG("bgmVolumn is %f, effectColumn is %f", bgmVolumn,effectColumn);
            initYinliangPic(bgmVolumn * 10, effectColumn * 10);
            
            pTextField1->setEnabled(true);
            pTextField2->setEnabled(true);
            pTextField1->setVisible(true);
            pTextField2->setVisible(true);
            
            
            //set the pressed button highlightened
            if(added != nullptr)
            {
                ui->removeChildByTag(2000);
            }
            added = Sprite::createWithSpriteFrameName("button_jbshezhi_1.png");
            added->setAnchorPoint(Vec2(0.5f,0.5f));
            ui->addChild(added, 10, 2000);
            Vec2 pos = btn->getPosition();
            pos.x = pos.x + 75;
            pos.y = pos.y - 75;
            added->setPosition(pos);
            
            
            
            //show the user's saved personal info
            UserData* data = new UserData();
            Vector<__String*>* userInfo = data->getUserInfo();
            if(userInfo->size() == 2){
                pTextField1->setText(userInfo->at(0)->getCString());
                pTextField2->setText(userInfo->at(1)->getCString());
            }else{
                CCLOG("get user info failed or not saved yet!");
            }
            
            //COVEN
            delete data;
            data = NULL;
            delete userInfo;
            userInfo = NULL;
        }
        else if (id == kTagBtnShangDian)
        {
            ui_JBSheZhi->setVisible(false);
            jieshaoUI->setVisible(false);
            xinxi->setVisible(false);

            ui_shangdian->setVisible(true);
            
            pTextField1->setEnabled(false);
            pTextField2->setEnabled(false);
            pTextField1->setVisible(false);
            pTextField2->setVisible(false);
            pTextField1->setZOrder(0);
            pTextField2->setZOrder(0);
            
            if(added !=nullptr)
            {
                ui->removeChildByTag(2000);
            }
            added = Sprite::createWithSpriteFrameName("button_shangdian_1.png");
            added->setAnchorPoint(Vec2(0.5f,0.5f));
            ui->addChild(added, 10, 2000);
            Vec2 pos = btn->getPosition();
            pos.x = pos.x + 75;
            pos.y = pos.y - 75;
            added->setPosition(pos);
        }
        else if (id == kTagBtnXuanChuan)//介绍
        {
            xinxi->setVisible(false);
            ui_shangdian->setVisible(false);
            ui_JBSheZhi->setVisible(false);
            
            if(added !=nullptr)
            {
                ui->removeChildByTag(2000);
            }
            added = Sprite::createWithSpriteFrameName("button_xuanchuan_1.png");
            added->setAnchorPoint(Vec2(0.5f,0.5f));
            ui->addChild(added, 10, 2000);
            Vec2 pos = btn->getPosition();
            pos.x = pos.x + 75;
            pos.y = pos.y - 75;
            added->setPosition(pos);
            
            pTextField1->setEnabled(false);
            pTextField2->setEnabled(false);
            pTextField1->setVisible(false);
            pTextField2->setVisible(false);
            pTextField1->setZOrder(0);
            pTextField2->setZOrder(0);
            
            CCSize vSize = Director::getInstance()->getVisibleSize();
            Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
            float gx = vOrigin.x - (jieshaoUI->getContentSize().width - vSize.width) / 2;
            float gy = vOrigin.y - (jieshaoUI->getContentSize().height - vSize.height) / 2;
            jieshaoUI->setPosition(Vec2(gx - 200, gy - 200));
            jieshaoUI->setVisible(true);
         
        }
    
    
    
                                                    //商店标签按钮
        else if (id == kTagBtnLiBao)
        {
            //礼包高亮
            if(added_Shangdian != nullptr)
            {
                ui_shangdian->removeChildByTag(103);
            }
            added_Shangdian = Sprite::createWithSpriteFrameName("shangdian_libao_biaoqian_1.png");
            ui_shangdian->addChild(added_Shangdian,10,103);
            added_Shangdian->setAnchorPoint(Vec2(0, 1));
            added_Shangdian->setPosition(btn->getPosition());
            
            
            scrollView_libao->setVisible(true);
            scrollView_fuwu->setVisible(false);
            scrollView_jianbihua->setVisible(false);
            scrollView_jingling->setVisible(false);
            
            //check if the user has bought the liBao
            UserData* data = new UserData();
            __String* isLiBaoBought = (__String*)data->isLiBaoBought;
            int length = isLiBaoBought->length();
            if(length == 3){
                ImageView* liBaoBought = (ImageView*)scrollView_libao->getChildByName("goumai");
                liBaoBought->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/libao/button_lb_goumai_2.png");
                liBaoBought->setEnabled(false);
            }
            
            
        }
        else if (id == kTagBtnFuWu)
        {
            //服务高亮
            if(added_Shangdian != nullptr)
            {
                ui_shangdian->removeChildByTag(103);
            }
            added_Shangdian = Sprite::createWithSpriteFrameName("shangdian_fuwu_biaoqian_1.png");
            ui_shangdian->addChild(added_Shangdian,10,103);
            added_Shangdian->setAnchorPoint(Vec2(0, 1));
            added_Shangdian->setPosition(btn->getPosition());
            
            
            scrollView_libao->setVisible(false);
            scrollView_fuwu->setVisible(true);
            scrollView_jianbihua->setVisible(false);
            scrollView_jingling->setVisible(false);
        }
        else if (id == kTagBtnJingling)
        {
            //精灵高亮
            if(added_Shangdian != nullptr)
            {
                ui_shangdian->removeChildByTag(103);
            }
            added_Shangdian = Sprite::createWithSpriteFrameName("shangdian_jingling_biaoqian_1.png");
            ui_shangdian->addChild(added_Shangdian,10,103);
            added_Shangdian->setAnchorPoint(Vec2(0, 1));
            added_Shangdian->setPosition(btn->getPosition());
            
            scrollView_libao->setVisible(false);
            scrollView_fuwu->setVisible(false);
            scrollView_jianbihua->setVisible(false);
            scrollView_jingling->setVisible(true);
            
            //根据用户购买精灵的情况来更新UI
            UserData* data = new UserData();
            __Dictionary* elfDic = data->elfDic;
            __String* jl1 = dynamic_cast<__String*>(elfDic->objectForKey("1"));
            __String* jl2 = dynamic_cast<__String*>(elfDic->objectForKey("2"));
            __String* jl3 = dynamic_cast<__String*>(elfDic->objectForKey("3"));
            __String* jl4 = dynamic_cast<__String*>(elfDic->objectForKey("4"));
            __String* jl5 = dynamic_cast<__String*>(elfDic->objectForKey("5"));
            
            int length1 = jl1->length();
            int length2 = jl2->length();
            int length3 = jl3->length();
            int length4 = jl4->length();
            int length5 = jl5->length();
            
            
            if(length1 == 3)
            {
                //将精灵1的购买按钮置为已购买，并设为unable
                JLGoumai1->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
                JLGoumai1->setEnabled(false);
            }
            if(length2 == 3)
            {
                //将精灵2的购买按钮置为已购买，并设为unable
                JLGoumai2->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
                JLGoumai2->setEnabled(false);
            }
            if(length3 == 3)
            {
                //将精灵1的购买按钮置为已购买，并设为unable
                JLGoumai3->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
                JLGoumai3->setEnabled(false);
            }
            if(length4 == 3)
            {
                //将精灵2的购买按钮置为已购买，并设为unable
                JLGoumai4->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
                JLGoumai4->setEnabled(false);
            }
            if(length5 == 3)
            {
                //将精灵1的购买按钮置为已购买，并设为unable
                JLGoumai5->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
                JLGoumai5->setEnabled(false);
            }
           
            //COVEN
            delete data;
            data  = NULL;
        }
        else if (id == kTagBtnJianBiHua)
        {
            float width = scrollView_jianbihua->getContentSize().width;
            float height = scrollView_jianbihua->getContentSize().height;
            CCLOG("%f, %f",width,height);
            
            float _width = scrollView_jianbihua->getCustomSize().width;
            float _height = scrollView_jianbihua->getCustomSize().height;
            CCLOG("_%f, _%f",_width,_height);
            
            
            
            
            //简笔画高亮
            if(added_Shangdian != nullptr)
            {
                ui_shangdian->removeChildByTag(103);
            }
            added_Shangdian = Sprite::createWithSpriteFrameName("shangdian_jianbihua_biaoqian_1.png");
            ui_shangdian->addChild(added_Shangdian,10,103);
            added_Shangdian->setAnchorPoint(Vec2(0, 1));
            added_Shangdian->setPosition(btn->getPosition());
            
            scrollView_libao->setVisible(false);
            scrollView_fuwu->setVisible(false);
            scrollView_jingling->setVisible(false);
            scrollView_jianbihua->setVisible(true);
            
            
            
            //decreaseHeight and num_jbh_goumai has got in init_ui()
            //the scrollview's height has been changed too...
            //so...
            //这里面不涉及到对contianerSize的操作，只是对简笔画位置的更改
            //num_jbh_goumai:用户已经购买的简笔画数量
            
            
           
        
            
            
        }
    
    
    
    //-------------------------------------------各种购买按钮-----------------------------------------
    else if(id == kTagBtnLiBaoGoumai)
    {
        //CCLOG("libao_goumai is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::lb_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
    }
    else if(id == kTagBtnJLGoumai_1)
    {
        ImageView* goumai1 = (ImageView*)scrollView_jingling->getChildByName("goumai_1");
        ImageView* goumai2 = (ImageView*)scrollView_jingling->getChildByName("goumai_2");
        
        float dis = goumai2->getPosition().y - goumai1->getPosition().y;
        CCLOG("dis %f", dis);
        
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jl1_goumai, this));
        btn->runAction(CCSequence::create(action1
                                            ,action2
                                            ,action3
                                            ,action4
                                            ,action5
                                            ,action6
                                            ,call
                                            ,NULL));
        
        
        
    }
    else if(id == kTagBtnJLGoumai_2)
    {
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jl2_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
        
    }
    else if(id == kTagBtnJLGoumai_3)
    {
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jl3_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
        
    }
    else if(id == kTagBtnJLGoumai_4)
    {
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jl4_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
        
    }
    else if(id == kTagBtnJLGoumai_5)
    {
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jl5_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
        
    }
    
    else if(id == kTagBtnJBHGoumai_1)
    {
        CCLOG("JBHGoumai1 is touched");
        
        
        
        
        
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh1_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
        
    }
    else if(id == kTagBtnJBHGoumai_2)
    {
        CCLOG("JBHGoumai2 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh2_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
    }
    else if(id == kTagBtnJBHGoumai_3)
    {
        CCLOG("JBHGoumai3 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh3_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
      
    }
    else if(id == kTagBtnJBHGoumai_4)
    {
        CCLOG("JBHGoumai4 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh4_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
       
    }
    else if(id == kTagBtnJBHGoumai_5)
    {
        CCLOG("JBHGoumai5 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh5_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
     
    }
    else if(id == kTagBtnJBHGoumai_6)
    {
        CCLOG("JBHGoumai6 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh6_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
    }
    else if(id == kTagBtnJBHGoumai_7)
    {
        
        CCLOG("JBHGoumai7 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh7_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
       
    }
    else if(id == kTagBtnJBHGoumai_8)
    {
        
        CCLOG("JBHGoumai8 is touched");
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::jbh8_goumai, this));
        btn->runAction(CCSequence::create(action1
                                          ,action2
                                          ,action3
                                          ,action4
                                          ,action5
                                          ,action6
                                          ,call
                                          ,NULL));
        
    }
   
    else if(id == kTagBtnHuiFuGouMai)
    {
        auto action1 = ScaleTo::create(0.3f, 0.9f);
        auto action2 = ScaleTo::create(0.1f, 1.0f);
        auto action3 = ScaleTo::create(0.1f, 1.05f);
        auto action4 = ScaleTo::create(0.1f, 0.9f);
        auto action5 = ScaleTo::create(0.05f, 1.05f);
        auto action6 = ScaleTo::create(0.05f, 1.0f);
        CallFunc* call  =CallFunc::create(CC_CALLBACK_0(SceneSetupDialog::huiFuGouMai_callfunc, this));
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

int SceneSetupDialog::getNewBoughtJBHNumber()
{
    return newBoughtJBHNumber;
}

void SceneSetupDialog::setNewBoughtJBHNumber(int newBoughtJBHNumber)
{
    this->newBoughtJBHNumber = newBoughtJBHNumber;
}

int* SceneSetupDialog::getNewBoughtJBHSet()
{
    return newBoughtJBHSet;
}

void SceneSetupDialog::setNewBoughtJBHSet(int *newBoughtJBHSet)
{
    this->newBoughtJBHSet = newBoughtJBHSet;
}







void SceneSetupDialog::huiFuGouMai_callfunc()
{
    //CCLOG("huifugoumai is touched");
    //iap->_setup = this;
    //iap->restoreCompletedTransactions();
    //UserData* data = new UserData();
    //CCLOG("恢复之后:");
    //data->showData();
}


void SceneSetupDialog::countUpMoveDistances()
{
    //得到每一个简笔画应该上移的距离
    for (int i = 0; i < JBH_SET_NUMBER;)
    {
        if(*(isJianbihuaGoumai + i))
        {
            num_jbh_goumai++;
            if(i != JBH_SET_NUMBER - 1)
            {
                i++;
                *(upMoveDistances + i) = num_jbh_goumai;
            }
            else
            {
                *(upMoveDistances + i) = num_jbh_goumai;
                i++;
            }
        }
        else
        {
            *(upMoveDistances + i) = num_jbh_goumai;
            i++;
        }
    }//for
}




void SceneSetupDialog::closeCallback()
{
    this->retain();
    this->removeFromParentAndCleanup(true);
}





void SceneSetupDialog::updateJBHBoughtStatus(int setId)
{
    *(newBoughtJBHSet + newBoughtJBHNumber) = setId;
    newBoughtJBHNumber++;
}


bool SceneSetupDialog::updateUserData(bool isJBHBought, const char* idx){
    bool hasUpdated = false;
    
    if(isJBHBought){
        UserData* data = new UserData();
        __Dictionary* jbhDic = data->jbhDic;
        jbhDic->setObject(__String::create("yes"), idx);
        data->sceneDic->setObject(__String::create("yes"), idx);
        //write to file
        std::string path = CCFileUtils::getInstance()->getWritablePath();
        std::string _doc1 = path + "test.plist";
        bool hasWritenToFile = data->plistDic->writeToFile(_doc1.c_str());
        if(hasWritenToFile){
            hasUpdated = true;
        }
        
    }else{
        UserData* data = new UserData();
        __Dictionary* elfDic = data->elfDic;
        elfDic->setObject(__String::create("yes"), idx);
        //write to file
        std::string path = CCFileUtils::getInstance()->getWritablePath();
        std::string _doc1 = path + "test.plist";
        data->plistDic->writeToFile(_doc1.c_str());
        hasUpdated = true;
    }
    return hasUpdated;
}





void SceneSetupDialog::afterJBHGouMai(int setID)
{
    //让第setID套简笔画添加到简笔画图鉴中去
    //setID 1 to JBH_SET_NUMBER
    //现在让这个函数兼而处理用户的购买精灵的事件
    //还有购买礼包事件
    switch (setID){
        case 1:
        {
            //CCLOG("set1 is bought");tested successfully on 14/8/28
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"1");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(1);//这里面更新的数据是为了和title做交互，便于简笔画图鉴的显示
            
            
            
            break;
        }
        case 2:
        {
            //CCLOG("set1 is bought");tested successfully on 14/8/28
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"2");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(2);
            break;
        }
        case 3:
        {
            //CCLOG("set1 is bought");tested successfully on 14/8/28
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
           
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"3");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(3);
            
            
            break;
        }
        case 4:
        {
            //CCLOG("set1 is bought");tested successfully on 14/8/28
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            
            
            
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"4");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(4);
            break;
        }
        case 5:
        {
            //CCLOG("set1 is bought");tested successfully on 14/8/28
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"5");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(5);
            break;
        }
         
            
            //case 6,7,8分别处理精灵3,4,5
        case 6:
        {
            JLGoumai3->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
            JLGoumai3->setEnabled(false);
            //修改plist使精灵1的购买是yes
            updateUserData(false,"3");
            sceneTitle->boughtElfId = 3;
            
            
            /*
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"5");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(5);
             */
            
            break;
        }
        case 7:
        {
            JLGoumai4->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
            JLGoumai4->setEnabled(false);
            //修改plist使精灵1的购买是yes
            updateUserData(false,"4");
            sceneTitle->boughtElfId = 4;
            
            /*
            //CCLOG("set1 is bought");tested successfully on 14/8/28
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"5");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(5);
             */
            
            break;
        }case 8:
        {
            JLGoumai5->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
            JLGoumai5->setEnabled(false);
            //修改plist使精灵1的购买是yes
            updateUserData(false,"5");
            sceneTitle->boughtElfId = 5;
            
            
            /*
            *(isJianbihuaGoumai + setID - 1) = true;
            //更改购买图片为已购买图片并set unable
            JBHGouMais.at(setID - 1)->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/jbh/button_jbh_goumai_2.png");
            JBHGouMais.at(setID - 1)->setEnabled(false);
            
            
            //更新UserData中的数据
            bool hasUpdated = updateUserData(true,"5");
            if(hasUpdated){
                CCLOG("has been updated");
            }
            updateJBHBoughtStatus(5);
             */
            
            break;
        }
            
            
            
            //处理精灵购买------------------------------------------------------
        case 9:
        {
            //购买精灵1
            //更改精灵的购买按钮为已购买，并且设为unable
            JLGoumai1->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
            JLGoumai1->setEnabled(false);
            //修改plist使精灵1的购买是yes
            updateUserData(false,"1");
            sceneTitle->boughtElfId = 1;
            
            break;
        }
        case 10:
        {
            //购买精灵2
            //更改精灵的购买按钮为已购买，并且设为unable
            JLGoumai2->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/elf/button_jl_goumai_2.png");
            JLGoumai2->setEnabled(false);
            //修改plist使精灵2的购买是yes
            updateUserData(false,"2");
            sceneTitle->boughtElfId = 2;
            break;
        }
            //-------------------------------------------------礼包购买
        case 11:
        {
            //设置礼包购买按钮为已购买，并unable
            scrollView_libao = (cocos2d::ui::ScrollView*)getChildFromMyUI((ImageView*)ui->getChildByName("ui_shangdian"), "ScrollView_libao");
            ImageView* lb_goumai = (ImageView*)scrollView_libao->getChildByName("goumai");
            if(lb_goumai != nullptr){
                lb_goumai->loadTexture(SETUP_DIALOG_UI_PATH + "/boughtStateChange/libao/button_lb_goumai_2.png");
                lb_goumai->setEnabled(false);
            }

            //update userData
            UserData* data = new UserData();
            data->plistDic->setObject(new __String("yes"), "isLiBaoBought");
            //write to file
            std::string path = CCFileUtils::getInstance()->getWritablePath();
            std::string _doc1 = path + "test.plist";
            data->plistDic->writeToFile(_doc1.c_str());
            
            
            this->afterJBHGouMai(1);
            this->afterJBHGouMai(2);
            this->afterJBHGouMai(3);
            this->afterJBHGouMai(4);
            this->afterJBHGouMai(5);
            this->afterJBHGouMai(6);
            this->afterJBHGouMai(7);
            this->afterJBHGouMai(8);
   
            this->afterJBHGouMai(9);
            this->afterJBHGouMai(10);
            
            /*
            this->afterJBHGouMai(3);
            this->afterJBHGouMai(4);
            this->afterJBHGouMai(5);
             */
            
            /*
            this->afterJBHGouMai(9);
            this->afterJBHGouMai(10);
             */
            
            
        }
        
    }
}
/*
void SceneSetupDialog::onExit(){
    Layer::onExit();
    
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
    
    Util::cleanTextureCacheWithMessage("exit title");
    
}
*/

void SceneSetupDialog::uiRegButton_imageview(Widget* parent, const std::string& name, int k, int z)
{
	ImageView* btn = (ImageView*)parent->getChildByName(name);
	if (btn)
	{
		//CCLOG("注册成功");
        btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneSetupDialog::onClickUi_ImageView));
		btn->setZOrder(z);
		//parent->addChild(btn, z);
	}
}


void SceneSetupDialog::clearJBHZongJia()
{
    //清零简笔画总价按钮的数字
    int count = 0;
    count++;//为了和图片资源保持一致
    std::ostringstream oss;
    oss<<count;
    std::string sCount = oss.str();
    std::string str1 = "button_jbh_goumai_";
    std::string str2 = ".png";
    std::string filename = str1+sCount+str2;
    //zongJia->loadTexture(filename,Widget::TextureResType::PLIST);
}




//基本设置中增加的方法
void SceneSetupDialog::initYinliangPic(int bgmColumn, int effectColumn)
{
    //传入的bgmColumn实际是m(0~1)的十倍，因为switch好像只能接受int
    switch (bgmColumn) {
        case 0:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_0.png",Widget::TextureResType::PLIST);
            break;
        }
        case 1:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_1.png",Widget::TextureResType::PLIST);
            break;
        }
        case 2:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_2.png",Widget::TextureResType::PLIST);
            break;
        }
        case 5:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_3.png",Widget::TextureResType::PLIST);
            break;
        }
        case 6:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_4.png",Widget::TextureResType::PLIST);
            break;
        }
        case 8:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_5.png",Widget::TextureResType::PLIST);
            break;
        }
        case 10:
        {
            bgmusic->loadTexture("jibenshezhi_yingliang_6.png",Widget::TextureResType::PLIST);
            break;
        }
        default:
        {
            CCLOG("invalid bgmColumn input");
            break;
        }
            
    }
    
    
    switch (effectColumn) {
        case 0:
        {
            volume->loadTexture("jibenshezhi_yingliang_0.png",Widget::TextureResType::PLIST);
            break;
        }
        case 1:
        {
            volume->loadTexture("jibenshezhi_yingliang_1.png",Widget::TextureResType::PLIST);
            break;
        }
        case 2:
        {
            volume->loadTexture("jibenshezhi_yingliang_2.png",Widget::TextureResType::PLIST);
            break;
        }
        case 5:
        {
            volume->loadTexture("jibenshezhi_yingliang_3.png",Widget::TextureResType::PLIST);
            break;
        }
        case 6:
        {
            volume->loadTexture("jibenshezhi_yingliang_4.png",Widget::TextureResType::PLIST);
            break;
        }
        case 8:
        {
            volume->loadTexture("jibenshezhi_yingliang_5.png",Widget::TextureResType::PLIST);
            break;
        }
        case 10:
        {
            volume->loadTexture("jibenshezhi_yingliang_6.png",Widget::TextureResType::PLIST);
            break;
        }
        default:
        {
            CCLOG("invalid bgmColumn input");
            break;
        }
            
    }
}

bool SceneSetupDialog::onTouchBegan(Touch * touch, Event * pEvent)
{
	Vec2 posW = touch->getLocation();
    
    
    auto start = touch->getPreviousLocation();
    startP = posW;
    
    //CCLOG("start%f     %f", startP.x,startP.y);
    
    
    //pTextField1->setVisible(false);
    
    if(startP.x>721 && startP.x<915 && startP.y>394 &&startP.y<454 && flag1==0)
    {
        
        //pTextField1->setVisible(true);
        //pTextField1->setEnabled(true);
        CCLOG("added's position is (%f,%f)", added->getPosition().x, added->getPosition().y);
        CCLOG("jbshezhi's position is (%f,%f)", jbshezhi->getPosition().x, jbshezhi->getPosition().y);
        
        if((added->getPosition().x - 75) == jbshezhi->getPosition().x)
        {
            pTextField1->attachWithIME();
            CCLOG("IME attached");
        }
        
    }
    
    if(startP.x>721 && startP.x<915 && startP.y>282 &&startP.y<342 && flag2==0)
    {
        if((added->getPosition().x - 75) == jbshezhi->getPosition().x)
        {
            pTextField2->attachWithIME();
            CCLOG("IME attached");
        }

        //flag2=1;
    }
    //  else if(flag2==1) pTextField2->detachWithIME();
    
    
    
	return true;
}

void SceneSetupDialog::onTouchEnded(Touch * touch, Event * pEvent)
{
    auto end = touch->getLocation();
    
    
    
    if((added->getPosition().x - 75) == jbshezhi->getPosition().x)
    {
        //现在是在基本设置下
        if(end.x<510 && startP.x>308 && end.y<600 && startP.y >540 && startP.x<510 && end.x>308 && startP.y<600 && end.y >540)
        {
            if (end.x>=325 && end.x<356)
            {
                volumeFlag1=1;
                m=0.1;
            }
            else if (end.x>=356 && end.x<387)
            {
                volumeFlag1=2;
                m=0.2;
            }
            else if (end.x>=387 && end.x<418)
            {
                volumeFlag1=3;
                m=0.5;
            }
            else if (end.x>=418 && end.x<449)
            {
                volumeFlag1=4;
                m=0.6;
            }
            else if (end.x>=449 && end.x<480)
            {
                volumeFlag1=5;
                m=0.8;
            }
            else if (end.x>=480 && end.x<510)
            {
                volumeFlag1=6;
                m=1.0;
            }
            else if(end.x>=308 && end.x<325)
            {
                volumeFlag1=0;
                m=0;
            }
            
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m);
            
            
            
            
            if(volumeFlag1==0)      bgmusic->loadTexture("jibenshezhi_yingliang_0.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==1) bgmusic->loadTexture("jibenshezhi_yingliang_1.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==2) bgmusic->loadTexture("jibenshezhi_yingliang_2.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==3) bgmusic->loadTexture("jibenshezhi_yingliang_3.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==4) bgmusic->loadTexture("jibenshezhi_yingliang_4.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==5) bgmusic->loadTexture("jibenshezhi_yingliang_5.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==6) bgmusic->loadTexture("jibenshezhi_yingliang_6.png",Widget::TextureResType::PLIST);
            
        }
        
        else if(end.x<510 && startP.x>308 && end.y<460 && startP.y >397 && startP.x<510 && end.x>308 && startP.y<460 && end.y >397)                //语音音效
        {
            if (end.x>=325 && end.x<356)
            {
                volumeFlag2=1;
                n=0.1;
            }
            else if (end.x>=356 && end.x<387)
            {
                volumeFlag2=2;
                n=0.2;
            }
            else if (end.x>=387 && end.x<418)
            {
                volumeFlag2=3;
                n=0.5;
            }
            else if (end.x>=418 && end.x<449)
            {
                volumeFlag2=4;
                n=0.6;
            }
            else if (end.x>=449 && end.x<480)
            {
                volumeFlag2=5;
                n=0.8;
            }
            else if (end.x>=480 && end.x<510)
            {
                volumeFlag2=6;
                n=1.0;
            }
            else if(end.x>=308 && end.x<325)
            {
                volumeFlag2=0;
                n=0;
            }
            
            SimpleAudioEngine::sharedEngine()->setEffectsVolume(n);
            
            
            
            
            if(volumeFlag2==0)      volume->loadTexture("jibenshezhi_yingliang_0.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==1) volume->loadTexture("jibenshezhi_yingliang_1.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==2) volume->loadTexture("jibenshezhi_yingliang_2.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==3) volume->loadTexture("jibenshezhi_yingliang_3.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==4) volume->loadTexture("jibenshezhi_yingliang_4.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==5) volume->loadTexture("jibenshezhi_yingliang_5.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==6) volume->loadTexture("jibenshezhi_yingliang_6.png",Widget::TextureResType::PLIST);
            
        }
    }
    
}



void SceneSetupDialog::onTouchMoved(Touch * touch, Event * pEvent)
{
	Vec2 posW = touch->getLocation();
    
	auto end = touch->getLocation();
    
    CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    Vec2 posWCenter = Vec2(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height / 2);
    
    CCLOG("end%f     %f", end.x,end.y);
    

    
    
    
    //if(end.x<510 && startP.x>325 && end.y<638 && startP.y >558 && startP.x<510 && end.x>325 && startP.y<638 && end.y >558)                     //背景音乐
    
    
    if((added->getPosition().x - 75) == jbshezhi->getPosition().x)
    {
        if(end.x<510 && startP.x>308 && end.y<600 && startP.y >540 && startP.x<510 && end.x>308 && startP.y<600 && end.y >540)
        {
            if (end.x>=325 && end.x<356)
            {
                volumeFlag1=1;
                m=0.1;
            }
            else if (end.x>=356 && end.x<387)
            {
                volumeFlag1=2;
                m=0.2;
            }
            else if (end.x>=387 && end.x<418)
            {
                volumeFlag1=3;
                m=0.4;
            }
            else if (end.x>=418 && end.x<449)
            {
                volumeFlag1=4;
                m=0.6;
            }
            else if (end.x>=449 && end.x<480)
            {
                volumeFlag1=5;
                m=0.8;
            }
            else if (end.x>=480 && end.x<510)
            {
                volumeFlag1=6;
                m=1.0;
            }
            else if(end.x>=308 && end.x<325)
            {
                volumeFlag1=0;
                m=0;
            }
            
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m);
            
            
            
            
            
            if(volumeFlag1==0)      bgmusic->loadTexture("jibenshezhi_yingliang_0.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==1) bgmusic->loadTexture("jibenshezhi_yingliang_1.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==2) bgmusic->loadTexture("jibenshezhi_yingliang_2.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==3) bgmusic->loadTexture("jibenshezhi_yingliang_3.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==4) bgmusic->loadTexture("jibenshezhi_yingliang_4.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==5) bgmusic->loadTexture("jibenshezhi_yingliang_5.png",Widget::TextureResType::PLIST);
            else if(volumeFlag1==6) bgmusic->loadTexture("jibenshezhi_yingliang_6.png",Widget::TextureResType::PLIST);
            
        }
        
        else if(end.x<510 && startP.x>308 && end.y<460 && startP.y >397 && startP.x<510 && end.x>308 && startP.y<460 && end.y >397)                //语音音效
        {
            if (end.x>=325 && end.x<356)
            {
                volumeFlag2=1;
                n=0.1;
            }
            else if (end.x>=356 && end.x<387)
            {
                volumeFlag2=2;
                n=0.2;
            }
            else if (end.x>=387 && end.x<418)
            {
                volumeFlag2=3;
                n=0.4;
            }
            else if (end.x>=418 && end.x<449)
            {
                volumeFlag2=4;
                n=0.6;
            }
            else if (end.x>=449 && end.x<480)
            {
                volumeFlag2=5;
                n=0.8;
            }
            else if (end.x>=480 && end.x<510)
            {
                volumeFlag2=6;
                n=1.0;
            }
            else if(end.x>=308 && end.x<325)
            {
                volumeFlag2=0;
                n=0;
            }
            
            SimpleAudioEngine::sharedEngine()->setEffectsVolume( n);
            
            
            
            
            
            if(volumeFlag2==0)      volume->loadTexture("jibenshezhi_yingliang_0.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==1) volume->loadTexture("jibenshezhi_yingliang_1.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==2) volume->loadTexture("jibenshezhi_yingliang_2.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==3) volume->loadTexture("jibenshezhi_yingliang_3.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==4) volume->loadTexture("jibenshezhi_yingliang_4.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==5) volume->loadTexture("jibenshezhi_yingliang_5.png",Widget::TextureResType::PLIST);
            else if(volumeFlag2==6) volume->loadTexture("jibenshezhi_yingliang_6.png",Widget::TextureResType::PLIST);
            
            
        }
    }
    
}


