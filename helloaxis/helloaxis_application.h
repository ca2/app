#pragma once



namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS application :
      virtual public ::helloaura::application,
      virtual public ::axis::application
   {
   public:


      application(::particle * pparticle);
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual void init_instance() override;
      virtual int  exit_application() override;

      virtual void on_request(::request * prequest) override;

      virtual string get_helloaura() override;

   };


} // namespace helloaxis



