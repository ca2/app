#pragma once

#include "acme/prototype/prototype/matter.h"
#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/time/time/time.h"
#include "acme/graphics/draw2d/color.h"
#include "aura/graphics/draw2d/graphics_pointer.h"

namespace user
{

   // Composed overlay; the host is supplied only while drawing, never retained.
   class CLASS_DECL_BERG render_lines : virtual public ::matter
   {
   public:
      ::string_array m_straLines;
      ::string_array m_straCachedLines;
      ::image::image_pointer m_pimageCache;
      ::write_text::font_pointer m_pfont;
      ::color::color m_colorText;
      ::i32_size m_sizeContent;
      ::i32 m_iPaddingLeft = 100;
      ::i32 m_iPaddingBottom = 100;
      class ::time m_timeCacheInterval;
      class ::time m_timeLastBitmapUpdate;
      bool m_bCacheBuilt = false;

      render_lines();
      ~render_lines() override;

      // Use this when publishing from another thread. Direct array edits must
      // be made on the drawing thread or under synchronization().
      void set_line(::collection::index iLine, const ::scoped_string & strLine);
      void draw(::user::interaction * phost, ::draw2d::graphics_pointer & pgraphics);
   };

} // namespace user
