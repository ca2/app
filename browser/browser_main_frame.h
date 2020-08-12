#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER main_frame :
      virtual public ::simple_main_frame
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame(::object * pobject);
      virtual ~main_frame();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      using ::simple_main_frame::get_translucency;
      virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::style_context * pcontext) override;
      virtual ::experience::frame * experience_get_frame() override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace browser



