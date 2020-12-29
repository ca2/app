#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE department :
      public ::apex::department
   {
   public:


      __pointer(pane_view)                                  m_ppaneview;
      __pointer(::user::single_document_template)       m_ptemplateMenu;


      department(::layered * pobjectContext);
      virtual ~department();

      void construct();

      virtual ::e_status init_instance() override;
      virtual void term_instance() override;


      virtual void on_request(::create * pcreate) override;


   };


} // namespace filehandler


