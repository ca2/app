#include "framework.h"
#include "base/user/simple/_simple.h"


simple_main_frame::simple_main_frame()
{

   m_ewindowflag              |= e_window_flag_auto_store_window_rect;
   m_ewindowflag              |= e_window_flag_main_frame;
   m_bAutoWindowFrame         = false;
   m_bWindowFrame             = true;
   m_bPlacing                 = false;
   m_bExplicitTranslucency    = false;

}

simple_main_frame::~simple_main_frame()
{
}


void simple_main_frame::assert_valid() const
{
   simple_frame_window::assert_valid();
}

void simple_main_frame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}


void simple_main_frame::install_message_routing(::channel * pchannel)
{

   simple_frame_window::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_create,pchannel,this,&simple_main_frame::_001OnCreate);

}


void simple_main_frame::_001OnCreate(::message::message * pmessage)
{

   __pointer(::message::create) pcreate(pmessage);

   if (Application.m_puiMain1.is_null())
   {

      Application.m_puiMain1 = this;

   }

   auto pcreateContext = pcreate->get_create();

   if (pcreateContext && pcreateContext->m_varArgs.is_true("window_frame"))
   {

      m_bWindowFrame = true;

   }
   else
   {

      m_bWindowFrame = !Application.is_true("client_only");

   }

   if (Application.is_true("opaque"))
   {

      m_bExplicitTranslucency = true;

      m_etranslucencyFrame = ::user::e_translucency_none;

   }
   else
   {

      m_bExplicitTranslucency = false;

   }

   if (pmessage->previous())
   {

      return;

   }

}


//bool simple_main_frame::get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::style_context * pcontext)
//{
//
//   if (m_bExplicitTranslucency)
//   {
//
//      etranslucency = m_etranslucency;
//
//      return true;
//
//   }
//
//   return ::user::style::get_translucency(etranslucency, eelement, pcontext);
//
//}
