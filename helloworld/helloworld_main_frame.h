#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD main_frame :
      virtual public simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame(::context_object * pcontextobject);
      virtual ~main_frame();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      using ::simple_frame_window::get_translucency;
      virtual bool get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::interaction * pinteraction);
      virtual ::experience::frame * experience_get_frame();

      virtual bool has_pending_graphical_update();

   };


} // namespace helloworld












