
#ifndef __SCENE_CONTROLLER_H__
#define __SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "SceneTitleUserData.h"
#include "BoughtSetsAndNum.h"

using namespace cocos2d;

enum eSceneId
{
	eSceneIdSceneTitle = 0,
	eSceneIdSceneModeGuid,
	eSceneIdSceneModeGuidDraw,
	eSceneIdSceneRenderTextureTest,
    eSceneIdSceneElfDialog,
    eSceneIdSceneDialog,
    eSceneIdSceneStickFigureDialog,
    eSceneIdHelloWorld,
    eSceneIdSceneHuaceDialog,
    eSceneIdSceneBigHuaceDialog,
    eSceneIdSceneSetupDialog,
    eSceneIdSceneShangdianDialog,
    eSceneIdSceneModeFreeDraw,
    eSceneIdSceneHaceDeleteDialog,
    eSceneIdSceneModeGuidStroke,
    
    
};

class SceneController
{

public:

	static SceneController* getInstance();

	Scene* createScene(Layer* layer);

	Layer* getSceneById(int scene_id);

	void startScene(int scene_id);

	void replaceScane(int scene_id);
    
    //added by myself
    void addScene(Node* parent,int scene_id);
    SceneTitleUserData* data;
    
    BoughtSetsAndNum* newBoughtJBHSetsAndNum;
    /*
    const static std::vector<std::string> drawingBGMs;
    const std::string getRandomBGM();
*/
    
};

#endif // __SCENE_CONTROLLER_H__