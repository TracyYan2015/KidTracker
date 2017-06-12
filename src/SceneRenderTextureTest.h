#ifndef __SCENE_RENDER_TEXTURE_TEST_H__
#define __SCENE_RENDER_TEXTURE_TEST_H__

#include "KTGlobalDef.h"
//#include "SuperAnimNodeV2.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "ArmatureTest.h"

//using namespace SuperAnim;
using namespace cocos2d;
using namespace cocostudio;


//grobal constants declaration
extern const std::string LAOSHU_PATH;
extern const std::string XIAOTU_PATH;
extern const std::string HB_PATH;
extern const std::string CS_PATH;
extern const int JBH_SET_NUMBER;
extern std::vector<std::string> DATU_PATHS;
extern std::vector<std::string> MH_DATU_PATH;
extern const std::string LAOSHU_PLIST_PATH;
extern int modeSoundTmp;

class SceneRenderTextureTest : public cocos2d::Layer
{
    //SuperAnimNode* mAnimNode[3];
public:
    Vec2 startP;
    cocostudio::Armature* arma;
    int volumFlag;
	SceneRenderTextureTest()
    : _rt(nullptr)
    , _brush(nullptr)
	{
        
	}
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SceneRenderTextureTest);
    
    
	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);
    
	Sprite* getBrush();
    
	void drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd);
    
	// ²¥·ÅÑÓ³Ù¶¯»­
	void playActionDelay(float delay, const std::function<void()> &func);
    
    virtual bool onTouchBegan(Touch * touch, Event * pEvent) override;
	virtual void onTouchMoved(Touch * touch, Event * pEvent) override;
    
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);
    
    
    virtual void update(float delta);
    //std::string* reloadPlists;
    //void plistImageAsyncCallback(cocos2d::Texture2D* texture);
    //int curReloadPlistNum;
    
    
    void onFrameEvent( CCZone * bone , const char * evt, int originFrameIndex, int currentFrameIndex );
    
	CCSize _canvasSize;
	RenderTexture* _rt;
	Sprite* _brush;
	Vector<Sprite*> _brushs;
	//std::vector<Sprite*> _brushs;
    
    
    Armature* logo;
    Armature* shaLou;
    
    
private:
    void addLaoshuPVR();
   
    
};

#endif // __SCENE_RENDER_TEXTURE_TEST_H__
