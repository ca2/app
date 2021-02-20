#pragma once


#include "apex/os/windows/_windows.h"


#include "top_level_enum.h"


#include "acme/os/_user.h"


#ifdef WINDOWS_DESKTOP
CLASS_DECL_AURA bool get_gui_thread_info(PGUITHREADINFO pinfo);
#endif

hcursor windows_create_cursor(::windowing::window * pwindow, const image * pimage, int xHotSpot, int yHotSpot);



#ifdef WINDOWS_DESKTOP
HBITMAP hbitmap_from_image(const ::image & image, const ::size_i32 & size);
#endif




#ifdef WINDOWS

bool GetLogFont(LOGFONTW * pfontw, const ::write_text::font * pfont);

#endif




inline void copy(CREATESTRUCTW * pcreatestructw, const ::user::create_struct * pcreatestruct)
{

   pcreatestructw->lpCreateParams      = pcreatestruct->lpCreateParams;
   pcreatestructw->hInstance           = (HINSTANCE) pcreatestruct->hInstance;
   pcreatestructw->hMenu               = (HMENU) pcreatestruct->hMenu;
   pcreatestructw->hwndParent          = (HWND) pcreatestruct->hwndParent;
   pcreatestructw->cy                  = pcreatestruct->cy;
   pcreatestructw->cx                  = pcreatestruct->cx;
   pcreatestructw->y                   = pcreatestruct->y;
   pcreatestructw->x                   = pcreatestruct->x;
   pcreatestructw->style               = pcreatestruct->style;
   pcreatestructw->lpszName            = pcreatestruct->lpszName;
   pcreatestructw->lpszClass           = pcreatestruct->lpszClass;
   pcreatestructw->dwExStyle           = pcreatestruct->dwExStyle;
   
}






//struct SIZEPARENTPARAMS
//{
//
//   RECTANGLE_I32  rectangle;       // parent client rectangle_i32 (trim as appropriate)
//   SIZE_I32  sizeTotal;  // total size_i32 on each side as on_layout proceeds
//   bool  bStretch;   // should stretch to fill all space
//
//};
namespace user
{

   CLASS_DECL_AURA void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction, const rectangle_i32 & rectangle);

} // namespace user
