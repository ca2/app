#include "framework.h"
#include "core/user/simple/_simple.h"


simple_tab_view::simple_tab_view()
{

}


simple_tab_view::~simple_tab_view()
{
}


// simple_tab_view diagnostics


void simple_tab_view::assert_valid() const
{
   ::user::impact::assert_valid();
}


void simple_tab_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}


void simple_tab_view::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::on_layout(pgraphics);

}








bool simple_tab_view::get_client_rect(RECTANGLE_I32 * prectangle)
{

   ::user::impact::get_client_rect(prectangle);

   return true;

}





void simple_tab_view::on_message_create(::message::message * pmessage)
{

   __pointer(::message::create) pcreate(pmessage);

   if(pcreate->previous())
      return;

   if(!::user::interaction::create_child(this))
   {
      pcreate->m_lresult = -1;
      return;
   }

}


void simple_tab_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::_001OnDraw(pgraphics);

}


void simple_tab_view::install_message_routing(::channel * pchannel)
{
   
   ::user::impact::install_message_routing(pchannel);
   
   ::user::tab::install_message_routing(pchannel);

}


void simple_tab_view::on_message_left_button_up(::message::message * pmessage)
{

   __pointer(::message::mouse) pmouse(pmessage);
   
   ::user::tab::on_message_left_button_up(pmessage);
   
   if (pmouse->m_bRet)
   {

      return;

   }

}


void simple_tab_view::_001OnMouseMove(::message::message * pmessage)
{
   
   __pointer(::message::mouse) pmouse(pmessage);
   
   ::user::tab::_001OnMouseMove(pmessage);
   
   if (pmouse->m_bRet)
   {

      return;

   }

}


void simple_tab_view::_001OnMouseLeave(::message::message * pmessage)
{

   __pointer(::message::mouse) pmouse(pmessage);

   ::user::tab::_001OnMouseLeave(pmessage);

   if (pmouse->m_bRet)
   {

      return;

   }

}

