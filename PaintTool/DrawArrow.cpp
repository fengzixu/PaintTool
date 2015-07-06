#include "stdafx.h"
#include "DrawArrow.h"
#include <math.h>

CDrawArrow::CDrawArrow()
{
    m_nLeftx = 0;
    m_nLefty = 0;
    m_nRightx = 0;
    m_nRighty = 0;
}

CDrawArrow::~CDrawArrow()
{

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
          m_Hdc
        , 0, 0
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
        , m_paint_struct.m_hCompatibleDC
        , 0, 0, SRCCOPY
        );
    ::SelectObject(m_paint_struct.m_hCompatibleDC, hOldPen);
    return TRUE;
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

BOOL CDrawArrow::Draw()
{
    BOOL bRet = FALSE;
    RECT rcClient = {0};
    int x3 = 0, y3 = 0, x4 = 0, y4 = 0;

    ::GetClientRect(m_Hwnd, &rcClient);
    ::SetClassLong(m_Hwnd, GCL_HCURSOR,(LONG)LoadCursor(NULL, IDC_CROSS));
    ::ShowCursor(TRUE);

    CPublicResourceManager::GetInstance()->_ClearFrontStack();
    m_paint_struct = CPublicResourceManager::GetInstance()->_PopDCFromBackStack();

    WriteDC(rcClient);
    bRet= IsSaveDc(m_bStack_flag, m_paint_struct);
    return bRet;
}