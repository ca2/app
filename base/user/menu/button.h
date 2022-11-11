#pragma once


#include "aura/user/user/button.h"
#include "interaction.h"


namespace user
{


   class CLASS_DECL_BASE menu_button :
      virtual public button,
      virtual public menu_interaction
   {
   public:


      menu_button();
      virtual ~menu_button();


      virtual void initialize_menu_interaction(menu_item* pitem) override;


      void install_message_routing(::channel * pchannel) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      // virtual bool create_interaction(::user::interaction * pparent, const ::atom & atom) override;

      virtual void _001DrawCheck(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawDefault(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      void on_calc_size(calc_size * psize) override;

      bool keyboard_focus_is_focusable() override;

      ::color::color _001GetButtonBackgroundColor() override;


   };


} // namespace user







