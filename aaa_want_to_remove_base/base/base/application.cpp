#include "framework.h"
#include "aura/id.h"


//extern thread_pointer < memdleak_block > t_plastblock;

namespace base
{


   //UINT application::APPM_LANGUAGE = WM_APP + 117;
   //WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application()
   {

      create_factory < ::user::user >();

      //m_bBaseProcessInitialize         = false;
      //m_bBaseProcessInitializeResult   = false;

      //m_bBaseInitialize1               = false;
      //m_bBaseInitialize1Result         = false;

      //m_bBaseInitialize                = false;
      //m_bBaseInitializeResult          = false;

      //m_bBaseInitializeInstance        = false;
      //m_bBaseInitializeInstanceResult  = false;




   }

   application::~application()
   {

   }


   ::estatus application::initialize(::object * pobjectContext)
   {

      auto estatus = ::aura::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

//   void application::install_message_routing(::channel * pchannel)
//   {
//
//
//
//   }


   //void application::update(::update * pupdate)
   //{

   //   ::aura::application::update(pupdate);

   //   if (pupdate->m_bRet)
   //   {
   //
   //      return;

   //   }
   //
   //   ::user::form_callback::update(pupdate);

   //   if (pupdate->m_bRet)
   //   {

   //      return;

   //   }

   //}


   ::estatus application::process_init()
   {

      if(::aura::application::process_init())
      {

         return true;

      }

      return true;

   }


   ::estatus application::init_instance()
   {

      if (!::aura::application::init_instance())
      {

         return false;

      }

      auto estatus = create_impact_system();

      if (failed(estatus))
      {

         return false;

      }

      return true;

   }


   ::estatus     application::create_impact_system()
   {

      return ::success;

   }


   void application::process_message_filter(i32 code,::message::message * pmessage)
   {

      if(pmessage == nullptr)
         return;   // not handled

      SCAST_PTR(::message::base,pbase,pmessage);

      __pointer(::user::frame_window) pTopFrameWnd;
      //::user::interaction * pMainWnd;
      ::user::interaction * pMsgWnd;
      switch(code)
      {
      //case MSGF_DDEMGR:
      // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
      //  never call the next hook.
      // By returning FALSE, the message will be dispatched
      //  instead (the default behavior).
      //return;

      case MSGF_MENU:

         pMsgWnd = dynamic_cast < ::user::interaction * > (pbase->m_puserinteraction);

         if(pMsgWnd != nullptr)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if(pTopFrameWnd != nullptr && pTopFrameWnd->IsTracking() &&
                  pTopFrameWnd->m_bHelpMode)
            {
               //pMainWnd = __get_main_window();
               //if((m_puiMain != nullptr) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               //{
               //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
               //   pbase->m_bRet = true;
               //   return;
               //}
            }
         }
      // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         //pMainWnd = __get_main_window();
         if(code == MSGF_DIALOGBOX && m_puiActive != nullptr &&
               pbase->m_id >= WM_KEYFIRST && pbase->m_id <= WM_KEYLAST)
         {
         }
         break;
      }
      // default to not handled

   }





















   /*string application::get_cred(const string & strRequestUrlParam,const ::rect & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::account::get_cred(this,strUsername,strPassword,strToken);

      if(str == "ok" && strUsername.has_char() && strPassword.has_char())
         return "ok";

      if(!bInteractive)
         return "failed";

      __pointer(::account::simple_ui) pinteraction;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string(::dir::system() / "config\\system\\ignition_server.txt");

         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

         strRequestUrl = "https://account.ca2.cc/";

      }

      pinteraction = __new(::account::simple_ui(this,strRequestUrl));

      pinteraction->m_login.m_peditUser->set_window_text(strUsername);

      pinteraction->m_login.m_ppassword->set_window_text("");

      string strResult = pinteraction->get_cred(rect,strUsername,strPassword,strToken,strTitle);

      pinteraction->DestroyWindow();

      ::account::set_cred(this,strToken,strUsername,strPassword);

      return strResult;

   }*/


   //__pointer(::user::user) application::create_user()
   //{

   //   return __new(::user::user);

   //}


   bool application::on_thread_on_idle(::thread_impl * pimpl,LONG lCount)
   {

      if(lCount <= 0)
      {

         __pointer(::user::interaction) pinteraction;

         while(get_frame(pinteraction))
         {
            //::user::interaction * pinteraction = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
            bool bOk = false;
            try
            {

               bOk = pinteraction != nullptr && pinteraction->is_window_visible();
            }
            catch(...)
            {
            }
            if(!bOk)
            {
               //   try
               //   {
               //      Application.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      Session.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      System.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
            }
            else
            {
//               sl.unlock();
               try
               {
                  pinteraction->send_message(WM_IDLEUPDATECMDUI,(WPARAM)TRUE);
               }
               catch(...)
               {

               }
               //             sl.lock();
            }
         }


      }
      else if(lCount >= 0)
      {
      }

      return lCount < 0;  // nothing more to do if lCount >= 0

   }




