#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_button :
      virtual public button,
      virtual public menu_interaction
   {
   public:


      menu_button();
      virtual ~menu_button();


      virtual ::e_status initialize_menu_interaction(menu_item* pitem) override;


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      // virtual bool create_interaction(::user::interaction * pparent, const ::id & id) override;

      virtual void _001DrawCheck(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawDefault(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      virtual void on_calc_size(calc_size * psize) override;

      virtual bool keyboard_focus_is_focusable() const override;

      virtual color32_t _001GetButtonBackgroundColor() override;


   };


} // namespace user







