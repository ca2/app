#include "framework.h"
////#include "berg/user/simple/_component.h"
#include "main_frame.h"
#include "acme/constant/message.h"
#include "acme/handler/request.h"
#include "aura/message/user.h"
#include "aura/user/user/system.h"
#include "aura/windowing/windowing.h"
#include "berg/platform/application.h"
#include "berg/user/experience/frame.h"


simple_main_frame::simple_main_frame()
{

   m_bAutomaticallyStoreWindowRectangle = true;
   //m_ewindowflag              |= e_window_flag_auto_store_window_rect;
   m_ewindowflag              |= e_window_flag_main_frame;
   ///m_bAutoWindowFrame         = false;
   m_bPlacing                 = false;
   m_bExplicitTranslucency    = false;
   

}


simple_main_frame::~simple_main_frame()
{

}


void simple_main_frame::install_message_routing(::channel * pchannel)
{

   simple_frame_window::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_create,pchannel,this,&simple_main_frame::on_message_create);

}


void simple_main_frame::on_message_create(::message::message * pmessage)
{

   if (::system()->is_sandboxed())
   {

      //m_bWindowFrame = false;

   }

   ::pointer<::message::create>pcreate(pmessage);

   auto papp = get_app();

   if (papp->m_pacmeuserinteractionMain.is_null())
   {

      papp->m_pacmeuserinteractionMain = this;

   }
   
//   if(m_pusersystem 
//      && m_pusersystem->m_prequest
//      && m_pusersystem->m_prequest->m_payloadArguments.is_true("window_frame"))
//   {
//
//      m_bWindowFrame = true;
//
//   }
//   else
//   {
//
//      m_bWindowFrame = papp->m_bExperienceMainFrame;
//
//   }
//   
//   
//   if (m_bWindowFrame.undefined())
//   {
//
//      auto & bApplicationExperienceMainFrame = papp->m_bExperienceMainFrame;
//
//      if (bApplicationExperienceMainFrame.is_set())
//      {
//
//         if (get_parent() == nullptr)
//         {
//
//            m_bWindowFrame = bApplicationExperienceMainFrame;
//
//         }
//         else
//         {
//
//            m_bWindowFrame = false;
//
//         }
//
//      }
//      else
//      {
//
//#if defined(UNIVERSAL_WINDOWS) || defined(APPLE_IOS) || defined(__ANDROID__)
//
//         m_bWindowFrame = false;
//
//#else
//
//         m_bWindowFrame = get_parent() == nullptr || wfi_has_up_down();
//
//#endif
//
//      }
//
//   }


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



