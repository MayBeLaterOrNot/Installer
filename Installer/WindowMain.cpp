#include "WindowMain.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <format>
#include "Font.h"
#include "Util.h"

WindowMain::WindowMain() {
    long w{ 1000 }, h{ 700 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;

    buttons.push_back(std::make_shared<Button>(this, w - 180, h - 100, 140, 60, false,20.0,ConvertToUTF8(L"开始")));
    auto iconCode = reinterpret_cast<const char*>(u8"\ue6e6");
    buttons.push_back(std::make_shared<Button>(this, w - 78, 32, 46, 46, true,20,iconCode));


	InitWindow(x,y,w,h,L"HikLink安装程序");  
}
WindowMain::~WindowMain() {

}

void WindowMain::OnPaint(){
    for (const auto& btn:buttons)
    {
        btn->Paint(PaintCtx);
    }
}

int WindowMain::OnHitTest(const int& x, const int& y) {
    if (x > 16 && x < w - 78 && y>16 && y < 100) {
        return HTCAPTION;
    }
    else
    {
        return HTCLIENT;
    }    
}

bool WindowMain::OnMouseMove(const int& x, const int& y) {
    for (const auto& btn : buttons)
    {
        btn->MouseMove(x,y);
    }
    return true;
}
