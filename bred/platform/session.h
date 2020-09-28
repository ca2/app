#pragma once


namespace bred
{


   class CLASS_DECL_BRED session :
      virtual public ::base::session
   {
   public:


      session();
      virtual ~session();

      void common_construct();


      virtual ::estatus initialize(::layered * pobjectContext) override;


   };


} // namespace base




