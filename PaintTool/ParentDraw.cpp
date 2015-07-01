#include "stdafx.h"
#include "ParentDraw.h"

CParentDraw::CParentDraw()
{

}

CParentDraw::~CParentDraw()
{

}

BOOL CParentDraw::_InitParentDraw(int pixel, COLORREF color, HWND hwnd, HDC hdc)
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
    _SetPenAndBrush();
    return 0;
}

HWND CParentDraw::_GetHwnd()
{
    return m_Hwnd;
}

HDC CParentDraw::_GetDc()
{
    return m_Hdc;
}

COLORREF CParentDraw::_GetColor()
{
   return m_Color;
}

int CParentDraw::_GetPixel()
{
     return m_nPixel;
}

HPEN CParentDraw::_GetPen()
{
    return m_hPen;
}

HGDIOBJ CParentDraw::_GetBrush()
{
    return m_hBrush;
}

//BOOL CParentDraw::_SetColor(COLORREF color)
//{
//     m_Color = color;
//     _SetPenAndBrush();
//     return TRUE;
//}
//
//BOOL CParentDraw::_SetPixel(int num)
//{
//     m_nPixel += num;
//     
//     if (m_nPixel < 1)
//     {
//         m_nPixel = 1;
//     }
//     
//     _SetPenAndBrush();
//     return TRUE;
//}

BOOL CParentDraw::_SetPenAndBrush()
{
    m_hPen = ::CreatePen(PS_SOLID, m_nPixel, m_Color);
    m_hBrush = ::GetStockObject(NULL_BRUSH);
    return TRUE;
}

BOOL CParentDraw::IsSaveDc(BOOL saveflag, Paint_Struct temp_struct)
{
    bool returnvalue = TRUE;
    m_pPublicResource = CPublicResourceManager::GetInstance();

    if (m_pPublicResource == NULL)
    {
        returnvalue = FALSE;
    }

    if (DROW == saveflag && m_pPublicResource != NULL)
    {
        m_pPublicResource->_PushDCToBackStack(temp_struct);
    }
    else
    {
        ::DeleteObject(temp_struct.m_hCompatibleBMP);
        ::DeleteDC(temp_struct.m_hCompatibleDC);
    }
    return TRUE;
}