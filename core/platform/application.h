#pragma once


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::bred::application
   {
   public:


      application();
      virtual ~application();

      void common_construct();


      virtual ::e_status initialize(::layered * pobjectContext) override;
      virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

   };


} // namespace core




