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


      virtual ::e_status initialize(::layered * pobjectContext) override;


   };


} // namespace bred




