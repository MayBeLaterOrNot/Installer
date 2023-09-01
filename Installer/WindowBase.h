#pragma once
#include <Windows.h>
#include <blend2d.h>
#include <string>
#include <vector>
#include <memory>
#include "Button.h"

class WindowBase
{
public:
	WindowBase();
	~WindowBase();
	void Repaint();
	void Show();
protected:
	void InitWindow(const int& x, const int& y,const long& w,const long& h,const std::wstring& title);
	virtual void OnPaint() {};
	virtual int OnHitTest(const int& x, const int& y) { return HTCAPTION; };
	virtual bool OnLeftButtonDown(const int& x, const int& y) { return false; };
	virtual bool OnRightButtonDown(const int& x, const int& y) { return false; };
	virtual bool OnMouseMove(const int& x, const int& y) { return false; };
	virtual bool OnLeftButtonUp(const int& x, const int& y) { return false; };
	BLContext* PaintCtx;
	BLImage* CanvasImage;
	long w, h;
	int x, y;
	bool IsLeftBtnDown;
	std::vector<std::shared_ptr<Button>> Buttons;
	HWND hwnd;
private:
	void InitCanvas();
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	
	void DrawShadow();	
	void* pixelData;
	unsigned long pixelDataSize;
	HBITMAP bitmap;	
	HDC compatibleDC = NULL;
};

