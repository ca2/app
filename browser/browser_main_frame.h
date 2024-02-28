#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER main_frame :
      virtual public ::simple_main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame(::particle * pparticle);
      virtual ~main_frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      using ::simple_main_frame::get_translucency;
      ::user::enum_translucency get_translucency(::user::style * pstyle) override;
      ::experience::frame * frame_experience() override;

      bool has_pending_graphical_update() override;

   };


} // namespace browser



