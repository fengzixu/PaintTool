// PaintToolView.h : interface of the CPaintToolView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlstr.h>
#include "PublicResourceManager.h"
#include <GdiPlus.h>
using namespace Gdiplus;

class CPaintToolView : public CWindowImpl<CPaintToolView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CPaintToolView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
        MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
        MESSAGE_HANDLER(WM_CHAR, OnChar)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
    LRESULT OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    BOOL SetDrawType(int nType);
    BOOL Draw(int draw_type);
    BOOL InitMembers();
    BOOL SetPixel(int num);
    BOOL SetColor(COLORREF color);
    BOOL PaintLast();
    BOOL Replay();
    BOOL Front();
    BOOL SaveFile();
    BOOL SaveBitmap(TCHAR* filepath);
    BOOL CPaintToolView::WriteToFile
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
private:
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
    HDC m_temp_dc;
    LPCTSTR lpString;
    CString m_cstrText;
    COLORREF m_Color;
    BOOL m_bPaintflag;
    int m_nPixel;
    BOOL m_bCurveflag;
    CPublicResourceManager* m_PublicResourceManager;
};
