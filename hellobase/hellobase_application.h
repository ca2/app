#pragma once



namespace hellobase
{


   class CLASS_DECL_APP_HELLO_BASE application :
      virtual public ::helloaxis::application,
      virtual public ::berg::application
   {
   public:


      ::user::document *                     m_pdocMenu;
      ::user::single_document_template *     m_ptemplateHelloBaseMain;



      application(::particle * pparticle);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual string preferred_experience() override;
      virtual void init_instance() override;
      virtual int  exit_application() override;

      virtual void on_request(::request * prequest) override;

      virtual string get_helloaura() override;

   };


} // namespace hellobase



