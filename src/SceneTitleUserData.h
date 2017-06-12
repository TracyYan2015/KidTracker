//
//  SceneTitleUserData.h
//  KidTracer
//
//  Created by user on 14-10-14.
//
//

#ifndef __KidTracer__SceneTitleUserData__
#define __KidTracer__SceneTitleUserData__

#include <iostream>
#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneTitle.h"



using namespace cocos2d;
using namespace ui;


class SceneTitleUserData
{
public:
    
    static SceneTitleUserData* getInstance(SceneTitle* sceneTitle);
    SceneTitleUserData();
    
    
    //用户在每次进入设置中购买简笔画的时候，都将当前本地的plist中简笔画中的数据保存在这里
    Vector<__String*> getLocalJBHData();
    void setLocalJBHData(Vector<__String*> data);
    
    
    void setSceneData(int _id, int idTemp, int vectorId, int vectorIdTemp);
    
    void setElfData1(int _id, int idTemp, int idVector, int idVectorTemp);
    void setElfData2(Vector<ImageView*> elfs
                     ,int elfsSize
                     ,int selected_elf_id);
    
    void setJBHData1(int stickFigure_id
                     ,int stickfigureIdTemp
                     ,int stickFigure_id_vector//0 ~ 40
                     ,int stickFigureIdVectorTemp);
    
    void setJBHData2(int squareBlueRingId//1~3
                     ,int squareBlueRingIdTemp
                     ,std::string jbhName//从简笔画的下面三幅图得到的文件名
                     ,std::string jbhNameTemp
                     ,int stickFigureSize);
    
    

    void printData();
    

    int scene_id;  //1～3
    int sceneIdTemp;
    int sceneVectorId;
    int sceneVectorIdTemp;
    
    int elf_id;// 1~3
    int elfIdTemp;
    int elf_id_vector; //0~2
    int elfIdVectorTemp;
    Vector<ImageView*> elfs;
    int elfsSize;
    int selected_elf_id;//传递给引导模式，用于随机精灵
    
    
    int stickFigure_id;
    int stickfigureIdTemp;
    int stickFigure_id_vector;//0 ~ 40
    int stickFigureIdVectorTemp;
    int squareBlueRingId;//1~3
    int squareBlueRingIdTemp;
    std::string jbhName;//从简笔画的下面三幅图得到的文件名
    std::string jbhNameTemp;
    int stickFigureSize;
    
    Vector<__String*> localJBHData;
    
};
#endif /* defined(__KidTracer__SceneTitleUserData__) */
