#ifndef __DRAW_RECT_H
#define __DRAW_RECT_H

#include "resource.h"
#include "ParentDraw.h"

class CDrawRect : public CParentDraw
{
public:
    CDrawRect();
    ~CDrawRect();
    BOOL WriteDC(RECT& rcClient);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
};

#endif