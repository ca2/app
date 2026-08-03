// Created by camilo on 2026-07-31 17:44 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME device_independent_bitmap :
      virtual public ::pixmap
   {
   public:


      HDC            m_hdcMemory;
      HBITMAP        m_hbitmap;
      HBITMAP        m_hbitmapOld;


      device_independent_bitmap();
      ~device_independent_bitmap() override;


      virtual void defer_create_device_independent_bitmap(const ::i32_size & sizeRaw);
      virtual void destroy_device_independent_bitmap();


   };


} // namespace windows
