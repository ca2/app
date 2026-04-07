//
// Created by camilo on 2026-04-06 14:24 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ImageList.h"

namespace innate_subsystem
{

   ImageList::ImageList()
   {

   }


   ImageList::~ImageList()
   {


   }


   void ImageList::initializeImageList()
   {



   }


   void ImageList::createImageList(const int_size& size, int flags, int iInitialSize, int iGrow)
   {

      m_pparticleThis->createImageList(size, flags, iInitialSize, iGrow);

   }


   void ImageList::destroyImageList()
   {

      m_pparticleThis->destroyImageList();

   }


   void ImageList::addIcon(innate_ui::icon* pinnateuiicon)
   {

      m_pparticleThis->addIcon(pinnateuiicon);

   }

}// namespace innate_subsystem