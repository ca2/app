// From core/graphics/color_selector 2025-03-11 23:19 <3ThomasBorregaardSorensen!!
// From userex/color_impact 2023-10-09 01:30 <3ThomasBorregaardSorensen!!
#pragma once


namespace graphics
{


   class CLASS_DECL_AXIS color_selector :
      virtual public ::particle
   {
   public:


      ::color::hls                     m_hls;

      ::function < void(const ::color::hls & hls, bool bFinal) >    m_callbackHls;


      color_selector();
      ~color_selector() override;


      virtual void set_sel_color(const ::color::hls & hls);
      virtual ::color::hls get_sel_color();

      
      //virtual ::color::color color_selector_get_color();
      //virtual void color_selector_set_color(const ::color::color & color);


      virtual void on_color_change();


      virtual void graphics_set_mouse_capture() = 0;
      virtual void graphics_release_mouse_capture() = 0;
      virtual void graphics_redraw() = 0;


   };


} // namespace graphics


