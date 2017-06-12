#include "SceneController.h"
#include "SceneTitle.h"
#include "SceneModeGuid.h"
#include "SceneModeGuidDraw.h"
#include "SceneRenderTextureTest.h"
#include "SceneElfDialog.h"
#include "SceneDialog.h"
#include "SceneStickFigureDialog.h"
#include "HelloWorldScene.h"
#include "SceneHuacedialog.h"
#include "SceneBigHuaceDialog.h"
#include "SceneSetupDialog.h"
#include "SceneModeFreeDraw.h"
#include "SceneHaceDeleteDialog.h"
#include "SceneModeGuidStroke.h"

#define CASE(className) case eSceneId##className: \
	sceneLayer = className::create(); break;



SceneController* SceneController::getInstance()
{
	static SceneController s_instance;
	return &s_instance;
}

Scene* SceneController::createScene(Layer* layer)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}




Layer* SceneController::getSceneById(int scene_id)
{
	Layer* sceneLayer = nullptr;

    
    switch (scene_id)
	{
		CASE(SceneTitle)
		CASE(SceneModeGuid)
		CASE(SceneModeGuidDraw)
		CASE(SceneRenderTextureTest)
        CASE(SceneElfDialog)
        CASE(SceneDialog)
        CASE(SceneStickFigureDialog)
        CASE(HelloWorld)
        CASE(SceneHuaceDialog)
            if(scene_id == eSceneIdHelloWorld){
                sceneLayer = SceneTitle::create(); break;
            }
            
        CASE(SceneBigHuaceDialog)
        CASE(SceneSetupDialog)
        CASE(SceneModeFreeDraw)
        CASE(SceneHaceDeleteDialog)
        CASE(SceneModeGuidStroke)
	}

	return sceneLayer;
}

void SceneController::startScene(int scene_id)
{
	auto director = Director::getInstance();

	Scene* scene = createScene(getSceneById(scene_id));

	// run
	director->runWithScene( scene );
}

void SceneController::replaceScane(int scene_id)
{
	auto director = Director::getInstance();

	//TransitionFade* tScene = TransitionFade::create(0.5f, createScene(getSceneById(scene_id)));
	
	director->replaceScene(createScene(getSceneById(scene_id)));
}


void SceneController::addScene(Node *parent, int scene_id)
{
    parent->addChild(createScene(getSceneById(scene_id)),10);
}


