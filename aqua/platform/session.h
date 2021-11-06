#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA session :
      virtual public ::apex::session
   {
   public:


      session();
      ~session() override;

      void common_construct();


      ::e_status initialize(::object * pobject) override;

      void on_instantiate_application(::application* papp) override;


   };


} // namespace aqua




