#pragma once


#include "apex/os/windows/_windows.h"


#include "top_level_enum.h"



#ifdef WINDOWS_DESKTOP
CLASS_DECL_AURA bool get_gui_thread_info(PGUITHREADINFO pinfo);
#endif

hcursor windows_create_cursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);

#ifdef WINDOWS_DESKTOP


inline void copy(Gdiplus::ColorMatrix & a, const color_matrix & b)
{

   copy_color_matrix(a.m, b.a);

}


#endif

#ifdef WINDOWS_DESKTOP
HBITMAP hbitmap_from_image(const ::image & image, const ::size_i32 & size);
#endif



#ifdef WINDOWS_DESKTOP


CLASS_DECL_AURA HBITMAP CreateHBITMAP(pixmap * ppixmap);
CLASS_DECL_AURA HBITMAP CreateHBITMAP2(pixmap * ppixmap);


#endif


#ifdef WINDOWS

bool GetLogFont(LOGFONTW * pfontw, const ::draw2d::font * pfont);

#endif



#ifdef WINDOWS_DESKTOP


// Derived from Microsoft KB318876!!
// on 2014-06-29!! During World Cup Games 2014!! Oitavas de Final, third game between Nederland and Mexico!!
// Thank you God!!
// Thank you Microsoft!!
// Thank you Pappi!! Pelo passeio no Mercado Municipal de Curitiba com a Mummi e pelo almoo com o-bento de sushi e onigiri delicioso!!
// Obrigado Mummi por tudo!! E por hoje tambm e por propiciar isso tudo!! Por falar to profundamente do Chico Xavier mesmo com muitas dvidas minhas!!
// Meu Deus me ajude!!


CLASS_DECL_AURA HBITMAP CreateAlphaBitmapV5(const ::image * pimage);
CLASS_DECL_AURA hicon CreateAlphaIcon(const ::image * pimage, bool bIcon = true, int xHotSpot = 0, int yHotSpot = 0);


#endif




void copyd(CREATESTRUCTW * pcreatestructw, const ::user::create_struct * pcreatestruct)
{

   pcreatestructw->lpCreateParams      = pcreatestruct->lpCreateParams;
   pcreatestructw->hInstance           = pcreatestruct->hInstance;
   pcreatestructw->hMenu               = pcreatestruct->hMenu;
   pcreatestructw->hwndParent          = pcreatestruct->hwndParent;
   pcreatestructw->cy                  = pcreatestruct->cy;
   pcreatestructw->cx                  = pcreatestruct->cx;
   pcreatestructw->y                   = pcreatestruct->y;
   pcreatestructw->x                   = pcreatestruct->x;
   pcreatestructw->style               = pcreatestruct->style;
   pcreatestructw->lpszName            = pcreatestruct->lpszName;
   pcreatestructw->lpszClass           = pcreatestruct->lpszClass;
   pcreatestructw->dwExStyle           = pcreatestruct->dwExStyle;
   
}

namespace user
{

   CLASS_DECL_AURA void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction, const rectangle_i32 & rectangle);

} // namespace user
