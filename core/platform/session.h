#pragma once


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::base::session
   {
   public:


      session();
      virtual ~session();

      void common_construct();


      virtual ::estatus initialize(::layered * pobjectContext) override;


   };


} // namespace core




