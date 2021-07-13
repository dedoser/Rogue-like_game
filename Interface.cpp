#include "Interface.h"
#include <string>

Interface::Interface(int *keys)
{
	key_count = keys;
	std::string name = "../resources/font/";
	for (int i = 0; i < 10; ++i)
	{
		digit.push_back(Image(name + (char)('0' + i) + std::string(".png")));
	}
	letter.push_back(Image(name + "k.png"));
	letter.push_back(Image(name + "e.png"));
	letter.push_back(Image(name + "y.png"));
	letter.push_back(Image(name + "s.png"));
	letter.push_back(Image(name + "dots.png"));
}

void	Interface::Draw(Image &screen)
{
	int x = 1024;
	for (int i = x; i < 1440; ++i)
		for (int j = 0; j < 992; ++j)
			screen.PutPixel(i, j, color);
	x = 1050;
	int y = 800;
	for (int i = 0; i < 5; ++i)
	{
		letter[i].Draw(screen, x, y, 32);
		x += 32;
	}
	int tmp = *key_count;
	int deg = 0;
	if (tmp == 0)
		deg = 1;
	while (tmp != 0)
	{
		deg++;
		tmp /= 10;
	}
	tmp = *key_count;
	int ten = 1;
	for (int i = 0; i < deg - 1; ++i)
		ten *= 10;
	while (ten != 0)
	{
		digit[tmp / ten].Draw(screen, x, y, 32);
		x += 32;
		tmp /= 10;
		ten /= 10;
	}
}
