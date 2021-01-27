#include "framework.h"
#include "core/html/html/_html.h"
#include "core/html/impl/_impl.h"
#include "hi5_twitter_authorization.h"
#include "core/user/simple/_simple.h"
//#include "core/user/simple/_simple.h"

//#include <openssl/rsa.h>
//#include <openssl/engine.h>
//#include <openssl/err.h>


//typedef string ( *SALT)(__pointer(::aura::application), const char * , string_array &);

namespace hi5
{


   namespace twitter
   {


      authorization::authorization(::object * pobject, const char * pszAuthorizationUrl, const char * pszForm, bool bAuth, bool bInteractive) :
         ::object(pobject)
      {

         m_strAuthorizationUrl=pszAuthorizationUrl;
         m_bInteractive    = bInteractive;
         m_bAuth    = bAuth;
         m_strForm         = pszForm;
         m_ptemplatePane   = new ::user::single_document_template(
         "system/auth",
         __type(::user::document),
         __type(simple_frame_window),
         System.get_pane_tab_view_type_info());
         m_pviewAuth       = nullptr;
         m_pdocAuth        = nullptr;
         m_pdocument            = nullptr;
         m_ptabview        = nullptr;
      }

      authorization::~authorization()
      {
      }

      string authorization::get_pin()
      {
         ensure_main_document();
         page1();

         if(m_pviewAuth == nullptr)
            return "";

         m_pviewAuth->SetTimer(8888, 484, nullptr);
         //m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);

         m_ptabview->get_wnd()->RunModalLoop();


         m_ptemplatePane->close_all_documents(FALSE);
         return m_strPin;
      }

      void authorization::ensure_main_document()
      {

         if(m_pdocument != nullptr)
            return;

         __pointer(::create) pcreate(e_create);

         pcreate->m_bMakeVisible = false;
         pcreate->m_puserinteractionParent = System.cast < ::user::interaction >("top_parent");
         pcreate->m_bOuterPopupAlertLike = true;

         m_ptemplatePane->do_request(pcreate);

         m_pdocument = ::user::__document(pcreate);

         if(m_pdocument == nullptr)
            return;

         __pointer(user::tab_view) pview = m_pdocument->get_typed_view < user::tab_view >();
         m_ptabview = pview;
         pview->create_impact("twitter_authorization", "ca2open", this);
         pview->set_cur_tab_by_id("twitter_authorization");
      }


      void authorization::page1()
      {

         if(m_pdocAuth == nullptr)
            return;

         string strUrl;

         strUrl = "http://spaignition.api.server.ca2.cc/query?node=install_application&id=";

         string strAppName;

         if(Application.m_strAppName == "winactionarea")
         {

            strAppName = "_set_windesk";

         }
         else
         {

            strAppName = Application.m_strAppName;

         }

         strUrl += strAppName;

         strUrl += "&key=name";

         property_set set;

         property_set & setDoc = m_pdocAuth->form_document_property_set();

         setDoc["application_name"] = Context.http().get(strUrl,set);

         setDoc["authorization_link"] = m_strAuthorizationUrl;

         setDoc["ext_authorization_link"] ="ext://" + m_strAuthorizationUrl;
         if(m_strLicense.is_empty())
         {

            setDoc["reason"] = "Authenticating";

         }
         else
         {

            setDoc["reason"] = "Licensing";

         }

         if(!m_pdocAuth->on_open_document(Context.dir().matter(m_strForm)))
         {

            return;

         }

         //::html::matter * pelemental = m_pdocAuth->get_html_data()->get_element_by_id("authorization_link");

         //::html::impl::text * ptext = dynamic_cast < ::html::impl::text * > (pelemental->m_pimpl);

         ////__pointer(::user::interaction) ptext = m_pdocAuth->get_html_data()->get_child_by_id("authorization_link");

         //ptext->m_strLink = "ext://" + m_strAuthorizationUrl;

         //ptext->m_bLink = true;

         display_main_frame();

      }


      void authorization::display_main_frame()
      {

         ::rect rectOpen;

         m_ptabview->get_parent_frame()->best_top_level_parent(rectOpen);

         i32 iWidth = rectOpen.width();

         i32 iHeight = rectOpen.height();

         rectOpen.deflate(iWidth / 5, iHeight / 50);

         rectOpen.top = iHeight * 2 / 3;

         //__pointer(::user::frame_window) pframe = m_pviewAuth->get_parent_frame();

         //if(pframe != nullptr)
         //{

         //   pframe->m_puserstyle = this;

         //}

         m_ptabview->get_parent_frame()->order_front();

         m_ptabview->get_parent_frame()->place(rectOpen);

         m_pviewAuth->get_parent_frame()->SetForegroundWindow();

         m_ptabview->top_level_frame()->display(e_display_normal, e_activation_set_foreground);

      }


      void authorization::pageMessage(const char * pszMatter, property_set & set)
      {

         ensure_main_document();

         m_pdocAuth->get_form_data()->m_pimpl->get_property_set() = set;
         m_pdocAuth->on_open_document(Context.dir().matter(pszMatter));
         display_main_frame();
         //m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);

         m_ptabview->get_wnd()->RunModalLoop();

         m_ptabview->get_wnd()->EndModalLoop(e_dialog_result_ok);

      }


      void authorization::on_create_impact(::user::impact_data * pimpactdata)
      {

         if (pimpactdata->m_id == "twitter_authorization")
         {

            auto puser = User;

            m_pdocAuth = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);

            if (m_pdocAuth != nullptr)
            {

               m_pviewAuth = m_pdocAuth->get_typed_view < ::user::form >();
               m_pviewAuth->set_form_callback(this);
               pimpactdata->m_pdocument = m_pdocAuth;
               pimpactdata->m_puserinteraction = m_pviewAuth->get_parent_frame();

            }

         }
         if(pimpactdata->m_puserinteraction != nullptr)
         {
            pimpactdata->m_eflag.add(::user::e_flag_hide_all_others_on_show);
         }

      }
      void authorization::on_change_cur_sel()
      {
//         switch(get_view_id())
//         {
//         case 1:
//         {
//         }
//         break;
//
//         }
//
      }


      void authorization::on_control_event( ::user::control_event * pevent)
      {

         if(pevent->m_eevent == ::user::e_event_button_clicked || pevent->m_eevent == ::user::e_event_enter_key)
         {

            if(pevent->m_puie->m_id == "submit" || pevent->m_eevent == ::user::e_event_enter_key)
            {

               auto pinteraction = m_pviewAuth->get_child_by_name("pin");

               pinteraction->_001GetText(m_strPin);

               m_ptabview->get_wnd()->EndModalLoop(e_dialog_result_ok);

               m_ptabview->get_parent_frame()->display(e_display_none);

            }

         }

      }


      bool authorization::style_translucency(::user::enum_translucency & etranslucency, ::user::enum_element)
      {

         etranslucency = ::user::e_translucency_present;

         return true;

      }



   } // namespace twitter


} // namespace hi5




