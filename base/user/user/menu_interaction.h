#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_interaction :
      virtual public interaction
   {
   public:


      __pointer(menu_item)        m_pmenuitem;


      menu_interaction();
      virtual ~menu_interaction();

      
      virtual ::e_status initialize_menu_interaction(menu_item* pitem);


      inline ::base::session* get_session() const;


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawCheck(::draw2d::graphics_pointer & pgraphics);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawDefault(::draw2d::graphics_pointer & pgraphics);

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual void on_calc_size(calc_size * psize) override;


   };


} // namespace user







