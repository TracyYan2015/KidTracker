#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "SceneController.h"
#include "SceneKidTracer.h"
#include "SceneRenderTextureTest.h"
#include "SceneTitle.h"
#include "SceneModeGuid.h"
#include "SceneRenderTextureTestAlpha.h"
#include "SceneModeGuidDraw.h" // @sonikk 2014-7-20 0:38:50
#include "C2DXShareSDK.h"

#include "ShareSDK/ShareSDK.h"



using namespace cn::sharesdk;

USING_NS_CC;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}


void AppDelegate::authResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("授权成功");
            break;
        case C2DXResponseStateFail:
            CCLog("授权失败");
            break;
        default:
            break;
    }
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) 
	{
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);

		glview->setFrameSize(1024.0f, 768.0f);

		//glview->setFrameSize(1136, 640.0f);
    }
	glview->setDesignResolutionSize(1366.0f, 768.0f, ResolutionPolicy::FIXED_HEIGHT);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 30);


	
	
	
    
    SceneController::getInstance()->startScene(eSceneIdSceneRenderTextureTest);
    C2DXShareSDK::open(CCString::create("2ab7ac9e55d1"), false);
    
    
    
    
    __Dictionary *sinaConfigDict = CCDictionary::create();
    sinaConfigDict -> setObject(__String::create("568898243"), "app_key");
    sinaConfigDict -> setObject(__String::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaConfigDict -> setObject(__String::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);

    __Dictionary *wxConfigDict = __Dictionary::create();
    //correct id and secret
    wxConfigDict -> setObject(__String::create("wx416db3e2e770108c"), "app_id");
    wxConfigDict->setObject(__String::create("67566ad82e17a6f087282f047b5174ae"), "app_secret");
    
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiSession, wxConfigDict);
    
    
    __Dictionary* qZoneConfigDict = __Dictionary::create();
    qZoneConfigDict->setObject(__String::create("1103449900"), "app_id");
    qZoneConfigDict->setObject(__String::create("JWKWu1hE3SVrzJzd"), "app_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeQZone, qZoneConfigDict);
    
    __Dictionary* tencentWeiboConfigDict = __Dictionary::create();
    tencentWeiboConfigDict->setObject(__String::create("801553220"), "app_key");
    tencentWeiboConfigDict->setObject(__String::create("7fd7c9d3c7858ec63e9fe3cdc571b60f"), "app_secret");
    
    //tencentWeiboConfigDict->setObject(__String::create("801307650"), "app_key");
   // tencentWeiboConfigDict->setObject(__String::create("ae36f4ee3946e1cbb98d6965b0b2ff5c"), "app_secret");
    tencentWeiboConfigDict->setObject(__String::create("http://www.baidu.com"), "redirect_uri");
    
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTencentWeibo, tencentWeiboConfigDict);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
