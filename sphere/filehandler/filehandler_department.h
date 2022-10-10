#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE department :
      public ::acme::department
   {
   public:


      ::pointer<pane_impact>                                 m_ppaneimpact;
      ::pointer<::user::single_document_template>      m_ptemplateMenu;


      department(::object * pobject);
      virtual ~department();

      void construct();

      virtual void init_instance() override;
      virtual void term_instance() override;


      virtual void on_request(::create * pcreate) override;


   };


} // namespace filehandler


