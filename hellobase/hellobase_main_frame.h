#pragma once


namespace hellobase
{


   class CLASS_DECL_APP_HELLO_BASE main_frame :
      virtual public ::user::frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame(::object * pobject);
      virtual ~main_frame();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      using ::user::frame_window::get_translucency;
      virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction);

      virtual bool has_pending_graphical_update();

   };


} // namespace hellobase












