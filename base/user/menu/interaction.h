#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_BASE menu_interaction :
      virtual public interaction
   {
   public:


      ::pointer<menu_item>       m_pmenuitem;


      menu_interaction();
      ~menu_interaction() override;

      
      virtual void initialize_menu_interaction(menu_item* pmenuitem);


      ::base::application* get_app();
      ::base::session* get_session();
      ::base::system* get_system();
      ::base::user* user();

      void install_message_routing(::channel * pchannel) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawCheck(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawDefault(::draw2d::graphics_pointer & pgraphics);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      virtual void on_calc_size(calc_size * psize) override;


   };


} // namespace user







