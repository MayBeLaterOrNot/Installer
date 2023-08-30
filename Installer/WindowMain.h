#pragma once
#include <Windows.h>
#include <blend2d.h>
#include <vector>
#include <memory>
#include "WindowBase.h"
#include "Button.h"

class WindowMain:public WindowBase
{
public:
	WindowMain();
	~WindowMain();
private:
	void OnPaint() override;
	int OnHitTest(const int& x, const int& y) override;
	bool OnMouseMove(const int& x, const int& y) override;

	std::vector<std::shared_ptr<Button>> buttons;
};

