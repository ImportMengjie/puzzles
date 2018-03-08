#pragma once
/*
一个vector 其一是切割图片编码.
*/

//random随机函数 将切割图片的编码随机排列.
//bool set(int ,int) 将俩个vector中元素交换位置,并判断是否顺序排列,如顺序排列则返回true.
//
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;

class container{
private:
	vector<int> photo;
	int step;
	int bouder;
	double startTime;
	

public:

	container(int bouder);

	void random();


	bool set(int f, int s);
	
	void setStartTime(double time)
	{
		this->startTime = time;
	}
	double getStartTime()
	{
		return this->startTime;
	}

	vector<int> getPhoto()
	{
		return photo;
	}

	int getStep()
	{
		return step;
	}
	int getBouder()
	{
		return bouder;
	}

};


class RectModel {
private:
	string name;
	
public:
	int x1, y1, x2, y2;//x1,y1 必须为左上顶点
	int high, wide;
	RectModel(int x1, int y1, int x2, int y2,string name="")
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
		this->name = name;
		high = abs(y1 - y2);
		wide = abs(x1 - x2);
	}

	RectModel()
	{
		this->x1 = -1;
		this->x2 = -1;
		this->y1 = -1;
		this->y2 = -1;
		this->name = "";
		high = -1;
		wide = -1;
	}

	void setName(string name)
	{
		this->name = name;
	}

	string getName()
	{
		return name;
	}

	void set(int x1, int y1, int x2, int y2, string name = "")
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
		this->name = name;
		high = abs(y1 - y2);
		wide = abs(x1 - x2);
	}

	bool contains(int x, int y)
	{
		if (x > x1 && x < x2 && y > y1 && y < y2)
			return true;
		else
			return false;
	}
};
