#include "framework.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/handler/topic.h"
#include "aqua/xml/document.h"
#include "base/user/user/document.h"
#include "base/user/form/impact.h"
#include "base/user/form/document.h"
#include "core/user/netuser/_netuser.h"
#include "core/user/user/user.h"
#include "core/platform/session.h"


namespace usernet
{


   network_configuration::network_configuration()
   {

      m_pdocument   = nullptr;
      m_pimpact  = nullptr;

   }


   network_configuration::~network_configuration()
   {
   }


   bool network_configuration::initialize(::pointer<::user::interaction>puiParent)
   {

      auto pcontext = m_papplication;
      
      auto psession = pcontext->m_psession->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      m_pdocument = puser->create_form(this, nullptr, this, puiParent);

      if(m_pdocument != nullptr)
      {

         m_pimpact = m_pdocument->get_typed_impact < ::user::form > ();

         m_pimpact->set_form_callback(this);

         return true;

      }

      return false;

   }


   bool network_configuration::initialize_child(::pointer<::user::interaction>puiParent)
   {

      auto pcontext = m_papplication;
      
      auto psession = pcontext->m_psession->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      puser->create_child_form(this, nullptr, this, puiParent);

      if(m_pdocument != nullptr)
      {

         m_pimpact = m_pdocument->get_typed_impact < ::user::form > ();

         m_pimpact->set_form_callback(this);

         return true;

      }

      return false;

   }


   void network_configuration::on_show()
   {

      //auto pcontext = get_context();

      if(!m_pdocument->on_open_document(directory()->matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }

      xml::document doc;

      doc.load(file()->as_string(directory()->appdata() / "proxy.xml"));
         
      string strProxy(doc.root()->attribute("server").as_string());

      i32 iProxyPort;

      iProxyPort = doc.root()->attribute("port");
         
      auto pinteraction = m_pimpact->get_child_by_name("server");
         
      pinteraction->set_text(strProxy, ::action_context(::e_source_data) +  ::e_source_load);

      pinteraction = m_pimpact->get_child_by_name("port");
         
      pinteraction->set_text(::as_string(iProxyPort), ::action_context(::e_source_data) +  ::e_source_load);

   }


   void network_configuration::handle(::topic * ptopic, ::context * )
   {

      //auto pcontext = get_context();

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_interaction()->m_atom == "submit")
         {

            auto pinteraction = m_pimpact->get_child_by_name("server");

            string strServer;

            strServer = pinteraction->get_text();

            if(strServer.length() == 0)
            {

               file()->erase(directory()->appdata()/ "proxy.xml");

            }
            else
            {

               xml::document doc;

               doc.root()->set_name("proxy");

               doc.root()->set_attribute("server", strServer);

               pinteraction = m_pimpact->get_child_by_name("port");

               string strPort;

               strPort = pinteraction->get_text();

               doc.root()->set_attribute("port", strPort);

               file()->put_text(directory()->appdata()/"proxy.xml", doc.get_xml());

            }

         }

      }

   }


} // namespace usernet


