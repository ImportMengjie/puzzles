#include"View.h"

View::View(int bouder)
	:m_container(bouder)
{
	img = newimage(PHOTO_SIZE,PHOTO_SIZE);
	m_container.setStartTime(0);
}

void View::draw(string fileStr)
{
	getimage(img, fileStr.c_str());
	putimage(START_X, START_Y, img);

	for (int a = 0;a < (m_container.getBouder()*m_container.getBouder());a++)
	{
		block *b=new block(a, m_container.getBouder());
		m_block.push_back(b);
	}
}



void View::upset()
{
	m_container.random();
	reDraw();
}

void View::reDraw()
{
	cleardevice();
	vector<int> photo = m_container.getPhoto();
	
	for (int a = 0;a < (m_container.getBouder()*m_container.getBouder());a++)
	{
		int *arr = NULL;
		int t = (photo)[a];
		arr = block::getNumLocation(a, this->m_container.getBouder());
		putimage(arr[0], arr[1], this->m_block[t]->getImg());
		delete(arr);
	}

	int side = PHOTO_SIZE / m_container.getBouder();
	for (int a = 0;a < ((m_container.getBouder() - 1) * 2);a++)
	{
		setlinestyle(SOLID_LINE);
		setcolor(WHITE);
		setlinewidth(200);
		line(START_X + side*(a + 1), 0, START_X + side*(a + 1), 800);
		line(0, START_Y + side*(a + 1), 800, START_Y + side*(a + 1));
	}
}

void View::reDraw(int except)
{
	cleardevice();
	vector<int> photo = m_container.getPhoto();
	int side = PHOTO_SIZE / m_container.getBouder();
	for (int a = 0;a < (m_container.getBouder()*m_container.getBouder());a++)
	{
		int *arr = NULL;
		int t = (photo)[a];
		arr = block::getNumLocation(a, this->m_container.getBouder());
		if (a == except)
		{
			setfillcolor(WHITE);
			bar(arr[0], arr[1], arr[0] + side, arr[1] + side);
		}
		else
			putimage(arr[0], arr[1], this->m_block[t]->getImg());
		delete(arr);
	}

	
	for (int a = 0;a < ((m_container.getBouder() - 1) * 2);a++)
	{
		setlinestyle(SOLID_LINE);
		setcolor(WHITE);
		setlinewidth(200);
		line(START_X + side*(a + 1), 0, START_X + side*(a + 1), 800);
		line(0, START_Y + side*(a + 1), 800, START_Y + side*(a + 1));
	}
}


bool View::set(int f, int s)
{
	bool B=this->m_container.set(f, s);
	reDraw();
	return B;
}

