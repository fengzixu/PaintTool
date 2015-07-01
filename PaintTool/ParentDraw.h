#ifndef __PARENT_DRAW_H
#define __PARENT_DRAW_H
#include "resource.h"
#include "PublicResourceManager.h"
class CParentDraw
{
public :
    CParentDraw();
    ~CParentDraw();
    HWND _GetHwnd();
    HDC  _GetDc();
    COLORREF _GetColor();
    int _GetPixel();
    HPEN _GetPen();
    HGDIOBJ _GetBrush();
    //BOOL _SetColor(COLORREF color);
    //BOOL _SetPixel(int num);
    BOOL _SetPenAndBrush();
    BOOL _InitParentDraw(int pixel, COLORREF color, HWND hwnd, HDC hdc);
    BOOL PaintLast();
    BOOL IsSaveDc(BOOL saveflag, Paint_Struct temp_struct);
private:
    HWND m_Hwnd;
    HDC m_Hdc;
    HPEN m_hPen;
    HGDIOBJ m_hBrush;
    int m_nPixel;
    COLORREF m_Color;
    CPublicResourceManager* m_pPublicResource;

};

#endif
