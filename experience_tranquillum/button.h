#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM button :
      virtual public ::experience::button
   {
   public:


      ::draw2d::region_pointer                 m_spregion;
      ::draw2d::pen_pointer                    m_pen;
      ::draw2d::brush_pointer                  m_brush;


      button();
      virtual ~button();


      virtual void on_hit_test(::user::item & item) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics)override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnShowWindow);
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;



      virtual bool keyboard_focus_is_focusable() override;

   };



} // namespace tranquillum


   } // namespace experience



