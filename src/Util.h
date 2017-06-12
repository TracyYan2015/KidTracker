#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;
using namespace cocos2d::extension;


class Util
{
public:


	// value convert
	static float str_to_float(const std::string& str);

	static int str_to_int(const std::string& str);

	static Vec2 str_to_point(const std::string& str);

	// 字符串分割，直接获取某个分割位上的字符。index从0开始  如"a,b,c" [1]="b"
	static std::string strSplitAt(std::string str, const char* seprator, int index);

	// 字符串分割,把所有的分割内容以vector返回 (如果传入""，则返回vector size=1 "")
	static void strSplit(std::string str, const char* seprator, std::vector<std::string>& strs_out);
    
    
    static std::string int_to_str(int val);
    
    static void addPVR(std::string plistPath);
    static void removePVR(std::string plistPath);
    static void loadPlists(std::vector<std::string> plist_paths);
    static void unloadPlists(std::vector<std::string> plist_paths);
    static void printTextureCacheInfo(std::string situation);
    
    static void cleanTextureCacheWithMessage(std::string situation);
    
    
    static void exitCallback();
    
    
    //get random BGM for one of the 3 modes
    static int randomModeSound();
    
    static void sortCCStringArray(__Array* array);
    
    
    //3-8
    static int findVectorIdByCCString(Vector<__String*> vector, __String* string);
    
};

#endif // _UTIL_H_
