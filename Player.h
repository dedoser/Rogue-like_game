#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Room.h"
#include "Interface.h"
struct Point
{
  float x;
  float y;
};

struct Player
{
  explicit Player(Point pos = {.x = 10, .y = 10}) :
                 coords(pos), old_coords(coords), inter(&key_count) {};
  bool Moved() const;
  MovementDir RetDir() {return dir_pl;};
  void ProcessInput(MovementDir dir);
  void Draw(Image &screen);
  void InterDraw(Image &screen) {inter.Draw(screen);}
  void OpenDoor();
  void GetKey();
  void OpenTexts();
  void ChangeText();
  void InterReload() {inter.Reload(&key_count);}
  void ChangeRoom(Room *new_r, int x, int y);
  int  NeedChange() {return (change);};
  int  EndGame(){return end_game;}
  int KeyCount() {return key_count;}
  Room *ret_room(){return cur_room;};
  Player(int x, int y, Room &r);
private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 255, .a = 255};
  int map_x, map_y;
  int move_speed = 4;
  Room  *cur_room;
  MovementDir   dir_pl;
  Image *cur;
  int   cur_text;
  std::vector<Image> left;
  std::vector<Image> right;
  std::vector<Image> up;
  std::vector<Image> down;
  int frame_count;
  int change;
  int   key_count;
  int end_game;
  Interface inter;
};

#endif //MAIN_PLAYER_H
