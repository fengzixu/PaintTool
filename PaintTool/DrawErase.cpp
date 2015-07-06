#include "stdafx.h"
#include "DrawErase.h"
#include "DrawManager.h"

Paint_Struct CDrawErase::ms_static_struct = {0};
CDrawErase::CDrawErase()
{

}

CDrawErase::~CDrawErase()
{

}

BOOL CDrawErase::ChangeCursorResource(HCURSOR& hCursor)
{
    hCursor = AtlLoadCursor(IDC_ERRSOR_CURSOR);
    ::SetClassLong(m_Hwnd,GCL_HCURSOR,(LONG)(hCursor));
    ::ShowCursor(TRUE);
    return 0;
}


BOOL CDrawErase::WriteDC(RECT& rcClient, HPEN& hPen)
{
    HPEN hOldPen = NULL;
    hOldPen = (HPEN)::SelectObject(ms_static_struct.m_hCompatibleDC, hPen);
    ::MoveToEx(ms_static_struct.m_hCompatibleDC, m_nStartx + 5, m_nStarty +5, NULL);
    ::LineTo(ms_static_struct.m_hCompatibleDC, m_nEndx + 5, m_nEndy + 5);
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

BOOL CDrawErase::Draw()
{
    BOOL bRect = FALSE;
    RECT rcClient = {0};
    HCURSOR hCursor = NULL;
    Point start_point(m_nStartx, m_nStarty);
    Point end_point(m_nEndx, m_nEndy);
    HPEN hPen = CreatePen(PS_SOLID, 15, RGB(255,255,255));
    ::GetClientRect(m_Hwnd, &rcClient);
    CPublicResourceManager::GetInstance()->_ClearFrontStack();
    if (FALSE ==  CDrawManager::GetInstance()->GetCurveFlag())
    {
        ms_static_struct = CPublicResourceManager::GetInstance()->_PopDCFromBackStack();
        CDrawManager::GetInstance()->SetCurveFlag(TRUE);
    }                      
    ChangeCursorResource(hCursor);
    WriteDC(rcClient, hPen);
    if (DROW == m_bStack_flag)
    {
        CPublicResourceManager::GetInstance()->_PushDCToBackStack(ms_static_struct);
    }
    bRect = True;
    return bRect;
}