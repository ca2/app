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



      virtual void initialize(::object * pobject) override;
      __pointer(::progress::real) show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount) override;


      //virtual void prepare_impact_menu(::user::menu * pmenu);


      virtual string prepare_impact_options();
      virtual string prepare_impact_options_header();
      virtual string prepare_impact_options_main_body();
      virtual string prepare_impact_options_footer();


   };


} // namespace core




