#include "stdafx.h"
#include "PublicResourceManager.h"

CPublicResourceManager* CPublicResourceManager::m_pPublic_resource_manager = NULL;
CPublicResourceManager::CPublicResourceManager()
{
     m_bPushFlag = FALSE;
     m_bFirstPainCurve = FALSE;
}

CPublicResourceManager::~CPublicResourceManager()
{

}
CPublicResourceManager* CPublicResourceManager::GetInstance()
{
    if (m_pPublic_resource_manager == NULL)
    {
        m_pPublic_resource_manager = new CPublicResourceManager();
    }

    return m_pPublic_resource_manager;
}

HWND CPublicResourceManager::_GetHwnd()
{
    return m_Hwnd;
}

HDC CPublicResourceManager::_GetDc()
{
    return m_Hdc;
}

BOOL CPublicResourceManager::_SetHDC()
{
    BOOL returnvalue = TRUE;
    RECT rcClient = {0};
    SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &m_rcScreen, 0);
    ::GetClientRect(m_Hwnd, &rcClient);                                                  //获取到用户区域
    m_Hdc = ::GetDC(m_Hwnd);                                                         //获取画布
    m_Paint_struct.m_hCompatibleDC = ::CreateCompatibleDC(m_Hdc);                    //创建兼容DC,利用双缓冲技术防止闪烁Z
    m_Paint_struct.m_hCompatibleBMP = ::CreateCompatibleBitmap
    (
          m_Hdc
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
    );

    if (NULL == m_Hdc || NULL == m_Paint_struct.m_hCompatibleDC || NULL == m_Paint_struct.m_hCompatibleBMP)
    {
        returnvalue = FALSE;
    }

    m_Paint_struct.nWidth = rcClient.right - rcClient.left;
    m_Paint_struct.nHigh = rcClient.bottom - rcClient.top;
    m_Paint_struct.m_hBitMap = (HBITMAP)::SelectObject(m_Paint_struct.m_hCompatibleDC, m_Paint_struct.m_hCompatibleBMP);
    ::StretchBlt(
        m_Paint_struct.m_hCompatibleDC
        , 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top
        , m_Hdc
        , 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top
        ,SRCCOPY);
    if (FALSE == m_bPushFlag)
    {
        _PushDCToBackStack(m_Paint_struct);
        m_bPushFlag = TRUE;
    }
    //_PushDCToBackStack(m_Paint_struct);
    return returnvalue;
}

BOOL CPublicResourceManager::_SetHwnd(HWND hwnd)
{
    BOOL returnvalue = TRUE;

    if (NULL == hwnd)
    {
        returnvalue = FALSE;
    }
    else
    {
        m_Hwnd = hwnd;
        if (FALSE == _SetHDC())
        {
            returnvalue = FALSE;
        }
    }
    
    return returnvalue;
}

BOOL CPublicResourceManager::_PushDCToBackStack(Paint_Struct old_paint)
{
    m_BackStack.push(old_paint);
    return TRUE;
}

