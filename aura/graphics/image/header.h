#pragma once


#include "acme/primitive/geometry2d/size.h"


#pragma pack(push, image_header, 1)


#ifdef __cplusplus
struct CLASS_DECL_AURA image_header
#else
struct image_header
#endif
{


   e_image_type               m_etype;
   ::color::color             m_cr;
   ::size_i32                 m_size;


#ifdef __cplusplus


   image_header() :
      m_size(0, 0)
   {

      m_etype = image_type_complex;
      m_cr = 0;

   }

   bool operator == (const image_header & d) const
   {

      if (m_etype != d.m_etype)
         return false;

      if (m_size != d.m_size)
         return false;

      switch (m_etype)
      {
      case image_type_plain_color:
         return m_cr == d.m_cr;
      default:
         return true;
      };

   }

   bool operator != (const image_header & d) const
   {
      return !operator ==(d);
   }

   int width() const { return m_size.cx; }
   int height() const { return m_size.cy; }
   int area() const { return m_size.area(); }
   ::size_i32 size() const { return m_size; }

   void reset()
   {

      m_size.Null();
      m_cr = 0;
      m_etype = image_type_complex;


   }


#endif


};


template < >
inline uptr uptr_hash<const ::image_header&>(const ::image_header& key)
{
   ::u32 u = (::u32)key.m_etype;
   if (key.m_etype == ::image_type_plain_color)
   {
      u |= key.m_cr;
   }
   u |= key.m_size.cx << 16;
   u |= key.m_size.cy << 24;
   return u;
}



#pragma pack(pop, image_header)



