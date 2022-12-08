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

      virtual void init_instance() override;
      virtual i32  exit_application() override;

      virtual void on_request(::request * prequest) override;

      virtual string get_helloaura() override;

   };


} // namespace helloaxis



