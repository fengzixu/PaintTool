#include "stdafx.h"
#include "resource.h"
#include "PaintToolView.h"
#include "PublicResourceManager.h"
#include "ParentDraw.h"
#include "DrawLine.h"
#include "DrawRect.h"
#include "DrawCircle.h"
#include "DrawCurve.h"
#include "DrawErasr.h"
#include "DrawArrow.h"
#include "DrawText.h"

#define BACKSPACE_CODE 0x08
#define BITMAP_FILE_TYPE 0x4d42
BOOL CPaintToolView::InitMembers()
{
    m_PublicResourceManager = CPublicResourceManager::GetInstance();
    m_nDownX = 0;
    m_nDownY = 0;
    m_nMoveX = 0;
    m_nMoveY = 0;
    m_nUpX = 0;
    m_nUpY = 0;
    m_nDrawType = 0;
    m_nIsMouseDown = 0;
    m_nIsDrawText = 0;
    m_nIsErasr = 0;
    m_nIsPen = 0;
    m_Color = RGB(0, 0, 0);
    m_nPixel = 1;
    m_temp_hwnd  = NULL;
    m_temp_dc = NULL;
    m_bPaintflag = FALSE;
    m_bCurveflag = FALSE;
    return TRUE;
}

LRESULT CPaintToolView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CPaintDC dc(m_hWnd);
    //TODO: Add your drawing code here
    PaintLast();
    if(m_nIsDrawText == 1)
    {
        Draw(DROWBACK);
    }
    return 0;
}

BOOL CPaintToolView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

BOOL CPaintToolView::Draw(int draw_type)
{
    m_bPaintflag = TRUE;
    switch(m_nDrawType)
    {
    case DRAW_LINE:
        {
          CDrawLine drawline;
          drawline._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
          drawline.InitDrawLineMembers(m_nDownX, m_nDownY, m_nUpX, m_nUpY, draw_type);
          drawline.Draw();
        }
        break;
    case DRAW_RECT:
        {
          CDrawRect drawrect;
          drawrect._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
          drawrect.InitDrawRectMembers(m_nDownX, m_nDownY, m_nUpX, m_nUpY, draw_type);
          drawrect.Draw();
        }
        break;

    case DRAW_CIRCLE:
        {
           CDrawCircle drawcircle;
           drawcircle._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
           drawcircle.InitDrawCircleMembers(m_nDownX, m_nDownY, m_nUpX, m_nUpY, draw_type);
           drawcircle.Draw();
        }
        break;
    case DRAW_PEN:
        {
            CDrawCurve drawcurve;
            drawcurve._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
            drawcurve.InitDrawCurveMembers(m_nDownX, m_nDownY, m_nUpX, m_nUpY, draw_type);
            drawcurve.Draw(m_bCurveflag);
        }
        break;
    case DRAW_CLEAR:
        {
           CDrawErasr drawerasr;
           drawerasr._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
           drawerasr.InitDrawErasrMembers(m_nDownX, m_nDownY, m_nUpX, m_nUpY, draw_type);
           drawerasr.Draw(m_bCurveflag);
        }
        break;
    case DRAW_ARROW:
        {
            CDrawArrow drawarrow;
            drawarrow._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
            drawarrow.InitDrawArrowMembers(m_nDownX, m_nDownY, m_nUpX, m_nUpY, draw_type);
            drawarrow.Draw();
        }
        break;
    case DRAW_TEXT:
        {
            CDrawText drawtext;
            drawtext._InitParentDraw(m_nPixel, m_Color, m_PublicResourceManager->_GetHwnd(), m_PublicResourceManager->_GetDc());
            drawtext.InitDrawTextMembers(m_nDownX, m_nDownY, m_cstrText, draw_type);
            drawtext.Draw();
        }
        break;
    }

    return TRUE;
}

LRESULT CPaintToolView::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    m_PublicResourceManager->_SetHwnd(m_hWnd);
    POINT m_point = {0};
    GetCursorPos(&m_point);
    ScreenToClient(&m_point);
    if(m_nIsDrawText != 1)
    {
        m_nDownX = m_point.x;
        m_nDownY = m_point.y;
    }
    m_nIsMouseDown = 1;
    if(m_nDrawType ==  DRAW_TEXT)
    {
        m_nIsDrawText = m_nIsDrawText == 1 ? 0 : 1;
        if (m_nIsDrawText == 0)                             //已经换了位置写字，之前的要保存，并且清空字符串缓冲区
        {
            m_cstrText.Delete(m_cstrText.GetLength() - 1);
            Draw(DROW);
            m_nDownX = m_point.x;
            m_nDownY = m_point.y;
            m_cstrText.Empty();
            m_cstrText = "|";
            m_nIsDrawText = 1;
        }
        else
        {
            m_cstrText = "|";
            Draw(DROWBACK);
        }
    }
    return 0;
}

