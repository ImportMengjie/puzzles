#include<graphics.h>
#include<stdio.h>
#include"Menu.h"
#include<Windows.h>
#include"resource.h"


void getFilename(int level, string &str);
bool tip(View *pV);


int level;
bool is_first;

int main() throw()
{
	setinitmode(INIT_WITHLOGO);
	
	initgraph(800, 800);
	setbkcolor(WHITE);
	setcaption("拼图");
	
	SendMessageA(ege::getHWnd(), WM_SETICON, IDI_ICON1, (LPARAM)LoadIconA(getHInstance(), MAKEINTRESOURCE(IDI_ICON1)));
	
	is_first=true;
	View *view = NULL;
	FileData::read();
	
	Menu menu;
	menu.show();
	
	for (int flag=-1;is_run();flag = menu.run())
	{
		if (flag == BUTTON_NEWGAME)
		{
			delete(view);
			view = new View(2);
			level = 1;
			
			if (tip(view))//进入游戏
			{
				view->upset();
				
				while (is_run())
				{
					if (view->run())//成功,进入下一关
					{
						double time = view->getContainer().getStartTime();
						int step = view->getContainer().getStep();
						
						//保存数据.
						FileData::wirte(level, step, time);
						
						view->reDraw();
						
						level++;
						if (level == 6)
						{
							MessageBox(getHWnd(), "恭喜你已经通关,厉害呢.", "厉害呢", MB_OK);
							goto EXIT;
						}
						delete(view);
					
						view = new View(level+1);
						if (tip(view))//下一关开场
						{
							view->upset();
							continue;
						}
						else//返回菜单
						{
							is_first = true;
							menu.show();
							break;
						}
					}
					else//暂停游戏,返回菜单
					{
						view->upset();
						is_first = true;
						menu.show();
						break;
					}
					
				}
				continue;//进入菜单循环

			}
			else//进入菜单
			{
				is_first = true;
				menu.show();
				continue;
			}
			
			continue;
		}
		else if (flag == BUTTON_RESUME)
		{
			is_first = false;
			while (is_run())
			{
				if (view->run())//成功,进入下一关
				{
					double time = view->getContainer().getStartTime();
					int step = view->getContainer().getStep();

					//保存数据.
					FileData::wirte(level, step, time);
					
					level++;
					if (level == 6)
					{
						MessageBox(getHWnd(), "恭喜你已经通关,厉害呢.", "厉害呢", MB_OK);
						delete(view);
						goto EXIT;
					}
					delete(view);

					view = new View(level + 1);
					if (tip(view))//下一关开场
					{
						view->upset();
						continue;
					}
					else//返回菜单
					{
						is_first = true;
						menu.show();
						break;
					}
				}
				else//暂停游戏,返回菜单
				{
					is_first = true;
					menu.show();
					break;
				}

			}
			continue;
		}
		else if (flag == BUTTON_EXIT)
		{
			break;
		}

	}

EXIT:    delete(view);
	ege::closegraph();
}


void getFilename(int level, string &str)
{
	char c[100];
	srand((unsigned)time(NULL));
	int num = rand() % 3 + 1;
	sprintf_s(c, 100, "src\\resource\\level_%d_%d.dat", level, num);
	str = c;
	
}


bool tip(View *pV)
{
	
	string strFile;
	getFilename(level, strFile);
	pV->draw(strFile);
	for (mouse_msg msg;is_run();msg = getmouse())
	{
		if (msg.is_left() && msg.is_up())//鼠标左击进入游戏
		{
			if (is_first)
			{
				is_first = false;
				continue;
			}
				
			return true;
		}
		else if (msg.is_right()&&msg.is_up())//鼠标右击进入菜单
		{
			pV->upset();
			is_first = true;
			return false;
		}
	}
	return false;
}