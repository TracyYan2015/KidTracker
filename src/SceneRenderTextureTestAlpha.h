#ifndef __SCENE_RENDER_TEXTURE_TEST_ALPHA_H__
#define __SCENE_RENDER_TEXTURE_TEST_ALPHA_H__

#include "KTGlobalDef.h"

#include "cocos2d.h"

using namespace cocos2d;


class SceneRenderTextureTestAlpha : public cocos2d::Layer
{
public:

	SceneRenderTextureTestAlpha()
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
    CREATE_FUNC(SceneRenderTextureTestAlpha);


	void playActionPointPath(Node* node, const std::vector<Vec2>& points, int index);

	Sprite* getBrush();

	void drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd);

	// ²¥·ÅÑÓ³Ù¶¯»­
	void playActionDelay(float delay, const std::function<void()> &func);

	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);

	CCSize _canvasSize;
	RenderTexture* _rt;
	Sprite* _brush;
	Vector<Sprite*> _brushs;
	//std::vector<Sprite*> _brushs;
};

#endif // __SCENE_RENDER_TEXTURE_TEST_ALPHA_H__