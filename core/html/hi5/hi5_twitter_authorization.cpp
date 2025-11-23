#include "framework.h"
#include "hi5_twitter_authorization.h"
#include "acme/constant/id.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/networking/http/context.h"
#include "axis/user/form/data.h"
#include "berg/user/simple/frame_window.h"
#include "berg/user/user/single_document_template.h"
#include "berg/user/form/impact.h"
#include "berg/user/user/tab_impact.h"
#include "berg/user/form/document.h"
#include "core/platform/application.h"
#include "core/platform/session.h"
#include "core/platform/system.h"
#include "core/user/user/user.h"
////#include "core/user/simple/_component.h"

//#include <openssl/rsa.h>
//#include <openssl/engine.h>
//#include <openssl/err.h>


//typedef string ( *SALT)(::pointer<::aura::application> const ::string & , string_array_base &);

namespace hi5
{


   namespace twitter
   {


      authorization::authorization()
      {


         m_pviewAuth       = nullptr;
         m_pformdocumentAuth        = nullptr;
         m_pdocument            = nullptr;
         m_ptabimpact        = nullptr;
      }

      authorization::~authorization()
      {
      }


      void authorization::initialize_twitter_authorization(::object* pparticle, const ::scoped_string & scopedstrAuthorizationUrl, const ::scoped_string & scopedstrForm, bool bAuth, bool bInteractive)
      {

         // auto estatus = 
         
         ::object::initialize(pparticle);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         m_strAuthorizationUrl = scopedstrAuthorizationUrl;
         m_bInteractive = bInteractive;
         m_bAuth = bAuth;
         m_strForm = scopedstrForm;

         auto psystem = system();

         m_ptemplatePane = ___new ::user::single_document_template(
            "system/auth",
            ::as_type < ::user::document >(),
            ::as_type < simple_frame_window >(),
            psystem->get_pane_tab_impact_type_info());

         //return estatus;

      }


      string authorization::get_pin()
      {
         ensure_main_document();
         page1();

         if(m_pviewAuth == nullptr)
            return "";

         m_pviewAuth->set_timer(8888, 500_ms, nullptr);
         //m_ptabimpact->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);

         m_ptabimpact->get_wnd()->wait_for_dialog_result();


         m_ptemplatePane->close_all_documents(false);
         return m_strPin;
      }

      void authorization::ensure_main_document()
      {

         if (m_pdocument != nullptr)
         {

            return;

         }

         ::pointer<::request>prequest(e_create, this);

         auto psystem = system();

         prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;
         prequest->m_puserelementParent = psystem->cast < ::user::interaction >("top_parent");
         prequest->m_bOuterPopupAlertLike = true;

         m_ptemplatePane->request(prequest);

         m_pdocument = ::user::__document(prequest);

         if (m_pdocument == nullptr)
         {

            return;

         }

         ::pointer<user::tab_impact>ptabimpact = m_pdocument->get_typed_impact < user::tab_impact >();

         m_ptabimpact = ptabimpact;

         auto pimpactkit = ptabimpact->get_impact_kit();

         pimpactkit->add_impact_item("twitter_authorization", "ca2open", this);

         // pimpact->create_impact
         ptabimpact->set_current_tab_by_id("twitter_authorization");
      }


