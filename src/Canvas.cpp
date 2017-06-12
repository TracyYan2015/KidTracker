#include "Canvas.h"


Canvas::Canvas()
: _rt(nullptr)
, _brush(nullptr)
, frameCount(0)
{
    //this->scheduleUpdate();
}

Canvas::~Canvas()
{

}


bool Canvas::init()
{

	Node::init();

	return true;
}

void Canvas::update(float delta){
    frameCount++;
    if(_rt != nullptr){
        //CCLOG("frameCount is %d", frameCount);
        //CCLOG("_rt''s reference count is %d",_rt->getReferenceCount());
    }
   
}

bool Canvas::init(eCanvasMode mode)
{
    
	_mode = mode;
	CCSize vSize = Director::getInstance()->getVisibleSize();
	Vec2 vOrigin = Director::getInstance()->getVisibleOrigin();
	if (mode == eCanvasMode::GUIDE)
    {
        _brush_bg = Sprite::create("data/canvas/ydms_wq_8.png");
        _brush_bg->setVisible(false);
    }
    
	else if (mode == eCanvasMode::STROKE_GUIDE)
	{
		_brush_bg = Sprite::create("data/canvas/canvas_bg_t.png");//blank
		_brush_bg->setBlendFunc({GL_ONE, GL_ZERO});
	}
	else if (mode == eCanvasMode::STROKE_DRAW)
	{
		_brush_bg = Sprite::create("data/canvas/canvas_bg_t.png");//blank
		_brush_bg->setBlendFunc({ GL_ONE, GL_ZERO });
	}	
	else if (mode == eCanvasMode::FREE)
	{
		
	}
	float w = _brush_bg->getContentSize().width;
	float h = _brush_bg->getContentSize().height;
	_canvasSize = CCSize(w, h);
    
    _brush_bg->retain(); //coven0202 memory leak
    
    
    
	_rt = RenderTexture::create(_canvasSize.width, _canvasSize.height, Texture2D::PixelFormat::RGBA8888);
    this->addChild(_rt, 0);
	Vec2 posFix = Vec2(_canvasSize.width / 2, _canvasSize.height / 2);
	_rt->setAnchorPoint(Vec2::ZERO);
	_rt->setPosition(Vec2::ZERO + posFix);
    

	cleanCanvas();
	return true;
}

void Canvas::onTouchMoved(Touch * touch, Event * pEvent, eElfMotion state)
{
	auto start = touch->getPreviousLocation();
	auto end = touch->getLocation();
    start = _rt->convertToNodeSpace(start) + _canvasSize / 2;
	end = _rt->convertToNodeSpace(end) + _canvasSize / 2;

    if(state == eElfMotion::Move)
        drawLine(_rt, _brush, start, end);
}



void Canvas::replaceNode(Node* node)
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


void Canvas::drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd)
{
	float distance = posStart.distance(posEnd);
	float difx = posEnd.x - posStart.x;
	float dify = posEnd.y - posStart.y;

	_brushs.clear();

	for (int i = 0; i < distance; i++)
	{
		// Sprite* brush = Sprite::create("data/canvas/brush5.png");
		Sprite* brush = Sprite::create("data/canvas/brush7.png");
		brush->retain();

		BlendFunc bf;
		bf.dst = GL_SRC_ALPHA;
		bf.src = GL_ONE_MINUS_SRC_ALPHA;
		brush->setBlendFunc(bf);

		_brushs.pushBack(brush);
	}

	canvas->begin();
	for (int i = 0; i < distance; i++)//
	{
		float delta = (float)i / distance;
		Vec2 pos = ccp(posStart.x + (difx * delta), posStart.y + (dify * delta));
		// CCLOG("[%d] - (%d,%d)", i, (int)pos.x, (int)pos.y );

		Sprite* br = _brushs.at(i);
		br->setPosition(pos);
		br->visit();


	}
	canvas->end();

}

void Canvas::drawLine(const char* brush_image_path, float scale, BlendFunc blendFunc, Vec2 posStart, Vec2 posEnd,bool usePlist)
{
	RenderTexture* renderTexture = _rt;
	float distance = posStart.distance(posEnd);
	float difx = posEnd.x - posStart.x;
	float dify = posEnd.y - posStart.y;

	_brushs.clear();
	for (int i = 0; i < distance; i++)
	{
        Sprite* brush;
        if(usePlist){
            brush = Sprite::createWithSpriteFrameName(brush_image_path);
        }else{
            brush = Sprite::create(brush_image_path);
        }
        
		brush->retain();

		brush->setScale(scale);
		brush->setBlendFunc(blendFunc);

		_brushs.pushBack(brush);
        int count = brush->getReferenceCount();
        
        //12-15
        brush->release();
	}

	renderTexture->begin();
	for (int i = 0; i < distance; i++)//
	{
		float delta = (float)i / distance;
		Vec2 pos = ccp(posStart.x + (difx * delta), posStart.y + (dify * delta));
		Sprite* br = _brushs.at(i);
		br->setPosition(pos);
        br->visit();
	}
	renderTexture->end();

	

}

void Canvas::drawPixel(const int& x, const int& y)
{
	RenderTexture* renderTexture = _rt;

	Image* finalImage = renderTexture->newImage();

	unsigned char *pData = finalImage->getData();

	int h = finalImage->getHeight();
	int w = finalImage->getWidth();

	size_t len = finalImage->getDataLen();

	int w_bytes = len / h;

	int index = y * w_bytes + x * 4;
	pData[index] = 255; //r
	pData[index + 1] = 0;
	pData[index + 2] = 0;
	pData[index + 3] = 255; // a

}


