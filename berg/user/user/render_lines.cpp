#include "platform.h"
#include "render_lines.h"
#include "aura/user/user/interaction.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/write_text/font.h"

namespace user
{

   render_lines::render_lines()
   {
      defer_create_synchronization();
      m_colorText = ::color::yellow;
      m_timeCacheInterval = 100_ms;
   }

   render_lines::~render_lines() {}

   void render_lines::set_line(::collection::index iLine, const ::scoped_string & strLine)
   {
      if (iLine < 0) return;
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      m_straLines.atø(iLine) = strLine;
   }

   void render_lines::draw(::user::interaction * phost, ::draw2d::graphics_pointer & pgraphics)
   {
      if (!phost) return;
      _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
      if (m_straLines.is_empty()) return;

      bool bChanged = m_straLines.get_count() != m_straCachedLines.get_count();
      for (::collection::index i = 0; !bChanged && i < m_straLines.get_count(); ++i)
         bChanged = m_straLines[i] != m_straCachedLines[i];

      // Throttle relative to the last bitmap build, rather than the last text
      // change, so continuously changing lines cannot postpone updates forever.
      if (!m_bCacheBuilt || (bChanged && m_timeLastBitmapUpdate.elapsed() >= m_timeCacheInterval))
      {
         if (!m_pfont)
         {
            constructø(m_pfont);
            m_pfont->create_font("Arial", 20_px, e_font_weight_normal);
         }
         ::draw2d::save_context context(pgraphics);
         pgraphics->set(m_pfont);
         ::i32 width = 1;
         ::i32 lineHeight = 24;
         for (auto & strLine : m_straLines)
         {
            auto extent = pgraphics->get_text_extent(strLine);
            width = maximum(width, (::i32)extent.cx + 4);
            lineHeight = maximum(lineHeight, (::i32)extent.cy + 2);
         }
         ::i32_size sizeContent(width, lineHeight * (::i32)m_straLines.get_count());
         auto sizeAllocation = sizeContent;
         if (m_pimageCache.ok())
         {
            sizeAllocation.cx = maximum(sizeAllocation.cx, m_pimageCache->width());
            sizeAllocation.cy = maximum(sizeAllocation.cy, m_pimageCache->height());
         }
         defer_constructø(m_pimageCache);
         m_pimageCache->update_as_render_target(sizeAllocation, phost->draw2d_domain());
         if (m_pimageCache.nok()) return; // Retry on the next draw.
         {
            auto graphics = m_pimageCache->acquire_graphics();
            graphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
            graphics->fill_rectangle(::i32_rectangle(m_pimageCache->size()), ::color::transparent);
            graphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
            graphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);
            graphics->set_solid_color(m_colorText);
            graphics->set(m_pfont);
            for (::collection::index i = 0; i < m_straLines.get_count(); ++i)
               graphics->text_out(0, (::i32)i * lineHeight, m_straLines[i]);
         }
         // Finish the graphics lease before publishing the image as a source.
         m_sizeContent = sizeContent;
         m_straCachedLines = m_straLines;
         m_timeLastBitmapUpdate = ::time::now();
         m_bCacheBuilt = true;
      }

      ::draw2d::save_context context(pgraphics);
      auto sizeHost = phost->rectangle(::user::e_layout_design).size();
      auto y = maximum(0, sizeHost.cy - m_iPaddingBottom - m_sizeContent.cy);
      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
      ::image::image_source source(m_pimageCache, ::f64_rectangle(m_sizeContent));
      ::image::image_drawing_options options(::f64_rectangle(
         m_iPaddingLeft, y, m_iPaddingLeft + m_sizeContent.cx, y + m_sizeContent.cy));
      pgraphics->draw({options, source});
   }

} // namespace user
