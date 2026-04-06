//
// Created by camilo on 2026-04-06 14:24 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ImageList.h"


namespace windows
{
   namespace innate_subsystem
   {

      ImageList::ImageList()
      {

      }


      ImageList::~ImageList()
      {


      }


      void ImageList::initialize_image_list()
      {



      }


      void ImageList::create(int cx, int cy, int flags, int iInitialSize, int iGrow)
      {
        m_himagelist = ImageList_Create(cx,
                              cy,
                                                     flags, iInitialSize,iGrow);


      }


   }// namespace innate_subsystem
}// namnamespace  windows