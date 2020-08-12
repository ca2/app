#pragma once


namespace user
{


   class CLASS_DECL_APP_CORE_EXPERIENCE_CORE meta_button :
      virtual public ::experience::button
   {
   public:


      ::draw2d::region_pointer                 m_spregion;


      meta_button(::object * pobject);
      virtual ~meta_button();


      virtual void on_hit_test(::user::item & item);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void install_message_routing(::channel * pchannel);



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);



      virtual bool keyboard_focus_is_focusable();

   };



} // namespace user




