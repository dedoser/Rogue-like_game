#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Image.h"

class Room
{
private:
	std::vector<std::string> data;
	int	w, h;
	char type;
	void	file_info(std::string &name);
	Image	*wall;
	Image	*floor;
	Image	*key;
	Image	*exit;
	Image	*op_exit;
	Image	*main_exit;
public:
	Room(char l);
	Room(const Room &room);
	void	Draw(Image &screen);
	int		find_player(int &x, int &y);
	char	ret_val(int x, int y);
	void	put_val(int x, int y, char val);
	void	copy_texts(std::string text, Image *val);
	char	ret_type(){return (type); }
	void	clean_exit(int mode);
	void	find_exit(MovementDir dir, int &x, int &y);
};


#endif

