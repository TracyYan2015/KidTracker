#ifndef __UTIL_CSV_H__
#define __UTIL_CSV_H__

#include "cocos2d.h"
#include <vector>
#include <iostream>

using namespace std;

/*
[0] 表头
[1] 属性	id	name
[2] 类型	int	string
[3] 注释
[4] 描述
[5]		1	sonikk
[6]		2	索尼克
[7]		3	kk
*/

class UtilCSV
{
public:

	UtilCSV(istream& fin = cin, string sep = ",")
		: _rowIndexName(1)
		, _rowIndexType(2)
		, _rowIndexData(5)
		, fieldsep(sep)
		, cols(0)
	{

	}

	virtual ~UtilCSV(void);



	bool openFile(const char* fileName);
	void cleanR(std::string& str); // 去除\r
	int findColsData(int cols, const char* value);

	inline int getCols(){ return cols; }
	inline int getRows(){ return data.size(); };

	//获取指定行列的数据
	const char* getData(unsigned int rows, unsigned int cols);

	// 获取数据起始行偏移量
	int getDataStartRowIndex();
	const char* findColByName(unsigned int row, const char* name);
	int getInt32(unsigned int row, const char* name);
	float getFloat32(unsigned int row, const char* name);
	double getDouble64(unsigned int row, const char* name);
	const char* getString(unsigned int row, const char* name);


	//用以存储数据
	std::vector<std::vector<std::string>> data;


private:

	short _rowIndexName; // 名称字段行偏移量(从0开始) 默认为1
	short _rowIndexType; // 类型字段行偏移量(从0开始) 默认为2
	short _rowIndexData; // 有效数据存放区域行偏移量(从0开始) 默认为5

	string fieldsep;
	int cols;

	void StringSplit(const string& str, vector<string>& tokens, const char& delimiters);
	void split(vector<string>& field, string line);
	int advplain(const string& line, string& fld, int);
	int advquoted(const string& line, string& fld, int);

};

#endif //__UTIL_CSV_H__