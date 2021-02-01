#pragma once


namespace user
{


   class place_holder_container;


   class CLASS_DECL_BASE place_holder :
      virtual public interaction
   {
   public:


      place_holder();
      virtual ~place_holder();


      __pointer(place_holder) create_shadow_clone();


      //virtual bool create_child(::user::place_holder_container * pcontainer);

      virtual void install_message_routing(::channel * pchannel) override;

      virtual bool can_merge(::user::interaction * pinteraction) override;
      virtual bool merge(::user::interaction * pinteraction) override;
      virtual __pointer(place_holder) place_hold(::user::interaction* pinteraction);
      virtual bool unplace(::user::interaction * pinteraction);
      virtual bool is_place_holding(::user::interaction * pinteraction);

      virtual void on_remove_child(::user::interaction * pinteraction) override;
      virtual void on_hide_child(::user::interaction * pinteraction) override;

      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      ::user::interaction * get_hold();

      virtual bool is_place_holder() override;

      virtual bool _001IsBackgroundBypass();

      virtual void route_command_message(::user::command * pcommand) override;

      virtual void get_child_rect(RECTANGLE_I32 * prectangle) override;


   };

   class CLASS_DECL_BASE place_holder_ptra :
      virtual public __pointer_array(place_holder)
   {
   public:

      i32 place_hold(::user::interaction * pinteraction);
      i32 unplace(::user::interaction * pinteraction);

   };

} // namespace user
