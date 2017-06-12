#ifndef __PICTURE_DATA_H__
#define __PICTURE_DATA_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;


class StrokeData
{
public:
	std::vector<Vec2> pos;
	bool isWait;
};


class PictureData
{
public:
	PictureData();
	void loadStrokeData();//解析纯文本文件中的坐标数据
    void setPath(std::string path);
	std::vector<StrokeData*> strokes;
    std::string mh_picData;
};

#endif // __PICTURE_DATA_H__