Paint_Struct CPublicResourceManager::_PopDCFromBackStack()
{
    RECT rcClient = {0};
    Paint_Struct paint_temp = {0};
    ::GetClientRect(m_Hwnd, &rcClient);
    paint_temp = m_BackStack.top();
    m_Paint_struct.m_hCompatibleDC = ::CreateCompatibleDC(paint_temp.m_hCompatibleDC);
    m_Paint_struct.m_hCompatibleBMP = ::CreateCompatibleBitmap
    (
          paint_temp.m_hCompatibleDC
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
    );
    m_Paint_struct.m_hBitMap = (HBITMAP)::SelectObject(m_Paint_struct.m_hCompatibleDC, m_Paint_struct.m_hCompatibleBMP);
    Rectangle
        (
          m_Paint_struct.m_hCompatibleDC
        , 0, 0, (rcClient.right - rcClient.left) + 10
        , (rcClient.bottom - rcClient.top) + 10
        );
    ::StretchBlt
    (
          m_Paint_struct.m_hCompatibleDC
        , 0 ,0, m_Paint_struct.nWidth
        , m_Paint_struct.nHigh
        , paint_temp.m_hCompatibleDC
        , 0, 0
        , m_Paint_struct.nWidth
        , m_Paint_struct.nHigh
        , SRCCOPY
    );
    return m_Paint_struct;
}
BOOL CPublicResourceManager::_PopBackStack()
{
    Paint_Struct paint_temp = {0};
    paint_temp = m_BackStack.top();
    ::DeleteObject(paint_temp.m_hCompatibleBMP);
    ::DeleteDC(paint_temp.m_hCompatibleDC);
    m_BackStack.pop();
    return TRUE;
}
BOOL CPublicResourceManager::_ClearFrontStack()
{
    Paint_Struct temp = {0};
    while(m_FrontStack.size() != 0)
    {
        temp = m_FrontStack.top();
        ::DeleteObject(temp.m_hCompatibleBMP);
        ::DeleteDC(temp.m_hCompatibleDC);
        m_FrontStack.pop();
    }
    return TRUE;
}
BOOL CPublicResourceManager::_ClearBackStack()
{
    Paint_Struct temp = {0};
    while(m_BackStack.size() != 0)
    {
        temp = m_BackStack.top();
        ::DeleteObject(temp.m_hCompatibleBMP);
        ::DeleteDC(temp.m_hCompatibleDC);
        m_BackStack.pop();
    }
    return TRUE;

}
BOOL CPublicResourceManager::_PushDCToFrontStack(Paint_Struct old_paint)
{
    m_FrontStack.push(old_paint);
    return TRUE;
}
Paint_Struct CPublicResourceManager::_PopDCFromFrontStack()
{
    RECT rcClient = {0};
    Paint_Struct paint_temp = {0};
    ::GetClientRect(m_Hwnd, &rcClient);
    paint_temp = m_FrontStack.top();
    m_Paint_struct.m_hCompatibleDC = ::CreateCompatibleDC(paint_temp.m_hCompatibleDC);
    m_Paint_struct.m_hCompatibleBMP = ::CreateCompatibleBitmap
    (     paint_temp.m_hCompatibleDC
        , rcClient.right - rcClient.left
        , rcClient.bottom - rcClient.top
    );
    m_Paint_struct.m_hBitMap = (HBITMAP)::SelectObject(m_Paint_struct.m_hCompatibleDC, m_Paint_struct.m_hCompatibleBMP);
    Rectangle(m_Paint_struct.m_hCompatibleDC, 0, 0, (rcClient.right - rcClient.left) + 10, (rcClient.bottom - rcClient.top) + 10);
    ::StretchBlt(
        m_Paint_struct.m_hCompatibleDC
        , 0, 0, m_Paint_struct.nWidth
        , m_Paint_struct.nHigh
        , paint_temp.m_hCompatibleDC
        , 0, 0
        , m_Paint_struct.nWidth
        , m_Paint_struct.nHigh
        , SRCCOPY
        );
    return m_Paint_struct;
}
BOOL CPublicResourceManager::_PopFrontStack()
{
    Paint_Struct paint_temp = {0};
    paint_temp = m_FrontStack.top();
    ::DeleteObject(paint_temp.m_hCompatibleBMP);
    ::DeleteDC(paint_temp.m_hCompatibleDC);
    m_FrontStack.pop();
    return TRUE;
}


BOOL CPublicResourceManager::Reaplay()
{
    Paint_Struct temp_paint = {0};
    BOOL bRet = FALSE;
    RECT rcClient = {0};
    ::GetClientRect(m_Hwnd, &rcClient);
    if(m_BackStack.size() > 1)
    {
        temp_paint = _PopDCFromBackStack();
        _PopBackStack();
        _PushDCToFrontStack(temp_paint);
        temp_paint = _PopDCFromBackStack();
        ::BitBlt(
              m_Hdc, 0, 0
            , rcClient.right - rcClient.left
            , rcClient.bottom - rcClient.top
            , temp_paint.m_hCompatibleDC
            , 0, 0
            , SRCCOPY
            );
        bRet = TRUE;
    }
    return bRet;

}

BOOL CPublicResourceManager::Front()
{
    Paint_Struct temp_paint = {0};
    BOOL bRet = FALSE;
    RECT rcClient = {0};
    ::GetClientRect(m_Hwnd, &rcClient);
    if(m_FrontStack.size() > 0)
    {
        temp_paint = _PopDCFromFrontStack();
        _PopFrontStack();
        _PushDCToBackStack(temp_paint);
        ::BitBlt(
              m_Hdc, 0, 0
            , rcClient.right - rcClient.left
            , rcClient.bottom - rcClient.top
            , temp_paint.m_hCompatibleDC
            , 0, 0
            , SRCCOPY
            );
        bRet = TRUE;
    }
    return bRet;
}

BOOL CPublicResourceManager::_GetCurveFlag()
{
    return m_bFirstPainCurve;
}

BOOL CPublicResourceManager::_SetCurveFlag(BOOL inputflag)
{
    m_bFirstPainCurve = inputflag;
    return TRUE;
}