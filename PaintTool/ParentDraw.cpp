#include "stdafx.h"
#include "ParentDraw.h"

CParentDraw::CParentDraw()
{

}

CParentDraw::~CParentDraw()
{

}

BOOL CParentDraw::_InitParentDraw(
                                  int pixel
                                  , COLORREF color
                                  , HWND hwnd, HDC hdc
                                  , int startx
                                  , int starty
                                  , int endx
                                  , int endy
                                  , BOOL stack_flag
                                  , CString text
                                  )
{  
    bool returnvalue = TRUE;

    if (NULL == hwnd)
    {
       returnvalue = FALSE;
    }
    else
    {
       m_Hwnd = hwnd;
    }

    if(NULL == hdc)
    {
        returnvalue = FALSE;
    }
    else
    {
        m_Hdc = hdc;
    }

    m_nPixel = pixel;
    m_Color = color;
    m_nStartx = startx;
    m_nStarty = starty;
    m_nEndx = endx;
    m_nEndy = endy;
    m_bStack_flag = stack_flag;
    m_lpString = text;
    _SetPenAndBrush();
    return 0;
}

BOOL CParentDraw::_SetPenAndBrush()
{
    m_hPen = ::CreatePen(PS_SOLID, m_nPixel, m_Color);
    m_hBrush = ::GetStockObject(NULL_BRUSH);
    return TRUE;
}

BOOL CParentDraw::IsSaveDc(BOOL saveflag, Paint_Struct temp_struct)
{
    bool returnvalue = TRUE;

    if (CPublicResourceManager::GetInstance() == NULL)
    {
        returnvalue = FALSE;
    }

    if (DROW == saveflag && CPublicResourceManager::GetInstance() != NULL)
    {
        CPublicResourceManager::GetInstance()->_PushDCToBackStack(temp_struct);
    }
    else
    {
        ::DeleteObject(temp_struct.m_hCompatibleBMP);
        ::DeleteDC(temp_struct.m_hCompatibleDC);
    }
    return TRUE;
}