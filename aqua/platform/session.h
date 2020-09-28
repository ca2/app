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


      virtual ::estatus initialize(::layered * pobjectContext) override;


   };


} // namespace aqua




