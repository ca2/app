// Created by camilo on 2025-03-08 23:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "wallpaper_transform.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/node.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/write_text/font.h"


namespace wallpaper_transform_system_summary
{


   wallpaper_transform::wallpaper_transform()
   {

      //m_pzlibfilefuncdef = zip_filefuncdef_malloc();

   }


   wallpaper_transform::~wallpaper_transform()
   {


   }


   void wallpaper_transform::initialize(::particle* pparticle)
   {

      ::particle::initialize(pparticle);

      øconstruct(m_pfont);

      m_pfont->create_font(e_font_sans_ui, 24_pt);

   }


   void wallpaper_transform::transform(::image::image * pimage)
   {

      auto psummary = node()->operating_system_summary();

      auto r = pimage->rectangle();

      r.top() = r.bottom() - 150;
      r.left() += 40;

      pimage->g()->set(m_pfont);

      pimage->g()->set_text_color(::color::white);

      pimage->g()->draw_text(psummary->m_strSystem, r);

      r.top() = r.bottom() - 200;

      pimage->g()->draw_text(node()->get_host_name(), r);

   }


   //::string wallpaper_transform::component_implementation_name()
   //{

   //   return system()->http_text("app/wallpaper_transform_system_summmary", "component_implementation_name");

   //}



} // namespace wallpaper_transform_system_summary



