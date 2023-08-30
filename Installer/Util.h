#pragma once
#include <string>
#include <Windows.h>
#include "blend2d.h"

std::string ConvertToUTF8(const std::wstring& wstr);
std::string ConvertToUTF8(const LPWSTR& wstr);
void ChangeCursor(LPCTSTR cursor);
BLPoint GetCenterTextPoint(const std::string& str,const double& x, const double& y, const double& w, const double& h);
void Debug(const std::string& info);

