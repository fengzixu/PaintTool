#include "stdafx.h"
#include "DrawLine.h"

CDrawLine::CDrawLine()
{

}

CDrawLine::~CDrawLine()
{

}

BOOL CDrawLine::InitDrawLineMembers(int startx, int starty, int endx, int endy,BOOL stack_flag)
{
    m_nStartx = startx;
    m_nStarty = starty;
    m_nEndx = endx;
    m_nEndy = endy;
    m_bStack_flag = stack_flag;
    m_hdc = _GetDc();
    m_hwnd = _GetHwnd();
    m_hPen = _GetPen();
    m_pPublicResource = CPublicResourceManager::GetInstance();
    return TRUE;
}

BOOL CDrawLine::Draw()
{
    BOOL bRect = FALSE;
    RECT rcClient = {0};
    ::SetClassLong(m_hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);
    ::GetClientRect(m_hwnd, &rcClient);

    m_pPublicResource->_ClearFrontStack();
    m_paint_struct = m_pPublicResource->_PopDCFromBackStack();

    HPEN hOldPen = (HPEN)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hPen);
    ::MoveToEx(m_paint_struct.m_hCompatibleDC, m_nStartx, m_nStarty, NULL);
    ::LineTo(m_paint_struct.m_hCompatibleDC, m_nEndx, m_nEndy);
    ::BitBlt(
          m_hdc, 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_paint_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY);
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldPen);
    bRect = IsSaveDc(m_bStack_flag, m_paint_struct);
    return bRect;
}