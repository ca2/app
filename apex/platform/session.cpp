#include "framework.h"
#include "session.h"
#include "system.h"
#include "application.h"
#include "node.h"
#include "os_context.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
////#include "acme/exception/exception.h"
#include "acme/primitive/primitive/url.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/handler/request.h"
#include "acme/platform/system_setup.h"
#include "acme/primitive/data/listener.h"
#include "acme/primitive/text/context.h"
#include "apex/filesystem/fs/fs.h"
#include "apex/filesystem/fs/ifs.h"
#include "apex/filesystem/fs/link.h"
#include "apex/filesystem/fs/remote_native.h"
#include "apex/filesystem/fs/set.h"
#include "apex/message/channel.h"
#include "apex/message/command.h"
#include "apex/message/message.h"
//#include "apex/operating_system.h"
#include "apex/user/primitive.h"


#if defined(APPLE_IOS) || defined(UNIVERSAL_WINDOWS) || defined(ANDROID)


namespace OPERATING_SYSTEM_NAMESPACE
{


   CLASS_DECL_APEX ::user::interaction * create_host_window();


} // namespace OPERATING_SYSTEM_NAMESPACE


#endif


//#ifdef CUBE
//extern "C"
//::acme::application * cube_get_app();
//#endif

void defer_term_ui();


//CLASS_DECL_ACME bool is_verbose();


int_bool point_is_window_origin(::point_i32 ptHitTest, ::windowing::window * pwindowExclude, int iMargin);

#ifdef UNIVERSAL_WINDOWS

//#include "acme/operating_system/universal_windows/_universal_windows.h"

#elif defined(LINUX)

void x11_on_start_session();

#endif


namespace apex
{


   session::session()
   {

      m_papexsession = this;

      m_bSimpleMessageLoop = false;
      m_bMessageThread = true;
      m_iEdge = -1;

      //set_layer(LAYERED_APEX, this);

      //add_factory_item < ::user::user >();
      //add_factory_item < ::apex::session, ::apex::session >();

      //m_XstrAppId                    = "core_session";
      //m_strAppName                  = "core_session";
      //m_strBaseSupportId            = "core_session";
      //m_strInstallToken             = "core_session";

      //m_puiLastUserInputPopup = nullptr;

      //m_pdocs = create_session_docs();

      //m_bLicense				               = false;

      //m_bLicense           = false;
      //m_eexclusiveinstance = e_exclusive_instance_none;

   }


   session::~session()
   {

      //if(acmesystem()->m_etracelevel >= e_trace_level_information)
      {

         information("apex::session::~session()");

      }

   }


   void session::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::thread::initialize(pparticle);

      ::apex::context::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bIfs                           = true;

      m_bProgrammerMode                = false;

      m_bSystemSynchronizedCursor      = true;

      //set_context_session(this);


      auto psystem = acmesystem()->m_papexsystem;

      if (psystem != nullptr)
      {

         m_bSystemSynchronizedCursor   = psystem->m_bSystemSynchronizedCursor;

      }

      //m_pappCurrent                    = nullptr;

      m_bZipIsDir2                     = true;

      m_iEdge                          = 0;

      m_bShowPlatform                  = false;

      m_pappCurrent                    = nullptr;

