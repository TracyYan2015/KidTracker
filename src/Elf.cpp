#include "Elf.h"
#include "KTGlobalDef.h"
int randomnum=0;
CCSize sizeV;
Vec2 posStart1;

void Elf::init(Armature* arma,CCSize v)
{
	this->arma = arma;
    sizeV=v;
}


void Elf::setState(eElfMotion state)
{
	this->state = state;
    
    
	auto anim = arma->getAnimation();
	//std::string movName = anim->getCurrentMovementID();
    
	if (state == eElfMotion::Idle)
	{
		//if (movName != "idle")
        anim->play("idle");
	}
	else if (state == eElfMotion::Move)
	{
		//if (movName != "move")
        anim->play("move");
	}
	else if (state == eElfMotion::Wait)
	{
		//if (movName != "wait")
        anim->play("wait");
	}
	else if (state == eElfMotion::Jump)
	{
		//if (movName != "jump")
        anim->play("jump");
	}
    
}


void Elf::setPictureData(PictureData* picData)
{
	_picData = picData;

	bool isStand_out = false;
	Vec2 pos = getTracePosition(isStand_out);
	arma->setPosition(pos);
}


Vec2 Elf::getRandomPosition(Node* node)
{
	float r = 40.0f + CCRANDOM_0_1() * 40.0f; // r = [100 ~ 200]
	float rAngle = CCRANDOM_0_1() * 360.0f;
	float rTheta = CC_DEGREES_TO_RADIANS(rAngle);

	float xTo = r * cosf(rTheta);
	float yTo = r * sinf(rTheta);
	Vec2 posTo = arma->getPosition() + Vec2(xTo, yTo);

	return posTo;
}


Vec2 Elf::getTracePosition(bool& isStand_out)
{
    Vec2 pos1=posStart1;
	do
	{
		if (_picData == nullptr) break;

		if (_picData->strokes.size() <= 0) break;

		if (_strokeIndex >= _picData->strokes.size()) break;

		int pointSize = _picData->strokes[_strokeIndex]->pos.size();

		if (pointSize <= 0) break;

		isStand_out = (pointSize == 1) ? true : false;

		pos1 = _picData->strokes[_strokeIndex]->pos[_strokePointIndex];
        //上下翻转
        pos1=Vec2( pos1.x, sizeV.height - pos1.y);

	} while (false);

	return pos1;
}


void Elf::setTouchDown(bool isDown, const Vec2& posW)
{
	_isTouchDown = isDown;
	_posWTouchDown = posW;
}


int Elf::getElfId()
{
    return this->elfId;
}

void Elf::setElfId(int elfId)
{
    this->elfId = elfId;
}




bool Elf::checkToMove(const Vec2& posWorld)
{

    Vec2 posTo;
	do
	{
		if (_isMoving) break;
        
        int movenum=checkPointInCircle(posWorld);
        //1表示在圈内
        //0表示在圈外
		if (movenum==0)
		{
			if(state!=eElfMotion::Wait) setState(eElfMotion::Wait);
			break;
		}
        
        posStart1 = arma->getPosition();// grobal variable
		bool isStand_out = false;
        for(int i=0;i<movenum;i++)
        {
            posTo = getTracePosition(isStand_out);
        }
		if(state!=eElfMotion::Move) setState(eElfMotion::Move);
		Vec2 posEnd = posTo;
        
		float dis = posStart1.distance(posEnd);
		float v = 900.0f / 1.0f;
		float t = dis / v;
		auto act_mt = MoveTo::create(t, posTo);
		auto act_cb = CallFunc::create([&, this]{
			_isMoving = false;
            
			_strokePointIndex++;
			if (_strokePointIndex >= _picData->strokes[_strokeIndex]->pos.size())
			{
				_strokePointIndex = 0;
				_strokeIndex++;
				
				if (_strokeIndex >= _picData->strokes.size())
				{
					//MessageBox("finish", "info");
					_strokeIndex = 0;
					_strokePointIndex = 0;
					arma->getEventDispatcher()->dispatchCustomEvent(MSG_EVENT_GAME_FINISH, nullptr);
				}
				else
				{
					Vec2 pos_start = _picData->strokes[_strokeIndex]->pos[0];
                    pos_start=Vec2( pos_start.x, sizeV.height - pos_start.y);
					arma->setPosition(pos_start);
				}
                
			}
            
		});
        
		auto seq = Sequence::create(act_mt, act_cb, nullptr);
        
		arma->stopAllActions();
		arma->runAction(seq);
        
		_isMoving = true;
        
		return true;
        
	} while (false);
    
    
	return false;
}


void Elf::update(float dt)
{
	if (_isTouchDown)
	{
		this->checkToMove(_posWTouchDown);
	}
}


int Elf::checkPointInCircle(const Vec2& posWorldCheck)
{
	if (arma)
	{
		Vec2 posWorldCenter = arma->convertToWorldSpaceAR(Vec2::ZERO);
        
        //check_reduis=20.0f
		float rr = (check_raduis)*(check_raduis);
        float rr2=(check_raduis+40)*(check_raduis+40);
		float xx = (posWorldCheck.x - posWorldCenter.x)*(posWorldCheck.x - posWorldCenter.x);
		float yy = (posWorldCheck.y - posWorldCenter.y)*(posWorldCheck.y - posWorldCenter.y);
        
        if ((xx + yy) < rr2) {
            return 1;
        }else{
            return 0;
        }
        
        //if(((xx + yy) > rr)&&((xx+yy)<rr2)){return 1;}
        //else if((xx+yy)<rr) {return 1;}
        
	}
}
