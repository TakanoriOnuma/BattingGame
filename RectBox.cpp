#include "RectBox.h"

RectBox::RectBox()
	: width(0.0), length(0.0), height(0.0)
{
}

RectBox::RectBox(double length, double width, double height)
	: length(length), width(width), height(height)
{
}