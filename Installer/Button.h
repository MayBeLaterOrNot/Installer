#pragma once
#include <string>
#include <blend2d.h>
#include <functional>
#include "Align.h"
class Button
{
public:
	Button();
	~Button();
	void Paint(BLContext* PaintCtx);
	bool MouseMove(const int& x, const int& y);
	bool MouseUp(const int& x, const int& y);
	std::function<void(Button* sender)> OnMouseEnter;
	std::function<void(Button* sender)> OnMouseOut;
	std::function<void(Button* sender)> OnMouseUp;
	BLRgba32 BackgroundColor;
	BLRgba32 ForegroundColor;
	BLBoxI Box;
	std::string Text;
	Align Align{ Align::Center };
	bool IsMouseEnter{ false };
	bool IsIcon{false};
	double FontSize{20};
	double Radius{0};
};

