#pragma once
#include <stdio.h>
#include <string>
#include<graphics.h>

using namespace std;

class Record {	
public:
	int level;
	int step;
	int time;
	int x, y;
	Record(int level);

};

class FileData {
private:
	static string fileName;
	
	static bool saveToFile(FILE *fp) throw();
	static bool saveToClass(FILE *fp) throw();
	FileData();
public:
	static Record record[5];
	static void read() throw();
	static void wirte(int level,int step, int time) throw();
	
};