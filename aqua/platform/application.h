#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA application :
      virtual public ::apex::application
   {
   public:


      application();
      virtual ~application();

      void common_construct();


      virtual ::estatus initialize(::layered * pobjectContext) override;
      //virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

   };


} // namespace aqua




