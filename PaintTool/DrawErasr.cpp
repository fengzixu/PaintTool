#include "stdafx.h"
#include "DrawErasr.h"

Paint_Struct CDrawErasr::m_static_struct = {0};

CDrawErasr::CDrawErasr()
{

}

CDrawErasr::~CDrawErasr()
{

}

BOOL CDrawErasr::ChangeCursorResource(HCURSOR& hCursor)
{
    hCursor = AtlLoadCursor(IDC_ERRSOR_CURSOR);
    ::SetClassLong(m_hwnd, GCL_HCURSOR, (LONG)(hCursor));
    ::ShowCursor(TRUE);
    return 0;
}

BOOL CDrawErasr::InitDrawErasrMembers(int startx, int starty, int endx, int endy,BOOL stack_flag)
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

BOOL CDrawErasr::WriteDC(RECT& rcClient)
{
    HPEN hPen = CreatePen(PS_SOLID, 15, RGB(255,255,255));
    HPEN hOldPen = NULL;
    hOldPen = (HPEN)::SelectObject(m_static_struct.m_hCompatibleDC, hPen);
    ::MoveToEx(m_static_struct.m_hCompatibleDC, m_nStartx + 5, m_nStarty +5, NULL);
    ::LineTo(m_static_struct.m_hCompatibleDC, m_nEndx + 5, m_nEndy + 5);
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

BOOL CDrawErasr::Draw(BOOL& cureflag)
{
    BOOL bRect = FALSE;
    RECT rcClient = {0};
    HPEN hOldPen = NULL;
    HCURSOR hCursor = NULL;
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
    ChangeCursorResource(hCursor);
    WriteDC(rcClient);
    if (m_bStack_flag == DROW)
    {
        m_pPublicResource->_PushDCToBackStack(m_static_struct);
    }
    bRect = True;
    return bRect;
}