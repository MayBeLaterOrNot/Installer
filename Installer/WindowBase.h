#pragma once
#include <Windows.h>
#include <blend2d.h>

class WindowBase
{
public:
	WindowBase();
	~WindowBase();
protected:
	void InitWindow(const int& x, const int& y,const long& w,const long& h);
	virtual void OnPaint() {};
	BLContext* PaintCtx;
	BLImage* CanvasImage;
	long w, h;
	int x, y;
private:
	void InitCanvas();
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	int OnHitTest(const int& x, const int& y) { return HTCAPTION; };  //HTCLIENT
	void Repaint();
	void DrawShadow();	
	void* pixelData;
	unsigned long pixelDataSize;
	HBITMAP bitmap;	
	HDC compatibleDC = NULL;
	HWND hwnd;

};

