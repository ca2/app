#pragma once


#include "berg/user/simple/frame_window.h"


namespace userex
{


   class CLASS_DECL_CORE dialog_frame :
      virtual public ::simple_frame_window
   {
   public:


      bool                       m_bExplicitTranslucency;


      dialog_frame();
      virtual ~dialog_frame();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual bool pre_create_window(::user::system * pusersystem) override;

      void install_message_routing(::channel * pchannel) override;


      //using ::sphere::dialog_frame::get_translucency;
      //::user::enum_translucency get_translucency(::user::style * pstyle) override;
      ::pointer<::experience::frame > frame_experience() override;

      //bool has_pending_graphical_update() override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);


   };


} // namespace userex












