#pragma once


#ifdef __cplusplus

#define mutant_size ::size

#else

#define mutant_size  SIZE

#endif


#pragma pack(push, image_header, 1)


#ifdef __cplusplus
struct CLASS_DECL_AURA image_header
#else
struct image_header
#endif
{

   e_image_type         m_etype;
   COLORREF             m_cr;
   mutant_size          m_size;


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
   ::size size() const { return m_size; }

   void reset()
   {

      m_size.Null();
      m_cr = 0;
      m_etype = image_type_complex;


   }


#endif


};


#pragma pack(pop, image_header)



