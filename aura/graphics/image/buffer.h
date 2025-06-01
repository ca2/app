// created by Camilo on 2025-06-01 01:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/graphics/image/pixmap.h"


namespace image
{


   class CLASS_DECL_AURA buffer :
      virtual public ::particle,
      virtual public ::pixmap
   {
   public:


      ::pixmap *                             m_ppixmapLock;
      ::image::enum_copy_disposition         m_ecopydisposition;
      ::memory							            m_memory;


      buffer();
      ~buffer() override;


      virtual buffer * lock(int stride, enum_copy_disposition ecopydisposition, ::pixmap * ppixmapLock);
      virtual buffer * no_padding_lock(enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock);
      virtual buffer * source_lock(enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock);
      
      void unlock();


   };


} // namespace image



