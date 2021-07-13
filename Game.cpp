#include "Game.h"
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include "stb_image.h"

void	Game::clean_exits()
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < rooms[i].size(); ++j)
		{
			if (i == 0 && j == 0)
				rooms[i][j].clean_exit(0);
			else if (i == 0 && j == rooms[i].size() - 1)
				rooms[i][j].clean_exit(2);
			else if (i == 0 && j != 0 && j != rooms[i].size() - 1)
				rooms[i][j].clean_exit(1);
			else if (i == h - 1 && j == 0)
				rooms[i][j].clean_exit(5);
			else if (i == h - 1 && j == rooms[i].size() - 1)
				rooms[i][j].clean_exit(6);
			else if (j == 0 && i != 0 && i != h - 1)
				rooms[i][j].clean_exit(3);
			else if (j == rooms[i].size() - 1 && i != 0 && i != h - 1)
				rooms[i][j].clean_exit(4);
			else if (i == h - 1)
				rooms[i][j].clean_exit(7);
		}
	}
}

void	Game::change_room()
{
	switch (pl.RetDir())
	{
		case MovementDir::UP:
			room_y--;
			break;
		case MovementDir::DOWN:
			room_y++;
			break;
		case MovementDir::LEFT:
			room_x--;
			break;
		case MovementDir::RIGHT:
			room_x++;
			break;
	}
	rooms[room_y][room_x].find_exit(pl.RetDir(), cur_x, cur_y);
	pl.ChangeRoom(&rooms[room_y][room_x], cur_x, cur_y);
	anim = 1;
}

Player	*Game::ret_player()
{
	return (&pl);
}

void	Game::send_texts(Room &room)
{
	if (room.ret_type() == 'A')
	{
		room.copy_texts("floor", &textA[0]);
		room.copy_texts("wall", &textA[1]);
	}
	else if (room.ret_type() == 'B')
	{
		room.copy_texts("floor", &textB[0]);
		room.copy_texts("wall", &textB[1]);
	}
	else if (room.ret_type() == 'C')
	{
		room.copy_texts("floor", &textC[0]);
		room.copy_texts("wall", &textC[1]);
	}
	else if (room.ret_type() == 'D')
	{
		room.copy_texts("floor", &textD[0]);
		room.copy_texts("wall", &textD[1]);
	}
	room.copy_texts("exit", &exit);
	room.copy_texts("main_exit", &main_exit);
	room.copy_texts("op_exit", &op_exit);
	room.copy_texts("key", &key);
}

void	Game::open_texts()
{
	std::string name = std::string("../resources/") + "A" + std::string("/");
	textA.push_back(Image(name + "floor.png"));
	textA.push_back(Image(name + "wall.png"));
	name = std::string("../resources/") + 'B' + std::string("/");
	textB.push_back(Image(name + std::string("floor.png")));
	textB.push_back(Image(name + std::string("wall.png")));
	name = std::string("../resources/") + 'C' + std::string("/");
	textC.push_back(Image(name + std::string("floor.png")));
	textC.push_back(Image(name + std::string("wall.png")));
	name = std::string("../resources/") + 'D' + std::string("/");
	textD.push_back(Image(name + std::string("floor.png")));
	textD.push_back(Image(name + std::string("wall.png")));
	
}

void	Game::draw(Image &screen)
{
	if (!pl.EndGame())
	{
		pl.ret_room()->Draw(screen);
		pl.Draw(screen);
		pl.InterDraw(screen);
	}
	else
	{
		for (int i = 0; i < end.Height(); ++i)
			for (int j = 0; j < end.Width(); ++j)
				screen.PutPixel(j, i, end.GetPixel(j, 991 -i));
	}
}

void	Game::init_player()
{
	for (int i = 0; i < h; ++i)
		for (int j = 0; j < rooms[i].size(); ++j)
		{
			if (rooms[i][j].find_player(cur_x, cur_y))
			{
				pl = Player(cur_x, cur_y, rooms[i][j]);
				pl.InterReload();
				room_x = j;
				room_y = i;
				return;
			}
		}
}

void	Game::init_rooms()
{
	for (int i = 0; i < h; ++i)
	{
		std::vector<Room> tmp;
		for (int j = 0; j < map[i].length(); ++j)
		{
			tmp.push_back(Room(map[i][j]));
			send_texts(tmp[j]);
		}
		rooms.push_back(tmp);
	}
}

Game::Game() :
	exit("../resources/doorc.png"), op_exit("../resources/dooro.png"),
	main_exit("../resources/door1.png"), key("../resources/key.png"), end("../resources/end.png")
{
	std::ifstream file("../main.txt");
	std::string str;

	h = 0;
	while (!file.eof())
	{
		getline(file, str);
		if (str.length() == 0)
			break;
		map.push_back(str);
		++h;
	}
	file.close();
	open_texts();
	init_rooms();
	init_player();
	clean_exits();
	anim = 0;
}

Game::~Game()
{
	exit.del_data();
	main_exit.del_data();
	op_exit.del_data();
	key.del_data();
	textA[0].del_data();
	textA[1].del_data();
	textB[0].del_data();
	textB[1].del_data();
	textC[0].del_data();
	textC[1].del_data();
	textD[0].del_data();
	textD[1].del_data();
}

void	Game::disapear(Image &screen, int width, int &y)
{
	if (anim++ != 1)
		return;
	y--;
	for (int i = 0; i < width; ++i)
	{
		screen.PutPixel(i, y, Pixel {.r = 0, .g = 0, .b = 0, .a = 255});
	}
	anim = y != 0;
}
