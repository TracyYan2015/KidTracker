//
//  UserData.cpp
//  KidTracer
//
//  Created by Bian Wu on 19/8/14.
//
//

#include "UserData.h"

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

UserData::UserData()
{
    std::string _doc = CCFileUtils::getInstance()->getWritablePath()+"test.plist";
    const char* testPlistPath =_doc.c_str();
    
    plistDic = __Dictionary::createWithContentsOfFile(testPlistPath);
    
    sizeStr = dynamic_cast<__String*>(plistDic->objectForKey("size"));
    
    if(sizeStr == NULL){
        const char* testPlistPath1 = "test.plist";
        __Dictionary* plistDic1 = __Dictionary::createWithContentsOfFile(testPlistPath1);
        plistDic1->writeToFile(testPlistPath);
        plistDic = __Dictionary::createWithContentsOfFile(testPlistPath);
        sizeStr = dynamic_cast<__String*>(plistDic->objectForKey("size"));
    }
    fileStr = dynamic_cast<__String*>(plistDic->objectForKey("file"));
    nameStr = dynamic_cast<__String*>(plistDic->objectForKey("name"));
    ageStr = dynamic_cast<__String*>(plistDic->objectForKey("age"));
    jbhDic = dynamic_cast<__Dictionary*>(plistDic->objectForKey("jbh"));
    elfDic = dynamic_cast<__Dictionary*>(plistDic->objectForKey("elf"));
    sceneDic = dynamic_cast<__Dictionary*>(plistDic->objectForKey("scene"));
    albumArr = dynamic_cast<__Array*>(plistDic->objectForKey("pic"));
    
    
    isLiBaoBought = dynamic_cast<__String*>(plistDic->objectForKey("isLiBaoBought"));
}


Vector<__String*>* UserData::getUserInfo(){
    Vector<__String*>*  userInfo = new Vector<__String*>();
    
    __String* name = dynamic_cast<__String*>(plistDic->objectForKey("name"));
    __String* age = dynamic_cast<__String*>(plistDic->objectForKey("age"));
    
    if(name->length()){
        userInfo->pushBack(name);
    }
    if(age->length()){
        userInfo->pushBack(age);
    }
    
    
    return userInfo;
}

void UserData::setUser(__String* name, __String* age)
{
    __String* pName = name;
    __String* pAge = age;
    plistDic->setObject(pName, "name");
    plistDic->setObject(pAge, "age");
    
    std::string path = CCFileUtils::getInstance()->getWritablePath();
    std::string _doc1 = path + "test.plist";
    plistDic->writeToFile(_doc1.c_str());
}

int UserData::addPicItem()
{
    //-----------获得系统时间，并生成一条图片文件记录
    auto date = CCDate::createWithCurrentTime();

    int albumlength = sizeStr->intValue()+1;
    fileStr = dynamic_cast<__String*>(plistDic->objectForKey("file"));
    int fileInt = fileStr->intValue()+1;
    
    __Dictionary * picdic = new __Dictionary();
    __String* pPath = __String::create(String::createWithFormat("%d.png",fileInt)->getCString());
    picdic->setObject(pPath, "path");
    __String* pYr = __String::create(String::createWithFormat("%d",date->getYear()%100)->getCString());
    picdic->setObject(pYr, "yr");
    __String* pMo = __String::create(String::createWithFormat("%d",date->getMonth())->getCString());
    picdic->setObject(pMo, "mo");
    __String* pDa = __String::create(String::createWithFormat("%d",date->getDay())->getCString());
    picdic->setObject(pDa, "da");
    __String* pHr = __String::create(String::createWithFormat("%d",date->getHours())->getCString());
    picdic->setObject(pHr, "hr");
    __String* pMi = __String::create(String::createWithFormat("%d",date->getMinutes())->getCString());
    picdic->setObject(pMi, "mi");
    
    
    albumArr->addObject(picdic);
    plistDic->setObject(albumArr, "pic");
    __String* plength = __String::create(String::createWithFormat("%d",albumlength)->getCString());
    plistDic->setObject(plength, "size");
    __String* flength = __String::create(String::createWithFormat("%d",fileInt)->getCString());
    plistDic->setObject(flength, "file");
    
    std::string path = CCFileUtils::getInstance()->getWritablePath();
    std::string _doc1 = path + "test.plist";
    plistDic->writeToFile(_doc1.c_str());
    
    return fileInt;
}

