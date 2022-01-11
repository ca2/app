#include "framework.h"
#include "core/html/html/_html.h"
#include "core/html/impl/_impl.h"
#if !BROAD_PRECOMPILED_HEADER
#include "hi5_twitter_authorization.h"
#include "core/user/simple/_simple.h"
#endif
//#include "core/user/simple/_simple.h"

//#include <openssl/rsa.h>
//#include <openssl/engine.h>
//#include <openssl/err.h>


//typedef string ( *SALT)(__pointer(::aura::application), const ::string & , string_array &);

namespace hi5
{


   namespace twitter
   {


      authorization::authorization()
      {


         m_pviewAuth       = nullptr;
         m_pdocAuth        = nullptr;
         m_pdocument            = nullptr;
         m_ptabview        = nullptr;
      }

      authorization::~authorization()
      {
      }


      void authorization::initialize_twitter_authorization(::object* pobject, const ::string & pszAuthorizationUrl, const ::string & pszForm, bool bAuth, bool bInteractive)
      {

         auto estatus = ::object::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

         m_strAuthorizationUrl = pszAuthorizationUrl;
         m_bInteractive = bInteractive;
         m_bAuth = bAuth;
         m_strForm = pszForm;

         auto psystem = get_system()->m_pcoresystem;

         m_ptemplatePane = new ::user::single_document_template(
            "system/auth",
            __type(::user::document),
            __type(simple_frame_window),
            psystem->get_pane_tab_view_type_info());

         return estatus;

      }


      string authorization::get_pin()
      {
         ensure_main_document();
         page1();

         if(m_pviewAuth == nullptr)
            return "";

         m_pviewAuth->SetTimer(8888, 500_ms, nullptr);
         //m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);

         m_ptabview->get_wnd()->RunModalLoop();


         m_ptemplatePane->close_all_documents(false);
         return m_strPin;
      }

      void authorization::ensure_main_document()
      {

         if (m_pdocument != nullptr)
         {

            return;

         }

         __pointer(::create) pcreate(e_create, this);

         auto psystem = m_psystem->m_paurasystem;

         pcreate->m_bMakeVisible = false;
         pcreate->m_puserprimitiveParent = psystem->cast < ::user::interaction >("top_parent");
         pcreate->m_bOuterPopupAlertLike = true;

         m_ptemplatePane->do_request(pcreate);

         m_pdocument = ::user::__document(pcreate);

         if(m_pdocument == nullptr)
            return;

         __pointer(user::tab_view) pview = m_pdocument->get_typed_view < user::tab_view >();
         m_ptabview = pview;
         pview->create_impact("twitter_authorization", "ca2open", this);
         pview->set_current_tab_by_id("twitter_authorization");
      }


      void authorization::page1()
      {

         if(m_pdocAuth == nullptr)
            return;

         string strUrl;

         strUrl = "http://spaignition.api.server.ca2.software/query?node=install_application&id=";

         string strAppName;

         auto papplication = get_application();

         if(papplication->m_strAppName == "winactionarea")
         {

            strAppName = "_set_windesk";

         }
         else
         {

            strAppName = papplication->m_strAppName;

         }

         strUrl += strAppName;

         strUrl += "&key=name";

         property_set set;

         property_set & setDoc = m_pdocAuth->form_document_property_set();

         auto pcontext = get_context();

         setDoc["application_name"] = pcontext->m_papexcontext->http().get(strUrl,set);

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

         if(!m_pdocAuth->on_open_document(pcontext->m_papexcontext->dir().matter(m_strForm)))
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

         ::rectangle_i32 rectangleOpen;

         m_ptabview->get_parent_frame()->best_top_level_parent(rectangleOpen);

         i32 iWidth = rectangleOpen.width();

         i32 iHeight = rectangleOpen.height();

         rectangleOpen.deflate(iWidth / 5, iHeight / 50);

         rectangleOpen.top = iHeight * 2 / 3;

         //__pointer(::user::frame_window) pframe = m_pviewAuth->get_parent_frame();

         //if(pframe != nullptr)
         //{

         //   pframe->m_puserstyle = this;

         //}

         m_ptabview->get_parent_frame()->order_front();

         m_ptabview->get_parent_frame()->place(rectangleOpen);

         m_pviewAuth->get_parent_frame()->set_foreground_window();

         m_ptabview->top_level_frame()->display(e_display_normal, e_activation_set_foreground);

      }


      void authorization::pageMessage(const ::string & pszMatter, property_set & set)
      {

         ensure_main_document();

         m_pdocAuth->get_form_data()->m_pimpl->get_property_set() = set;

         auto pcontext = get_context();

         m_pdocAuth->on_open_document(pcontext->m_papexcontext->dir().matter(pszMatter));
         display_main_frame();
         //m_ptabview->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);

         m_ptabview->get_wnd()->RunModalLoop();

         m_ptabview->get_wnd()->EndModalLoop(e_dialog_result_ok);

      }


      void authorization::on_create_impact(::user::impact_data * pimpactdata)
      {

         if (pimpactdata->m_id == "twitter_authorization")
         {

            auto pcontext = m_pcontext;
            
            auto psession = pcontext->m_pcoresession;
            
            auto puser = psession->m_puser->m_pcoreuser;

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


      void authorization::handle(::subject * psubject, ::context *pcontext)   
      {

         if(psubject->m_id == ::e_subject_click || psubject->m_id == ::e_subject_enter_key)
         {

            if(psubject->user_interaction()->m_id == "submit" || psubject->m_id == ::e_subject_enter_key)
            {

               auto pinteraction = m_pviewAuth->get_child_by_name("pin");

               pinteraction->_001GetText(m_strPin);

               m_ptabview->get_wnd()->EndModalLoop(e_dialog_result_ok);

               m_ptabview->get_parent_frame()->display(e_display_none);

            }

         }

      }


      bool authorization::style_translucency(::user::enum_translucency & etranslucency, ::enum_element)
      {

         etranslucency = ::user::e_translucency_present;

         return true;

      }



   } // namespace twitter


} // namespace hi5




