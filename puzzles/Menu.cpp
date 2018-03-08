#include "Menu.h"

Button::Button(int x1, int y1, int x2, int y2, string name)
	:rect(x1, y1, x2, y2, name)
{
	
}

bool Button::contains(int x, int y)
{
	return rect.contains(x, y);
}






Menu::Menu()
{
	this->Menu_1 = newimage(PHOTO_SIZE, PHOTO_SIZE);
	getimage(Menu_1, "src\\menu_1.dat");
	this->Menu_2 = newimage(PHOTO_SIZE, PHOTO_SIZE);
	getimage(Menu_2, "src\\menu_2.dat");
	this->About = newimage(PHOTO_SIZE, PHOTO_SIZE);
	getimage(About, "src\\about.dat");
	this->Records = newimage(PHOTO_SIZE, PHOTO_SIZE);
	getimage(Records, "src\\records.dat");
	this->Small = newimage();
	getimage(Small, "src\\small.dat");

	this->bNewGame = new BNewgame(102, 103, 297, 156);
	this->bAbout = new BAbout(102, 379, 295, 436);
	this->bExit = new BExit(145, 562, 239, 602);
	this->bResume = new BResume(132, 21, 268, 68);
	this->bRecords = new BResords(105, 251, 298, 306);
	this->bReturn = new BReturn(600, 700, 718, 746);

	this->buttons_menu.push_back(bNewGame);
	this->buttons_menu.push_back(bAbout);
	this->buttons_menu.push_back(bExit);
	this->buttons_menu.push_back(bRecords);

	this->buttons_return.push_back(bReturn);

	this->is_menu1 = true;
	this->now = NOW_MENU_1;
	this->nowImg = Menu_1;



}

void Menu::addButton(Button * button)
{
	this->buttons_menu.push_back(button);
}





void Menu::show()
{
	putimage(0, 0, nowImg);
}

int Menu::run()
{
	vector<Button *> *pButton = NULL;


	for (mouse_msg msg;is_run();msg = getmouse())
	{
		int button_sideX = 0;
		int button_sideY = 0;
		



		if (now == NOW_MENU_1 || now == NOW_MENU_2)
			pButton = &this->buttons_menu;
		else if (now == NOW_ABOUT || now == NOW_RECORDS)
			pButton = &this->buttons_return;
		else
			return BUTTON_ERRO;

		if (msg.is_left() && msg.is_down())//鼠标单击消息
		{
			for (int a = 0;a < (*pButton).size();a++)
			{
				if ((*pButton)[a]->contains(msg.x, msg.y))
				{
					int flag = (*pButton)[a]->actionPerformed(msg, this);
					if (flag == BUTTON_NEWGAME)
					{
						return BUTTON_NEWGAME;
					}
					else if (flag == BUTTON_RESUME)
					{
						return BUTTON_RESUME;
					}
					else if (flag == BUTTON_RETURN)
					{
						
						continue;
					}
					else if (flag == BUTTON_EXIT)
					{
						return BUTTON_EXIT;
					}
					else
						continue;
				}
				else
					continue;
			}

			continue;
		
		}

		if (msg.is_move() && !msg.is_down() && !msg.is_up() && !msg.is_left() && !msg.is_up())//鼠标移动
		{
			for (int a = 0;a < (*pButton).size();a++)
			{
				
				if ((*pButton)[a]->contains(msg.x, msg.y))
				{
					this->show();
					button_sideX = (SMALL_X - ((*pButton)[a]->rect.x2 - (*pButton)[a]->rect.x1))*0.5;
					button_sideY = (SMALL_Y - ((*pButton)[a]->rect.y2 - (*pButton)[a]->rect.y1))*0.5;
					putimage_alphablend(NULL, this->Small, (*pButton)[a]->rect.x1 - button_sideX, (*pButton)[a]->rect.y1 - button_sideY, 0x88);
					break;
				}
				else
					this->show();
			}
		}



	}
}




Menu::~Menu()
{
	delimage(Menu_1);
	delimage(Menu_2);
	delimage(Records);
	delimage(Small);
	delimage(About);
	delete(this->bAbout);
	delete(this->bExit);
	delete(this->bNewGame);
	delete(this->bRecords);
	delete(this->bResume);
	delete(this->bReturn);
}



int BResume::actionPerformed(mouse_msg & msg, Menu * menu)
{

	return BUTTON_RESUME;
}



int BNewgame::actionPerformed(mouse_msg & msg, Menu * menu)
{
	menu->is_menu1 = false;
	menu->addButton(menu->bResume);
	menu->now = NOW_MENU_2;
	menu->nowImg = menu->Menu_2;
	return BUTTON_NEWGAME;
}

int BResords::actionPerformed(mouse_msg & msg, Menu * menu)
{
	menu->now = NOW_RECORDS;
	menu->nowImg = menu->Records;
	//画纪录,保存img,show()
	menu->show();
	setcolor(WHITE);
	//setfont(-25, 0, "Consolas");
	setfont(-25, 0, "微软雅黑");
	setfontbkcolor(BLACK);
	for (int a = 0;a < 5;a++)
	{
		
		xyprintf(FileData::record[a].x+5, FileData::record[a].y+8, "%02d", FileData::record[a].time / 60);
		xyprintf(FileData::record[a].x+66, FileData::record[a].y+8, "%02d", FileData::record[a].time % 60);
		xyprintf(FileData::record[a].x+270, FileData::record[a].y + 8, "%5d", FileData::record[a].step);
	}
	PIMAGE newImg=newimage(PHOTO_SIZE, PHOTO_SIZE);
	getimage(newImg, START_X, START_Y, PHOTO_SIZE, PHOTO_SIZE);
	delimage(menu->Records);
	menu->Records = newImg;
	menu->nowImg = newImg;
	return BUTTON_RETURN;
}

int BAbout::actionPerformed(mouse_msg & msg, Menu * menu)
{
	menu->now = NOW_ABOUT;
	menu->nowImg = menu->About;
	menu->show();
	return BUTTON_RETURN;
}

int BReturn::actionPerformed(mouse_msg & msg, Menu * menu)
{
	if (menu->is_menu1)
	{
		menu->now = NOW_MENU_1;
		menu->nowImg = menu->Menu_1;
	}
	else
	{
		menu->now = NOW_MENU_2;
		menu->nowImg = menu->Menu_2;
	}
	return BUTTON_RETURN;
}
