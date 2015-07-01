#ifndef __DRAWARROW_H
#define __DRAWARROW_H

#include "ParentDraw.h"

class CDrawArrow : public CParentDraw
{
public:
    CDrawArrow();
    ~CDrawArrow();
    BOOL InitDrawArrowMembers(int startx, int starty, int endx, int endy,BOOL stack_flag);
    BOOL Draw();
    BOOL WriteDC(RECT& rcClient);
    void CalculatePoint(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4);

private:
    CPublicResourceManager* m_pPublicResource;
    HPEN m_hPen;
    HDC m_hdc;
    HWND m_hwnd;
    Paint_Struct m_paint_struct;
    BOOL m_bStack_flag;
    int m_nStartx;
    int m_nEndx;
    int m_nStarty;
    int m_nEndy;
    int m_nLeftx;
    int m_nLefty;
    int m_nRightx;
    int m_nRighty;
};

#endif