LRESULT CPaintToolView::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    POINT m_point = {0};
    GetCursorPos(&m_point);
    ScreenToClient(&m_point);
    m_nUpX = m_point.x;
    m_nUpY = m_point.y;
    m_nIsMouseDown = 0;
    if(m_nDrawType != DRAW_TEXT)
    {
        Draw(DROW);
        m_bCurveflag = FALSE;
    }
    return 0;
}
LRESULT CPaintToolView::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    if(m_nIsMouseDown == 1 && m_nDrawType != DRAW_TEXT)
    {
        POINT pointUpPoint = {0};
        GetCursorPos(&pointUpPoint);
        ScreenToClient(&pointUpPoint);
        m_nUpX = pointUpPoint.x;
        m_nUpY   = pointUpPoint.y;
        if(m_nIsErasr == 1 || m_nIsPen == 1)
        {
            Draw(DROWBACK);
            m_nDownX = m_nUpX;
            m_nDownY = m_nUpY;
        }
        else
            Draw(DROWBACK);
    }
    return 0;
}
LRESULT CPaintToolView::OnChar(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (1 == m_nIsDrawText)
    {
        int old_length = m_cstrText.GetLength();
        if(BACKSPACE_CODE == wParam)                  //如果是退格键
        {
            m_cstrText.Delete(m_cstrText.GetLength() - 1);                      //删除结束符，还有一个真正的符号
            m_cstrText.Delete(m_cstrText.GetLength() - 1);
            m_cstrText += "|";
        }
        else
        {
            CString csTemp = "";
            csTemp.Format(_T("%c"), wParam);
            m_cstrText.Delete(m_cstrText.GetLength() - 1);
            m_cstrText += csTemp;
            m_cstrText += "|";
        }
        if(m_cstrText.GetLength() != old_length)
        {
            Draw(m_nIsDrawText == 1 ? DRAW_BACK : DROW);
        }
    }
    return 0;
}

BOOL CPaintToolView::SetDrawType(int nType)
{
    m_nDrawType = nType;
    m_nIsErasr = m_nIsPen = 0;
    if (m_nDrawType != DRAW_TEXT)
        m_nIsDrawText = 0;
    if(nType == DRAW_CLEAR)
        m_nIsErasr = 1;
    if(nType == DRAW_PEN)
        m_nIsPen = 1;
    if(m_nDrawType == DRAW_CLEAR || m_nDrawType == DRAW_PEN)
        m_bCurveflag = FALSE;
    return TRUE;
}

BOOL CPaintToolView::SetPixel(int num)
{
    m_nPixel += num;

    if (m_nPixel < 1)
    {
        m_nPixel = 1;
    }
    return TRUE;
}

BOOL CPaintToolView::SetColor(COLORREF color)
{
    m_Color = color;
    return TRUE;
}

BOOL CPaintToolView::PaintLast()
{   
    Paint_Struct temp_struct = {0};
    if(m_temp_hwnd != NULL && m_temp_dc != NULL)
    {
        temp_struct = m_PublicResourceManager->_PopDCFromBackStack();

        RECT rcClient;
        ::GetClientRect(m_temp_hwnd, &rcClient);
        ::BitBlt(
            m_temp_dc, 0, 0,
            rcClient.right - rcClient.left,
            rcClient.bottom - rcClient.top,
            temp_struct.m_hCompatibleDC,
            0, 0, SRCCOPY);
    }
    if (m_PublicResourceManager != NULL && m_bPaintflag != FALSE)
    {
        m_temp_dc = m_PublicResourceManager->_GetDc();
        m_temp_hwnd = m_PublicResourceManager->_GetHwnd();
    }
    return TRUE;
}

BOOL CPaintToolView::Replay()
{
   if (FALSE == m_PublicResourceManager->Reaplay())
   {
       MessageBox(L"已经不能回退了，亲。\r\n(づ￣3￣)づ╭?～",L"出错啦",MB_OK);
   }
   else
   {
       if (m_nDrawType != DRAW_TEXT)
           m_nIsDrawText = 0;
   }
   return TRUE;
}

BOOL CPaintToolView::Front()
{
    
    if (FALSE == m_PublicResourceManager->Front())
    {
        MessageBox(L"已经不能恢复了，亲。\r\n(づ￣3￣)づ╭?～",L"出错啦",MB_OK);
    }
    else
    {
        if (m_nDrawType != DRAW_TEXT)
            m_nIsDrawText = 0;
    }
    return TRUE;
}

