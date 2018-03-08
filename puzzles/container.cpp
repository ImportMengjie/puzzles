#include"container.h"

container::container(int bouder)
{
	for (int a = 0;a < (bouder*bouder);a++)
	{
		photo.push_back(a);
	}
	step = 0;
	this->bouder = bouder;
	this->startTime = -1;
}

void container::random()
{
	step = 0;
	srand((unsigned)time(NULL));
	//1-size();
	for (int a = 0;a < photo.size();a++)
	{
		int number = rand() % photo.size();
		int t = 0;
		t = photo[a];
		photo[a] = photo[number];
		photo[number] = t;
	}

	for (int a = 0;a < photo.size();a++)
	{
		if (a == (photo.size() - 1))
		{
			this->random();
			return;
		}
			
		if (photo[a] != (photo[a + 1] - 1))
			return;
		else
			continue;
	}


}

bool container::set(int f, int s)
{
	if (f == s)
		return false;
	step++;
	int t = 0;
	t = photo[f];
	photo[f] = photo[s];
	photo[s] = t;

	for (int a = 0;a < photo.size();a++)
	{
		if (a == (photo.size() - 1))
			return true;

		if (photo[a] != (photo[a + 1]-1))
			return false;
		else
			continue;
	}
}
