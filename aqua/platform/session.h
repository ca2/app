#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA session :
      virtual public ::apex::session
   {
   public:


      session();
      virtual ~session();

      void common_construct();


      virtual ::e_status initialize(::object * pobject) override;

      virtual void on_instantiate_application(::application* papp) override;

   };


} // namespace aqua




