// From impact.h on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "impact.h"


namespace app_integration
{


   class CLASS_DECL_APP_INTEGRATION ffmpeg :
      virtual public impact
   {
   public:



      ffmpeg();
      ~ffmpeg() override;

      
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

   };


} // namespace simple_drawing


