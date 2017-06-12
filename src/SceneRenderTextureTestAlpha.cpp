#include "SceneRenderTextureTestAlpha.h"

USING_NS_CC;

enum kTag
{
	kTagCanvas = 100,
};

Scene* SceneRenderTextureTestAlpha::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneRenderTextureTestAlpha::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneRenderTextureTestAlpha::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SceneRenderTextureTestAlpha::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(posV.x + sizeV.width - closeItem->getContentSize().width/2 ,
                                posV.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("SceneRenderTextureTestAlpha", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(posV.x + sizeV.width/2,
                            posV.y + sizeV.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	/*
    // add "SceneRenderTextureTestAlpha" splash screen"
    auto sp = Sprite::create("tracer.png");
	sp->setScale(0.5f);
    // position the sprite on the center of the screen
    sp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sp, 0);
    */

	/*
	auto sp = Sprite::create("bg.png");
	sp->setScale(1.0f);
	sp->setAnchorPoint(Point::ZERO);
	sp->setPosition(posV + Point(0.0f, 0.0f));
	this->addChild(sp, 0);


	Node* canvas = Node::create();
	canvas->setTag(kTagCanvas);
	canvas->setAnchorPoint(Point::ZERO);
	canvas->setPosition( Point(118.0f, 150.0f) );
	this->addChild(canvas, 0);
	*/

	// center
	Sprite* bg = Sprite::create("data/canvas/bg.png");
	bg->setAnchorPoint(Point::ZERO);
	float x = (sizeV.width - bg->getContentSize().width) /2;
	float y = (sizeV.height - bg->getContentSize().height) / 2;
	bg->setPosition(Point(x, y));
	this->addChild(bg);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(SceneRenderTextureTestAlpha::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	// center
	Sprite* brush_bg = Sprite::create("data/canvas/ydms_wq_8.png");
	brush_bg->retain();
	float w = brush_bg->getContentSize().width;
	float h = brush_bg->getContentSize().height;
	_canvasSize = Size(w, h);


	Sprite* brush = Sprite::create("data/canvas/brush3.png");
	brush->retain();
	//brush->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
	//brush->setBlendFunc(BlendFunc::ADDITIVE);


	Size vSize = CCDirector::getInstance()->getOpenGLView()->getVisibleSize();
	RenderTexture* canvas = RenderTexture::create(_canvasSize.width, _canvasSize.height, Texture2D::PixelFormat::RGBA8888);
	canvas->retain();
	//rt->setContentSize(Size(w, h));
	canvas->setAnchorPoint(Point(0.5f, 0.5f));
	canvas->setPosition(Point(vSize.width / 2, vSize.height / 2) + Point(-6.0f, 73.0f));
	//rt->setPosition(Point(100.0f, 100.0f));
	this->addChild(canvas, 0);

	//rt->setClearColor(Color4F(0.0f, 1.0f, 1.0f, 0.0f));
	//canvas->clear(0.0f, 0.3f, 0.0f, 1.0f);
	canvas->clear(1.0f, 1.0f, 1.0f, 0.0f);

	{

		canvas->begin();
		brush_bg->setPosition(Point(brush_bg->getContentSize().width / 2, brush_bg->getContentSize().height / 2));
		brush_bg->visit();
		canvas->end();
	}

	
// 	// begin drawing to the render texture
// 	rt->begin();
// 
// 	kmGLPushMatrix();
// 	kmGLLoadMatrix(&_modelViewTransform);
// 
// 	glLineWidth(5.0f);
// 	DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
// 	DrawPrimitives::drawLine(Point(50.0f, 50.0f), Point(200.0f, 50.0f));
// 
// 	kmGLPopMatrix();
// 
// 	// finish drawing and return context back to the screen
// 	rt->end();


	drawLine(canvas, brush, Point(50.0f, 50.0f), Point(150.0f, 50.0f));

	_brush = brush;
	_rt = canvas;


	this->playActionDelay(2.0f, [&]{

		drawLine(_rt, _brush, Point(150.0f, 50.0f), Point(150.0f, 100.0f));

	});

// 	glLineWidth(5.0f);
// 	DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
// 	DrawPrimitives::drawLine(Point(50.0f, 50.0f), Point(200.0f, 50.0f));

    return true;
}


void SceneRenderTextureTestAlpha::menuCloseCallback(Ref* pSender)
{


	exit(0);

	/*

// 	std::vector<Point> points = {
// 		Point(1, 1),
// 		Point(10, 10),
// 		Point(20, 20),
// 		Point(30, 40),
// 		Point(30, 50),
// 		Point(30, 60)
// 	};


	Node* canvas = this->getChildByTag(kTagCanvas);

	std::vector<Point> points = {
		Point(498, 463),
		Point(503, 461),
		Point(508, 460),
		Point(513, 459),
		Point(518, 458),
		Point(523, 458),
		Point(528, 458),
		Point(533, 459),
		Point(538, 460),
		Point(543, 461),
		Point(548, 463),
		Point(553, 466),
		Point(558, 468),
		Point(563, 472),
		Point(568, 476),
		Point(573, 481),
		Point(578, 487),
		Point(583, 496),
		Point(585, 501),
		Point(587, 506),
		Point(588, 511),
		Point(589, 516),
		Point(589, 521),
		Point(590, 526),
		Point(590, 531),
		Point(589, 536),
		Point(588, 541),
		Point(587, 546),
		Point(585, 551),
		Point(583, 556),
		Point(580, 561),
		Point(577, 566),
		Point(573, 571),
		Point(568, 575),
		Point(563, 580),
		Point(558, 583),
		Point(553, 586),
		Point(548, 588),
		Point(543, 590),
		Point(538, 591),
		Point(533, 592),
		Point(528, 593),
		Point(523, 593),
		Point(518, 593),
		Point(513, 593),
		Point(508, 592),
		Point(503, 591),
		Point(498, 589),
		Point(493, 586),
		Point(488, 584),
		Point(483, 580),
		Point(478, 576),
		Point(473, 571),
		Point(468, 566),
		Point(465, 561),
		Point(462, 556),
		Point(460, 551),
		Point(458, 546),
		Point(456, 541),
		Point(456, 536),
		Point(455, 531),
		Point(455, 526),
		Point(455, 516),
		Point(456, 511)
	};

	Sprite* sp = Sprite::create("tracer.png");
	sp->setScale(0.5f);
	sp->setPosition(points[0]);
	canvas->addChild(sp);

	playActionPointPath(sp, points, 0);

	*/

	return;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void SceneRenderTextureTestAlpha::playActionPointPath(Node* node, const std::vector<Point>& points, int index)
{

	Point posStart = node->getPosition();
	Point posEnd = points[index];
	float dis = posStart.distance(posEnd);
	float v = 100 / 1.0f;
	float t = dis / v;

	auto act_m = MoveTo::create(t, points[index]);
	auto act_cb = CallFunc::create([=]{

		int nextIndex = (index + 1);
		if (nextIndex < points.size())
			playActionPointPath(node, points, nextIndex);
		else
		{
			// end
		}

	});
	auto seq = Sequence::create(act_m, act_cb, nullptr);

	node->runAction(seq);
}

void SceneRenderTextureTestAlpha::drawLine(RenderTexture* canvas, Sprite* brush, Point posStart, Point posEnd)
{
	float distance = posStart.distance(posEnd);
	float difx = posEnd.x - posStart.x;
	float dify = posEnd.y - posStart.y;

	_brushs.clear();

	for (int i = 0; i < distance; i++)
	{
		//Sprite* br = Sprite::create("brush1.png");

// 		Sprite* brush = Sprite::create("data/canvas/brush4.png");
// 		brush->retain();
// 
// 		BlendFunc bf;
// 		bf.dst = GL_SRC_ALPHA;
// 		bf.src = GL_ONE_MINUS_SRC_ALPHA;
// 		brush->setBlendFunc(bf);

		// -----------------------------------
// 		Sprite* brush = Sprite::create("data/canvas/brush5.png");
// 		brush->retain();
// 
// 		BlendFunc bf;
// 		bf.dst = GL_SRC_ALPHA;
// 		bf.src = GL_ONE_MINUS_SRC_ALPHA;
// 		brush->setBlendFunc(bf);

		// Sprite* brush = Sprite::create("data/canvas/brush5.png");
		Sprite* brush = Sprite::create("data/canvas/brush7.png");
		brush->retain();

		BlendFunc bf;
		bf.dst = GL_SRC_ALPHA; //GL_SRC_ALPHA;
		//bf.src = GL_SRC_ALPHA; //GL_ONE_MINUS_SRC_ALPHA;
		bf.src = GL_ONE_MINUS_SRC_ALPHA;
		brush->setBlendFunc(bf);


// 		BlendFunc bf;
// 		bf.dst = GL_ZERO;
// 		//bf.src = GL_ALPHA;
// 		bf.src = GL_ZERO;
// 		brush->setBlendFunc(bf);


// 		BlendFunc bf;
// 		bf.dst = GL_ZERO;
// 		bf.src = GL_DST_ALPHA;
// 		brush->setBlendFunc(bf);



		//brush->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
		//brush->setBlendFunc(BlendFunc::ADDITIVE);

		_brushs.pushBack(brush);
	}
	
	canvas->begin();
	for (int i = 0; i < distance; i++)//
	{
		float delta = (float)i / distance;
		Point pos = ccp(posStart.x + (difx * delta), posStart.y + (dify * delta));
		// CCLOG("[%d] - (%d,%d)", i, (int)pos.x, (int)pos.y );

		Sprite* br = _brushs.at(i);
		br->setPosition(pos);
		br->visit();
	}
	canvas->end();

}

Sprite* SceneRenderTextureTestAlpha::getBrush()
{
	Sprite* brush = Sprite::create("brush1.png");


	return brush;
}

void SceneRenderTextureTestAlpha::playActionDelay(float delay, const std::function<void()> &func)
{
	auto a_dt = DelayTime::create(delay);
	auto a_cb = CallFunc::create(func);
	auto a_seq = Sequence::create(a_dt, a_cb, nullptr);
	this->runAction(a_seq);
}

void SceneRenderTextureTestAlpha::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	auto touch = touches[0];
	auto start = touch->getPreviousLocation(); 
	auto end = touch->getLocation();

// 	Point posAp = _rt->getAnchorPoint();
// 	Point posApInPix = Point(_rt->getContentSize().width * posAp.x, _rt->getContentSize().height * posAp.y);
// 	start = _rt->convertToNodeSpace(start) + posApInPix;
// 	end = _rt->convertToNodeSpace(end) + posApInPix;

	start = _rt->convertToNodeSpace(start) + _canvasSize / 2;
	end = _rt->convertToNodeSpace(end) + _canvasSize / 2;


	drawLine(_rt, _brush, start, end);
}
