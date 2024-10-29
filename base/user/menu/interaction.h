#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_BASE menu_interaction :
      virtual public interaction
   {
   public:


      ::pointer<::menu::item>       m_pmenuitem;


      menu_interaction();
      ~menu_interaction() override;


      void destroy() override;

      
      virtual void initialize_menu_interaction(::menu::item* pmenuitem);


      // ::base::application* get_app();
      // ::base::session* get_session();
      // ::base::system* get_system();
      // ::base::user* baseuser() override;

      void install_message_routing(::channel * pchannel) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawCheck(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawDefault(::draw2d::graphics_pointer & pgraphics);


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);


      ::size_f64 get_preferred_size(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user