PBITMAPINFO CPaintToolView::CreateBitmapInfoStruct(HBITMAP hBmp)
{
    BITMAP bmBmp = {0}; 
    PBITMAPINFO pbmiBitMapInfo = NULL; 
    WORD    wClrBits = 0; 
    if (!::GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmBmp))
    {
        goto EXIT0;
    }
    wClrBits = (WORD)(bmBmp.bmPlanes * bmBmp.bmBitsPixel);
    if (wClrBits == 1)
    {
        wClrBits = 1; 
    }
    else if (wClrBits <= 4)
    {
        wClrBits = 4;
    }
    else if (wClrBits <= 8)
    {
         wClrBits = 8;
    }
    else if (wClrBits <= 16)
    {
        wClrBits = 16;
    }
    else if (wClrBits <= 24)
    {
         wClrBits = 24; 
    }
    else
    {
       wClrBits = 32;
    } 
    if (wClrBits != 24) 
    {
        pbmiBitMapInfo = (PBITMAPINFO) LocalAlloc(LPTR
            , sizeof(BITMAPINFOHEADER)
            + sizeof(RGBQUAD) * (1<< wClrBits));
    }
    else 
    {
        pbmiBitMapInfo = (PBITMAPINFO) LocalAlloc(LPTR,
            sizeof(BITMAPINFOHEADER)); 
    }
    pbmiBitMapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmiBitMapInfo->bmiHeader.biWidth = bmBmp.bmWidth;
    pbmiBitMapInfo->bmiHeader.biHeight = bmBmp.bmHeight;
    pbmiBitMapInfo->bmiHeader.biPlanes = bmBmp.bmPlanes;
    pbmiBitMapInfo->bmiHeader.biBitCount = bmBmp.bmBitsPixel;
    if (wClrBits < 24) 
    {
        pbmiBitMapInfo->bmiHeader.biClrUsed = (1 << wClrBits);
    }
    pbmiBitMapInfo->bmiHeader.biCompression = BI_RGB;
    pbmiBitMapInfo->bmiHeader.biSizeImage = ((pbmiBitMapInfo->bmiHeader.biWidth * wClrBits +31) & ~31) /8
        * pbmiBitMapInfo->bmiHeader.biHeight;
    pbmiBitMapInfo->bmiHeader.biClrImportant = 0;
EXIT0:
    return pbmiBitMapInfo;
}


BOOL CPaintToolView::WriteToFile(BITMAPFILEHEADER& hBitMapFile
                                 , PBITMAPINFOHEADER& pbihBitMap
                                 , LPTSTR& pszFile
                                 , DWORD& dwTemp
                                 , DWORD& dwTotal
                                 , DWORD& dwCB
                                 , BYTE* pbyByte
                                 , LPBYTE lpBits
                                 )
{
   BOOL bRet = FALSE;
   HANDLE hFile = NULL;
   hFile = CreateFile
       (
       pszFile,
       GENERIC_READ | GENERIC_WRITE
       , FILE_SHARE_READ
       , NULL
       , CREATE_ALWAYS
       , FILE_ATTRIBUTE_NORMAL
       , (HANDLE) NULL
       );
   if (INVALID_HANDLE_VALUE == hFile)
   {
       bRet = FALSE;
       goto EXIT0;
   } 
   hBitMapFile.bfType = BITMAP_FILE_TYPE;
   hBitMapFile.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
       pbihBitMap->biSize + pbihBitMap->biClrUsed 
       * sizeof(RGBQUAD) + pbihBitMap->biSizeImage); 
   hBitMapFile.bfReserved1 = 0; 
   hBitMapFile.bfReserved2 = 0; 
   hBitMapFile.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
       pbihBitMap->biSize + pbihBitMap->biClrUsed 
       * sizeof (RGBQUAD);

   if (!WriteFile(hFile, (LPVOID) &hBitMapFile, sizeof(BITMAPFILEHEADER), 
       (LPDWORD) &dwTemp,  NULL)) 
   {
       bRet = FALSE;
       goto EXIT0; 
   }

   if (!WriteFile(hFile, (LPVOID) pbihBitMap, sizeof(BITMAPINFOHEADER) 
       + pbihBitMap->biClrUsed * sizeof (RGBQUAD),
       (LPDWORD) &dwTemp, ( NULL)))
   {
       bRet = FALSE;
       goto EXIT0;
   }

   dwTotal = dwCB = pbihBitMap->biSizeImage;
   pbyByte = lpBits; 
   if (!WriteFile(hFile, (LPSTR) pbyByte, (int) dwCB, (LPDWORD) &dwTemp,NULL)) 
   {
       bRet = FALSE;
       goto EXIT0; 
   }

   bRet = TRUE;

EXIT0:
   if(hFile != NULL)
   {
       CloseHandle(hFile);
   }

   if(lpBits != NULL)
   {
       GlobalFree((HGLOBAL)lpBits);
   }

   return bRet;
}

