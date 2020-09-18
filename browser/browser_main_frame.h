#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER main_frame :
      virtual public ::simple_main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame(::layered * pobjectContext);
      virtual ~main_frame();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      using ::simple_main_frame::get_translucency;
      virtual ::user::e_translucency get_translucency(::user::style * pstyle) const override;
      virtual ::experience::frame * experience_get_frame() override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace browser



