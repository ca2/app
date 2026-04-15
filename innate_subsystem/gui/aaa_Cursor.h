//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include "subsystem/particle.h"


namespace innate_subsystem
{

   namespace image_list
   {
      enum enum_create
      {

         e_create_mask             =0x00000001,
      };
   }

   class ImageListInterface :
   virtual public particle_interface
   {
   public:




      //virtual ~ImageListInterface() = 0;

      virtual void initialize_image_list() = 0;

      virtual void create(int cx, int cy, int flags, int iInitialSize = 1, int iGrow = 1) = 0



   };



   class CLASS_DECL_INNATE_SUBSYSTEM ImageList :
   virtual public composite<ImageList
   {
   public:

      ImageList();

       ~ImageList()override;

      void initialize_image_list() override;

      void create(int cx, int cy, int flags, int iInitialSize = 1, int iGrow = 1) override;


   };

} // namespace innate_subsystem
