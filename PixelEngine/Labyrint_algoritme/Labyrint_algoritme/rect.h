#ifndef RECT_H
#define RECT_H

class Rect
{
public:
	int index, size;
	bool visited;

	Rect();
	Rect(int index, int size);

	~Rect();
};

#endif