BOOL CPaintToolView::SaveBitmap(TCHAR* szfilename)
{
    Paint_Struct paint_struct = m_PublicResourceManager->_PopDCFromBackStack();
    LPTSTR pszFile = szfilename;
    BOOL bRet = FALSE;
    PBITMAPINFO pbiBitMapInfo = CreateBitmapInfoStruct(paint_struct.m_hCompatibleBMP);
    HANDLE hFile = NULL;
    BITMAPFILEHEADER hBitMapFile = {0};
    PBITMAPINFOHEADER pbihBitMap = {0};
    LPBYTE lpBits = NULL;
    DWORD dwTotal = 0;
    DWORD dwCB = 0;
    BYTE* pbyByte = NULL;
    DWORD dwTemp = 0;

    pbihBitMap = (PBITMAPINFOHEADER) pbiBitMapInfo; 
    if(pbihBitMap == NULL)
    {
        bRet = FALSE;
        goto EXIT0;
    }

    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbihBitMap->biSizeImage);
    if (!lpBits) 
    {
        bRet = FALSE;
        goto EXIT0;
    }

    if (!GetDIBits(paint_struct.m_hCompatibleDC, paint_struct.m_hCompatibleBMP, 0, (WORD) pbihBitMap->biHeight, lpBits, pbiBitMapInfo, 
        DIB_RGB_COLORS))
    {
        bRet = FALSE;
        goto EXIT0;
    }

    bRet = WriteToFile(hBitMapFile, pbihBitMap, pszFile, dwTemp, dwTotal, dwCB, pbyByte, lpBits);
    /*hFile = CreateFile
        (
        pszFile,
        GENERIC_READ | GENERIC_WRITE
        , FILE_SHARE_READ, 
        NULL
        , CREATE_ALWAYS
        , FILE_ATTRIBUTE_NORMAL
        , (HANDLE) NULL
        );
    if (INVALID_HANDLE_VALUE == hFile)
    {
        goto EXIT0;
    } 
    hBitMapFile.bfType = BITMAP_FILE_TYPE;
    hBitMapFile.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
        pbihBitMap->biSize + pbihBitMap->biClrUsed 
        * sizeof(RGBQUAD) + pbihBitMap->biSizeImage); 
    hBitMapFile.bfReserved1 = 0; 
    hBitMapFile.bfReserved2 = 0; 
    hBitMapFile.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
        pbihBitMap->biSize + pbihBitMap->biClrUsed 
        * sizeof (RGBQUAD); 
    if (!WriteFile(hFile, (LPVOID) &hBitMapFile, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTemp,  NULL)) 
    {
        goto EXIT0; 
    }
    if (!WriteFile(hFile, (LPVOID) pbihBitMap, sizeof(BITMAPINFOHEADER) 
        + pbihBitMap->biClrUsed * sizeof (RGBQUAD),
        (LPDWORD) &dwTemp, ( NULL)))
    {
        goto EXIT0;
    }
    dwTotal = dwCB = pbihBitMap->biSizeImage;
    pbyByte = lpBits; 
    if (!WriteFile(hFile, (LPSTR) pbyByte, (int) dwCB, (LPDWORD) &dwTemp,NULL)) 
    {
        goto EXIT0; 
    }*/
EXIT0:
    if(hFile != NULL)
    {
        CloseHandle(hFile);
    }
    if(lpBits != NULL)
    {
        GlobalFree((HGLOBAL)lpBits);
    }

    return bRet;

}

BOOL CPaintToolView::SaveFile()
{
    CFileDialog fileDialog
        (
        FALSE, NULL, NULL
        , OFN_OVERWRITEPROMPT
        , _T("Bitmap(*.bmp)|*.bmp|所有文件(*.*)|*.*||")
        );

    TCHAR szFilePath[1024] = {0};
    fileDialog.m_ofn.lpstrFile = szFilePath;
    fileDialog.m_ofn.nMaxFile = 1023;

    if(IDOK == fileDialog.DoModal())
    {
        CComBSTR bstrFilePath(fileDialog.m_ofn.lpstrFile);
        wcscat_s(szFilePath,1024,L".bmp");
        if(SaveBitmap(szFilePath) == TRUE)
        {
            ::MessageBox(m_hWnd, L"文件成功保存\n\ro(∩_∩)o ",L"保存成功", 0);
            return TRUE;
        }
        else
        {
            ::MessageBox(m_hWnd, L"文件保存失败！::>_<::",L"保存失败", 0);
        }
    }
    else
    {
      ::MessageBox(m_hWnd, L"文件保存失败！::>_<::",L"保存失败", 0);
    }

    if(m_nDrawType != DRAW_TEXT)
    {
        m_nIsDrawText = 0;
    }

    return FALSE;
}