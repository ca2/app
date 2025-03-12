// From core/graphics/color_selector 2025-03-11 23:22 <3ThomasBorregaardSorensen!!
// From userex/color_impact 2023-10-09 01:30 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "color_selector.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/graphics/image/image32.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/font.h"
#include "aura/user/user/frame_interaction.h"
#include "aura/message/user.h"
//#include "aura/operating_system/windows_common/graphics.h"
#include "aura/platform/system.h"



namespace graphics
{


   color_selector::color_selector()
   {

   }


   color_selector::~color_selector()
   {


   }


   void color_selector::set_sel_color(const ::color::hls & hls)
   {

      m_hls = hls;

   }


   ::color::hls color_selector::get_sel_color()
   {

      return m_hls;

   }


   //::color::color color_selector::color_selector_get_color()
   //{

   //   ::color::color color;

   //   color.set_hls(m_hls);

   //   color.m_uchOpacity = 255;

   //   return color;

   //}


   //void color_selector::color_selector_set_color(const ::color::color & color)
   //{

   //   color.get_hls(m_hls);

   //}


   void color_selector::on_color_change()
   {


   }


} // namespace graphics



