#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include "Player.h"
#include "Interface.h"

class Game
{
private:
	Player	pl;
	std::vector<std::string> map;
	int	w, h;
	std::vector<std::vector<Room>> rooms;
	std::vector<Image> textA;
	std::vector<Image> textB;
	std::vector<Image> textC;
	std::vector<Image> textD;
	int		cur_x, cur_y;
	int		room_x, room_y;
	Image	exit;
	Image	main_exit;
	Image	op_exit;
	Image	key;
	Image	end;
	int		anim;
public:
	Game();
	void	init_player();
	void	init_rooms();
	void	draw(Image &screen);
	Player	*ret_player();
	void	open_texts();
	void	send_texts(Room &room);
	void	change_room();
	void	clean_exits();
	void	disapear(Image &screen, int width, int &y);
	int		ret_anim(){return anim;}
	~Game();
};

#endif
