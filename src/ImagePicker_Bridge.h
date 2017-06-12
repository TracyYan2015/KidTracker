//
//  ImagePicker_Bridge.h
//  KidTracer
//
//  Created by Bian Wu on 23/8/14.
//
//

#ifndef __KidTracer__ImagePicker_Bridge__
#define __KidTracer__ImagePicker_Bridge__

#include <iostream>
#include "ImagePicker.h"
#include "SceneModeFreeDraw.h"

class ImagePicker_Bridge : public ImagePickerDelegate
{
public:
    ImagePicker_Bridge();
    ~ImagePicker_Bridge();

    void didFinishPickingWithResult(cocos2d::Texture2D* result);
    
    SceneModeFreeDraw* _st;

};
#endif /* defined(__KidTracer__ImagePicker_Bridge__) */
