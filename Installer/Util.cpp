#include "Util.h"
#include "Font.h"
std::string ConvertToUTF8(const std::wstring& wstr)
{
    const int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}

std::string ConvertToUTF8(const LPWSTR& wstr)
{
    const int count = WideCharToMultiByte(CP_UTF8, 0, wstr, (int)wcslen(wstr), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], count, NULL, NULL);
    return str;
}

void ChangeCursor(LPCTSTR cursor)
{
    auto hCursor = LoadCursor(NULL, cursor);
    SetCursor(hCursor);
}

BLPoint GetCenterTextPoint(const std::string& str, const double& x, const double& y, const double& w, const double& h) {
    auto font = Font::Get()->fontText;
    BLFontMetrics fm = font->metrics();
    BLTextMetrics tm;
    BLGlyphBuffer gb;
    gb.setUtf8Text(str.c_str());
    font->shape(gb);
    font->getTextMetrics(gb, tm);
    BLPoint point;
    point.x = x + (w - (tm.boundingBox.x1 - tm.boundingBox.x0)) / 2;
    point.y = y + fm.ascent + (h - font->size()) / 2;
    return point;
}

void Debug(const std::string& info)
{
    OutputDebugStringA("\r\n");
    OutputDebugStringA(info.c_str());
    OutputDebugStringA("\r\n");
}