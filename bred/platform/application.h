#pragma once


namespace bred
{


   class CLASS_DECL_BRED application :
      virtual public ::base::application
   {
   public:


      application();
      ~application() override;


      void common_construct();


      virtual void initialize(::object * pobject) override;
      //virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount);

   };


} // namespace bred




