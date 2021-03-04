#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{

   network_configuration::network_configuration()
   {
//      m_pdocument   = nullptr;
      //    m_pview  = nullptr;
   }

   network_configuration::~network_configuration()
   {
   }

   bool network_configuration::initialize(__pointer(::user::interaction) puiParent)
   {
      /*m_pdocument = Application.create_form(this, puiParent);
      if(m_pdocument != nullptr)
      {
         m_pview = m_pdocument->get_typed_view < ::user::form > ();
         m_pview->m_pcallback = this;
         return true;
      }*/
      return false;
   }

   bool network_configuration::initialize_child(__pointer(::user::interaction) puiParent)
   {
      /*
      m_pdocument = psession->user()->create_child_form(this, puiParent);
      if(m_pdocument != nullptr)
      {
         m_pview = m_pdocument->get_typed_view < ::user::form > ();
         m_pview->m_pcallback = this;
         return true;
      }*/
      return false;
   }

   void network_configuration::on_show()
   {
      /*
      if(!m_pdocument->on_open_document(Context.dir().matter("system/network/configuration/proxy.xhtml")))
      {
         return;
      }
      xml::node node(get_object());
      if(node.load(System->file_as_string(System, Context.dir().appdata("proxy.xml"))))
      {
         string strProxy = node.attr("server");
         i32 iProxyPort = node.attr("port");
         __pointer(::user::interaction) pinteraction = m_pview->get_child_by_name("server");
         __pointer(::user::primitive) ptext =  (pinteraction);
         ptext->_001SetText(strProxy, false);
         pinteraction = m_pview->get_child_by_name("port");
         ptext =  (pinteraction);
         ptext->_001SetText(__str(iProxyPort), false);
      }*/
   }




} // namespace user
