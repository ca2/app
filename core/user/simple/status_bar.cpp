#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_status_bar::simple_status_bar()
{

}


simple_status_bar::~simple_status_bar()
{
}

/*
 // BEGIN_MESSAGE_MAP(simple_status_bar, ::user::status_bar)
   //{{__MSG_MAP(simple_status_bar)
   ON_WM_ERASEBKGND()
   //}}__MSG_MAP
 // END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// simple_status_bar message handlers


/*
bool simple_status_bar::OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics)
{
   return true;
}
*/

void simple_status_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{
   return;
//   ::rectangle_i32 rectClient;
//
//   get_client_rect(rectClient);
//
//   
//
//   class imaging & imaging = System.imaging();
//#ifdef WINDOWS_DESKTOP
//   imaging.color_blend(
//      pgraphics,
//      rectClient.left,
//      rectClient.top,
//      rectClient.width(),
//      rectClient.height(),
//      psession->get_default_color(COLOR_3DFACE),
//      208);
//#else
//   imaging.color_blend(
//      pgraphics,
//      rectClient.left,
//      rectClient.top,
//      rectClient.width(),
//      rectClient.height(),
//      ARGB(255, 190, 184, 177),
//      208);
//#endif
//
//

}

