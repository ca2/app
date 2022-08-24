#include "framework.h"
#include "core/user/simple/_component.h"
#include "status_bar.h"


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
//   ::rectangle_i32 rectangleClient;
//
//   get_client_rect(rectangleClient);
//
//   
//
//   class imaging & imaging = psystem->imaging();
//#ifdef WINDOWS_DESKTOP
//   imaging.color_blend(
//      pgraphics,
//      rectangleClient.left,
//      rectangleClient.top,
//      rectangleClient.width(),
//      rectangleClient.height(),
//      psession->get_default_color(COLOR_3DFACE),
//      208);
//#else
//   imaging.color_blend(
//      pgraphics,
//      rectangleClient.left,
//      rectangleClient.top,
//      rectangleClient.width(),
//      rectangleClient.height(),
//      argb(255, 190, 184, 177),
//      208);
//#endif
//
//

}

