#pragma once
#include <string>
#include <blend2d.h>
#include "WindowBase.h"
class Button
{
public:
	Button(WindowBase* parent, 
		const int& x, const int& y, const int& w, const int& h, 
		const bool& isIcon,const double& fontSize,
		const std::string& text);
	~Button();
	void Paint(BLContext* PaintCtx);
	void MouseMove(const int& x, const int& y);
	BLRectI rect;
	std::string text;
	bool IsMouseEnter = false;
	bool isIcon;
	double fontSize;
	WindowBase* parent;
};

