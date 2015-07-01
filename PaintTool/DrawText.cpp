#include "stdafx.h"
#include "DrawText.h"

CDrawText::CDrawText()
{

}

CDrawText::~CDrawText()
{

}

BOOL CDrawText::InitDrawTextMembers(int startx, int starty, CString text, BOOL stack_flag)
{
    m_nStartx = startx;
    m_nStarty = starty;
    m_bStack_flag = stack_flag;
    m_lpString = text;
    m_hdc = _GetDc();
    m_hwnd = _GetHwnd();
    m_hPen = _GetPen();
    m_Brush = _GetBrush();
    m_pPublicResource = CPublicResourceManager::GetInstance();
    return TRUE;
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
          m_hdc
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
    ::GetClientRect(m_hwnd, &rcClient);
    ::SetClassLong(m_hwnd, GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_IBEAM));
    ::ShowCursor(TRUE);
    rcText.left = m_nStartx;
    rcText.right = rcClient.right;
    rcText.top = m_nStarty;
    rcText.bottom = rcClient.bottom;

    m_pPublicResource->_ClearFrontStack();
    m_paint_struct = m_pPublicResource->_PopDCFromBackStack();

    WriteDC(rcClient, rcText);
    IsSaveDc(m_bStack_flag, m_paint_struct);
    bRet = TRUE;
    return bRet;
}