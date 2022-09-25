#include "framework.h"


namespace filehandler
{


   department::department(::object * pobject) :
      ::acme::department(pobject)
   {

      m_ptemplateMenu   = nullptr;
      m_ppaneimpact       = nullptr;

   }


   department::~department()
   {
   }


   void department::construct()
   {

   }

   bool department::init_instance()
   {


      add_factory_item <pane_impact >();
      add_factory_item <document >();
      add_factory_item <frame >();
      add_factory_item <impact >();

      if(!::acme::department::init_instance())
         return false;



      ::user::single_document_template* pdoctemplate = memory_new ::user::single_document_template(
      this,
      "html/frame",
      __type(document),
      __type(frame),       // top level SDI frame::user::interaction_impl
      __type(pane_impact));
      papp->add_document_template(pdoctemplate);
      m_ptemplateMenu = pdoctemplate;


      return true;
   }


   void department::term_instance()
   {

      try
      {

         ::acme::department::term_instance();

      }
      catch(...)
      {

      }

   }


   void department::on_request(::create * pcreate)
   {

      if(m_ppaneimpact == nullptr)
      {

         m_ptemplateMenu->do_request(pcreate);

      }

      if(m_ppaneimpact != nullptr && pcreate->m_payloadFile.get_type() == ::e_type_string)
      {

         m_ppaneimpact->set_current_tab_by_id("default_file_handler://" + pcreate->m_payloadFile.get_string());

      }

   }






} // namespace filehandler




