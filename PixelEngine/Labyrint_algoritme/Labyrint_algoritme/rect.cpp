#include "rect.h"

Rect::Rect(int index, int size)
{
	this->index = index;
	this->size = size;
	this->visited = false;
}