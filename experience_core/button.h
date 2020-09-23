#pragma once


namespace experience
{


   namespace aura
   {


      class CLASS_DECL_APP_EXPERIENCE_CORE button :
         virtual public ::experience::button
      {
      public:


         ::draw2d::region_pointer                 m_spregion;


         button();
         virtual ~button();


         virtual void on_hit_test(::user::item & item) override;

         virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
         virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;
         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

         virtual void install_message_routing(::channel * pchannel) override;



         virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;



         virtual bool keyboard_focus_is_focusable() override;

      };


   } // namespace aura


} // namespace experience



