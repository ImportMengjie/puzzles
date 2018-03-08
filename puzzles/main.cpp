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
	setcaption("ƴͼ");
	
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
			
			if (tip(view))//������Ϸ
			{
				view->upset();
				
				while (is_run())
				{
					if (view->run())//�ɹ�,������һ��
					{
						double time = view->getContainer().getStartTime();
						int step = view->getContainer().getStep();
						
						//��������.
						FileData::wirte(level, step, time);
						
						view->reDraw();
						
						level++;
						if (level == 6)
						{
							MessageBox(getHWnd(), "��ϲ���Ѿ�ͨ��,������.", "������", MB_OK);
							goto EXIT;
						}
						delete(view);
					
						view = new View(level+1);
						if (tip(view))//��һ�ؿ���
						{
							view->upset();
							continue;
						}
						else//���ز˵�
						{
							is_first = true;
							menu.show();
							break;
						}
					}
					else//��ͣ��Ϸ,���ز˵�
					{
						view->upset();
						is_first = true;
						menu.show();
						break;
					}
					
				}
				continue;//����˵�ѭ��

			}
			else//����˵�
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
				if (view->run())//�ɹ�,������һ��
				{
					double time = view->getContainer().getStartTime();
					int step = view->getContainer().getStep();

					//��������.
					FileData::wirte(level, step, time);
					
					level++;
					if (level == 6)
					{
						MessageBox(getHWnd(), "��ϲ���Ѿ�ͨ��,������.", "������", MB_OK);
						delete(view);
						goto EXIT;
					}
					delete(view);

					view = new View(level + 1);
					if (tip(view))//��һ�ؿ���
					{
						view->upset();
						continue;
					}
					else//���ز˵�
					{
						is_first = true;
						menu.show();
						break;
					}
				}
				else//��ͣ��Ϸ,���ز˵�
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
		if (msg.is_left() && msg.is_up())//������������Ϸ
		{
			if (is_first)
			{
				is_first = false;
				continue;
			}
				
			return true;
		}
		else if (msg.is_right()&&msg.is_up())//����һ�����˵�
		{
			pV->upset();
			is_first = true;
			return false;
		}
	}
	return false;
}