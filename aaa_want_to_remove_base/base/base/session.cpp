#include "framework.h"



namespace base
{


   session::session()
   {

      create_factory < ::user::user >();
      create_factory < ::base::session, ::aura::session >();

   }


   session::~session()
   {


   }


   ::estatus session::initialize(::object * pobjectContext)
   {

      auto estatus = ::aura::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }


      //m_strAppId = "base_session";
      //m_strAppName = "base_session";
      //m_strBaseSupportId = "base_session";
      //m_strInstallToken = "base_session";

      m_iMainMonitor = -1;

      m_puiCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_ecursorDefault = cursor_arrow;

      m_ecursor = cursor_default;

      m_puiMouseMoveCapture = nullptr;

      m_psavings = __new(class ::aura::savings(this));

      m_pcopydesk = nullptr;

      return estatus;

   }


   ::estatus session::process_init()
   {
      
      //m_himc = ImmCreateContext();

      INFO(".1");

      if (!::aura::session::process_init())
      {

         ERR(".2");

         return false;

      }

      //if (!::base::application::process_init())
      //{

      //   ERR(".3");

      //   return false;

      //}

      //m_puser = create_user();

      //if (m_puser == nullptr)
      //{

      //   ERR(".4");

      //   return false;

      //}

      //m_puser->add_ref(OBJ_REF_DBG_ARGS);

      auto estatus = __construct(m_puser);

      if (!estatus || !m_puser)
      {

         ERR(".4");

         return false;

      }

      INFO("end");

      return true;

   }


   ::estatus session::init1()
   {


      if (!::aura::session::init1())
         return false;

      //if (!::base::application::init1())
        // return false;

      //if (m_puserstyle.is_null())
      //{
      //
      //   defer_create_user_style(preferred_experience());
      //
      //}

      if (!m_puser->init1())
         return false;

      if (!m_puser->init2())
         return false;


      return true;

   }


   ::estatus session::init()
   {

      if (!::aura::session::init())
      {

         return false;

      }

      //if (!::base::application::init())
      //{

      //   return false;

      //}

      if (!m_puser->init())
      {

         return false;

      }

      ::set_message_box(&::simple_ui_message_box);

      return true;

   }


   void session::term_session()
   {

      //::base::application::term_application();

      ::aura::session::term_session();

      try
      {

         m_puser->term();

      }
      catch (...)
      {

      }


      m_puser.release();

   }




   bool session::prepare_menu_button(::user::menu_item * pitem)
   {

      __pointer(::user::button) pbutton = pitem->m_puserinteraction;

      if (pbutton->m_id == "close_menu")
      {

         pbutton->m_econtroltype = ::user::control_type_menu_button_close;

         pbutton->set_stock_icon(stock_icon_close);

         pbutton->resize_to_fit();

         return true;

      }
      else
      {

         pbutton->m_econtroltype = ::user::control_type_menu_button;

         int cx = pbutton->width();

         int cy = pbutton->height();

         pbutton->m_pmenuitemThis = pitem;

         ::rect rectMargin = pbutton->_001GetRect(::user::rect_menu_margin);

         int iCheckBoxSize = pbutton->_001GetInt(::user::int_check_box_size);

         int iElementPadding = pbutton->_001GetInt(::user::int_element_padding);

         auto & rectCheckBox = pbutton->m_rectCheckBox;

         rectCheckBox.left = rectMargin.left;
         rectCheckBox.top = rectMargin.top;
         rectCheckBox.bottom = cy - rectMargin.bottom;
         rectCheckBox.right = rectCheckBox.left + iCheckBoxSize;

         auto & rectText = pbutton->m_rectText;

         rectText.left = rectCheckBox.right + iElementPadding;
         rectText.top = rectMargin.top;
         rectText.bottom = cy - rectMargin.bottom;
         rectText.right = cx - rectMargin.right;

      }

      return true;

   }



   void session::frame_pre_translate_message(::message::message * pmessage)
   {

      if (pmessage->m_id == WM_GETTEXT
         || pmessage->m_id == WM_GETTEXTLENGTH
         )
      {

         pmessage->m_uiMessageFlags |= 3; // message considered pre translated
         pmessage->m_uiMessageFlags |= 16384; //  by early optmization

         return;

      }
      //else if (pmessage->m_id == WM_MOUSEMOVE)
      //{

      //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
      //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

      //   return;

      //}

      //try
      //{

      //   __pointer(::user::interaction) pinteraction;

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
      //      catch (exception_pointer e)
      //      {

      //         if (e.is < ::exit_exception>())
      //         {

      //            __rethrow(::move(e));

      //         }

      //      }
      //      catch (...)
      //      {
      //      }

      //   }

      //}
      //catch (exception_pointer e)
      //{

      //   if (e.is < ::exit_exception>())
      //   {

      //      __rethrow(::move(e));

      //   }

      //}
      //catch (...)
      //{

      //   pmessage->m_bRet = true;

      //}

   }


   void session::interactive_credentials(::account::credentials * pcredentials)
   {

      ::aura::session::interactive_credentials(pcredentials);

      if (pcredentials->m_estatus == ::success_credentials)
      {

         return;

      }

      if (!pcredentials->m_bInteractive)
      {

         pcredentials->m_estatus = error_credentials_non_interactive;

         return;

      }

      auto puser = pcredentials->m_puser;

      auto pdialog = ::__create_new<::account::dialog>();

      pdialog->initialize_account_dialog(pcredentials);

      pdialog->get_credentials();

      pdialog->DestroyWindow();

   }


   __pointer(::user::impact) session::get_view()
   {

      return nullptr;

   }


   void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText)

   {

      __throw(interface_only_exception());

   }


   void session::on_finally_focus_set(::user::primitive * pelementalFocus)
   {

      user()->set_mouse_focus_LButtonDown(pelementalFocus);

      aura::session::on_finally_focus_set(pelementalFocus);

   }


   bool session::on_ui_mouse_message(::message::mouse * pmouse)
   {

      ::aura::session::on_ui_mouse_message(pmouse);

      if(m_puserpresence.is_set())
      {

         m_puserpresence->on_ui_mouse_message(pmouse);

      }

      return true;

   }


} // namespace base



