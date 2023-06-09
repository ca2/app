#pragma once


#include "base/user/user/split_impact.h"


namespace userex
{


   class CLASS_DECL_CORE font_impact :
      virtual public ::user::split_impact
   {
   public:


      top_impact *                     m_ptopview;
      ::user::font_list_impact *       m_pimpact;
      bool                             m_bSourceFontSel;


      font_impact();
      ~font_impact() override;


      void install_message_routing(::channel * pchannel) override;


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      virtual void on_create_split_impact() override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      //void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      virtual bool set_sel_by_name(string str);


   };


} // namespace userex





