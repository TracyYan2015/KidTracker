#include "SceneModeGuid.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "SimpleAudioEngine.h"
#include "Util.h"
#include "SceneController.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;







enum kTag
{
	kTagCanvas = 100,
};


SceneModeGuid::SceneModeGuid()
: _pictureData(nullptr)
, _ui(nullptr)
, _guider(nullptr)
, _strokeIndex(0)
, _nextStrokeIndex(0)
{

	_pictureData = new PictureData();
}

SceneModeGuid::~SceneModeGuid()
{
	CC_SAFE_DELETE(_pictureData);
}


Scene* SceneModeGuid::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneModeGuid::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneModeGuid::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	// 开启触摸事件
	//this->setTouchEnabled(true);
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

    CCSize sizeV = Director::getInstance()->getVisibleSize();
    Vec2 posV = Director::getInstance()->getVisibleOrigin();

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

	


	_pictureData->loadStrokeData();

	//_pictureData;

	init_ui();

	Widget* canvas = _ui->getChildByName("pn_canvas");
	Vec2 pos = canvas->getPosition();
	CCSize size = canvas->getContentSize();

	Widget* img_canvas = _ui->getChildByName("img_canvas");
	img_canvas->setVisible(true);

	ArmatureDataManager::getInstance()->addArmatureFileInfo("an/role/elf_001/elf_001.ExportJson");
	Armature* arma = Armature::create("elf_001");
	arma->setScale(0.5f);
	arma->setPosition(Vec2::ZERO);
	canvas->addChild(arma);

	_guider = arma;


    return true;
}


bool SceneModeGuid::init_ui()
{


	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();

	Layout* ui = nullptr;
	{

		// ly_root -> getName("pn_start")
		ui = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui/SceneModeGuid/KidTracerModeGuid.ExportJson"));
		ui->setTouchEnabled(true);
		ui->setEnabled(true);
		ui->setAnchorPoint(Vec2(0.0f, 0.0f));

		float gx = vOrigin.x - (ui->getContentSize().width - vSize.width) / 2;
		float gy = vOrigin.y - (ui->getContentSize().height - vSize.height) / 2;
		ui->setPosition(Vec2(gx, gy));


		uiRegButton(ui, "btn_home", kTagBtnGuidHome, zTagDefault);
		//uiRegButton(ui, "btn_save", kTagBtnGuidSave, zTagDefault);
		uiRegButton(ui, "btn_restart", kTagBtnGuidRestart, zTagDefault);
		uiRegButton(ui, "btn_play_pre", kTagBtnGuidPlayPre, zTagDefault);
		uiRegButton(ui, "btn_play_next", kTagBtnGuidPlayNext, zTagDefault);

		onClickUi(nullptr, TouchEventType::TOUCH_EVENT_CANCELED);

		/*
		{
			Widget* wg = ui->getChildByName("tf_input");
			Util::replaceTextFieldToEditBox(wg, kTagEditBoxInputSearchKey, this);
		}
		*/
	}
	_ui = ui;
	this->addChild(ui, zTagBtnRefresh - 100);


	return true;
}




void SceneModeGuid::playActionPointPath(Node* node, const std::vector<Vec2>& points, int index)
{

	node->stopActionByTag(1);

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
			onPointPathEnd(node);
		}

	});
	auto seq = Sequence::create(act_m, act_cb, nullptr);
	seq->setTag(1);

	node->runAction(seq);
}


void SceneModeGuid::playActionPointWait(Node* node, float delay)
{
	node->stopActionByTag(1);

	auto act_d = DelayTime::create(delay);
	auto act_cb = CallFunc::create([=]{

		onPointPathEnd(node);

	});
	auto seq = Sequence::create(act_d, act_cb, nullptr);
	seq->setTag(1);

	node->runAction(seq);
}


void SceneModeGuid::onPointPathEnd(Node* node)
{
	node->setVisible(false);


	_strokeIndex = _nextStrokeIndex;
	
}

bool SceneModeGuid::playStroke(int strokeIndex)
{
	Armature* guider = _guider;
	int n = _pictureData->strokes.size();
	if (strokeIndex >= 0 && strokeIndex < n)
	{
		_nextStrokeIndex = strokeIndex;
		auto points = _pictureData->strokes[strokeIndex]->pos;
		bool isWait = _pictureData->strokes[strokeIndex]->isWait;

		Vec2 posReady = points[0];
		guider->setPosition(posReady);

		guider->setVisible(true);
		
		// guider->getAnimation()->play((isWait) ? "wait" : "move");
		if (isWait)
		{
			guider->getAnimation()->play("wait");
			playActionPointWait(guider, 3.0f);
		}
		else
		{
			guider->getAnimation()->play("move");
			playActionPointPath(guider, points, 0);
		}
		

		

		return true;
	}

	return false;
}


void SceneModeGuid::onClickUi(Ref* sender, TouchEventType type)
{
	int id = -1;
	Button* btn = dynamic_cast<Button*>(sender);
	if (btn != nullptr)
	{
		id = btn->getTag();
	}

	if (type != TOUCH_EVENT_ENDED)
		return;

	CCLOG("onClick!!! id=%d", id);

	


	if (id == kTagBtnGuidHome)
	{
		int scene_id = eSceneIdSceneTitle;
		SceneController::getInstance()->replaceScane(scene_id);
	}
	else if (id == kTagBtnGuidRestart)
	{

	}
	else if (id == kTagBtnGuidPlayPre)
	{
		playStroke(1);
	}
	else if (id == kTagBtnGuidPlayNext)
	{
		playStroke(_strokeIndex + 1);
	}

}

void SceneModeGuid::uiRegButton(Widget* parent, const std::string& name, int k, int z)
{
	Button* btn = (Button*)parent->getChildByName(name);
	if (btn)
	{
		btn->setTag(k);
		btn->addTouchEventListener(this, toucheventselector(SceneModeGuid::onClickUi));
		btn->setZOrder(z);
		//parent->addChild(btn, z);
	}

}




bool SceneModeGuid::onTouchBegan(Touch * touch, Event * pEvent)
{
	int a = 0;

	CCLOG("stroke#00");

	return true;
}

void SceneModeGuid::onTouchMoved(Touch * touch, Event * pEvent)
{
	int a = 0;

	Vec2 posW = touch->getLocation();
	// CCLOG("%d,%d", (int)posW.x, (int)posW.y);

	Widget* img_canvas = _ui->getChildByName("img_canvas");
	if (img_canvas)
	{
		Vec2 posN = img_canvas->convertToNodeSpace(posW);

		CCLOG("%d,%d", (int)posN.x, (int)posN.y);
	}


}

void SceneModeGuid::onTouchEnded(Touch * touch, Event * pEvent)
{
	int a = 0;


}

void SceneModeGuid::registerTouchEvent(Node* node)
{
	//node->setTouchEnabled(true);
	node->setVisible(true);
	node->setZOrder(100);
	// 注册事件
	{

		auto ed = node->getEventDispatcher();
		ed->setEnabled(true);
		auto el = EventListenerTouchOneByOne::create();
		el->setSwallowTouches(true);

		el->onTouchBegan = [&](Touch* pTouch, Event* pEvent)->bool{
			CCLOG("stroke#00");
			return true;
		};
		el->onTouchMoved = [&](Touch* pTouch, Event* pEvent)->void{
			Vec2 pos = pTouch->getLocation();
			CCLOG("%d,%d", (int)pos.x, (int)pos.y);
		};

		ed->addEventListenerWithSceneGraphPriority(el, node);
	}
}
