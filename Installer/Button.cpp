#include "Button.h"
#include "Font.h"
#include "Util.h"
#include "WindowBase.h"


Button::Button(WindowBase* parent, 
    const int& x, const int& y, const int& w, const int& h, 
    const bool& isIcon, const double& fontSize,
    const std::string& text) :
    parent{parent}, rect(x, y, w, h), 
    isIcon{isIcon},fontSize{fontSize},
    text{ text }
{

}
Button::~Button() {

}

void Button::Paint(BLContext* PaintCtx) {
    BLRoundRect rect(this->rect, 8);
    PaintCtx->fillRoundRect(rect, IsMouseEnter? BLRgba32(0xff5b8c00) :BLRgba32(0xffd3f261));
    BLFont* font;
    if (isIcon) {
        font = Font::Get()->fontIcon;
    }
    else
    {
       font = Font::Get()->fontText;
    }
    font->setSize(fontSize);
    BLPoint point = GetCenterTextPoint(text, rect.x, rect.y, rect.w, rect.h);
    PaintCtx->setFillStyle(IsMouseEnter ? BLRgba32(255, 255, 255):BLRgba32(60, 60, 60));
    PaintCtx->fillUtf8Text(point, *font, text.c_str());
}

void Button::MouseMove(const int& x, const int& y) {
    if (IsMouseEnter) {
        if (x < rect.x || y < rect.y || x>rect.x + rect.w || y > rect.y + rect.h) {
            IsMouseEnter = false;
            ChangeCursor(IDC_ARROW);
            parent->Repaint();
        }
    }
    else
    {
        if (x > rect.x && x < rect.x + rect.w && y>rect.y && y < rect.y + rect.h) {
            IsMouseEnter = true;
            ChangeCursor(IDC_HAND);
            parent->Repaint();
        }
    }    
}