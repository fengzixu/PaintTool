#ifndef __DRAW_MANAGER_H
#define __DRAW_MANAGER_H

#include "resource.h"
#include "DrawLine.h"
#include "DrawRect.h"
#include "DrawCircle.h"
#include "DrawArrow.h"
#include "DrawPen.h"
#include "DrawErase.h"
#include "DrawText.h"
#include <atlstr.h>
#define BACKSPACE_CODE 0x08
#define BITMAP_FILE_TYPE 0x4d42

class CDrawManager
{
public:
    static CDrawManager* GetInstance();
    BOOL SetDrawType(int nType);
    BOOL Draw(int draw_type);
    BOOL InitMembers(HWND hwnd);
    BOOL SetPixel(int num);
    BOOL SetColor(COLORREF color);
    BOOL PaintLast();
    BOOL Replay();
    BOOL Front();
    BOOL SaveFile();
    BOOL SaveBitmap(TCHAR* filepath);
    BOOL WriteToFile
        (
        BITMAPFILEHEADER& hBitMapFile
        , PBITMAPINFOHEADER& pbihBitMap
        , LPTSTR& pszFile
        , DWORD& dwTemp
        , DWORD& dwTotal
        , DWORD& dwCB
        , BYTE* pbyByte
        , LPBYTE lpBits
        );
   PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
   BOOL ManagerPaint();
   BOOL ManagerButtonDown(POINT point);
   BOOL ManagerButtonUp(POINT point);
   BOOL ManagerButtonMove(POINT point);
   BOOL ManagerButtonChar(WPARAM wParam, LPARAM lParam);
   BOOL ReadyToDrawGraphics(int draw_type);
   BOOL SetCurveFlag(BOOL flag);
   BOOL GetCurveFlag();
private:
    CDrawManager();
    ~CDrawManager();

private:
    static CDrawManager* m_pDrawManager;
    int m_nDownX;
    int m_nDownY;
    int m_nMoveX;
    int m_nMoveY;
    int m_nUpX;
    int m_nUpY;
    int m_nDrawType;
    int m_nIsMouseDown;
    int m_nIsDrawText;
    int m_nIsErasr;
    int m_nIsPen;
    HWND m_temp_hwnd;
    HWND m_hWnd;
    HDC m_temp_dc;
    LPCTSTR lpString;
    CString m_cstrText;
    COLORREF m_Color;
    BOOL m_bPaintflag;
    int m_nPixel;
    BOOL m_bCurveflag;
    CParentDraw* m_pParent;
};


#endif