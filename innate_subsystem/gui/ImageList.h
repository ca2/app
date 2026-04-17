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
   virtual public ::Particle
   {
   public:




      //virtual ~ImageListInterface() = 0;

      virtual void initializeImageList() = 0;

      virtual void createImageList(const ::int_size & size, int flags, int iInitialSize = 1, int iGrow = 1) = 0;

      virtual void destroyImageList() = 0;

      virtual void addIcon(IconInterface * picon) = 0;



   };



   class CLASS_DECL_INNATE_SUBSYSTEM ImageListComposite :
   virtual public Composite<ImageListInterface>
   {
   public:


      ImplementCompositeø(ImageList, imagelist)

      //ImageList();

       //~ImageList()override;

         void initializeImageList() override
      {

         m_pimagelist->initializeImageList();
      }

      void createImageList(const ::int_size& size, int flags, int iInitialSize = 1, int iGrow = 1) override
      {
         m_pimagelist->createImageList(size, flags, iInitialSize, iGrow);
      }

      void destroyImageList() override { m_pimagelist->destroyImageList();
      }

      void addIcon(IconInterface* picon) override
      { m_pimagelist->addIcon(picon);
      }


   };


   class CLASS_DECL_INNATE_SUBSYSTEM ImageListAggregate :
virtual public Aggregate<ImageListComposite>
   {
   public:

      ImplementBaseø(ImageList)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM ImageList :
virtual public Object<ImageListAggregate>
   {
   public:


   };


} // namespace innate_subsystem
