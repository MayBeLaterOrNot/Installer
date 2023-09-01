#pragma once
#include <Windows.h>
#include <blend2d.h>

#include "WindowBase.h"
#include "Button.h"

class WindowMain:public WindowBase
{
public:
	WindowMain();
	~WindowMain();
private:
	int OnHitTest(const int& x, const int& y) override;	
	void initStartBtn();
	void initCloseBtn();
};

