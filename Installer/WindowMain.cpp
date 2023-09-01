#include "WindowMain.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <format>
#include "Font.h"
#include "Util.h"
#include "Downloader.h"

WindowMain::WindowMain() {
    long w{ 1000 }, h{ 700 };
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    int x = (rect.right - w) / 2;
    int y = (rect.bottom - h) / 2;
	InitWindow(x,y,w,h,L"HikLink安装程序");
    initStartBtn();
    initCloseBtn();
}
WindowMain::~WindowMain() {

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

void WindowMain::initStartBtn() {
    auto btn = std::make_shared<Button>();
    btn->Box = BLBoxI(w - 180, h - 100, w - 40, h - 40);
    btn->IsIcon = false;
    btn->FontSize = 20.0;
    btn->Text = ConvertToUTF8(L"开始");
    btn->Radius = 8.0;
    btn->ForegroundColor = BLRgba32(0xff000000);
    btn->BackgroundColor = BLRgba32(0xffd3f261);
    btn->OnMouseOut = [this](Button* sender) {
        sender->ForegroundColor = BLRgba32(0xff000000);
        sender->BackgroundColor = BLRgba32(0xffd3f261);
        ChangeCursor(IDC_ARROW);
        Repaint();
    };
    btn->OnMouseEnter = [this](Button* sender) {
        sender->ForegroundColor = BLRgba32(0xffffffff);
        sender->BackgroundColor = BLRgba32(0xff5b8c00);
        ChangeCursor(IDC_HAND);
        Repaint();
    };
    btn->OnMouseUp = [this](Button* sender) {
        auto downloader = new Downloader();
        downloader->Download(L"https://avatars.githubusercontent.com/u/2980915?v=4");
    };
    Buttons.push_back(std::move(btn));
}
void WindowMain::initCloseBtn() {
    auto btn = std::make_shared<Button>();
    btn->Box = BLBoxI(w - 56, 16, w - 16, 56);
    btn->IsIcon = true;
    btn->FontSize = 18.0;
    btn->Text = reinterpret_cast<const char*>(u8"\ue6e6");
    btn->ForegroundColor = BLRgba32(0xff333333);
    btn->BackgroundColor = BLRgba32(0xffffffff);
    btn->OnMouseOut = [this](Button* sender) {
        sender->BackgroundColor = BLRgba32(0xffffffff);
        ChangeCursor(IDC_ARROW);
        Repaint();
    };
    btn->OnMouseEnter = [this](Button* sender) {
        sender->BackgroundColor = BLRgba32(0xffcccccc);
        ChangeCursor(IDC_HAND);
        Repaint();
    };
    btn->OnMouseUp = [this](Button* sender) {
        SendMessage(hwnd, WM_CLOSE, NULL, NULL);
        PostQuitMessage(0);
    };
    Buttons.push_back(std::move(btn));
}
