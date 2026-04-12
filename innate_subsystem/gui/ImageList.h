//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include "subsystem/particle.h"


namespace subsystem_apex
{

   namespace image_list
   {
      enum enum_create
      {

         e_create_mask             =0x00000001,
      };
   }

   class ImageListInterface :
   virtual public ::subsystem::particle_interface<ImageListInterface>
   {
   public:




      //virtual ~ImageListInterface() = 0;

      virtual void initializeImageList() = 0;

      virtual void createImageList(const ::int_size & size, int flags, int iInitialSize = 1, int iGrow = 1) = 0;

      virtual void destroyImageList() = 0;

      virtual void addIcon(IconInterface * picon) = 0;



   };



   class CLASS_DECL_APEX ImageList :
   virtual public ::subsystem::composite<ImageListInterface>
   {
   public:

      ImageList();

       ~ImageList()override;

      void initializeImageList() override;

      void createImageList(const ::int_size & size, int flags, int iInitialSize = 1, int iGrow = 1) override;

      void destroyImageList() override;

      virtual void addIcon(IconInterface * picon) override;


   };

} // namespace subsystem_apex
