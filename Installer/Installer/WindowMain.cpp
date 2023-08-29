﻿#include "WindowMain.h"
#include <windowsx.h>
#include <dwmapi.h>
#include <format>

WindowMain::WindowMain() {
    InitWindow();
}
WindowMain::~WindowMain() {
    delete PaintCtx;
    delete CanvasImage;
    DeleteObject(compatibleDC);
    DeleteObject(bitmap);
}

void WindowMain::InitWindow()
{
    static int num = 0;
    std::wstring className = std::format(L"Install_{}", num++);
    auto hinstance = GetModuleHandle(NULL);
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &WindowMain::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(WindowMain*);
    wcx.hInstance = hinstance;
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = className.c_str();
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"注册窗口类失败", L"系统提示", NULL);
        return;
    }
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    x = (rect.right - w) / 2;
    y = (rect.bottom - h) / 2;
    hwnd = CreateWindowEx(WS_EX_LAYERED, wcx.lpszClassName, wcx.lpszClassName, 
        WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, x, y, w, h, NULL, NULL, hinstance, static_cast<LPVOID>(this));
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    InitCanvas();
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    Repaint();
    auto hCursor = LoadCursor(NULL, IDC_ARROW);
    SetCursor(hCursor);
}
void WindowMain::InitCanvas() {
    auto stride = w * 4;
    pixelDataSize = stride * h;
    pixelData = new unsigned char[pixelDataSize];
    PaintCtx = new BLContext();
    CanvasImage = new BLImage();
    CanvasImage->createFromData(w, h, BL_FORMAT_PRGB32, pixelData, stride, BL_DATA_ACCESS_RW, [](void* impl, void* externalData, void* userData) {
        delete[] externalData;
        });
    PaintCtx->begin(*CanvasImage);
    PaintCtx->clearAll();
    DrawShadow();
    PaintCtx->fillBox(16, 16, w - 16, h - 16,BLRgba32(255,255,255));
    PaintCtx->end();
    HDC hdc = GetDC(hwnd);
    compatibleDC = CreateCompatibleDC(NULL);
    bitmap = CreateCompatibleBitmap(hdc, w, h); //创建一副与当前DC兼容的位图
    DeleteObject(SelectObject(compatibleDC, bitmap));
    ReleaseDC(hwnd, hdc);
}
LRESULT CALLBACK WindowMain::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    auto obj = reinterpret_cast<WindowMain*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (obj) {
        return obj->WindowProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowMain::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_NCCALCSIZE:
        {
            if (wParam == TRUE)
            {
                return false;
            }
            break;
        }
        case WM_NCHITTEST:
        {
            return OnHitTest(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        }
        case WM_SETCURSOR: {
            return true;
        }
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

void WindowMain::Repaint()
{
    HDC hdc = GetDC(hwnd);
    BITMAPINFO info = { sizeof(BITMAPINFOHEADER), w, 0 - h, 1, 32, BI_RGB, pixelDataSize, 0, 0, 0, 0 };
    SetDIBits(hdc, bitmap, 0, h, pixelData, &info, DIB_RGB_COLORS); //使用指定的DIB颜色数据来设置位图中的像素
    BLENDFUNCTION blend = { .BlendOp{AC_SRC_OVER},.SourceConstantAlpha{255},.AlphaFormat{AC_SRC_ALPHA} };//按通道混合
    POINT pSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    UpdateLayeredWindow(hwnd, hdc, NULL, &sizeWnd, compatibleDC, &pSrc, NULL, &blend, ULW_ALPHA);//更新分层窗口
    ReleaseDC(hwnd, hdc);
}

void WindowMain::DrawShadow()
{
    {//左上
        BLGradient radial(BLRadialGradientValues(16, 16, 16, 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        PaintCtx->fillCircle(16, 16, 16, radial);

        PaintCtx->setCompOp(BL_COMP_OP_CLEAR);
        PaintCtx->setFillStyle(BLRgba32(0xFF000000));
        PaintCtx->fillBox(16, 0, 32, 16);
        PaintCtx->fillBox(0, 16, 16, 32);
        PaintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    {//右上
        BLGradient radial(BLRadialGradientValues(w - 16, 16, w - 16, 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        PaintCtx->fillCircle(w - 16, 16, 16, radial);

        PaintCtx->setCompOp(BL_COMP_OP_CLEAR);
        PaintCtx->setFillStyle(BLRgba32(0xFF000000));
        PaintCtx->fillBox(w - 32, 0, w - 16, 16);
        PaintCtx->fillBox(w - 16, 16, w, 32);
        PaintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    { //右下
        BLGradient radial(BLRadialGradientValues(w - 16, h - 16, w - 16, h - 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        PaintCtx->fillCircle(w-16, h-16, 16, radial);
        PaintCtx->setCompOp(BL_COMP_OP_CLEAR);
        PaintCtx->setFillStyle(BLRgba32(0xFF000000));
        PaintCtx->fillBox(w - 16, h-32, w, h-16);
        PaintCtx->fillBox(w-32, h-16, w - 16, h);
        PaintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    { //左下
        BLGradient radial(BLRadialGradientValues(16, h - 16, 16, h - 16, 16));
        radial.addStop(0.0, BLRgba32(0x22000000));
        radial.addStop(1.0, BLRgba32(0x00000000));
        PaintCtx->fillCircle(16, h - 16, 16, radial);
        PaintCtx->setCompOp(BL_COMP_OP_CLEAR);
        PaintCtx->setFillStyle(BLRgba32(0xFF000000));
        PaintCtx->fillBox(16, h - 16, 32, h);
        PaintCtx->fillBox(0, h - 32, 16, h - 16);
        PaintCtx->setCompOp(BL_COMP_OP_SRC_OVER);
    }
    { //上
        BLGradient linear(BLLinearGradientValues(0, 0, 0, 16));
        linear.addStop(0.0, BLRgba32(0x00000000));
        linear.addStop(1.0, BLRgba32(0x22000000));
        PaintCtx->fillBox(16, 0, w-16, 16, linear);
    }
    { //右
        BLGradient linear(BLLinearGradientValues(w - 16, 16, w, 16));
        linear.addStop(0.0, BLRgba32(0x22000000));
        linear.addStop(1.0, BLRgba32(0x00000000));
        PaintCtx->fillBox(w - 16, 16, w, h - 16, linear);
    }
    { //下
        BLGradient linear(BLLinearGradientValues(0, h - 16, 0, h));
        linear.addStop(0.0, BLRgba32(0x22000000));
        linear.addStop(1.0, BLRgba32(0x00000000));
        PaintCtx->fillBox(16, h - 16, w - 16, h, linear);
    }
    { //左
        BLGradient linear(BLLinearGradientValues(0, 0, 16, 0));
        linear.addStop(0.0, BLRgba32(0x00000000));
        linear.addStop(1.0, BLRgba32(0x22000000));
        PaintCtx->fillBox(0, 16, 16, h-16, linear);
    }
    PaintCtx->setStrokeWidth(0.8);
    PaintCtx->strokeBox(16, 16, w - 16, h - 16, BLRgba32(0, 128, 0));
}