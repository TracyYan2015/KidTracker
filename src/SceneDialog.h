#ifndef __SCENE_DIALOG_H__
#define __SCENE_DIALOG_H__


#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneTitle.h"

using namespace cocos2d;
using namespace ui;

class SceneDialog : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	bool init_ui();
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneDialog);
    
    
	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);
    
	virtual void onClickUi(Ref* sender, TouchEventType type);
    
    virtual void onClickUi_ImageView(Ref* sender, TouchEventType type);
    
	void uiRegButton(Widget* parent, const std::string& name, int k, int z);
    
    void uiRegButtonInListView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    void closeCallback1();
    
    
    void addScene2VectorWithSceneId(int id);
    void scenes_layout(Vector<Sprite*> dibans, Vector<ImageView*>  scenes);
    
    SceneTitle* sceneTitle;
    
    void initBlueRing_Word();//一进入场景图鉴，用这个方法进行初始化
    
    bool isDirectEntered;//如果是从主界面直接进入此对话框则置为true
    
    void make_a_change();
    
    
    
    
    

    
    //10.14新增口
    void initData(int id);
    int sceneId;
    int sceneVectorId;

    
    //not including the free
    int SCENES_NUMBER;
    
private:
    enum selected_scene_idx
    {
        scene1 = 1,
        scene2,
        scene3,
        
        
    };
    
    //3.7 according to the user bought status to decide which scene to show.
    void initScenes();

    
    Layout *ui;
    SpriteFrameCache *cache;
    Sprite* diban_scene1;
    Sprite* diban_scene2;
    Sprite* diban_scene3;
    Sprite* diban_scene4;
    Sprite* diban_scene5;
    Sprite* diban_scene6;
    Sprite* diban_scene7;
    Sprite* diban_scene8;
    Sprite* diban_scene9;
    Sprite* diban_scene10;
    Sprite* diban_scene11;
    Sprite* diban_scene12;
    Sprite* diban_scene13;
    Sprite* diban_scene14;
    Sprite* diban_scene15;
    Sprite* diban_scene16;
    
    ImageView* _scene1;
    ImageView* _scene2;
    ImageView* _scene3;
    ImageView* _scene4;
    ImageView* _scene5;
    ImageView* _scene6;
    ImageView* _scene7;
    ImageView* _scene8;
    ImageView* _scene9;
    ImageView* _scene10;
    ImageView* _scene11;
    ImageView* _scene12;
    ImageView* _scene13;
    ImageView* _scene14;
    ImageView* _scene15;
    ImageView* _scene16;
    
    
    
    Sprite* _jiahao;
    
    
    
    Vector<Sprite*> dibans;
    Vector<ImageView*> scenes;
    Vector<__String*> scenesHBFileNames;//keep the hb picture file name of every imageview of scenes. 
    
    
    //3.7 vectors hold all dibans and scenes no matter whether they are bought
    //including the 1st one
    Vector<Sprite*> generalDibans;
    Vector<ImageView*> generalScenes;
    
    
   
    
    void createScene(int sceneId);
    
    
    
    ImageView* back;   //上一步
    ImageView* start;   //开始
    void backFunc();
    void startFunc();
    
    //10.14added functions
    void sceneChangedCallback(int newId, ImageView* btn);
    void updateUserData(int sceneId,int sceneVectorId);
    
    static std::vector<std::string> SCENE_PlIST_PATHS;
    
    
};

#endif // __SCENE_TITLE_H__
