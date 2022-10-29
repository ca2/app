#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD main_frame :
      virtual public simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;


      main_frame(::particle * pparticle);
      virtual ~main_frame();


//      // void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;


      using ::simple_frame_window::get_translucency;
      virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction);
      virtual ::experience::frame * frame_experience();

      virtual bool has_pending_graphical_update();

   };


} // namespace helloworld












