#include "framework.h" 
#include "aura/xml/_.h"


namespace user
{


   user::user()
   {

      //m_pufeschema = nullptr;
      //m_pufe = nullptr;

   }


   user::~user()
   {

   }


   ::estatus user::init1()
   {

      create_factory <::user::document >();
      create_factory <::user::message_queue >();
      create_factory <::user::simple_view >();
      create_factory <::user::still >();

      //if(get_context_application()->is_system())
      {

         create_factory <keyboard_layout >();

      }

      if(!::aura::department::init1())
         return false;

      return true;

   }


   ::estatus user::init()
   {

      if (!::aura::department::init())
      {

         return false;

      }

      TRACE("::user::application::initialize");

      //xml::document docUser;

      //string strUser = Context.file().as_string(Context.dir().appdata()/"langstyle_settings.xml");

      //string strLangUser;

      //string strStyleUser;

      //if(docUser.load(strUser))
      //{

      //   if(docUser.get_child("lang") != nullptr)
      //   {

      //      strLangUser = docUser.get_child("lang")->get_value();

      //   }

      //   if(docUser.get_child("style") != nullptr)
      //   {

      //      strStyleUser = docUser.get_child("style")->get_value();

      //   }

      //}

      //if(strLangUser.has_char())
      //   Session.set_locale(strLangUser,::source_database);

      //if(strStyleUser.has_char())
      //   Session.set_schema(strStyleUser,::source_database);

      string strLicense = Application.get_license_id();


      //var & varTopicQuey = System.commnam_varTopicQuery;

      bool bHasInstall = System.is_true("install");

      bool bHasUninstall = System.is_true("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      if (!::aura::department::init())
      {

         return false;

      }

      return true;

   }


   ::estatus user::init2()
   {

      if(!::aura::department::init2())
         return false;

      return true;

   }


   void user::term()
   {


      //m_puserstyle.release();
//      ::aura::del(m_pufeschema);
//
//      ::aura::del(m_pufe);


      try
      {

         ::aura::department::term();

      }
      catch(...)
      {

      }

   }


   ::user::primitive * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::primitive * pmousefocus)
   {

      m_pmousefocusLButtonDown = pmousefocus;

   }


   ::user::primitive * user::get_mouse_focus_RButtonDown()
   {

      return m_pmousefocusRButtonDown;

   }


   void user::set_mouse_focus_RButtonDown(::user::primitive * pmousefocus)
   {

      m_pmousefocusRButtonDown = pmousefocus;

   }




   void user::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)

   {

      sync_lock sl(&Application.m_mutexFrame);

      __pointer(::user::interaction) pinteraction;

      while(Application.get_frame(pinteraction))
      {

         if(pinteraction != nullptr && pinteraction->is_window())
         {

            pinteraction->send_message(message,wparam,lparam);


            pinteraction->send_message_to_descendants(message,wparam,lparam);


         }

      }

   }




//   ::user::front_end_schema * GetUfeSchema(::object * pobject)
//   {
//
//      if (papp == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if (papp->m_psession == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if (papp->m_psession->m_puser == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      return Sess(papp).user()->GetUfeSchema();
//
//   }
//
//
//   ::user::front_end * GetUfe(::object * pobject)
//   {
//
//      return Sess(papp).user()->GetUfe();
//
//   }


//   ::user::front_end_schema * user::GetUfeSchema()
//   {
//
//      return m_pufeschema;
//
//   }
//
//
//   ::user::front_end * user::GetUfe()
//   {
//
//      return m_pufe;
//
//   }

   ::type user::controltype_to_typeinfo(::user::e_control_type econtroltype)
   {

      return ::type();

   }


//   __pointer(::user::impact) user::get_view()
//   {
//
//      return nullptr;
//
//   }


//   ::user::style * user::get_user_style()
//   {
//
//      retu
//
//   }

} //namespace user



