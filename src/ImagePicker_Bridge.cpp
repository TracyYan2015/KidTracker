//
//  ImagePicker_Bridge.cpp
//  KidTracer
//
//  Created by Bian Wu on 23/8/14.
//
//

#include "ImagePicker_Bridge.h"
#include "FreeCanvas.h"

ImagePicker_Bridge::ImagePicker_Bridge()
{

}

ImagePicker_Bridge::~ImagePicker_Bridge()
{

}

void ImagePicker_Bridge::didFinishPickingWithResult(cocos2d::Texture2D* result)
{
    
    CCRect rect;
    rect.setRect(108,5,784,628);
    auto sp = Sprite::createWithTexture(result,rect);
    sp->setAnchorPoint(Vec2(0,0));
    sp->setPosition(Vec2(0,0));
    /*
    RenderTexture* canvas = RenderTexture::create(_st->_canvas->getContentSize().width, _st->_canvas->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
	canvas->retain();
	Point posFix = Point(_st->_canvas->getContentSize().width/2, _st->_canvas->getContentSize().height/2);
	canvas->setAnchorPoint(Point::ZERO); // Point(0.5f, 0.5f)
	canvas->setPosition(Point::ZERO + posFix);
    _st->_canvas->addChild(canvas, 0);
    
	// «Âø’ª≠≤º
	canvas->clear(1.0f, 1.0f, 1.0f, 0.0f);
    
    canvas->begin();
    //sp->setPosition(Point(brush_bg->getContentSize().width / 2, brush_bg->getContentSize().height / 2));
    sp->visit();
    canvas->end();

    _st->_canvas->_rt = canvas;
    */
    /*
    Widget* pn_canvas = Widget::create();
    
    pn_canvas->setTouchEnabled(true);
	pn_canvas->setEnabled(true);
    pn_canvas->setTag(10000);
    pn_canvas->setZOrder(zTagDefault);
    int i = pn_canvas->getLocalZOrder();
    pn_canvas->removeAllChildren();
    pn_canvas->addChild(sp);
    */
    
    Widget* pn_canvas = Widget::create();
    pn_canvas->removeAllChildren();
	pn_canvas->setTouchEnabled(true);
	pn_canvas->setEnabled(true);
    pn_canvas->addChild(sp);
	_st->_canvas->replaceNode(pn_canvas);
    
    /* guowei
    FreeCanvas* canvas = FreeCanvas::create();
    //canvas->init(eCanvasMode::BACKGROUND);
	canvas->replaceNode(pn_canvas);
    canvas->setContentSize(pn_canvas->getContentSize());
	canvas->setAnchorPoint(pn_canvas->getAnchorPoint());
	canvas->setPosition(pn_canvas->getPosition());
	_st->_canvas = canvas;
    guowei */
    
    //_st->_canvas->addChild(sp);
    
    //********* guowei up
    
    /*
    FreeCanvas* canvas1 = FreeCanvas::create();
    canvas1->init(eCanvasMode::FREE);
    canvas1->setContentSize(pn_canvas->getContentSize());
	canvas1->setAnchorPoint(pn_canvas->getAnchorPoint());
	canvas1->setPosition(pn_canvas->getPosition());
	_st->_canvas = canvas1;
    */
    
    //_st->_ui->addChild((Widget*)pn_canvas,0);
    /*
    cocos2d::Texture2D* tx;
    pn_canvas->loadTexture(tx);

    Widget* pn_canvas = _ui->getChildByName("img_Canvas"); //KidTracerModeGuid.ExportJson
	pn_canvas->setTouchEnabled(true);
	pn_canvas->setEnabled(true);
	FreeCanvas* canvas = FreeCanvas::create();
	canvas->replaceNode(pn_canvas);
    //this->addChild(canvas);
	_canvas = canvas;
    */
}