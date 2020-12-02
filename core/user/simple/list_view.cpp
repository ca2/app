#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_list_view::simple_list_view()
{

}


simple_list_view::~simple_list_view()
{

}


void simple_list_view::install_message_routing(::channel * pchannel)
{
   
   BASE_TYPE::install_message_routing(pchannel);
   
}



/////////////////////////////////////////////////////////////////////////////
// simple_list_view drawing


void simple_list_view::OnDraw(::draw2d::graphics_pointer & pgraphics)
{
   
   UNREFERENCED_PARAMETER(pgraphics);
   
   ASSERT(FALSE);

}


void simple_list_view::assert_valid() const
{

   ::user::impact::assert_valid();

}


void simple_list_view::dump(dump_context & dumpcontext) const
{

   ::user::impact::dump(dumpcontext);

}


bool simple_list_view::pre_create_window(::user::create_struct& cs)
{

#ifdef WINDOWS_DESKTOP

   cs.style |= WS_CLIPCHILDREN;

#endif

   return ::user::impact::pre_create_window(cs);

}


__pointer(::user::interaction) simple_list_view::OnDrawInterfaceGetWnd()
{

   return this;

}



