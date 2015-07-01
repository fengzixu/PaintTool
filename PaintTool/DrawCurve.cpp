#include "stdafx.h"
#include "DrawCurve.h"

Paint_Struct CDrawCurve::m_static_struct = {0};
CDrawCurve::CDrawCurve()
{

}

CDrawCurve::~CDrawCurve()
{

}

BOOL CDrawCurve::ChangeCursorResource(HCURSOR& hCursor)
{
    hCursor = AtlLoadCursor(IDC_ERRSOR_CURSOR);
    ::SetClassLong(m_hwnd,GCL_HCURSOR,(LONG)(hCursor));
    ::ShowCursor(TRUE);
    return 0;
}

BOOL CDrawCurve::InitDrawCurveMembers(int startx, int starty, int endx, int endy,BOOL stack_flag)
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

BOOL CDrawCurve::WriteDC(RECT& rcClient)
{
    HPEN hOldPen = NULL;
    hOldPen = (HPEN)::SelectObject(m_static_struct.m_hCompatibleDC, m_hPen);
    ::MoveToEx(m_static_struct.m_hCompatibleDC, m_nStartx, m_nStarty, NULL);
    ::LineTo(m_static_struct.m_hCompatibleDC, m_nEndx, m_nEndy);
    ::BitBlt(
          m_hdc, 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_static_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY
        );
    ::SelectObject(m_static_struct.m_hCompatibleDC,hOldPen);
    return TRUE;
}

BOOL CDrawCurve::Draw(BOOL& cureflag)
{
    BOOL bRect = FALSE;
    RECT rcClient = {0};
    Point start_point(m_nStartx, m_nStarty);
    Point end_point(m_nEndx, m_nEndy);
    m_bCureFlag = cureflag;
    ::GetClientRect(m_hwnd, &rcClient);
    m_pPublicResource->_ClearFrontStack();
    if (FALSE == m_bCureFlag)
    {
        m_static_struct = m_pPublicResource->_PopDCFromBackStack();
        cureflag = True;
    }                      
    ::SetClassLong(m_hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);
    WriteDC(rcClient);
    if (m_bStack_flag == DROW)
    {
        m_pPublicResource->_PushDCToBackStack(m_static_struct);
    }
    bRect = True;
    return bRect;
}