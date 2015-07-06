#ifndef __PARENT_DRAW_H
#define __PARENT_DRAW_H
#include "resource.h"
#include "PublicResourceManager.h"
#include <GdiPlus.h>
#include <atlstr.h>
using namespace Gdiplus;
class CParentDraw
{
public:
    CParentDraw();
    ~CParentDraw();
    BOOL _SetPenAndBrush();
    BOOL _InitParentDraw(
          int pixel
        , COLORREF color
        , HWND hwnd, HDC hdc
        , int startx
        , int starty
        , int endx
        , int endy
        , BOOL stack_flag
        , CString text = L""
        );
    BOOL IsSaveDc(BOOL saveflag, Paint_Struct temp_struct);
    virtual BOOL Draw() = 0;

protected:
    HWND m_Hwnd;
    HDC m_Hdc;
    HPEN m_hPen;
    HGDIOBJ m_hBrush;
    COLORREF m_Color;
    int m_nPixel;
    int m_nStartx;
    int m_nEndx;
    int m_nStarty;
    int m_nEndy;
    BOOL m_bStack_flag;
    LPCTSTR m_lpString;
};

#endif
