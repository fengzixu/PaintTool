#ifndef __DRAWTEXT_H
#define __DRAWTEXT_H

#include "resource.h"
#include "ParentDraw.h"
#include <atlstr.h>
class CDrawText : public CParentDraw
{
public:
    CDrawText();
    ~CDrawText();
    BOOL WriteDC(RECT& rcClient, RECT& rcText);
    virtual BOOL Draw();

private:
    Paint_Struct m_paint_struct;
};

#endif