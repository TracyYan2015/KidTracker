#include "UtilCSV.h"

using namespace cocos2d;


UtilCSV::~UtilCSV(void)
{
}

void UtilCSV::StringSplit( const string& str, vector<string>& tokens, const char& delimiters )
{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos-lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void UtilCSV::split( vector<string>& field, string line )
{
    string fld;
    unsigned int i,j=0;

    if( line.length() ==0 )
        return;
    i=0;

    do 
    {
        if(j<line.length() && line[i]=='"')
            j = advquoted(line, fld, ++i);
        else
            j = advplain(line, fld, i);
        
        field.push_back(fld);
        i = j+1;

    } while (j<line.length());
}

int UtilCSV::advplain( const string& s, string& fld, int i)
{
    unsigned int j;
    j = s.find_first_of(fieldsep, i);
    if(j>s.length())
        j=s.length();
    fld = string(s,i,j-i);
    return j;
}

int UtilCSV::advquoted( const string& s, string& fld, int i)
{
    unsigned int j;
    fld = "";
    for (j=i; j<s.length(); ++j)
    {
        if(s[j]=='"' && s[++j]!='"')
        {
            unsigned int k = s.find_first_of(fieldsep, j);
            if(k>s.length())
                k = s.length();
            for(k-=j; k-->0;)
                fld += s[j++];
            break;
        }
        fld += s[j];
    }
    return j;
}

//解析 CVS 文件
bool UtilCSV::openFile( const char* fileName )
{
    string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    unsigned char* pBuffer = nullptr;
    ssize_t bufferSize = 0;
    // pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pathKey.c_str(), "r", &bufferSize);
	pBuffer = FileUtils::getInstance()->getFileData(pathKey.c_str(), "r", &bufferSize);

    string s = (char*)pBuffer;
    string str = s.substr(0,bufferSize);

    vector<string> line;
    StringSplit(str, line, '\n');
    for(unsigned int i=0; i<line.size(); ++i)
    {
        vector<string> field;
        split(field, line[i]);

		// 去除列末字段中的\r
		if ( (field.size() - 1) >= 0 )
			cleanR(field[ field.size()-1 ]);

        data.push_back(field);
        cols = max(cols, (int)field.size());
    }

    return true;
}

const char* UtilCSV::getData(unsigned int rows, unsigned int cols) 
{
    if (rows<0 || rows>=data.size() || cols<0 || cols>=data[rows].size())
    {
        return "";
    }
    return data[rows][cols].c_str();
}


void UtilCSV::cleanR(std::string& str)
{
	if (str.find_last_of("\r") == str.size() - 1)
	{
		str = str.substr(0, str.size() - 1);
	}
}


//获取指定数据的列下标
int UtilCSV::findColsData( int cols, const char* value )
{
    for (unsigned int i=0; i<data.size(); ++i)
    {
        if(strcmp(getData(i,cols),value)==0)
            return i;
    }
    return -1;
}


int UtilCSV::getDataStartRowIndex()
{
	return _rowIndexData;
}

const char* UtilCSV::findColByName(unsigned int row, const char* name)
{
	if (row >= data.size()) return nullptr;
	
	auto names = data[_rowIndexName];

	int col = 0;
	for (auto it = names.begin(); it != names.end(); ++it)
	{
		std::string& val = *it;
		if (*it == name)
		{
			return  data[row][col].c_str();
		}
		++col;
	}
	
	return nullptr;
}

int UtilCSV::getInt32(unsigned int row, const char* name)
{
	const char* str = findColByName(row, name);
	int val = -1;
	sscanf(str, "%d", &val);
	return val;
}

float UtilCSV::getFloat32(unsigned int row, const char* name)
{
	const char* str = findColByName(row, name);
	float val = -1;
	sscanf(str, "%f", &val);
	return val;
}

double UtilCSV::getDouble64(unsigned int row, const char* name)
{
	const char* str = findColByName(row, name);
	double val = -1;
	sscanf(str, "%lf", &val);
	return val;
}

const char* UtilCSV::getString(unsigned int row, const char* name)
{
	return findColByName(row, name);
}