void Canvas::savePointsToPngFile(const std::string& file_path, int w, int h, std::vector<Vec2>& points)
{
	RenderTexture* rt = RenderTexture::create(w, h);
	Image* finalImage = rt->newImage();

	unsigned char *pData = finalImage->getData();

// 	int h = finalImage->getHeight();
// 	int w = finalImage->getWidth();
	size_t len = finalImage->getDataLen();
	int w_bytes = len / h;

	int index = 0;
	for (auto it = points.begin(); it != points.end(); ++it)
	{
		const Vec2& pos = *it;
		index = pos.y * w_bytes + pos.x * 4;

		pData[index] = 255;
		pData[index + 1] = 0;
		pData[index + 2] = 0;
		pData[index + 3] = 255;

	}

	finalImage->saveToFile(file_path.c_str(), true);  //"c:\\aaa.png"
}


void Canvas::drawLine2(const char* brush_image_path, Vec2 posStart, Vec2 posEnd)
{

	BlendFunc bf;
	bf.dst = GL_SRC_ALPHA;
	bf.src = GL_ONE_MINUS_SRC_ALPHA;
	drawLine(brush_image_path, 1.0f, bf, posStart, posEnd,false);
}


void Canvas::drawLineSolid(const char* brush_image_path, Vec2 posStart, Vec2 posEnd,bool usePlist)
{
	drawLine(brush_image_path, 1.0f, BlendFunc::ALPHA_PREMULTIPLIED, posStart, posEnd,usePlist);
}



void Canvas::cleanCanvas()
{
	RenderTexture* rt = _rt;

	if (_mode == eCanvasMode::GUIDE)
	{
		rt->begin();
		_brush_bg->setPosition(Vec2(_brush_bg->getContentSize().width / 2, _brush_bg->getContentSize().height / 2));
		_brush_bg->visit();
		rt->end();
	}
	else if (_mode == eCanvasMode::STROKE_GUIDE)
	{
		rt->begin();
		_brush_bg->setPosition(Vec2(_brush_bg->getContentSize().width / 2, _brush_bg->getContentSize().height / 2));
		_brush_bg->visit();
		rt->end();

	}
	else if (_mode == eCanvasMode::STROKE_DRAW)
	{
		rt->begin();
		_brush_bg->setPosition(Vec2(_brush_bg->getContentSize().width / 2, _brush_bg->getContentSize().height / 2));
		_brush_bg->visit();
		rt->end();
	}
	else if (_mode == eCanvasMode::FREE)
	{

	}

}


void Canvas::getDrawPoints(std::vector<Vec2>& out_points)
{
	RenderTexture* renderTexture = _rt;
	Image* finalImage = renderTexture->newImage();
    
    
	unsigned char *pData = finalImage->getData();

	int h = finalImage->getHeight();
	int w = finalImage->getWidth();
	size_t len = finalImage->getDataLen();
	int w_bytes = len / h;

	int r, g, b, a;
	std::string str = "";
	//char buf[128];
	int index = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			index = y * w_bytes + x * 4;

			r = pData[index] & 0xff;
			g = pData[index + 1] & 0xff;
			b = pData[index + 2] & 0xff;
			a = pData[index + 3] & 0xff;

			if (a >= 32)
			{
				out_points.push_back(Vec2(x, y));
			}
		}
	}
    
    
    //12-15
    finalImage->release();

}


void Canvas::getIntersectPoints(int w_max, int h_max, std::vector<Vec2>& points_a, std::vector<Vec2>& points_b, std::vector<Vec2>& out_points)
{
	int w = w_max;
	int h = h_max;
	// w * h is the number of bit, so num_byte(byteLen equals (w * h) / 8)
	int byte_Len = (w * h) / 8 + 1;

	if (byte_Len <= 0) return;

	char* bitCache = new char[byte_Len];
	memset(bitCache, 0, sizeof(char)*byte_Len);
	{
		int bitIndex = 0;

		for (auto it = points_a.begin(); it != points_a.end(); ++it)
		{
			const Vec2& pt = *it;
			bitIndex = pt.y * w + pt.x;
			//将pt(x,y)对应的一个编号(bitIndex = pt.y * w + pt.x;)在bitCache中的那个bit置1.
			bitCache[bitIndex >> 3] |= (1 << (bitIndex % 8));
		}

		for (auto it = points_b.begin(); it != points_b.end(); ++it)
		{
			const Vec2& pt = *it;
			bitIndex = pt.y * w + pt.x;
			if ((bitCache[bitIndex >> 3] >> (bitIndex % 8)) & 1)
			{
				out_points.push_back(Vec2(pt));
			}
		}

	}
	delete[] bitCache;
}


void Canvas::getIntersectPoints(Canvas* canvasOther, std::vector<Vec2>& out_points)
{
	if (canvasOther == nullptr) return;

	int w = _canvasSize.width;
	int h = _canvasSize.height;
	
	std::vector<Vec2> points;
	this->getDrawPoints(points);

	std::vector<Vec2> other_points;
	canvasOther->getDrawPoints(other_points);

	Canvas::getIntersectPoints(w, h, points, other_points, out_points);

}

cocos2d::Size Canvas::getCanvasSize()
{
	return _canvasSize;
}



