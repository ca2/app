#include "framework.h"
#include "font_list.h"
#include "tree.h"
#include "user.h"
#include "font_combo_box.h"
#include "acme/handler/item.h"
#include "acme/platform/system_setup.h"
#include "apex/database/_binary_stream.h"
#include "apex/database/change_event.h"
#include "acme/handler/request.h"
#include "apex/platform/node.h"
#include "acme/prototype/data/tree_item.h"
//#include "apex/platform/os_context.h"

#include "apex/platform/savings.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/write_text/fonts.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/progress.h"
#include "aura/user/user/shell.h"
#include "aura/user/user/still.h"
#include "axis/html/html/html.h"
#include "axis/user/user/line_layout.h"
#include "base/user/user/picture.h"
#include "base/user/user/multiple_document_template.h"
#include "base/user/user/document_manager.h"
#include "base/user/form/document.h"
#include "base/user/form/impact.h"
#include "base/user/experience/orto_button.h"
#include "base/user/simple/child_frame.h"
#include "base/user/simple/toolbar.h"
#include "core/filesystem/filemanager/data.h"
#include "core/filesystem/filemanager/document.h"
#include "core/filesystem/filemanager/frame.h"
#include "core/filesystem/filemanager/impact.h"
#include "core/platform/application.h"
#include "core/platform/session.h"
#include "core/user/account/impact.h"
#include "core/user/rich_text/data.h"
#include "core/user/simple/list_data.h"
#include "core/user/simple/list_header_control.h"
#include "core/user/simple/list_impact.h"
#include "core/user/simple/mesh_data.h"
#include "core/user/simple/pane_document.h"
#include "core/user/simple/printer_list_impact.h"
#include "core/user/user/font_list_impact.h"
#include "core/user/user/color_selector_impact.h"
#include "core/user/userex/dialog_frame.h"
#include "core/user/userex/font_impact.h"
#include "core/user/userex/form_child_frame.h"
#include "core/user/userex/menu_document.h"
#include "core/user/userex/menu_frame.h"
//#include "core/user/userex/menu_impact.h"
#include "core/user/userex/pane_tab_impact.h"
#include "core/user/userex/progress.h"
#include "core/user/userex/split_impact.h"
#include "core/user/userex/top_impact.h"
#include "core/user/userex/top_toggle_impact.h"
#include "core/user/userex/top_edit_impact.h"


//void __html_initialize(::user::user * puserex);
//::type get_html_document_type();

//#ifdef WINDOWS_DESKTOP
//#include <Commdlg.h>
//#endif


//#if defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
//#include <stdio.h>
//#endif


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

CLASS_DECL_CORE::pointer< ::mutex > get_cred_mutex();


namespace core
{


   /* class user_static_factory
    {
    public:

       user_static_factory()
       {

          add_factory_item < user, ::user::user >();

       }

    };

    user_static_factory g_userstaticfactory;*/

   user::user()
   {

      print_line("core::user::user");

      m_pcoreuser = this;
      //m_ptemplateForm = nullptr;
      //m_ptemplateChildForm = nullptr;
      //m_ptemplatePlaceHolder = nullptr;
      //m_ptemplateHtmlChildForm1 = nullptr;

   }


   user::~user()
   {

   }



   ::core::application * user::get_app()
   {

      auto papplication = application();

      return ::is_set(papplication) ? papplication->m_pcoreapplication : nullptr;

   }


   ::core::session * user::get_session()
   {

      auto pacmesession = session();

      return ::is_set(pacmesession) ? pacmesession->m_pcoresession : nullptr;

   }


   ::core::system * user::get_system()
   {

      auto pacmesystem = system();

      return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

   }


