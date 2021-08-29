#include "framework.h"
#include "core/user/userex/_userex.h"
#include "core/user/account/_account.h"
#include "acme/platform/static_setup.h"
#include "aura/update.h"
#include "aqua/xml.h"
#include "aura/user/shell.h"
#include "core/user/user/_tree.h"


//void __html_initialize(::user::user * puserex);
//::type get_html_document_type();

//#ifdef WINDOWS_DESKTOP
//#include <Commdlg.h>
//#endif


#define new ACME_NEW


//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_CORE void attach_thread_input_to_main_thread(bool bAttach);
//#endif

//#ifdef MACOS
//
//bool macos_set_user_wallpaper(int iScreen, const ::string & psz);
//
////long long mm_get_user_wallpaper(long long llScreen, char ** ppp);
////
////CLASS_DECL_CORE string macos_get_user_wallpaper(int iScreen)
////{
////
////   string str;
////
////   char * psz = nullptr;
////
////   mm_get_user_wallpaper(iScreen, &psz);
////
////   if(psz != nullptr)
////   {
////
////      str = psz;
////
////      free(psz);
////
////   }
////
////   return str;
////
////}
////
//#endif

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


   ::e_status user::initialize(::object * pobject)
   {

      auto estatus = ::base::user::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status user::init1()
   {

      create_factory < ::user::picture::picture_impl >();

      //create_factory <::userex::keyboard_layout >();

      create_factory <::userex::top_edit_view >();
      create_factory <::userex::top_toggle_view >();
      create_factory <::userex::top_view >();

      create_factory <::user::tab_view >();

      create_factory < ::user::form_view > ();

      create_factory < simple_pane_document >();


      //if (!create_user_shell())
      //{

      //   WARN("Failed to create_user_shell");

      //   return false;

      //}


      if (!::base::user::init1())
      {

         return false;

      }

      //if (!initialize1_experience())
      //{

      //   return false;

      //}

      //m_phtml->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      //if(m_phtml == nullptr)
      //   return false;

      //m_phtml->construct(this);

      //m_bProcessInitializeResult = true;

      return true;

   }


   ::e_status user::init()
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

      create_factory < ::account::impact >();

      create_factory < form_document >();
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

      auto psystem = m_psystem->m_paurasystem;

      auto typeinfo = psystem->get_simple_frame_window_type_info();

      auto ptemplate = __new(::user::multiple_document_template(
         "system/form",
         __type(form_document),
         psystem->get_simple_frame_window_type_info(),
         __type(::user::form_view)));

      ptemplate->initialize(this);

      m_ptemplateForm = ptemplate;


      add_document_template(ptemplate);

      ptemplate = __new(::user::multiple_document_template(
         "system/form",
         __type(form_document),
         get_simple_child_frame_type_info(),
         __type(::user::form_view)));

      ptemplate->initialize(this);

      m_ptemplateChildForm = ptemplate;

      add_document_template(m_ptemplateChildForm);

      ptemplate = __new(::user::multiple_document_template(
            "system/form",
            __type(::user::document),
         psystem->get_simple_frame_window_type_info(),
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

      auto pxml = psystem->xml();

      auto pdocumentUser = pxml->create_document();

      auto pcontext = get_context();

      string strUser = pcontext->m_papexcontext->file().as_string(pcontext->m_papexcontext->dir().appdata() / "langstyle_settings.xml");

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

      //auto papplication = get_se();

      //if (strLangUser.has_char())
      //{

      //   psession->set_locale(strLangUser, ::e_source_database);

      //}

      //if (strStyleUser.has_char())
      //{

      //   psession->set_schema(strStyleUser, ::e_source_database);

      //}

      //string strLicense = papplication->get_license_id();


      //::payload & varTopicQuey = psystem->m_varTopicQuery;

//      bool bHasInstall = psystem->has_property("install");
//
//      bool bHasUninstall = psystem->has_property("uninstall");
//
//      if (!(bHasInstall || bHasUninstall)
//            && papplication->m_bLicense
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
//         if (!psession->is_licensed(strLicense))
//         {
//
//            //psession->licensing().m_mapInfo.erase_key(strLicense);
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

      //set_data_server(papplication->dataserver());


      create_factory <::userex::pane_tab_view >();
      create_factory <form_frame >();
      create_factory <form_child_frame >();

      create_factory <simple_toolbar >();
      create_factory <simple_toolbar, ::user::toolbar >();
      create_factory <::experience::orto_button >();

      estatus = initialize_filemanager_component(this);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::e_status user::init2()
   {

      if (!::acme::department::init2())
      {

         return false;

      }

      return true;

   }


   ::e_status user::destroy()
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

         ::acme::department::term();

      }
      catch (...)
      {

      }

      return ::success;

   }


   ::type user::controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {

      return ::type();

   }



   ::e_status user::term()
   {

      return ::success;

   }




   __pointer(::form_document) user::create_form(::object * pobject, ::type type, __pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
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

         document_manager()->add_document_template(psystem);

      }

      if (pobject == nullptr)
      {

         if (puserinteractionParent.is_set())
         {

            pobject = puserinteractionParent;

         }
         else
         {

            pobject = this;

         }

      }

      __pointer(::create) pcreate(e_create);

      pcreate->m_bMakeVisible = true;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->m_varArgs = varArgs;

      if (payload.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = payload.get_file_path();

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


   __pointer(::extended::future < ::conversation >) user::dialog_box(::object * pobject, const ::string & pszMatter, property_set & propertyset)
   {

      auto pbox = pobject->__create_new < class ::userex::message_box >();

      //auto pfuture = pbox->::extended::asynchronous< ::future<::conversation > >::future();

      auto pfuture = pbox->::extended::asynchronous< ::conversation >::future();

      // todo add property set to list;
      pbox->get_property_set().merge(propertyset);

      //r

      if (!pbox->show(pszMatter))
      {

         pfuture->set_status(::error_failed);

         return pfuture;

      }

      //process_subject(pbox->m_idResponse);

      return pfuture;

   }


   __pointer(::extended::future < ::conversation >) user::ui_message_box(::object * pobject, ::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox)
   {

      auto pbox = pobject->__create_new < ::userex::message_box >();

      auto pfuture = pbox->::extended::asynchronous< ::conversation >::future();

      property_set & propertyset = pbox->get_property_set();

      propertyset["message"] = pszMessage;

      //pbox->add_process(DIALOG_RESULT_PROCESS, process);

      auto psession = get_session();

      auto papplication = pobject->get_application();

      if (::is_set(puiOwner))
      {

         propertyset["application_name"] = papplication->m_strAppName;

      }
      else if (::is_set(psession->m_papplicationCurrent))
      {

         string strAppName = psession->m_papplicationCurrent->m_strAppName;

         propertyset["application_name"] = strAppName;

      }

      string strMatter;

      auto emessageboxType = emessagebox & e_message_box_type_mask;

      if(emessageboxType == e_message_box_yes_no_cancel)
      {

         strMatter = "system\\user\\message_box\\yesnocancel.xhtml";

      }
      else if (emessageboxType == e_message_box_yes_no)
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

            //return ::message_box(puserinteractionOwner->get_safe_handle(),strMessage,papplication->m_strAppName,fuStyle, functionargResult);

            pfuture->set_status(::error_failed);

            return pfuture;

         }

      }
      catch(...)
      {

         pfuture->set_status(::error_exception);

         return pfuture;
         //string strMessage = pszMessage;

         //strMessage.replace("<br>","\r\n");

         //return ::message_box(puserinteractionOwner == nullptr ? nullptr : puserinteractionOwner->get_handle(),strMessage,papplication->m_strAppName,fuStyle, functionargResult);

      }

      //return 0;

      return pfuture;

      //if(pbox->m_idResponse == "ok")
      //{

      //   return e_dialog_result_ok;

      //}
      //else if(pbox->m_idResponse == "yes")
      //{

      //   return e_dialog_result_yes;

      //}
      //else if(pbox->m_idResponse == "no")
      //{

      //   return e_dialog_result_no;

      //}
      //else if(pbox->m_idResponse == "cancel")
      //{

      //   return e_dialog_result_cancel;

      //}

      //if(fuStyle & MB_YESNOCANCEL)
      //{

      //   return e_dialog_result_cancel;

      //}
      //else
      //{

      //   return 0;

      //}

   }


   __pointer(::extended::future < ::conversation >) user::ui_message_box_timeout(::object * pobject, ::user::primitive * puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox)
   {

      UNREFERENCED_PARAMETER(puiOwner);

      auto pbox = pobject->__create_new < ::userex::message_box >();

      auto pfuture = pbox->::extended::asynchronous< ::conversation >::future();

      pbox->payload("message") = pszMessage;

      //pbox->add_process(DIALOG_RESULT_PROCESS, process);

      auto papplication = pobject->get_application();

      string strTitle = papplication->get_title();

      pbox->payload("application_name") = strTitle;

      pbox->m_millisDelay = durationTimeout;

      string strMatter;

      auto emessageboxType = emessagebox & e_message_box_type_mask;

      if (emessageboxType == e_message_box_yes_no_cancel)
      {

         strMatter = "system\\user\\message_box_timeout\\yesnocancel.xhtml";

      }
      else
      {

         strMatter = "system\\user\\message_box_timeout\\ok.xhtml";

      }

      if (!pbox->show(strMatter))
      {

         pfuture->set_status(::error_failed);

         return pfuture;

      }

      return pfuture;

   }


   i32 user::track_popup_menu(const ::string & pszMatter, const ::point_i32 & point, __pointer(::user::interaction) puie)
   {

      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(puie);

      return 1;

   }


   bool user::get_fs_size(string & strSize, const ::string & pszPath, bool & bPending)
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


   bool user::get_fs_size(i64 & i64Size, const ::string & pszPath, bool & bPending)
   {

      //db_server * pcentral = dynamic_cast <db_server *> (psystem->m_psimpledb->db());

      //if (pcentral == nullptr)
      //{

      //   return false;

      //}

      //return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);

      return false;

   }


   void user::data_on_after_change(::message::message * pmessage)
   {

      __pointer(::database::change_event) pchange(pmessage);

      if (pchange->m_datakey == "ca2.savings")
      {

         auto psession = get_session();

         CHANGE_EVENT_DATA_GET(pchange, (::i32 &) psession->m_paurasession->savings().m_eresourceflagsShouldSave.m_eenum);

      }

   }


   bool user::modal_get_color(::user::interaction * puiOwner, ::color::hls & hls)
   {

#ifdef WINDOWS_DESKTOP

      //CHOOSECOLOR cc;
      //::color::color crCustColors[16];

      //// init-int this array did not affect the mouse problem
      //// ::u32 idx ;
      //// for (idx=0; idx<16; idx++) {
      //// crCustColors[idx] = rgb(idx, idx, idx) ;
      //// }

      //::color::color color(hls);

      //ZeroMemory(&cc, sizeof(cc));
      //cc.lStructSize = sizeof(CHOOSECOLOR);
      //cc.rgbResult = c.get_rgb();
      //cc.lpCustColors = (COLORREF*) crCustColors;

      //cc.Flags = CC_RGBINIT | CC_FULLOPEN;
      //cc.hwndOwner = puiOwner->get_safe_handle(); // this hangs parent, as well as me

      //if (::ChooseColor(&cc))
      //{

      //   c.set_COLORREF(cc.rgbResult | (255 << 24));

      //   c.get_hls(hls);

      //   return true;

      //}

      return false;

#else

      will_use_view_hint(COLORSEL_IMPACT);

      auto pdocument = m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(puiOwner->get_application(), ::e_type_null, __visible(true));

      __pointer(::userex::color_view) pview = pdocument->get_typed_view < ::userex::color_view >();

      __pointer(::user::frame_window) pframe = pview->top_level_frame();

      pframe->set_owner(puiOwner);

      pframe->_001RunModalLoop();

      hls = pview->m_hls;

      return true;

#endif


   }


   void  user::AddToRecentFileList(const ::string & pszPathName)

   {

      UNREFERENCED_PARAMETER(pszPathName);


   }


   void user::_001OnFileNew()
   {
      
      auto papplication = get_application();
      
      ASSERT(papplication->document_manager() != nullptr);

      if (papplication->document_manager() == nullptr)
      {

         return;

      }

      papplication->document_manager()->_001OnFileNew();

   }


   ::e_status user::term_instance()
   {

      return ::success;

   }


   __pointer(::form_document) user::create_form(::object * pobject, __pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
   {

      if (m_ptemplateForm == nullptr)
      {

         return nullptr;

      }

      __pointer(::create) pcreate(e_create);

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->m_puserprimitiveAlloc = pview;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (payload.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = payload.get_file_path();

      }

      if (payload.get_type() == ::e_type_property_set && payload.has_property("hold") && payload["hold"].is_false())
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


   __pointer(::form_document) user::create_form(::object * pobject, ::user::form_callback * pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
   {

      auto ptemplateForm = m_ptemplateForm;

      //::aura::application * papp = ::get_application(pobject);

      //if (papp == nullptr)
      //{

      //   if (puserinteractionParent.is_set())
      //   {

      //      papp = puserinteractionParent->get_application();

      //   }
      //   else if (pcallback != nullptr)
      //   {

      //      papp = pcallback->get_application();

      //   }
      //   else
      //   {

      //      papp = get_application();

      //   }

      //}

      auto pcreate = pobject->__create_new < ::create >();

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (payload.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = payload.get_file_path();

         string strPath = payload.get_file_path();

      }

      if (payload.get_type() == ::e_type_property_set && payload.has_property("hold") && payload["hold"].is_false())
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


   __pointer(::form_document) user::create_child_form(::object * pobject, __pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
   {

      if (m_ptemplateChildForm == nullptr)
      {

         return nullptr;

      }

      auto papplication = pobject->get_application();

      if (papplication == nullptr)
      {

         if (puserinteractionParent.is_set())
         {

            papplication = puserinteractionParent->get_application();

         }
         else if (pcallback != nullptr)
         {

            papplication = pcallback->get_application();

         }
         else
         {

            papplication = get_application();

         }

      }

      auto pcreate = __create_new< ::create >();

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->m_puserprimitiveAlloc = pview;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (payload.get_file_path().has_char())
      {

         pcreate->m_pcommandline.defer_create(this);

         pcreate->m_pcommandline->m_varFile = payload.get_file_path();

      }

      if (payload.get_type() == ::e_type_property_set && payload.has_property("hold") && payload["hold"].is_false())
      {

         pcreate->m_bHold = false;

      }

      pcreate->finish_initialization();

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


   __pointer(::form_document) user::create_child_form(::object * pobject, ::user::form_callback * pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
   {

      auto papplication = pobject->get_application();

      if (papplication == nullptr)
      {

         if (puserinteractionParent.is_set())
         {

            papplication = puserinteractionParent->get_application();

         }
         else if (pcallback != nullptr)
         {

            papplication = pcallback->get_application();

         }
         else
         {

            papplication = get_application();

         }

      }

      auto pcreate = pobject->__create_new < ::create > ();

      pcreate->m_bMakeVisible = true;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->m_varArgs = varArgs;

      pcreate->m_varArgs["form_callback"] = pcallback;

      if (payload.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         ::file::path path = payload.get_file_path();

         pcreate->m_pcommandline->m_varFile = path;

      }

      pcreate->finish_initialization();

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

      return string(file_path_final_extension(strFilePath)).compare_ci("htm") == 0;

   }


   __pointer(::form_document) user::create_child_form(::object * pobject, ::type type, __pointer(::user::interaction) puserinteractionParent, ::payload payload, ::payload varArgs)
   {

      if (!type)
      {

         return nullptr;

      }

      ::user::impact_system * psystem = m_mapTemplate[type];

      if (psystem == nullptr)
      {

         ::type typeDocument = m_ptemplateChildForm->m_typeDocument;

         if (is_html_file(payload.get_file_path()))
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

         if (puserinteractionParent.is_set())
         {

            pobject = puserinteractionParent;

         }
         else
         {

            pobject = this;

         }

      }

      auto pcreate = pobject->__create_new < ::create >();

      pcreate->m_bMakeVisible = false;

      pcreate->m_puserprimitiveParent = puserinteractionParent;

      pcreate->m_varArgs = varArgs;

      if (payload.get_file_path().has_char())
      {

         pcreate->m_pcommandline.create(this);

         pcreate->m_pcommandline->m_varFile = payload.get_file_path();

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


   void user::route_command_message(::message::command * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   __pointer(::user::list_header) user::default_create_list_header(::object * pobject)
   {

      return pobject->__id_create < ::user::list_header > (default_type_list_header());

   }


   __pointer(::user::mesh_data) user::default_create_mesh_data(::object * pobject)
   {

      return pobject->__id_create < ::user::mesh_data > (default_type_list_data());

   }


   __pointer(::user::list_data) user::default_create_list_data(::object * pobject)
   {

      return pobject->__id_create <::user::list_data >(default_type_list_data());

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


   //string user::os_get_user_theme()
   //{

   //   return impl_get_os_desktop_theme();

   //}


   //bool user::set_os_desktop_theme(string strTheme)
   //{

   //   return impl_set_os_desktop_theme(strTheme);

   //}


   //string user::get_wallpaper(index iScreen)
   //{

   //   return impl_get_wallpaper(iScreen);

   //}


   //bool user::set_wallpaper(index iScreen, string strWallpaper)
   //{

   //   return impl_set_wallpaper(iScreen, strWallpaper);

   //}



#ifdef WINDOWS_DESKTOP


   //void user::enable_wallpaper_change_notification()
   //{

   //}


   //bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   //{

   //   return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != false;

   //}


   //string user::impl_get_wallpaper(index iScreen)
   //{

   //   wstring  wstr;

   //   wstr.get_string_buffer(MAX_PATH * 8);
   //   //::u32 uLen = pwsz.memsize();

   //   if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, (::u32)wstr.get_storage_length(), wstr.m_pdata, 0))
   //   {
   //      return "";

   //   }
   //   wstr.release_string_buffer();

   //   return wstr;

   //}


   //string user::impl_get_os_desktop_theme()
   //{

   //   return "";

   //}


   //bool user::impl_set_os_desktop_theme(string strTheme)
   //{

   //   UNREFERENCED_PARAMETER(strTheme);

   //   return true;

   //}


#elif defined(LINUX)


//   bool user::impl_set_os_desktop_theme(string strTheme)
//   {
//
//      auto pnode = Node;
//
//      return pnode->os_set_user_theme(strTheme);
//
//   }


//   string user::impl_get_os_desktop_theme()
//   {
//
//      return ::user::os_get_user_theme();
//
//   }


//   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
//   {
//
//      // wall-changer sourceforge.net contribution
//
//      auto pnode = Node;
//
//      if(::is_null(pnode))
//      {
//
//         return false;
//
//      }
//
//      return pnode->set_wallpaper(iScreen, strLocalImagePath);
//
//   }


//   string user::impl_get_wallpaper(index iScreen)
//   {
//
//      return ::os::get_wallpaper(iScreen);
//
//   }
//
//
//   void user::enable_wallpaper_change_notification()
//   {
//
//      auto pnode = Node;
//
//      if(pnode)
//      {
//
//         pnode->enable_wallpaper_change_notification();
//
//      }
//
//   }


#elif defined(APPLE_IOS)

//   bool user::impl_set_os_desktop_theme(string strTheme)
//   {
//
//      return false;
//
//   }
//
//   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
//   {
//
//      return false;
//
//   }
//
//   string user::impl_get_wallpaper(index iScreen)
//   {
//
//      return string();
//
//   }
//
//   string user::impl_get_os_desktop_theme()
//   {
//
//      return "";
//
//   }

//   void user::enable_wallpaper_change_notification()
//   {
//
//   }


#elif defined(ANDROID)

//   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
//   {
//
//      return psystem->android_set_user_wallpaper(strLocalImagePath);
//
//   }
//
//   string user::impl_get_wallpaper(index iScreen)
//   {
//
//      string strLocalImagePath;
//
//      psystem->android_get_user_wallpaper(strLocalImagePath);
//
//      return strLocalImagePath;
//
//   }

//   void user::enable_wallpaper_change_notification()
//   {
//
//   }


//   string user::impl_get_os_desktop_theme()
//   {
//
//      return "";
//
//   }
//
//
//   bool user::impl_set_os_desktop_theme(string strTheme)
//   {
//
//      UNREFERENCED_PARAMETER(strTheme);
//
//      return true;
//
//   }



#elif defined(_UWP)


//   void user::enable_wallpaper_change_notification()
//   {
//
//   }


//   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
//   {
//
//      // Someday we will be together...
//      // What do you mean...
//      // Cold Water...
//
//      return false;
//
//   }
//
//   string user::impl_get_wallpaper(index iScreen)
//   {
//
//      return string();
//
//   }
//
//   string user::impl_get_os_desktop_theme()
//   {
//
//      return "";
//
//   }
//
//
//   bool user::impl_set_os_desktop_theme(string strTheme)
//   {
//
//      UNREFERENCED_PARAMETER(strTheme);
//
//      return true;
//
//   }

#else

//
//   void user::enable_wallpaper_change_notification()
//   {
//
//   }

//   bool user::impl_set_wallpaper(index iScreen, string strLocalImagePath)
//   {
//
//      return macos_set_user_wallpaper((int)iScreen, strLocalImagePath);
//
//   }
//
//   string user::impl_get_wallpaper(index iScreen)
//   {
//
//      return macos_get_user_wallpaper((int)iScreen);
//
//   }
//
//
//
//
//
//   string user::impl_get_os_desktop_theme()
//   {
//
//      return "";
//
//   }
//
//
//   bool user::impl_set_os_desktop_theme(string strTheme)
//   {
//
//      UNREFERENCED_PARAMETER(strTheme);
//
//      return true;
//
//   }


#endif



} //namespace user



namespace core
{


   ::e_status user::initialize_userex()
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


   //i32 application::sync_message_box(::user::primitive * puiOwner, const ::string & pszMessage, ::u32 fuStyle)
   //{

   //   ::output_debug_string("\n\napp_message_box: " + string(pszMessage) + "\n\n");

   //   if (&Session == nullptr || psession->user() == nullptr)
   //      return ::base::application::sync_message_box(puiOwner, pszMessage, fuStyle);

   //   return puser->message_box(puiOwner, pszMessage, fuStyle);

   //}


   //i32 application::sync_message_box_timeout(::user::primitive * puserinteractionOwner, ::payload payload, ::duration durationTimeOut, ::u32 fuStyle)
   //{

   //   if (psession->user() == nullptr)
   //   {

   //      return ::base::application::sync_message_box_timeout(puserinteractionOwner, payload, durationTimeOut, fuStyle);

   //   }

   //   try
   //   {

   //      return puser->message_box_timeout(puserinteractionOwner, payload, durationTimeOut, fuStyle, this);

   //   }
   //   catch (...)
   //   {

   //   }

   //   return ::base::application::sync_message_box_timeout(puserinteractionOwner, payload, durationTimeOut, fuStyle);

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

      //m_pdocs->m_ptemplate_html->open_document_file(get_application(), itema[0]->get_user_path());

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

         m_mapimpactsystem[FILEMANAGER_IMPACT] = filemanager(idView)->m_pdocumenttemplate;

         //create_factory <::user::color_view >();

         //user()->m_mapimpactsystem[COLORSEL_IMPACT] = __new(::user::multiple_document_template(
         //   get_application(),
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

         auto psession = get_session();

         psession->add_document_template(ptemplate);

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

         auto psession = get_session();

         psession->add_document_template(ptemplate);

         m_mapimpactsystem[FONTSEL_IMPACT] = ptemplate;

         //auto psystem = m_psystem->m_paurasystem;

         //auto pdraw2d = psystem->draw2d();

         //pdraw2d->write_text()->fonts();



         //fork([&]()
         //{
         //         pdraw2d->fonts().m_pfontenumeration->check_need_update();


         //});

      }

   }


   //::e_status application::message_box(::user::primitive* puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 uFlags, ::function_arg function)
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

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_paurasession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      return puser->default_create_mesh_data(this);

   }


   __pointer(::user::list_header) list::create_list_header()
   {

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_paurasession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      return puser->default_create_list_header(this);

   }


   __pointer(::user::mesh_data) list::create_mesh_data()
   {

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_paurasession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      return puser->default_create_list_data(this);

   }


} // namespace user



