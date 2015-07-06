#include "stdafx.h"
#include "resource.h"
#include "PaintToolView.h"


BOOL CPaintToolView::InitManagerMembers()
{
    CDrawManager::GetInstance()->InitMembers(m_hWnd);
    m_bPaintflag = TRUE;
    return TRUE;
}

LRESULT CPaintToolView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CPaintDC dc(m_hWnd);
    CDrawManager::GetInstance()->ManagerPaint();                   //Ë¢ÐÂÖØ»æº¯Êý
    return 0;
}

BOOL CPaintToolView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CPaintToolView::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    POINT m_point = {0};
    GetCursorPos(&m_point);
    ScreenToClient(&m_point);
    CDrawManager::GetInstance()->ManagerButtonDown(m_point);
    return 0;
}

LRESULT CPaintToolView::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    POINT m_point = {0};
    GetCursorPos(&m_point);
    ScreenToClient(&m_point);
    CDrawManager::GetInstance()->ManagerButtonUp(m_point);
    return 0;
}
LRESULT CPaintToolView::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    POINT pointUpPoint = {0};
    GetCursorPos(&pointUpPoint);
    ScreenToClient(&pointUpPoint);
    CDrawManager::GetInstance()->ManagerButtonMove(pointUpPoint);
    return 0;
}
LRESULT CPaintToolView::OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    CDrawManager::GetInstance()->ManagerButtonChar(wParam, lParam);
    return 0;
}

BOOL CPaintToolView::SetDrawType(int nType)
{
    CDrawManager::GetInstance()->SetDrawType(nType);
    return TRUE;
}
