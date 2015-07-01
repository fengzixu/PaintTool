#include "stdafx.h"
#include "DrawRect.h"

CDrawRect::CDrawRect()
{

}

CDrawRect::~CDrawRect()
{

}

BOOL CDrawRect::InitDrawRectMembers(int startx, int starty, int endx, int endy, BOOL stack_flag)
{
    m_nStartx = startx;
    m_nStarty = starty;
    m_nEndx = endx;
    m_nEndy = endy;
    m_bStack_flag = stack_flag;
    m_hdc = _GetDc();
    m_hwnd = _GetHwnd();
    m_hPen = _GetPen();
    m_Brush = _GetBrush();
    m_pPublicResource = CPublicResourceManager::GetInstance();
    return TRUE;
}

BOOL CDrawRect::WriteDC(RECT& rcClient)
{
    HPEN hOldPen = (HPEN)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hPen);
    HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_paint_struct.m_hCompatibleDC, m_Brush);
    ::Rectangle(m_paint_struct.m_hCompatibleDC, m_nStartx ,m_nStarty, m_nEndx, m_nEndy);
    ::BitBlt(
          m_hdc, 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_paint_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY);
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldPen);
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldBrush);
    return TRUE;
}

BOOL CDrawRect::Draw()
{
    BOOL bRet = FALSE;
    RECT rcClient = {0};
    ::GetClientRect(m_hwnd, &rcClient);
    ::SetClassLong(m_hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);
     
    m_pPublicResource->_ClearFrontStack();
    m_paint_struct = m_pPublicResource->_PopDCFromBackStack();
    WriteDC(rcClient);
    bRet = IsSaveDc(m_bStack_flag, m_paint_struct);
    return bRet;
}