#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#include "core/user/account/_account.h"
#endif
#include "apex/platform/static_setup.h"
#include "aura/update.h"
#include "aura/xml/_.h"
#include "core/user/user/shell.h"
#include "core/user/user/_tree.h"


//void __html_initialize(::user::user * puserex);
//::type get_html_document_type();

#ifdef WINDOWS_DESKTOP
#include <Commdlg.h>
#endif


#define new ACME_NEW


//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_CORE void attach_thread_input_to_main_thread(bool bAttach);
//#endif

#ifdef MACOS

bool macos_set_user_wallpaper(int iScreen, const char * psz);

long long mm_get_user_wallpaper(long long llScreen, char ** ppp);

CLASS_DECL_CORE string macos_get_user_wallpaper(int iScreen)
{

   string str;

   char * psz = nullptr;

   mm_get_user_wallpaper(iScreen, &psz);

   if(psz != nullptr)
   {

      str = psz;

      free(psz);

   }

   return str;

}

#endif

CLASS_DECL_CORE ::mutex * get_cred_mutex();


namespace core
{


  /* class user_static_factory
   {
   public:

      user_static_factory()
      {

         create_factory < user, ::user::user >();

      }

   };

   user_static_factory g_userstaticfactory;*/

   user::user()
   {
      
      m_pcoreuser = this;

      m_ptemplateForm = nullptr;
      m_ptemplateChildForm = nullptr;
      m_ptemplatePlaceHolder = nullptr;
      m_ptemplateHtmlChildForm1 = nullptr;

   }


   user::~user()
   {

   }


   estatus user::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus user::init1()
   {

      create_factory < ::user::picture::picture_impl >();

      //create_factory <::userex::keyboard_layout >();

      create_factory <::userex::top_edit_view >();
      create_factory <::userex::top_toggle_view >();
      create_factory <::userex::top_view >();

      create_factory <::user::tab_view >();

      create_factory < ::user::form_view > ();

      create_factory < simple_pane_document >();


 /*     if (!create_user_shell())
      {

         WARN("Failed to create_user_shell");

         return false;

      }*/


      if (!::base::user::init1())
      {

         return false;

      }

      //if (!initialize1_experience())
      //{

      //   return false;

      //}
      
      //m_phtml->add_ref(OBJ_REF_DBG_ARGS);

      //if(m_phtml == nullptr)
      //   return false;

      //m_phtml->construct(this);

      //m_bProcessInitializeResult = true;

      return true;

   }

   ::user::shell* user::shell()
   {

      if (!m_pshell)
      {

         auto estatus = create_user_shell();

         if (!estatus)
         {

            TRACE("failed to create user shell");

         }

      }

      return m_pshell;

   }


