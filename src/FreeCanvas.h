//
//  FreeCanvas.h
//  KidTracer
//
//  Created by Bian Wu on 13/8/14.
//
//

#ifndef __KidTracer__FreeCanvas__
#define __KidTracer__FreeCanvas__

#include "cocos2d.h"

using namespace cocos2d;

class FreeCanvas : public Node
{
    
public:
    
	FreeCanvas();
    
	virtual ~FreeCanvas();
    
	CREATE_FUNC(FreeCanvas);
    
	virtual bool init() override;
    
	void onTouchMoved(Touch * touch, Event * pEvent);
    
	// ÃÊªª∂‘”¶µƒΩ⁄µ„
	void replaceNode(Node* node);
    
	void drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd);
    
    int penNo;
    int penXD;
    Sprite* brush1;
    
    void clear();
    void addDj();
    
protected:
    
    
	CCSize _canvasSize;
	RenderTexture* _rt;
	Sprite* _brush;
	Vector<Sprite*> _brushs;
};

#endif /* defined(__KidTracer__FreeCanvas__) */
