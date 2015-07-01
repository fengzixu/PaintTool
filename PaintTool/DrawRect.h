#ifndef __DRAW_RECT_H
#define __DRAW_RECT_H

#include "ParentDraw.h"

class  CDrawRect :public CParentDraw
{
public:
    CDrawRect();
    ~CDrawRect();
    BOOL InitDrawRectMembers(int startx, int starty, int endx, int endy,BOOL stack_flag);
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