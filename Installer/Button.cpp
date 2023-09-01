#include "Button.h"
#include "Font.h"
#include "Util.h"


Button::Button()
{

}
Button::~Button() {

}

void Button::Paint(BLContext* PaintCtx) {
    if (Radius != 0) {
        BLRoundRect rect(Box.x0, Box.y0, Box.x1-Box.x0, Box.y1-Box.y0, Radius);
        PaintCtx->fillRoundRect(rect,BackgroundColor);
    }
    else
    {
        PaintCtx->fillBox(Box, BackgroundColor);
    }
    if (!Text.empty()) {
        BLFont* font;
        if (IsIcon) {
            font = Font::Get()->fontIcon;
        }
        else
        {
            font = Font::Get()->fontText;
        }
        font->setSize(FontSize);
        BLFontMetrics fm = font->metrics();
        BLTextMetrics tm;
        BLGlyphBuffer gb;
        gb.setUtf8Text(Text.c_str());
        font->shape(gb);
        font->getTextMetrics(gb, tm);
        BLPoint point;
        switch (Align)
        {
            case Align::Unset: {

                break;
            }
            case Align::TopLeft: {

                break;
            }            
            case Align::TopRight: {

                break;
            }
            case Align::BottomLeft: {

                break;
            }
            case Align::BottomRight: {

                break;
            }
            case Align::TopCenter: {

                break;
            }
            case Align::BottomCenter: {

                break;
            }
            case Align::LeftCenter: {
                point.x = Box.x0;
                point.y = Box.y0 + fm.ascent + ((Box.y1 - Box.y0) - font->size()) / 2;
                break;
            }
            case Align::RightCenter: {

                break;
            }
            case Align::Center: {
                point.x = Box.x0 + ((Box.x1 - Box.x0) - (tm.boundingBox.x1 - tm.boundingBox.x0)) / 2;
                point.y = Box.y0 + fm.ascent + ((Box.y1 - Box.y0) - font->size()) / 2;
                break;
            }
        }
        PaintCtx->setFillStyle(ForegroundColor);
        PaintCtx->fillUtf8Text(point, *font, Text.c_str());
    }
    
}

bool Button::MouseMove(const int& x, const int& y) {
    if (Box.contains(x, y)) {
        if (!IsMouseEnter) {
            IsMouseEnter = true;
            if (OnMouseEnter) {
                OnMouseEnter(this);
            }
            return true;
        }
    }
    else
    {
        if (IsMouseEnter) {
            IsMouseEnter = false;
            if (OnMouseOut) {
                OnMouseOut(this);
            }
            return true;
        }
    }
    return false;
}
bool Button::MouseUp(const int& x, const int& y) {
    if (IsMouseEnter) {
        if (OnMouseUp) {
            OnMouseUp(this);
        }        
        return true;
    }
    return false;
}