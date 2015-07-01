#ifndef __DRAW_LINE_H
#define __DRAW_LINE_H
#include "ParentDraw.h"

class CDrawLine : public CParentDraw
{
public:
    CDrawLine();
    ~CDrawLine();
    BOOL InitDrawLineMembers(int startx, int starty, int endx, int endy,BOOL stack_flag);
    BOOL Draw();

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
};

#endif