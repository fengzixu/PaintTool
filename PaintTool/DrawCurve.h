#ifndef __DRAW_CURVE_H
#define __DRAW_CURVE_H
#include "ParentDraw.h"
#include <GdiPlus.h>
using namespace Gdiplus;

class CDrawCurve : public CParentDraw
{
public:
    CDrawCurve();
    ~CDrawCurve();
    BOOL InitDrawCurveMembers(int startx, int starty, int endx, int endy, BOOL stack_flag);
    BOOL ChangeCursorResource(HCURSOR& hCursor);
    BOOL Draw(BOOL& cureflag);
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
    BOOL m_bCureFlag;
    static Paint_Struct m_static_struct;
};

#endif