   ::estatus user::init()
   {

      if (!::base::user::init())
      {

         return ::error_failed;

      }

      if (!m_typeDefaultMeshData)
      {

         m_typeDefaultMeshData = __type(::simple_mesh_data);

      }

      if (!m_typeDefaultListData)
      {

         m_typeDefaultListData = __type(::simple_list_data);

      }

      if (!m_typeDefaultListHeader)
      {

         m_typeDefaultListHeader = __type(::simple_list_header_control);

      }

      
      create_factory < ::html::html >();
      create_factory < int_biunique  >();
      create_factory <::user::plain_edit >();
      create_factory < xfplayer_view_line  >();
      create_factory <::user::place_holder >();
      create_factory <::user::combo_box >();
      create_factory <::user::check_box >();
      create_factory <::user::place_holder_container >();

      create_factory < ::account::view >();

      create_factory < form_document >();
      create_factory < ::userex::split_view::Pane  >();
      create_factory < simple_child_frame  >();
      create_factory < ::userex::split_view  >();

      create_factory < ::simple_mesh_data  >();
      create_factory < ::simple_list_data  >();
      create_factory < ::simple_list_header_control  >();

      create_factory <::user::tree >();


      create_factory <simple_list_view >();
      create_factory <::user::document >();
      create_factory <simple_printer_list_view >();



      create_factory <::user::show < ::user::plain_edit > >();
      create_factory <::user::show < ::user::tree > >();
      create_factory <::user::show < ::user::list > >();

      create_factory <menu_document >();
      create_factory <menu_frame >();
      create_factory <menu_view >();

      

      auto& sys = System;

      auto typeinfo = sys.get_simple_frame_window_type_info();

      auto ptemplate = __new(::user::multiple_document_template(
         "system/form",
         __type(form_document),
         System.get_simple_frame_window_type_info(),
         __type(::user::form_view)));

      ptemplate->initialize(this);

      m_ptemplateForm = ptemplate;


      add_document_template(ptemplate);

      ptemplate = __new(::user::multiple_document_template(
         "system/form",
         __type(form_document),
         User.get_simple_child_frame_type_info(),
         __type(::user::form_view)));

      ptemplate->initialize(this);

      m_ptemplateChildForm = ptemplate;

      add_document_template(m_ptemplateChildForm);

      ptemplate = __new(::user::multiple_document_template(
            "system/form",
            __type(::user::document),
         System.get_simple_frame_window_type_info(),
         __type(::user::place_holder)));

      ptemplate->initialize(this);

      m_ptemplatePlaceHolder = ptemplate;

      add_document_template(ptemplate);

      auto estatus = initialize_html();

      if (!estatus)
      {

         //m_result.add(estatus);

         ERR("Failed to initialize html");

         return estatus;

      }
      
      estatus = __compose(m_phtml);
      
      if(!estatus)
      {
         
         return estatus;
         
      }

      TRACE("::user::application::initialize");

      auto pdocumentUser = create_xml_document();

      string strUser = Context.file().as_string(Context.dir().appdata() / "langstyle_settings.xml");

      string strLangUser;

      string strStyleUser;

      if (pdocumentUser->load(strUser))
      {

         if (pdocumentUser->get_child("lang") != nullptr)
         {

            strLangUser = pdocumentUser->get_child("lang")->get_value();

         }

         if (pdocumentUser->get_child("style") != nullptr)
         {

            strStyleUser = pdocumentUser->get_child("style")->get_value();

         }

      }

      if (strLangUser.has_char())
      {

         Application.set_locale(strLangUser, ::source_database);

      }

      if (strStyleUser.has_char())
      {

         Application.set_schema(strStyleUser, ::source_database);

      }

      //string strLicense = Application.get_license_id();


      //var & varTopicQuey = System.m_varTopicQuery;

//      bool bHasInstall = System.has_property("install");
//
//      bool bHasUninstall = System.has_property("uninstall");
//
//      if (!(bHasInstall || bHasUninstall)
//            && Application.m_bLicense
//            && strLicense.has_char())
//      {
//
//         // call application's is_licensed function
//         // because if delay is needed for authentication -
//         // or either asking for authentication -
//         // current application startup won't be
//         // exited by timeout.
//
//         i32 iRetry = 1;
//
//retry_license:
//
//         iRetry--;
//
//         if (!Session.is_licensed(strLicense))
//         {
//
//            //Session.licensing().m_mapInfo.remove_key(strLicense);
//
//            if (iRetry > 0)
//            {
//
//               goto retry_license;
//
//            }
//
//            return false;
//
//         }
//
//      }

      //set_data_server(Application.dataserver());


      create_factory <::userex::pane_tab_view >();
      create_factory <form_frame >();
      create_factory <form_child_frame >();

      create_factory <simple_toolbar >();
      create_factory <::experience::orto_button >();

      estatus = initialize_filemanager_component(Session.m_pappCurrent);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::estatus user::init2()
   {

      if (!::apex::department::init2())
      {

         return false;

      }

      return true;

   }


   void user::finalize()
   {

      try
      {

         __release(m_pshell);

      }
      catch (...)
      {

      }

      try
      {

         ::apex::department::term();

      }
      catch (...)
      {

      }


   }




   ::type user::controltype_to_typeinfo(::user::e_control_type econtroltype)
   {

      return ::type();

   }

   void user::term()
   {

   }




   __pointer(::form_document) user::create_form(::object * pobject, ::type type, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   {

      if (!type)
      {

         return nullptr;

      }

      __pointer(::user::impact_system) psystem = m_mapTemplate[type];

      if (psystem.is_null())
      {

         psystem = __new(::user::multiple_document_template(
                        m_ptemplateForm->m_strMatter,
                        m_ptemplateForm->m_typeDocument,
                        m_ptemplateForm->m_typeFrame,
                        type));

         m_mapTemplate[type] = psystem;

         User.document_manager()->add_document_template(psystem);

      }

      if (pobject == nullptr)
      {

         if (pwndParent.is_set())
         {

            pobject = pwndParent;

         }
         else
         {

            pobject = this;

         }

      }

      __pointer(::create) pcreate(e_create);

      pcreate->m_bMakeVisible = true;

      pcreate->m_puserinteractionParent = pwndParent;

      pcreate->m_varArgs = varArgs;

      if (var.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = var.get_file_path();

      }

      psystem->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      __pointer(::user::form_window) pform = pdocument->get_typed_view < ::user::form_window >();

      return pdocument;

   }


   ::estatus user::dialog_box(::layered * pobjectContext, const char * pszMatter, property_set & propertyset, ::future future)
   {

      auto pbox = __object(pobjectContext)->__create_new < class ::userex::message_box >();

      pbox->add_property_set(&propertyset);

      if (!pbox->show(pszMatter))
      {

         return ::error_failed;

      }

      future.receive_response(pbox->m_idResponse);

      return ::success;

   }


   ::estatus user::ui_message_box(::layered* pobjectContext, ::user::primitive * puiOwner, const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::future future)
   {

      auto pbox = __object(pobjectContext)->__create_new < ::userex::message_box >();

      property_set & propertyset = pbox->get_property_set();

      propertyset["message"] = pszMessage;

      pbox->add(future);

      if (::is_set(puiOwner))
      {

         propertyset["application_name"] = App(__object(pobjectContext)).m_strAppName;

      }
      else if (::is_set(Session.m_pappCurrent))
      {

         string strAppName = Sess(__object(pobjectContext)).m_pappCurrent->m_strAppName;

         propertyset["application_name"] = strAppName;

      }

      string strMatter;

      if((emessagebox & MB_YESNOCANCEL) == MB_YESNOCANCEL)
      {

         strMatter = "system\\user\\message_box\\yesnocancel.xhtml";

      }
      else if ((emessagebox & MB_YESNO) == MB_YESNO)
      {

         strMatter = "system\\user\\message_box\\yesno.xhtml";

      }
      else
      {

         strMatter = "system\\user\\message_box\\ok.xhtml";

      }

      try
      {

         if(!pbox->show(strMatter))
         {
            // commented 2020-06-28 03:32
            //string strMessage = pszMessage;

            //strMessage.replace("<br>","\r\n");

            //return ::message_box(pwndOwner->get_safe_handle(),strMessage,Application.m_strAppName,fuStyle, functionargResult);

            return ::error_failed;

         }

      }
      catch(...)
      {

         return ::error_failed;
         //string strMessage = pszMessage;

         //strMessage.replace("<br>","\r\n");

         //return ::message_box(pwndOwner == nullptr ? nullptr : pwndOwner->get_handle(),strMessage,Application.m_strAppName,fuStyle, functionargResult);

      }

      //return 0;

      return ::success;

      //if(pbox->m_idResponse == "ok")
      //{

      //   return IDOK;

      //}
      //else if(pbox->m_idResponse == "yes")
      //{

      //   return IDYES;

      //}
      //else if(pbox->m_idResponse == "no")
      //{

      //   return IDNO;

      //}
      //else if(pbox->m_idResponse == "cancel")
      //{

      //   return IDCANCEL;

      //}

      //if(fuStyle & MB_YESNOCANCEL)
      //{

      //   return IDCANCEL;

      //}
      //else
      //{

      //   return 0;

      //}

   }


   ::estatus user::ui_message_box_timeout(::layered * pobjectContext, ::user::primitive * puiOwner, const char* pszMessage, const char* pszTitle, const ::duration & durationTimeout, ::emessagebox emessagebox, ::future future)
   {

      UNREFERENCED_PARAMETER(puiOwner);

      auto pbox = __object(pobjectContext)->__create_new < ::userex::message_box >();

      pbox->value("message") = pszMessage;

      pbox->add(future);

      string strTitle = App(__object(pobjectContext)).get_title();

      pbox->value("application_name") = strTitle;

      pbox->m_tickDelay = (DWORD)durationTimeout.get_total_milliseconds();

      string strMatter;

      if ((emessagebox & MB_YESNOCANCEL) == MB_YESNOCANCEL)
      {

         strMatter = "system\\user\\message_box_timeout\\yesnocancel.xhtml";

      }
      else
      {

         strMatter = "system\\user\\message_box_timeout\\ok.xhtml";

      }

      if (!pbox->show(strMatter))
      {

         return ::error_failed;
         //__throw(resource_exception());

      }

      //if (pbox->m_idResponse == "ok")
      //{

      //   return IDOK;

      //}
      //else if (pbox->m_idResponse == "yes")
      //{

      //   return IDYES;

      //}
      //else if (pbox->m_idResponse == "no")
      //{

      //   return IDNO;

      //}
      //else if (pbox->m_idResponse == "cancel")
      //{

      //   return IDCANCEL;

      //}

      //if (fuStyle & MB_YESNOCANCEL)
      //{

      //   return IDCANCEL;

      //}
      //else
      //{

      //   return 0;

      //}

      return ::success;

   }


   i32 user::track_popup_menu(const char * pszMatter, const ::point & point, __pointer(::user::interaction) puie)
   {

      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(puie);

      return 1;

   }


   bool user::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
   {

      i64 i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.Empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.Format("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.Format("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.Format("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.Format("1 KB");

      }
      else
      {

         strSize.Format("0 KB");

      }

      if (bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool user::get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending)
   {

      //db_server * pcentral = dynamic_cast <db_server *> (&System.m_psimpledb->db());

      //if (pcentral == nullptr)
      //{

      //   return false;

      //}

      //return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);

      return false;

   }


   void user::data_on_after_change(::message::message * pmessage)
   {

      SCAST_PTR(::database::change_event, pchange, pmessage);

      if (pchange->m_datakey == "ca2.savings")
      {

         CHANGE_EVENT_DATA_GET(pchange, (::i32 &) Session.savings().m_eresourceflagsShouldSave.m_eenum);

      }

   }


   bool user::modal_get_color(::user::interaction * puiOwner, ::hls & hls)
   {

#ifdef WINDOWS_DESKTOP

      CHOOSECOLOR cc;
      COLORREF crCustColors[16];

      // init-int this array did not affect the mouse problem
      // uint idx ;
      // for (idx=0; idx<16; idx++) {
      // crCustColors[idx] = RGB(idx, idx, idx) ;
      // }

      ::color c(hls);

      ZeroMemory(&cc, sizeof(cc));
      cc.lStructSize = sizeof(CHOOSECOLOR);
      cc.rgbResult = c.get_rgb();
      cc.lpCustColors = crCustColors;

      cc.Flags = CC_RGBINIT | CC_FULLOPEN;
      cc.hwndOwner = puiOwner->get_safe_handle(); // this hangs parent, as well as me

      if (::ChooseColor(&cc))
      {

         c.set_COLORREF(cc.rgbResult | (255 << 24));

         c.get_hls(hls);

         return true;

      }

      return false;

#else

      User.will_use_view_hint(COLORSEL_IMPACT);

      auto pdocument = m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(puiOwner->get_context_application(), ::type_null, __visible(true));

      __pointer(::userex::color_view) pview = pdocument->get_typed_view < ::userex::color_view >();

      __pointer(::user::frame_window) pframe = pview->GetTopLevelFrame();

      pframe->SetOwner(puiOwner);

      pframe->_001RunModalLoop();

      hls = pview->m_hls;

      return true;

#endif


   }


   void  user::AddToRecentFileList(const char * pszPathName)

   {

      UNREFERENCED_PARAMETER(pszPathName);


   }


   void user::_001OnFileNew()
   {

      ASSERT(Application.document_manager() != nullptr);

      if (Application.document_manager() == nullptr)
      {

         return;

      }

      Application.document_manager()->_001OnFileNew();

   }


   void user::term_instance()
   {

   }


   __pointer(::form_document) user::create_form(::object * pobject, __pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   {

      if (m_ptemplateForm == nullptr)
      {

         return nullptr;

      }

      __pointer(::create) pcreate(e_create);

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserinteractionParent = pwndParent;

      pcreate->m_puiAlloc = pview;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (var.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = var.get_file_path();

      }

      if (var.get_type() == ::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {

         pcreate->m_bHold = false;

      }

      m_ptemplateForm->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      __pointer(::user::form_window) pform = pdocument->get_typed_view < ::user::form_window >();

      if (pform.is_set())
      {

         pform->set_form_callback(pcallback);

      }

      return pdocument;

   }


   __pointer(::form_document) user::create_form(::object * pobject, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   {

      auto ptemplateForm = m_ptemplateForm;

      //::aura::application * papp = ::get_context_application(pobject);

      //if (papp == nullptr)
      //{

      //   if (pwndParent.is_set())
      //   {

      //      papp = pwndParent->get_context_application();

      //   }
      //   else if (pcallback != nullptr)
      //   {

      //      papp = pcallback->get_context_application();

      //   }
      //   else
      //   {

      //      papp = get_context_application();

      //   }

      //}

      auto pcreate = pobject->__create_new < ::create >();

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserinteractionParent = pwndParent;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (var.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = var.get_file_path();

         string strPath = var.get_file_path();

      }

      if (var.get_type() == ::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {

         pcreate->m_bHold = false;

      }

      ptemplateForm->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      __pointer(::user::form_window) pform = pdocument->get_typed_view < ::user::form_window >();

      if (pform.is_set() && ::is_null(pform->get_form_callback()))
      {

         pform->set_form_callback(pcallback);

      }

      return pdocument;

   }


   __pointer(::form_document) user::create_child_form(::object * pobject, __pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   {

      if (m_ptemplateChildForm == nullptr)
      {

         return nullptr;

      }

      ::apex::application * papp = ::get_context_application(pobject);

      if (papp == nullptr)
      {

         if (pwndParent.is_set())
         {

            papp = pwndParent->get_context_application();

         }
         else if (pcallback != nullptr)
         {

            papp = pcallback->get_context_application();

         }
         else
         {

            papp = get_context_application();

         }

      }

      auto pcreate = __new(::create(pobject));

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserinteractionParent = pwndParent;

      pcreate->m_puiAlloc = pview;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (var.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = var.get_file_path();

      }

      if (var.get_type() == ::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {

         pcreate->m_bHold = false;

      }

      m_ptemplateChildForm->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      __pointer(::user::form_window) pform = pdocument->get_typed_view < ::user::form_window >();

      if (pform.is_set())
      {

         pform->set_form_callback(pcallback);

      }

      return pdocument;

   }


   __pointer(::form_document) user::create_child_form(::object * pobject, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   {

      ::apex::application * papp = ::get_context_application(pobject);

      if (papp == nullptr)
      {

         if (pwndParent.is_set())
         {

            papp = pwndParent->get_context_application();

         }
         else if (pcallback != nullptr)
         {

            papp = pcallback->get_context_application();

         }
         else
         {

            papp = get_context_application();

         }

      }

      auto pcreate = pobject->__create_new < ::create > ();

      pcreate->m_bMakeVisible = true;

      pcreate->m_puserinteractionParent = pwndParent;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (var.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         ::file::path path = var.get_file_path();

         pcreate->m_pcommandline->m_varFile = path;

      }

      m_ptemplateChildForm->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      __pointer(::user::form_window) pform = pdocument->get_typed_view < ::user::form_window >();

      if (pform.is_set())
      {

         pform->set_form_callback(pcallback);

      }

      return pdocument;

   }

   bool is_html_file(string strFilePath)
   {

      return file_extension_dup(strFilePath).contains_ci("htm");
   }

   __pointer(::form_document) user::create_child_form(::object * pobject, ::type type, __pointer(::user::interaction) pwndParent, var var, ::var varArgs)
   {

      if (!type)
      {

         return nullptr;

      }

      ::user::impact_system * psystem = m_mapTemplate[type];

      if (psystem == nullptr)
      {

         ::type typeDocument = m_ptemplateChildForm->m_typeDocument;

         if (is_html_file(var.get_file_path()))
         {

            typeDocument = get_html_document_type();

         }

         auto psystemNew = __new(::user::multiple_document_template(
                                m_ptemplateChildForm->m_strMatter,
                                typeDocument,
                                m_ptemplateChildForm->m_typeFrame,
                                type));

         psystemNew->initialize(pobject);

         psystem = psystemNew;

         m_mapTemplate[type] = psystem;

         document_manager()->add_document_template(psystem);

      }

      if (pobject == nullptr)
      {

         if (pwndParent.is_set())
         {

            pobject = pwndParent;

         }
         else
         {

            pobject = this;

         }

      }

      auto pcreate = pobject->__create_new < ::create >();

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserinteractionParent = pwndParent;

      pcreate->m_varArgs = varArgs;

      if (var.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = var.get_file_path();

      }

      psystem->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      __pointer(::user::form_window) pform = pdocument->get_typed_view < ::user::form_window >();

      return pdocument;

   }


   ::user::document * user::hold(__pointer(::user::interaction) pinteraction)
   {

      __pointer(::create) pcreate(e_create_new, pinteraction.m_p);

      pcreate->m_bMakeVisible = false;

      pcreate->m_bHold = false;

      m_ptemplatePlaceHolder->do_request(pcreate);

      __pointer(::form_document) pdocument = ::user::__document(pcreate);

      __pointer(::user::place_holder) pholder = pdocument->get_typed_view < ::user::place_holder  >();

      pholder->place_hold(pinteraction);

      return pdocument;

   }


   void user::route_command_message(::user::command * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   __pointer(::user::list_header) user::default_create_list_header(::layered * pobjectContext)
   {

      return __object(pobjectContext)->__id_create < ::user::list_header > (default_type_list_header());

   }


   __pointer(::user::mesh_data) user::default_create_mesh_data(::layered * pobjectContext)
   {

      return __object(pobjectContext)->__id_create < ::user::mesh_data > (default_type_list_data());

   }


   __pointer(::user::list_data) user::default_create_list_data(::layered * pobjectContext)
   {

      return __object(pobjectContext)->__id_create <::user::list_data >(default_type_list_data());

   }


   ::type user::default_type_mesh_data()
   {

      return m_typeDefaultMeshData;

   }


   ::type user::default_type_list_header()
   {

      return m_typeDefaultListHeader;

   }


   ::type user::default_type_list_data()
   {

      return m_typeDefaultListData;

   }


   string user::get_os_desktop_theme()
   {

      return impl_get_os_desktop_theme();

   }


   bool user::set_os_desktop_theme(string strTheme)
   {

      return impl_set_os_desktop_theme(strTheme);

   }


   string user::get_wallpaper(index iScreen)
   {

      return impl_get_wallpaper(iScreen);

   }


   bool user::set_wallpaper(index iScreen, string strWallpaper)
   {

      return impl_set_wallpaper(iScreen, strWallpaper);

   }


   string_array user::get_wallpaper()
   {

      ::count iMonitorCount = System.get_monitor_count();

      string_array stra;

      for (index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         stra.add(get_wallpaper(iScreen));

      }

      bool bAllEqual = true;

      for (index iScreen = 1; iScreen < iMonitorCount; iScreen++)
      {

         if (stra[iScreen] != stra[iScreen - 1])
         {

            bAllEqual = false;

         }

      }

      if (bAllEqual && stra.get_count() >= 2)
      {

         stra.set_size(1);

      }

      return stra;

   }


   void user::set_wallpaper(const string_array & straWallpaper)
   {

      if (straWallpaper.is_empty())
      {

         return;

      }

      ::count iMonitorCount = System.get_monitor_count();

#ifdef LINUX

      if (iMonitorCount > 0)
      {

         set_wallpaper(0, straWallpaper[0]);

      }

#else

      for (index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         string strWallpaper = iScreen % straWallpaper;

         set_wallpaper(iScreen, strWallpaper);

      }

#endif

   }


#ifdef WINDOWS_DESKTOP


   void user::enable_wallpaper_change_notification()
   {

   }


   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != FALSE;

   }


   string user::impl_get_wallpaper(index iScreen)
   {

      wstring  wstr;

      wstr.get_string_buffer(MAX_PATH * 8);
      //UINT uLen = pwsz.memsize();

      if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, (UINT)wstr.get_storage_length(), wstr.m_pdata, 0))
      {
         return "";

      }
      wstr.release_string_buffer();

      return wstr;

   }


   string user::impl_get_os_desktop_theme()
   {

      return "";

   }


   bool user::impl_set_os_desktop_theme(string strTheme)
   {

      UNREFERENCED_PARAMETER(strTheme);

      return true;

   }


#elif defined(LINUX)


   bool user::impl_set_os_desktop_theme(string strTheme)
   {

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      switch (::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:
      {

         bool bOk1 = ::user::gsettings_set("org.gnome.desktop.interface", "gtk-theme", strTheme);

         bool bOk2 = true;

         //if(::file::system_short_name().contains_ci("manjaro"))
         {

            bOk2 = ::user::gsettings_set("org.gnome.desktop.wm.preferences", "theme", strTheme);

         }

         Sleep(300);

         ::user::gsettings_sync();

         Sleep(300);

         return bOk1 && bOk2;

      }

      case ::user::desktop_mate:

      //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         return false;

      }

      return true;

   }


   string user::impl_get_os_desktop_theme()
   {

      return ::os::get_os_desktop_theme();

   }


   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // wall-changer sourceforge.net contribution

      switch (::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         return ::user::gsettings_set("org.gnome.desktop.background", "picture-uri", "file://" + strLocalImagePath);

      case ::user::desktop_mate:

         return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

      case ::user::desktop_lxde:

         call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         return false;

      }

      return true;

   }


   string user::impl_get_wallpaper(index iScreen)
   {

      return ::os::get_wallpaper(iScreen);

   }


   void user::enable_wallpaper_change_notification()
   {

      switch (::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         ::user::g_enable_wallpaper_change_notification("org.gnome.desktop.background", "picture-uri");

         break;

      case ::user::desktop_mate:

         ::user::g_enable_wallpaper_change_notification("org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, display_none, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

   }


#elif defined(APPLE_IOS)

   bool user::impl_set_os_desktop_theme(string strTheme)
   {

      return false;

   }

   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return false;

   }

   string user::impl_get_wallpaper(index iScreen)
   {

      return string();

   }

   string user::impl_get_os_desktop_theme()
   {

      return "";

   }

   void user::enable_wallpaper_change_notification()
   {

   }


#elif defined(ANDROID)

   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return ::get_context_system()->android_set_user_wallpaper(strLocalImagePath);

   }

   string user::impl_get_wallpaper(index iScreen)
   {

      string strLocalImagePath;

      ::get_context_system()->android_get_user_wallpaper(strLocalImagePath);

      return strLocalImagePath;

   }

   void user::enable_wallpaper_change_notification()
   {

   }


   string user::impl_get_os_desktop_theme()
   {

      return "";

   }


   bool user::impl_set_os_desktop_theme(string strTheme)
   {

      UNREFERENCED_PARAMETER(strTheme);

      return true;

   }



#elif defined(_UWP)


   void user::enable_wallpaper_change_notification()
   {

   }


   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // Someday we will be together...
      // What do you mean...
      // Cold Water...

      return false;

   }

   string user::impl_get_wallpaper(index iScreen)
   {

      return string();

   }

   string user::impl_get_os_desktop_theme()
   {

      return "";

   }


   bool user::impl_set_os_desktop_theme(string strTheme)
   {

      UNREFERENCED_PARAMETER(strTheme);

      return true;

   }

#else


   void user::enable_wallpaper_change_notification()
   {

   }

   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return macos_set_user_wallpaper((int)iScreen, strLocalImagePath);

   }

   string user::impl_get_wallpaper(index iScreen)
   {

      return macos_get_user_wallpaper((int)iScreen);

   }





   string user::impl_get_os_desktop_theme()
   {

      return "";

   }


   bool user::impl_set_os_desktop_theme(string strTheme)
   {

      UNREFERENCED_PARAMETER(strTheme);

      return true;

   }


#endif



} //namespace user



namespace core
{


   ::estatus user::initialize_userex()
   {

      ////if (is_system())
      //{

      //   create_factory <::user::keyboard_layout >();

      //}

      return true;

   }


   //__pointer(::user::user) application::create_userex()
   //{

   //   return __new(::user::user);

   //}


   //i32 application::sync_message_box(::user::primitive * puiOwner, const char * pszMessage, UINT fuStyle)
   //{

   //   ::output_debug_string("\n\napp_message_box: " + string(pszMessage) + "\n\n");

   //   if (&Session == nullptr || Session.user() == nullptr)
   //      return ::base::application::sync_message_box(puiOwner, pszMessage, fuStyle);

   //   return User.message_box(puiOwner, pszMessage, fuStyle);

   //}


   //i32 application::sync_message_box_timeout(::user::primitive * pwndOwner, var var, ::duration durationTimeOut, UINT fuStyle)
   //{

   //   if (Session.user() == nullptr)
   //   {

   //      return ::base::application::sync_message_box_timeout(pwndOwner, var, durationTimeOut, fuStyle);

   //   }

   //   try
   //   {

   //      return User.message_box_timeout(pwndOwner, var, durationTimeOut, fuStyle, this);

   //   }
   //   catch (...)
   //   {

   //   }

   //   return ::base::application::sync_message_box_timeout(pwndOwner, var, durationTimeOut, fuStyle);

   //}







   //::user::document * application::hold(__pointer(::user::interaction) pinteraction)
   //{

   //   return Sess(this).user()->hold(pinteraction);

   //}



   //bool user::initialize1_userex()
   //{

   //   if (!m_puserex->init())
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init1())
   //   {

   //      return false;

   //   }

   //   if (!m_puserex->init2())
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   void user::on_file_manager_open(::filemanager::data * pdata, ::file::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      //m_pdocs->m_ptemplate_html->open_document_file(get_context_application(), itema[0]->get_user_path());

   }




   //void user::initialize_bergedge_application_interface()
   //{

   //   //      i32 iCount = 32; // todo: get from bergedge profile

   //   //m_pdocs->m_pnaturedocument = nullptr;

   //}


   void user::on_frame_window_drop_files(::user::interaction * pinteraction, ::file::patha & patha)
   {

      for (auto & path : patha)
      {

         __pointer(::create) pcreate(e_create);

         pcreate->m_pcommandline->m_varFile = path;

         do_request(pcreate);

      }

   }


   //::user::document * user::userex_on_request(::create * pcreate)
   //{

   //   user()->do_request(pcreate);

   //   return ::user::__document(pcreate);

   //}


   void user::will_use_view_hint(::id idView)
   {

      if (idView == FILEMANAGER_IMPACT)
      {

         if (m_mapimpactsystem[FILEMANAGER_IMPACT] != nullptr)
         {

            return;

         }

         m_mapimpactsystem[FILEMANAGER_IMPACT] = User.filemanager(idView)->m_pdocumenttemplate;

         //create_factory <::user::color_view >();

         //user()->m_mapimpactsystem[COLORSEL_IMPACT] = __new(::user::multiple_document_template(
         //   get_context_application(),
         //   "main",
         //   __type(::user::document),
         //   __type(::prodevian_translucent_simple_frame_window),
         //   __type(::user::color_view)));

         //add_document_template(user()->m_mapimpactsystem[COLORSEL_IMPACT]);

      }
      else if (idView == COLORSEL_IMPACT)
      {

         if (m_mapimpactsystem[COLORSEL_IMPACT] != nullptr)
         {

            return;

         }

         create_factory <::userex::color_view >();

         auto ptemplate = __new(::user::multiple_document_template(
                               "main",
                               __type(::user::document),
                               __type(::simple_frame_window),
                               __type(::userex::color_view)));

         Session.add_document_template(ptemplate);

         m_mapimpactsystem[COLORSEL_IMPACT] = ptemplate;

      }
      else if (idView == FONTSEL_IMPACT)
      {

         if (m_bFontSelInitialized)
         {

            return;

         }

         m_bFontSelInitialized = true;

         create_factory <::user::font_list >();
         create_factory <::user::font_list_view >();
         create_factory <::userex::font_view >();

         auto ptemplate = __new(::user::multiple_document_template(
                               "main",
                               __type(::user::document),
                               __type(::simple_frame_window),
                               __type(::userex::font_view)));

         Session.add_document_template(ptemplate);

         m_mapimpactsystem[FONTSEL_IMPACT] = ptemplate;

         System.draw2d().fonts();

         

         //fork([&]()
         //{
         //         System.draw2d().fonts().m_pfontenumeration->check_need_update();


         //});

      }

   }


   //::estatus application::message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, UINT uFlags, ::function_arg function)
   //{

   //   auto estatus = ui_message_box(puiOwner->get_safe_handle(), pszMessage, pszTitle, fuStyle, functionarg);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return os_message_box(this, puiOwner, pszMessage, pszTitle, fuStyle, functionarg);

   //}

   __namespace_object_factory(user, ::static_setup::flag_object_user);



} // namespace core


namespace user
{


   __pointer(::user::mesh_data) mesh::create_mesh_data()
   {

      return User.default_create_mesh_data(get_context_object());

   }

   __pointer(::user::list_header) list::create_list_header()
   {

      return User.default_create_list_header(get_context_object());

   }


   __pointer(::user::mesh_data) list::create_mesh_data()
   {

      return User.default_create_list_data(get_context_object());

   }


} // namespace user



