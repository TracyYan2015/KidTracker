//
//  SceneTitleUserData.cpp
//  KidTracer
//
//  Created by user on 14-10-14.
//
//

#include "SceneTitleUserData.h"


SceneTitleUserData* SceneTitleUserData::getInstance(SceneTitle *sceneTitle){
    SceneTitleUserData* data = new SceneTitleUserData();
    data->setSceneData(sceneTitle->scene_id, sceneTitle->sceneIdTemp,sceneTitle->sceneVectorId,sceneTitle->sceneVectorIdTemp);
    data->setElfData1(sceneTitle->elf_id, sceneTitle->elfIdTemp, sceneTitle->elf_id_vector, sceneTitle->elfIdVectorTemp);
    data->setElfData2(sceneTitle->elfs, sceneTitle->elfsSize,sceneTitle->selected_elf_id);
    data->setJBHData1(sceneTitle->stickFigure_id, sceneTitle->stickfigureIdTemp, sceneTitle->stickFigure_id_vector, sceneTitle->stickFigureIdVectorTemp);
    data->setJBHData2(sceneTitle->squareBlueRingId, sceneTitle->squareBlueRingIdTemp, sceneTitle->jbhName, sceneTitle->jbhNameTemp, sceneTitle->stickFigureSize);
    data->setLocalJBHData(sceneTitle->localJBHStrings);
    
    return data;
    
}

SceneTitleUserData::SceneTitleUserData()
{
    
}
void SceneTitleUserData::setSceneData(int id, int idTemp,int vectorId,int vectorIdTemp)
{
    sceneIdTemp = idTemp;
    scene_id = id;
    sceneVectorId = vectorId;
    sceneVectorIdTemp = vectorIdTemp;
    
}
void SceneTitleUserData::setElfData1(int id, int idTemp, int idVector, int idVectorTemp)
{
    elf_id = id;
    elf_id_vector = idVector;
    elfIdTemp = idTemp;
    elfIdVectorTemp = idVectorTemp;
}
void SceneTitleUserData::setElfData2(Vector<ImageView*> elfs
                 ,int size
                 ,int selected_elf_id)
{
    this->elfs = elfs;
    elfsSize = size;
    this->selected_elf_id = selected_elf_id;
}

void SceneTitleUserData::setJBHData1(int stickFigure_id
                 ,int stickfigureIdTemp
                 ,int stickFigure_id_vector//0 ~ 40
                 ,int stickFigureIdVectorTemp)
{
    this->stickFigure_id = stickFigure_id;
    this->stickfigureIdTemp =stickfigureIdTemp;
    this->stickFigure_id_vector= stickFigure_id_vector;//0 ~ 40
    this->stickFigureIdVectorTemp = stickFigureIdVectorTemp;
}

void SceneTitleUserData::setJBHData2(int squareBlueRingId//1~3
                 ,int squareBlueRingIdTemp
                 ,std::string jbhName//从简笔画的下面三幅图得到的文件名
                 ,std::string jbhNameTemp
                 ,int stickFigureSize)
{
    this->squareBlueRingId = squareBlueRingId;//1~3
    this->squareBlueRingIdTemp = squareBlueRingIdTemp;
    this->jbhName = jbhName;//从简笔画的下面三幅图得到的文件名
    this->jbhNameTemp = jbhNameTemp;
    this->stickFigureSize = stickFigureSize;
}

void SceneTitleUserData::printData()
{
    CCLOG("JBH id is %d", stickFigure_id);
    CCLOG("sceneVectorId %d, sceneVectorIdTemp %d",sceneVectorId,sceneVectorIdTemp);
}

Vector<__String*> SceneTitleUserData::getLocalJBHData()
{
    return localJBHData;
}


void SceneTitleUserData::setLocalJBHData(Vector<__String*> data)
{
    this->localJBHData = data;
}


