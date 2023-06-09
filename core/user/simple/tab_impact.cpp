#include "framework.h"
#include "tab_impact.h"
#include "aura/message/user.h"


simple_tab_impact::simple_tab_impact()
{

}


simple_tab_impact::~simple_tab_impact()
{
}


// simple_tab_impact diagnostics


//void simple_tab_impact::assert_ok() const
//{
//   ::user::impact::assert_ok();
//}
//
//
//void simple_tab_impact::dump(dump_context & dumpcontext) const
//{
//   ::user::impact::dump(dumpcontext);
//}


void simple_tab_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::on_layout(pgraphics);

}


void simple_tab_impact::client_rectangle(::rectangle_i32 & rectangle, ::user::enum_layout elayout)
{

   ::user::impact::client_rectangle(rectangle, elayout);

}


void simple_tab_impact::on_message_create(::message::message * pmessage)
{

   ::pointer<::message::create>pcreate(pmessage);

   if(pcreate->previous())
      return;

   ::user::interaction::create_child(this);

   //if(!::user::interaction::create_child(this))
   //{
   //   pcreate->m_lresult = -1;
   //   return;
   //}

}


void simple_tab_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::_001OnDraw(pgraphics);

}


void simple_tab_impact::install_message_routing(::channel * pchannel)
{
   
   ::user::impact::install_message_routing(pchannel);
   
   ::user::tab::install_message_routing(pchannel);

}


void simple_tab_impact::on_message_left_button_up(::message::message * pmessage)
{

   auto pmouse = pmessage->m_union.m_pmouse;
   
   ::user::tab::on_message_left_button_up(pmessage);
   
   if (pmouse->m_bRet)
   {

      return;

   }

}


void simple_tab_impact::on_message_mouse_move(::message::message * pmessage)
{
   
   auto pmouse = pmessage->m_union.m_pmouse;
   
   ::user::tab::on_message_mouse_move(pmessage);
   
   if (pmouse->m_bRet)
   {

      return;

   }

}


void simple_tab_impact::on_message_mouse_leave(::message::message * pmessage)
{

   auto pmouse = pmessage->m_union.m_pmouse;

   ::user::tab::on_message_mouse_leave(pmessage);

   if (pmouse->m_bRet)
   {

      return;

   }

}

