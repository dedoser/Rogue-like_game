#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room
{
private:
	char	type;
	char	**data;
public:
	Room(std::string f_name);
	~Room();
};

Room::Room(std::string f_name)
{
}

Room::~Room()
{
}


#endif ROOM_H
