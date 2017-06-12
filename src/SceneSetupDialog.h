#ifndef __SCENE_SETUP_DIALOG_H__
#define __SCENE_SETUP_DIALOG_H__


#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "UserData.h"
#include "SceneTitle.h"
//#include "IOSiAP_Bridge.h"
//#include "IOSiAP.h"

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

class SceneSetupDialog : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	bool init_ui();
    
    
   // void onExit();
    
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneSetupDialog);
    
    
	//void playActionPointPath(Node* node, const std::vector<Point>& points, int index);
    
	//virtual void onClickUi(Ref* sender, TouchEventType type);
    
    virtual void onClickUi_ImageView(Ref* sender, TouchEventType type);
    
	void uiRegButton_imageview(Widget* parent, const std::string& name, int k, int z);
    
    //void uiRegButtonInListView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    Widget* getChildFromMyUI(Widget* parent, const std::string& name);
    
    void afterJBHGouMai(int setID);
    //void afterJLGouMai(int ID);//useless
    SceneTitle* sceneTitle;
    
    int* getNewBoughtJBHSet();
    void setNewBoughtJBHSet(int* newBoughtJBHSet);
    
    int getNewBoughtJBHNumber();
    void setNewBoughtJBHNumber(int newBoughtJBHNumber);
    void updateJBHBoughtStatus(int setId);
    
private:
    
    //10.17新增方法，传入一个bgmColumn和effectColumn，初始化音量的显示
    void initYinliangPic(int bgmColumn, int effectColumn);
    
    
    
    int* newBoughtJBHSet;
    int newBoughtJBHNumber;
    
    //将refreshJBH这个方法仅仅作为初次进入简笔画购买时的初始化工作，用户每次购买时的处理交给JBHBoughtCallback
    void refreshJBH(int decreaseHeight,int selectedJBHId, int numJBHGoumai);
    int num_jbh_goumai;
    int* upMoveDistances;//存储每一个简笔画因为更新而需要向上移动的距离
    void countUpMoveDistances();
    //10.15新增方法，用于用户购买简笔画后的显示更新
    //void JBHBoughtCallback(int boughtId);
    
    //11_21新增方法，用于再用户购买之后更新UserData中的数据
    bool updateUserData(bool isJBHBought, const char* idx);
    
    
    bool isLiBaoBought;
    
    enum selected_elf_idx
    {
        elf1 = 1,
        elf2,
        elf3,
        
        
    };
    
    int selected_elf_id = -1;
    ImageView* lastSelectedImageView;
    
    int decreaseHeight;
    
    Layout *ui;
    SpriteFrameCache *cache;
    
    Sprite* added;//用于在点击一个按钮之后，向那个按钮的位置添加一张相对应的高亮图片
    Sprite* added_Shangdian;//高亮照片,用于商店中的四个标签
    
    
    ImageView* shangdian;
    ImageView* home;
    ImageView* gsxinxi;
    ImageView* jbshezhi;
    ImageView* xuanchuan;
    
    
    void shangdianKeJian();
    //void homeKeJian();
    void gsxinxiKeJian();
    void jbshezhiKeJian();
    void xuanchuanKeJian();
    
    
    ImageView* ui_shangdian;
    ImageView* ui_JBSheZhi;
    cocos2d::ui::ScrollView* scrollView_libao;
    cocos2d::ui::ScrollView* scrollView_jianbihua;
    cocos2d::ui::ScrollView* scrollView_jingling;
    cocos2d::ui::ScrollView* scrollView_fuwu;
    
    bool* isJianbihuaGoumai;
    
    
    
    
    void clearJBHZongJia();//使简笔画总价按钮归零
    
    
    ImageView* jianbihua_1;
    ImageView* jianbihua_2;
    ImageView* jianbihua_3;
    ImageView* jianbihua_4;
    ImageView* jianbihua_5;
    ImageView* jianbihua_6;
    ImageView* jianbihua_7;
    ImageView* jianbihua_8;
    
    Vector<ImageView*> jianBiHuas;
    
    ImageView* jbh_goumai_1;
    ImageView* jbh_goumai_2;
    ImageView* jbh_goumai_3;
    ImageView* jbh_goumai_4;
    ImageView* jbh_goumai_5;
    ImageView* jbh_goumai_6;
    ImageView* jbh_goumai_7;
    ImageView* jbh_goumai_8;
    
    Vector<ImageView*> JBHGouMais;
    
    
    ImageView* jingling1;
    ImageView* jingling2;
    ImageView* jingling3;
    ImageView* jingling4;
    ImageView* jingling5;

    
    ImageView* JLGoumai1;
    ImageView* JLGoumai2;
    ImageView* JLGoumai3;
    ImageView* JLGoumai4;
    ImageView* JLGoumai5;

    
    ImageView* lb_goumai_btn;
    ImageView* libao;
    
    
    
    
    //bool isJL_1_Goumai;
    //bool isJL_2_Goumai;
    
    
    //为基本设置需要增加的内容
    //------------------------------------------------------
    bool onTouchBegan(Touch * touch, Event * pEvent);
    void onTouchMoved(Touch * touch, Event * pEvent);
    void onTouchEnded(Touch * touch, Event * pEvent);
    //void onEnter();
    //void onExit();
    
    Armature* buttonclick;
    Vec2 startP;
    int volumeFlag1=0;
    int volumeFlag2=0;
    float m=0.0f;
    float n=0.0f;
    Button* btn;
    ImageView* bgmusic;
    ImageView* volume;
    
    TextField *pTextField1;
    TextField *pTextField2;
    bool flag1=0;
    bool flag2=0;
    
	EventListenerTouchOneByOne* listener;
    //UserData* userdata;
    //---------------------------------------------------------
    
    
    
    void lb_goumai();
    void jl1_goumai();
    void jl2_goumai();
    void jl3_goumai();
    void jl4_goumai();
    void jl5_goumai();

    
    
    void jbh1_goumai();
    void jbh2_goumai();
    void jbh3_goumai();
    void jbh4_goumai();
    void jbh5_goumai();
    void jbh6_goumai();
    void jbh7_goumai();
    void jbh8_goumai();
    
    
    void huiFuGouMai_callfunc();
    
    
    ImageView* libao_btn;
    
    ImageView* huiFuGouMai;
    
    ImageView* xinxi;
    Layout* jieshaoUI;
    cocos2d::extension::ScrollView* mJieShaoScrollView;

    
    
    
};

#endif // __SCENE_TITLE_H__
