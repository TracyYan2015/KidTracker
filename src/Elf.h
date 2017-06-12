#ifndef __ELF_H__
#define __ELF_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "PictureData.h"

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;


enum eElfMotion
{
	Idle = 0,
	Move,
	Wait,
	Jump,
};

class Elf
{
public:
	Elf()
		: arma(nullptr)
		, _isTouchDown(false)
		, _posWTouchDown(Vec2::ZERO)
		, _isMoving(false)
		, _picData(nullptr)
		, _strokeIndex(0)
		, _strokePointIndex(0)
	{

	}
	void init(Armature* arma,CCSize v);
	void setState(eElfMotion state);
	void setPictureData(PictureData* picData);
	Vec2 getTracePosition(bool& isStand_out);
	void setTouchDown(bool isDown, const Vec2& posW);
	bool checkToMove(const Vec2& posWorld);
	void update(float dt);
	eElfMotion state;
	Armature* arma;
    int elfId;
    void setElfId(int elfId);
    int getElfId();
    const float check_raduis = 20.0f;
    Vec2 getRandomPosition(Node* node);
protected:
	int checkPointInCircle(const Vec2& posWorld);

	PictureData* _picData;

	bool _isTouchDown;

	Vec2 _posWTouchDown;

	bool _isMoving;

	int _strokeIndex;

	int _strokePointIndex;

private:

};


#endif // __ELF_H__