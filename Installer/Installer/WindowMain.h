#pragma once
#include <Windows.h>
#include <blend2d.h>

class WindowMain
{
public:
	WindowMain();
	~WindowMain();
private:
	int OnHitTest(const int& x, const int& y) { return HTCLIENT; };
	void BeforePaint() {};

	BLContext* PaintCtx;
	void* pixelData;
	HBITMAP bottomHbitmap;
	HDC hCompatibleDC = NULL;
};

