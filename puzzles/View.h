#pragma once
#include<graphics.h>
#include"container.h"
#include<string>
#include <math.h>
#define PHOTO_SIZE  800
#define START_X 0
#define START_Y 0



class block {
private:
	int num;
	PIMAGE img;
	int sideLength;
public:
	block(int num1, int bouder);
	static int* getNumLocation(int num, int bouder);//ע��delect����ֵ
	static int getLocationNum(int x, int y, int bouder);
	PIMAGE getImg()
	{
		return img;
	}
	int getNum()
	{
		return num;
	}
	int getSideLength()
	{
		return sideLength;
	}
	~block()
	{
		delimage(img);
	}
};



class View {
private:
	container m_container;
	PIMAGE img;
	vector<block*> m_block;

public:
	View(int bouder);
	void draw(string);//����ԭͼ��,����block��ʼ��.
	void upset();
	~View();
	void reDraw();
	bool set(int f, int s);
	bool run();
	void reDraw(int except);
	container & getContainer()
	{
		return m_container;
	}
};





