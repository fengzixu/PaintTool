#ifndef  __DRAW_PEN_H
#define  __DRAW_PEN_H

#include "resource.h"
#include "ParentDraw.h"

class CDrawPen : public CParentDraw
{
public:
    CDrawPen();
    ~CDrawPen();
    BOOL WriteDC(RECT& rcClient);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
    static Paint_Struct ms_static_struct;
};

#endif