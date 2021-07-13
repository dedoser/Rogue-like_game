#ifndef INTERFACE_H
#define INTERFACE_H

#include "Image.h"
#include <vector>
class Interface
{
private:
	Pixel color{.r = 65, .g = 105, .b = 255, .a = 255};
	std::vector<Image> digit;
	std::vector<Image> letter;
	int *key_count;
public:
	Interface(int *keys);
	void	Draw(Image &screen);
	void	IncCount() {key_count++;}
	void	Reload(int *keys) {key_count = keys;}
};

#endif
