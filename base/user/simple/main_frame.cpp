#include "framework.h"
////#include "base/user/simple/_component.h"
#include "main_frame.h"
#include "aura/message/user.h"
#include "base/platform/application.h"
#include "base/user/experience/frame.h"


simple_main_frame::simple_main_frame()
{

   m_ewindowflag              |= e_window_flag_auto_store_window_rect;
   m_ewindowflag              |= e_window_flag_main_frame;
   ///m_bAutoWindowFrame         = false;
   m_bPlacing                 = false;
   m_bExplicitTranslucency    = false;

}

simple_main_frame::~simple_main_frame()
{
}


void simple_main_frame::assert_ok() const
{
   simple_frame_window::assert_ok();
}

void simple_main_frame::dump(dump_context & dumpcontext) const
{
   simple_frame_window::dump(dumpcontext);
}


void simple_main_frame::install_message_routing(::channel * pchannel)
{

   simple_frame_window::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_create,pchannel,this,&simple_main_frame::on_message_create);

}


void simple_main_frame::on_message_create(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }

   __pointer(::message::create) pcreate(pmessage);

   auto papp = get_app();

   if (papp->m_puserinteractionMain.is_null())
   {

      papp->__refer(papp->m_puserinteractionMain, this);

   }

   auto pcreateContext = pcreate->get_create();

   if (pcreateContext && pcreateContext->m_payloadArgs.is_true("window_frame"))
   {

      m_bWindowFrame = true;

   }
   else
   {

      m_bWindowFrame = papp->m_bExperienceMainFrame;

   }

   if (papp->is_true("opaque"))
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


//bool simple_main_frame::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::style_context * pcontext)
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
