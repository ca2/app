//
// Created by camilo on 2024-09-06 19:59 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace image
{


   enum enum_mipmap
   {

      e_mipmap_none,
      e_mipmap_isotropic, // 3x original size (a bit more or less if there are scan adjustments)
      e_mipmap_anisotropic, // 4x original size (a bit more or less if there are scan adjustments)

   };


   enum enum_format
   {
      e_format_none,
      e_format_png,
      e_format_bmp,
      e_format_gif,
      e_format_jpeg,
      e_format_tga,
   };




   enum enum_sub_image
   {

      /// entire image
      e_sub_image_entire,
      /// rectangle are rates on any selectable source
      e_sub_image_rate,
      /// rectangle are coordinates on source image
      /// that would be selected by ::image::image_source_interface::size();
      e_sub_image_coordinates,
      /// null image
      e_sub_image_none,


   };


   enum enum_placement
   {

      e_placement_stretch,
      e_placement_source, // align is meaningful
      e_placement_aspect_fit, // align is meaninful

   };


} // namespace image



