#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA application :
      virtual public ::apex::application
   {
   public:


      __composite(::aqua::game)                       m_pgame;


      application();
      virtual ~application();

      void common_construct();


      virtual ::e_status initialize(::layered * pobjectContext) override;
      //virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

      virtual void _001OnFranceExit() override;

   };


} // namespace aqua




