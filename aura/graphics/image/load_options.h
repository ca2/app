//
// Created by camilo on 2024-09-06 19:55 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace image
{


   class CLASS_DECL_AURA load_options
   {
   public:


      bool sync = true;
      bool cache = true;
      bool helper_maps = false;
      bool toy = true;
      bool apply_exif_orientation = true;
      ::particle * pparticleSync = nullptr;
      ::function < void(::image::load_image *) > functionLoaded;

   };


} // namespace image