      //return ::success;

   }


   void session::install_message_routing(::channel* pchannel)
   {

      ::apex::context::install_message_routing(pchannel);
      
      MESSAGE_LINK(e_message_erase_application, pchannel, this, &session::on_message_erase_application);

   }


   //void session::on_initialize_window_object()
   //{

   //   if (m_bOnInitializeWindowObject)
   //   {

   //      return ::success_none;

   //   }

   //   m_bOnInitializeWindowObject = true;

   //   auto estatus = _on_initialize_window_object();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   //void session::_on_initialize_window_object()
   //{

   //   return ::success;

   //}


   void session::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
   {


   }


   string session::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   bool session::is_session() const
   {

      return true;

   }


   //void session::ui_init()
   //{

   //   return ::success;

   //}
   

   //void session::enum_display_monitors()
   //{


   //}
   

   //index session::get_main_monitor(::rectangle_i32* prectangle)
   //{

   //   return -1;

   //}


   //::count session::get_monitor_count()
   //{

   //   return -1;

   //}

   
   //bool  session::get_monitor_rectangle(index iMonitor, ::rectangle_i32* prectangle)
   //{

   //   return false;

   //}

   
   //::count session::get_desk_monitor_count()
   //{

   //   return -1;

   //}


   //bool  session::get_desk_monitor_rect(index iMonitor, ::rectangle_i32* prectangle)
   //{

   //   return false;

   //}


   //index session::get_main_workspace(::rectangle_i32* prectangle)
   //{

   //   return -1;

   //}


   //::count session::get_workspace_count()
   //{

   //   return -1;

   //}


   //bool  session::get_workspace_rectangle(index iWorkspace, ::rectangle_i32* prectangle)
   //{

   //   return false;

   //}

   //
   //::count session::get_desk_workspace_count()
   //{

   //   return -1;

   //}
  
   //
   //bool  session::get_desk_workspace_rect(index iWorkspace, ::rectangle_i32* prectangle)
   //{

   //   return false;

   //}


   //bool session::set_main_monitor(index iMonitor)
   //{

   //   return false;

   //}
   

   //bool session::set_main_workspace(index iWorkspace)
   //{

   //   return false;

   //}


   //bool session::workspace_to_monitor(::rectangle_i32* prectangle, index iMonitor, index iWorkspace)
   //{

   //   return false;

   //}


   //bool session::monitor_to_workspace(::rectangle_i32* prectangle, index iWorkspace, index iMonitor)
   //{

   //   return false;

   //}


   //bool session::workspace_to_monitor(::rectangle_i32* prectangle)
   //{

   //   return false;

   //}


   //bool session::monitor_to_workspace(::rectangle_i32* prectangle)
   //{

   //   return false;

   //}


   //void session::get_monitor(rectangle_i32_array& rectaMonitor, rectangle_i32_array& rectaIntersect, const ::rectangle_i32& rectangle)
   //{


   //}


   ::color::color session::get_default_color(::color::color color)
   {

      auto psystem = acmesystem()->m_papexsystem;

      auto pnode = psystem->node();

      if (!pnode)
      {

         return argb(127, 0, 0, 0);

      }

      return pnode->get_default_color(color);

   }






   //size_i32 session::get_window_minimum_size()
   //{

   //   return size_i32(300, 300);

   //}


   void session::init_task()
   {

      init_session();

      //auto estatus =
      
      //process_init();

      //if (!estatus)
      //{

      //   warning() <<"Failed at apex::session::init_thread after process_init";

      //   return estatus;

      //}

      //estatus = 
      
      //init_session();

      //if (!estatus)
      //{

      //   warning() <<"Failed at apex::session::init_thread after init_session";

      //   return estatus;

      //}

      // // now there is attempt here
      //estatus = defer_initialize_host_window();

      //if(!estatus)
      //{

      //   throw ::exception(::exception(estatus));

      //}

      //information() << ".1";

      //return true;

      //return estatus;

   }


   void session::term_task()
   {

      try
      {

         term_session();

      }
      catch (...)
      {

      }

      try
      {

         process_term();

      }
      catch(...)
      {

      }

      ::thread::term_task();

   }


   void session::process_init()
   {

      //information() << "apex::session::process_init";

      //auto estatus = ::apex::context::initialize_context();

      //if (!estatus)
      //{

         //return estatus;

      //}

      //auto estatus =
      __construct_new(m_ptextcontext);

      //if (!estatus)
      //{

      //   warning() <<"acme::str_context Failed to Allocate!!";

      //   return estatus;

      //}

      //information() << "acme::str_context Succeeded to Allocate!!";

      //information() << "apex::session::process_init success";

      //return ::success;

      initialize_context();

   }


   void session::init_session()
   {


      process_init();


      //auto estatus = 
      init1();

      //if (!estatus)
      //{

      //   warning() <<"Failed to init1 the session (::apex::session or ::apex::session derived)";

      //   return estatus;

      //}

      //estatus = 
      init2();

      //if (!estatus)
      //{

      //   warning() <<"Failed to init2 the session (::apex::session or ::apex::session derived)";

      //   return estatus;

      //}

      init();

      //if (!estatus)
      //{

      //   warning() <<"Failed to init() the session (::apex::session or ::apex::session derived)";

      //   return estatus;

      //}

//      return ::success;

   }


   void session::term_session()
   {

      try
      {

         term2();

      }
      catch (...)
      {

      }

      try
      {

         term1();

      }
      catch (...)
      {

      }

      try
      {

         term();

      }
      catch (...)
      {

      }



   }


   void session::on_message_erase_application(::message::message* pmessage)
   {

      ::pointer<::apex::application>papp(pmessage->m_lparam);

      erase_application(papp);

   }


   void session::term2()
   {

   }


   void session::term1()
   {

   }


   void session::process_term()
   {

      auto psystem = acmesystem()->m_papexsystem;

      psystem->post_message(e_message_erase_session, m_iEdge);

   }


   bool session::on_get_task_name(string& strTaskName)
   {

      if (acmeapplication()->m_bConsole)
      {

         return false;

      }

      return ::apex::context::on_get_task_name(strTaskName);

   }


   void session::on_request(::request * prequest)
   {

      auto psystem = acmesystem()->m_papexsystem;

      if (prequest->m_ecommand == e_command_protocol)
      {

         m_pappCurrent->request(prequest);

         return;

      }

      information() << "::apex::session::on_request(::pointer<::create> " << __type_name(this);

      //string strAppId = prequest->m_strAppId;

      //if (strAppId.is_empty())
      //{

      //   information() << "m_strAppId Is Empty!!";

      //   return;

      //}

      information() << "m_strAppId = " << prequest->m_strAppId;

      auto papplication = get_application(prequest->m_strAppId, true, prequest);

      if (!papplication)
      {

         destroy();

      }

      m_varCurrentImpactFile = prequest->m_payloadFile;

   }


   //::pointer<::user::menu_interaction>session::create_menu_button(::user::style_pointer & pstyle,::user::menu_item * pitem)
   //{

   //   throw ::interface_only();

   //   return nullptr;

   //}


   bool session::open_by_file_extension(const ::string & pszPathName, ::request * prequest)
   {

      auto prequestNew = __create_new < ::request >();

      prequestNew->m_payloadFile = pszPathName;

      prequestNew->m_puserelementParent = prequest->m_puserelementParent;

      return open_by_file_extension(prequestNew.get());

      //return get_app()->platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::request * prequest)
   {

      //return get_app()->platform_open_by_file_extension(m_iEdge, pcc);

      string strId;

      string strOriginalPathName(prequest->m_payloadFile);

      ::file::path strPathName(strOriginalPathName);

      auto pFind = strPathName.find("?");

      if (::is_set(pFind))
      {

         strPathName = strPathName(0, pFind);

      }

      if (strPathName.case_insensitive_ends(".ca2"))
      {

      }

      auto psystem = acmesystem();

      auto purl = psystem->url();

      string strProtocol = purl->get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = purl->get_server(strPathName);

         string str = purl->get_object(strPathName);

         str.begins_eat("/");

         prequest->m_payloadFile = str;

      }
      else
      {

         string strExtension = strPathName.final_extension();

         string_array straApp;

         throw ::exception(todo, "filehandler");

         //psystem->filehandler().get_extension_app(straApp, strExtension);

         //if (straApp.get_count() == 1)
         //{

         //   strId = straApp[0];

         //}
         //else
         //{

         //   strId = "app/sphere/default_file_handler";

         //}

      }

      auto papp = get_application(strId, true, prequest);

      if (papp == nullptr)
      {

         return false;

      }

      papp->request(prequest);

      return true;

   }


   void session::on_instantiate_application(::acme::application* papplication)
   {


      ::acme::session::on_instantiate_application(papplication);
      //papp->m_papexsession = this;
      //papp->m_papexsystem = m_papexsystem;
      //papp->m_pacmenode = m_pacmenode;
      //papp->m_papexnode = m_papexnode;

   }


   //::application * session::application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::request * prequest)
   //{

   //   ::pointer<::apex::application>papp;

   //   if (m_applicationa.lookup(pszAppId, papp))
   //   {

   //      return papp;

   //   }
   //   else
   //   {

   //      if (!bCreate)
   //      {

   //         return nullptr;

   //      }

   //      papp = nullptr;

   //      try
   //      {

   //         papp = create_application(pszAppId, bSynch, pcreate);

   //      }
   //      catch (const ::exception & e)
   //      {

   //         // apex::session, axis::session and ::base::session, could get more specialized handling in apex::application (apex::system)
   //         // Thank you Mummi (em Santos, cuidando do Lucinho e ajudando um monte a Carou e o Lucio e Eu 2019-01-15) !! Thank you God!! <3tbs

   //         handle_exception(e);

   //         //if (!acmesystem()->on_run_exception(esp))
   //         //{

   //         //   if (!App(this).on_run_exception(esp))
   //         //   {

   //         //      papp = nullptr;

   //         //   }

   //         //}

   //         //papp = nullptr;

   //      }
   //      catch (...)
   //      {

   //         //papp = nullptr;

   //      }

   //      if (!papp)
   //      {

   //         return nullptr;

   //      }

   //      app_add(papp);

   //      return papp;

   //   }

   //}


   bool session::is_licensed(const ::string & pszAppId, bool bInteractive)
   {

      if (has_property("install"))
      {

         return true;

      }

      if (has_property("uninstall"))
      {

         return true;

      }

      return false;

   }


   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      throw 0;

      return false;

      //return account()->get_auth(pszForm, strUsername, strPassword);

   }


   ::user::e_key session::key_modifiers()
   {

      ::user::e_key ekeyModifiers = ::user::e_key_none;

      if (is_key_pressed(::user::e_key_left_shift))
      {

         ekeyModifiers |= ::user::e_key_left_shift;

      }

      if (is_key_pressed(::user::e_key_right_shift))
      {

         ekeyModifiers |= ::user::e_key_right_shift;

      }

      if (is_key_pressed(::user::e_key_left_control))
      {

         ekeyModifiers |= ::user::e_key_left_control;

//#if !defined(__APPLE__)
//
//         ekeyModifiers |= ::user::e_key_system_left_command;
//
//#endif

      }

      if (is_key_pressed(::user::e_key_right_control))
      {

         ekeyModifiers |= ::user::e_key_right_control;

//#if !defined(__APPLE__)
//
//         ekeyModifiers |= ::user::e_key_system_right_command;
//
//#endif

      }

      if (is_key_pressed(::user::e_key_left_alt))
      {

         ekeyModifiers |= ::user::e_key_left_alt;

      }

      if (is_key_pressed(::user::e_key_right_alt))
      {

         ekeyModifiers |= ::user::e_key_right_alt;

      }

      if (is_key_pressed(::user::e_key_left_command))
      {

         ekeyModifiers |= ::user::e_key_left_command;

#if defined(__APPLE__)

         ekeyModifiers |= ::user::e_key_system_left_command;

#endif

      }

      if (is_key_pressed(::user::e_key_right_command))
      {

         ekeyModifiers |= ::user::e_key_right_command;

#if defined(__APPLE__)

         ekeyModifiers |= ::user::e_key_system_right_command;

#endif

      }

      if (is_key_pressed(::user::e_key_left_button))
      {

         ekeyModifiers |= ::user::e_key_left_button;

      }

      if (is_key_pressed(::user::e_key_middle_button))
      {

         ekeyModifiers |= ::user::e_key_middle_button;

      }

      if (is_key_pressed(::user::e_key_right_button))
      {

         ekeyModifiers |= ::user::e_key_right_button;

      }

      return ekeyModifiers;

   }


   bool session::is_key_pressed(::user::enum_key ekey)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = memory_new ::map < ::user::enum_key, bool >;

      }

      bool bPressed = false;

      if (ekey == ::user::e_key_shift)
      {

         m_pmapKeyPressed->lookup(::user::e_key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_shift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_command
#ifdef __APPLE__
         || ekey == ::user::e_key_system_command
#endif
         )
      {
         m_pmapKeyPressed->lookup(::user::e_key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_command, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_control
#ifndef __APPLE__
         || ekey == ::user::e_key_system_command
#endif
         )
      {
         m_pmapKeyPressed->lookup(::user::e_key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_control, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_alt)
      {
         m_pmapKeyPressed->lookup(::user::e_key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_left_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_right_alt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->lookup(ekey, bPressed);

      }

ret:

      return bPressed;

   }


   void session::set_key_pressed(::user::enum_key ekey, bool bPressed)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = memory_new ::map < ::user::enum_key, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }


   void session::init1()
   {

      //auto estatus = 
      

      initialize_context_1();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      __construct_new(m_pfs);

      //if (!estatus)
      //{

      //   information("\nFailed to __construct_new(m_pfs)");

      //   m_result.add(estatus);

      //   return false;

      //}

      // throw ::exception(todo("interaction"));
      //if (psystem->m_bUser)
      //{

      //   bool bCreateSessionWindow = defer_create_session_frame_window();

      //   if (!bCreateSessionWindow)
      //   {

      //      warning() <<"Could not create session window";

      //   }

      //}

      //estatus = __construct_new(m_puserpresence);

      //if (!estatus)
      //{

      //   m_result.add(estatus);

      //   information("Failed to create memory_new User Presence");

      //   return false;

      //}

      if (!m_pifs)
      {

         //estatus = 
         __construct(m_pifs, __new(ifs("")));

         //if (!estatus)
         //{

         //   m_result.add(estatus);

         //   information() << "Failed to create ifs";

         //}

      }

      if (!m_premotefs)
      {

         //estatus = 
         __construct(m_premotefs, __new(::fs::remote_native("")));

         //if (!estatus)
         //{

         //   m_result.add(estatus);

         //   information() << "Failed to create remotefs";

         //}

      }

      //if (!m_pftpfs)
      //{

      //   auto pftpfs = __new(ftpfs);

      //   auto estatus = pftpfs->initialize_ftpfs(this, "");

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      information("Failed to create ftpfs");

      //   }

      //   __construct(m_pftpfs, pftpfs);

      //}

      if (!m_pfsdata)
      {

         auto pset = __create_new<::fs::set>();

         auto plink = __create_new < ::fs::link>();

         plink->fill_os_user();

         pset->m_spafsdata.add(plink.m_p);

         pset->m_spafsdata.add(__create_new < ::fs::native>().m_p);

         //estatus = 
         __construct(m_pfsdata, pset);

         //if (!estatus)
         //{

         //   m_result.add(estatus);

         //   information() << "Failed to create fsdata";

         //}


      }

      //information() << ".2";


      //return true;

   }


   void session::defer_initialize_host_window(const ::rectangle_i32 * lpcrect)
   {

      //return ::success;

   }


   void session::init2()
   {

      ::e_status estatus;

      //information() << "apex::session::init2 .1";

      if (acmeapplication()->m_bUser)
      {

         //if (!m_paccount)
         //{

         //   estatus = __construct_new(m_paccount);

         //   if (!estatus)
         //   {

         //      fatal() <<"apex::session::init2 Failed to create account department";

         //      return false;

         //   }

         //}

         //if (!m_paccount->init_instance())
         //{

         //   return false;

         //}


      }

      //initialize_bergedge_application_interface();

      //SetRegistryKey("ca2core");

      if (!InitializeLocalDataCentral())
      {

         //output_error_message("Could not initialize Local data central");

         information("Could not initialize Local data central");

         //return false;

      }

      //return true;

   }


   void session::init()
   {

      ::e_status estatus = ::success;

      ::pointer<::fs::set>pfsset = m_pfsdata;

      if (m_bIfs)
      {

         if (m_pfsdata.is_null())
         {

            __construct(m_pfsdata, __new(::fs::set));

         }

         pfsset = m_pfsdata;

         if (pfsset.is_null())
         {

            pfsset->m_spafsdata.add_unique(m_pifs);

            pfsset->m_spafsdata.add_unique(m_premotefs);

         }

         ::file::listing patha;

         m_pfsdata->root_ones(patha);

      }

      //return estatus;

   }


   void session::term()
   {

      try
      {

         ::acme::del(m_pmapKeyPressed);

      }
      catch (...)
      {

         //m_result.add(error_failed);

      }

   }


   ::u32 session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}


   //bool session::on_create_frame_window()
   //{

   //   return true;

   //}


//   void session::translate_os_key_message(::user::key * pkey)
//   {
//
////      psession->keyboard().translate_os_key_message(pkey);
//
//   }


   void session::pre_translate_message(::message::message * pmessage)
   {

      if (::is_set(m_pappCurrent))
      {

         m_pappCurrent->pre_translate_message(pmessage);

      }

   }


   // ::user::style* session::get_user_style() const
   // {

   //    return m_puserstyle;

   // }


} // namespace apex








