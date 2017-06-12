#include "Util.h"
/*
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "ArmatureTest.h"
 */
#include "SceneTitle.h"
#include "SceneRenderTextureTest.h"


float Util::str_to_float(const std::string& str)
{
	float val = 0.0f;
	sscanf(str.c_str(), "%f", &val);
	return val;
}

int Util::str_to_int(const std::string& str)
{
	int val = 0;
	sscanf(str.c_str(), "%d", &val);
	return val;
}

std::string Util::int_to_str(int val)
{
	char buf[64];
	sprintf(buf, "%d", val);
	return buf;
}

Vec2 Util::str_to_point(const std::string& str)
{
	Vec2 pt = Vec2::ZERO;
	sscanf(str.c_str(), "%f,%f", &pt.x, &pt.y);
	return pt;
}

std::string Util::strSplitAt(std::string str, const char* seprator, int index)
{
	std::string strRet = "";
	//CCLOG("[0] 0x%x", &strRet);

	int pos = 0;
	int pos_start = 0;
	int seplen = strlen(seprator);

	int i = 0;
	do
	{
		pos = str.find(seprator, pos_start);

		if (i == index)
		{
			if (pos > 0)
				strRet = str.substr(pos_start, pos - pos_start);
			else
				strRet = str.substr(pos_start);
		}

		pos_start = pos + seplen;
		i++;
	} while (pos > 0);
	return strRet;
}

void Util::addPVR(std::string plistPath){
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(plistPath);
}

void Util::removePVR(std::string plistPath){
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->removeSpriteFramesFromFile(plistPath);
    TextureCache::getInstance()->removeUnusedTextures();
}

void Util::loadPlists(std::vector<std::string> plist_paths){
    for (int i = 0; i < plist_paths.size(); i++) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_paths.at(i));
    }
}

void Util::cleanTextureCacheWithMessage(std::string situation){
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    if(situation.size() != 0){
        CCLOG("%s",situation.c_str());
        CCLOG("%s",Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    }
    SceneTitle::loadYunPlists();
    
}

void Util::printTextureCacheInfo(std::string situation){
    CCLOG("%s",situation.c_str());
    CCLOG("%s",Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
}

void Util::exitCallback(){
    //Layer::onExit();
    
}

void Util::unloadPlists(std::vector<std::string> plist_paths){
    for (int i = 0; i < plist_paths.size(); i++) {
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist_paths.at(i));
        TextureCache::getInstance()->removeUnusedTextures();
    }
}
void Util::strSplit(std::string str, const char* seprator, std::vector<std::string>& strs_out)
{
	int pos = 0;
	int pos_start = 0;
	int seplen = strlen(seprator);
    
    
	do
	{
        pos = str.find(seprator, pos_start);
       // CCLOG("found position is %d", pos);
        //not found?returns -1
        if (pos > 0){
            strs_out.push_back(str.substr(pos_start, pos - pos_start));
        }else{
            strs_out.push_back(str.substr(pos_start));
        }
        /*
        else if(pos == 0){
            //pos = 0, means the split is at the start.
			//strs_out.push_back(str.substr(pos_start));//when lenght is not given, it continue to last
            //in this case, that means the whole string
        }
         */
		pos_start = pos + seplen;

	} while (pos >= 0);
}

void Util::sortCCStringArray(cocos2d::__Array *array){
    //array is an array of __String
    //冒泡排序
    for(int i=0;i<array->count();i++){
        for(int j=0;j<array->count()-i-1;j++){
            __String* a = dynamic_cast<__String*>(array->getObjectAtIndex(j));
            __String* b = dynamic_cast<__String*>(array->getObjectAtIndex(j + 1));
            if(strcmp(a->getCString(), b->getCString()) > 0){
                array->exchangeObjectAtIndex(j, j+ 1);
            }
        }
    }
    
    for(int i = 0; i < array->count(); i++) {
        __String* s = dynamic_cast<__String*>(array->getObjectAtIndex(i));
        CCLOG("%s", s->getCString());
    }
    
}





int Util::findVectorIdByCCString(Vector<__String*> vector, cocos2d::__String *string){
    int vectorId = 0;
    
    for (int i = 0; i < vector.size(); i++) {
        __String* tmp = dynamic_cast<__String*>(vector.at(i));
        int result = std::strcmp(tmp->getCString(), string->getCString());
        if(result == 0){
            vectorId = i;
            break;
        }
    }
    return vectorId;
}

int Util::randomModeSound()
{
    int randInt = arc4random()%8; 
    while(modeSoundTmp == randInt)
    {
        randInt = arc4random()%8;
    }
    modeSoundTmp = randInt;
    return randInt;
}
