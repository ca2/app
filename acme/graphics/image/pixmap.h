// Split to pixmap_t.h by camilo on 2026-07-24 01:46 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap_lease.h"


class CLASS_DECL_ACME pixmap :
   public pixmap_t,
   virtual public ::particle
{
public:

   
   memory                  m_memoryPixmap;
   ::interlocked_count     m_interlockedcountMap;


   pixmap();
   ~pixmap() override;


   virtual void create(const ::i32_size &size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG,
                       ::i32 iGoodStride = -1, bool bPreserve = false);

   virtual void create_from_data(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan,
                                 ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, bool bPreserve = false);


   inline bool is_ok() const { return ::particle::is_ok() && this->_is_ok(); }
   virtual bool _is_ok() const override;

   virtual pixmap_lease map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map_base to m_pcolorref before manipulate it

   //virtual void unmap(bool bDoUnmap = false) const; // some implementations may require to unmap from m_pcolorref to update *os* bitmap
   virtual void mult_alpha_fast();

   virtual void set_exif_orientation(int iExifOrientation);

   virtual void on_load_image();

   virtual void defer_update_image();

   virtual ::image::image_extension * get_extension();

   virtual void copy(const ::i32_size &size, const ::image32_t *pimage32, ::i32 iScan);

   virtual void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan);

protected:

   friend class pixmap_lease;

   virtual void _map(bool bApplyAlphaTransform =
                           true); // some implementations may requrire to map_base to m_pcolorref before manipulate it
   
   
   virtual bool _on_map(bool bApplyAlphaTransform = true);

   virtual void
      _unmap(bool bDoUnmap = false); // some implementations may require to unmap from m_pcolorref to update *os* bitmap

   virtual bool
   _on_unmap(bool bDoUnmap = false); // some implementations may require to unmap from m_pcolorref to update *os* bitmap

};


//#pragma pack(pop, pixmap)



using pixmap_pointer = ::pointer < ::pixmap >;

inline void image32_t::copy(const ::i32_size & size, ::i32 iStrideDst, const ::pixmap_t * ppixmapSrc)
{
   
   copy(size.minimum(ppixmapSrc->size()), iStrideDst, ppixmapSrc->m_pimage32, ppixmapSrc->m_iScan);

}



inline void image32_t::copy(const ::pixmap_t* p)
{
   copy(::i32_point(), p->size(), p->width() * 4, p->image32(), p->m_iScan);
}



