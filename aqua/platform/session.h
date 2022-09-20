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


      void initialize(::object * pobject) override;

      void on_instantiate_application(::apex::application* papp) override;


   };


} // namespace aqua




