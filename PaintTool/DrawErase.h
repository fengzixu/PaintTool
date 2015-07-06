#ifndef __DRAWERASE_H
#define __DRAWERASE_H

#include "resource.h"
#include "ParentDraw.h"

class CDrawErase : public CParentDraw
{
public:
    CDrawErase();
    ~CDrawErase();
    BOOL WriteDC(RECT& rcClient, HPEN& hPen);
    BOOL ChangeCursorResource(HCURSOR& hCursor);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
    static Paint_Struct ms_static_struct;
};

#endif