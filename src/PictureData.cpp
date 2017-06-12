#include "PictureData.h"

#include "Util.h"


void PictureData::setPath(std::string path)
{
    mh_picData=path;
    
}

PictureData::PictureData():
mh_picData("data/point/laoshu/laoshu_001.txt")
{
    
}
void PictureData::loadStrokeData(){
	unsigned char* buf = NULL;
	ssize_t bufferSize = 0;
	buf = FileUtils::getInstance()->getFileData(mh_picData, "r", &bufferSize);
    if(buf == nullptr){
        buf = FileUtils::getInstance()->getFileData("data/point/laoshu/laoshu_001.txt", "r", &bufferSize);}
	std::string str = std::string(reinterpret_cast<char*>(buf));
	std::vector<std::string> str_lines;
	Util::strSplit(str, "\r\n", str_lines);
	this->strokes.clear();int id = 0;
	StrokeData* pre_sd = nullptr;
	StrokeData* cur_sd = nullptr;
	for (auto it = str_lines.begin(); it != str_lines.end(); ++it){
		if (*it == ""){continue;}
		else if ((*it).find("stroke") != std::string::npos){
			std::string str_id = Util::strSplitAt((*it), "#", 1);
			id = Util::str_to_int(str_id);
			bool isEnd = false;
			if (id >= 0){
				pre_sd = cur_sd;
				StrokeData* sd = new StrokeData();
				this->strokes.push_back(sd);
				cur_sd = sd;
				if (id > 0){isEnd = true;}
			}else{
				isEnd = true;
				pre_sd = cur_sd;
			}
			if (isEnd){pre_sd->isWait = (pre_sd->pos.size() == 1) ? true : false;}
		}
		else if ((*it).find(",") != std::string::npos){
			Vec2 pos = Util::str_to_point(*it);
			cur_sd->pos.push_back(pos);
		}
	}
	CC_SAFE_DELETE(buf);
}
