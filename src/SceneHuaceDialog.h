#ifndef __SCENE_HUACE_DIALOG_H__
#define __SCENE_HUACE_DIALOG_H__


#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"


using namespace cocos2d;
using namespace ui;
using namespace std;

class MyDate
{
private:
    int* date = new int[12];
    Vector<Sprite*> sDate;
    void turnNum2Sprite(int num);
    
public:
    void setDate(int* date);
    void add2SDate();//将数字一个个添加到Vector<Sprite*> sDate
    int* getDate();
    void display();
};


class SceneHuaceDialog : public cocos2d::Layer
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
    CREATE_FUNC(SceneHuaceDialog);
    
    
	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);
    
	virtual void onClickUi(Ref* sender, TouchEventType type);
        
	void uiRegButton(Widget* parent, const std::string& name, int k, int z);
    
    //void uiRegButtonInScrollView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    
     Layout *ui;
    Layout *ui_big;
    
    void layout();
    
    bool isDelete;
    void deleteItemFromHace(int idx);
    //void onExit();
    
private:
    enum selected_huace_idx
    {
        huace1 = 1,
        huace2,
        huace3,
        
        
        
    };
    
    int selected_huace_id = -1;
    
    
    EventListenerTouchOneByOne* listener;
    bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    void onTouchMoved(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    void onTouchEnded(cocos2d::Touch * touch,cocos2d::Event * pEvent);
    
    
    CCRect getBoundingBox_worldspace(Sprite*);
    
    cocos2d::ui::ScrollView* huaces;
    
    //Vector<> dates;
    
    
    int innerContainerY;
    
    //Vector<Sprite*>  xxdbs;
    Vector<ImageView*> xxdbs;
    
    Vector<Sprite*>  images;
    Vector<Sprite*>  deleteBtns;
    
    
    
    void refreshXXQ();//重新加载信息区
    
    void showVector_Sprite(Vector<Sprite*>);
    
    void loadDate_Time();//显示日期和时间
    void myDateLayout(Vector<Sprite*> myDate, int idx_xxdb);
    
    void myTimeLayout(Vector<Sprite*> myTime, int idx_xxdb);
    
    void loadVectorsFromPlist();//先clear三个vectors，然后从plist中加载图片文件
    
    static std::vector<std::string> HUACE_PLIST_PATHS;
};



#endif // __SCENE_TITLE_H__