      void authorization::page1()
      {

         if(m_pformdocumentAuth == nullptr)
            return;

         string strUrl;

         strUrl = "http://spaignition.api.ca2.network/query?node=install_application&atom=";

         string strAppName;

         auto papp = get_app();

         if(papp->m_strAppName == "winactionarea")
         {

            strAppName = "_set_windesk";

         }
         else
         {

            strAppName = papp->m_strAppName;

         }

         strUrl += strAppName;

         strUrl += "&key=name";

         ::property_set set;

         ::property_set & setDoc = m_pformdocumentAuth->form_document_property_set();

         // auto pcontext = get_context();

         setDoc["application_name"] = http()->get(strUrl,set);

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

         if(!m_pformdocumentAuth->on_open_document(directory()->matter(m_strForm)))
         {

            return;

         }

         //::html::matter * pelemental = m_pformdocumentAuth->get_html_data()->get_element_by_id("authorization_link");

         //::html::impl::text * ptext = dynamic_cast < ::html::impl::text * > (pelemental->m_pimpl);

         ////::pointer<::user::interaction>ptext = m_pformdocumentAuth->get_html_data()->get_child_by_id("authorization_link");

         //ptext->m_strLink = "ext://" + m_strAuthorizationUrl;

         //ptext->m_bLink = true;

         display_main_frame();

      }


      void authorization::display_main_frame()
      {

         ::int_rectangle rectangleOpen;

         m_ptabimpact->parent_frame()->best_top_level_parent(rectangleOpen);

         int iWidth = rectangleOpen.width();

         int iHeight = rectangleOpen.height();

         rectangleOpen.deflate(iWidth / 5, iHeight / 50);

         rectangleOpen.top() = iHeight * 2 / 3;

         //::pointer<::user::frame_window>pframe = m_pviewAuth->get_parent_frame();

         //if(pframe != nullptr)
         //{

         //   pframe->m_puserstyle = this;

         //}

         m_ptabimpact->parent_frame()->order_front();

         m_ptabimpact->parent_frame()->place(rectangleOpen);

         m_pviewAuth->parent_frame()->set_foreground_window(nullptr);

         m_ptabimpact->top_level_frame()->display(e_display_normal, { ::user::e_activation_set_foreground });

      }


      void authorization::pageMessage(const ::scoped_string & scopedstrMatter, ::property_set & set)
      {

         ensure_main_document();

         m_pformdocumentAuth->get_form_data()->m_pimpl->property_set() = set;

         // auto pcontext = get_context();

         m_pformdocumentAuth->on_open_document(directory()->matter(scopedstrMatter));
         display_main_frame();
         //m_ptabimpact->get_wnd()->RunModalLoop(MLF_NOIDLEMSG | MLF_NOKICKIDLE);

         m_ptabimpact->get_wnd()->wait_for_dialog_result();

         m_ptabimpact->get_wnd()->set_dialog_result(e_dialog_result_ok);

      }


      void authorization::on_create_impact(::user::impact_data * pimpactdata)
      {

         if (pimpactdata->id() == "twitter_authorization")
         {

            auto pcontext = m_papplication;
            
            auto psession = pcontext->m_psession;
            
            auto puser = psession->m_puser;

            m_pformdocumentAuth = puser->create_child_form(this, nullptr, this, pimpactdata->m_pplaceholder);

            if (m_pformdocumentAuth != nullptr)
            {

               m_pviewAuth = m_pformdocumentAuth->get_typed_impact < ::user::form >();
               m_pviewAuth->set_form_callback(this);
               pimpactdata->m_pdocument = m_pformdocumentAuth;
               pimpactdata->m_puserinteraction = m_pviewAuth->parent_frame();

            }

         }
         if(pimpactdata->m_puserinteraction != nullptr)
         {
            pimpactdata->m_eflag.add(::user::e_flag_hide_all_others_on_show);
         }

      }
      void authorization::on_change_cur_sel()
      {
//         switch(get_impact_id())
//         {
//         case 1:
//         {
//         }
//         break;
//
//         }
//
      }


      void authorization::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         if(ptopic->id() == ::id_click || ptopic->id() == ::id_enter_key)
         {

            if(ptopic->user_interaction()->id() == "submit" || ptopic->id() == ::id_enter_key)
            {

               auto pinteraction = m_pviewAuth->get_child_by_name("pin");

               m_strPin = pinteraction->as_text();

               m_ptabimpact->get_wnd()->set_dialog_result(e_dialog_result_ok);

               m_ptabimpact->parent_frame()->display(e_display_none);

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




