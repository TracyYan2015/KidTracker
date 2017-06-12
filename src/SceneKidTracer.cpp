#include "SceneKidTracer.h"

USING_NS_CC;

enum kTag
{
	kTagCanvas = 100,
};

Scene* SceneKidTracer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneKidTracer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneKidTracer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SceneKidTracer::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(posV.x + Director::getInstance()->getVisibleSize().width - closeItem->getContentSize().width/2 ,
                                posV.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Fllow Draw Mode", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(posV.x + Director::getInstance()->getVisibleSize().width/2,
                            posV.y + Director::getInstance()->getVisibleSize().height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	/*
    // add "SceneKidTracer" splash screen"
    auto sp = Sprite::create("tracer.png");
	sp->setScale(0.5f);
    // position the sprite on the center of the screen
    sp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sp, 0);
    */


	auto sp = Sprite::create("bg.png");
	sp->setScale(1.0f);
	sp->setAnchorPoint(Vec2::ZERO);
	sp->setPosition(posV + Vec2(0.0f, 0.0f));
	this->addChild(sp, 0);


	Node* canvas = Node::create();
	canvas->setTag(kTagCanvas);
	canvas->setAnchorPoint(Vec2::ZERO);
	canvas->setPosition( Vec2(118.0f, 150.0f) );
	this->addChild(canvas, 0);

    return true;
}


void SceneKidTracer::menuCloseCallback(Ref* pSender)
{

	Node* canvas = this->getChildByTag(kTagCanvas);

	std::vector<Vec2> points= {
		Vec2(498, 463),
		Vec2(503, 461),
		Vec2(508, 460),
		Vec2(513, 459),
		Vec2(518, 458),
		Vec2(523, 458),
		Vec2(528, 458),
		Vec2(533, 459),
		Vec2(538, 460),
		Vec2(543, 461),
		Vec2(548, 463),
		Vec2(553, 466),
		Vec2(558, 468),
		Vec2(563, 472),
		Vec2(568, 476),
		Vec2(573, 481),
		Vec2(578, 487),
		Vec2(583, 496),
		Vec2(585, 501),
		Vec2(587, 506),
		Vec2(588, 511),
		Vec2(589, 516),
		Vec2(589, 521),
		Vec2(590, 526),
		Vec2(590, 531),
		Vec2(589, 536),
		Vec2(588, 541),
		Vec2(587, 546),
		Vec2(585, 551),
		Vec2(583, 556),
		Vec2(580, 561),
		Vec2(577, 566),
		Vec2(573, 571),
		Vec2(568, 575),
		Vec2(563, 580),
		Vec2(558, 583),
		Vec2(553, 586),
		Vec2(548, 588),
		Vec2(543, 590),
		Vec2(538, 591),
		Vec2(533, 592),
		Vec2(528, 593),
		Vec2(523, 593),
		Vec2(518, 593),
		Vec2(513, 593),
		Vec2(508, 592),
		Vec2(503, 591),
		Vec2(498, 589),
		Vec2(493, 586),
		Vec2(488, 584),
		Vec2(483, 580),
		Vec2(478, 576),
		Vec2(473, 571),
		Vec2(468, 566),
		Vec2(465, 561),
		Vec2(462, 556),
		Vec2(460, 551),
		Vec2(458, 546),
		Vec2(456, 541),
		Vec2(456, 536),
		Vec2(455, 531),
		Vec2(455, 526),
		Vec2(455, 516),
		Vec2(456, 511)
	};

	Sprite* sp = Sprite::create("tracer.png");
	sp->setScale(0.5f);
	sp->setPosition(points[0]);
	canvas->addChild(sp);

	playActionPointPath(sp, points, 0);

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

void SceneKidTracer::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
{

	Vec2 posStart = node->getPosition();
	Vec2 posEnd = points[index];
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
