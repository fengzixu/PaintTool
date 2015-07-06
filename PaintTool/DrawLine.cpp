#include "stdafx.h"
#include "DrawLine.h"
CDrawLine::CDrawLine()
{

}

CDrawLine::~CDrawLine()
{

}

BOOL CDrawLine::WriteDC(RECT& rcClient)
{
    HPEN hOldPen = (HPEN)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hPen);
    ::MoveToEx(m_paint_struct.m_hCompatibleDC, m_nStartx, m_nStarty, NULL);
    ::LineTo(m_paint_struct.m_hCompatibleDC, m_nEndx, m_nEndy);
    ::BitBlt(
        m_Hdc, 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_paint_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY);
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldPen);
    return TRUE;
}

BOOL CDrawLine::Draw()
{
    BOOL bRect = FALSE;
    RECT rcClient = {0};
    ::SetClassLong(m_Hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);
    ::GetClientRect(m_Hwnd, &rcClient);

    CPublicResourceManager::GetInstance()->_ClearFrontStack();
    m_paint_struct = CPublicResourceManager::GetInstance()->_PopDCFromBackStack();
    WriteDC(rcClient);
    bRect = IsSaveDc(m_bStack_flag, m_paint_struct);
    return bRect;
}