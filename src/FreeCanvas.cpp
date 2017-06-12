//
//  FreeCanvas.cpp
//  KidTracer
//
//  Created by Bian Wu on 13/8/14.
//
//

#include "FreeCanvas.h"


FreeCanvas::FreeCanvas()
: _rt(nullptr)
, _brush(nullptr)
{
    
}

FreeCanvas::~FreeCanvas()
{
    
}


void FreeCanvas::replaceNode(Node* node)
{
 	if (node)
	{
        Node* parent = node->getParent();
        if (this->getParent())
		{
			this->removeFromParent();
		}
        
		this->setContentSize(node->getContentSize());
		this->setAnchorPoint(node->getAnchorPoint());
		this->setPosition(node->getPosition() );
        
		parent->addChild(this, node->getLocalZOrder());
		node->removeFromParentAndCleanup(true);
	}
}


void FreeCanvas::drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd)
{
	float distance = posStart.distance(posEnd);
	float difx = posEnd.x - posStart.x;
	float dify = posEnd.y - posStart.y;
	_brushs.clear();
	for (int i = 0; i < distance; i++)
	{
		CCSprite* brush = CCSprite::createWithSpriteFrameName(String::createWithFormat("zyms_xx_%d.png",penNo)->getCString());
        float bf = penXD/10.0f/6.0f;
        brush->setScale(bf, bf);
		brush->retain();
		_brushs.pushBack(brush);
        brush->release();
	}
    
	canvas->begin();//绘制开始
	for (int i = 0; i < distance; i++)
	{
		float delta = (float)i / distance;
		Vec2 pos = ccp(posStart.x + (difx * delta), posStart.y + (dify * delta));
		Sprite* br = _brushs.at(i);//创建笔刷精灵
		br->setPosition(pos);
		br->visit();//绘制笔刷精灵
	}
	canvas->end();//绘制结束
    
}

bool FreeCanvas::init()
{
    
	Node::init();
    
    penNo = 1;
    penXD = 10;
    CCSpriteBatchNode *spriteBatch=CCSpriteBatchNode::create("data/freecanvas/color1.png");
    this->addChild(spriteBatch);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("data/freecanvas/color1.plist");

    
	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
    
	
	Sprite* brush_bg = Sprite::create("data/canvas/ydms_wq_8.png");
	brush_bg->retain();
	float w = brush_bg->getContentSize().width;
	float h = brush_bg->getContentSize().height;
	_canvasSize = CCSize(w, h);
    
	// ¥¥Ω®∂ØÃ¨≤ƒ÷
	RenderTexture* canvas = RenderTexture::create(_canvasSize.width, _canvasSize.height, Texture2D::PixelFormat::RGBA8888);
	canvas->retain();
	//canvas->setContentSize(Size(w, h));
	Vec2 posFix = Vec2(_canvasSize.width/2, _canvasSize.height/2);
	canvas->setAnchorPoint(Vec2::ZERO); // Point(0.5f, 0.5f)
	canvas->setPosition(Vec2::ZERO + posFix);
    
	//rt->setPosition(Point(100.0f, 100.0f));
	this->addChild(canvas, 0);
    
	canvas->clear(1.0f, 1.0f, 1.0f, 0.0f);
    
	_rt = canvas;
	
    
    //12-15
    canvas->release();
    brush_bg->release();
    
    
	return true;
}

void FreeCanvas::onTouchMoved(Touch * touch, Event * pEvent)
{
	auto start = touch->getPreviousLocation();
	auto end = touch->getLocation();
	start = _rt->convertToNodeSpace(start) + _canvasSize / 2;
	end = _rt->convertToNodeSpace(end) + _canvasSize / 2;
    drawLine(_rt, _brush, start, end);
}

void FreeCanvas::clear()
{
    _rt->clear(1.0f, 1.0f, 1.0f, 0.0f);
}

void FreeCanvas::addDj()
{
    Sprite* brush_bg1 = Sprite::create("data/canvas/ydms_wq_8.png");
    
    CCSpriteBatchNode *spriteBatch=CCSpriteBatchNode::create("data/freecanvas/penxd.png");
    this->addChild(spriteBatch);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("data/freecanvas/penxd.plist");
	// center (¥¥Ω®ª≠≤ºµƒ≤£¡ß∞Â)
	Sprite* brush_bg = Sprite::createWithSpriteFrameName("zyms_dj_big_001.png");
	brush_bg->retain();
	float w = brush_bg1->getContentSize().width;
	float h = brush_bg1->getContentSize().height;
	_canvasSize = CCSize(w, h);
    
	// ¥¥Ω®∂ØÃ¨≤ƒ÷
	RenderTexture* canvas = RenderTexture::create(_canvasSize.width, _canvasSize.height, Texture2D::PixelFormat::RGBA8888);
	canvas->retain();
	Vec2 posFix = Vec2(_canvasSize.width/2, _canvasSize.height/2);
	canvas->setAnchorPoint(Vec2::ZERO); // Point(0.5f, 0.5f)
	canvas->setPosition(Vec2::ZERO + posFix);
    
	this->addChild(canvas, 0);
    
	// «Âø’ª≠≤º
	canvas->clear(1.0f, 1.0f, 1.0f, 0.0f);
    
	{
		canvas->begin();
		brush_bg->setPosition(Vec2(brush_bg->getContentSize().width / 2, brush_bg->getContentSize().height / 2));
		brush_bg->visit();
		canvas->end();
	}
    
    
    
	_rt = canvas;
    
    //12-15
    brush_bg->release();
    canvas->release();
    
    
}



