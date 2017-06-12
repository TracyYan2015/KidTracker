#include "SceneTemplate.h"

USING_NS_CC;

enum kTag
{
	kTagCanvas = 100,
};

Scene* SceneTemplate::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneTemplate::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneTemplate::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CCSize sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SceneTemplate::menuCloseCallback, this));
    
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
    
    auto label = LabelTTF::create("SceneTemplate", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(posV.x + sizeV.width/2,
                            posV.y + sizeV.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	
    // add "SceneTemplate" splash screen"
    auto sp = Sprite::create("tracer.png");
	sp->setScale(0.5f);
    // position the sprite on the center of the screen
    sp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sp, 0);
    


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
     */
    
    

    return true;
}

/*
void SceneTemplate::menuCloseCallback(Ref* pSender)
{


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
 */

 





void SceneTemplate::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
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
