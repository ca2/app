#pragma once



namespace hellobase
{


   class CLASS_DECL_APP_HELLO_BASE application :
      virtual public ::helloaxis::application,
      virtual public ::base::application
   {
   public:


      ::user::document *                     m_pdocMenu;
      ::user::single_document_template *     m_ptemplateHelloBaseMain;



      application(::context_object * pcontextobject);
      virtual ~application();

      virtual string preferred_experience() override;
      virtual ::e_status init_instance() override;
      virtual i32  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual string get_helloaura() override;

   };


} // namespace hellobase



