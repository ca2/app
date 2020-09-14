#pragma once


class CLASS_DECL_AURA image_frame_array :
   virtual public __pointer_array(::image_frame)
{
public:


   ::image_pointer      m_pimage;
   tick                 m_tickTotal;
   ::count              m_countLoop; // 0 - infinite loop
   ::index              m_iLoop;
   int                  m_iTransparentIndex;
   bool                 m_bTransparent;
   COLORREF             m_crTransparent;
   COLORREF             m_crBack;
   BYTE                 m_backgroundIndex;
   ::size               m_sizeLogical;
   ::size               m_size;
   ::image_pointer      m_pimageCompose;
   colorref_array       m_colorrefa;


   image_frame_array();
   virtual ~image_frame_array();


   const ::size size() { return m_size; }
   const ::size & size() const { return m_size; }

   ::rect rect(const ::point & point = nullptr) { return ::rect(point, m_size); }
   const ::rect rect(const ::point & point = nullptr) const { return ::rect(point, m_size); }

   virtual ::image_pointer calc_current_frame(image_dynamic & dynamic);


   inline image_extension * extension() { return m_pimage->extension(); }

};
