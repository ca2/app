#pragma once


namespace app_core_build
{


   class CLASS_DECL_APP_CORE_BUILD main_frame :
      virtual public ::simple_main_frame
   {
   public:


      main_frame();
      virtual ~main_frame();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual ::experience::frame * frame_experience() override;

      virtual bool has_pending_graphical_update() override;


   };


} // namespace app_core_build



