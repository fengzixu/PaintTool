#include "stdafx.h"
#include "DrawText.h"

CDrawText::CDrawText()
{

}
CDrawText::~CDrawText()
{

}

BOOL CDrawText::WriteDC(RECT& rcClient, RECT& rcText)
{
    int nlen = _tcslen(m_lpString);
    HPEN hOldPen = (HPEN)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hPen);
    int nOldMode = ::SetBkMode(m_paint_struct.m_hCompatibleDC, TRANSPARENT);
    ::DrawText
        (
        m_paint_struct.m_hCompatibleDC
        , m_lpString, nlen, &rcText
        , DT_LEFT | DT_WORDBREAK | DT_EDITCONTROL
        );
    ::BitBlt
        (
          m_Hdc
        , 0, 0, rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_paint_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY
        );
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldPen);
    ::SetBkMode(m_paint_struct.m_hCompatibleDC, nOldMode);
    return TRUE;
}

BOOL CDrawText::Draw()
{
    BOOL bRet = FALSE;
    int nlen = _tcslen(m_lpString);
    RECT rcClient = {0};
    RECT rcText = {0};
    ::GetClientRect(m_Hwnd, &rcClient);
    ::SetClassLong(m_Hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_IBEAM));
    ::ShowCursor(TRUE);
    rcText.left = m_nStartx;
    rcText.right = rcClient.right;
    rcText.top = m_nStarty;
    rcText.bottom = rcClient.bottom;

    CPublicResourceManager::GetInstance()->_ClearFrontStack();
    m_paint_struct =  CPublicResourceManager::GetInstance()->_PopDCFromBackStack();

    WriteDC(rcClient, rcText);
    IsSaveDc(m_bStack_flag, m_paint_struct);
    bRet = TRUE;
    return bRet;
}