//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include "subsystem/platform/particle.h"


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

      virtual void create(::i32 cx, ::i32 cy, ::i32 flags, ::i32 iInitialSize = 1, ::i32 iGrow = 1) = 0



   };



   class CLASS_DECL_INNATE_SUBSYSTEM ImageList :
   virtual public composite<ImageList
   {
   public:

      ImageList();

       ~ImageList()override;

      void initialize_image_list() override;

      void create(::i32 cx, ::i32 cy, ::i32 flags, ::i32 iInitialSize = 1, ::i32 iGrow = 1) override;


   };

} // namespace innate_subsystem
