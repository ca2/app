#pragma once


#include "base/user/user/impact.h"


namespace userex
{


   class CLASS_DECL_CORE home_impact :
      virtual public ::user::impact
   {
   public:


      class CLASS_DECL_CORE item
      {

      public: 

         string            m_strName;
         ::file::path      m_path;

      };


      home_impact();
      virtual ~home_impact();


      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      ///void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_mouse(const ::int_point & point);
      virtual void rebuild_luminance();

//      virtual ::color::color get_color();
//      virtual void set_color(::color::color color);

   };


} // namespace userex




