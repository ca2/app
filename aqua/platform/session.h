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


      virtual ::e_status initialize(::context_object * pcontextobject) override;


   };


} // namespace aqua




