// From impact.h by camilo on 2024-05-03 18:45 <3ThomasBorregaardSorensen!!
// a summary - Tab with quite few redrawing for more CPU for building.
#pragma once


#include "apex/platform/app_consumer.h"
#include "berg/user/user/impact.h"
//#include "berg/user/user/options_impact_handler.h"
#include "impact_interface.h"


namespace coding
{


   class CLASS_DECL_CODING summary :
      virtual public ::app_consumer < application, ::user::impact >
   {
   public:


      int                                    m_iLeftMargin;
      int                                    m_iLeftWidth;
      int                                    m_yStart;



      ::pointer<::write_text::font>         m_pfontTopic;
      ::pointer<::write_text::font>         m_pfontTopic2;
      ::pointer<::write_text::font>         m_pfontBold;

      ::pointer<::write_text::font>         m_pfontStatus;
      ::pointer<::write_text::font>         m_pfontElapsed;

      ::string m_strTopicSlowImprecise1;
      ::string_array m_straPinned;
      ::string m_strElapsedSlowImprecise;


      summary();
      ~summary() override;

      void install_message_routing(::channel* pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);


      virtual void update_designed_for_rare_calling();


      void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;


      document* get_document();

   };


} // namespace coding



