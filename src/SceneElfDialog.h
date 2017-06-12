#ifndef __SCENE_ELF_DIALOG_H__
#define __SCENE_ELF_DIALOG_H__


#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneTitle.h"


using namespace cocos2d;
using namespace ui;

class SceneElfDialog : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	bool init_ui();
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneElfDialog);
    
    
	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);
    
	virtual void onClickUi(Ref* sender, TouchEventType type);
    
    virtual void onClickUi_ImageView(Ref* sender, TouchEventType type);
    
	void uiRegButton(Widget* parent, const std::string& name, int k, int z);
    
    //void uiRegButtonInListView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    void elfs_layout();
    
    SceneTitle* sceneTitle;
    
    void initBlueRing_Word();//用这个方法来使一进入精灵图鉴就初始化bluering&word
    
    void testFunc();
    
    bool isDirectEntered;//如果是从主界面直接进入此对话框则置为true
    
    
    void make_a_change();//改变标题图片 增加下一步按钮等
    
    int elfsSize;
    
    bool* isJLGouMai;
    
    
    //int selected_elf_id;// 1~3
    //int selected_id_vector;//the selected idx of vector 0~2
    
    
    int elfId;
    int elfIdVector;
  
    
    
    //10.14定义新接口，用于从sceneTitle中传入elfDialog中数据的处理（本地化）
    //防止新增精灵时id_vector的改变
    void initData(int id, int id_vector, int boughtId);
    //10.14新增方法，统一管理选择精灵事件处理
    void elfChangedCallback(int id, int idVector, ImageView* btn);
    void updateUserData(int id, int idVector);
    
    //void onExit();
    
private:
    enum selected_elf_idx
{
    elf1 = 1,
    elf2,
    elf3,
    
    
};
    
    
    ImageView* lastSelectedImageView;
    Layout *ui;
    SpriteFrameCache *cache;
    Vector<Sprite*> dibans;
    Vector<ImageView*> elfs;
    Vector<Sprite*> generalDibans;
    Vector<ImageView*> generalElfs;
    Sprite* diban_elf1;
    Sprite* diban_elf2;
    Sprite* diban_elf3;
    Sprite* diban_elf4;
    Sprite* diban_elf5;
    Sprite* diban_elf6;
    
    ImageView* _elf1;
    ImageView* _elf2;
    ImageView* _elf3;
    ImageView* _elf4;
    ImageView* _elf5;
    ImageView* _elf6;
    
    
    
    Sprite* _jiahao;
    
    ImageView* next;
    void nextFunc();
    
    
    static std::vector<std::string> ELF_PLIST_PATHS;
    
    
    void initElfs();
    Vector<__String*> elfsHBFileNames;
    
    
};

#endif // __SCENE_TITLE_H__