#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace apex
{






   //void session::initialize(::particle * pparticle)
   //{

   //   auto estatus = ::apex::session::initialize(pparticle);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   //void session::install_message_routing(::channel* pchannel)
   //{

   //   ::thread::install_message_routing(pchannel);

   ////   //apex::application::install_message_routing(pchannel);
   ////   apex::session::install_message_routing(pchannel);

   //}


   void session::_001OnFileNew()
   {

   }


   void session::launch_app(const ::string & psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const ::string & psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   //void session::reuqest(::request * prequest)
   //{

   //   request(pcreate);

   //}




   //void session::request_topic_file(::payload& varQuery)
   //{

   //   auto psession = get_session();

   //   request_file(psession->m_varTopicFile, varQuery);

   //}


   //void session::request_topic_file()
   //{

   //   auto psession = get_session();

   //   request_file(psession->m_varTopicFile);

   //}


   ::pointer<::apex::application>session::get_current_application()
   {

      auto psession = get_session();

      return psession->m_pappCurrent;

   }

   bool session::is_remote_session()
   {


      return m_pcontext->m_papexcontext->os_context()->is_remote_session();


   }


   //bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   //{

   //   if (emouse == ::user::e_mouse_left_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_left_button);
   //   }
   //   else if (emouse == ::user::e_mouse_right_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_right_button);
   //   }
   //   else if (emouse == ::user::e_mouse_middle_button)
   //   {
   //      return psession->is_key_pressed(::user::e_key_middle_button);
   //   }
   //   else
   //   {
   //      throw ::exception(::exception("not expected enum_mouse value"));
   //   }


   //}





//
//   bool session::open_file(::filemanager::data* pdata, ::file::item_array& itema)
//   {
//
//      UNREFERENCED_PARAMETER(pdata);
//
//      if (itema.get_size() > 0)
//      {
//
//         return true;
//
//      }
//
//      return false;
//
//   }








   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = memory_new nature::database(this);

      //if(m_pdatabase == nullptr)
      //{
      //   information("VmpLightApp::init_instance failed to instatiate LightDB");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   information("VmpLightApp::init_instance failed to initialize LightDB");
      //   return false;
      //}

      return true;

   }


   //void session::check_topic_file_change()
   //{

   //   auto psession = get_session();

   //   if (psession->m_varCurrentImpactFile != psession->m_varTopicFile && !psession->m_varTopicFile.is_empty())
   //   {

   //      psession->m_varCurrentImpactFile = psession->m_varTopicFile;

   //      request_topic_file();

   //   }

   //}


   //::user::place_holder_ptra session::get_place_holder(::pointer<::user::frame_window>pmainframe, ::request * prequest)
   //{

   //   UNREFERENCED_PARAMETER(pcreate);

   //   ::user::place_holder_ptra holderptra;


   //   ::application & app = App(pmainframe->get_app());

   //   string strAppName = app.m_strAppName;

   //   //if(get_document()->get_typed_impact < ::bergedge::pane_impact >() != nullptr)
   //   //{

   //   //   get_document()->get_typed_impact < ::bergedge::pane_impact >()->set_current_tab_by_id("app:" + strAppName);

   //   //   holderptra.add(get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_tab_holder(get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_tab_by_id("app:" + strAppName)));

   //   //}
   //   //else
   //   //{

   //   //   holderptra.add(get_document()->get_typed_impact < ::bergedge::impact >());

   //   //}

   //   return holderptra;

   //}

   //bool session::place(::user::main_frame* pmainframe, ::create* pcreate)
   //{

   //   //get_place_holder(pmainframe, pcreate).hold(pmainframe);

   //   return true;

   //}





   void session::set_app_title(const ::string & pszAppId, const ::string & pszTitle)
   {

      ::pointer<::acme::application>papplication;

      if (m_applicationa.lookup(pszAppId, papplication) && papplication)
      {

         //::pointer<::bergedge::pane_impact>ppaneimpact = get_document()->get_typed_impact < ::bergedge::pane_impact >();

         //if(ppaneimpact != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneimpact->get_pane_by_id("app:" + strAppName);

         //   if(ppane != nullptr)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneimpact->on_layout(pgraphics);

         //   }

         //}

      }

   }



   ::pointer<::apex::session>session::get_session()
   {

      return this;

   }



   //   bool session::is_serviceable() const
   //   {
   //
   //
   ////      return ::session::application::is_serviceable();
   //      return false;
   //
   //
   //   }


      //bool session::on_uninstall()
      //{


      //   bool bOk1 = true;
      //   bool bOk2 = true;

      //   try
      //   {

      //      bOk1 = ::apex::session::on_uninstall();

      //   }
      //   catch(...)
      //   {
      //      bOk1 = false;
      //   }




      //   return bOk1 && bOk2;


      //}


      //void session::os_native_bergedge_start()
      //{

      //   if (!::application::os_native_bergedge_start())
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //service_base * session::allocate_new_service()
      //{


      //   return ::application::allocate_new_service();


      //}





   //::draw2d::cursor* session::get_default_cursor()
   //{

   //   return pdraw2d->get_cursor(m_ecursorDefault);

   //}


   void session::main()
   {

      //return ::apex::session::main();
      return ::thread::main();

   }


   //::apex::session * session::query_bergedge()
   //{

   //   ::apex::session * psession = nullptr;

   //   if(psystem->m_pbergedgemap == nullptr)
   //      return nullptr;

   //   if(!psystem->m_pbergedgemap->lookup(0,psession))
   //   {
   //      return nullptr;
   //   }

   //   return psession;

   //}


   //void session::on_user_logon(::account::user* puser)
   //{

   //   ::apex::session::on_user_logon(puser);

   //}


//   void session::interactive_credentials(::account::credentials* pcredentials)
//   {
//
//
//      //if (!USER)
//      //{
//
//      //   //   //pcredentials->m_puser->m_estatusAuthentication = ::error_credentials_non_interactive;
//
//      //   return;
//
//      //}
//      pcredentials->m_estatus = error_failed;
//
//      manual_reset_event ev;
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      //if (m_pmainpane != nullptr && m_pmainpane == nullptr)
//      //{
//
//      //   try
//      //   {
//
//      //      m_pmainpane->interactive_credentials(pcredentials);
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
//      if (pcredentials->m_estatus == ::success_credentials ||
//         ::failed(pcredentials->m_estatus, STATUS_RANGE_AUTHENTICATION))
//      {
//
//         return;
//
//      }
//
//#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)
//      //attach_thread_input_to_main_thread(false);
//#endif
//
//      ::apex::session::interactive_credentials(pcredentials);
//
//      if (pcredentials->m_estatus == ::success_credentials)
//      {
//
//         return;
//
//      }
//
//      if (!pcredentials->m_bInteractive)
//      {
//
//         pcredentials->m_estatus = error_credentials_non_interactive;
//
//         return;
//
//      }
//
//      auto puser = pcredentials->m_puser;
//
//      //auto pdialog = ::__create_new<::account::dialog>();
//
//      //pdialog->initialize_account_dialog(pcredentials);
//
//      //pdialog->get_credentials();
//
//      //pdialog->DestroyWindow();
//
//
//   }


   //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32& rectangle, ::draw2d::brush_pointer& pbrushText)
   //{

   //   string_array& straTitle = pane.m_straTitle;

   //   pgraphics->set(pbrushText);

   //   if (straTitle.get_count() <= 1)
   //   {

   //      pgraphics->_DrawText(pane.get_title(), recte_bottom_left, e_draw_text_no_prefix);

   //   }
   //   else
   //   {

   //      ::rectangle_i32 rectangleText(rectangle);


   //      ::write_text::font_pointer pfont;
   //      font = pgraphics->get_current_font();
   //      size_i32 sSep = ptab->get_data()->m_sizeSep;
   //      ::rectangle_i32 rectangleEmp;
   //      for (index i = 0; i < straTitle.get_size(); i++)
   //      {
   //         string str = straTitle[i];
   //         size_i32 s = pane.m_sizeaText[i];
   //         rectangleText.right = rectangleText.left + s.cx();
   //         pgraphics->_DrawText(str, rectangleTexte_bottom_left, e_draw_text_no_prefix);
   //         rectangleText.left += s.cx();
   //         if (i < straTitle.get_upper_bound())
   //         {
   //            rectangleText.right = rectangleText.left + sSep.cx();
   //            rectangleEmp = rectangleText;
   //            rectangleEmp.deflate(1, 1);
   //            ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
   //            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //            if (ptab->m_pitemHover == (::enum_element)(::e_element_split + i))
   //            {
   //               pgraphics->fill_rectangle(rectangleEmp, argb(128, 150, 184, 255));
   //               pgraphics->set(ptab->get_data()->m_pbrushTextHover);
   //            }
   //            else
   //            {
   //               //pgraphics->fill_rectangle(rectangleEmp,argb(128,208,223,233));
   //               pgraphics->set(ptab->get_data()->m_pbrushText);
   //            }
   //            pgraphics->set(ptab->m_pfontTab);
   //            pgraphics->set_alpha_mode(emode);
   //            pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectangleText, e_align_center, e_draw_text_no_prefix);
   //            rectangleText.left += sSep.cx();
   //            pgraphics->set(pfont);
   //            pgraphics->set(pbrushText);
   //         }
   //      }

   //   }

   //}


   string_array session::get_user_wallpaper()
   {

      string_array stra;

      //string_array straSource = psession->userex()->get_wallpaper();

      //for (string str : straSource)
      //{

      //   if (str.case_insensitive_begins_eat("file://"))
      //   {

      //      str = ::url::decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }


   ::user::primitive* session::get_user_interaction_host()
   {

      return m_puserprimitiveHost;

   }


   ::user::primitive * session::get_host_primitive()
   {

      return m_puserprimitiveHost;
   
   }


   void session::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      command_handler(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      if (acmesystem())
      {

         acmesystem()->m_papexsystem->route_command(pcommand, false);

      }

   }


   void session::frame_pre_translate_message(::message::message* pmessage)
   {

//      if (pmessage->m_atom == WM_GETTEXT
//         || pmessage->m_atom == WM_GETTEXTLENGTH
//         )
//      {
//
//         pmessage->m_uiMessageFlags |= 3; // message considered pre translated
//         pmessage->m_uiMessageFlags |= 16384; //  by early optmization
//
//         return;
//
//      }
      //else if (pmessage->m_atom == e_message_mouse_move)
      //{

      //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
      //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   return;

      //}

      //try
      //{

      //   ::pointer<::user::interaction>pinteraction;

      //   while (get_frame(pinteraction))
      //   {

      //      try
      //      {

      //         if (pinteraction != nullptr)
      //         {

      //            pinteraction->pre_translate_message(pmessage);

      //            if (pmessage->m_bRet)
      //               return;

      //         }

      //      }
      //      catch (const ::exception & e)
      //      {

      //         if (e.is < ::exit_exception>())
      //         {

      //            __rethrow(::transfer(e));

      //         }

      //      }
      //      catch (...)
      //      {
      //      }

      //   }

      //}
      //catch (const ::exception & e)
      //{

      //   if (e.is < ::exit_exception>())
      //   {

      //      __rethrow(::transfer(e));

      //   }

      //}
      //catch (...)
      //{

      //   pmessage->m_bRet = true;

      //}

   }



   void session::destroy()
   {

      ::acme::application_container::m_applicationa.erase_all();

      ::apex::context::destroy();

      //return success;

   }

   


} // namespace apex



