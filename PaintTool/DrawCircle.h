#ifndef __DRAW_CIRCLE_H
#define __DRAW_CIRCLE_H

#include "ParentDraw.h"
#include <GdiPlus.h>
using namespace Gdiplus;

class CDrawCircle : public CParentDraw
{
public:
    CDrawCircle();
    ~CDrawCircle();
    BOOL InitDrawCircleMembers(int startx, int starty, int endx, int endy,BOOL stack_flag);
    BOOL Draw();
    BOOL WriteDC(RECT& rcClient);

private:
    CPublicResourceManager* m_pPublicResource;
    HPEN m_hPen;
    HGDIOBJ m_Brush;
    HDC m_hdc;
    HWND m_hwnd;
    Paint_Struct m_paint_struct;
    BOOL m_bStack_flag;
    int m_nStartx;
    int m_nEndx;
    int m_nStarty;
    int m_nEndy;
};

#endif