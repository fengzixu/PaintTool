#ifndef __DRAW_LINE_H
#define __DRAW_LINE_H
#include "ParentDraw.h"

class CDrawLine : public CParentDraw
{
public:
    CDrawLine();
    ~CDrawLine();
    BOOL WriteDC(RECT& rcClient);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
};

#endif