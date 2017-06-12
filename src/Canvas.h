#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "cocos2d.h"
#include "Elf.h"

using namespace cocos2d;


enum eCanvasMode
{
	GUIDE,
	STROKE_GUIDE, // 手绘引导
	STROKE_DRAW, // 手绘
	FREE
};

class Canvas : public Node
{

public:
    
    Sprite* _brush_bg;

	Canvas();

	virtual ~Canvas();

	CREATE_FUNC(Canvas);

	virtual bool init() override;

	bool init(eCanvasMode mode);

	void onTouchMoved(Touch * touch, Event * pEvent,  eElfMotion state);

	void replaceNode(Node* node);


	void cleanCanvas();

	CCSize getCanvasSize();

	void drawLine(RenderTexture* canvas, Sprite* brush, Vec2 posStart, Vec2 posEnd);

	void drawLine2(const char* brush_image_path, Vec2 posStart, Vec2 posEnd);

	void drawLineSolid(const char* brush_image_path, Vec2 posStart, Vec2 posEnd,bool usePlist);

	// 绘制
	void drawLine(const char* brush_image_path, float scale, BlendFunc blendFunc, Vec2 posStart, Vec2 posEnd,bool usePlist);

	void drawPixel(const int& x, const int& y);

	static void savePointsToPngFile(const std::string& file_path, int w, int h, std::vector<Vec2>& points);

	void getDrawPoints(std::vector<Vec2>& out_points);

	static void getIntersectPoints(int w_max, int h_max, std::vector<Vec2>& points_a, std::vector<Vec2>& points_b, std::vector<Vec2>& out_points);

	void getIntersectPoints(Canvas* canvas, std::vector<Vec2>& out_points);
    RenderTexture* _rt;
    
    
    void update(float delta);
    

protected:
	eCanvasMode _mode;
	CCSize _canvasSize;
	
	Sprite* _brush;
	Vector<Sprite*> _brushs;
    int frameCount;
};

#endif // __CANVAS_H__