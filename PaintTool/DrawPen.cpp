#include "stdafx.h"
#include "DrawPen.h"
#include "DrawManager.h"

Paint_Struct CDrawPen::ms_static_struct = {0};
CDrawPen::CDrawPen()
{

}

CDrawPen::~CDrawPen()
{

}

BOOL CDrawPen::WriteDC(RECT& rcClient)
{
    HPEN hOldPen = NULL;
    hOldPen = (HPEN)::SelectObject(ms_static_struct.m_hCompatibleDC, m_hPen);
    ::MoveToEx(ms_static_struct.m_hCompatibleDC, m_nStartx, m_nStarty, NULL);
    ::LineTo(ms_static_struct.m_hCompatibleDC, m_nEndx, m_nEndy);
    ::BitBlt(
          m_Hdc, 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , ms_static_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY
        );
    ::SelectObject(ms_static_struct.m_hCompatibleDC,hOldPen);
    return TRUE;
}

BOOL CDrawPen::Draw()
{
    BOOL bRect = FALSE;
    RECT rcClient = {0};
    Point start_point(m_nStartx, m_nStarty);
    Point end_point(m_nEndx, m_nEndy);
    ::GetClientRect(m_Hwnd, &rcClient);
    CPublicResourceManager::GetInstance()->_ClearFrontStack();
    if (FALSE ==  CDrawManager::GetInstance()->GetCurveFlag())
    {
        ms_static_struct = CPublicResourceManager::GetInstance()->_PopDCFromBackStack();
        CDrawManager::GetInstance()->SetCurveFlag(TRUE);
    }                      
    ::SetClassLong(m_Hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);
    WriteDC(rcClient);
    if (DROW == m_bStack_flag)
    {
        CPublicResourceManager::GetInstance()->_PushDCToBackStack(ms_static_struct);
    }
    bRect = True;
    return bRect;
}