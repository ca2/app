#include "framework.h"
#include "core/user/netuser/_netuser.h"
#include "aqua/xml.h"


namespace usernet
{


   network_configuration::network_configuration()
   {

      m_pdocument   = nullptr;
      m_pview  = nullptr;

   }


   network_configuration::~network_configuration()
   {
   }


   bool network_configuration::initialize(__pointer(::user::interaction) puiParent)
   {
      
      auto puser = User;

      m_pdocument = puser->create_form(this, this, puiParent);

      if(m_pdocument != nullptr)
      {

         m_pview = m_pdocument->get_typed_view < ::user::form > ();

         m_pview->set_form_callback(this);

         return true;

      }

      return false;

   }


   bool network_configuration::initialize_child(__pointer(::user::interaction) puiParent)
   {

      auto puser = User;

      puser->create_child_form(this, this, puiParent);

      if(m_pdocument != nullptr)
      {

         m_pview = m_pdocument->get_typed_view < ::user::form > ();

         m_pview->set_form_callback(this);

         return true;

      }

      return false;

   }

   void network_configuration::on_show()
   {
      if(!m_pdocument->on_open_document(Context.dir().matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }

      xml::document doc;

      if(doc.load(Context.file().as_string(Context.dir().appdata()/"proxy.xml")))
      {
         
         string strProxy(doc.root()->attribute("server"));

         i32 iProxyPort = doc.root()->attribute("port");
         
         auto pinteraction = m_pview->get_child_by_name("server");
         
         pinteraction->_001SetText(strProxy, ::action_context(::e_source_data) +  ::e_source_load);

         pinteraction = m_pview->get_child_by_name("port");
         
         pinteraction->_001SetText(__str(iProxyPort), ::action_context(::e_source_data) +  ::e_source_load);

      }

   }

   void network_configuration::on_control_event(::user::control_event * pevent)
   {


      if(pevent->m_eevent == ::user::e_event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {

            auto pinteraction = m_pview->get_child_by_name("server");

            string strServer;

            pinteraction->_001GetText(strServer);

            if(strServer.get_length() == 0)
            {

               Context.file().del(Context.dir().appdata()/ "proxy.xml");

            }
            else
            {

               xml::document doc;

               doc.root()->set_name("proxy");

               doc.root()->set_attribute("server", strServer);

               pinteraction = m_pview->get_child_by_name("port");

               string strPort;

               pinteraction->_001GetText(strPort);

               doc.root()->set_attribute("port", strPort);

               Context.file().put_contents(Context.dir().appdata()/"proxy.xml", doc.get_xml());

            }

         }

      }

   }


} // namespace usernet


