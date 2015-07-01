#ifndef __DRAW_TEXT_H
#define __DRAW_TEXT_H
#include "ParentDraw.h"
#include <atlstr.h>
class CDrawText : public CParentDraw
{
public:
    CDrawText();
    ~CDrawText();
    BOOL InitDrawTextMembers(int startx, int starty, CString text, BOOL stack_flag);
    BOOL CDrawText::WriteDC(RECT& rcClient, RECT& rcText);
    BOOL Draw();

private:
    CPublicResourceManager* m_pPublicResource;
    HPEN m_hPen;
    HGDIOBJ m_Brush;
    HDC m_hdc;
    HWND m_hwnd;
    Paint_Struct m_paint_struct;
    BOOL m_bStack_flag;
    LPCTSTR m_lpString;
    int m_nStartx;
    int m_nEndx;
    int m_nStarty;
    int m_nEndy;
};

#endif