#include "Player.h"
#include <iostream>

void Player::ChangeRoom(Room *new_r, int x, int y)
{
  cur_room = new_r;
  coords.x = x;
  coords.y = y;
  change = 0;
}

bool Player::Moved() const
{
  if(coords.x == old_coords.x && coords.y == old_coords.y)
    return false;
  else
    return true;
}

void  Player::GetKey()
{
  if (cur_room->ret_val(map_x, map_y) == 'K')
  {
    cur_room->put_val(map_x, map_y, '.');
    key_count++;
  }
}

void  Player::OpenDoor()
{
  if (key_count == 0)
    return ;
  if (cur_room->ret_val(map_x + 1, map_y) == 'x')
  {
    cur_room->put_val(map_x + 1, map_y, 'X');
    key_count--;
  }
  else if (cur_room->ret_val(map_x - 1, map_y) == 'x')
  {
    cur_room->put_val(map_x - 1, map_y, 'X');
    key_count--;
  }
  else if (cur_room->ret_val(map_x, map_y + 1) == 'x')
  {
    cur_room->put_val(map_x, map_y + 1, 'X');
    key_count--;
  }
  else if (cur_room->ret_val(map_x, map_y - 1) == 'x')
  {
    cur_room->put_val(map_x, map_y - 1, 'X');
    key_count--;
  }
}

void Player::ProcessInput(MovementDir dir)
{
  float move_dist = 0.08;
  // printf("%d %d\n", coords.x, coords.y);
  switch(dir)
  {
    case MovementDir::DOWN:
      if (cur_room->ret_val(coords.x, coords.y + move_dist) != '#' &&
          cur_room->ret_val(coords.x, coords.y + move_dist) != 'x')
      {
        old_coords.y = coords.y;
        coords.y += move_dist;
        map_y = coords.y;
      }
      if (dir_pl != dir)
        cur = &down[0];
      break;
    case MovementDir::UP:
      if (cur_room->ret_val(coords.x, coords.y - move_dist) != '#' &&
          cur_room->ret_val(coords.x, coords.y - move_dist) != 'x')
      {
        old_coords.y = coords.y;
        coords.y -= move_dist;
        map_y = coords.y;
      }
      if (dir_pl != dir)
        cur = &up[0];
      break;
    case MovementDir::LEFT:
      if (cur_room->ret_val(coords.x - move_dist, coords.y) != '#' &&
          cur_room->ret_val(coords.x - move_dist, coords.y) != 'x')
      {
        old_coords.x = coords.x;
        coords.x -= move_dist;
        map_x = coords.x;
      }
      if (dir_pl != dir)
        cur = &left[0];
      break;
    case MovementDir::RIGHT:
      if (cur_room->ret_val(coords.x + move_dist, coords.y) != '#' &&
          cur_room->ret_val(coords.x + move_dist, coords.y) != 'x')
      {
        old_coords.x = coords.x;
        coords.x += move_dist;
        map_x = coords.x;
      }
      if (dir_pl != dir)
        cur = &right[0];
      break;
    default:
      break;
  }
  if (dir_pl != dir)
    dir_pl = dir;
  if (cur_room->ret_val(coords.x, coords.y) == 'X')
    change = 1;
  if (cur_room->ret_val(coords.x, coords.y) == 'Q')
    end_game = 1;
}

void Player::Draw(Image &screen)
{
  // if(Moved())
  // {
  //   for(int y = old_coords.y; y <= old_coords.y + tileSize; ++y)
  //   {
  //     for(int x = old_coords.x; x <= old_coords.x + tileSize; ++x)
  //     {
  //       screen.PutPixel(x, y, backgroundColor);
  //     }
  //   }
  //   old_coords = coords;
  // }
  Pixel tmp;
  for(int y = screen.Height() - (int)coords.y * tileSize; y >= screen.Height() - (int)coords.y * tileSize - tileSize; --y)
  {
    for(int x = (int)coords.x * tileSize; x <= (int)coords.x * tileSize + tileSize; ++x)
    {
      tmp = cur->GetPixel(x % tileSize, 32 - y % tileSize);
      if (tmp.a == 0)
        continue;
      screen.PutPixel(x, y, tmp);
    }
  }
  // cur->Draw(screen, (int)coords.x * tileSize, (int)coords.y * tileSize, tileSize);
}

void  Player::OpenTexts()
{
  std::string name = "../resources/player/";
  left.push_back(Image(name + "left1.png"));
  left.push_back(Image(name + "left2.png"));
  left.push_back(Image(name + "left3.png"));
  right.push_back(Image(name + "right1.png"));
  right.push_back(Image(name + "right2.png"));
  right.push_back(Image(name + "right3.png"));
  down.push_back(Image(name + "down1.png"));
  down.push_back(Image(name + "down2.png"));
  down.push_back(Image(name + "down3.png"));
  up.push_back(Image(name + "up1.png"));
  up.push_back(Image(name + "up2.png"));
  up.push_back(Image(name + "up3.png"));
}

void  Player::ChangeText()
{
  if (frame_count == 30)
  {
    cur_text = (cur_text + 1) % 3;
    if (dir_pl == MovementDir::UP)
      cur = &up[cur_text];
    else if (dir_pl == MovementDir::DOWN)
      cur = &down[cur_text];
    else if (dir_pl == MovementDir::LEFT)
      cur = &left[cur_text];
    else if (dir_pl == MovementDir::RIGHT)
      cur = &right[cur_text];
    frame_count = 0;
  }
  else frame_count++;
}

Player::Player(int x, int y, Room &r) : inter(&key_count)
{
  coords.x = x;
  coords.y = y;
  map_x = x;
  map_y = y;
  old_coords.x = x;
  old_coords.y = y;
  cur_room = &r;
  key_count = 0;
  cur_text = 0;
  OpenTexts();
  cur = &up[0];
  frame_count = 0;
  change = 0;
  end_game = 0;
}
