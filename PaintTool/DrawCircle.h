#ifndef __DRAW_CIRCLE_H
#define __DRAW_CIRCLE_H

#include "resource.h"
#include "ParentDraw.h"

class CDrawCircle : public CParentDraw
{
public:
    CDrawCircle();
    ~CDrawCircle();
    BOOL WriteDC(RECT& rcClient);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
};

#endif