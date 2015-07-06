#include "stdafx.h"
#include "DrawRect.h"


CDrawRect::CDrawRect()
{

}

CDrawRect::~CDrawRect()
{

}

BOOL CDrawRect::WriteDC(RECT& rcClient)
{
    HPEN hOldPen = (HPEN)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hPen);
    HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hBrush);
    ::Rectangle(m_paint_struct.m_hCompatibleDC, m_nStartx ,m_nStarty, m_nEndx, m_nEndy);
    ::BitBlt(
          m_Hdc, 0, 0
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
    ::GetClientRect(m_Hwnd, &rcClient);
    ::SetClassLong(m_Hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);

    CPublicResourceManager::GetInstance()->_ClearFrontStack();
    m_paint_struct =  CPublicResourceManager::GetInstance()->_PopDCFromBackStack();
    WriteDC(rcClient);
    bRet = IsSaveDc(m_bStack_flag, m_paint_struct);
    return bRet;
}