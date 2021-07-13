#include "Room.h"
#include <fstream>

void	Room::clean_exit(int mode)
{
	switch (mode)
	{
		case 0: //левая верхняя угловая комната
			for (int j = 0; j < w; ++j)
				if (data[0][j] == 'x')
					data[0][j] = '#';
			for (int i = 0; i < h; ++i)
				if (data[i][0] == 'x')
					data[i][0] = '#';
			break;
		case 1: //верхняя комната
			for (int j = 0; j < w; ++j)
				if (data[0][j] == 'x')
					data[0][j] = '#';
			break;
		case 2: //правая верхняя угловая комната
			for (int j = 0; j < w; ++j)
				if (data[0][j] == 'x')
					data[0][j] = '#';
			for (int i = 0; i < h; ++i)
				if (data[i][w - 1] == 'x')
					data[i][w - 1] = '#';
			break;
		case 3: //левая комната
			for (int i = 0; i < h; ++i)
				if (data[i][0] == 'x')
					data[i][0] = '#';
			break;
		case 4: //правая комната
			for (int i = 0; i < h; ++i)
				if (data[i][w - 1] == 'x')
					data[i][w - 1] = '#';
			break;
		case 5: //левая нижняя угловая комната
			for (int i = 0; i < h; ++i)
				if (data[i][0] == 'x')
					data[i][0] = '#';
			for (int j = 0; j < w; ++j)
				if (data[h - 1][j] == 'x')
					data[h - 1][j] = '#';
			break;
		case 6: //правая нижняя угловая комната
			for (int i = 0; i < h; ++i)
				if (data[i][w - 1] == 'x')
					data[i][w - 1] = '#';
			for (int j = 0; j < w; ++j)
				if (data[h - 1][j] == 'x')
					data[h - 1][j] = '#';
			break;
		case 7: //нижняя комната
			for (int j = 0; j < w; ++j)
				if (data[h - 1][j] == 'x')
					data[h - 1][j] = '#';
			break;
	}
}

void	Room::copy_texts(std::string text, Image *val)
{
	if (text == "wall")
		wall = val;
	else if (text == "floor")
		floor = val;
	else if (text == "exit")
		exit = val;
	else if (text == "main_exit")
		main_exit = val;
	else if (text == "op_exit")
		op_exit = val;
	else if (text == "key")
		key = val;
}

char	Room::ret_val(int x, int y)
{
	// printf("%d %d %c\n", x, y, data[y][x]);
	return data[y][x];
}

void	Room::put_val(int x, int y, char val)
{
	data[y][x] = val;
}

int	Room::find_player(int &x, int &y)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < data[i].length(); ++j)
		{
			if (data[i][j] == '@')
			{
				x = j;
				y = i;
				data[i][j] = '.';
				return (1);
			}
		}
	}
	return (0);
}

void	Room::file_info(std::string &name)
{
	std::ifstream file(name);
	std::string str;
	int res = 0;

	while (!file.eof())
	{
		getline(file, str);
		if (str.length() == 0)
			break;
		++res;
	}
	h = res;
	file.close();
}

Room::Room(const Room &room)
{
	data = room.data;
	w = room.w;
	h = room.h;
	type = room.type;
	wall = room.wall;
	floor = room.floor;
	exit = room.exit;
	op_exit = room.op_exit;
	main_exit = room.main_exit;
	key = room.key;
}

Room::Room(char l)
{
	type = l;
	std::string name = std::string("../") + l + std::string(".txt");
	file_info(name);
	std::ifstream file(name);

	data = std::vector<std::string>(h);
	for (int i = 0; i < h; ++i)
		getline(file, data[i]);
	w = data[0].length();
	// printf("%d\n", w);
	file.close();
}

void	DrawSquare(Image &screen, int x, int y)
{
	for (int i = 0; i < 32; ++i)
	{
		for (int j = 0; j < 32; ++j)
		{
			screen.PutPixel(x + j, y + i, Pixel{.r = 0, .g = 0, .b = 0, .a = 255});
		}
	}
}

void	Room::Draw(Image &screen)
{
	int x = 0;
	int y = 0;

	for (int i = h - 1; i >= 0; --i)
	{
		x = 0;
		// printf("%d\n", i);
		for (int j = 0; j < w; ++j)
		{
			// printf("%c %d %d %d\n", data[i][j], x, y, w);
			switch(data[i][j])
			{
				case '#':
					// printf("%d %d\n", x, y);
					wall->Draw(screen, x, y, 32);
					break;
				case '.':
					floor->Draw(screen, x, y, 32);
					break;
				case ' ':
					DrawSquare(screen, x, y);
					break;
				case 'K':
					floor->Draw(screen, x, y, 32);
					key->Draw(screen, x, y, 32);
					break;
				case 'x':
					exit->Draw(screen, x, y, 32);
					break;
				case 'X':
					op_exit->Draw(screen, x, y, 32);
					break;
				case 'Q':
					main_exit->Draw(screen, x, y, 32);
					break;
				default:
					break;
			}
			x += 32;
		}
		y += 32;
	}
}

void	Room::find_exit(MovementDir dir, int &x, int &y)
{
	switch (dir)
	{
		case MovementDir::UP :
			for (int j = 0; j < w; ++j)
				if (data[h - 1][j] == 'x' || data[h - 1][j] == 'X')
				{
					data[h - 1][j] = 'X';
					x = j;
					y = h - 2;
				}
			break;
		case MovementDir::DOWN :
			for (int j = 0; j < w; ++j)
				if (data[0][j] == 'x' || data[0][j] == 'X')
				{
					data[0][j] = 'X';
					x = j;
					y = 1;
				}
			break;
		case MovementDir::LEFT :
			for (int i = 0; i < h; ++i)
				if (data[i][w - 1] == 'x' || data[i][w - 1] == 'X')
				{
					write(1, "a", 1);
					data[i][w - 1] = 'X';
					x = w - 2;
					y = i;
				}
			break;
		case MovementDir::RIGHT :
			for (int i = 0; i < h; ++i)
				if (data[i][0] == 'x' || data[i][0] == 'X')
				{
					data[i][0] = 'X';
					x = 1;
					y = i;
				}
			break;
	}
}
