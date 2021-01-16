#pragma once



namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS application :
      virtual public ::helloaura::application,
      virtual public ::axis::application
   {
   public:


      application(::layered * pobjectContext);
      virtual ~application();

      virtual ::e_status init_instance() override;
      virtual i32  exit_application() override;

      virtual void on_request(::create * pcreate) override;

      virtual string get_helloaura() override;

   };


} // namespace helloaxis



