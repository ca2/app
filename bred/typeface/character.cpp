//
// Created by camilo on 2026-01-16 23:25 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "character.h"
#include "bred/gpu/context.h"
#include "bred/gpu/pixmap.h"
#include "bred/gpu/renderer.h"


namespace typeface
{


   ::gpu::pixmap * character::get_gpu_pixmap(::gpu::renderer * pgpurenderer)
   {

      if (!m_ppixmapOptional)
      {

         if (Size.cx <= 0 || Size.cy <= 0)
         {

            throw ::exception(error_wrong_state);

         }

         m_ppixmapOptional = pgpurenderer->m_pgpucontext->create_gpu_pixmap({ Size.x, Size.y });

         //ch.m_ppixmap->initialize_gpu_pixmap(m_pgpurenderer, { ch.Size.x, ch.Size.y });

         if (::is_set(m_ppixmapOptional))
         {

            m_ppixmapOptional->set_pixels(m_memory.data());

         }

      }

      return m_ppixmapOptional;

   }


} // namespace typeface



