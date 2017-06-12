#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
//#include "SceneTitleUserData.h"
#include "BoughtSetsAndNum.h"
#include "UserData.h"

using namespace cocos2d;
using namespace ui;

class SceneTitle : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	bool init_ui();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneTitle);


	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);

	virtual void onClickUi(Ref* sender, TouchEventType type);

	void uiRegButton(Widget* parent, const std::string& name, int k, int z);

    //void test();
    
    
    //10.22 added by yanjia
    //为了在主界面和设置界面之间的转化能用replaceScene
    //在这两者之间的数据交互改用UserData.
    //在this->init中初始化
    Vector<__String*> localJBHStrings;
    
    //void onExit();
    
    
    int scene_id;  //1-7
    int sceneIdTemp;
    int sceneVectorId;
    int sceneVectorIdTemp;
    
    
    int elf_id;// 1~3
    int elfIdTemp;
    int elf_id_vector; //0~2
    int elfIdVectorTemp;
    Vector<ImageView*> elfs;
    int elfsSize;
    int selected_elf_id;//传递给引导模式，用于随机精灵
    int boughtElfId;//10.14从设置模式中传入，默认值是4
    
    
    int stickFigure_id;
    int stickfigureIdTemp;
    int stickFigure_id_vector;//0 ~ 40
    int stickFigureIdVectorTemp;
    int squareBlueRingId;//1~3
    int squareBlueRingIdTemp;
    std::string jbhName;//从简笔画的下面三幅图得到的文件名
    std::string jbhNameTemp;
    int* newBoughtJBHSet;// = new int[8];init in the SceneTitle:init();
    int newBoughtJBHSetNumber;
    int stickFigureSize;
    
    
    
    
    Button* setup;
    Button* scene;
    Button* elf;
    Button* stickFigure;
    Button* huace;
    
    Button* modeYD;
    Button* modeZY;
    Button* modeMH;
    
    void setupKeJian();
    void sceneKeJian();
    void elfKeJian();
    void elfKeJian_YD();
    void stickFigureKeJian();
    void huaceKeJian();
    //void modeYDKeJian();
    void modeZYKeJian();
    void modeMHKeJian();
    void confirmUserChoices();
    
    void playZYEffect1();
    void playZYEffect2();
    void playMHEffect1();
    void playMHEffect2();
    
    void getDataFromSceneController();
    //SceneTitleUserData* createSTUserData();
    
    
    //10.23新增方法，为getNewBoughtSet()提供参数，以便适应新的数据传递机制：
    //即设置与主界面之间场景的转化是通过replaceScene，数据传递通过修改本地plist
    int* getNewBoughtSet(Vector<__String*> oldJBHDic, Vector<__String*> newJBHDic);
    int getNewBoughtSetNum(Vector<__String*> oldJBHDic, Vector<__String*> newJBHDic);
    Vector<__String*> getCCStringVectorFromUserData(UserData* data);
    
    
    static void setLocalPlistValueTo(std::string allHaveBeenBought);
    
    static void clearCache();
    static void loadYunPlists();
private:
    
    //void testForSpriteBatchNode();
    
    
};

#endif // __SCENE_TITLE_H__