bool View::run()
{
	bool trade = false;
	bool follow = false;
	int num=-1;
	int distanceX = -1;
	int distanceY = -1;
	int centerDX = -1;
	int centerDY = -1;
	int nextNum = -1;
	double startTime = ege::fclock();
	double time = this->m_container.getStartTime();

	setlinewidth(20);
	setlinestyle(SOLID_LINE);
	setcolor(RED);
	
	int side = (PHOTO_SIZE / this->m_container.getBouder());
	for (mouse_msg msg;is_run();msg = getmouse())
	{
		vector<int> photo = m_container.getPhoto();
		if (msg.is_left() && msg.is_up() && num>=0 && !msg.is_move())//拖动完成
		{
			
			nextNum = block::getLocationNum(msg.x, msg.y, this->m_container.getBouder());
			if (nextNum < 0)
			{
				trade = false;
				follow = false;
				nextNum = -1;
				centerDY = -1;
				centerDX = -1;
				distanceY = -1;
				distanceX = -1;
				num = -1;
				this->reDraw();
				continue;
			}
				
			if (this->set(num, nextNum))
			{
				time += (ege::fclock() - startTime);
				m_container.setStartTime(time);
				return true;
			}
				
			trade = false;
			follow = false;
			nextNum = -1;
			centerDY = -1;
			centerDX = -1;
			distanceY = -1;
			distanceX = -1;
			num = -1;
			continue;
		}

		if (msg.is_left() && msg.is_down() && num<0 && !follow && !msg.is_up() && !msg.is_right() && !msg.is_move())//按下左键准备拖动
		{
			num = block::getLocationNum(msg.x, msg.y, this->m_container.getBouder());
			if (num < 0)
				continue;
			else
			{
				int *arr = block::getNumLocation(num, this->m_container.getBouder());
				distanceX = msg.x - arr[0];
				distanceY = msg.y - arr[1];
				centerDX = (START_X + arr[0] + 0.5*side) - msg.x;
				centerDY = (START_Y + arr[1] + 0.5*side) - msg.y;
				follow = true;
				trade = true;
			}
			continue;	
		}

		if (msg.is_move() && follow && num >= 0)//拖动中
		{
			this->reDraw(num);
			nextNum = block::getLocationNum(msg.x, msg.y, this->m_container.getBouder());
			int *a = block::getNumLocation(nextNum, this->m_container.getBouder());
			ege::setlinewidth(5);
			ege::setcolor(WHITE);
			rectangle(a[0], a[1], a[0] + side, a[1] + side);
			//putimage(msg.x-distanceX,msg.y-distanceY,this->m_block[photo[num]]->getImg());
			putimage_alphablend(NULL, this->m_block[photo[num]]->getImg(), msg.x - distanceX, msg.y - distanceY, 0x80);
			delete a;
			continue;
		}
		
		

		if (msg.is_right() && msg.is_down())//按下右键返回
		{
			time += (ege::fclock() - startTime);
			m_container.setStartTime(time);
			return false;
		}

		//if (msg.is_move() && !msg.is_down() && !trade)//移动鼠标
		//{
		//	if (msg.x > PHOTO_SIZE || msg.y > PHOTO_SIZE)
		//	{
		//		this->reDraw();
		//		continue;
		//	}
		//	int tNum = block::getLocationNum(msg.x, msg.y, this->m_container.getBouder());
		//	if (tNum < 0 || tNum > (this->m_container.getBouder() ^ 2));
		//	{
		//		this->reDraw();
		//		continue;
		//	}
		//	int *a = block::getNumLocation(tNum, this->m_container.getBouder());
		//	this->reDraw();
		//	//putimage(a[0] - side*0.1, a[1] - side*0.1,  side*1.1, side*1.1, this->m_block[photo[tNum]]->getImg(), 0, 0, side, side);
		//	ege::setlinewidth(3);
		//	ege::setcolor(WHITE);
		//	ege::rectangle(a[0], a[1], a[0] + side, a[1] + side);
		//	delete a;
		//	continue;
		//}

			
	}

	return false;

	
}



View::~View()
{
	delimage(img);
	for (int a = 0;a < m_block.size();a++)
	{
		delete(m_block[a]);
	}

}





int* block::getNumLocation(int num,int bouder)
{
	if (num >= (bouder*bouder))
		return NULL;
	int side = PHOTO_SIZE / bouder;
	int *a = new int[2];
	a[0] = 0;
	a[1] = 0;
	num++;
	int t = num%bouder;
	int t2 = num / bouder;
	if (t == 0)
	{
		a[0] = START_X + side*(bouder-1);
		a[1] = START_Y + (t2-1)*side;
		
	}
	else
	{
		a[0] = START_X + side*(t - 1);
		a[1] = START_Y + t2*side;
	}
	return a;
}

int block::getLocationNum(int x, int y, int bouder)
{
	if (x > PHOTO_SIZE || y > PHOTO_SIZE || x < 0 || y < 0)
		return -1;

	int side = PHOTO_SIZE / bouder;
	x -= START_X;
	y -= START_Y;
	if (x <= side)
		x = 0;
	if (y <= side)
		y = 0;
	x = (x - (x%side));
	y = (y - (y%side));

	int tx = x / side;
	int ty = y / side;



	return tx + ty*bouder;
}


block::block(int num1,int bouder)
{
	num = num1;
	img = newimage();
	sideLength = PHOTO_SIZE / bouder;
	int *a = block::getNumLocation(num1, bouder);
	getimage(img, a[0], a[1], sideLength, sideLength);
	delete(a);
}

