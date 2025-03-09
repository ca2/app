// Created by camilo on 2025-03-08 23:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/graphics/image/wallpaper_transform.h"
#include "acme/platform/component_implementation.h"


namespace wallpaper_transform_system_summary
{


   class CLASS_DECL_WALLPAPER_TRANSFORM_SYSTEM_SUMMARY wallpaper_transform :
      virtual public ::image::wallpaper_transform,
      virtual public ::component_implementation
   {
   public:


      wallpaper_transform();
      ~wallpaper_transform() override;


      void initialize(::particle * pparticle) override;


      void transform(::image::image * pimage) override;
      ::string component_implementation_name() override;


   };


} // namespace wallpaper_transform_system_summary




