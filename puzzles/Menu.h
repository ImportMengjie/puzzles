#pragma once

#include"View.h"
#include"IO.h"

#define NOW_MENU_1 0
#define NOW_MENU_2 1
#define NOW_ABOUT 2
#define NOW_RECORDS 3

#define BUTTON_RETURN 0
#define BUTTON_RESUME 1
#define BUTTON_EXIT 2
#define BUTTON_ERRO 3
#define BUTTON_NEWGAME 4


#define SMALL_X 200
#define SMALL_Y 30
class Menu;
class BNewgame;
class BResume;


class Button {
public:
	RectModel rect;
	Button(int x1, int y1, int x2, int y2, string name);
	virtual int actionPerformed(mouse_msg &msg,Menu *menu) = 0;//µã»÷ÏûÏ¢
	bool contains(int x, int y);
};

class Menu {
private:
	Button *bNewGame;
	Button *bResume;
	Button *bRecords;
	Button *bAbout;
	Button *bExit;
	Button *bReturn;
	vector<Button *> buttons_menu;
	vector<Button *> buttons_return;
	ege::PIMAGE Menu_1;
	ege::PIMAGE Menu_2;
	ege::PIMAGE About;
	ege::PIMAGE Small;
	ege::PIMAGE Records;
	ege::PIMAGE nowImg;
	bool is_menu1;
	int now;

	friend class Menu;
	friend class BNewgame;
	friend class BResume;
	friend class BResords;
	friend class BAbout;
	friend class BReturn;

public:
	Menu();
	void addButton(Button *button);
	//void removeButton(Button *button);
	void show();
	int run();
	~Menu();
};


class BResume :public Button {
public:

	BResume(int x1, int y1, int x2, int y2)
		:Button(x1,y1,x2,y2,"resume")
	{

	}
	int actionPerformed(mouse_msg &msg, Menu *menu);
};

class BNewgame :public Button {
public:
	BNewgame(int x1, int y1, int x2, int y2)
		:Button(x1, y1, x2, y2, "resume")
	{

	}
	int actionPerformed(mouse_msg &msg, Menu *menu);
};

class BResords :public Button {
public:
	BResords(int x1, int y1, int x2, int y2)
		:Button(x1, y1, x2, y2, "resume")
	{

	}

	int actionPerformed(mouse_msg &msg, Menu *menu);
};

class BAbout :public Button {
public:
	BAbout(int x1, int y1, int x2, int y2)
		:Button(x1, y1, x2, y2, "resume")
	{

	}

	int actionPerformed(mouse_msg &msg, Menu *menu);

};

class BExit :public Button {
public:
	BExit(int x1, int y1, int x2, int y2)
		:Button(x1, y1, x2, y2, "resume")
	{

	}
	int actionPerformed(mouse_msg &msg, Menu *menu)
	{
		return BUTTON_EXIT;
	}
};

class BReturn :public Button {
public:
	BReturn(int x1, int y1, int x2, int y2)
		:Button(x1, y1, x2, y2, "resume")
	{

	}
	int actionPerformed(mouse_msg &msg, Menu *menu);
};