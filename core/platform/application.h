#pragma once


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::bred::application
   {
   public:


      application();
      ~application() override;


      void common_construct();

      inline ::core::application* get_application() const { return m_pcoreapplication; }
      inline ::core::session* get_session() const { return m_pcoresession; }
      inline ::core::system* get_system() const { return m_pcoresystem; }



      virtual ::e_status initialize(::object * pobject) override;
      __pointer(::progress::real) show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount) override;
      


      virtual string prepare_menu_impact();
      virtual string prepare_menu_impact_header();
      virtual string prepare_menu_impact_main_body();
      virtual string prepare_menu_impact_footer();


   };


} // namespace core