   void user::initialize(::particle * pparticle)
   {

      //auto estatus =

      print_line("core::user::initialize\n");

      ::base::user::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void user::init1()
   {


      ::base::user::init1();

      factory()->add_factory_item < ::user::picture::picture_impl >();

      factory()->add_factory_item <::userex::top_edit_impact >();
      factory()->add_factory_item <::userex::top_toggle_impact >();
      factory()->add_factory_item <::userex::top_impact >();

      factory()->add_factory_item < ::user::font_combo_box >();

      factory()->add_factory_item < simple_pane_document >();
      factory()->add_factory_item < simple_frame_window  >();


      factory()->add_factory_item < ::simple_toolbar, ::user::toolbar >();


      factory()->add_factory_item < ::simple_toolbar >();

      factory()->add_factory_item < ::user::rich_text::data >();

      factory()->add_factory_item <::userex::dialog_frame >();



   }


   void user::init()
   {

      ::base::user::init();

      //if (!::base::user::init())
      //{

      //   return ::error_failed;

      //}

      if (!m_typeatomDefaultMeshData)
      {

         m_typeatomDefaultMeshData = ::type < ::simple_mesh_data >();

      }

      if (!m_typeatomDefaultListData)
      {

         m_typeatomDefaultListData = ::type < ::simple_list_data >();

      }

      if (!m_typeatomDefaultListHeader)
      {

         m_typeatomDefaultListHeader = ::type < ::simple_list_header_control >();

         auto strAtomDefaultListHeader = m_typeatomDefaultListHeader.as_string();

         information() << "m_typeatomDefaultListHeader : " << strAtomDefaultListHeader;

      }


      factory()->add_factory_item < ::html::html >();
      factory()->add_factory_item < int_biunique  >();
      factory()->add_factory_item <::user::plain_edit >();
      factory()->add_factory_item <::user::place_holder >();
      factory()->add_factory_item <::user::combo_box >();
      factory()->add_factory_item <::user::check_box >();
      factory()->add_factory_item <::user::place_holder_container >();

      factory()->add_factory_item < ::account::impact >();

      factory()->add_factory_item < ::userex::split_impact  >();

      factory()->add_factory_item < ::simple_mesh_data  >();
      factory()->add_factory_item < ::simple_list_data  >();
      factory()->add_factory_item < ::simple_list_header_control  >();

      factory()->add_factory_item <::user::tree >();


      factory()->add_factory_item <simple_list_impact >();
      factory()->add_factory_item <::user::document >();
      factory()->add_factory_item <simple_printer_list_impact >();



      factory()->add_factory_item <::user::show < ::user::plain_edit > >();
      factory()->add_factory_item <::user::show < ::user::tree > >();
      factory()->add_factory_item <::user::show < ::user::list > >();

      factory()->add_factory_item <menu_document >();
      factory()->add_factory_item <menu_frame >();
      //factory()->add_factory_item <menu_impact >();

      auto psystem = system()->m_paurasystem;

      auto typeinfo = psystem->get_simple_frame_window_type_info();

      add_impact_system(
         "system/form", ::place(new ::user::multiple_document_template(
         "system/form",
         ::type < form_document >(),
         psystem->get_simple_frame_window_type_info(),
         ::type < ::user::form_impact >())));

      //ptemplate->initialize(this);

      //m_ptemplateForm = ptemplate;


      //add_document_template(ptemplate);
      //add_impact_system(
      //   "system/form_child",
      //   ::place(new ::user::multiple_document_template(
      //   "system/form",
      //   ::type < form_document >(),
      //   get_simple_child_frame_type_info(),
      //   ::type < ::user::form_impact >())));

      //ptemplate->initialize(this);

     // m_ptemplateChildForm = ptemplate;

      //add_document_template(m_ptemplateChildForm);
      add_impact_system(
         "system/form_placeholder", ::place(new ::user::multiple_document_template(
         "system/form",
         ::type < ::user::document >(),
         psystem->get_simple_frame_window_type_info(),
         ::type < ::user::place_holder >())));

      //ptemplate->initialize(this);

      //m_ptemplatePlaceHolder = ptemplate;

      //add_document_template(ptemplate);

      add_impact_system(
         "progress_impact", ::place(new ::user::multiple_document_template(
         "main",
         ::type < ::user::document >(),
         ::type < ::userex::dialog_frame >(),
         ::type < ::userex::progress_impact >())));

      //m_ptemplateProgress2 = pmultitemplate;

      //add_document_template(pmultitemplate);

      //auto estatus = 

      initialize_html();

      //if (!estatus)
      //{

      //   //m_result.add(estatus);

      //   error() <<"Failed to initialize html";

      //   return estatus;

      //}

      //estatus = 

      __construct(m_phtml);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      informationf("::user::application::initialize");

      //      auto pxml = psystem->xml();
      //
      //      auto pdocumentUser = pxml->create_document();
      //
      //      auto pcontext = get_context();
      //
      //      string strUser = file()->as_string(dir()->appdata() / "langstyle_settings.xml");
      //
      //      string strLangUser;
      //
      //      string strStyleUser;
      //
      //      if (pdocumentUser->load(strUser))
      //      {
      //
      //         if (pdocumentUser->get_child("lang") != nullptr)
      //         {
      //
      //            strLangUser = pdocumentUser->get_child("lang")->get_value();
      //
      //         }
      //
      //         if (pdocumentUser->get_child("style") != nullptr)
      //         {
      //
      //            strStyleUser = pdocumentUser->get_child("style")->get_value();
      //
      //         }
      //
      //      }

            //auto papp = get_se();

            //if (strLangUser.has_char())
            //{

            //   psession->set_locale(strLangUser, ::e_source_database);

            //}

            //if (strStyleUser.has_char())
            //{

            //   psession->set_schema(strStyleUser, ::e_source_database);

            //}

            //string strLicense = papp->get_license_id();


            //::payload & varTopicQuey = psystem->m_varTopicQuery;

      //      bool bHasInstall = psystem->has_property("install");
      //
      //      bool bHasUninstall = psystem->has_property("uninstall");
      //
      //      if (!(bHasInstall || bHasUninstall)
      //            && papp->m_bLicense
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

            //set_data_server(papp->dataserver());


      factory()->add_factory_item <::userex::pane_tab_impact >();
      factory()->add_factory_item <form_frame >();
      factory()->add_factory_item <form_child_frame >();

      factory()->add_factory_item <::experience::orto_button >();

      //estatus = 

      //initialize_filemanager_component(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   void user::init2()
   {

      ::base::user::init2();

      //if (!::acme::department::init2())
      //{

      //   return false;

      //}

      //return true;

   }


   void user::destroy()
   {

      try
      {

         m_pshell.release();

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

      //return ::success;

   }


   ::type_atom user::controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {

      return {};

   }


   void user::term()
   {

      //return ::success;

   }


   pointer< ::sequence < ::conversation > > user::dialog_box(::particle * pparticle, const ::string & pszMatter, property_set & propertyset)
   {

      return nullptr;
      //auto pbox = pparticle->__create_new < class ::userex::message_box >();

      ////auto pfuture = pbox->::extended::asynchronous< ::future<::conversation > >::future();

      //auto psequence = pbox->sequence();

      //// todo add property set to list;
      //pbox->get_property_set().merge(propertyset);

      ////r

      //if (!pbox->show(pszMatter))
      //{

      //   //pfuture->set_status(::error_failed);

      //   return psequence;

      //}

      ////process_subject(pbox->m_atomResponse);

      //return psequence;

   }


   pointer< ::sequence < ::conversation > > user::ui_message_box(::particle * pparticle, ::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox)
   {

      return nullptr;

      //auto pbox = pparticle->__create_new < ::userex::message_box >();

      //auto pfuture = pbox->::extended::asynchronous< ::conversation >::sequence();

      //property_set & propertyset = pbox->get_property_set();

      //propertyset["message"] = pszMessage;

      ////pbox->add_process(DIALOG_RESULT_PROCESS, process);

      //auto psession = get_session();

      //auto papp = pparticle->get_app();

      //if (::is_set(puiOwner))
      //{

      //   propertyset["application_name"] = papp->m_strAppName;

      //}
      //else if (::is_set(psession->m_pappCurrent))
      //{

      //   string strAppName = psession->m_pappCurrent->m_strAppName;

      //   propertyset["application_name"] = strAppName;

      //}

      //string strMatter;

      //auto emessageboxType = emessagebox & e_message_box_type_mask;

      //if(emessageboxType == e_message_box_yes_no_cancel)
      //{

      //   strMatter = "system\\user\\message_box\\yesnocancel.xhtml";

      //}
      //else if (emessageboxType == e_message_box_yes_no)
      //{

      //   strMatter = "system\\user\\message_box\\yesno.xhtml";

      //}
      //else
      //{

      //   strMatter = "system\\user\\message_box\\ok.xhtml";

      //}

      //try
      //{

      //   if(!pbox->show(strMatter))
      //   {
      //      // commented 2020-06-28 03:32
      //      //string strMessage = pszMessage;

      //      //strMessage.replace("<br>","\r\n");

      //      //return ::message_box(puserinteractionOwner->get_safe_handle(),strMessage,papp->m_strAppName,fuStyle, functionargResult);

      //      pfuture->set_status(::error_failed);

      //      return pfuture;

      //   }

      //}
      //catch(...)
      //{

      //   pfuture->set_status(::error_exception);

      //   return pfuture;
      //   //string strMessage = pszMessage;

      //   //strMessage.replace("<br>","\r\n");

      //   //return ::message_box(puserinteractionOwner == nullptr ? nullptr : puserinteractionOwner->get_handle(),strMessage,papp->m_strAppName,fuStyle, functionargResult);

      //}

      ////return 0;

      //return pfuture;

      ////if(pbox->m_atomResponse == "ok")
      ////{

      ////   return e_dialog_result_ok;

      ////}
      ////else if(pbox->m_atomResponse == "yes")
      ////{

      ////   return e_dialog_result_yes;

      ////}
      ////else if(pbox->m_atomResponse == "no")
      ////{

      ////   return e_dialog_result_no;

      ////}
      ////else if(pbox->m_atomResponse == "cancel")
      ////{

      ////   return e_dialog_result_cancel;

      ////}

      ////if(fuStyle & MB_YESNOCANCEL)
      ////{

      ////   return e_dialog_result_cancel;

      ////}
      ////else
      ////{

      ////   return 0;

      ////}

   }


   pointer< ::sequence < ::conversation > > user::ui_message_box_timeout(::particle * pparticle, ::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle, const class time & timeTimeout, const ::e_message_box & emessagebox)
   {

      //__UNREFERENCED_PARAMETER(puiOwner);

      //auto pbox = pparticle->__create_new < ::userex::message_box >();

      //auto pfuture = pbox->::extended::asynchronous< ::conversation >::sequence();

      //pbox->payload("message") = pszMessage;

      ////pbox->add_process(DIALOG_RESULT_PROCESS, process);

      //auto papp = pparticle->get_app();

      //string strTitle = papp->title();

      //pbox->payload("application_name") = strTitle;

      //pbox->m_timeDelay = timeTimeout;

      //string strMatter;

      //auto emessageboxType = emessagebox & e_message_box_type_mask;

      //if (emessageboxType == e_message_box_yes_no_cancel)
      //{

      //   strMatter = "system\\user\\message_box_timeout\\yesnocancel.xhtml";

      //}
      //else
      //{

      //   strMatter = "system\\user\\message_box_timeout\\ok.xhtml";

      //}

      //if (!pbox->show(strMatter))
      //{

      //   pfuture->set_status(::error_failed);

      //   return pfuture;

      //}

      //return pfuture;

      return nullptr;

   }

//
//   i32 user::track_popup_menu(const ::string & pszMatter, const ::point_i32 & point, ::pointer<::user::interaction>puie)
//   {
//
//      //__UNREFERENCED_PARAMETER(pszMatter);
//      //__UNREFERENCED_PARAMETER(point);
//      //__UNREFERENCED_PARAMETER(puie);
//
//      return ::bred::user::track_popup_menu(pszMatter, point, puie);
//
//   }


   bool user::get_fs_size(string & strSize, const ::string & pszPath, bool & bPending)
   {

      i64 i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.formatf("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.formatf("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.formatf("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.formatf("1 KB");

      }
      else
      {

         strSize.formatf("0 KB");

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

      ::pointer<::database::change_event>pchange(pmessage);

      if (pchange->m_strDataKey == "ca2.savings")
      {

         auto psession = get_session();

         CHANGE_EVENT_DATA_GET(pchange, (::i32 &)psession->m_paurasession->savings().m_eresourceflagsShouldSave.m_eenum);

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
      //cc.lpCustColors = (::color::color*) crCustColors;

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

      will_use_impact_hint(COLORSEL_IMPACT);

      auto pdocument = impact_system(COLORSEL_IMPACT)->open_document_file(puiOwner->get_app(), ::e_type_null, true);

      ::pointer<::user::color_selector_impact>pimpact = pdocument->get_typed_impact < ::user::color_selector_impact >();

      ::pointer<::user::frame_window>pframe = pimpact->top_level_frame();

      pframe->set_owner(puiOwner);

      pframe->_001RunModalLoop();

      hls = pimpact->m_hls;

      return true;

#endif


   }


   void  user::AddToRecentFileList(const ::string & pszPathName)

   {

      __UNREFERENCED_PARAMETER(pszPathName);


   }


   void user::_001OnFileNew()
   {

      auto papp = get_app();

      ASSERT(papp->document_manager() != nullptr);

      if (papp->document_manager() == nullptr)
      {

         return;

      }

      papp->document_manager()->_001OnFileNew();

   }


   void user::term_instance()
   {

      //return ::success;

   }


   //::pointer<::form_document>user::create_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>puserinteractionParent, ::payload payload, ::payload varArgs)
   //{

   //   auto ptemplateForm = m_ptemplateForm;

   //   //::aura::application * papp = ::get_app(pparticle);

   //   //if (papp == nullptr)
   //   //{

   //   //   if (puserinteractionParent.is_set())
   //   //   {

   //   //      papp = puserinteractionParent->get_app();

   //   //   }
   //   //   else if (pcallback != nullptr)
   //   //   {

   //   //      papp = pcallback->get_app();

   //   //   }
   //   //   else
   //   //   {

   //   //      papp = get_app();

   //   //   }

   //   //}

   //   auto prequest = ::__create_new < ::request >(pparticle);

   //   prequest->m_bMakeVisible = false;

   //   prequest->m_puserelementParent = puserinteractionParent;

   //   prequest->m_payloadArguments = varArgs;

   //   prequest->m_payloadArguments["form_callback"] = pcallback;

   //   auto pathFile = payload.as_file_path();

   //   if (pathFile.has_char())
   //   {

   //      prequest->m_payloadFile = pathFile;

   //   }

   //   if (payload.get_type() == ::e_type_property_set && payload.has_property("hold") && payload["hold"].is_false())
   //   {

   //      prequest->m_bHold = false;

   //   }

   //   ptemplateForm->request(prequest);

   //   ::pointer<::form_document>pformdocument = ::user::__document(prequest);

   //   if (pformdocument.is_null())
   //   {

   //      return nullptr;

   //   }

   //   ::pointer<::user::form_window>pform = pformdocument->get_typed_impact < ::user::form_window >();

   //   if (pform.is_set() && ::is_null(pform->get_form_callback()))
   //   {

   //      pform->set_form_callback(pcallback);

   //   }

   //   return pformdocument;

   //}




   //::pointer<::form_document>user::create_child_form(::particle * pparticle, ::user::form_callback * pcallback, ::pointer<::user::interaction>puserinteractionParent, ::payload payload, ::payload varArgs)
   //{

   //   auto papp = pparticle->application();

   //   if (papp == nullptr)
   //   {

   //      if (puserinteractionParent.is_set())
   //      {

   //         papp = puserinteractionParent->get_app();

   //      }
   //      else if (pcallback != nullptr)
   //      {

   //         papp = pcallback->get_app();

   //      }
   //      else
   //      {

   //         papp = get_app();

   //      }

   //   }

   //   auto prequest = ::__create_new < ::request > (pparticle);

   //   prequest->m_bMakeVisible = true;

   //   prequest->m_puserelementParent = puserinteractionParent;

   //   prequest->m_payloadArguments = varArgs;

   //   prequest->m_payloadArguments["form_callback"] = pcallback;

   //   auto pathFile = payload.as_file_path();

   //   if (pathFile.has_char())
   //   {

   //      prequest->m_payloadFile = pathFile;

   //   }

   //   prequest->finish_initialization();

   //   m_ptemplateChildForm->request(prequest);

   //   ::pointer<::form_document>pformdocument = ::user::__document(prequest);

   //   if (pformdocument.is_null())
   //   {

   //      return nullptr;

   //   }

   //   ::pointer<::user::form_window>pform = pformdocument->get_typed_impact < ::user::form_window >();

   //   if (pform.is_set() && ::is_set(pcallback))
   //   {

   //      pform->set_form_callback(pcallback);

   //   }

   //   return pformdocument;

   //}


   ::user::document * user::hold(::pointer<::user::interaction>pinteraction)
   {

      ::pointer<::request>prequest(e_create_new, pinteraction.m_p);

      prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

      prequest->m_bHold = false;

      impact_system("place_holder")->request(prequest);

      ::pointer<::form_document>pformdocument = ::user::__document(prequest);

      ::pointer<::user::place_holder>pholder = pformdocument->get_typed_impact < ::user::place_holder  >();

      pholder->place_hold(pinteraction);

      return pformdocument;

   }


   void user::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      __UNREFERENCED_PARAMETER(pcommand);

   }


   ::pointer<::user::list_header>user::default_create_list_header(::particle * pparticle)
   {

      auto typeListHeader = default_type_list_header();

      information() << "default_create_list_header : " << typeListHeader.as_string();

      return pparticle->__id_create < ::user::list_header >(typeListHeader);

   }


   ::pointer<::user::mesh_data>user::default_create_mesh_data(::particle * pparticle)
   {

      return pparticle->__id_create < ::user::mesh_data >(default_type_list_data());

   }


   ::pointer<::user::list_data>user::default_create_list_data(::particle * pparticle)
   {

      return pparticle->__id_create <::user::list_data >(default_type_list_data());

   }


   ::type_atom user::default_type_mesh_data()
   {

      return m_typeatomDefaultMeshData;

   }


   ::type_atom user::default_type_list_header()
   {

      return m_typeatomDefaultListHeader;

   }


   ::type_atom user::default_type_list_data()
   {

      return m_typeatomDefaultListData;

   }


   //string user::os_get_user_theme()
   //{

   //   return impl_get_os_desktop_theme();

   //}


   //bool user::set_os_desktop_theme(string strTheme)
   //{

   //   return impl_set_os_desktop_theme(strTheme);

   //}


   //string user::get_wallpaper(::collection::index iScreen)
   //{

   //   return impl_get_wallpaper(iScreen);

   //}


   //bool user::set_wallpaper(::collection::index iScreen, string strWallpaper)
   //{

   //   return impl_set_wallpaper(iScreen, strWallpaper);

   //}



#ifdef WINDOWS_DESKTOP


   //void user::enable_wallpaper_change_notification()
   //{

   //}


   //bool user::impl_set_wallpaper(::collection::index iScreen, string strLocalImagePath)
   //{

   //   return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != false;

   //}


   //string user::impl_get_wallpaper(::collection::index iScreen)
   //{

   //   wstring  wstr;

   //   wstr.get_buffer(MAX_PATH * 8);
   //   //::u32 uLen = pwsz.memsize();

   //   if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, (::u32)wstr.get_storage_length(), wstr.m_pdata, 0))
   //   {
   //      return "";

   //   }
   //   wstr.release_buffer();

   //   return wstr;

   //}


   //string user::impl_get_os_desktop_theme()
   //{

   //   return "";

   //}


   //bool user::impl_set_os_desktop_theme(string strTheme)
   //{

   //   __UNREFERENCED_PARAMETER(strTheme);

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


//   bool user::impl_set_wallpaper(::collection::index iScreen, string strLocalImagePath)
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


//   string user::impl_get_wallpaper(::collection::index iScreen)
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
//   bool user::impl_set_wallpaper(::collection::index iScreen, string strLocalImagePath)
//   {
//
//      return false;
//
//   }
//
//   string user::impl_get_wallpaper(::collection::index iScreen)
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

//   bool user::impl_set_wallpaper(::collection::index iScreen, string strLocalImagePath)
//   {
//
//      return psystem->android_set_user_wallpaper(strLocalImagePath);
//
//   }
//
//   string user::impl_get_wallpaper(::collection::index iScreen)
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
//      __UNREFERENCED_PARAMETER(strTheme);
//
//      return true;
//
//   }



#elif defined(UNIVERSAL_WINDOWS)


//   void user::enable_wallpaper_change_notification()
//   {
//
//   }


//   bool user::impl_set_wallpaper(::collection::index iScreen, string strLocalImagePath)
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
//   string user::impl_get_wallpaper(::collection::index iScreen)
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
//      __UNREFERENCED_PARAMETER(strTheme);
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

//   bool user::impl_set_wallpaper(::collection::index iScreen, string strLocalImagePath)
//   {
//
//      return macos_set_user_wallpaper((int)iScreen, strLocalImagePath);
//
//   }
//
//   string user::impl_get_wallpaper(::collection::index iScreen)
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
//      __UNREFERENCED_PARAMETER(strTheme);
//
//      return true;
//
//   }


#endif



} //namespace core



namespace core
{


   void user::initialize_userex()
   {

      ////if (is_system())
      //{

      //   add_factory_item <::user::keyboard_layout >();

      //}

      //return true;

   }


   //::pointer<::user::user>application::create_userex()
   //{

   //   return ::place(new ::user::user());

   //}


   //i32 application::sync_message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, ::u32 fuStyle)
   //{

   //   ::acme::get()->platform()->informationf("\n\napp_message_box: " + string(pszMessage) + "\n\n");

   //   if (&Session == nullptr || psession->user() == nullptr)
   //      return ::base::application::sync_message_box(puiOwner, pszMessage, fuStyle);

   //   return puser->message_box(puiOwner, pszMessage, fuStyle);

   //}


   //i32 application::sync_message_box_timeout(::user::interaction_base * puserinteractionOwner, ::payload payload, ::time timeTimeOut, ::u32 fuStyle)
   //{

   //   if (psession->user() == nullptr)
   //   {

   //      return ::base::application::sync_message_box_timeout(puserinteractionOwner, payload, timeTimeOut, fuStyle);

   //   }

   //   try
   //   {

   //      return puser->message_box_timeout(puserinteractionOwner, payload, timeTimeOut, fuStyle, this);

   //   }
   //   catch (...)
   //   {

   //   }

   //   return ::base::application::sync_message_box_timeout(puserinteractionOwner, payload, timeTimeOut, fuStyle);

   //}







   //::user::document * application::hold(::pointer<::user::interaction>pinteraction)
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

      __UNREFERENCED_PARAMETER(pdata);

      //m_pdocs->m_ptemplate_html->open_document_file(get_app(), itema[0]->get_user_path());

   }




   //void user::initialize_bergedge_application_interface()
   //{

   //   //      i32 iCount = 32; // todo: get from bergedge profile

   //   //m_pdocs->m_pnaturedocument = nullptr;

   //}


   void user::on_frame_window_drop_files(::user::interaction * pinteraction, ::file::path_array & patha)
   {

      for (auto & path : patha)
      {

         ::pointer<::request>prequest(e_create, this);

         prequest->m_payloadFile = path;

         request(prequest);

      }

   }


   //::user::document * user::userex_on_request(::request * prequest)
   //{

   //   user()->do_request(pcreate);

   //   return ::user::__document(pcreate);

   //}


   void user::will_use_impact_hint(::atom idImpact)
   {

      if (idImpact == FILEMANAGER_IMPACT)
      {

         if (impact_system(FILEMANAGER_IMPACT) != nullptr)
         {

            return;

         }


         application()->m_pcoreapplication->filemanager();

         //if (::is_null(user()->impact_system("filemanager_filemanager")))
         {

            //m_pimpactsystemFileManager = 
            add_impact_system(
               FILEMANAGER_IMPACT, ::place(new ::user::multiple_document_template(
                  "filemanager",
                  ::type < ::filemanager::document >(),
                  ::type < ::filemanager::frame >(),
                  ::type < ::filemanager::impact >())));
            //::type < main_impact >()));

         //auto psession = get_session();

         //psession->add_document_template(m_pimpactsystemFileManager);

         }



         //m_mapimpactsystem[FILEMANAGER_IMPACT] = filemanager(idImpact)->m_pimpactsystem;

         //add_factory_item <::user::color_impact >();

   //      add_impact_system(
   //COLORSEL_IMPACT, ::place(new ::user::multiple_document_template(
   //   "main",
   //   ::type < ::user::document >(),
   //   ::type < ::simple_frame_window >(),
   //   ::type < ::user::color_selector_impact >())));


         //user()->m_mapimpactsystem[COLORSEL_IMPACT] = ::place(new ::user::multiple_document_template(
         //   get_app(),
         //   "main",
         //   ::type < ::user::document >(),
         //   ::type < ::prodevian_translucent_simple_frame_window >(),
         //   ::type < ::user::color_impact >())));

         //add_document_template(user()->m_mapimpactsystem[COLORSEL_IMPACT]);

      }
      else if (idImpact == COLORSEL_IMPACT)
      {

         if (impact_system(COLORSEL_IMPACT) != nullptr)
         {

            return;

         }

         factory()->add_factory_item <::user::color_selector_impact >();

         add_impact_system(
            COLORSEL_IMPACT, ::place(new ::user::multiple_document_template(
            "main",
            ::type < ::user::document >(),
            ::type < ::simple_frame_window >(),
            ::type < ::user::color_selector_impact >())));

         //auto psession = get_session();

         //psession->add_document_template(ptemplate);

         //m_mapimpactsystem[COLORSEL_IMPACT] = ptemplate;

      }
      else if (idImpact == FONTSEL_IMPACT)
      {

         if (m_bFontSelInitialized)
         {

            return;

         }

         m_bFontSelInitialized = true;

         factory()->add_factory_item <::user::font_list >();
         factory()->add_factory_item <::user::font_list_impact >();
         factory()->add_factory_item <::userex::font_impact >();

         add_impact_system(
            FONTSEL_IMPACT, ::place(new ::user::multiple_document_template(
            "main",
            ::type < ::user::document >(),
            ::type < ::simple_frame_window >(),
            ::type < ::userex::font_impact >())));

         //auto psession = get_session();

         //psession->add_document_template(ptemplate);

         //m_mapimpactsystem[FONTSEL_IMPACT] = ptemplate;

         fork([this]()
         {

            auto psystem = system()->m_paurasystem;

            auto pdraw2d = psystem->draw2d();

            auto pfonts = pdraw2d->write_text()->fonts();

            pfonts->enumerate_fonts("system");

         });

      }

   }


   //void application::message_box(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 uFlags, ::function_arg function)
   //{

   //   auto estatus = ui_message_box(puiOwner->get_safe_handle(), pszMessage, pszTitle, fuStyle, functionarg);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return message_box_synchronous(this, puiOwner, pszMessage, pszTitle, fuStyle, functionarg);

   //}

   __namespace_object_factory(user, ::system_setup::flag_object_user);



} // namespace userex


namespace user
{


   ::pointer<::user::mesh_data>mesh::create_mesh_data()
   {

      return user()->m_pcoreuser->default_create_mesh_data(this);

   }


   ::pointer<::user::list_header>list::create_list_header()
   {

      return user()->m_pcoreuser->default_create_list_header(this);

   }


   ::pointer<::user::mesh_data>list::create_mesh_data()
   {

      return user()->m_pcoreuser->default_create_list_data(this);

   }






} // namespace user