void UserData::delPicItem(int index)
{
    int albumlength = sizeStr->intValue();
    albumArr->removeObjectAtIndex(index);
    plistDic->setObject(albumArr, "pic");
    __String* plength = __String::create(String::createWithFormat("%d",albumlength-1)->getCString());
    plistDic->setObject(plength, "size");
    
    std::string path = CCFileUtils::getInstance()->getWritablePath();
    std::string _doc1 = path + "test.plist";
    plistDic->writeToFile(_doc1.c_str());
}


void UserData::showData()
{
    CCLOG("show data start!!!");
    int albumlength = sizeStr->intValue();

    CCLOG("name= %s, age=%s \n", nameStr->getCString(), ageStr->getCString());


    {
        __String* jbh1 = dynamic_cast<__String*>(jbhDic->objectForKey("1"));
        __String* jbh2 = dynamic_cast<__String*>(jbhDic->objectForKey("2"));
        __String* jbh3 = dynamic_cast<__String*>(jbhDic->objectForKey("3"));
        __String* jbh4 = dynamic_cast<__String*>(jbhDic->objectForKey("4"));
        __String* jbh5 = dynamic_cast<__String*>(jbhDic->objectForKey("5"));
        
        
        CCLOG("jbh1~8= %s, %s, %s, %s, %s \n", jbh1->getCString(), jbh2->getCString(), jbh3->getCString(), jbh4->getCString(), jbh5->getCString());
    }
    
    __String* scene1 = dynamic_cast<__String*>(sceneDic->objectForKey("1"));
    __String* scene2 = dynamic_cast<__String*>(sceneDic->objectForKey("2"));
    __String* scene3 = dynamic_cast<__String*>(sceneDic->objectForKey("3"));
    __String* scene4 = dynamic_cast<__String*>(sceneDic->objectForKey("4"));
    __String* scene5 = dynamic_cast<__String*>(sceneDic->objectForKey("5"));
    
    
    CCLOG("scene1~5= %s, %s, %s, %s, %s  \n", scene1->getCString(), scene2->getCString(), scene3->getCString(), scene4->getCString(), scene5->getCString());
    
    __String* name = dynamic_cast<__String*>(plistDic->objectForKey("name"));
    __String* age = dynamic_cast<__String*>(plistDic->objectForKey("age"));
    CCLOG("name is %s, age is %s",name->getCString(),age->getCString());

    {
        __String* elf1 = dynamic_cast<__String*>(elfDic->objectForKey("1"));
        __String* elf2 = dynamic_cast<__String*>(elfDic->objectForKey("2"));
        __String* elf3 = dynamic_cast<__String*>(elfDic->objectForKey("3"));
        __String* elf4 = dynamic_cast<__String*>(elfDic->objectForKey("4"));
        __String* elf5 = dynamic_cast<__String*>(elfDic->objectForKey("5"));
        
        
        CCLOG("elf1~2= %s, %s,%s, %s,%s \n", elf1->getCString(), elf2->getCString(),elf3->getCString(), elf4->getCString(),elf5->getCString());
    }
    

    for(int i=0; i<albumlength; i++)
    {
        
        __Dictionary* picitem = dynamic_cast<__Dictionary*>(albumArr->getObjectAtIndex(i));
        __String* picpath = dynamic_cast<__String*>(picitem->objectForKey("path"));
        __String* picyr = dynamic_cast<__String*>(picitem->objectForKey("yr"));
        __String* picmo = dynamic_cast<__String*>(picitem->objectForKey("mo"));
        __String* picda = dynamic_cast<__String*>(picitem->objectForKey("da"));
        __String* pichr = dynamic_cast<__String*>(picitem->objectForKey("hr"));
        __String* picmi = dynamic_cast<__String*>(picitem->objectForKey("mi"));
        
        CCLOG("path=%s, yr=%s, mo=%s, da=%s, hr=%s, mi=%s \n", picpath->getCString(), picyr->getCString(), picmo->getCString(), picda->getCString(), pichr->getCString(), picmi->getCString());
    }
}