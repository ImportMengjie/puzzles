#include "IO.h"

string FileData::fileName = "src/data.dat";
Record FileData::record[5] = {Record(1),Record(2),Record(3),Record(4),Record(5)};


Record::Record(int level)
{
	this->level = level;
	this->x = 208;
	this->step = 0;
	this->time = 0;
	if (level == 1)
	{
		this->y = 116;
	}
	else if (level == 2)
		this->y = 235;
	else if (level == 3)
		this->y = 347;
	else if (level == 4)
		this->y = 453;
	else if (level == 5)
		this->y = 554;
	else
		this->y = 0;
}

bool FileData::saveToFile(FILE * fp)
{
	int count = fwrite(FileData::record, sizeof(Record), 5, fp);
	if (count == 5)
		return true;
	else
		return false;
}

bool FileData::saveToClass(FILE * fp)
{
	int count = fread(FileData::record, sizeof(Record), 5, fp);
	if (count == 5)
		return true;
	else
	    return false;
}

void FileData::read()
{
	FILE *fp = fopen(fileName.c_str(), "rb");
	if (fp == NULL)//�ļ�������
	{
		fp = fopen(fileName.c_str(), "w+b");
		saveToFile(fp);
	}
	else//�ļ�����
	{
		saveToClass(fp);
	}
	fclose(fp);
}

void FileData::wirte(int level,int step, int time)
{
	char text[200] = {0};
	bool temp=true;

	if (FileData::record[level - 1].step == 0 || FileData::record[level - 1].step > step)
	{
		FileData::record[level - 1].step = step;
		temp = false;
	}
	
	if (FileData::record[level - 1].time == 0 || FileData::record[level - 1].time > time)
	{
		FileData::record[level - 1].time = time;
		temp = false;
	}

	if (FileData::record[level - 1].step <= step&&FileData::record[level - 1].time <= time&&temp)
	{
		sprintf_s(text, 200, "��ϲ��ͨ����%d��,��ʱ:%d��%d��,����:%d.��δ���Ƽ�¼.", level, time/60,time%60, step);
		MessageBox(ege::getHWnd(), text, "�ɹ�", MB_OK);
		return;
	}
	FILE *fp = fopen(FileData::fileName.c_str(), "w+b");
	saveToFile(fp);
	fclose(fp);
	sprintf_s(text, 200, "��ϲ��ͨ����%d��,��ʱ:%d��%d��,����:%d.�����Ƽ�¼.������!", level, time / 60, time % 60, step);
	MessageBox(ege::getHWnd(), text, "��ϲ", MB_OK);
	
}
