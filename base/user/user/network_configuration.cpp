#include "framework.h"
#include "network_configuration.h"


namespace user
{

   network_configuration::network_configuration()
   {
//      m_pdocument   = nullptr;
      //    m_pimpact  = nullptr;
   }

   network_configuration::~network_configuration()
   {
   }

   bool network_configuration::initialize(::pointer<::user::interaction>puiParent)
   {
      /*m_pdocument = papp->create_form(this, puiParent);
      if(m_pdocument != nullptr)
      {
         m_pimpact = m_pdocument->get_typed_impact < ::user::form > ();
         m_pimpact->m_pcallback = this;
         return true;
      }*/
      return false;
   }

   bool network_configuration::initialize_child(::pointer<::user::interaction>puiParent)
   {
      /*
      m_pdocument = psession->user()->create_child_form(this, puiParent);
      if(m_pdocument != nullptr)
      {
         m_pimpact = m_pdocument->get_typed_impact < ::user::form > ();
         m_pimpact->m_pcallback = this;
         return true;
      }*/
      return false;
   }

   void network_configuration::on_show()
   {
      /*
      if(!m_pdocument->on_open_document(directory()->matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }
      xml::node node(this);
      if(node.load(psystem->file_system()->as_string(System, directory()->appdata("proxy.xml"))))
      {
         string strProxy = node.attr("server");
         i32 iProxyPort = node.attr("port");
         ::pointer<::user::interaction>pinteraction = m_pimpact->get_child_by_name("server");
         ::pointer<::user::interaction_base>ptext =  (pinteraction);
         ptext->set_text(strProxy, false);
         pinteraction = m_pimpact->get_child_by_name("port");
         ptext =  (pinteraction);
         ptext->set_text(as_string(iProxyPort), false);
      }*/
   }




} // namespace user
