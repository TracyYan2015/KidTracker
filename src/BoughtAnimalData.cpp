//
//  BoughtAnimalData.cpp
//  KidTracer
//
//  Created by user on 14-10-13.
//
//

#include "BoughtAnimalData.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

#include "stdio.h"
#include "stdlib.h"

#include "CCDate.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;


std::string BoughtAnimalData::getAnimalName()
{
    return animalName;
}
std::string BoughtAnimalData::getImageFileName()
{
    return imageFileName;
}
std::string BoughtAnimalData::getImageFileNameMH()
{
    return imageFileNameMH;
}
int BoughtAnimalData::getId()
{
    return id;
}

int BoughtAnimalData::getConcreteId()
{
    return concreteId;
}

void BoughtAnimalData::setId(int id)
{
    this->id = id;
}
void BoughtAnimalData::setConcreteId(int concreteId)
{
    this->concreteId = concreteId;
}
void BoughtAnimalData::setAnimalName(std::string animalName)
{
    this->animalName = animalName;
}
void BoughtAnimalData::setImageFileName(std::string fileName)
{
    this->imageFileName = fileName;
}
void BoughtAnimalData::setImageFileNameMH(std::string fileNameMH)
{
    this->imageFileNameMH = fileNameMH;
}

BoughtAnimalData::BoughtAnimalData(int _id, int _concreteId, std::string _animalName, std::string _fileName, std::string _fileNameMH):
id(_id),
concreteId(_concreteId),
animalName(_animalName),
imageFileName(_fileName),
imageFileNameMH(_fileNameMH)
{

}

void BoughtAnimalData::showData()
{
    CCLOG("id %d concreteId %d animalName %s", id, concreteId, animalName.c_str());
    CCLOG("fileName %s fileNameMH %s", imageFileName.c_str(), imageFileNameMH.c_str());
}


