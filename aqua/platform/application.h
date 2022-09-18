#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA application :
      virtual public ::apex::application
   {
   public:


      __composite(::aqua::game)                       m_paquagame;
      __pointer(::networking_application)             m_pnetworkingapplication;
     

      application();
      ~application() override;


      void common_construct();


      inline ::aqua::system* get_system();

      virtual void initialize(::object * pobject) override;
      //virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

      void exit_application() override;

      virtual void game_on_create(::aqua::game * pgame);

      bool load_cached_string(string& str, const ::atom& atom, bool bLoadStringTable) override;


   };


} // namespace aqua




