#ifndef __DRAW_ARROW_H
#define __DRAW_ARROW_H

#include "resource.h"
#include "ParentDraw.h"

class CDrawArrow : public CParentDraw
{
public:
    CDrawArrow();
    ~CDrawArrow();
    BOOL WriteDC(RECT& rcClient);
    void CalculatePoint(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
    int m_nLeftx;
    int m_nLefty;
    int m_nRightx;
    int m_nRighty;
};

#endif