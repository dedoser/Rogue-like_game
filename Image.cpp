#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

Image::Image(){}

Image::Image(const std::string &a_path)
{
  // Pixel3 *tmp;
  // if((tmp = (Pixel3 *)stbi_load(a_path.c_str(), &width, &height, &channels, 0)) != nullptr)
  // {
  //   size = width * height * channels;
  // }
  // data = new Pixel[width * height];
  // self_allocated = true;
  // for (int i = 0; i < width; ++i)
  //   for (int j = 0; j < height; ++j)
  //   {
  //     data[height * j + i].r = tmp[j * height + i].r;
  //     data[height * j + i].g = tmp[j * height + i].g;
  //     data[height * j + i].b = tmp[j * height + i].b;
  //     data[height * j + i].a = 255;
  //   }
  // stbi_image_free(tmp);
  if ((data = (Pixel *)stbi_load(a_path.c_str(), &width, &height, &channels, sizeof(Pixel))) != nullptr)
  {
    size = width * height * channels;
  }
}

Image::Image(int a_width, int a_height, int a_channels)
{
  data = new Pixel[a_width * a_height] {};

  if(data != nullptr)
  {
    width = a_width;
    height = a_height;
    size = a_width * a_height * a_channels;
    channels = a_channels;
    self_allocated = true;
  }
}

int Image::Save(const std::string &a_path)
{
  auto extPos = a_path.find_last_of('.');
  if(a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG")
  {
    stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
  }
  else if(a_path.substr(extPos, std::string::npos) == ".jpg" || a_path.substr(extPos, std::string::npos) == ".JPG" ||
          a_path.substr(extPos, std::string::npos) == ".jpeg" || a_path.substr(extPos, std::string::npos) == ".JPEG")
  {
    stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
  }
  else
  {
    std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path << "\n";
    return 1;
  }

  return 0;
}

void  Image::Draw(Image &screen, int x, int y, int size)
{
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
    {
      if (data[32 * i + j].a == 0)
        continue;
      screen.PutPixel(x + j, y + 31 - i, data[32 * i + j]);
    }
}

void  Image::del_data()
{
  stbi_image_free(data);
}

Image::~Image()
{
}
