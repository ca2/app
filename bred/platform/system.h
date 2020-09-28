#pragma once


namespace bred
{


   class CLASS_DECL_BRED system :
      virtual public ::base::system
   {
   public:


      system();
      virtual ~system();

      void common_construct();


      virtual ::estatus initialize(::layered * pobjectContext) override;


   };


} // namespace bred




