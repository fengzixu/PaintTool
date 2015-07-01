#include "stdafx.h"
#include "DrawArrow.h"
#include <math.h>
CDrawArrow::CDrawArrow()
{

}

CDrawArrow::~CDrawArrow()
{

}

BOOL CDrawArrow::InitDrawArrowMembers(int startx, int starty, int endx, int endy,BOOL stack_flag)
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

BOOL CDrawArrow::WriteDC(RECT& rcClient)
{
    HPEN hOldPen = (HPEN)::SelectObject(m_paint_struct.m_hCompatibleDC, m_hPen);
    CalculatePoint(m_nStartx, m_nStarty, m_nEndx, m_nEndy, m_nLeftx, m_nLefty, m_nRightx, m_nRighty);
    ::MoveToEx(m_paint_struct.m_hCompatibleDC, m_nStartx, m_nStarty, NULL);
    ::LineTo(m_paint_struct.m_hCompatibleDC, m_nEndx, m_nEndy);
    ::MoveToEx(m_paint_struct.m_hCompatibleDC, m_nEndx, m_nEndy, NULL);
    ::LineTo(m_paint_struct.m_hCompatibleDC, m_nLeftx, m_nLefty);
    ::MoveToEx(m_paint_struct.m_hCompatibleDC, m_nEndx, m_nEndy, NULL);
    ::LineTo(m_paint_struct.m_hCompatibleDC, m_nRightx, m_nRighty);
    ::BitBlt(
        m_hdc
        , 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_paint_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY
        );
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldPen);
    return TRUE;
}

BOOL CDrawArrow::Draw()
{
    BOOL bRet = FALSE;
    RECT rcClient = {0};
    int x3 = 0, y3 = 0, x4 = 0, y4 = 0;

    ::GetClientRect(m_hwnd, &rcClient);
    ::SetClassLong(m_hwnd, GCL_HCURSOR,(LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);

    m_pPublicResource->_ClearFrontStack();
    m_paint_struct = m_pPublicResource->_PopDCFromBackStack();

    WriteDC(rcClient);
    bRet= IsSaveDc(m_bStack_flag, m_paint_struct);
    return bRet;
}

void CDrawArrow::CalculatePoint(int x1, int y1, int x2, int y2, int &x3, int &y3, int &x4, int &y4)
{
    double fLong = sqrt((double)(y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)) / 10;
    double fX = x2- (x2- x1) / 3;
    double fY = y2- (y2- y1) / 3;
    double fAngle = atan((double)(y2 - y1)/(double)(x2 - x1));
    double fValueX = sin(fAngle) * fLong;
    double fValueY = cos(fAngle) * fLong;
    x3 = (int)(fX - fValueX);
    y3 = (int)(fY + fValueY);
    x4 = (int)(fX + fValueX);
    y4 = (int)(fY - fValueY);
}