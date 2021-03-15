#include "framework.h"


namespace filehandler
{


   department::department(::context_object * pcontextobject) :
      ::apex::department(pobject)
   {

      m_ptemplateMenu   = nullptr;
      m_ppaneview       = nullptr;

   }


   department::~department()
   {
   }


   void department::construct()
   {

      //m_strAppName         = "default_file_handler";
      //m_strBaseSupportId   = "default_file_handler";
      //m_strInstallToken    = "default_file_handler";
      //m_bLicense           = false;

   }

   bool department::init_instance()
   {


      create_factory <pane_view >();
      create_factory <document >();
      create_factory <frame >();
      create_factory <view >();

      if(!::apex::department::init_instance())
         return false;



      ::user::single_document_template* pdoctemplate = new ::user::single_document_template(
      this,
      "html/frame",
      __type(document),
      __type(frame),       // top level SDI frame::user::interaction_impl
      __type(pane_view));
      papplication->add_document_template(pdoctemplate);
      m_ptemplateMenu = pdoctemplate;


      return true;
   }


   void department::term_instance()
   {

      try
      {

         ::apex::department::term_instance();

      }
      catch(...)
      {

      }

   }


   void department::on_request(::create * pcreate)
   {

      if(m_ppaneview == nullptr)
      {

         m_ptemplateMenu->do_request(pcreate);

      }

      if(m_ppaneview != nullptr && pcreate->m_pcommandline->m_varFile.get_type() == ::e_type_string)
      {

         m_ppaneview->set_cur_tab_by_id("default_file_handler://" + pcreate->m_pcommandline->m_varFile.get_string());

      }

   }






} // namespace filehandler




