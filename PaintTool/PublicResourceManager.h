
#ifndef __PUBLIC_RESOURCE_H
#define __PUBLIC_RESOURCE_H
#include "resource.h"
#include <stack>
typedef struct _Paint
{
    HDC m_hCompatibleDC;
    HBITMAP m_hCompatibleBMP;
    HBITMAP m_hBitMap;
    int nWidth;
    int nHigh;
}Paint_Struct;

class CPublicResourceManager
{
public:
    static CPublicResourceManager* GetInstance();
    BOOL Reaplay();
    BOOL Front();
    BOOL _PushDCToBackStack(Paint_Struct old_paint);
    Paint_Struct _PopDCFromBackStack();
    BOOL _PopBackStack();
    BOOL _ClearFrontStack();
    BOOL _ClearBackStack();
    BOOL _PushDCToFrontStack(Paint_Struct old_paint);
    Paint_Struct _PopDCFromFrontStack();
    BOOL _PopFrontStack();
    BOOL _SetHwnd(HWND hwnd);
    BOOL _SetHDC();
    BOOL _SetClientRC();
    BOOL _SetPenAndBrush();
    BOOL _SetCurveFlag(BOOL inputflag);
    HWND _GetHwnd();
    HDC  _GetDc();
    BOOL _GetCurveFlag();

private:
    CPublicResourceManager();
    ~CPublicResourceManager();
    
private:
    static CPublicResourceManager* m_pPublic_resource_manager;
    std::stack<Paint_Struct>m_BackStack;
    std::stack<Paint_Struct>m_FrontStack;
    Paint_Struct m_Paint_struct;
    HWND m_Hwnd;
    HDC m_Hdc;
    RECT m_rcScreen;
    BOOL m_bPushFlag;
    BOOL m_bFirstPainCurve;
};

#endif