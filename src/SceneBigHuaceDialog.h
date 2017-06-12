#ifndef __SCENE_BIG_HUACE_DIALOG_H__
#define __SCENE_BIG_HUACE_DIALOG_H__


#include "KTGlobalDef.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "C2DXShareSDK.h"

using namespace cn::sharesdk;


using namespace cocos2d;
using namespace ui;

class SceneBigHuaceDialog : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	bool init_ui();
    
    
    //void onExit();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneBigHuaceDialog);
    
    
	//void playActionPointPath(Node* node, const std::vector<Point>& points, int index);
    
    
    virtual void onClickUi_ImageView(Ref* sender, TouchEventType type);
    
	void uiRegButton(Widget* parent, const std::string& name, int k, int z);
    
    //void uiRegButtonInListView(Widget* parent, const std::string& name, int z);
    
    void closeCallback();
    
    //void elfs_layout(Vector<Sprite*> elfs);
    
    
    void addBigPicByID(int idx);
    void addSprite(Sprite* sprite);
    Sprite* returnSprite();
    void setFileName(std::string filename);
    
    void getPictureFromScreenShot();
    
    
    
    
private:
    /*
    enum selected_elf_idx
    {
        elf1 = 1,
        elf2,
        elf3,
        
        
    };
     */
    
    //int selected_elf_id = -1;
    //ImageView* lastSelectedImageView;
    Layout *ui;
    SpriteFrameCache *cache;
    Sprite* added;
    std::string fileName;
    
    
    /*
    Vector<Sprite*> elfs;
    Sprite* diban_elf1;
    Sprite* diban_elf2;
    Sprite* diban_elf3;
    ImageView* _elf1;
    ImageView* _elf2;
    ImageView* _elf3;
    Sprite* _jiahao;
     */
    
};

#endif // __SCENE_TITLE_H__
