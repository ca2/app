#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA application :
      virtual public ::application
   {
   public:


      __composite(::aqua::game)                       m_pgame;


      application();
      virtual ~application();

      void common_construct();


      inline ::aqua::system* get_system();

      virtual ::e_status initialize(::object * pobject) override;
      //virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

      virtual void _001OnFranceExit() override;

      virtual void game_on_create(::aqua::game * pgame);




   };


} // namespace aqua




