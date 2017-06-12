//
//  BoughtAnimalData.h
//  KidTracer
//
//  Created by user on 14-10-13.
//
//

#ifndef __KidTracer__BoughtAnimalData__
#define __KidTracer__BoughtAnimalData__

#include <iostream>

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;

class BoughtAnimalData
{
private:
    int id;
    int concreteId;
    std::string animalName;
    std::string imageFileName;//描红模式预览小图
    std::string imageFileNameMH;//描红模式预览大图
    
public:
    void setId(int id);
    void setConcreteId(int concreteId);
    void setAnimalName(std::string animalName);
    void setImageFileName(std::string fileName);
    void setImageFileNameMH(std::string fileNameMH);
    
    int getId();
    int getConcreteId();
    std::string getAnimalName();
    std::string getImageFileName();
    std::string getImageFileNameMH();
    BoughtAnimalData(int id, int concreteId, std::string animalName, std::string fileName, std::string fileNameMH);
    
    void showData();
    
    
    
};

#endif /* defined(__KidTracer__BoughtAnimalData__) */
