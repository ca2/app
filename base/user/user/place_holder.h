#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class place_holder_container;


   class CLASS_DECL_BASE place_holder :
      virtual public interaction
   {
   public:


      place_holder();
      ~place_holder() override;


      ::pointer<place_holder>create_shadow_clone();


      //virtual bool create_child(::user::place_holder_container * pcontainer);

      void install_message_routing(::channel * pchannel) override;


      bool on_add_child(::user::interaction * puserinteractionChild) override;

      bool is_this_visible(enum_layout elayout = e_layout_design) override;


      virtual bool can_merge(::user::interaction * pinteraction) override;
      virtual bool merge(::user::interaction * pinteraction) override;
      virtual ::pointer<place_holder>place_hold(::user::interaction* pinteraction);
      virtual bool unplace(::user::interaction * pinteraction);
      virtual bool is_place_holding(::user::interaction * pinteraction);

      virtual void on_erase_child(::user::interaction * pinteraction) override;
      virtual void on_hide_child(::user::interaction * pinteraction) override;

      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      ::user::interaction * get_hold();

      virtual bool is_place_holder() override;

      virtual bool _001IsBackgroundBypass();

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      virtual void get_child_rect(::rectangle_i32 & rectangle) override;


   };


   class CLASS_DECL_BASE place_holder_ptra :
      virtual public pointer_array < place_holder >
   {
   public:

      i32 place_hold(::user::interaction * pinteraction);
      i32 unplace(::user::interaction * pinteraction);

   };

} // namespace user
