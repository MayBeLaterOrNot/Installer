#include "WindowMain.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <format>

WindowMain::WindowMain() {
    long w{ 1000 }, h{ 700 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
	InitWindow(x,y,w,h);
    
}
WindowMain::~WindowMain() {

}

void WindowMain::OnPaint(){
    PaintCtx->fillRoundRect(w - 180, h - 100, 140, 60,8,8, BLRgba32(0xffd3f261));
}
