#pragma once
#include <Windows.h>
#include <blend2d.h>
#include "WindowBase.h"

class WindowMain:public WindowBase
{
public:
	WindowMain();
	~WindowMain();
private:
	void OnPaint() override;
};

