// Created by camilo on 2022-11-08 23:36 <3ThomasBorregaardSorensen!!
#pragma once


#define NOK_IMAGE (::e_flag_none)
#define OK_IMAGE (::e_flag_success)
#define DEFAULT_CREATE_IMAGE_FLAG (::e_flag_success)


namespace image
{



      enum enum_mipmap
      {

         e_mipmap_none,
         e_mipmap_isotropic, // 3x original size (a bit more or less if there are scan adjustments)
         e_mipmap_anisotropic, // 4x original size (a bit more or less if there are scan adjustments)

      };



   enum enum_copy_disposition
   {

      e_copy_disposition_none,
      e_copy_disposition_y_swap,

   };


   class image_frame_array;
   class image_frame;


} // namespace image