   //bool application::enable_window(::user::primitive * pinteraction,bool bEnable)
   //{

   //   // if control has the focus, move the focus before disabling
   //   if(!bEnable)
   //   {

   //      if(Session.get_focus_ui() == pinteraction->m_puiThis)
   //      {

   //         Application.send_message(pinteraction->m_puiThis->GetParent(), WM_NEXTDLGCTL, 0, (LPARAM)FALSE);

   //      }

   //   }

   //   return pinteraction->m_puiThis->enable_window(bEnable);

   //}


   //bool application::set_window_text(::user::interaction * pinteraction,const string & strText)
   //{

   //   pinteraction->set_window_text(strText);

   //   return true;

   //}



   ::type application::user_default_controltype_to_typeinfo(::user::e_control_type e_type)
   {

      return ::type();

   }


   i32 application::hotplugin_host_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,::hotplugin::host * phost,::hotplugin::plugin * pplugin)
   {

      return hotplugin::host::s_host_starter_start_sync(pszCommandLine,get_context_application(),nullptr);

   }



   void application::remove_document_template(::user::impact_system * pimpactsystem)
   {

   }




//   ::user::style_base * application::userstyle()
//   {
//
//      if (m_psession->m_puserstyle == nullptr)
//      {
//
//         m_psession->defer_create_user_style(preferred_experience());
//
//      }
//
//      return m_psession->m_puserstyle;
//
//   }
//
//
//   ::user::style_base * application::userstyle(::user::e_schema estyle)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if(puserstyle == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      return puserstyle->operator[](estyle);
//
//   }


   void application::on_create_impact(::user::impact_data * pimpactdata)
   {


   }


   bool application::process_message()
   {

      return ::thread::process_message();

   }


   void application::SetCurrentHandles()
   {

      ::aura::application::SetCurrentHandles();

   }


   void application::term_application()
   {

      try
      {

         aura::application::term_application();

      }
      catch(...)
      {

      }

   }


   ::draw2d::icon * application::set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon)
   {

      ::draw2d::icon * piconOld = get_icon(pobject, bBigIcon);

      if (bBigIcon)
      {

         pobject->value("big_icon") = ( __pointer(object)) picon;

      }
      else
      {

         pobject->value("small_icon") = ( __pointer(object)) picon;

      }

      return piconOld;

   }


   ::draw2d::icon * application::get_icon(object * pobject, bool bBigIcon) const
   {

      if (bBigIcon)
      {

         return const_cast <object *> (pobject)->cast < ::draw2d::icon >("big_icon");

      }
      else
      {

         return const_cast <object *> (pobject)->cast < ::draw2d::icon >("small_icon");

      }

   }


   void application::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_initialize_control)
      {

         if (pevent->m_puie->m_id == __id(system_startup_checkbox))
         {

            try
            {
               __pointer(::user::check) pcheck = pevent->m_puie;

               if(pcheck.is_set())
               {

                  pcheck->_001SetCheck(
                  Context.os().is_user_auto_start(get_executable_appid()),
                  ::source_initialize);

               }
            }
            catch (...)
            {

            }

         }

      }
      else if (pevent->m_eevent == ::user::event_set_check)
      {

         if (pevent->m_puie->m_id == __id(system_startup_checkbox)
               && pevent->m_actioncontext.is_user_source())
         {

            try
            {

               __pointer(::user::check) pcheck = pevent->m_puie;

               if(pcheck.is_set())
               {

                  Context.os().register_user_auto_start(
                  get_executable_appid(),
                  get_executable_path(),
                  pcheck->echeck() == ::check_checked);

               }

               pevent->m_bRet = true;

               return;

            }
            catch (...)
            {

            }

         }

      }

   }


   ::user::interaction * application::create_menu_interaction()
   {

      return __new(::user::button);

   }


   __pointer(::user::document) application::defer_create_view(string strView, ::user::interaction * puiParent, ewindowflag ewindowflag, const ::id & id)
   {

      auto pcontroller = ::aura::application::defer_create_view(strView, puiParent, ewindowflag, id);

      if (pcontroller)
      {

         return pcontroller;

      }

      return nullptr;

   }


   ::type application::control_type_from_id(const ::id & id, ::user::e_control_type & econtroltype)
   {

      string str(id);

      if (str.begins_ci("still_"))
      {

         econtroltype = ::user::control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("label_"))
      {

         econtroltype = ::user::control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("edit_"))
      {

         econtroltype = ::user::control_type_edit_plain_text;

         return __type(::user::plain_edit);

      }
      else if (str.begins_ci("button_"))
      {

         econtroltype = ::user::control_type_button;

         return __type(::user::button);

      }

      return ::aura::application::control_type_from_id(id, econtroltype);

   }


   //::form_property_set * application::get_form_property_set()
   //{

   //   auto pset = ::user::form_callback::get_form_property_set();

   //   if (::is_set(pset))
   //   {

   //      return pset;

   //   }

   //   return this;

   //}


} // namespace base



