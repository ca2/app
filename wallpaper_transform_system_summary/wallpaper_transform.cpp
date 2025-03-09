// Created by camilo on 2025-03-08 23:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "wallpaper_transform.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/node.h"


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

   }


   void wallpaper_transform::transform(::image::image * pimage)
   {

      auto psummary = node()->operating_system_summary();

      auto r = pimage->rectangle();

      r.top() = r.bottom() - 100;

      pimage->g()->draw_text(psummary->m_strSystem, r);

   }


   ::string wallpaper_transform::component_implementation_name()
   {

      return "System Summary at Wallpaper";

   }



} // namespace wallpaper_transform_system_summary



