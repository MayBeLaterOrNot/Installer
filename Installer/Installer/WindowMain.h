#pragma once
#include <Windows.h>
#include <blend2d.h>

class WindowMain
{
public:
	WindowMain();
	~WindowMain();
private:
	void InitCanvas();
	void InitWindow();
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	int OnHitTest(const int& x, const int& y) { return HTCAPTION; };  //HTCLIENT
	void Repaint();
	void DrawShadow();

	BLContext* PaintCtx;
	void* pixelData;
	unsigned long pixelDataSize;
	HBITMAP bitmap;
	BLImage* CanvasImage;
	HDC compatibleDC = NULL;
	HWND hwnd;
	unsigned w{ 1000 }, h{700};
	int x, y;
};

