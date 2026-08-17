//
// Created by camilo on 2023-10-06 20:16 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "pixmap.h"
#include "acme/graphics/draw2d/task_tool.h"
#include "acme/graphics/graphics/double_pass_scale.h"
#include "acme/graphics/image/_exif.h"
#include "acme/parallelization/tools.h"



pixmap::pixmap()
{

   m_iExifOrientation = 0;

}


pixmap::~pixmap()
{


}


void pixmap::create_as_descriptor(const ::i32_size & size, ::enum_flag eflagCreate, ::i32 iGoodStride)
{

   if (size == m_sizeRaw && size == m_size)
   {

      return;

   }

   destroy();

   m_sizeRaw = size;

   m_size = size;

   m_iScan = size.cx * 4;

   if (iGoodStride >= m_iScan)
   {

      m_iScan = iGoodStride;

   }

   m_eflagElement = eflagCreate;

   m_estatus = success;

}


void pixmap::create_from_data(const ::i32_size & size, const ::image32_t * ppixmap32, ::i32 iScan,
                              ::enum_flag eflagCreate, bool bPreserve)
{

   create_as_descriptor(size, DEFAULT_CREATE_IMAGE_FLAG, iScan);

   copy(size, ppixmap32, m_iScan);

}


#define byte_clip2(i) (i)
void pixmap::mult_alpha_fast()
{
   auto ppixmap = this->map();

   //::u8 *dst = (::u8 *)ppixmap->data();
   //::i64 size = scan_area();


   //  >> 2 instead of >> 2 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) *
   //  (254/255) > 255

   auto h = ppixmap->height();

   auto w = ppixmap->width();

   for (::i32 iLine = 0; iLine < ppixmap->height(); iLine++)
   {

      auto ppixmap32Line = ppixmap->line_data(iLine);

      auto x = ppixmap->width();

      while (x > 0)
      {
         auto dst = (::u8 *)ppixmap32Line;
         if (dst[3] == 0)
         {
            *((image32_t *)dst) = {};
         }
         else if (dst[3] != 255)
         {
            dst[0] = byte_clip2(((::i32)dst[0] * (::i32)dst[3]) >> 8);
            dst[1] = byte_clip2(((::i32)dst[1] * (::i32)dst[3]) >> 8);
            dst[2] = byte_clip2(((::i32)dst[2] * (::i32)dst[3]) >> 8);
         }
         x--;
         ppixmap32Line++;
      }
   }

   // return true;
}

bool pixmap::_is_ok() const 
{
   return ::particle::_is_ok() && pixmap_t::is_ok();
}

//
// pixmap_lease pixmap::map(bool bApplyTransform) const
// {
//
//    return {(::pixmap *)this, bApplyTransform};
//
// }
//
//
// pixmap_lease pixmap::map(const ::i32_rectangle & rectangle) const
// {
//
//    return { (::pixmap*)this, rectangle };
//
// }


bool pixmap::_on_map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform)
{

   if (m_interlockedcountMap > 0)
   {

      if (!m_bMapped)
      {

         throw ::exception(error_wrong_state);

      }

   }
   
   m_interlockedcountMap++;

   if (m_bMapped)
   {

      return false;

   }

   return true;

}

pixmap_lease pixmap::map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform)
{

   return {this, rectangle, bApplyAlphaTransform};

}


void pixmap::_map(const ::i32_rectangle & rectangle, bool bApplyTransform)
{

   if (!_on_map(rectangle, bApplyTransform))
   {

      return;

   }

   auto ppixmap32Owned = (::image32_t *)m_memoryPixmap.data();

   auto bUsingOwnedMemory =
      ::is_set(ppixmap32Owned)
      && m_pimage32Raw == ppixmap32Owned;

   if (m_iScan < m_sizeRaw.cx * 4)
   {

      m_iScan = m_sizeRaw.cx * 4;

   }

   if (!m_pimage32Raw
      || !m_pimage32
      || (bUsingOwnedMemory && m_memoryPixmap.size() < m_iScan * m_sizeRaw.cy))
   {

      m_memoryPixmap.set_size(m_iScan * m_sizeRaw.cy);

      m_pimage32Raw = (::image32_t *)m_memoryPixmap.data();

   }

   if (rectangle.is_empty())
   {

      pixmap_map();

   }
   else
   {

      pixmap_map(rectangle);

   }

   m_bMapped = true;

}


void pixmap::set_exif_orientation(int iExifOrientation)
{



}


// void pixmap::on_load_image()
// {
//
//
// }


//void pixmap::defer_update_image()
//{
//
//
//}

//
// ::pixmap::image_extension * pixmap::get_extension()
// {
//
//    return nullptr;
//
// }
//

void pixmap::create_isotropic(::pixmap * ppixmap, ::f64 fIsotropicRate)
{

   ::i32 cx = (::i32)(fIsotropicRate * this->width());

   ::i32 cy = (::i32)(fIsotropicRate * this->height());

   ppixmap->create_as_descriptor({cx, cy});

   //if (::parallelization::get_priority() == ::e_priority_idle)
   //{

     // map();

      C2PassScale < CBlackmanFilter > scale(1.0);

      scale.Scale(
         ppixmap->image32(),
         ppixmap->color_indexes(),
         ppixmap->width(),
         ppixmap->height(),
         ppixmap->scan_size(),
         image32(),
         width(),
         height(),
         scan_size()
      );

   // }
   // else
   // {
   //
   //    auto pgraphicsImage = ppixmap->acquire_graphics();
   //
   //    pgraphicsImage->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
   //
   //    ::pixmap::image_source imagesource(pgraphicsImage, ::i32_rectangle_dimension(0, 0, width(), height()));
   //
   //    ::pixmap::image_drawing_options imagedrawingoptions(::i32_rectangle_dimension(0, 0, cx, cy));
   //
   //    ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   //    pgraphicsImage->draw(imagedrawing);
   //
   // }
   //
   // ppixmap->set_mipmap(ppixmap->m_emipmap);

   //return true;

}

void pixmap::copy(const pixmap_t * ppixmap)
{

   create_as_descriptor(ppixmap->size());

   auto ppixmapThis = this->map();

   copy(ppixmap->size(), ppixmap->m_pimage32, ppixmap->m_iScan);

}


void pixmap::copy(const ::i32_size &size, const ::image32_t *ppixmap32, ::i32 iScan)
{

   auto ppixmapThis = this->map();

   copy(size, ppixmap32, iScan);
   
}




void pixmap::on_load_image(const image32_t *ppixmap32, const ::i32_size &size, int iScan)
{

   create_as_descriptor(size, DEFAULT_CREATE_IMAGE_FLAG, iScan);

   copy(size, ppixmap32, iScan);

}


//
//void pixmap::unmap(bool bDoUnmap) const
//{
//
//   ((pixmap *)this)->_unmap(bDoUnmap);
//
//}


bool pixmap::_on_unmap(bool bDoUnmap)
{

   if (m_interlockedcountMap <= 0)
   {

      throw ::exception(error_wrong_state);

   }

   m_interlockedcountMap--;

   if (m_interlockedcountMap > 0)
   {

      return false;

   }

   if ((!m_bMapped || !m_pimage32Raw) && bDoUnmap)
   {

      throw ::exception(error_wrong_state);
   }

   return true;

}


void pixmap::_unmap(bool bDoUnmap)
{

   if (!_on_unmap(bDoUnmap))
   {

      return;

   }

   if (bDoUnmap)
   {

      m_pimage32Raw = nullptr;
      m_pimage32 = nullptr;

   }

   m_bMapped = false;

}


//::pixmap::lock pixmap::lock(::i32 stride, ::pixmap::enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
//{
//
//   //m_ppixmapLock = ppixmapLock;
//
//   m_ecopydisposition = ecopydisposition;
//
//   if (//m_ppixmapLock->m_iScan == stride 
//      m_iScan == stride
//      && m_ecopydisposition == ::pixmap::e_copy_disposition_none)
//   {
//
//      //reference(*m_ppixmapLock);
//
//
//
//   }
//   else
//   {
//         
//      m_memoryPixmap.set_size(scan_area_in_bytes());
//
//      m_pimage32Raw = (::image32_t *) m_memoryPixmap.data();
//
//      m_pimage32 = m_pimage32Raw;
//
//      ///::pixmap_t::create(m_memory, m_ppixmapLock->size(), stride);
//
//   }
//
//   //return this;
//      
//}
//
//
//::pixmap::lock pixmap::no_padding_lock(::pixmap::enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
//{
//      
//   return lock(ppixmapLock->width() * 4, ecopydisposition, ppixmapLock);
//
//}
//
//
//::pixmap::lock pixmap::source_lock(::pixmap::enum_copy_disposition ecopydisposition, ::pixmap* ppixmapLock)
//{
//
//   return lock(ppixmapLock->m_iScan, ecopydisposition, ppixmapLock);
//
//}
//
//   
//void pixmap::unlock(::pixmap::lock * ppixmaplock)
//{
//
//   if (ppixmaplock->data() != this->data())
//   {
//
//      p->pixmap_t::copy(this, m_ecopydisposition);
//
//   }
//
//}


CLASS_DECL_ACME::string _001_image32_diagnostics(const ::i32_size & size, const image32_t * ppixmap32, int iScan)
{

   ::string strImage32;

   strImage32.formatf("\n\n   ppixmap32=%p (%d,%d) scan=%d,", ppixmap32, size.cx, size.cy, iScan);

   auto pu8 = (::u8 *)ppixmap32;

   if (!pu8)
   {

      return strImage32;

   }

   ::collection::count opaqueCount = 0;
   ::collection::count transparentCount = 0;
   ::collection::count translucentCount = 0;
   ::collection::count pixelCount = 0;

   for (int i = 0; i < size.cy; i++)
   {

      auto pu8Line = pu8 + (iScan * i);

      auto p = pu8Line;

      for (int j = 0; j < size.cx; j++)
      {

         auto r = p[0];
         auto g = p[1];
         auto b = p[2];
         auto a = p[3];

         if (a == 255)
         {

            opaqueCount++;

         }
         else if (a == 0)
         {

            transparentCount++;

         }
         else
         {

            translucentCount++;

         }

         p += 4;

         pixelCount++;

      }

   }

   strImage32.append_formatf("\n   pixel=%llu opaque=%llu transp=%llu transl=%llu\n", pixelCount, opaqueCount, transparentCount, translucentCount);

   return strImage32;

}


::pixmap_pointer pixmap::get_resized_pixmap(const ::i32_size & size)
{

   return this;

}








void pixmap::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc)
{

   map();

   echannelDst = (::color::enum_channel)(((::i32)echannelDst) % 4);
   echannelSrc = (::color::enum_channel)(((::i32)echannelSrc) % 4);

   if (echannelDst == echannelSrc)
   {

      //return true;
      return;

   }

   ::u8* pdataDst = (::u8*)data() + ((::i32)echannelDst);

   ::u8* pdataSrc = (::u8*)data() + ((::i32)echannelSrc);

   for (::i32 y = 0; y < height(); y++)
   {

      ::u8* pdst = &pdataDst[m_iScan * y];

      ::u8* psrc = &pdataSrc[m_iScan * y];

      for (::i32 x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}


void pixmap::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::pixmap  * ppixmap)
{

   if (size() != ppixmap->size())
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   auto ppixmapThis = map();

   if (m_pimage32 == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   auto ppixmapPixmap = ppixmap->map();

   if (ppixmapPixmap->image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   echannelDst = (::color::enum_channel)(((::i32)echannelDst) % 4);
   echannelSrc = (::color::enum_channel)(((::i32)echannelSrc) % 4);

   ::u8* pdataDst = (::u8*)data() + ((::i32)echannelDst);

   ::u8* pdataSrc = (::u8*)ppixmapPixmap->data() + ((::i32)echannelSrc);

   for (::i32 y = 0; y < height(); y++)
   {

      ::u8* pdst = &pdataDst[m_iScan * y];

      ::u8* psrc = &pdataSrc[ppixmapPixmap->m_iScan * y];

      for (::i32 x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}




void pixmap::blend2(const ::i32_point& pointDstParam, ::pixmap * ppixmapSrc, const ::i32_point& pointSrcParam, const ::i32_size& sizeParam, ::u8 bA)
{

   ::pixmap * ppixmapDst = this;

   //ppixmapDst->map();

//   ppixmapSrc->map();

   ::i32_point pointDst(pointDstParam);

   ::i32_point pointSrc(pointSrcParam);

   ::i32_size size(sizeParam);

   pointDst += m_point;

   if (pointSrc.x < 0)
   {
      pointDst.x -= pointSrc.x;
      pointSrc.x = 0;
   }

   if (pointSrc.y < 0)
   {
      pointDst.y -= pointSrc.y;
      pointSrc.y = 0;
   }

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {

      return;

   }
      //return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {
   //   return true;

      return;
   }

   ::i32 xEnd = minimum(size.cx, minimum(ppixmapSrc->width() - pointSrc.x, ppixmapDst->width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmapSrc->height() - pointSrc.y, ppixmapDst->height() - pointDst.y));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

   ::i32 scanSrc = ppixmapSrc->m_iScan;

   ::u8 * pdst = ((::u8 *)ppixmapDst->image32()) + (scanDst * pointDst.y) + (pointDst.x * sizeof(image32_t));

   ::u8 * psrc = ((::u8 *)ppixmapSrc->image32()) + (scanSrc * pointSrc.y) + (pointSrc.x * sizeof(image32_t));

   ::u8 * pdst2;

   ::u8 * psrc2;

   if (bA == 0)
   {

   }
   else if (bA == 255)
   {

      for (::i32 y = 0; y < yEnd; y++)
      {

         pdst2 = pdst + (scanDst * y);

         psrc2 = psrc + (scanSrc * y);

         for (::i32 x = 0; x < xEnd; x++)
         {

            ::i32 aDst = pdst2[3];

            ::i32 aSrc = psrc2[3];

            if (aDst == 0)
            {

            }
            else if (aSrc == 0)
            {

               *((image32_t *)pdst2) = {};

            }
            else
            {

               //::i32 r = (pdst2[0] * 255) / aDst;
               //::i32 g = (pdst2[1] * 255) / aDst;
               //::i32 b = (pdst2[2] * 255) / aDst;

               //::i32 a = aSrc * aDst;

               //pdst2[0] = (r * a) >> 16;
               //pdst2[1] = (g * a) >> 16;
               //pdst2[2] = (b * a) >> 16;
               //pdst2[3] = a >> 8;
               pdst2[0] = ((::i32) pdst2[0] * aSrc) / 255;
               pdst2[1] = ((::i32) pdst2[1] * aSrc) / 255;
               pdst2[2] = ((::i32) pdst2[2] * aSrc) / 255;
               pdst2[3] = (aDst * aSrc) / 255;

            }

            pdst2 += 4;

            psrc2 += 4;

         }

      }

   }
   else
   {
      for (::i32 y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memory_copy(pdst2, psrc2, xEnd * 4);
         for (::i32 x = 0; x < xEnd; x++)
         {

            //*pdst2 = *psrc2;

            //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
            //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
            //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
            //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
            //::u8 acomplement = (~psrc2[3] * bA) >> 8;
            //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
            //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
            //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
            //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
            ::u8 acomplement = (~psrc2[3] * bA) >> 8;
            pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
            pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
            pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
            pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);

            pdst2 += 4;

            psrc2 += 4;

         }
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }

   }

   //return true;

}


void pixmap::blend(const ::i32_point& pointDst, ::pixmap * ppixmapSrc, const ::i32_point& pointSrc, const ::i32_size& size)
{

   return blend(pointDst, ppixmapSrc, pointSrc, size, 255);

}


void pixmap::blend(const ::i32_point& pointDstParam, ::pixmap * ppixmapSrc, const ::i32_point& pointSrcParam, const ::i32_size& sizeParam, ::u8 bA)
{

   ::pixmap * ppixmapDst = this;

   ::i32_point pointDst(pointDstParam);

   ::i32_point pointSrc(pointSrcParam);

   ::i32_size size(sizeParam);


   ppixmapDst->map();

   ppixmapSrc->map();

   pointDst += m_point;

   if (pointSrc.x < 0)
   {
      pointDst.x -= pointSrc.x;
      pointSrc.x = 0;
   }

   if (pointSrc.y < 0)
   {
      pointDst.y -= pointSrc.y;
      pointSrc.y = 0;
   }

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {

      //  return true;

      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      //return true;

      return;

   }

   ::i32 xEnd = minimum(size.cx, minimum(ppixmapSrc->width() - pointSrc.x, ppixmapDst->width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmapSrc->height() - pointSrc.y, ppixmapDst->height() - pointDst.y));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

   ::i32 scanSrc = ppixmapSrc->m_iScan;


   ::u8* pdst2;

   ::u8* psrc2;

#ifdef __APPLE__
   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * (ppixmapDst->height() - pointDst.y - yEnd) + pointDst.x * sizeof(image32_t)];

   ::u8* psrc = &((::u8*)ppixmapSrc->image32())[scanSrc * (ppixmapSrc->height() - pointSrc.y - yEnd) + pointSrc.x * sizeof(image32_t)];

#else

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   ::u8* psrc = &((::u8*)ppixmapSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

#endif

   bool bFontListBlend = true;

   if (bFontListBlend)
   {

      if (bA == 0)
      {

      }
      else if (bA == 255)
      {

         for (::i32 y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (::i32 x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               ::u8 acomplement = ~psrc2[3];
               pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }
      }
      else
      {
         for (::i32 y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (::i32 x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               //::u8 acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               ::u8 acomplement = (~psrc2[3] * bA) >> 8;
               pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
               pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
               pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
               pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }

      }

      // bFontListData

   }
   else
   {

      // !bFontListData
      // bBouncingBall...

      if (bA == 0)
      {

      }
      else if (bA == 255)
      {

         for (::i32 y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (::i32 x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               ::u8 a = pdst2[3];
               ::u8 alpha = psrc2[3];
               if (a == 0)
               {

               }
               else if (alpha == 0)
               {

                  *((image32_t *)pdst2) = {};

               }
               else
               {

                  //::i32 d0 = pdst2[0] * 255 / a;
                  //::i32 d1 = pdst2[1] * 255 / a;
                  //::i32 d2 = pdst2[2] * 255 / a;

                  //::i32 s0 = psrc2[0] * 255 / alpha;
                  //::i32 s1 = psrc2[1] * 255 / alpha;
                  //::i32 s2 = psrc2[2] * 255 / alpha;

                  //d0 = ((s0 * a) + (d0 * alpha)) >> 8;
                  //d1 = ((s1 * a) + (d1 * alpha)) >> 8;
                  //d2 = ((s2 * a) + (d2 * alpha)) >> 8;
                  //pdst2[3] = ((psrc2[3] * a) + (pdst2[3] * alpha)) >> 8;

                  //pdst[0] = (d0 * pdst2[3]) >> 8;
                  //pdst[1] = (d1 * pdst2[3]) >> 8;
                  //pdst[2] = (d2 * pdst2[3]) >> 8;

                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);

                  pdst2[0] = (pdst2[0] * alpha) >> 8;
                  pdst2[1] = (pdst2[1] * alpha) >> 8;
                  pdst2[2] = (pdst2[2] * alpha) >> 8;
                  pdst2[3] = (pdst2[3] * alpha) >> 8;
               }



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }
      }
      else
      {
         for (::i32 y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (::i32 x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               //::u8 acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               ::u8 acomplement = (~psrc2[3] * bA) >> 8;
               pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
               pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
               pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
               pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }

      }

   }

   //return true;

}


void pixmap::precision_blend(const ::i32_point& pointDst, ::pixmap * ppixmapSrc, const ::i32_point& pointSrc, const ::i32_size& size)
{

   return precision_blend(pointDst, ppixmapSrc, pointSrc, size, 255);

}


void pixmap::precision_blend(const ::i32_point& pointDstParam, ::pixmap * ppixmapSrc, const ::i32_point& pointSrcParam, const ::i32_size& sizeParam, ::u8 bA)
{

   ::pixmap * ppixmapDst = this;

   ::i32_point pointDst(pointDstParam);

   ::i32_point pointSrc(pointSrcParam);

   ::i32_size size(sizeParam);

   auto ppixmapTarget = ppixmapDst->map();

   auto ppixmapSource = ppixmapSrc->map();

   pointDst += m_point;

   if (pointSrc.x < 0)
   {
      pointDst.x -= pointSrc.x;
      pointSrc.x = 0;
   }

   if (pointSrc.y < 0)
   {
      pointDst.y -= pointSrc.y;
      pointSrc.y = 0;
   }

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {

      //return true;

      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      //return true;

      return;

   }

   ::i32 xEnd = minimum(size.cx, minimum(ppixmapSrc->width() - pointSrc.x, ppixmapDst->width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmapSrc->height() - pointSrc.y, ppixmapDst->height() - pointDst.y));

   if (xEnd < 0)
   {
    
      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

   ::i32 scanSrc = ppixmapSrc->m_iScan;

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   ::u8* psrc = &((::u8*)ppixmapSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   ::u8* pdst2;

   ::u8* psrc2;

   if (bA == 0)
   {

   }
   else if (bA == 255)
   {

      for (::i32 y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memory_copy(pdst2, psrc2, xEnd * 4);
         for (::i32 x = 0; x < xEnd; x++)
         {

            //*pdst2 = *psrc2;

            //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
            //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
            //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
            //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
            ::u8 acomplement = ~psrc2[3];
            pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) / 255);
            pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) / 255);
            pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) / 255);
            pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) / 255);



            pdst2 += 4;

            psrc2 += 4;

         }
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }
   }
   else
   {
      for (::i32 y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memory_copy(pdst2, psrc2, xEnd * 4);
         for (::i32 x = 0; x < xEnd; x++)
         {

            //*pdst2 = *psrc2;

            //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
            //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
            //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
            //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
            //::u8 acomplement = (~psrc2[3] * bA) >> 8;
            //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
            //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
            //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
            //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
            ::u8 acomplement = (~psrc2[3] * bA) / 255;
            pdst2[0] = byte_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) / 255);
            pdst2[1] = byte_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) / 255);
            pdst2[2] = byte_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) / 255);
            pdst2[3] = byte_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) / 255);



            pdst2 += 4;

            psrc2 += 4;

         }
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }

   }

   //return true;

}


void pixmap::fork_blend(const ::i32_point& pointDst, ::pixmap * ppixmapSrc, const ::i32_point& pointSrc, const ::i32_size& size)
{

   //return 
   
   fork_blend(pointDst, ppixmapSrc, pointSrc, size, 255);

}


void pixmap::fork_blend(const ::i32_point& pointDstParam, ::pixmap * ppixmapSrc, const ::i32_point& pointSrcParam, const ::i32_size& sizeParam, ::u8 bA)
{

   if (bA == 0)
   {

      //return true;

      return;

   }

   ::pixmap * ppixmapDst = this;

   ::i32_point pointDst(pointDstParam);

   ::i32_point pointSrc(pointSrcParam);

   ::i32_size size(sizeParam);

   ppixmapDst->map();

   ppixmapSrc->map();

   pointDst += m_point;

   if (pointSrc.x < 0)
   {
      pointDst.x -= pointSrc.x;
      pointSrc.x = 0;
   }

   if (pointSrc.y < 0)
   {
      pointDst.y -= pointSrc.y;
      pointSrc.y = 0;
   }

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointSrc.x -= pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {

      //return true;

      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointSrc.y -= pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      //return true;

   }

   ::i32 xEnd = minimum(size.cx, minimum(ppixmapSrc->width() - pointSrc.x, ppixmapDst->width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmapSrc->height() - pointSrc.y, ppixmapDst->height() - pointDst.y));

   if (xEnd <= 0)
   {

      //return false;

      return;

   }

   if (yEnd <= 0)
   {

      //return false;

      return;

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

   ::i32 scanSrc = ppixmapSrc->m_iScan;

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   ::u8* psrc = &((::u8*)ppixmapSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   //::u8 * pdst5; // dst opacity map if available // opacity map does not make sense for images that machine

   ::u8* psrcOpacity; // src opacity map if available

   ::u8* psrcTransparency; // src transparency map if available

   if (ppixmapSrc->m_memoryPixmap.size() == ppixmapSrc->area() * 2)
   {

      psrcOpacity = &ppixmapSrc->m_memoryPixmap.data()[ppixmapSrc->width() * pointSrc.y + pointSrc.x];

   }
   else
   {

      psrcOpacity = nullptr;

   }

   if (ppixmapSrc->m_memoryPixmap.size() == ppixmapSrc->area() * 2)
   {

      psrcTransparency =
         &ppixmapSrc->m_memoryPixmap.data()[ppixmapSrc->area() + ppixmapSrc->width() * pointSrc.y + pointSrc.x];

   }
   else
   {

      psrcTransparency = nullptr;

   }

   //::pointer<::aura::system>psystem = system();

   auto pgroup = system()->task_group();

   synchronous_lock slGroup(pgroup->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto ptool = system()->task_tool(::e_task_tool_draw2d);

   synchronous_lock slTool(ptool->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   if (!pgroup || !ptool)
   {

      return blend(pointDst, ppixmapSrc, pointSrc, size, bA);

   }

   ::i32 y = 0;

   pgroup->select_tool(ptool);

   pgroup->prepare(::e_task_op_tool, yEnd);

   for (auto& ptoolitem : ptool->m_itema)
   {

      ::pointer<::draw2d::task_tool_item>pitem = ptoolitem;

      pitem->m_eop = ::draw2d::task_tool_item::op_blend;

      pitem->m_w = ppixmapSrc->width();

      pitem->m_h = ppixmapSrc->height();

      pitem->m_ySkip = (::i32)(pgroup->task_count());

      pitem->m_y = y;

      pitem->m_yEnd = yEnd;

      pitem->m_bA = bA;

      pitem->m_x = 0;

      pitem->m_xEnd = xEnd;

      pitem->m_pdst2 = pdst;

      pitem->m_psrc2 = psrc;

      pitem->m_psrcOpacity = psrcOpacity;

      pitem->m_psrcTransparency = psrcTransparency;

      pitem->m_scanSrc = scanSrc;

      pitem->m_scanDst = scanDst;

      y++;

   }

   pgroup->call();

   //return true;

}


void pixmap::draw_ignore_alpha(const ::i32_point& pointDstParam, ::pixmap * ppixmap, const ::i32_rectangle& rectangleSrcParam)
{

   ::i32_point pointDst(pointDstParam);

   ::i32_point pointSrc(rectangleSrcParam.top_left());

   ::i32_size size(rectangleSrcParam.size());

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {
    
      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      return;

   }

   ::i32 xEnd = minimum(size.cx, minimum(ppixmap->width() - pointSrc.x, width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmap->height() - pointSrc.y, height() - pointDst.y));

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   ::i32 s1 = m_iScan / sizeof(image32_t);

   ::i32 s2 = ppixmap->m_iScan / sizeof(image32_t);

   image32_t* pdst = &image32()[s1 * pointDst.y] + pointDst.x;

   image32_t* psrc = &ppixmap->image32()[s2 * pointSrc.y] + pointSrc.x;

   image32_t* pdst2;

   image32_t* psrc2;

   ::i32 i = 0;

   for (::i32 y = 0; y < yEnd; y++)
   {

      pdst2 = &pdst[s1 * y];

      psrc2 = &psrc[s2 * y];

      for (::i32 x = 0; x < xEnd; x++)
      {

         if (psrc2->u8_opacity(ppixmap->color_indexes()) == 0)
         {
            i++;
         }
         else
         {
            *pdst2 = *psrc2;
         }

         pdst2++;

         psrc2++;

      }

   }

   //return true;

}


void pixmap::blend(const ::i32_point& pointDstParam, ::pixmap * ppixmapSrc, const ::i32_point& pointSrcParam, ::pixmap * ppixmapAlf, const ::i32_point& pointDstAlfParam, const ::i32_size& sizeParam)
{

   ::pixmap * ppixmapDst = this;

   ppixmapDst->map();
   ppixmapSrc->map();
   ppixmapAlf->map();

   ::i32_point pointDst(pointDstParam);

   ::i32_point pointSrc(pointSrcParam);

   ::i32_point pointDstAlf(pointDstAlfParam);

   ::i32_size size(sizeParam);

   if (pointSrc.x < 0)
   {
      pointDst.x -= pointSrc.x;
      pointDstAlf.x -= pointSrc.x;
      pointSrc.x = 0;
   }

   if (pointSrc.y < 0)
   {
      pointDst.y -= pointSrc.y;
      pointDstAlf.y -= pointSrc.y;
      pointSrc.y = 0;
   }

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {
    
      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      return;

   }

   ::i32 xEnd = minimum(size.cx, minimum(ppixmapSrc->width() - pointSrc.x, ppixmapDst->width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmapSrc->height() - pointSrc.y, ppixmapDst->height() - pointDst.y));

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   if (pointDstAlf.x < 0)
   {

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

   ::i32 scanSrc = ppixmapSrc->m_iScan;

   ::i32 scanAlf = ppixmapAlf->m_iScan;

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   ::u8* psrc = &((::u8*)ppixmapSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   ::u8* palf = &((::u8*)ppixmapAlf->image32())[-scanAlf * pointDstAlf.y - pointDstAlf.x * sizeof(image32_t)] + 3;

   ::u8* pdst2;

   ::u8* psrc2;

   //::u8* palf2;

   //::i32 x1;
   //::i32 x2;
   //::i32 y1;
   //::i32 y2;

   //x1 = pointDstAlf.x;
   //x2 = ppixmapAlf->width() + x1;
   //y1 = pointDstAlf.y;
   //y2 = ppixmapAlf->height() + y1;


   //::i32 a;

   for (::i32 y = 0; y < yEnd; y++)
   {

      pdst2 = (::u8*)&pdst[scanDst * y];

      psrc2 = (::u8*)&psrc[scanSrc * y];

      //palf2 = (::u8*)&palf[scanAlf * y];

      for (::i32 x = 0; x < xEnd; x++)
      {

         if (psrc2[3] > 0)
         {
            //               if (false && x >= x1 && x < x2 && y >= y1 && y < y2)
            //               {
            //
            //                  a = (*palf2 * psrc2[3]) / 255;
            //                  a = psrc2[3];
            //                  //a = (::i32) (::u8) sqrt((::f32) (*palf2 * psrc2[3]));
            //                  pdst2[3] = (::u8)maximum(a, pdst2[3]);
            //                  //pdst2[3] = (::u8)((((::i32)psrc2[3] - (::i32)pdst2[3]) * a + ((::i32)pdst2[3] * 255)) / 255);
            //                  pdst2[3] = (::u8)(maximum(psrc2[3], pdst2[3]));
            //
            //                  //                  if (a > 0)
            //                  {
            //
            //                     pdst2[0] = (::u8)((((::i32)psrc2[0] - (::i32)pdst2[0]) * a + ((::i32)pdst2[0] * 255)) / 255);
            //                     pdst2[1] = (::u8)((((::i32)psrc2[1] - (::i32)pdst2[1]) * a + ((::i32)pdst2[1] * 255)) / 255);
            //                     pdst2[2] = (::u8)((((::i32)psrc2[2] - (::i32)pdst2[2]) * a + ((::i32)pdst2[2] * 255)) / 255);
            //
            //                  }
            //
            //               }
            //               else
            {

               //pdst2[3] = (::u8)(maximum(psrc2[3], pdst2[3]));
               //pdst2[3] = (::u8)((((::i32)psrc2[3] - (::i32)pdst2[3]) * (::i32)psrc2[3] + ((::i32)pdst2[3] * 255)) / 255);
               //pdst2[0] = (::u8)((((::i32)psrc2[0] - (::i32)pdst2[0]) * (::i32)psrc2[3] + ((::i32)pdst2[0] * 255)) / 255);
               //pdst2[1] = (::u8)((((::i32)psrc2[1] - (::i32)pdst2[1]) * (::i32)psrc2[3] + ((::i32)pdst2[1] * 255)) / 255);
               //pdst2[2] = (::u8)((((::i32)psrc2[2] - (::i32)pdst2[2]) * (::i32)psrc2[3] + ((::i32)pdst2[2] * 255)) / 255);
               pdst2[3] = (::u8)(maximum(((((::i32)psrc2[3] - (::i32)pdst2[3]) * (::i32)psrc2[3] + ((::i32)pdst2[3] * 255)) / 255), pdst2[3]));
               pdst2[0] = (::u8)((((::i32)psrc2[0] - (::i32)pdst2[0]) * (::i32)psrc2[3] + ((::i32)pdst2[0] * 255)) / 255);
               pdst2[1] = (::u8)((((::i32)psrc2[1] - (::i32)pdst2[1]) * (::i32)psrc2[3] + ((::i32)pdst2[1] * 255)) / 255);
               pdst2[2] = (::u8)((((::i32)psrc2[2] - (::i32)pdst2[2]) * (::i32)psrc2[3] + ((::i32)pdst2[2] * 255)) / 255);

            }
         }


         pdst2 += 4;

         psrc2 += 4;

         //palf2 += 4;


      }

   }

   //return true;

}

/*
void pixmap::blend(const ::i32_point & pointDst,::pixmap * ppixmapSrc, const ::i32_point & pointSrc, const ::i32_size & size)
{

   ::pixmap * ppixmapDst = this;

   ppixmapDst->map();
   ppixmapSrc->map();


   if (pointSrc.x < 0)
   {
      pointDst.x -= pointSrc.x;
      pointSrc.x = 0;
   }

   if (pointSrc.y < 0)
   {
      pointDst.y -= pointSrc.y;
      pointSrc.y = 0;
   }

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
      return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return true;

   ::i32 xEnd = minimum(size.cx, minimum(ppixmapSrc->width() - pointSrc.x, ppixmapDst->width() - pointDst.x));

   ::i32 yEnd = minimum(size.cy, minimum(ppixmapSrc->height() - pointSrc.y, ppixmapDst->height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;



   ::i32 scanDst = ppixmapDst->m_iScan;

   ::i32 scanSrc = ppixmapSrc->m_iScan;

#ifdef __APPLE__

   ::u8 * pdst = &((::u8 *)ppixmapDst->image32())[scanDst * (ppixmapDst->height() - pointDst.y - 1) + pointDst.x * sizeof(image32_t)] + 3;

   ::u8 * psrc = &((::u8 *)ppixmapSrc->image32())[scanSrc * (ppixmapSrc->height() - pointSrc.y - 1) + pointSrc.x * sizeof(image32_t)] + 3;

#else

   ::u8 * pdst = &((::u8 *)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)] + 3;

   ::u8 * psrc = &((::u8 *)ppixmapSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)] + 3;

#endif

   ::u8 * pdst2;

   ::u8 * psrc2;

   ppixmapDst->div_alpha(pointDst, ::i32_size(xEnd, yEnd));
   ppixmapSrc->div_alpha(pointSrc, ::i32_size(xEnd, yEnd));


   for (::i32 y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (::u8 *) &pdst[scanDst * (-y)];

      psrc2 = (::u8 *) &psrc[scanSrc * (-y)];

#else

      pdst2 = (::u8 *) &pdst[scanDst * y];

      psrc2 = (::u8 *) &psrc[scanSrc * y];

#endif

      for (::i32 x = 0; x < xEnd; x++)
      {

         *pdst2 = *psrc2 * *pdst2 / 255;

         pdst2+=4;

         psrc2+=4;

      }

   }
   ppixmapDst->mult_alpha(pointDst, ::i32_size(xEnd, yEnd));
   ppixmapSrc->mult_alpha(pointSrc, ::i32_size(xEnd, yEnd));

   return true;

}
*/


void pixmap::set_rgb(::i32 R, ::i32 G, ::i32 B)
{

   ::i64 size = scan_area();

   image32_t* pcr = data();

   if (pcr == nullptr)
   {

      //return false;

      return;

   }

   sort_image_rgb(R, G, B);

   for (::i32 i = 0; i < size; i++)
   {

      ((::u8*)pcr)[0] = R;
      ((::u8*)pcr)[1] = G;
      ((::u8*)pcr)[2] = B;

      pcr++;

   }

   //return true;

}


/*   void pixmap::Fill ( ::i32 R, ::i32 G, ::i32 B )
   {
      image32_t color=rgb ( B, G, R );
      ::i64 size = area();

      image32_t * pcr;

      ::i64 iSize32 = size / 32;
      ::i32 i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &data()[i];
         pcr[0] = color;
         pcr[1] = color;
         pcr[2] = color;
         pcr[3] = color;
         pcr[4] = color;
         pcr[5] = color;
         pcr[6] = color;
         pcr[7] = color;
         pcr[8] = color;
         pcr[9] = color;
         pcr[10] = color;
         pcr[11] = color;
         pcr[12] = color;
         pcr[13] = color;
         pcr[14] = color;
         pcr[15] = color;
         pcr[16] = color;
         pcr[17] = color;
         pcr[18] = color;
         pcr[19] = color;
         pcr[20] = color;
         pcr[21] = color;
         pcr[22] = color;
         pcr[23] = color;
         pcr[24] = color;
         pcr[25] = color;
         pcr[26] = color;
         pcr[27] = color;
         pcr[28] = color;
         pcr[29] = color;
         pcr[30] = color;
         pcr[31] = color;
      }

      for (i=0; i<i32_size; i++ )
      {
         data()[i]=color;
      }
   }
   */


//void pixmap::flip_vertical(::pixmap * ppixmap)
//{
//
//   create(ppixmap->size());
//
//   //if (!create(ppixmap->size()))
//   //{
//
//   //   //return false;
//
//   //   return;
//
//   //}
//
//   ::i32 w = width();
//
//   ::i32 h = height();
//
//   ::i32 sw = w * 4;
//
//   ::i32 dsw = m_iScan / 4;
//
//   ::i32 ssw = ppixmap->m_iScan / 4;
//
//   for (::collection::index y = 0; y < h; y++)
//   {
//
//      ::memory_copy(&image32()[y * dsw], &ppixmap->image32()[(h - y - 1) * ssw], sw);
//
//   }
//
////   return true;
//
//}
//
//
//void pixmap::flip_horizontal(::pixmap * ppixmapSource)
//{
//
//   if (ppixmapSource == this)
//   {
//
//      return flip_horizontal();
//
//   }
//
//   create(ppixmapSource->size());
//
//   //if (!create(ppixmapSource->size()))
//   //{
//
//   //   return false;
//
//   //}
//
//   ::i32 half = -1;
//
//   ::i32 dsw = m_iScan / 4;
//
//   ::i32 ssw = ppixmapSource->m_iScan / 4;
//
//   ::i32 w = width();
//
//   ::i32 h = height();
//
//   auto ppixmap32 = image32();
//
//   auto ppixmap32Source = ppixmapSource->image32();
//
//   for (::collection::index y = 0; y < h; y++)
//   {
//
//      for (::collection::index x = 0; x < w; x++)
//      {
//
//         ppixmap32[y * dsw + x] = ppixmap32Source[y * ssw + w - x - 1];
//
//      }
//
//   }
//
////   return true;
//
//}


void pixmap::flip_horizontally()
{

   map();

   ::i32 half = -1;

   ::i32 sw = m_iScan / 4;

   ::i32 w = width();

   ::i32 halfw = w / 2;

   ::i32 h = height();

   auto ppixmap32 = image32();

   for (::collection::index y = 0; y < h; y++)
   {

      for (::collection::index x = 0; x < halfw; x++)
      {

         __swap(ppixmap32[y * sw + x], ppixmap32[y * sw + w - x - 1]);

      }

   }

   //return true;

}


void pixmap::flip_vertically()
{

   map();

   ::i32 half = -1;

   ::i32 sw = m_iScan / 4;

   ::i32 h = height();

   ::i32 halfh = h / 2;

   ::i32 w = width();

   auto ppixmap32 = image32();

   memory line;

   line.set_size(m_iScan);

   for (::collection::index y = 0; y < halfh; y++)
   {

      auto plineFirstHalf = ppixmap32 + (y * sw);

      auto plineSecondHalf = ppixmap32 + ((h - y - 1) * sw);

      memory_copy(line.data(), plineFirstHalf, m_iScan);
      memory_copy(plineFirstHalf, plineSecondHalf, m_iScan);
      memory_copy(plineSecondHalf, line.data(), m_iScan);

   }

   //return true;

}


//void pixmap::flipx(::pixmap * ppixmap)
//{
//
//   //return 
//   
//   flip_horizontal(ppixmap);
//
//}
//
//
//void pixmap::flipy(::pixmap * ppixmap)
//{
//
//   //return 
//   
//   flip_vertical(ppixmap);
//
//}
//


::pixmap_pointer pixmap::horizontally_flipped()
{

   ::pixmap_pointer ppixmap = this->clone();

   ppixmap->flip_horizontally();

   return ppixmap;

}


::pixmap_pointer pixmap::vertically_flipped()
{

   ::pixmap_pointer ppixmap = this->clone();

   ppixmap->flip_vertically();

   return ppixmap;

}


void pixmap::ToAlpha(::i32 i)
{
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[3] = dst[i];
      dst += 4;
   }

   //return true;

}


void pixmap::from_alpha()
{

   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = dst[3];
      dst[1] = dst[3];
      dst[2] = dst[3];
      dst += 4;
   }

   //return true;

}


void pixmap::mult_alpha(::pixmap * ppixmap, bool bPreserveAlpha)
{
   __UNREFERENCED_PARAMETER(ppixmap);
   __UNREFERENCED_PARAMETER(bPreserveAlpha);

   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = lower_byte(((::i32)dst[0] * (::i32)dst[3]) >> 8);
      dst[1] = lower_byte(((::i32)dst[1] * (::i32)dst[3]) >> 8);
      dst[2] = lower_byte(((::i32)dst[2] * (::i32)dst[3]) >> 8);

      dst[4 + 0] = lower_byte(((::i32)dst[4 + 0] * (::i32)dst[4 + 3]) >> 8);
      dst[4 + 1] = lower_byte(((::i32)dst[4 + 1] * (::i32)dst[4 + 3]) >> 8);
      dst[4 + 2] = lower_byte(((::i32)dst[4 + 2] * (::i32)dst[4 + 3]) >> 8);

      dst[8 + 0] = lower_byte(((::i32)dst[8 + 0] * (::i32)dst[8 + 3]) >> 8);
      dst[8 + 1] = lower_byte(((::i32)dst[8 + 1] * (::i32)dst[8 + 3]) >> 8);
      dst[8 + 2] = lower_byte(((::i32)dst[8 + 2] * (::i32)dst[8 + 3]) >> 8);

      dst[12 + 0] = lower_byte(((::i32)dst[12 + 0] * (::i32)dst[12 + 3]) >> 8);
      dst[12 + 1] = lower_byte(((::i32)dst[12 + 1] * (::i32)dst[12 + 3]) >> 8);
      dst[12 + 2] = lower_byte(((::i32)dst[12 + 2] * (::i32)dst[12 + 3]) >> 8);

      dst[16 + 0] = lower_byte(((::i32)dst[16 + 0] * (::i32)dst[16 + 3]) >> 8);
      dst[16 + 1] = lower_byte(((::i32)dst[16 + 1] * (::i32)dst[16 + 3]) >> 8);
      dst[16 + 2] = lower_byte(((::i32)dst[16 + 2] * (::i32)dst[16 + 3]) >> 8);

      dst[20 + 0] = lower_byte(((::i32)dst[20 + 0] * (::i32)dst[20 + 3]) >> 8);
      dst[20 + 1] = lower_byte(((::i32)dst[20 + 1] * (::i32)dst[20 + 3]) >> 8);
      dst[20 + 2] = lower_byte(((::i32)dst[20 + 2] * (::i32)dst[20 + 3]) >> 8);

      dst[24 + 0] = lower_byte(((::i32)dst[24 + 0] * (::i32)dst[24 + 3]) >> 8);
      dst[24 + 1] = lower_byte(((::i32)dst[24 + 1] * (::i32)dst[24 + 3]) >> 8);
      dst[24 + 2] = lower_byte(((::i32)dst[24 + 2] * (::i32)dst[24 + 3]) >> 8);

      dst[28 + 0] = lower_byte(((::i32)dst[28 + 0] * (::i32)dst[28 + 3]) >> 8);
      dst[28 + 1] = lower_byte(((::i32)dst[28 + 1] * (::i32)dst[28 + 3]) >> 8);
      dst[28 + 2] = lower_byte(((::i32)dst[28 + 2] * (::i32)dst[28 + 3]) >> 8);

      dst += 4 * 8;
      size -= 8;
   }
   while (size--)
   {
      dst[0] = lower_byte(((::i32)dst[0] * (::i32)dst[3]) >> 8);
      dst[1] = lower_byte(((::i32)dst[1] * (::i32)dst[3]) >> 8);
      dst[2] = lower_byte(((::i32)dst[2] * (::i32)dst[3]) >> 8);
      dst += 4;
   }

   //return true;

}


#define byte_clip2(i) (i)
void pixmap::mult_alpha()
{
   map();

   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();


   //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = byte_clip2(((::i32)dst[0] * (::i32)dst[3]) / 255);
      dst[1] = byte_clip2(((::i32)dst[1] * (::i32)dst[3]) / 255);
      dst[2] = byte_clip2(((::i32)dst[2] * (::i32)dst[3]) / 255);

      dst[4 + 0] = byte_clip2(((::i32)dst[4 + 0] * (::i32)dst[4 + 3]) / 255);
      dst[4 + 1] = byte_clip2(((::i32)dst[4 + 1] * (::i32)dst[4 + 3]) / 255);
      dst[4 + 2] = byte_clip2(((::i32)dst[4 + 2] * (::i32)dst[4 + 3]) / 255);

      dst[8 + 0] = byte_clip2(((::i32)dst[8 + 0] * (::i32)dst[8 + 3]) / 255);
      dst[8 + 1] = byte_clip2(((::i32)dst[8 + 1] * (::i32)dst[8 + 3]) / 255);
      dst[8 + 2] = byte_clip2(((::i32)dst[8 + 2] * (::i32)dst[8 + 3]) / 255);

      dst[12 + 0] = byte_clip2(((::i32)dst[12 + 0] * (::i32)dst[12 + 3]) / 255);
      dst[12 + 1] = byte_clip2(((::i32)dst[12 + 1] * (::i32)dst[12 + 3]) / 255);
      dst[12 + 2] = byte_clip2(((::i32)dst[12 + 2] * (::i32)dst[12 + 3]) / 255);

      dst[16 + 0] = byte_clip2(((::i32)dst[16 + 0] * (::i32)dst[16 + 3]) / 255);
      dst[16 + 1] = byte_clip2(((::i32)dst[16 + 1] * (::i32)dst[16 + 3]) / 255);
      dst[16 + 2] = byte_clip2(((::i32)dst[16 + 2] * (::i32)dst[16 + 3]) / 255);

      dst[20 + 0] = byte_clip2(((::i32)dst[20 + 0] * (::i32)dst[20 + 3]) / 255);
      dst[20 + 1] = byte_clip2(((::i32)dst[20 + 1] * (::i32)dst[20 + 3]) / 255);
      dst[20 + 2] = byte_clip2(((::i32)dst[20 + 2] * (::i32)dst[20 + 3]) / 255);

      dst[24 + 0] = byte_clip2(((::i32)dst[24 + 0] * (::i32)dst[24 + 3]) / 255);
      dst[24 + 1] = byte_clip2(((::i32)dst[24 + 1] * (::i32)dst[24 + 3]) / 255);
      dst[24 + 2] = byte_clip2(((::i32)dst[24 + 2] * (::i32)dst[24 + 3]) / 255);

      dst[28 + 0] = byte_clip2(((::i32)dst[28 + 0] * (::i32)dst[28 + 3]) / 255);
      dst[28 + 1] = byte_clip2(((::i32)dst[28 + 1] * (::i32)dst[28 + 3]) / 255);
      dst[28 + 2] = byte_clip2(((::i32)dst[28 + 2] * (::i32)dst[28 + 3]) / 255);

      dst += 4 * 8;
      size -= 8;
   }
   while (size > 0)
   {
      dst[0] = byte_clip2(((::i32)dst[0] * (::i32)dst[3]) / 255);
      dst[1] = byte_clip2(((::i32)dst[1] * (::i32)dst[3]) / 255);
      dst[2] = byte_clip2(((::i32)dst[2] * (::i32)dst[3]) / 255);
      dst += 4;
      size--;
   }

   //return true;

}





void pixmap::mult_alpha(const ::i32_point& pointDstParam, const ::i32_size& sizeParam)
{

   ::i32_point pointDst(pointDstParam);

   ::i32_size size(sizeParam);

   ::pixmap * ppixmapDst = this;

   ppixmapDst->map();

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {


      //return false;

      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      //return false;

      return;

   }

   ::i32 xEnd = minimum(size.cx, ppixmapDst->width() - pointDst.x);

   ::i32 yEnd = minimum(size.cy, ppixmapDst->height() - pointDst.y);

   if (xEnd < 0)
   {

      //return false;

      return;

   }

   if (yEnd < 0)
   {

      //return false;

      return;

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

#ifdef __APPLE__

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * (height() - pointDst.y - 1) + pointDst.x * sizeof(image32_t)];

#else

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

#endif

   ::u8* pdst2;

   for (::i32 y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (::u8*)&pdst[scanDst * (-y)];

#else

      pdst2 = (::u8*)&pdst[scanDst * y];

#endif

      for (::i32 x = 0; x < xEnd; x++)
      {

         pdst2[0] = byte_clip(((::i32)pdst2[0] * (::i32)pdst2[3]) / 255);
         pdst2[1] = byte_clip(((::i32)pdst2[1] * (::i32)pdst2[3]) / 255);
         pdst2[2] = byte_clip(((::i32)pdst2[2] * (::i32)pdst2[3]) / 255);

         pdst2 += 4;

      }

   }

   //return true;

}


// void pixmap::create_thumbnail(const ::scoped_string & scopedstr)
// {
//
//    //return false;
//
// }


void pixmap::div_alpha()
{

   auto ppixmapImageThis = map();

   ::u8* dst = (::u8*)ppixmapImageThis->data();
   ::i64 size = ppixmapImageThis->scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   /*      while (size >= 8)
         {
            dst[0] = lower_byte(((::i32)dst[0] * (::i32)dst[3])>> 8);
            dst[1] = lower_byte(((::i32)dst[1] * (::i32)dst[3])>> 8);
            dst[2] = lower_byte(((::i32)dst[2] * (::i32)dst[3])>> 8);

            dst[4+0] = lower_byte(((::i32)dst[4+0] * (::i32)dst[4+3])>> 8);
            dst[4+1] = lower_byte(((::i32)dst[4+1] * (::i32)dst[4+3])>> 8);
            dst[4+2] = lower_byte(((::i32)dst[4+2] * (::i32)dst[4+3])>> 8);

            dst[8+0] = lower_byte(((::i32)dst[8+0] * (::i32)dst[8+3])>> 8);
            dst[8+1] = lower_byte(((::i32)dst[8+1] * (::i32)dst[8+3])>> 8);
            dst[8+2] = lower_byte(((::i32)dst[8+2] * (::i32)dst[8+3])>> 8);

            dst[12+0] = lower_byte(((::i32)dst[12+0] * (::i32)dst[12+3])>> 8);
            dst[12+1] = lower_byte(((::i32)dst[12+1] * (::i32)dst[12+3])>> 8);
            dst[12+2] = lower_byte(((::i32)dst[12+2] * (::i32)dst[12+3])>> 8);

            dst[16+0] = lower_byte(((::i32)dst[16+0] * (::i32)dst[16+3])>> 8);
            dst[16+1] = lower_byte(((::i32)dst[16+1] * (::i32)dst[16+3])>> 8);
            dst[16+2] = lower_byte(((::i32)dst[16+2] * (::i32)dst[16+3])>> 8);

            dst[20+0] = lower_byte(((::i32)dst[20+0] * (::i32)dst[20+3])>> 8);
            dst[20+1] = lower_byte(((::i32)dst[20+1] * (::i32)dst[20+3])>> 8);
            dst[20+2] = lower_byte(((::i32)dst[20+2] * (::i32)dst[20+3])>> 8);

            dst[24+0] = lower_byte(((::i32)dst[24+0] * (::i32)dst[24+3])>> 8);
            dst[24+1] = lower_byte(((::i32)dst[24+1] * (::i32)dst[24+3])>> 8);
            dst[24+2] = lower_byte(((::i32)dst[24+2] * (::i32)dst[24+3])>> 8);

            dst[28+0] = lower_byte(((::i32)dst[28+0] * (::i32)dst[28+3])>> 8);
            dst[28+1] = lower_byte(((::i32)dst[28+1] * (::i32)dst[28+3])>> 8);
            dst[28+2] = lower_byte(((::i32)dst[28+2] * (::i32)dst[28+3])>> 8);

            dst += 4 * 8;
            size -= 8;
         }*/
   while (size--)
   {
      if (dst[3] == 0)
      {
         dst[0] = 0;
         dst[1] = 0;
         dst[2] = 0;
      }
      else
      {
         dst[0] = byte_clip((::i32)dst[0] * 255 / (::i32)dst[3]);
         dst[1] = byte_clip((::i32)dst[1] * 255 / (::i32)dst[3]);
         dst[2] = byte_clip((::i32)dst[2] * 255 / (::i32)dst[3]);
      }

      dst += 4;

   }

   //return true;

}


void pixmap::div_alpha(const ::i32_point& pointDstParam, const ::i32_size& sizeParam)
{

   ::i32_point pointDst(pointDstParam);

   ::i32_size size(sizeParam);


   ::pixmap * ppixmapDst = this;

   ppixmapDst->map();

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
   {
    
      return;

   }

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
   {

      return;

   }


   ::i32 xEnd = minimum(size.cx, ppixmapDst->width() - pointDst.x);

   ::i32 yEnd = minimum(size.cy, ppixmapDst->height() - pointDst.y);

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   ::i32 scanDst = ppixmapDst->m_iScan;

#ifdef __APPLE__

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * (height() - pointDst.y - 1) + pointDst.x * sizeof(image32_t)];

#else

   ::u8* pdst = &((::u8*)ppixmapDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

#endif

   ::u8* pdst2;

   for (::i32 y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (::u8*)&pdst[scanDst * (-y)];

#else

      pdst2 = (::u8*)&pdst[scanDst * y];

#endif

      for (::i32 x = 0; x < xEnd; x++)
      {

         if (pdst2[3] == 0)
         {
            pdst2[0] = 0;
            pdst2[1] = 0;
            pdst2[2] = 0;
         }
         else
         {
            pdst2[0] = byte_clip((::i32)pdst2[0] * 255 / (::i32)pdst2[3]);
            pdst2[1] = byte_clip((::i32)pdst2[1] * 255 / (::i32)pdst2[3]);
            pdst2[2] = byte_clip((::i32)pdst2[2] * 255 / (::i32)pdst2[3]);
         }

         pdst2 += 4;

      }

   }

   //return true;

}


void pixmap::Map(::i32 ToRgb, ::i32 FromRgb)
{

   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();

   while (size--)
   {

      *dst = (::u8)(*dst == FromRgb ? ToRgb : *dst);

      dst += 4;

   }

   //return true;

}


void pixmap::ToAlphaAndFill(::i32 i, ::color::color color)
{

   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();

   ::u8 uchB = color.u8_blue();
   ::u8 uchG = color.u8_green();
   ::u8 uchR = color.u8_red();

   while (size--)
   {
      dst[3] = dst[i];
      dst[0] = uchB;
      dst[1] = uchG;
      dst[2] = uchR;
      dst += 4;
   }

   //return true;

}


void pixmap::GrayToARGB(::color::color color)
{

   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();

   ::u32 dwB = color.u8_blue();
   ::u32 dwG = color.u8_green();
   ::u32 dwR = color.u8_red();

   while (size-- > 0)
   {
      dst[3] = dst[0];
      dst[0] = (::u8)(((dwB * dst[3]) / 256) & 0xff);
      dst[1] = (::u8)(((dwG * dst[3]) / 256) & 0xff);
      dst[2] = (::u8)(((dwR * dst[3]) / 256) & 0xff);
      dst += 4;
   }

   //return true;

}


void pixmap::BitBlt(::pixmap * ppixmap, ::i32 op)
{

   if (op == 123) // zero dest rgb, invert alpha, and OR src rgb
   {

      throw ::exception(todo);
      //stretch(ppixmap);

   }

   //return true;

}


void pixmap::BitBlt(::i32 cxParam, ::i32 cyParam, ::pixmap * ppixmap, ::i32 op)
{

   map();

   ppixmap->map();

   if (op == 1 && size() == ppixmap->size() && ppixmap->m_iScan == m_iScan) // op == 1 indicates can ignore cxParam and cyParam and perform full ::memory_copy
   {

      if (cyParam <= 0)
      {
       //  return false;

         return;

      }

      cyParam = minimum(cyParam, minimum(ppixmap->height(), height()));

#if defined(__APPLE__)

      ::memory_copy(&image32()[m_iScan / 4 * (ppixmap->height() - cyParam)], &ppixmap->image32()[m_iScan / 4 * (ppixmap->height() - cyParam)], cyParam * m_iScan);

#else

      ::memory_copy(image32(), ppixmap->image32(), cyParam * m_iScan);

#endif

   }
   else if (op == 0 || op == 1)
   {

      if (cxParam <= 0)
      {

         return;

      }

      if (cyParam <= 0)
      {

         return;

      }

      cxParam = minimum(cxParam, minimum(ppixmap->width(), width()));

      cyParam = minimum(cyParam, minimum(ppixmap->height(), height()));

      ::i32 iStrideSrc = ppixmap->m_iScan;

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(image32_t);

      }

      if (m_iScan == iStrideSrc && m_iScan == ppixmap->m_iScan)
      {

         ::memory_copy(image32(), ppixmap->image32(), cyParam * m_iScan);

      }
      else
      {

         ::i32 wsrc = iStrideSrc / sizeof(image32_t);
         ::i32 wdst = m_iScan / sizeof(image32_t);
         ::i32 cw = minimum(cxParam, width()) * sizeof(image32_t);

         ::i32 h = minimum(cyParam, height());


         image32_t* psrc = ppixmap->image32();
         image32_t* pdst = image32();

         for (::i32 i = 0; i < h; i++)
         {

            ::memory_copy(pdst, psrc, cw);

            pdst += wdst;

            psrc += wsrc;

         }

      }

   }

   //return true;

}


void pixmap::invert()
{

   map();

   ::i64 size = scan_area();
   ::u8* pb = (::u8*)data();

   for (::i32 i = 0; i < size; i++)
   {
      pb[0] = 255 - pb[0];

      pb[1] = 255 - pb[1];

      pb[2] = 255 - pb[2];

      pb += 4;


   }

   //return true;

}


void pixmap::channel_invert(::color::enum_channel echannel)
{

   ::i64 size = scan_area();

   ::u8* pb = (::u8*)data();


   pb += ((::i32)echannel) % 4;


   for (::i32 i = 0; i < size; i++)
   {

      *pb = 255 - *pb;


      pb += 4;


   }

   //return true;

}


void pixmap::channel_multiply(::f64 dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult)
{

   if (dRate < 0)
   {

      return;

   }

   //#ifdef __APPLE__
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {

      div_alpha();

   }
   //#endif
   ::i64 size = scan_area();
   ::u8* pb = (::u8*)data();

   pb += ((::i32)echannel) % 4;

   ::i32 iDiv = 256 * 256;
   ::i32 iMul = (::i32)(dRate * ((::f64)iDiv));
   ::i32 iRes;
   for (::i64 i = 0; i < size; i++)
   {
      iRes = *pb * iMul / iDiv;

      *pb = (::u8)(iRes > 255 ? 255 : iRes);

      pb += 4;

   }
   //#ifdef __APPLE__
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {
      mult_alpha();
   }
   //#endif

   //return true;

}


void pixmap::channel_multiply(::color::enum_channel echannel, ::pixmap * ppixmap, bool bIfAlphaIgnorePreDivPosMult)
{

   //      ::i64 size = area();

   map();

   ppixmap->map();
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {
      div_alpha();
   }

   ::u8* pb1 = (::u8*)data();


   ::u8* pb2 = (::u8*)ppixmap->data();


   pb1 += ((::i32)echannel) % 4;


   pb2 += ((::i32)echannel) % 4;


   for (::i32 y = 0; y < height(); y++)
   {

      ::u8* pb1_2 = pb1 + (m_iScan * y);


      ::u8* pb2_2 = pb2 + (ppixmap->m_iScan * y);


      for (::i32 x = 0; x < width(); x++)
      {

         ::i32 i = (::u8)(((::u32)*pb1_2 * (::u32)*pb2_2) / 255);

         *pb2 = i;


         pb1_2 += 4;


         pb2_2 += 4;


      }

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {

      mult_alpha();

   }

   //return true;

}


void pixmap::channel_darken(::color::enum_channel echannel, ::pixmap * ppixmap)
{

   ::i64 size = scan_area();

   ::u8* pb1 = (::u8*)data();

   ::u8* pb2 = (::u8*)ppixmap->data();

   pb1 += ((::i32)echannel) % 4;

   pb2 += ((::i32)echannel) % 4;

   for (::i64 i = 0; i < size; i++)
   {
      *pb1 = *pb1 < *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void pixmap::channel_lighten(::color::enum_channel echannel, ::pixmap * ppixmap)
{

   ::i64 size = scan_area();
   ::u8* pb1 = (::u8*)data();

   ::u8* pb2 = (::u8*)ppixmap->data();

   pb1 += ((::i32)echannel) % 4;

   pb2 += ((::i32)echannel) % 4;

   for (::i64 i = 0; i < size; i++)
   {
      *pb1 = *pb1 > *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void pixmap::channel_from(::color::enum_channel echannel, ::pixmap * ppixmap)
{

   map();

   ppixmap->map();

   ::i64 size = m_iScan * height() / sizeof(image32_t);

   ::i64 i64_size = size / 64;

   ::u8* pb1 = (::u8*)data();

   ::u8* pb2 = (::u8*)ppixmap->data();

   pb1 += ((::i32)echannel) % 4;

   pb2 += ((::i32)echannel) % 4;

   ::i64 i = 0;
   for (; i < i64_size; i++)
   {
      pb1[4 * 0] = pb2[4 * 0];

      pb1[4 * 1] = pb2[4 * 1];

      pb1[4 * 2] = pb2[4 * 2];

      pb1[4 * 3] = pb2[4 * 3];

      pb1[4 * 4] = pb2[4 * 4];

      pb1[4 * 5] = pb2[4 * 5];

      pb1[4 * 6] = pb2[4 * 6];

      pb1[4 * 7] = pb2[4 * 7];

      pb1[4 * 8] = pb2[4 * 8];

      pb1[4 * 9] = pb2[4 * 9];

      pb1[4 * 10] = pb2[4 * 10];

      pb1[4 * 11] = pb2[4 * 11];

      pb1[4 * 12] = pb2[4 * 12];

      pb1[4 * 13] = pb2[4 * 13];

      pb1[4 * 14] = pb2[4 * 14];

      pb1[4 * 15] = pb2[4 * 15];

      pb1[4 * 16] = pb2[4 * 16];

      pb1[4 * 17] = pb2[4 * 17];

      pb1[4 * 18] = pb2[4 * 18];

      pb1[4 * 19] = pb2[4 * 19];

      pb1[4 * 20] = pb2[4 * 20];

      pb1[4 * 21] = pb2[4 * 21];

      pb1[4 * 22] = pb2[4 * 22];

      pb1[4 * 23] = pb2[4 * 23];

      pb1[4 * 24] = pb2[4 * 24];

      pb1[4 * 25] = pb2[4 * 25];

      pb1[4 * 26] = pb2[4 * 26];

      pb1[4 * 27] = pb2[4 * 27];

      pb1[4 * 28] = pb2[4 * 28];

      pb1[4 * 29] = pb2[4 * 29];

      pb1[4 * 30] = pb2[4 * 30];

      pb1[4 * 31] = pb2[4 * 31];


      pb1[4 * 32] = pb2[4 * 32];

      pb1[4 * 33] = pb2[4 * 33];

      pb1[4 * 34] = pb2[4 * 34];

      pb1[4 * 35] = pb2[4 * 35];

      pb1[4 * 36] = pb2[4 * 36];

      pb1[4 * 37] = pb2[4 * 37];

      pb1[4 * 38] = pb2[4 * 38];

      pb1[4 * 39] = pb2[4 * 39];

      pb1[4 * 40] = pb2[4 * 40];

      pb1[4 * 41] = pb2[4 * 41];

      pb1[4 * 42] = pb2[4 * 42];

      pb1[4 * 43] = pb2[4 * 43];

      pb1[4 * 44] = pb2[4 * 44];

      pb1[4 * 45] = pb2[4 * 45];

      pb1[4 * 46] = pb2[4 * 46];

      pb1[4 * 47] = pb2[4 * 47];

      pb1[4 * 48] = pb2[4 * 48];

      pb1[4 * 49] = pb2[4 * 49];

      pb1[4 * 50] = pb2[4 * 50];

      pb1[4 * 51] = pb2[4 * 51];

      pb1[4 * 52] = pb2[4 * 52];

      pb1[4 * 53] = pb2[4 * 53];

      pb1[4 * 54] = pb2[4 * 54];

      pb1[4 * 55] = pb2[4 * 55];

      pb1[4 * 56] = pb2[4 * 56];

      pb1[4 * 57] = pb2[4 * 57];

      pb1[4 * 58] = pb2[4 * 58];

      pb1[4 * 59] = pb2[4 * 59];

      pb1[4 * 60] = pb2[4 * 60];

      pb1[4 * 61] = pb2[4 * 61];

      pb1[4 * 62] = pb2[4 * 62];

      pb1[4 * 63] = pb2[4 * 63];


      pb1 += 4 * 64;

      pb2 += 4 * 64;

   }
   i *= 64;
   for (; i < size; i++)
   {
      *pb1 = *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void pixmap::channel_from(::color::enum_channel echannel, ::pixmap * ppixmap, const ::i32_rectangle& rectangleParam)
{

   map();

   ppixmap->map();

   ::i32_rectangle rectangle;

   if (!rectangle.intersect(this->rectangle(), rectangleParam))
   {

      return;

   }

   if (!rectangle.intersect(ppixmap->rectangle(), rectangle))
   {

      return;

   }

   ::u8* pb1 = ((::u8*)data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * m_iScan);


   ::u8* pb2 = ((::u8*)ppixmap->data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * ppixmap->m_iScan);


   pb1 += ((::i32)echannel) % 4;


   pb2 += ((::i32)echannel) % 4;


   ::i32 h = rectangle.height();

   ::i32 w = rectangle.width();

   for (::i32 i = 0; i < h; i++)
   {

      ::u8* pb1_2 = pb1;


      ::u8* pb2_2 = pb2;


      for (::i32 j = 0; j < w; j++)
      {

         *pb1_2 = *pb2_2;


         pb1_2 += 4;


         pb2_2 += 4;


      }

      pb1 += m_iScan;


      pb2 += ppixmap->m_iScan;


   }

   //return true;

}



void pixmap::channel_multiply(::color::enum_channel echannel, ::pixmap * ppixmap, const ::i32_rectangle& rectangleParam, bool bIfAlphaIgnorePreDivPosMult)
{

   map();

   ppixmap->map();

   ::i32_rectangle rectangle;

   if (!rectangle.intersect(this->rectangle(), rectangleParam))
   {

      return;

   }

   if (!rectangle.intersect(ppixmap->rectangle(), rectangle))
   {

      return;

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {

      div_alpha(rectangle.top_left(), rectangle.size());

   }

#ifdef __APPLE__

   ::u8* pb1 = ((::u8*)data()) + (rectangle.left * sizeof(image32_t) + (height() - rectangle.top - 1) * m_iScan);


   ::u8* pb2 = ((::u8*)ppixmap->data()) + (rectangle.left * sizeof(image32_t) + (ppixmap->height() - rectangle.top - 1) * ppixmap->m_iScan);


#else

   ::u8* pb1 = ((::u8*)data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * m_iScan);


   ::u8* pb2 = ((::u8*)ppixmap->data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * ppixmap->m_iScan);


#endif

   pb1 += ((::i32)echannel) % 4;


   pb2 += ((::i32)echannel) % 4;


   ::i32 h = rectangle.height();

   ::i32 w = rectangle.width();

   for (::i32 i = 0; i < h; i++)
   {

      ::u8* pb1_2 = pb1;


      ::u8* pb2_2 = pb2;


      for (::i32 j = 0; j < w; j++)
      {

         *pb1_2 = *pb2_2 * *pb1_2 / 255;


         pb1_2 += 4;


         pb2_2 += 4;


      }

#ifdef __APPLE__

      pb1 -= m_iScan;


      pb2 -= ppixmap->m_iScan;


#else

      pb1 += m_iScan;


      pb2 += ppixmap->m_iScan;


#endif

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {

      mult_alpha(rectangle.top_left(), rectangle.size());

   }

   //return true;

}


void pixmap::fill_glass(::i32 R, ::i32 G, ::i32 B, ::i32 A)
{

   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();

   while (size--)
   {

      dst[0] = (::u8)(((B - dst[0]) * A + (dst[0] << 8)) >> 8);
      dst[1] = (::u8)(((G - dst[1]) * A + (dst[1] << 8)) >> 8);
      dst[2] = (::u8)(((R - dst[2]) * A + (dst[2] << 8)) >> 8);
      dst += 4;

   }

   //return true;

}


void pixmap::fill_stippled_glass(::i32 R, ::i32 G, ::i32 B)
{

   image32_t color(rgb(B, G, R), color_indexes());
   ::i32 w = width();
   ::i32 h = height();

   for (::i32 j = 0; j < w; j++)
   {
      for (::i32 i = 0; i < h; i++)
      {
         data()[j * w + i] = ((i + j) & 0x1) ? data()[j * w + i] : color;
      }
   }

   //return true;

}


//void pixmap::to(::pixmap * ppixmap) const
//{
//
//   if (::is_null(ppixmap))
//   {
//
//      return false;
//
//   }
//
//   return ppixmap->from(this);
//
//}


// void pixmap::copy_from(::pixmap * ppixmap, ::eobject eobjectCreate)
// {
//
//    if (size() != ppixmap->size())
//    {
//
//       create(ppixmap->size(), eobjectCreate);
//
//    }
//    else
//    {
//
//       m_eobject = eobjectCreate;
//
//    }
//
//    //ppixmap->defer_realize(pgraphicsImage);
//    //defer_realize(pgraphicsImage);
//
//    map();
//
//    ((::pixmap::image*)ppixmap)->map();
//    // If ppixmapSize Wrong Re-create image_impl
//    // do Paste
//
//    if (m_iScan == ppixmap->m_iScan)
//    {
//
//       ::memory_copy(data(), ppixmap->data(), height() * m_iScan);
//
//    }
//    else
//    {
//
//       ::i32 iScan = minimum(m_iScan, ppixmap->m_iScan);
//
//       for (::i32 i = 0; i < height(); i++)
//       {
//
//          ::memory_copy(&((::u8*)data())[m_iScan * i], &((::u8*)ppixmap->data())[ppixmap->m_iScan * i], iScan);
//
//       }
//
//    }
//
//    return true;
//
// }


//void pixmap::bitmap_blend(::draw2d::graphics* pgraphics, const ::i32_rectangle& rectangle)
//{
//
//   ::pixmap::image_source imagesource(pgraphics);
//
//
//   return pgraphics->stretch(rectangle, pgraphics) != false;
//
//
//}


void pixmap::color_blend(::color::color color, ::u8 bAlpha)
{

   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();

   ::u32 dwB = color.u8_blue();
   ::u32 dwG = color.u8_green();
   ::u32 dwR = color.u8_red();

   ::u32 dwB_ = dwB << 8;
   ::u32 dwG_ = dwG << 8;
   ::u32 dwR_ = dwR << 8;

   while (size--)
   {
      dst[0] = (::u8)(((dst[0] - dwB) * bAlpha + dwB_) >> 8);
      dst[1] = (::u8)(((dst[1] - dwG) * bAlpha + dwG_) >> 8);
      dst[2] = (::u8)(((dst[2] - dwG) * bAlpha + dwR_) >> 8);
      dst += 4;
   }

   //return true;

}


void pixmap::op(const ::scoped_string & scopedstr)
{

   if (scopedstr == "horz-__swap")
   {

      map();

      // half width
      ::i32 hx = width() / 2;
      // aligned scan
      ::i32 as = m_iScan / sizeof(image32_t);

      for (::collection::index i = 0; i < height(); i++)
      {
         for (::collection::index j = 0; j < hx; j++)
         {
            __swap(image32()[i * as + j], image32()[i * as + width() - j]);
         }
      }

      //return true;
   }

   //return false;

}


::memory pixmap::copy_with_no_stride()
{
   
   memory m;
   m.set_size(area() * 4);
   auto ppixmap32Target = (image32_t *) m.data();
   ppixmap32Target->copy(this->width(), this->height(), this->width() * 4, this->data(), this->m_iScan);
   return ::transfer(m);
   
}


::memory pixmap::vertical_swap_copy_with_no_stride()
{
   
   memory m;
   m.set_size(area() * 4);
   auto ppixmap32Target = (image32_t *) m.data();
   ppixmap32Target->vertical_swap_copy(this->width(), this->height(), this->width() * 4, this->data(), this->m_iScan);
   return ::transfer(m);
   
}


void pixmap::Blend(::pixmap * ppixmap, ::i32 A)
{

   if (size() != ppixmap->size())
   {

      throw ::exception(error_wrong_state);

   }

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = (::u8)(((src[0] - dst[0]) * A + (dst[0] << 8)) >> 8);
      dst[1] = (::u8)(((src[1] - dst[1]) * A + (dst[1] << 8)) >> 8);
      dst[2] = (::u8)(((src[2] - dst[2]) * A + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
   }

   //return true;

}


void pixmap::Blend(::pixmap * ppixmap, ::pixmap * ppixmapA, ::i32 A)
{
   if (size() != ppixmap->size() ||
      size() != ppixmapA->size())
      throw ::exception(error_wrong_state);

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::u8* alf = (::u8*)ppixmapA->data();
   ::i64 size = scan_area();

   A = 2 - A;

   while (size--)
   {
      dst[0] = (::u8)(((src[0] - dst[0]) * alf[A] + (dst[0] << 8)) >> 8);
      dst[1] = (::u8)(((src[1] - dst[1]) * alf[A] + (dst[1] << 8)) >> 8);
      dst[2] = (::u8)(((src[2] - dst[2]) * alf[A] + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
      alf += 4;
   }

   //return true;

}


void pixmap::Blend(::pixmap * ppixmap, ::pixmap * ppixmapA)
{
   if (size() != ppixmap->size() ||
      size() != ppixmapA->size())
      throw ::exception(error_wrong_state);

   map();
   ppixmap->map();
   ppixmapA->map();

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::u8* alf = ((::u8*)ppixmapA->data()) + 3;
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = (::u8)(((src[0] - dst[0]) * (*alf) + (dst[0] << 8)) >> 8);
      dst[1] = (::u8)(((src[1] - dst[1]) * (*alf) + (dst[1] << 8)) >> 8);
      dst[2] = (::u8)(((src[2] - dst[2]) * (*alf) + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
      alf += 4;
   }

   //return true;

}



void pixmap::blend(::pixmap * ppixmap, ::pixmap * ppixmapRate)
{
   if (size() != ppixmap->size() ||
      size() != ppixmapRate->size())
      throw ::exception(error_wrong_state);

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::u8* alf = (::u8*)ppixmapRate->data();
   ::i64 size = scan_area();

   while (size >= 2)
   {
      dst[00] = (::u8)(((((::i32)src[00] - (::i32)dst[00]) * (::i32)alf[00]) + (::i32)dst[00] * (::i32)255) / 255);
      dst[01] = (::u8)(((((::i32)src[01] - (::i32)dst[01]) * (::i32)alf[01]) + (::i32)dst[01] * (::i32)255) / 255);
      dst[02] = (::u8)(((((::i32)src[02] - (::i32)dst[02]) * (::i32)alf[02]) + (::i32)dst[02] * (::i32)255) / 255);
      dst[03] = (::u8)(((((::i32)src[03] - (::i32)dst[03]) * (::i32)alf[03]) + (::i32)dst[03] * (::i32)255) / 255);
      dst[04] = (::u8)(((((::i32)src[04] - (::i32)dst[04]) * (::i32)alf[04]) + (::i32)dst[04] * (::i32)255) / 255);
      dst[05] = (::u8)(((((::i32)src[05] - (::i32)dst[05]) * (::i32)alf[05]) + (::i32)dst[05] * (::i32)255) / 255);
      dst[06] = (::u8)(((((::i32)src[06] - (::i32)dst[06]) * (::i32)alf[06]) + (::i32)dst[06] * (::i32)255) / 255);
      dst[07] = (::u8)(((((::i32)src[07] - (::i32)dst[07]) * (::i32)alf[07]) + (::i32)dst[07] * (::i32)255) / 255);
      dst += 4 * 2;
      src += 4 * 2;
      alf += 4 * 2;
      size -= 2;
   }
   while (size > 0)
   {
      dst[00] = (::u8)(((((::i32)src[00] - (::i32)dst[00]) * (::i32)alf[00]) + (::i32)dst[00] * (::i32)255) / 255);
      dst[01] = (::u8)(((((::i32)src[01] - (::i32)dst[01]) * (::i32)alf[01]) + (::i32)dst[01] * (::i32)255) / 255);
      dst[02] = (::u8)(((((::i32)src[02] - (::i32)dst[02]) * (::i32)alf[02]) + (::i32)dst[02] * (::i32)255) / 255);
      dst[03] = (::u8)(((((::i32)src[03] - (::i32)dst[03]) * (::i32)alf[03]) + (::i32)dst[03] * (::i32)255) / 255);
      dst += 4;
      src += 4;
      alf += 4;
      size--;
   }

   //return true;
}


void pixmap::Darken(::pixmap * ppixmap)
{

   if (size() != ppixmap->size())
   {

      throw ::exception(error_wrong_state);

   }

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = (::u8)((src[0] < dst[0]) ? src[0] : dst[0]);
      dst[1] = (::u8)((src[1] < dst[1]) ? src[1] : dst[1]);
      dst[2] = (::u8)((src[2] < dst[2]) ? src[2] : dst[2]);
      dst += 4;
      src += 4;
   }

   //return true;

}


void pixmap::Difference(::pixmap * ppixmap)
{

   if (size() != ppixmap->size())
   {

      throw ::exception(error_wrong_state);

   }

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      ::i32 Difference;
      Difference = src[0] - dst[0];
      dst[0] = (::u8)((Difference < 0) ? -Difference : Difference);
      Difference = src[1] - dst[1];
      dst[1] = (::u8)((Difference < 0) ? -Difference : Difference);
      Difference = src[2] - dst[2];
      dst[2] = (::u8)((Difference < 0) ? -Difference : Difference);
      dst += 4;
      src += 4;
   }

   //return true;

}


void pixmap::Lighten(::pixmap * ppixmap)
{

   if (size() != ppixmap->size())
   {

      throw ::exception(error_wrong_state);

   }

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = (::u8)((src[0] > dst[0]) ? src[0] : dst[0]);
      dst[1] = (::u8)((src[1] > dst[1]) ? src[1] : dst[1]);
      dst[2] = (::u8)((src[2] > dst[2]) ? src[2] : dst[2]);
      dst += 4;
      src += 4;
   }

   //return true;

}


/// centered on 0.
/// > 0 lighter (safe)
/// < 0 darker (non safe)
void pixmap::lighten(::f64 dRate)
{
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] += (::u8)((dst[3] - dst[0]) * dRate);
      dst[1] += (::u8)((dst[3] - dst[1]) * dRate);
      dst[2] += (::u8)((dst[3] - dst[2]) * dRate);
      dst += 4;
   }

   //return true;

}


void pixmap::Multiply(::pixmap * ppixmap)
{

   if (size() != ppixmap->size())
   {

      throw ::exception(error_wrong_state);

   }

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = (::u8)(((src[0]) * (dst[0])) >> 8);
      dst[1] = (::u8)(((src[1]) * (dst[1])) >> 8);
      dst[2] = (::u8)(((src[2]) * (dst[2])) >> 8);
      dst += 4;
      src += 4;
   }

   //return true;

}


void pixmap::Screen(::pixmap * ppixmap)
{

   if (size() != ppixmap->size())
   {

      throw ::exception(error_wrong_state);

   }

   ::u8* src = (::u8*)ppixmap->data();
   ::u8* dst = (::u8*)data();
   ::i64 size = scan_area();

   while (size--)
   {
      dst[0] = (::u8)(255 - (((255 - src[0]) * (255 - dst[0])) >> 8));
      dst[1] = (::u8)(255 - (((255 - src[1]) * (255 - dst[1])) >> 8));
      dst[2] = (::u8)(255 - (((255 - src[2]) * (255 - dst[2])) >> 8));
      dst += 4;
      src += 4;
   }

   //return true;

}

//
// void pixmap::copy_from_no_create(::pixmap * ppixmap, const ::i32_point & point)
// {
//
//    ::i32_size s(ppixmap->size() - point);
//
//    auto sizeCopy = ::i32_size(::minimum(size().cx, s.cx), ::minimum(size().cy, s.cy));
//
//    if (sizeCopy.area() > 0)
//    {
//
//       ::pixmap::image_source imagesource(ppixmap, { point, sizeCopy });
//
//       ::f64_rectangle rectangle(sizeCopy);
//
//       ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
//
//       ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//       auto pgraphics = acquire_graphics();
//
//       pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//       pgraphics->draw(imagedrawing);
//       //{
//
//       //   return false;
//
//       //}
//
//    }
//
//    //return true;
//
// }
//
//
// void pixmap::copy_from_no_create(::pixmap * ppixmap)
// {
//
//    return copy_from_no_create(ppixmap, {});
//
// }
//
//
//
// void pixmap::copy_from(::pixmap * ppixmap, const ::i32_point  & point, ::enum_flag eflagCreate)
// {
//
//    ::i32_size s(ppixmap->size() - point);
//
//    if (size() != s)
//    {
//
//       create_as_descriptor(s, eflagCreate);
//       //if (!create(s))
//       //{
//
//       //   return false;
//
//       //}
//
//    }
//
// //   if(ppixmap->m_bMapped && m_bMapped) {
// //
// //      m_pimage32->copy(size(),m_iScan, ppixmap->m_pimage32, ppixmap->m_iScan);
// //
// //   } else
// //   {
//
//
//       copy_from_no_create(ppixmap, point);
//
// //   }
//
// //   memcpy(data(), ppixmap->data(), this->scan_area_in_bytes());
//    //copy_from_no_create(ppixmap, point);
//
// }


void pixmap::copy_from(::pixmap * ppixmap, enum_flag eflagCreate)
{

   if (ppixmap->m_pimage32Raw && m_pimage32Raw)
   {

      create_as_descriptor(ppixmap->size(), DEFAULT_CREATE_IMAGE_FLAG, ppixmap->scan_size());

      auto ppixmapTarget = this->map();

      auto ppixmapSource = ppixmap->map();

      ppixmapSource->copy(ppixmapSource);

      return;

   }

   return copy_from(ppixmap, {}, eflagCreate);

}


//void pixmap::copy_to(::pixmap * ppixmap, const i32_point & point)
//{
//
//   return ppixmap->copy_from(this);
//
//}


void pixmap::fill_rectangle(const ::i32_rectangle& rectangle, ::i32 R, ::i32 G, ::i32 B)
{

   ::i32 x = rectangle.left;

   ::i32 y = rectangle.top;

   ::i32 w = rectangle.width();

   ::i32 h = rectangle.height();

   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + w) < width()) ? w : width() - x;
   ::i32 Δy = ((y + h) < height()) ? h : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Fill return
   if ((Δx <= 0) || (Δy <= 0))
   {

      return;

   }

   map();

   image32_t* dst = data() + (py * width()) + px;

   while (Δy--)
   {

      for (::i32 i = 0; i < Δx; i++)
      {

         ((::u8*)&dst[i])[0] = R;
         ((::u8*)&dst[i])[1] = G;
         ((::u8*)&dst[i])[2] = B;

      }

      dst += m_iScan / sizeof(image32_t);

   }

   //return true;

}


void pixmap::fill_rectangle(const ::i32_rectangle& rectangle, ::color::color color)
{

   // if (m_bMapped)
   // {

   if (!m_bMapped)
   {
      throw ::exception(error_wrong_state);

   }

      ::i32 x = rectangle.left;

      ::i32 y = rectangle.top;

      ::i32 w = rectangle.width();

      ::i32 h = rectangle.height();

      ::image32_t u32Color(color, color_indexes());

      // Clip Rect
      ::i32 px = x;
      if (w < 0)
      {
         px += w;
         w = -w;
      }

      px = (px >= 0) ? px : 0;
      ::i32 py = y;
      if (h < 0)
      {
         py += h;
         h = -h;
      }
      py = (py >= 0) ? py : 0;
      ::i32 Δx;
      Δx = ((px + w) < width()) ? w : width() - px;
      ::i32 Δy;
      Δy = ((py + h) < height()) ? h : height() - py;
      Δx = (px >= 0) ? Δx : Δx + x;
      Δy = (py >= 0) ? Δy : Δy + y;

      // If Nothing to Fill return
      if ((Δx <= 0) || (Δy <= 0))
         return;

      // Prepare buffer Address
      image32_t* dst = data() + (py * width()) + px;

      while (Δy--)
      {

         for (::i32 i = 0; i < Δx; i++)
         {

            dst[i] = u32Color;

         }

         dst += m_iScan / sizeof(image32_t);

      }

   }
   // else
   // {
   //
   //    auto pgraphics = acquire_graphics();
   //
   //    ::draw2d::enum_alpha_mode emodeOld = pgraphics->alpha_mode();
   //
   //    if (pgraphics->alpha_mode() != ::draw2d::e_alpha_mode_set)
   //    {
   //
   //       pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //
   //    }
   //
   //    pgraphics->fill_rectangle(rectangle, color);
   //
   //    if (pgraphics->alpha_mode() != emodeOld)
   //    {
   //
   //       pgraphics->set_alpha_mode(emodeOld);
   //
   //    }
   //
   // }
   //
   // //return true;

//}


void pixmap::fill_glass_rect(const ::i32_rectangle& rectangle, ::i32 R, ::i32 G, ::i32 B, ::i32 A)

{

   ::i32 x = rectangle.left;

   ::i32 y = rectangle.top;

   ::i32 w = rectangle.width();

   ::i32 h = rectangle.height();


   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + w) < width()) ? w : width() - x;
   ::i32 Δy = ((y + h) < height()) ? h : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to FillGlass return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Address
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do FillGlass
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[0] = (::u8)(((B - dst[0]) * A + (dst[0] << 8)) >> 8);
         dst[1] = (::u8)(((G - dst[1]) * A + (dst[1] << 8)) >> 8);
         dst[2] = (::u8)(((R - dst[2]) * A + (dst[2] << 8)) >> 8);
         dst += 4;
      }

      dst += (width() - Δx) << 2;

   }

   //return true;

}


void pixmap::fill_stippled_glass_rect(const ::i32_rectangle& rectangle, ::i32 R, ::i32 G, ::i32 B)

{

   ::i32 x = rectangle.left;

   ::i32 y = rectangle.top;

   ::i32 w = rectangle.width();

   ::i32 h = rectangle.height();


   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + w) < width()) ? w : width() - x;
   ::i32 Δy = ((y + h) < height()) ? h : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to FillStippledGlass return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Address
   image32_t* dst = data() + (py * width()) + px;
   image32_t color(rgb(B, G, R), color_indexes());

   // Do FillStippledGlass
   for (::i32 j = 0; j < Δy; j++)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[i] = ((i + j) & 0x1) ? dst[i] : color;
      }
      dst += width();
   }

   //return true;

}


void pixmap::BlendRect(::pixmap * ppixmap, ::i32 x, ::i32 y, ::i32 A)
{
   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + ppixmap->width()) < width()) ? ppixmap->width() : width() - x;
   ::i32 Δy = ((y + ppixmap->height()) < height()) ? ppixmap->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Blend return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   ::u8* src = (::u8*)ppixmap->data() + (((py - y) * ppixmap->width()) + px - x) * 4;
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do Blend
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[0] = (::u8)(((src[0] - dst[0]) * A + (dst[0] << 8)) >> 8);
         dst[1] = (::u8)(((src[1] - dst[1]) * A + (dst[1] << 8)) >> 8);
         dst[2] = (::u8)(((src[2] - dst[2]) * A + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (ppixmap->width() - Δx) << 2;
   }

   //return true;

}


void pixmap::DarkenRect(::pixmap * ppixmap, ::i32 x, ::i32 y)
{
   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + ppixmap->width()) < width()) ? ppixmap->width() : width() - x;
   ::i32 Δy = ((y + ppixmap->height()) < height()) ? ppixmap->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Darken return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   ::u8* src = (::u8*)ppixmap->data() + (((py - y) * ppixmap->width()) + px - x) * 4;
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do Darken
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[0] = (::u8)((src[0] < dst[0]) ? src[0] : dst[0]);
         dst[1] = (::u8)((src[1] < dst[1]) ? src[1] : dst[1]);
         dst[2] = (::u8)((src[2] < dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (ppixmap->width() - Δx) << 2;
   }

   //return true;

}


void pixmap::DifferenceRect(::pixmap * ppixmap, ::i32 x, ::i32 y)
{
   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + ppixmap->width()) < width()) ? ppixmap->width() : width() - x;
   ::i32 Δy = ((y + ppixmap->height()) < height()) ? ppixmap->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Difference return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   ::u8* src = (::u8*)ppixmap->data() + (((py - y) * ppixmap->width()) + px - x) * 4;
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do Difference
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         ::i32 Difference;
         Difference = src[0] - dst[0];
         dst[0] = (::u8)((Difference < 0) ? -Difference : Difference);
         Difference = src[1] - dst[1];
         dst[1] = (::u8)((Difference < 0) ? -Difference : Difference);
         Difference = src[2] - dst[2];
         dst[2] = (::u8)((Difference < 0) ? -Difference : Difference);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (ppixmap->width() - Δx) << 2;
   }

   //return true;

}


void pixmap::LightenRect(::pixmap * ppixmap, ::i32 x, ::i32 y)
{
   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + ppixmap->width()) < width()) ? ppixmap->width() : width() - x;
   ::i32 Δy = ((y + ppixmap->height()) < height()) ? ppixmap->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Lighten return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   ::u8* src = (::u8*)ppixmap->data() + (((py - y) * ppixmap->width()) + px - x) * 4;
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do Lighten
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[0] = (::u8)((src[0] > dst[0]) ? src[0] : dst[0]);
         dst[1] = (::u8)((src[1] > dst[1]) ? src[1] : dst[1]);
         dst[2] = (::u8)((src[2] > dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (ppixmap->width() - Δx) << 2;
   }

   return;

}


void pixmap::MultiplyRect(::pixmap * ppixmap, ::i32 x, ::i32 y)
{
   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + ppixmap->width()) < width()) ? ppixmap->width() : width() - x;
   ::i32 Δy = ((y + ppixmap->height()) < height()) ? ppixmap->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Multiply return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   ::u8* src = (::u8*)ppixmap->data() + (((py - y) * ppixmap->width()) + px - x) * 4;
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do Multiply
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[0] = (::u8)(((src[0]) * (dst[0])) >> 8);
         dst[1] = (::u8)(((src[1]) * (dst[1])) >> 8);
         dst[2] = (::u8)(((src[2]) * (dst[2])) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (ppixmap->width() - Δx) << 2;
   }

   //return true;

}


void pixmap::ScreenRect(::pixmap * ppixmap, ::i32 x, ::i32 y)
{
   // Clip Rect
   ::i32 px = (x >= 0) ? x : 0;
   ::i32 py = (y >= 0) ? y : 0;
   ::i32 Δx = ((x + ppixmap->width()) < width()) ? ppixmap->width() : width() - x;
   ::i32 Δy = ((y + ppixmap->height()) < height()) ? ppixmap->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Screen return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   ::u8* src = (::u8*)ppixmap->data() + (((py - y) * ppixmap->width()) + px - x) * 4;
   ::u8* dst = (::u8*)data() + ((py * width()) + px) * 4;

   // Do Screen
   while (Δy--)
   {
      for (::i32 i = 0; i < Δx; i++)
      {
         dst[0] = (::u8)(255 - (((255 - src[0]) * (255 - dst[0])) >> 8));
         dst[1] = (::u8)(255 - (((255 - src[1]) * (255 - dst[1])) >> 8));
         dst[2] = (::u8)(255 - (((255 - src[2]) * (255 - dst[2])) >> 8));
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (ppixmap->width() - Δx) << 2;
   }

   //return true;

}


//////////////////////////////////////////////////////////////////////
// Line Functions
//////////////////////////////////////////////////////////////////////

/*void pixmap::Line ( ::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 R, ::i32 G, ::i32 B )
{
::i32 Δx, Δy, k1, k2, d, x, y;
image32_t color=rgb ( B, G, R );

Δx=x2-x1;
Δy=y2-y1;
d=(Δy<<1)-Δx;
k1=Δy<<1;
k2=(Δy-Δx)<<1;
x=x1;
y=y1;

data()[y*width()+x]=color;
while (x<Δx)
{
if (d<=0)
{
d+=k1;
x++;
}
else
{
d+=k2;
x++;
y++;
}
data()[y*width()+x]=color;
}
}*/


void pixmap::horizontal_line(::i32 y, ::color::color color, ::i32 x1, ::i32 x2)
{
   if (width() == 0)
      return;
   map();
   if (x1 < 0)
      x1 = 0;
   if (x2 >= width())
      x2 = width() - 1;
   image32_t u32ImageColor(color, color_indexes());
   
   auto h = height();

   if (y >= h)
      return;
   
#ifdef __APPLE__
   
   auto yflipped = (h - y - 1);

   image32_t* pdata = (image32_t*)((::u8 *) data() + x1 * sizeof(image32_t) +  yflipped * (m_iScan));

#else

   image32_t* pdata = (image32_t*)((::u8 *) data() + x1 * sizeof(image32_t) + y * (m_iScan));

#endif

   for (::i32 x = x1; x <= x2; x++)
   {

      *pdata = u32ImageColor;

      pdata++;

   }

   //return true;

}


void pixmap::vertical_line(::i32 x, ::color::color color, ::i32 y1, ::i32 y2)
{
   if (height() == 0)
      return;
   map();
   if (y1 < 0)
      y1 = 0;
   if (y2 >= height())
      y2 = height() - 1;
   //y1 %= height();
   //y2 %= height();
   //if (y2 < 0)
     // y2 += height();
   //if (x1 < 0)
     // x1 += width();
   image32_t u32ImageColor(color, color_indexes());

#ifdef __APPLE__

   image32_t* pdata = (image32_t*)((::u8*)data() + x *sizeof(image32_t) + ((height() - y2 - 1) * m_iScan));

#else

   image32_t* pdata = (image32_t*)((::u8*)data() + x *sizeof(image32_t) + (y1 * m_iScan));
   
#endif

   for (::i32 y = y1; y <= y2; y++)
   {

      *pdata = u32ImageColor;

      ((::u8*&)pdata)+=m_iScan;

   }

   //return true;

}


void pixmap::frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color)
{

   horizontal_line(y, color, x, x + w - 1);

   vertical_line(x, color, y + 1, y + h - 2);

   horizontal_line(y + h - 1, color, x, x + w - 1);

   vertical_line(x + w - 1, color, y + 1, y + h - 2);

}

void pixmap::frame_pixel_perfect_rectangle(::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::color::color& color, ::i32 width)
{

   if (width <= 0)
   {

      return;

   }

   while (true)
   {

      frame_pixel_perfect_rectangle(x, y, w, h, color);

      width--;

      if (width <= 0)
      {

         break;

      }

      x++;
      y++;
      w -= 2;
      h -= 2;

   }

}


void pixmap::Line(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 R, ::i32 G, ::i32 B)
{
   ::i32 d, x, y, aura, ay, sx, sy, Δx, Δy;
   image32_t color(rgb(B, G, R), color_indexes());

   Δx = x2 - x1;
   aura = abs(Δx) << 1;
   sx = (Δx < 0) ? -1 : 1;
   Δy = y2 - y1;
   ay = abs(Δy) << 1;
   sy = (Δy < 0) ? -1 : 1;
   x = x1;
   y = y1;

   if (aura > ay)
   {
      d = ay - (aura >> 1);
      while (x != x2)
      {
         data()[y * (m_iScan / sizeof(image32_t)) + x] = color;
         if (d >= 0)
         {
            y += sy;
            d -= aura;
         }
         x += sx;
         d += ay;
      }
   }
   else
   {
      d = aura - (ay >> 1);
      while (y != y2)
      {
         data()[y * (m_iScan / sizeof(image32_t)) + x] = color;
         if (d >= 0)
         {
            x += sx;
            d -= ay;
         }
         y += sy;
         d += aura;
      }
   }

   //return true;

}


void pixmap::LineGlass(::i32 x1, ::i32 y1, ::i32 x2, ::i32 y2, ::i32 R, ::i32 G, ::i32 B, ::i32 A)
{
   ::i32 d, x, y, aura, ay, sx, sy, Δx, Δy;
   //      image32_t color=rgb ( B, G, R );
   ::u8* dst = (::u8*)data();

   Δx = x2 - x1;
   aura = abs(Δx) << 1;
   sx = (Δx < 0) ? -1 : 1;
   Δy = y2 - y1;
   ay = abs(Δy) << 1;
   sy = (Δy < 0) ? -1 : 1;
   x = x1;
   y = y1;

   if (aura > ay)
   {
      d = ay - (aura >> 1);
      while (x != x2)
      {
         dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] = (::u8)(((B - dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2]) * A + (dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] = (::u8)(((G - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] = (::u8)(((R - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] << 8)) >> 8);
         if (d >= 0)
         {
            y += sy;
            d -= aura;
         }
         x += sx;
         d += ay;
      }
   }
   else
   {
      d = aura - (ay >> 1);
      while (y != y2)
      {
         dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] = (::u8)(((B - dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2]) * A + (dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] = (::u8)(((G - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] = (::u8)(((R - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] << 8)) >> 8);
         if (d >= 0)
         {
            x += sx;
            d -= ay;
         }
         y += sy;
         d += aura;
      }
   }

   //return true;

}


void pixmap::Mask(::color::color colorMask, ::color::color colorInMask, ::color::color colorOutMask)
{
   image32_t crFind(colorMask, color_indexes());
   image32_t crSet(colorInMask, color_indexes());
   image32_t crUnset(colorOutMask, color_indexes());

   ::i64 size = scan_area();

   for (::i32 i = 0; i < size; i++)
      if (data()[i] == crFind)
         data()[i] = crSet;
      else
         data()[i] = crUnset;

   //return true;

}


void pixmap::transparent_color(::color::color color)
{

   image32_t crFind(color, color_indexes());

   ::i64 iSize = scan_area();

   for (::i32 i = 0; i < iSize; i++)
   {

      if (data()[i].rgb(color_indexes()) == crFind.rgb(color_indexes()))
      {

         ((::u8*)&data()[i])[3] = 255;

      }
      else
      {

         ((::u8*)&data()[i])[3] = 0;

      }

   }

   //return true;

}


void pixmap::channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, ::color::enum_channel echannel)
{

   ::i32 size = (m_iScan / sizeof(image32_t)) * height();

   ::u8 * puch = (::u8 * )data();

   puch += ((::i32)echannel) % 4;

   for (::i32 i = 0; i < size; i++)
   {

      if (*puch == uchFind)
      {

         *puch = uchSet;

      }
      else
      {

         *puch = uchUnset;

      }

      puch += 4;

   }

   //return true;

}


::color::color pixmap::GetPixel(::i32 x, ::i32 y)
{

   map();

   ::u32 ui = (data() + x + line(y) * (m_iScan / sizeof(image32_t)))->m_u32;

   ::u8* p = (::u8*)&ui;

   ::i32 iOpacity = p[m_colorindexes.m_u8IndexOpacity];

   if (iOpacity == 0)
   {

      return rgb(
         p[m_colorindexes.m_u8IndexRed], 
         p[m_colorindexes.m_u8IndexGreen], 
         p[m_colorindexes.m_u8IndexBlue]);
                            
   }
   else
   {

      return argb(iOpacity,
         p[m_colorindexes.m_u8IndexRed] * 255 / iOpacity,
         p[m_colorindexes.m_u8IndexGreen] * 255 / iOpacity,
         p[m_colorindexes.m_u8IndexBlue] * 255 / iOpacity);

   }

}


// too slow for animation on AMD XP gen_hon.
// TOP SUGGESTION:
// The gradient can't have more then 256 levels of the most bright color
// (white). So creating a radial fill of radius 256 and then using fasting
// stretching algorithms is much faster than calculating radial fill.
void pixmap::RadialFill(::u8 alpha, ::u8 red, ::u8 green, ::u8 blue, ::i32 xCenter, ::i32 yCenter, ::i32 iRadius)
{

   if (iRadius == 0)
   {

      //return false;

      return;

   }

   /*if(version == 0)
   {

   ::i32 iR = iRadius - 1;

   ::i32 xL = xCenter - iR;
   ::i32 xU = xCenter + iR;
   ::i32 yL = yCenter - iR;
   ::i32 yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(image32_t))) xU = m_Size.(m_iScan / sizeof(image32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   ::u8 *dst = ((::u8 *)(data() + xL + yL * m_Size.(m_iScan / sizeof(image32_t))));
   ::u32 dwAdd = ((m_Size.(m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
   ::i32 size=m_Size.(m_iScan / sizeof(image32_t))*m_Size.height();
   ::f64 iLevel;

   ::i32 Δx, Δy;
   ::i32 dx0, dy0;
   ::i32 dx1, dy1;
   ::i32 dx2, dy2;
   ::i32 dx3, dy3;
   ::i32 dx4, dy4;
   ::i32 dx5, dy5;
   ::i32 dx6, dy6;
   ::i32 dx7, dy7;
   ::i32 dx8, dy8;
   ::i32 dx9, dy9;
   ::i32 dxA, dyA;
   ::i32 dxB, dyB;
   ::i32 dxC, dyC;
   ::i32 dxD, dyD;
   ::i32 dxE, dyE;
   ::i32 dxF, dyF;

   ulong dr;
   ulong dq;
   ulong dr0, dq0;
   ulong dr1, dq1;
   ulong dr2, dq2;
   ulong dr3, dq3;
   ulong dr4, dq4;
   ulong dr5, dq5;
   ulong dr6, dq6;
   ulong dr7, dq7;
   ulong dr8, dq8;
   ulong dr9, dq9;
   ulong drA, dqA;
   ulong drB, dqB;
   ulong drC, dqC;
   ulong drD, dqD;
   ulong drE, dqE;
   ulong drF, dqF;
   ::i32 x, y;

   {
   for(y = yL; y <= yU; y++)
   {
   for(x = xL; x <= xU; x++)
   {
   Δx = abs(x - xCenter);
   Δy = abs(y - yCenter);
   isqrt((Δx * Δx) + (Δy * Δy), &dr, &dq);
   if(dr < iRadius)
   {
   iLevel = 1.0 - dr * 1.0 / iRadius;
   dst[0] = blue  * iLevel;
   dst[1] = green * iLevel;
   dst[2] = red   * iLevel;
   }
   dst += 4;
   }
   dst += dwAdd;
   }
   }
   }
   else if(version == 1)*/
   {

      ::u8* pbAlloc = (::u8*)malloc(iRadius * iRadius);

      ::u8* pb = pbAlloc;



      ::i32 x, y;
      ::i32 b;

      //         ::i32 r2 = iRadius * iRadius;

      for (y = 0; y < iRadius; y++)
      {
         for (x = y; x < iRadius; x++)
         {
            b = (::i32)(sqrt((::f64)(x * x) + (y * y)) * 255 / iRadius);
            if (b > 255)
               b = 0;
            else
               b = 255 - b;


            pb[x + y * iRadius] = (::u8)b;

            pb[y + x * iRadius] = (::u8)b;

         }
      }


      ::i32 iR = iRadius - 1;

      ::i32 xL = xCenter - iR;
      ::i32 xU = xCenter + iR;
      ::i32 yL = yCenter - iR;
      ::i32 yU = yCenter + iR;


      if (xL < 0) xL = 0;
      if (xU >= width()) xU = width() - 1;
      if (yL < 0) yL = 0;
      if (yU >= height()) yU = height() - 1;


      ::u8* dst = ((::u8*)(data() + xL + yL * (m_iScan / sizeof(image32_t))));
      ::u32 dwAdd = (((m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
      //         ::i64 size = area();

      ::i32 Δx, Δy;

      // Top Left

      for (y = yL; y <= yU; y++)
      {
         for (x = xL; x <= xU; x++)
         {
            Δx = abs(x - xCenter);
            Δy = abs(y - yCenter);
            b = pb[Δx + Δy * iRadius];

            dst[0] = (::u8)(blue * b / 255);
            dst[1] = (::u8)(green * b / 255);
            dst[2] = (::u8)(red * b / 255);
            dst[3] = (::u8)(alpha * b / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

      free(pbAlloc);

   }

   //return true;

}


void pixmap::RadialFill(
   ::u8 alpha1, ::u8 red1, ::u8 green1, ::u8 blue1,
   ::u8 alpha2, ::u8 red2, ::u8 green2, ::u8 blue2,
   ::i32 xCenter, ::i32 yCenter, ::i32 iRadius)
{
   if (iRadius == 0)
      //return false;
      return;

   map();
   /*if(version == 0)
   {

   ::i32 iR = iRadius - 1;

   ::i32 xL = xCenter - iR;
   ::i32 xU = xCenter + iR;
   ::i32 yL = yCenter - iR;
   ::i32 yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(image32_t))) xU = m_Size.(m_iScan / sizeof(image32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   ::u8 *dst = ((::u8 *)(data() + xL + yL * m_Size.(m_iScan / sizeof(image32_t))));
   ::u32 dwAdd = ((m_Size.(m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
   ::i32 size=m_Size.(m_iScan / sizeof(image32_t))*m_Size.height();
   ::f64 iLevel;

   ::i32 Δx, Δy;
   ::i32 dx0, dy0;
   ::i32 dx1, dy1;
   ::i32 dx2, dy2;
   ::i32 dx3, dy3;
   ::i32 dx4, dy4;
   ::i32 dx5, dy5;
   ::i32 dx6, dy6;
   ::i32 dx7, dy7;
   ::i32 dx8, dy8;
   ::i32 dx9, dy9;
   ::i32 dxA, dyA;
   ::i32 dxB, dyB;
   ::i32 dxC, dyC;
   ::i32 dxD, dyD;
   ::i32 dxE, dyE;
   ::i32 dxF, dyF;

   ulong dr;
   ulong dq;
   ulong dr0, dq0;
   ulong dr1, dq1;
   ulong dr2, dq2;
   ulong dr3, dq3;
   ulong dr4, dq4;
   ulong dr5, dq5;
   ulong dr6, dq6;
   ulong dr7, dq7;
   ulong dr8, dq8;
   ulong dr9, dq9;
   ulong drA, dqA;
   ulong drB, dqB;
   ulong drC, dqC;
   ulong drD, dqD;
   ulong drE, dqE;
   ulong drF, dqF;
   ::i32 x, y;

   {
   for(y = yL; y <= yU; y++)
   {
   for(x = xL; x <= xU; x++)
   {
   Δx = abs(x - xCenter);
   Δy = abs(y - yCenter);
   isqrt((Δx * Δx) + (Δy * Δy), &dr, &dq);
   if(dr < iRadius)
   {
   iLevel = 1.0 - dr * 1.0 / iRadius;
   dst[0] = blue  * iLevel;
   dst[1] = green * iLevel;
   dst[2] = red   * iLevel;
   }
   dst += 4;
   }
   dst += dwAdd;
   }
   }
   }
   else if(version == 1)*/
   {

      //         memory mem;
      //
      //         mem.set_size((iRadius * iRadius) + 4);
      //
      //         ::u8 * pbAlloc = mem.data();

      //
      //         ::u8 * pb = pbAlloc;

      //
      //
      //         ::i32 x, y;
      //         ::i32 b;
      //
      ////         ::i32 r2 = iRadius * iRadius;
      //
      //         for(y = 0; y < iRadius; y++)
      //         {
      //            for(x = y; x < iRadius; x++)
      //            {
      //
      //               b = (::i32) (sqrt((::f64) (x * x) + (y * y)) * 255 / iRadius);
      //
      //               if(b > 255)
      //                  b = 255;
      //
      //
      //               pb[x + y * iRadius] = (::u8) b;

      //               pb[y + x * iRadius] = (::u8) b;

      //            }
      //         }


      ::i32 iR = iRadius;

      ::i32 xL = xCenter - iR;
      ::i32 xU = xCenter + iR;
      ::i32 yL = yCenter - iR;
      ::i32 yU = yCenter + iR;


      if (xL < 0) xL = 0;
      if (xU > width()) xU = width();
      if (yL < 0) yL = 0;
      if (yU > height()) yU = height();


      ::u8* dst = ((::u8*)(data() + xL + yL * (m_iScan / sizeof(image32_t))));
      ::u32 dwAdd = (((m_iScan / sizeof(image32_t)) - xU) + xL) * 4;
      //         ::i64 size = area();

      ::f64 Δx, Δy;

      ::f64 dRadius = 255.0 / (::f64)iRadius;

      ::u8 bComp;

      ::i32 b;

      // Top Left

      ::i32 y;
      ::i32 x;

      for (y = yL; y < yU; y++)
      {
         for (x = xL; x < xU; x++)
         {
            Δx = abs(x - xCenter);
            Δy = abs(y - yCenter);
            b = (::i32)(sqrt((Δx * Δx) + (Δy * Δy)) * dRadius);

            if (b > 255)
            {
               b = 255;
            }

            bComp = 255 - b;
            dst[0] = (::u8)(((blue1 * bComp) + (blue2 * b)) / 255);
            dst[1] = (::u8)(((green1 * bComp) + (green2 * b)) / 255);
            dst[2] = (::u8)(((red1 * bComp) + (red2 * b)) / 255);
            dst[3] = (::u8)(((alpha1 * bComp) + (alpha2 * b)) / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

   }

   //return true;

}



// void pixmap::SetIconMask(::pixmap::icon* picon, ::i32 cx, ::i32 cy)
// {
//
//    //      throw ::exception(todo);
//    //
//    //      // xxx todo create(width(), height());
//    //
//    //      if (width() <= 0 || height() <= 0)
//    //         return;
//    //
//    //
//    //
//    //
//    //      // White blend image_impl
//    //      image_impl ppixmap1;
//    //
//    //      throw ::exception(todo);
//    //
//    //      // xxx todo ppixmap1->create_as_descriptor(width(), height());
//    //
//    //      ppixmap1->Fill(0, 255, 255, 255);
//    //
//    //#ifdef UNIVERSAL_WINDOWS
//    //
//    //      throw ::interface_only();
//    //
//    //#else
//    //
//    //      ppixmap1->pgraphics->DrawIcon(
//    //         0, 0,
//    //         picon,
//    //         width(), height(),
//    //         0,
//    //         nullptr,
//    //         DI_IMAGE | DI_MASK);
//    //
//    //#endif
//    //
//    //      // Black blend image_impl
//    //      image_impl ppixmap2;
//    //
//    //
//    //      throw ::exception(todo);
//    //
//    //      // xxx todo ppixmap2->create_as_descriptor(width(), height());
//    //      ppixmap2->Fill(0, 0, 0, 0);
//    //
//    //#ifdef UNIVERSAL_WINDOWS
//    //
//    //      throw ::interface_only();
//    //
//    //#else
//    //
//    //      ppixmap2->pgraphics->DrawIcon(
//    //         0, 0,
//    //         picon,
//    //         width(), height(),
//    //         0,
//    //         nullptr,
//    //         DI_IMAGE | DI_MASK);
//    //
//    //#endif
//    //
//    //      // Mask image_impl
//    //      image_impl imageM;
//    //      throw ::exception(todo);
//    //
//    //      // xxx todo imageM.create(width(), height());
//    //
//    //#ifdef UNIVERSAL_WINDOWS
//    //
//    //      throw ::interface_only();
//    //
//    //#else
//    //
//    //      imageM.pgraphics->DrawIcon(
//    //         0, 0,
//    //         picon,
//    //         width(), height(),
//    //         0,
//    //         nullptr,
//    //         DI_MASK);
//    //
//    //#endif
//    //
//    //      ::u8 * r1 = (::u8 *)ppixmap1->data();
//    //      ::u8 * r2 = (::u8 *)ppixmap2->data();
//    //      ::u8 * srcM = (::u8 *)imageM.data();
//    //      ::u8 * dest = (::u8 *)data();
//    //      ::i32 iSize = width()*height();
//    //
//    //      ::u8 b;
//    //      ::u8 bMax;
//    //      while (iSize-- > 0)
//    //      {
//    //         if (srcM[0] == 255)
//    //         {
//    //            bMax = 0;
//    //         }
//    //         else
//    //         {
//    //            bMax = 0;
//    //            b = (::u8)(r1[0] - r2[0]);
//    //            bMax = maximum(b, bMax);
//    //            b = (::u8)(r1[1] - r2[1]);
//    //            bMax = maximum(b, bMax);
//    //            b = (::u8)(r1[2] - r2[2]);
//    //            bMax = maximum(b, bMax);
//    //            bMax = 255 - bMax;
//    //         }
//    //         dest[0] = bMax;
//    //         dest[1] = bMax;
//    //         dest[2] = bMax;
//    //         dest += 4;
//    //         srcM += 4;
//    //         r1 += 4;
//    //         r2 += 4;
//    //      }
//    //
//
//    //return true;
//
// }


void pixmap::rotate(const ::f64_angle & angle, ::f64 dScale)
{

   ::pixmap_pointer ppixmap = this->clone();

   rotate(ppixmap, angle, dScale);

}


void pixmap::rotate(::pixmap * ppixmap, const ::f64_angle & angle, ::f64 dScale)
{

   if (dScale == 1.0)
   {

      if (angle.degree() == 90.0)
      {

         create_as_descriptor({ppixmap->height(), ppixmap->width()});

         //if (!create({ ppixmap->height(), ppixmap->width() }))
         //{

         //   return false;

         //}

         map();

         ppixmap->map();

         ::i32 cx = ppixmap->width();

         ::i32 cy = ppixmap->height();

         ::i32 s = m_iScan / sizeof(image32_t);

         ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

         for (::i32 i = 0; i < cx; i++)
         {

            for (::i32 j = 0; j < cy; j++)
            {

               image32()[i * s + j] = ppixmap->image32()[(cy - j - 1) * srcS + i];

            }

         }

         //return ppixmap;

         return;

      }
      else if (angle.degree() == 180.0)
      {

         create_as_descriptor(ppixmap->size());

         map();

         ppixmap->map();

         ::i32 cx = width();

         ::i32 cy = height();

         ::i32 s = m_iScan / sizeof(image32_t);

         ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

         for (::i32 i = 0; i < cy; i++)
         {

            for (::i32 j = 0; j < cx; j++)
            {

               image32()[(cy - i - 1) * s + (cx - j - 1)] = ppixmap->image32()[i * srcS + j];

            }

         }

         return;

      }
      else if (angle.degree() == 270.0)
      {

         create_as_descriptor({ppixmap->height(), ppixmap->width()});

         map();

         ppixmap->map();

         ::i32 cx = ppixmap->width();

         ::i32 cy = ppixmap->height();

         ::i32 s = m_iScan / sizeof(image32_t);

         ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

         for (::i32 i = 0; i < cx; i++)
         {

            for (::i32 j = 0; j < cy; j++)
            {

               image32()[i * s + j] = ppixmap->image32()[j * srcS + (cx - i - 1)];

            }

         }

         return;

      }

   }

   ::f64 o = angle.radian();

   ::i32 a = (::i32)(::fabs((::f64)ppixmap->width() * ::sin(o)) + ::fabs((::f64)ppixmap->height() * ::cos(o)));

   ::i32 b = (::i32)(::fabs((::f64)ppixmap->width() * ::cos(o)) + ::fabs((::f64)ppixmap->height() * ::sin(o)));

   a = (::i32)(a * dScale);

   b = (::i32)(b * dScale);

   if (a <= 0 || b <= 0)
   {

      //return nullptr;

      return;

   }

   create_as_descriptor({b, a});

   map();

   ppixmap->map();

   ::i32 wSource = ppixmap->width();

   ::i32 hSource = ppixmap->height();

   auto pdataSource = ppixmap->image32();

   ::i32 wTarget = width();

   ::i32 hTarget = height();

   auto pdataTarget = image32();

   ::i32 l = maximum(wTarget, hTarget);

   ::i32 jmax = minimum(l, hTarget / 2);

   ::i32 jmin = -jmax;

   ::i32 imax = minimum(l, wTarget / 2);

   ::i32 imin = -imax;

   ::i32 xoff = wSource / 2;

   ::i32 yoff = hSource / 2;

   //::f64 o = dAngle * pi() / 180.0;

   ::i32 ioff = wTarget / 2;

   ::i32 joff = hTarget / 2;

   ::i32 dsw = m_iScan / sizeof(image32_t);

   ::i32 ssw = ppixmap->m_iScan / sizeof(image32_t);

   ::f64 dCos = ::cos(o) * dScale;

   ::f64 dSin = ::sin(o) * dScale;

   ::i32 x;

   ::i32 y;

   for (::i32 j = jmin; j < jmax; j++)
   {

      for (::i32 i = imin; i < imax; i++)
      {

         x = (::i32)fabs((dCos * i - dSin * j) + xoff);

         y = (::i32)fabs((dSin * i + dCos * j) + yoff);

         x %= wSource;

         y %= hSource;

         pdataTarget[(j + joff) * dsw + (i + ioff)] = pdataSource[y * ssw + x];

      }

   }

}


::pixmap_pointer pixmap::rotated(const ::f64_angle & angle, ::f64 dScale)
{

   if (dScale == 1.0)
   {

      if (angle.degree() == 90.0)
      {

            auto ppixmap = system()->create_pixmap({height(), width()});

            //if (!create({ ppixmap->height(), ppixmap->width() }))
            //{

            //   return false;

            //}

            map();

            ppixmap->map();

            ::i32 cx = width();

            ::i32 cy = height();

            ::i32 s = m_iScan / sizeof(image32_t);

            ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

            for (::i32 i = 0; i < cx; i++)
            {

               for (::i32 j = 0; j < cy; j++)
               {

                  ppixmap->image32()[i * s + j] = image32()[(cy - j - 1) * srcS + i];

               }

            }

            return ppixmap;

         }

      else  if (angle.degree() == 180.0)
      {

         auto ppixmap = ::system()->create_pixmap(size());



         //map();

         //ppixmap->map();

         ::i32 cx = width();

         ::i32 cy = height();

         ::i32 s = m_iScan / sizeof(image32_t);

         ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

         for (::i32 i = 0; i < cy; i++)
         {

            for (::i32 j = 0; j < cx; j++)
            {

               ppixmap->image32()[(cy - i - 1) * s + (cx - j - 1)] = image32()[i * srcS + j];

            }

         }

         return ppixmap;
      }
      else if (angle.degree() ==270.0)
      {

               auto ppixmap = ::system()->create_pixmap({ height(), width() });

            //map();

            //ppixmap->map();

            ::i32 cx = width();

            ::i32 cy = height();

            ::i32 s = m_iScan / sizeof(image32_t);

            ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

            for (::i32 i = 0; i < cx; i++)
            {

               for (::i32 j = 0; j < cy; j++)
               {

                  ppixmap->image32()[i * s + j] = image32()[j * srcS + (cx - i - 1)];

               }

            }

            return ppixmap;

         }

   }

   ::f64 o = angle.radian();

   ::i32 a = (::i32)(::fabs((::f64)width() * ::sin(o)) + ::fabs((::f64)height() * ::cos(o)));

   ::i32 b = (::i32)(::fabs((::f64)width() * ::cos(o)) + ::fabs((::f64)height() * ::sin(o)));

   a = (::i32) (a * dScale);

   b = (::i32) (b * dScale);

   if (a <= 0 || b <= 0)
   {

      return nullptr;

   }

   auto ppixmap = ::system()->create_pixmap({ b, a });

   //map();

   //ppixmap->map();

   ::i32 wSource = width();

   ::i32 hSource = height();

   auto pdataSource = image32();

   ::i32 wTarget = ppixmap->width();

   ::i32 hTarget = ppixmap->height();

   auto pdataTarget = ppixmap->image32();

   ::i32 l = maximum(wTarget, hTarget);

   ::i32 jmax = minimum(l, hTarget / 2);

   ::i32 jmin = -jmax;

   ::i32 imax = minimum(l, wTarget / 2);

   ::i32 imin = -imax;

   ::i32 xoff = wSource / 2;

   ::i32 yoff = hSource / 2;

   //::f64 o = dAngle * pi() / 180.0;

   ::i32 ioff = wTarget / 2;

   ::i32 joff = hTarget / 2;

   ::i32 dsw = m_iScan / sizeof(image32_t);

   ::i32 ssw = ppixmap->m_iScan / sizeof(image32_t);

   ::f64 dCos = ::cos(o) * dScale;

   ::f64 dSin = ::sin(o) * dScale;

   ::i32 x;

   ::i32 y;

   for (::i32 j = jmin; j < jmax; j++)
   {

      for (::i32 i = imin; i < imax; i++)
      {

         x = (::i32)fabs((dCos * i - dSin * j) + xoff);

         y = (::i32)fabs((dSin * i + dCos * j) + yoff);

         x %= wSource;

         y %= hSource;

         pdataTarget[(j + joff) * dsw + (i + ioff)] = pdataSource[y * ssw + x];

      }

   }

   return ppixmap;

}


//::pixmap_pointer pixmap::rotated(const angle& angle, ::f64 dScale)
//{
//
//   map();
//
//   ppixmap->map();
//
//   ::i32 wSource = ppixmap->width();
//
//   ::i32 hSource = ppixmap->height();
//
//   auto pdataSource = ppixmap->image32();
//
//   ::i32 wTarget = width();
//
//   ::i32 hTarget = height();
//
//   auto pdataTarget = image32();
//
//   if (wSource < 2 || hSource < 2 || ::is_null(pdataSource)) return;
//
//   if (wTarget < 2 || hTarget < 2 || ::is_null(pdataTarget)) return;
//
//   ::i32 l = maximum(wTarget, hTarget);
//
//   ::i32 jmax = minimum(l, hTarget / 2);
//
//   ::i32 jmin = -jmax;
//
//   ::i32 imax = minimum(l, wTarget / 2);
//
//   ::i32 imin = -imax;
//
//   ::i32 xoff = wSource / 2;
//
//   ::i32 yoff = hSource / 2;
//
//   ::f64 o = dAngle * pi() / 180.0;
//
//   ::i32 ioff = wTarget / 2;
//
//   ::i32 joff = hTarget / 2;
//
//   ::i32 dsw = m_iScan / sizeof(image32_t);
//
//   ::i32 ssw = ppixmap->m_iScan / sizeof(image32_t);
//
//   ::f64 dCos = ::cos(dAngle * pi() / 180.0) * dScale;
//
//   ::f64 dSin = ::sin(dAngle * pi() / 180.0) * dScale;
//
//   ::i32 x;
//
//   ::i32 y;
//
//   for (::i32 j = jmin; j < jmax; j++)
//   {
//
//      for (::i32 i = imin; i < imax; i++)
//      {
//
//         x = (::i32)fabs((dCos * i - dSin * j) + xoff);
//
//         y = (::i32)fabs((dSin * i + dCos * j) + yoff);
//
//         x %= wSource;
//
//         y %= hSource;
//
//         pdataTarget[(j + joff) * dsw + (i + ioff)] = pdataSource[y * ssw + x];
//
//      }
//
//   }
//
//   //return true;
//
//}
//

void pixmap::Rotate034(::pixmap * ppixmap, ::f64 dAngle, ::f64 dScale)
{

   //map();
   //ppixmap->map();

   auto hdst = height();
   auto wdst = width();

   auto hsrc = ppixmap->height();
   auto wsrc = ppixmap->width();

   if (hdst != hsrc)
   {

      informationf("different height");

   }

   if (wdst != wsrc)
   {

      informationf("different width");

   }

   auto hdstmid = hdst / 2.0;
   auto wdstmid = wdst / 2.0;

   ::i32 ihdstmid = (::i32)hdstmid;

   auto hsrcmid = hsrc / 2.0;
   auto wsrcmid = wsrc / 2.0;

   //::i32 l = maximum(w, h);

   ::i32 jdstmin = (::i32)-hdstmid;
   ::i32 jdstmax = jdstmin + hdst;
   ::i32 idstmin = (::i32)-wdstmid;
   ::i32 idstmax = idstmin + wdst;

   ::i32 k = 0;

   ::f64 dCos = ::cos(dAngle * π / 180.0) * dScale;

   ::f64 dSin = ::sin(dAngle * π / 180.0) * dScale;

   auto pdataSrc = ppixmap->data();

   auto pdataDst = data();

   ::i32 strideSrc = ppixmap->m_iScan / sizeof(image32_t);

   ::i32 strideDst = m_iScan / sizeof(image32_t);

   for (::i32 jdst = jdstmin; jdst < jdstmax; jdst++)
   {

      ::i32 lineDst = (::i32)(jdst + ihdstmid);

      if (lineDst < 0)
      {

         informationf("pixmap::Rotate034 lineDst < 0");

      }

      image32_t* pline = pdataDst + (lineDst * strideDst);

      for (::i32 idst = idstmin; idst < idstmax; idst++)
      {

         ::i32 xsrc, ysrc;

         ::f64 dj = jdst;
         ::f64 di = idst;

         xsrc = (::i32)((dCos * di - dSin * dj) + wsrcmid);
         ysrc = (::i32)((dSin * di + dCos * dj) + hsrcmid);

         image32_t colorSrc(::color::black, color_indexes());

         if (xsrc >= 0 && xsrc < wsrc && ysrc >= 0 && ysrc < hsrc)
         {

            colorSrc = pdataSrc[ysrc * strideSrc + xsrc];

         }

         *pline = colorSrc;

         pline++;

      }

   }

   //return true;

}


//void pixmap::rotated(::pixmap * ppixmap, const ::i32_rectangle& rectangle, ::f64 dAngle, ::f64 dScale)
//
//{
//
//   ::i32 l = maximum(width(), height());
//
//   ::i32 jmax = minimum(l, height() / 2);
//   ::i32 jmin = -jmax;
//   ::i32 imax = minimum(l, width() / 2);
//   ::i32 imin = -imax;
//
//   ::i32 joff = height() / 2 + rectangle.left;
//
//   ::i32 ioff = width() / 2 + rectangle.top;
//
//   ::i32 stride_unit = m_iScan / sizeof(image32_t);
//   //::i32 iAngle = iStep % 360;
//   //::i32 iAngle = iStep;
//   //::i32 iAngle = 1;
//   //::i32 k = 0;
//
//   /*     for ( ::i32 j=jmin; j<jmax; j++ )
//   {
//   for ( ::i32 i=imin; i<imax; i++ )
//   {
//   ::i32 x, y;
//
//   // A Combination of a 2d Translation/rotation/Scale Matrix
//   x=::i32(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
//   y=::i32(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
//   data()[(j+joff)*width()+(i+ioff)]=
//   ppixmap->data()[abs(y%height())*width()+abs(x%width())];
//   //k++;
//   }
//   (j+joff)*width()+(i+ioff)
//   }*/
//
//   ::i32 k = 0;
//   ::f64 dCos = ::cos(dAngle * pi() / 180.0) * dScale;
//   ::f64 dSin = ::sin(dAngle * pi() / 180.0) * dScale;
//   ::i32 cx1 = width() - 1;
//   ::i32 cy1 = height() - 1;
//   for (::i32 j = jmin; j < jmax; j++)
//   {
//      for (::i32 i = imin; i < imax; i++)
//      {
//         ::i32 x, y;
//
//         // A Combination of a 2d Translation/rotation/Scale Matrix
//         //x=abs((::i32(dCos * i - dSin * j) + ioff) % width());
//         //y=abs((::i32(dSin * i + dCos * j) + joff) % height());
//
//         x = (::i32)fabs((dCos * i - dSin * j) + ioff);
//         y = (::i32)fabs((dSin * i + dCos * j) + joff);
//
//         if ((x / width()) % 2 == 0)
//         {
//            x %= width();
//         }
//         else
//         {
//            x = cx1 - (x % width());
//         }
//
//         if ((y / height()) % 2 == 0)
//         {
//            y %= height();
//         }
//         else
//         {
//            y = cy1 - (y % height());
//         }
//
//         data()[(j + joff) * stride_unit + (i + ioff)] = ppixmap->data()[y * stride_unit + x];
//
//         k++;
//
//      }
//
//   }
//
//   //return true;
//
//}



//void pixmap::rotate90()
//{
//
//   ::pixmap_pointer ppixmap = clone();
//
//   return rotate90(ppixmap);
//
//}
//
//
//void pixmap::rotate180()
//{
//
//   ::pixmap_pointer ppixmap = clone();
//
//   return rotate180(ppixmap);
//
//}
//
//
//void pixmap::rotate270()
//{
//
//   ::pixmap_pointer ppixmap = clone();
//
//   return rotate270(ppixmap);
//
//}


void pixmap::e_rotate_90_flip_horizontally(::pixmap * ppixmap)
{

   create_as_descriptor(ppixmap->size());

   //map();

   //ppixmap->map();

   ::i32 cx = ppixmap->width();

   ::i32 cy = ppixmap->height();

   ::i32 s = m_iScan / sizeof(image32_t);

   ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

   for (::i32 i = 0; i < cx; i++)
   {

      for (::i32 j = 0; j < cy; j++)
      {

         image32()[i * s + j] = ppixmap->image32()[j * srcS + i];

      }

   }

}


void pixmap::e_rotate_180_flip_horizontally(::pixmap * ppixmap)
{

   create_as_descriptor(ppixmap->size());
   
   //map();

   //ppixmap->map();

   ::i32 cx = width();

   ::i32 cy = height();

   ::i32 s = m_iScan / sizeof(image32_t);

   ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

   for (::i32 i = 0; i < cy; i++)
   {

      for (::i32 j = 0; j < cx; j++)
      {

         image32()[i * s + j] = ppixmap->image32()[(cy - i - 1) * srcS + j];

      }

   }

}


void pixmap::e_rotate_270_flip_horizontally(::pixmap * ppixmap)
{

   create_as_descriptor(ppixmap->size());

   //map();

   //ppixmap->map();

   ::i32 cx = ppixmap->width();

   ::i32 cy = ppixmap->height();

   ::i32 s = m_iScan / sizeof(image32_t);

   ::i32 srcS = ppixmap->m_iScan / sizeof(image32_t);

   for (::i32 i = 0; i < cx; i++)
   {

      for (::i32 j = 0; j < cy; j++)
      {

         image32()[i * s + j] = ppixmap->image32()[(cy - j - 1) * srcS + (cx - i - 1)];

      }

   }

}


void pixmap::e_rotate_90_flip_horizontally()
{

   ::pixmap_pointer ppixmap = this->clone();

   return e_rotate_90_flip_horizontally(ppixmap);

}


void pixmap::e_rotate_180_flip_horizontally()
{

   ::pixmap_pointer ppixmap = this->clone();

   return e_rotate_180_flip_horizontally(ppixmap);

}


void pixmap::e_rotate_270_flip_horizontally()
{

   ::pixmap_pointer ppixmap = this->clone();

   return e_rotate_270_flip_horizontally(ppixmap);

}


/// @brief  This function acts only in a cpu buffer
/// @param uch 
void pixmap::fill_byte(uchar uch)
{

   //auto ppixmapThis = map();

   //if (m_bMapped)
   //{

      if (area() <= 0 || data() == nullptr)
      {

         return;

      }

      ::i32 iScan = m_iScan;

      ::i32 iHeight = size().cy;

      if (iScan <= 0 || iHeight <= 0)
      {

         return;

      }

      memory_set(data(), uch, (memsize)(iScan * iHeight));

   //}
   //else 
   //{

   //   auto pgraphics = acquire_graphics();

   //   auto color = argb(uch, uch, uch, uch);

   //   auto ealphamode = pgraphics->alpha_mode();

   //   if (ealphamode != ::draw2d::e_alpha_mode_set)
   //   {

   //      pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //   }

   //   pgraphics->fill_rectangle(::f64_rectangle(m_size), color);

   //   if (ealphamode != ::draw2d::e_alpha_mode_set)
   //   {

   //      pgraphics->set_alpha_mode(ealphamode);

   //   }

   //}

   ////return true;

}


void pixmap::clear(::color::color color)
{

   //if (m_bMapped)
   {

      image32_t u32Color(color, color_indexes());

      ::i64 size = scan_area();

      ::u8 a = color.u8_opacity();
      ::u8 r = color.u8_red();
      ::u8 g = color.u8_green();
      ::u8 b = color.u8_blue();

      r = r * a / 255;

      g = g * a / 255;

      b = b * a / 255;

      if (a == r && a == g && a == b)
      {

         memory_set(image32(), a, m_iScan * height());

         return;

      }

      image32_t u32ColorImage(argb(a, r, g, b), color_indexes());

      image32_t* pcr = image32();

      for (::i64 i = 0; i < size; i++)
      {

         pcr[i] = u32ColorImage;

      }

   }
   // else
   // {
   //
   //    auto pgraphics = acquire_graphics();
   //
   //
   //    if (pgraphics != nullptr)
   //    {
   //
   //       auto ealphamode = pgraphics->alpha_mode();
   //
   //       if (ealphamode != ::draw2d::e_alpha_mode_set)
   //       {
   //
   //          pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //       }
   //
   //       pgraphics->fill_rectangle(rectangle(), color);
   //
   //       if (ealphamode != ::draw2d::e_alpha_mode_set)
   //       {
   //
   //          pgraphics->set_alpha_mode(ealphamode);
   //       }
   //    }
   // }

   //return true;

}


//void pixmap::clear(const ::color::color & colorFill)
//{
//   
//   fill(colorFill);
//   
//}


void pixmap::clear_argb(::i32 a, ::i32 r, ::i32 g, ::i32 b)
{

   if (a == r && a == g && a == b)
   {

      fill_byte(a);

   }
   else
   {

      auto color = argb(a, r, g, b);

      clear(color);

   }

   //return true;

}


::color::color pixmap::GetAverageColor()
{

   //map();

   ::i64 iRLine;

   ::i64 iGLine;

   ::i64 iBLine;

   ::i64 iDiv = width() * height();

   if (iDiv > 0)
   {

      iRLine = 0;

      iGLine = 0;

      iBLine = 0;

      for (::i32 y = 0; y < height(); y++)
      {

         ::u8* pb = ((::u8*)data()) + m_iScan * y;


         for (::i32 x = 0; x < width(); x++)
         {

            iRLine += pb[2];


            iGLine += pb[1];


            iBLine += pb[0];


            pb += 4;


         }

      }

      ::i32 iR = (::i32)(iRLine / iDiv);

      ::i32 iG = (::i32)(iGLine / iDiv);

      ::i32 iB = (::i32)(iBLine / iDiv);

      return rgb(iR, iG, iB);

   }
   else
   {

      return {};

   }

}


::color::color pixmap::GetAverageOpaqueColor()
{

   //map();

   ::f64 dR = 0.0;
   ::f64 dG = 0.0;
   ::f64 dB = 0.0;

   ::i32 iRLine;
   ::i32 iGLine;
   ::i32 iBLine;

   ::f64 dDiv = width() * height();

   if (dDiv > 0)
   {

      for (::i32 y = 0; y < height(); y++)
      {
         iRLine = 0;
         iGLine = 0;
         iBLine = 0;
         ::u8* pb = ((::u8*)data()) + m_iScan * y;

         for (::i32 x = 0; x < width(); x++)
         {
            if (pb[3] == 255)

            {

               iRLine += pb[2];

               iGLine += pb[1];

               iBLine += pb[0];


            }
            pb += 4;

         }
         dR += iRLine / dDiv;
         dG += iGLine / dDiv;
         dB += iBLine / dDiv;
      }
      ::i32 iR = (::i32)dR;
      ::i32 iG = (::i32)dG;
      ::i32 iB = (::i32)dB;
      return rgb(iR, iG, iB);
   }
   else
   {
      
      return {};

   }

}


void pixmap::do_xor(::pixmap * ppixmap)
{

   if (width() != ppixmap->width()
      || height() != ppixmap->height())
   {

      //return false;

      return;

   }

   ::i32 iCount = width() * height();
   ::u32* pd1 = (::u32*)data();

   ::u32* pd2 = (::u32*)ppixmap->data();

   for (::i32 i = 0; i < iCount; i++)
   {
      *pd1 = *pd1 ^ *pd2;

      pd1++;

      pd2++;

   }

   //return true;

}


void pixmap::create_frame(const ::i32_size& size, ::i32 iFrameCount)
{

   ::i32 iSliceCount = (::i32)sqrt((::f64)iFrameCount);

   return create_as_descriptor(size / iSliceCount);

}


void pixmap::set_frame1(void* pdata, ::i32 iFrame, ::i32 iFrameCount)

{
   ::i32 iSliceCount = (::i32)sqrt((::f64)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   ::i32 iFrameWidth = width() / iSliceCount;
   ::i32 iFrameHeight = height() / iSliceCount;
   ::i32 iX = iFrame % iSliceCount;
   ::i32 iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (::i32 y = 0; y < iFrameHeight; y++)
   {
      pdstline = &pdst[y * width()];

      for (::i32 x = 0; x < iFrameWidth; x++)
      {
         *pdstline = *psrc;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void pixmap::set_frame2(void* pdata, ::i32 iFrame, ::i32 iFrameCount)

{

   ::i32 iSliceCount = (::i32)sqrt((::f64)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   ::i32 iFrameWidth = width() / iSliceCount;
   ::i32 iFrameHeight = height() / iSliceCount;
   ::i32 iX = iFrame % iSliceCount;
   ::i32 iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (::i32 y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (::i32 x = 0; x < iFrameWidth; x++)
      {
         *pdstline = *psrc;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void pixmap::xor_image_frame2(void* pdata, ::i32 iFrame, ::i32 iFrameCount)

{
   ::i32 iSliceCount = (::i32)sqrt((::f64)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   ::i32 iFrameWidth = width() / iSliceCount;
   ::i32 iFrameHeight = height() / iSliceCount;
   ::i32 iX = iFrame % iSliceCount;
   ::i32 iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (::i32 y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (::i32 x = 0; x < iFrameWidth; x++)
      {
         pdstline->m_u32 ^= psrc->m_u32;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void pixmap::get_frame(void* pdata, ::i32 iFrame, ::i32 iFrameCount)

{
   ::i32 iSliceCount = (::i32)sqrt((::f64)iFrameCount);
   ::i32 iFrameWidth = width() / iSliceCount;
   ::i32 iFrameHeight = height() / iSliceCount;
   ::i32 iX = iFrame % iSliceCount;
   ::i32 iY = iFrame / iSliceCount;
   image32_t* psrc = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* pdst = (image32_t*)pdata;

   image32_t* psrcline;

   for (::i32 y = 0; y < iFrameHeight; y++)
   {
      psrcline = &psrc[y * width()];

      for (::i32 x = 0; x < iFrameWidth; x++)
      {
         *pdst = *psrcline;

         pdst++;

         psrcline++;

      }
   }

   //return true;

}


bool pixmap::is_rgb_black()
{

   ::i32 iSize = width() * height();

   image32_t* p = data();

   for (::i32 i = 0; i < iSize; i++)
   {

      if ((p->m_u32 & 0x00FFFFFF) != 0)
      {

         return false;

      }

      p++;

   }

   return true;

}


void pixmap::DivideRGB(::i32 iDivide)
{

   if (iDivide == 0)
   {

      return;

   }

   ::i32 iCount = width() * height();

   ::u8* p = ((::u8*)data());

   ::i32 i = 0;

   ::i32 iCount1 = iCount - iCount % 8;

   for (; i < iCount1; i++)
   {

      p[0] /= (::u8)iDivide;

      p[1] /= (::u8)iDivide;

      p[2] /= (::u8)iDivide;


      p[4] /= (::u8)iDivide;

      p[5] /= (::u8)iDivide;

      p[6] /= (::u8)iDivide;


      p[8] /= (::u8)iDivide;

      p[9] /= (::u8)iDivide;

      p[10] /= (::u8)iDivide;


      p[12] /= (::u8)iDivide;

      p[13] /= (::u8)iDivide;

      p[14] /= (::u8)iDivide;


      p[16] /= (::u8)iDivide;

      p[17] /= (::u8)iDivide;

      p[28] /= (::u8)iDivide;


      p[20] /= (::u8)iDivide;

      p[21] /= (::u8)iDivide;

      p[22] /= (::u8)iDivide;


      p[24] /= (::u8)iDivide;

      p[25] /= (::u8)iDivide;

      p[26] /= (::u8)iDivide;


      p[28] /= (::u8)iDivide;

      p[29] /= (::u8)iDivide;

      p[30] /= (::u8)iDivide;


      p += 4 * 8;

   }
   for (; i < iCount; i++)
   {
      p[0] /= (::u8)iDivide;

      p[1] /= (::u8)iDivide;

      p[2] /= (::u8)iDivide;

      p += 4;

   }

   //return true;

}


void pixmap::DivideARGB(::i32 iDivide)
{

   if (iDivide == 0)
   {

      return;

   }

   ::i32 iCount = width() * height();

   ::u8* p = ((::u8*)data());

   for (::i32 i = 0; i < iCount; i++)
   {
      p[0] /= (::u8)iDivide;

      p[1] /= (::u8)iDivide;

      p[2] /= (::u8)iDivide;

      p[3] /= (::u8)iDivide;

      p += 4;

   }

   //return true;

}


void pixmap::DivideA(::i32 iDivide)
{

   if (iDivide == 0)
   {

      //return false;

      return;

   }

   ::i32 iCount = width() * height();

   ::u8* p = ((::u8*)data());

   for (::i32 i = 0; i < iCount; i++)
   {
      p[3] /= (::u8)iDivide;

      p += 4;

   }

   //return true;

}


void pixmap::set_mipmap(::image::enum_mipmap emipmap)
{

   if (m_emipmap == emipmap)
   {

      //return true;

      return;

   }

   if (emipmap != ::image::e_mipmap_none)
   {

      return _set_mipmap(emipmap);

   }

   //return true;

}


void pixmap::_set_mipmap(::image::enum_mipmap emipmap)
{

   ASSERT(emipmap != ::image::e_mipmap_none);

   ::pixmap_pointer ppixmap = this->clone();

   ::i32 cxSource = ppixmap->width();

   ::i32 cySource = ppixmap->width();

   ::i32 iSourceScan = ppixmap->scan_size();

   ::f64 cx = cxSource;

   ::f64 cy = cySource;

   if (emipmap == ::image::e_mipmap_isotropic)
   {

      ::f64 newcx = cx + cx / 2.0 - 1.0;

      ::f64 newcy = cy;

      create_as_descriptor({(::i32)newcx, (::i32)newcy});

      //if (!create({ (::i32)newcx, (::i32)newcy }))
      //{

      //   throw ::exception(error_resource);

      //}
      //
      // auto pgraphics = acquire_graphics();
      //
      // pgraphics->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);
      //
       ::i32 x = cxSource;
      //
       ::i32 y = 0;
      //
      // ::pixmap::image_source imagesource(ppixmap);
      //
      // ::f64_rectangle rectangle(::f64_size(cxSource, cySource));
      //
      // ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
      //
      // ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
      //
      // pgraphics->draw(imagedrawing);

      while (cx >= 1.0 && cy >= 1.0)
      {

         cx /= 2.0;

         cy /= 2.0;

         //if (::parallelization::get_priority() == ::e_priority_idle)
         //{

            //map();

            C2PassScale < CBlackmanFilter > scale(1.0);

            scale.Scale(
               &image32()[x + y * m_iScan / sizeof(image32_t)],
               color_indexes(),
               (::u32)cx,
               (::u32)cy,
               m_iScan,
               ppixmap->data(),
               cxSource,
               cySource,
               iSourceScan
            );

         //}
         // else
         // {
         //
         //    ::pixmap::image_source imagesource(ppixmap, ::i32_rectangle_dimension(0, 0, (::i32)cx, (::i32)cy));
         //
         //    auto rectangle = f64_rectangle_dimension(x, y, cx, cy);
         //
         //    ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
         //
         //    ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
         //
         //    pgraphics->draw(imagedrawing);
         //
         // }

         y += (::i32)cy;

      }

      m_emipmap = ::image::e_mipmap_isotropic;

   }
   else
   {

      ::f64 newcx = cx * 2.0 - 1.0;

      ::f64 newcy = cy * 2.0 - 1.0;

      create_as_descriptor({(::i32)newcx, (::i32)newcy});

      //if (!create({ (::i32)newcx, (::i32)newcy }))
      //{

      //   throw ::exception(error_resource);

      //}

      ::i32 Δx;

      ::i32 x = 0;

      ::i32 xPrevious;
      ::i32 yPrevious;
      ::i32 cxPrevious;
      ::i32 cyPrevious;

      xPrevious = 0;
      cxPrevious = cxSource;

      for (Δx = (::i32)cx; Δx > 0; x += Δx, Δx /= 2)
      {

         yPrevious = 0;
         cyPrevious = ppixmap->height();

         for (::i32 y = 0, Δy = (::i32)cy; Δy > 0; y += Δy, Δy /= 2)
         {

            //if (::parallelization::get_priority() == ::e_priority_idle)
            {

               //map();

               C2PassScale < CBlackmanFilter > scale(1.0);

               scale.Scale(
                  &image32()[x + y * m_iScan / sizeof(image32_t)],
                  color_indexes(),
                  Δx,
                  Δy,
                  m_iScan,
                  &ppixmap->image32()[xPrevious + yPrevious * ppixmap->m_iScan / sizeof(image32_t)],
                  cxPrevious,
                  cyPrevious,
                  ppixmap->m_iScan
               );

               yPrevious = y;
               cyPrevious = Δy;
               ppixmap = this;

            }
            // else
            // {
            //
            //    ::pixmap::image_source imagesource(ppixmap, ::i32_rectangle_dimension(0, 0, ppixmap->width(), ppixmap->height()));
            //
            //    auto rectangle = f64_rectangle_dimension(x, y, Δx, Δy);
            //
            //    ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
            //
            //    ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
            //
            //    auto pgraphics = acquire_graphics();
            //
            //    pgraphics->draw(imagedrawing);
            //
            // }

         }

         xPrevious = x;
         cxPrevious = Δx;

      }

      m_emipmap = ::image::e_mipmap_anisotropic;

   }

   size() = ppixmap->size();

   //return true;

}


// void pixmap::set_origin(const ::i32_point& point)
// {
//
//    m_point = point;
//
//    if (!m_bMapped)
//    {
//
//       auto pgraphics = acquire_graphics();
//
//       pgraphics->place_impact_area(point, m_size);
//
//    }
//
//    //return true;
//
// }
//
//
// void pixmap::create_helper_map()
// {
//
//    if (m_pextension && m_pextension->m_pframea)
//    {
//
//       for (auto& pframe : *m_pextension->m_pframea)
//       {
//
//          if (pframe != this)
//          {
//
//             pframe->m_ppixmap->create_helper_map();
//
//          }
//
//       }
//
//    }
//
//    _create_helper_map();
//
//    //return true;
//
// }
//
//
// void pixmap::_create_helper_map()
// {
//
//
//    ::collection::index a;
//
//    a = (::collection::index)(area());
//
//    //return true;
//
//    ::collection::index jNextBoundary;
//    ::collection::index jStart;
//    ::u8* pdata = (::u8*)image32();
//
//    if (pdata == nullptr || a <= 0)
//    {
//
//       //return false;
//
//       return;
//
//    }
//
//    ::collection::index w = width();
//    ::collection::index h = height();
//    ::collection::index sw = w * sizeof(image32_t);
//    ::collection::index aa = w * h;
//    {
//
//       m_memoryPixmap.set_size(a * 2);
//
//       m_memoryPixmap.set(0);
//       ::u8 *opacity = m_memoryPixmap.data();
//
//       for (::collection::index i = 0; i < height(); i++)
//       {
//
//          for (::collection::index j = 0; j < sw; j += 4)
//          {
//
//             if (pdata[i * m_iScan + j + 3] == 255)
//             {
//                jStart = j;
//                jNextBoundary = minimum(j + 960, sw);
//                for (j += 4; j < jNextBoundary; j += 4)
//                {
//                   if (pdata[i * m_iScan + j + 3] != 255)
//                   {
//                      break;
//                   }
//                }
//
//                j -= 4;
//
//                ::collection::index c = (j - jStart) >> 2;
//
//                ::collection::index m = j >> 2;
//
//                ::u8 n = 1;
//
//                ::u8* o = &opacity[(::i32)(i * w)];
//
//                while (c >= 0)
//                {
//
//                   o[m] = n;
//
//                   m--;
//
//                   n++;
//
//                   c--;
//
//                }
//
//             }
//
//          }
//
//       }
//
//    }
//
//    {
//
//       ::u8* transparency = m_memoryPixmap.data() + a;
//
//       for (::collection::index i = 0; i < height(); i++)
//       {
//
//          for (::collection::index j = 0; j < sw; j += 4)
//          {
//
//             if (pdata[i * m_iScan + j + 3] == 0)
//             {
//
//                jStart = j;
//
//                jNextBoundary = minimum(j + 960, sw);
//
//                for (j += 4; j < jNextBoundary; j += 4)
//                {
//
//                   if (pdata[i * m_iScan + j + 3] != 0)
//                   {
//
//                      break;
//
//                   }
//
//                }
//
//                j -= 4;
//
//                ::collection::index c = (j - jStart) >> 2;
//
//                ::collection::index m = j >> 2;
//
//                ::u8 n = 1;
//
//                ::u8* t = &transparency[(::i32)(i * w)];
//
//                while (c >= 0)
//                {
//
//                   t[m] = n;
//
//                   m--;
//
//                   n++;
//
//                   c--;
//
//                }
//
//             }
//
//          }
//
//       }
//
//    }
//
//    //return true;
//
// }

//
// void pixmap::set_size_scaler(::f64 dSizeScaler)
// {
//
//    m_dSizeScaler = dSizeScaler;
//
//    //if (!m_bMapped)
//    //{
//
//       //auto pgraphics = acquire_graphics();
//
//       //pgraphics->m_dSizeScaler = dSizeScaler;
//
//    //}
//
//    //return true;
//
// }


//void pixmap::set_alpha_mode(::draw2d::enum_alpha_mode emode)
//{
//
//   m_ealphamode = emode;
//
//   if (!m_bMapped)
//   {
//
//      pgraphics->set_alpha_mode(emode);
//
//   }
//
//   //return true;
//
//}
//

//::i32 pixmap::cos(::i32 i, ::i32 iAngle)
//{
//
//   __UNREFERENCED_PARAMETER(i);
//   __UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   return 0;
//
//}
//
//
//::i32 pixmap::sin(::i32 i, ::i32 iAngle)
//{
//
//   __UNREFERENCED_PARAMETER(i);
//   __UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   //return 0;
//
//}
//
//
//::i32 pixmap::cos10(::i32 i, ::i32 iAngle)
//{
//
//   __UNREFERENCED_PARAMETER(i);
//   __UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   return 0;
//
//}
//
//
//::i32 pixmap::sin10(::i32 i, ::i32 iAngle)
//{
//
//   __UNREFERENCED_PARAMETER(i);
//   __UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   return 0;
//
//}

/*   ::i32 pixmap::width()
   {
      throw ::interface_only();
   }

   ::i32 pixmap::height()
   {
      throw ::interface_only();
   }

   ::i64 pixmap::area()
   {
      return ((::i64) width()) * ((::i64)height());
   }

   i32_size pixmap::size()
   {
      return i64_size(width(), height());
   }*/

//
// ::f64 pixmap::pi() const
// {
//
//    return atan(1.0) * 4.0;
//
// }
//

void pixmap::fill_channel(::i32 intensity, ::color::enum_channel echannel)
{
   //map();
   ::i32 offset = ((::i32)echannel) % 4;
   ::i64 size = scan_area();

   image32_t* pcr = (image32_t*)&((::u8*)image32())[offset];

   ::u8* pb;

   ::i64 iSize32 = size / 32;
   ::i32 i;
   for (i = 0; i < iSize32; i += 32)
   {
      pb = (::u8*)&pcr[i];
      pb[0 * 4] = (::u8)intensity;
      pb[1 * 4] = (::u8)intensity;
      pb[2 * 4] = (::u8)intensity;
      pb[3 * 4] = (::u8)intensity;
      pb[4 * 4] = (::u8)intensity;
      pb[5 * 4] = (::u8)intensity;
      pb[6 * 4] = (::u8)intensity;
      pb[7 * 4] = (::u8)intensity;
      pb[8 * 4] = (::u8)intensity;
      pb[9 * 4] = (::u8)intensity;
      pb[10 * 4] = (::u8)intensity;
      pb[11 * 4] = (::u8)intensity;
      pb[12 * 4] = (::u8)intensity;
      pb[13 * 4] = (::u8)intensity;
      pb[14 * 4] = (::u8)intensity;
      pb[15 * 4] = (::u8)intensity;
      pb[16 * 4] = (::u8)intensity;
      pb[17 * 4] = (::u8)intensity;
      pb[18 * 4] = (::u8)intensity;
      pb[19 * 4] = (::u8)intensity;
      pb[20 * 4] = (::u8)intensity;
      pb[21 * 4] = (::u8)intensity;
      pb[22 * 4] = (::u8)intensity;
      pb[23 * 4] = (::u8)intensity;
      pb[24 * 4] = (::u8)intensity;
      pb[25 * 4] = (::u8)intensity;
      pb[26 * 4] = (::u8)intensity;
      pb[27 * 4] = (::u8)intensity;
      pb[28 * 4] = (::u8)intensity;
      pb[29 * 4] = (::u8)intensity;
      pb[30 * 4] = (::u8)intensity;
      pb[31 * 4] = (::u8)intensity;
   }

   for (i = 0; i < size; i++)
   {
      *((::u8*)&pcr[i]) = (::u8)intensity;
   }

   //return true;

}


void pixmap::white_fill_channel(::i32 intensity, ::color::enum_channel echannel)
{
   //map();
   ::i32 offset = ((::i32)echannel) % 4;
   ::i64 size = scan_area();

   image32_t* pcr = (image32_t*)&((::u8*)image32())[offset];

   //      ::u8 * pb;

   ::i64 iSize32 = size / 32;
   ::i32 i;
   //      for (i=0; i < iSize32; i+=32 )
   //      {
   //         pb = (::u8 *) &pcr[i];
   //         pb[0 * 4] = (::u8) intensity;
   //         pb[1 * 4] = (::u8) intensity;
   //         pb[2 * 4] = (::u8) intensity;
   //         pb[3 * 4] = (::u8) intensity;
   //         pb[4 * 4] = (::u8) intensity;
   //         pb[5 * 4] = (::u8) intensity;
   //         pb[6 * 4] = (::u8) intensity;
   //         pb[7 * 4] = (::u8) intensity;
   //         pb[8 * 4] = (::u8) intensity;
   //         pb[9 * 4] = (::u8) intensity;
   //         pb[10 * 4] = (::u8) intensity;
   //         pb[11 * 4] = (::u8) intensity;
   //         pb[12 * 4] = (::u8) intensity;
   //         pb[13 * 4] = (::u8) intensity;
   //         pb[14 * 4] = (::u8) intensity;
   //         pb[15 * 4] = (::u8) intensity;
   //         pb[16 * 4] = (::u8) intensity;
   //         pb[17 * 4] = (::u8) intensity;
   //         pb[18 * 4] = (::u8) intensity;
   //         pb[19 * 4] = (::u8) intensity;
   //         pb[20 * 4] = (::u8) intensity;
   //         pb[21 * 4] = (::u8) intensity;
   //         pb[22 * 4] = (::u8) intensity;
   //         pb[23 * 4] = (::u8) intensity;
   //         pb[24 * 4] = (::u8) intensity;
   //         pb[25 * 4] = (::u8) intensity;
   //         pb[26 * 4] = (::u8) intensity;
   //         pb[27 * 4] = (::u8) intensity;
   //         pb[28 * 4] = (::u8) intensity;
   //         pb[29 * 4] = (::u8) intensity;
   //         pb[30 * 4] = (::u8) intensity;
   //         pb[31 * 4] = (::u8) intensity;
   //      }


   for (i = 0; i < size; i++)
   {

      *((::u8*)&pcr) = (::u8)(((::i32)intensity * (::i32)*((::u8*)&pcr)) / 255);

      pcr++;

   }

   //return true;

}




void pixmap::all_channels_copy(::color::enum_channel echannelSrc, ::pixmap * ppixmap)
{

   if (size() != ppixmap->size())
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   //auto mapThis = map();

   if (image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   //auto ppixmapImage = ppixmap->map();

   if (ppixmap->image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   echannelSrc = (::color::enum_channel)(((::i32)echannelSrc) % 4);

   ::u8 * pdataDst = (::u8 *)data();

   ::u8 * pdataSrc = (::u8 *)ppixmap->data() + ((::i32)echannelSrc);

   for (::i32 y = 0; y < height(); y++)
   {

      ::u8 * pdst = &pdataDst[m_iScan * y];

      ::u8 * psrc = &pdataSrc[ppixmap->m_iScan * y];

      for (::i32 x = 0; x < width(); x++)
      {

         pdst[0] = *psrc;
         pdst[1] = *psrc;
         pdst[2] = *psrc;
         pdst[3] = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}


void pixmap::tint(::pixmap * ppixmap, ::color::color color)
{

   create_as_descriptor(ppixmap->size());


   /*{

      return false;

   }*/

   //map();

   ::u8* src = (::u8*)ppixmap->image32();
   ::u8* dst = (::u8*)image32();
   ::i64 size = scan_area();

   ::u8 uchR = (::u8)color.u8_red();
   ::u8 uchG = (::u8)color.u8_green();
   ::u8 uchB = (::u8)color.u8_blue();

   //      ::i32 i = 0;;


   //while (size > 16)
   //{
   //   //dst[3] = dst[i];
   //   dst[0] = (uchB * src[3]) >> 8;
   //   dst[1] = (uchG * src[3]) >> 8;
   //   dst[2] = (uchR * src[3]) >> 8;
   //   dst[3] = src[3];

   //   dst[4] = (uchB * src[7]) >> 8;
   //   dst[5] = (uchG * src[7]) >> 8;
   //   dst[6] = (uchR * src[7]) >> 8;
   //   dst[7] = src[7];

   //   dst[8] = (uchB * src[11]) >> 8;
   //   dst[9] = (uchG * src[11]) >> 8;
   //   dst[10] = (uchR * src[11]) >> 8;
   //   dst[11] = src[11];

   //   dst[12] = (uchB * src[15]) >> 8;
   //   dst[13] = (uchG * src[15]) >> 8;
   //   dst[14] = (uchR * src[15]) >> 8;
   //   dst[15] = src[15];

   //   dst[16] = (uchB * src[19]) >> 8;
   //   dst[17] = (uchG * src[19]) >> 8;
   //   dst[18] = (uchR * src[19]) >> 8;
   //   dst[19] = src[19];

   //   dst[20] = (uchB * src[23]) >> 8;
   //   dst[21] = (uchG * src[23]) >> 8;
   //   dst[22] = (uchR * src[23]) >> 8;
   //   dst[23] = src[23];

   //   dst[24] = (uchB * src[27]) >> 8;
   //   dst[25] = (uchG * src[27]) >> 8;
   //   dst[26] = (uchR * src[27]) >> 8;
   //   dst[27] = src[27];

   //   dst[28] = (uchB * src[31]) >> 8;
   //   dst[29] = (uchG * src[31]) >> 8;
   //   dst[30] = (uchR * src[31]) >> 8;
   //   dst[31] = src[31];

   //   dst[32] = (uchB * src[35]) >> 8;
   //   dst[33] = (uchG * src[35]) >> 8;
   //   dst[34] = (uchR * src[35]) >> 8;
   //   dst[35] = src[35];

   //   dst[36] = (uchB * src[39]) >> 8;
   //   dst[37] = (uchG * src[39]) >> 8;
   //   dst[38] = (uchR * src[39]) >> 8;
   //   dst[39] = src[39];

   //   dst[40] = (uchB * src[43]) >> 8;
   //   dst[41] = (uchG * src[43]) >> 8;
   //   dst[42] = (uchR * src[43]) >> 8;
   //   dst[43] = src[43];

   //   dst[44] = (uchB * src[47]) >> 8;
   //   dst[45] = (uchG * src[47]) >> 8;
   //   dst[46] = (uchR * src[47]) >> 8;
   //   dst[47] = src[47];

   //   dst[48] = (uchB * src[51]) >> 8;
   //   dst[49] = (uchG * src[51]) >> 8;
   //   dst[50] = (uchR * src[51]) >> 8;
   //   dst[51] = src[51];

   //   dst[52] = (uchB * src[55]) >> 8;
   //   dst[53] = (uchG * src[55]) >> 8;
   //   dst[54] = (uchR * src[55]) >> 8;
   //   dst[55] = src[55];

   //   dst[56] = (uchB * src[59]) >> 8;
   //   dst[57] = (uchG * src[59]) >> 8;
   //   dst[58] = (uchR * src[59]) >> 8;
   //   dst[59] = src[59];

   //   dst[60] = (uchB * src[63]) >> 8;
   //   dst[61] = (uchG * src[63]) >> 8;
   //   dst[62] = (uchR * src[63]) >> 8;
   //   dst[63] = src[63];

   //   dst += 4 * 16;
   //   src += 4 * 16;
   //   size -= 16;
   //}
   //::u8 tableR[256];
   //::u8 tableG[256];
   //::u8 tableB[256];
   //for (::collection::index i = 0; i < 255; i++)
   //{
   //   tableR[i] = (uchR * i) >> 8;
   //   tableG[i] = (uchG * i) >> 8;
   //   tableB[i] = (uchB * i) >> 8;
   //}
   //while (size > 0)
   //{
   //   dst[0] = tableR[src[3]];
   //   dst[1] = tableG[src[3]];
   //   dst[2] = tableB[src[3]];
   //   dst += 4;
   //   src += 4;
   //   size--;
   //}

   image32_t o(argb(255, uchR, uchG, uchB), color_indexes());

   while (size > 0)
   {

      ::u8 bA = src[3];

      if (bA == 0)
      {

         *((image32_t *)dst) = {};

      }
      else if (bA == 255)
      {

         *((image32_t*)dst) = o;

      }
      else
      {
         dst[0] = (uchB * bA) >> 8;
         dst[1] = (uchG * bA) >> 8;
         dst[2] = (uchR * bA) >> 8;
         dst[3] = bA;
      }

      dst += 4;
      src += 4;
      size--;
   }

   //return true;

}


void pixmap::saturation(::f64 dRate)
{

   //map();

   ::u8* dst = (::u8*)image32();

   ::i64 size = scan_area();

   ::i32 iDiv = 255 * 255;

   ::i32 iMul = (::i32)(dRate * (::f64)iDiv);

   while (size > 0)
   {

      ::i32 iMax = maximum(maximum(dst[0], dst[1]), dst[2]);

      ::i32 iMin = minimum(minimum(dst[0], dst[1]), dst[2]);

      ::i32 iMid = (iMax + iMin) / 2;

      dst[0] = ((dst[0] - iMid) * iMul / iDiv) + iMid;

      dst[1] = ((dst[1] - iMid) * iMul / iDiv) + iMid;

      dst[2] = ((dst[2] - iMid) * iMul / iDiv) + iMid;

      dst += 4;

      size--;

   }

   //return true;

}


void pixmap::lightness(::f64 dRate)
{

   rate_rgb(as_byte(dRate * 255.0), 255);

   //return true;

}


void pixmap::opacity(::f64 dRate)
{

   ::i32 iA = as_byte(255. * dRate);

   //map();

   try
   {
      ::u8* puch = (::u8*)data();
      ::i64 iArea = scan_area();
      while (iArea > 0)
      {
         puch[0] = maximum(0, minimum(255, puch[0] * iA / 255));
         puch[1] = maximum(0, minimum(255, puch[1] * iA / 255));
         puch[2] = maximum(0, minimum(255, puch[2] * iA / 255));
         puch[3] = maximum(0, minimum(255, puch[3] * iA / 255));
         puch += 4;
         iArea--;
      }
   }
   catch (...)
   {

   }

   //return true;

}


void pixmap::set_rgb_pre_alpha(::i32 R, ::i32 G, ::i32 B, ::i32 A)
{

   //map();

   ::u8* dst = (::u8*)image32();
   ::i64 size = scan_area();

   ::u8 uchB = (::u8)R;
   ::u8 uchG = (::u8)G;
   ::u8 uchR = (::u8)B;

   //      ::i32 i = 0;;

   while (size > 0)
   {
      //dst[3] = dst[i];
      dst[0] = ((::i32)uchB * (::i32)dst[3] * A) >> 16;
      dst[1] = ((::i32)uchG * (::i32)dst[3] * A) >> 16;
      dst[2] = ((::i32)uchR * (::i32)dst[3] * A) >> 16;
      dst[3] = ((::i32)dst[3] * A) >> 8;
      dst += 4;
      size--;
   }

   while (size > 16)
   {
      //dst[3] = dst[i];
      dst[0] = (uchB * dst[3] * A) >> 16;
      dst[1] = (uchG * dst[3] * A) >> 16;
      dst[2] = (uchR * dst[3] * A) >> 16;
      dst[3] = (dst[3] * A) >> 8;

      dst[4] = (uchB * dst[7] * A) >> 16;
      dst[5] = (uchG * dst[7] * A) >> 16;
      dst[6] = (uchR * dst[7] * A) >> 16;
      dst[7] = (dst[7] * A) >> 8;

      dst[8] = (uchB * dst[11] * A) >> 16;
      dst[9] = (uchG * dst[11] * A) >> 16;
      dst[10] = (uchR * dst[11] * A) >> 16;
      dst[11] = (dst[11] * A) >> 8;

      dst[12] = (uchB * dst[15] * A) >> 16;
      dst[13] = (uchG * dst[15] * A) >> 16;
      dst[14] = (uchR * dst[15] * A) >> 16;
      dst[15] = (dst[15] * A) >> 8;

      dst[16] = (uchB * dst[19] * A) >> 16;
      dst[17] = (uchG * dst[19] * A) >> 16;
      dst[18] = (uchR * dst[19] * A) >> 16;
      dst[19] = (dst[19] * A) >> 8;

      dst[20] = (uchB * dst[23] * A) >> 16;
      dst[21] = (uchG * dst[23] * A) >> 16;
      dst[22] = (uchR * dst[23] * A) >> 16;
      dst[23] = (dst[23] * A) >> 8;

      dst[24] = (uchB * dst[27] * A) >> 16;
      dst[25] = (uchG * dst[27] * A) >> 16;
      dst[26] = (uchR * dst[27] * A) >> 16;
      dst[27] = (dst[27] * A) >> 8;

      dst[28] = (uchB * dst[31] * A) >> 16;
      dst[29] = (uchG * dst[31] * A) >> 16;
      dst[30] = (uchR * dst[31] * A) >> 16;
      dst[31] = (dst[31] * A) >> 8;

      dst[32] = (uchB * dst[35] * A) >> 16;
      dst[33] = (uchG * dst[35] * A) >> 16;
      dst[34] = (uchR * dst[35] * A) >> 16;
      dst[35] = (dst[35] * A) >> 8;

      dst[36] = (uchB * dst[39] * A) >> 16;
      dst[37] = (uchG * dst[39] * A) >> 16;
      dst[38] = (uchR * dst[39] * A) >> 16;
      dst[39] = (dst[39] * A) >> 8;

      dst[40] = (uchB * dst[43] * A) >> 16;
      dst[41] = (uchG * dst[43] * A) >> 16;
      dst[42] = (uchR * dst[43] * A) >> 16;
      dst[43] = (dst[43] * A) >> 8;

      dst[44] = (uchB * dst[47] * A) >> 16;
      dst[45] = (uchG * dst[47] * A) >> 16;
      dst[46] = (uchR * dst[47] * A) >> 16;
      dst[47] = (dst[47] * A) >> 8;

      dst[48] = (uchB * dst[51] * A) >> 16;
      dst[49] = (uchG * dst[51] * A) >> 16;
      dst[50] = (uchR * dst[51] * A) >> 16;
      dst[51] = (dst[51] * A) >> 8;

      dst[52] = (uchB * dst[55] * A) >> 16;
      dst[53] = (uchG * dst[55] * A) >> 16;
      dst[54] = (uchR * dst[55] * A) >> 16;
      dst[55] = (dst[55] * A) >> 8;

      dst[56] = (uchB * dst[59] * A) >> 16;
      dst[57] = (uchG * dst[59] * A) >> 16;
      dst[58] = (uchR * dst[59] * A) >> 16;
      dst[59] = (dst[59] * A) >> 8;

      dst[60] = (uchB * dst[63] * A) >> 16;
      dst[61] = (uchG * dst[63] * A) >> 16;
      dst[62] = (uchR * dst[63] * A) >> 16;
      dst[63] = (dst[63] * A) >> 8;

      dst += 4 * 16;
      size -= 16;
   }

   //return true;

}


void pixmap::set_rgb(::color::color color)
{

   return set_rgb(color.u8_red(), color.u8_green(), color.u8_blue());

}


//void pixmap::set_rgb(::i32 R, ::i32 G, ::i32 B)
//{
//
//   return set(R, G, B);
//
//}


::i64 pixmap::get_rgba_area(::color::color color) const
{

   ::i64 areaRgba = 0;

   image32_t u32ColorImage(color, color_indexes());

   const image32_t* p = this->data();

   areaRgba++;

   auto area = this->area();

   while (area > 0)
   {

      if (*p == u32ColorImage)
      {

         areaRgba++;

      }

      area--;

      p++;

   }

   return areaRgba;

}


::i64 pixmap::get_rgba_area(::color::color color, const ::i32_rectangle &rect) const
{

   ::i32_rectangle r(rect);

   if (r.intersect(this->rectangle()).is_empty())
   {

      return 0;

   }

   ::collection::count areaRgba = 0;

   image32_t u32ColorImage(color, color_indexes());

   ::i32 wscan = m_iScan / sizeof(image32_t);

   ::i32 w = r.width();

   ::i32 h = r.height();

   ::i32 scanadvance = wscan - w;

   const image32_t* p = this->data() + r.left + wscan * r.top;

   areaRgba++;

   while (h > 0)
   {

      for (::i32 x = 0; x < w; x++)
      {

         if (*p == u32ColorImage)
         {

            areaRgba++;

         }

         p++;

      }

      p += scanadvance;

      h--;


   }

   return areaRgba;

}


::i64 pixmap::_001GetTopLeftWeightedOpaqueArea(::i32 iAlphaMin) const
{

   auto r = this->rectangle();

   return _001GetTopLeftWeightedOpaqueArea(iAlphaMin, r);

}


::i64 pixmap::_001GetTopLeftWeightedOpaqueArea(::i32 iAlphaMin, const ::i32_rectangle &rect) const
{

   //map();

   if(::is_null(this->data()))
   {

      return 0;

   }

   ::i32_rectangle r(rect);

   ::i32_rectangle rTotal(this->rectangle());

   if (r.intersect(rTotal).is_empty())
   {

      return 0;

   }

   ::i64 areaRgba = 0;

   ::i32 wscan = m_iScan / sizeof(image32_t);

   ::i32 w = r.width();

   ::i32 h = r.height();

   ::i64 areaRgbaLast = 0;

   const image32_t* p = this->data() + r.left + wscan * r.top;

   areaRgba++;

   for (::i32 y = r.top; y < r.bottom; y++)
   {

      auto ysq = (rTotal.bottom - y);

      auto pbyte = &((::u8*)p)[m_colorindexes.m_u8IndexOpacity];

      for (::i32 x = r.left; x < r.right; x++)
      {

         if (*pbyte > iAlphaMin)
         {

            areaRgba += ((rTotal.right - x) + ysq);

         }

         pbyte += sizeof(image32_t);

      }

      p += wscan;

      h--;
      if (areaRgba < areaRgbaLast)
      {

         informationf("_001GetTopLeftWeightedOpaqueArea areaRgba < areaRgbaLast");

      }

      areaRgbaLast = areaRgba;

   }

   return areaRgba;

}


void pixmap::multiply_rgb_by_source_alpha(::color::color color)
{

   auto u8Red = color.u8_red();
   auto u8Green = color.u8_green();
   auto u8Blue = color.u8_blue();
   ::u8 u8Opacity;

   auto u8IndexOpacity = m_colorindexes.m_u8IndexOpacity;
   auto u8IndexRed = m_colorindexes.m_u8IndexRed;
   auto u8IndexGreen = m_colorindexes.m_u8IndexGreen;
   auto u8IndexBlue = m_colorindexes.m_u8IndexBlue;

   ::u8* puch = (::u8*)data();
   ::i64 iArea = scan_area();
   while (iArea > 0)
   {

      u8Opacity = puch[u8IndexOpacity];

      puch[u8IndexRed] = u8Red * u8Opacity / 255;
      puch[u8IndexGreen] = u8Green * u8Opacity / 255;
      puch[u8IndexBlue] = u8Blue * u8Opacity / 255;

      puch += 4;

      iArea--;

   }

   //return true;

}


void pixmap::rgb_from(::pixmap * ppixmap)
{

   //if (!
   create_as_descriptor(ppixmap->size());
   //{

   //   return false;

   //}

   //try
   //{

      ::u8* puchSrc = (::u8*)data();
      ::u8* puchDst = (::u8*)ppixmap->data();
      ::i64 iArea = ppixmap->scan_area();
      while (iArea > 0)
      {
         puchDst[0] = puchSrc[0];
         puchDst[1] = puchSrc[1];
         puchDst[2] = puchSrc[2];
         puchDst += 4;
         puchSrc += 4;
         iArea--;
      }

   //}
   //catch (...)
   //{

   //   return false;

   //}

   //return true;

}


void pixmap::pixelate(::i32 iSize)
{

   if (iSize <= 1)
   {

      //return true;

      return;

   }

   //map();

   ::i32 w = width();
   ::i32 h = height();
   ::i32 s = m_iScan / sizeof(image32_t);

   ::i32 xCount = w / iSize;
   ::i32 yCount = h / iSize;

   ::i32 iDiv;
   ::i32 iDiv2;

   ::i32 a;
   ::i32 r;
   ::i32 g;
   ::i32 b;
   ::i32 a2;
   ::i32 r2;
   ::i32 g2;
   ::i32 b2;
   //bool bFirst;
   image32_t* pdata = data();
   ::i32 x1;
   ::i32 y1;
   for (::i32 x = 0; x < xCount; x++)
   {
      x1 = x * iSize;
      for (::i32 y = 0; y < yCount; y++)
      {
         y1 = y * iSize;
         a = 0;
         r = 0;
         g = 0;
         b = 0;
         a2 = 0;
         r2 = 0;
         g2 = 0;
         b2 = 0;
         iDiv = 0;
         iDiv2 = 0;
         //bFirst = true;
         for (::i32 i = 0; i < iSize; i++)
         {
            for (::i32 j = 0; j < iSize; j++)
            {
               image32_t cr = pdata[x1 + i + (y1 + j) * s];
               a += cr.u8_opacity(color_indexes());
               r += cr.u8_red(color_indexes());
               g += cr.u8_green(color_indexes());
               b += cr.u8_blue(color_indexes());
               iDiv++;
               if (iDiv >= 64)
               {
                  a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                  r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                  g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                  b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                  a = 0;
                  r = 0;
                  g = 0;
                  b = 0;
                  iDiv = 0;
                  iDiv2++;
               }
            }
         }
         if (iDiv > 0)
         {
            a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
            r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
            g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
            b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
         }
         image32_t cr(argb(a2, r2, g2, b2), color_indexes());
         for (::i32 i = 0; i < iSize; i++)
         {
            for (::i32 j = 0; j < iSize; j++)
            {

               pdata[x1 + i + (y1 + j) * s] = cr;

            }

         }

      }

   }

   if (w % iSize != 0)
   {
      ::i32 x = xCount;
      ::i32 x1 = x * iSize;
      ::i32 iMax = w - xCount * iSize;
      for (::i32 y = 0; y < yCount; y++)
      {
         y1 = y * iSize;
         a = 0;
         r = 0;
         g = 0;
         b = 0;
         a2 = 0;
         r2 = 0;
         g2 = 0;
         b2 = 0;
         iDiv = 0;
         iDiv2 = 0;
         //bFirst = true;
         for (::i32 i = 0; i < iMax; i++)
         {
            for (::i32 j = 0; j < iSize; j++)
            {
               image32_t cr = pdata[x1 + i + (y1 + j) * w];
               a += cr.u8_opacity(color_indexes());
               r += cr.u8_red(color_indexes());
               g += cr.u8_green(color_indexes());
               b += cr.u8_blue(color_indexes());
               iDiv++;
               if (iDiv >= 64)
               {
                  a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                  r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                  g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                  b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                  a = 0;
                  r = 0;
                  g = 0;
                  b = 0;
                  iDiv = 0;
                  iDiv2++;
               }
            }
         }
         if (iDiv > 0)
         {
            a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
            r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
            g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
            b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
         }
         image32_t cr(argb(a2, r2, g2, b2), color_indexes());
         for (::i32 i = 0; i < iMax; i++)
         {
            for (::i32 j = 0; j < iSize; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

   }

   if (h % iSize != 0)
   {
      ::i32 y = yCount;
      ::i32 y1 = y * iSize;
      ::i32 jMax = h - yCount * iSize;
      for (::i32 x = 0; x < xCount; x++)
      {
         x1 = x * iSize;
         a = 0;
         r = 0;
         g = 0;
         b = 0;
         a2 = 0;
         r2 = 0;
         g2 = 0;
         b2 = 0;
         iDiv = 0;
         iDiv2 = 0;
         //bFirst = true;
         for (::i32 i = 0; i < iSize; i++)
         {
            for (::i32 j = 0; j < jMax; j++)
            {
               image32_t cr = pdata[x1 + i + (y1 + j) * w];
               a += cr.u8_opacity(color_indexes());
               r += cr.u8_red(color_indexes());
               g += cr.u8_green(color_indexes());
               b += cr.u8_blue(color_indexes());
               iDiv++;
               if (iDiv >= 64)
               {
                  a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                  r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                  g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                  b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                  a = 0;
                  r = 0;
                  g = 0;
                  b = 0;
                  iDiv = 0;
                  iDiv2++;
               }
            }
         }
         if (iDiv > 0)
         {
            a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
            r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
            g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
            b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
         }
         image32_t cr(argb(a2, r2, g2, b2), color_indexes());
         for (::i32 i = 0; i < iSize; i++)
         {
            for (::i32 j = 0; j < jMax; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

   }

   if (w % iSize != 0)
   {
      ::i32 x = xCount;
      ::i32 x1 = x * iSize;
      ::i32 iMax = w - xCount * iSize;
      ::i32 y = yCount;
      ::i32 y1 = y * iSize;
      ::i32 jMax = h - yCount * iSize;
      x1 = x * iSize;
      a = 0;
      r = 0;
      g = 0;
      b = 0;
      a2 = 0;
      r2 = 0;
      g2 = 0;
      b2 = 0;
      iDiv = 0;
      iDiv2 = 0;
      //bFirst = true;
      for (::i32 i = 0; i < iMax; i++)
      {
         for (::i32 j = 0; j < jMax; j++)
         {
            image32_t cr = pdata[x1 + i + (y1 + j) * w];
            a += cr.u8_opacity(color_indexes());
            r += cr.u8_red(color_indexes());
            g += cr.u8_green(color_indexes());
            b += cr.u8_blue(color_indexes());
            iDiv++;
            if (iDiv >= 64)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
               a = 0;
               r = 0;
               g = 0;
               b = 0;
               iDiv = 0;
               iDiv2++;
            }
         }
      }
      if (iDiv > 0)
      {

         a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
         r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
         g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
         b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);

      }

      image32_t cr(argb(a2, r2, g2, b2), color_indexes());

      for (::i32 i = 0; i < iMax; i++)
      {

         for (::i32 j = 0; j < jMax; j++)
         {

            pdata[x1 + i + (y1 + j) * w] = cr;

         }

      }

   }

   //return true;

}


   void pixmap::draw_error_line(::f64 x1, ::f64 h, ::f64 x2, ::i32 iStyle, const ::color::color & color)
   {

      ::i32 u8Red = color.u8_red();
      ::i32 u8Green = color.u8_green();
      ::i32 u8Blue = color.u8_blue();
      ::i32 u8Opacity = color.u8_opacity();

      if (iStyle == 0)
      {

         fill_solid_rectangle({x1, h, x2, h+ 1}, color);

      }
      else
      {

         //::image::image_pointer pimage;

         ::f64 w = x2 - x1 + 1;

         //auto estatus =

         //constructø(pimage);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus =

         create_as_descriptor({ (::i32)w, 6 });

         //if (!estatus || pimage->area() <= 0)
         if (area() <= 0)
         {

            throw ::exception(error_failed);

         }



         ::f64 dStep = 0.125;
         ::f64 dPeriod = 7.0;
         ::f64 dTint;
         ::f64 dHalfH = 1.33;
         ::f64 dHSpan = 0.7;
         ::f64 dH = 2.5;
         ::f64 dCurl = 2.3;
         ::f64 dBaseTint = 2.0;
         ::f64 dCircleX;
         ::f64 dCircleY;

         auto ppixmapImage = this->map();

         ppixmapImage->fill_byte(0);

         auto pimage32 = ppixmapImage->image32();

         auto scan = ppixmapImage->scan_size();

         auto wscan = scan / sizeof(::color32_t);

         for (::f64 Δx = 0; Δx < w; Δx += dStep)
         {
            dCircleX = fmod(Δx, (::f64)(dPeriod));
            ::f64 dSign = dCircleX < (dPeriod / 2.0) ? 1.0 : -1.0;
            dCircleX -= dPeriod / 2.0;
            dTint = dBaseTint * 0.51;
            dCircleY = dSign * sqrt(dPeriod * dPeriod / 4.0 - dCircleX * dCircleX) * 0.05;
            {
               ::f64 Δy = (sin((::f64)Δx * 2.0 * 3.1415 / dPeriod) - fmod(Δx, (::f64)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               ;
               Δy = (Δy * dHalfH + dH - dHSpan);
               ::i32 x = (::i32)round(Δx);
               ::i32 y = (::i32)round(Δy);
               if (x < 0 || y < 0 || x >= this->width() || y >= this->height())
               {
               }
               else
               {
                  ::i32 opacity = pimage32[x + wscan * y].u8_opacity(this->m_colorindexes);
                  ::f64 fy = 1.0 - fmod(fabs(Δy), 1.0);
                  ::f64 fx = 1.0 - fmod(fabs(Δx), 1.0);
                  opacity = (::i32)(opacity + ((fx * fy) * 255.0 * dStep * dTint));
                  opacity = minimum(opacity, 255);
                  pimage32[x + wscan * y].assign(argb((opacity * u8Opacity) / 255, u8Blue, u8Green, u8Red), this->color_indexes());
               }
            }
            dTint = dBaseTint * 0.51;
            {
               ::f64 Δy = (sin((::f64)Δx * 2.0 * 3.1415 / dPeriod) - fmod(Δx, (::f64)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               Δy = (Δy * dHalfH + dH + dHSpan);
               ::i32 x = (::i32)round(Δx);
               ::i32 y = (::i32)round(Δy);
               if (x < 0 || y < 0 || x >= this->width() || y >= this->height())
               {
               }
               else
               {
                  ::i32 opacity = pimage32[x + wscan * y].u8_opacity(this->color_indexes());
                  ::f64 fy = 1.0 - fmod(fabs(Δy), 1.0);
                  ::f64 fx = 1.0 - fmod(fabs(Δx), 1.0);
                  opacity = (::i32)(opacity + ((fx * fy) * 255.0 * dStep * dTint));
                  opacity = minimum(opacity, 255);
                  pimage32[x + wscan * y].assign(argb((opacity * u8Opacity) / 255, u8Blue, u8Green, u8Red), this->color_indexes());
               }

            }

            dTint = dBaseTint * 2.3;

            {
               ::f64 Δy = (sin((::f64)Δx * 2.0 * 3.1415 / dPeriod) - fmod(Δx, (::f64)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               Δy = (Δy * dHalfH + dH);
               ::i32 x = (::i32)round(Δx);
               ::i32 y = (::i32)round(Δy);
               if (x < 0 || y < 0 || x >= this->width() || y >= this->height())
               {
               }
               else
               {
                  ::i32 opacity = pimage32[x + wscan].u8_opacity(this->color_indexes());
                  ::f64 fy = 1.0 - fmod(fabs(Δy), 1.0);
                  ::f64 fx = 1.0 - fmod(fabs(Δx), 1.0);
                  opacity = (::i32)(opacity + ((fx * fy) * 255.0 * dStep * dTint));
                  opacity = minimum(opacity, 255);
                  pimage32[x + wscan * y].assign(argb((opacity * u8Opacity) / 255, u8Blue, u8Green, u8Red), this->color_indexes());

               }

            }

         }
         //
         // set_alpha_mode(::draw2d::e_alpha_mode_blend);
         //
         // auto rectangleTarget = ::f64_rectangle(::f64_point(x1, h), pimage->size());
         //
         // {
         //
         //    ::image::image_source imagesource(pimage);
         //
         //    ::f64_rectangle rectangle(rectangleTarget);
         //
         //    ::image::image_drawing_options imagedrawingoptions(rectangle);
         //
         //    ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
         //
         //    draw(imagedrawing);
         //
         // }

      }

      //return true;

   }


void pixmap::rate_rgb(::i32 iMul, ::i32 iDiv)
{

   //map();

   try
   {
      ::u8* puch = (::u8*)data();
      ::i64 iArea = scan_area();
      while (iArea > 0)
      {
         puch[0] = maximum(0, minimum(255, puch[0] * iMul / iDiv));
         puch[1] = maximum(0, minimum(255, puch[1] * iMul / iDiv));
         puch[2] = maximum(0, minimum(255, puch[2] * iMul / iDiv));
         puch += 4;
         iArea--;
      }
   }
   catch (...)
   {

   }

   //return true;

}


//void pixmap::_map(bool bApplyAlphaTransform)
//{
//
//
//   return *this;
//
//}
//
//
// void pixmap::_unmap(bool bDoUnmap)
// {
//
//    pixmap::_unmap();
//
//    if (bDoUnmap)
//    {
//
//       if (::is_set(m_pgraphicsOwned))
//       {
//
//          auto pgraphicsOwned = m_pgraphicsOwned;
//
//          ::i32_rectangle rectangleThis(m_size);
//
//          ::i32_rectangle rectangleMap(rectangle());
//
//          if (rectangleThis.contains(rectangleMap.origin()))
//          {
//
//             pgraphicsOwned->place_impact_area(rectangleMap);
//
//          }
//          else
//          {
//
//             pgraphicsOwned->place_impact_area(0, 0, m_sizeRaw.width(), m_sizeRaw.height());
//
//          }
//
//       }
//
//    }
//
//    //return true;
//
// }


// void pixmap::set_mapped()
// {
//
//    m_bMapped = false;
//
// //   return true;
//
// }

//
//   void pixmap::update_window(::aura::draw_interface * puserinteraction,::message::message * pmessage,bool bTransferBuffer)
//   {
//
//      __UNREFERENCED_PARAMETER(puserinteraction);
//      __UNREFERENCED_PARAMETER(pmessage);
//
//      // default implementation does nothing, image_impl should be now updated (before calling update interaction_impl)
//      // and ready to be queried if post queried
//
////      throw ::interface_only();
//
//
//      return true;
//
//   }


//void pixmap::print_window(::aura::draw_interface * puserinteraction,::message::message * pmessage)
//{

//   __UNREFERENCED_PARAMETER(puserinteraction);
//   __UNREFERENCED_PARAMETER(pmessage);

//   throw ::interface_only();

//   return false;

//}


void pixmap::gradient_fill(::color::color color1, ::color::color color2, const i32_point& point1, const i32_point& point2)
{

   ::f64 Δx = point2.x - point1.x;

   ::f64 Δy = point1.y - point2.y;

   if (Δx == 0.0 && Δy == 0.0)
   {

      clear_argb(
         byte_clip(color1.u8_opacity() * 0.5 + color2.u8_opacity() * 0.5),
         byte_clip(color1.u8_red() * 0.5 + color2.u8_red() * 0.5),
         byte_clip(color1.u8_green() * 0.5 + color2.u8_green() * 0.5),
         byte_clip(color1.u8_blue() * 0.5 + color2.u8_blue() * 0.5));

   }
   else if (Δx == 0.0)
   {

      gradient_horizontal_fill(color1, color2, point1.y, point2.y);

   }
   else if (Δy == 0.0)
   {

      gradient_vertical_fill(color1, color2, point1.x, point2.x);

   }
   else
   {

      //         ::i32 x1 = minimum(point1.x, point2.x);

      //       ::i32 x2 = maximum(point1.x, point2.x);

      //     ::i32 y1 = minimum(point1.y, point2.y);

      //   ::i32 y2 = maximum(point1.y, point2.y);

      //         ::i32 top = y1;
      //
      //       ::i32 left = x1;
      //
      //       ::i32 right = width() - x2;
      //
      //  ::i32 bottom = height() - y2;

      ::i32 dim = maximum(width(), height());

      auto angle = ::geometry::atan2(Δy, Δx);

      ::pixmap_pointer ppixmap;

      auto pmathematics = mathematics();

      if (fabs(Δx) > fabs(Δy))
      {

         ::f64 sin = ::sin(angle);

         //auto estatus =
         
         constructø(ppixmap);

         //if (!estatus)
         //{

         //   return false;

         //}

         //estatus = 
         
         ppixmap->create_as_descriptor({(::i32)(dim / sin), (::i32)(dim / sin)});

         //if (!estatus)
         //{

         //   return false;

         //}

         ppixmap->gradient_horizontal_fill(color1, color2, point1.y, point2.y);

         ppixmap->rotate(this, -angle, 1.0);

      }
      else
      {

         ::f64 cos = ::cos(angle);

         //auto estatus =
         
         constructø(ppixmap);

         //if (!estatus)
         //{

         //   return false;

         //}

         //estatus = 
         ppixmap->create_as_descriptor({(::i32)(dim / cos), (::i32)(dim / cos)});

         //if (!estatus)
         //{

         //   return false;

         //}

         ppixmap->gradient_vertical_fill(color1, color2, point1.x, point2.x);

         ppixmap->rotate(this, π - angle, 1.0);

      }

   }

   //return true;

}


void pixmap::gradient_horizontal_fill(::color::color color1, ::color::color color2, ::i32 start, ::i32 end)
{

   if (end < start)
   {
      ::__swap(start, end);
      ::__swap(color1, color2);
   }

   end = minimum(end, height() - 1);
   image32_t clr(color1, color_indexes());
   ::u8* pb = (::u8*)image32();
   image32_t* pdata;
   ::i32 line = 0;
   for (; line < start; line++)
   {
      pdata = (image32_t*)&pb[m_iScan * line];
      for (::i32 row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }
   ::f64 d;
   for (; line < end; line++)
   {

      d = ((::f64)(line - start)) / ((::f64)(end - start));

      clr.assign(argb(
         byte_clip(color1.u8_opacity() * (1.0 - d) + color2.u8_opacity() * d),
         byte_clip(color1.u8_red() * (1.0 - d) + color2.u8_red() * d),
         byte_clip(color1.u8_green() * (1.0 - d) + color2.u8_green() * d),
         byte_clip(color1.u8_blue() * (1.0 - d) + color2.u8_blue() * d)), color_indexes());

      pdata = (image32_t*)&pb[m_iScan * line];
      for (::i32 row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }
   clr.assign(color2, color_indexes());
   for (; line < height(); line++)
   {
      pdata = (image32_t*)&pb[m_iScan * line];
      for (::i32 row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }

   //return true;

}


void pixmap::gradient_vertical_fill(::color::color color1, ::color::color color2, ::i32 start, ::i32 end)
{

   if (end < start)
   {
      ::__swap(start, end);
      ::__swap(color1, color2);
   }

   end = minimum(end, width() - 1);

   image32_t clr(color1, color_indexes());
   
   ::u8* pb = (::u8*)image32();
   
   image32_t* pdata;
   
   ::i32 row = 0;

   for (; row < start; row++)
   {
      pdata = (image32_t*)&pb[sizeof(image32_t) * row];
      for (::i32 line = 0; line < height(); line++)
      {
         *pdata = clr;
         pdata += m_iScan;
      }
   }
   
   ::f64 d;

   for (; row < end; row++)
   {

      d = ((::f64)(row - start)) / ((::f64)(end - start));

      clr.assign(argb(
         byte_clip(color1.u8_opacity() * (1.0 - d) + color2.u8_opacity() * d),
         byte_clip(color1.u8_red() * (1.0 - d) + color2.u8_red() * d),
         byte_clip(color1.u8_green() * (1.0 - d) + color2.u8_green() * d),
         byte_clip(color1.u8_blue() * (1.0 - d) + color2.u8_blue() * d)), 
         color_indexes());

      pdata = (image32_t*)&pb[sizeof(image32_t) * row];

      for (::i32 line = 0; line < width(); line++)
      {

         *pdata = clr;

         pdata += m_iScan;

      }

   }
   
   clr.assign(color2, color_indexes());

   for (; row < width(); row++)
   {
      
      pdata = (image32_t*)&pb[sizeof(image32_t) * row];

      for (::i32 line = 0; line < width(); line++)
      {
         
         *pdata = clr;

         pdata += m_iScan;

      }

   }

  // return true;
//
}


void pixmap::gradient_horizontal_fill(::color::color color1, ::color::color color2)
{

   gradient_horizontal_fill(color1, color2, 0, height() - 1);

   //return true;

}


void pixmap::gradient_vertical_fill(::color::color color1, ::color::color color2)
{

   gradient_vertical_fill(color1, color2, 0, width() - 1);

   //return true;

}


void pixmap::invert_rgb()
{

   return invert_rgb(rectangle());

}


void pixmap::invert_rgb(const ::i32_rectangle& rectangle)

{

   ::i32 s = m_iScan;

   ::i32 left;
   ::i32 right;
   ::i32 top;
   ::i32 bottom;

   left = minimum(maximum(0, rectangle.left), width());


   right = minimum(maximum(0, rectangle.right), width());


   top = minimum(maximum(0, rectangle.top), height());


   bottom = minimum(maximum(0, rectangle.bottom), height());

   ::i32 start = left * 4 + top * s;

   for (::i32 y = top; y < bottom; y++, start += s)
   {

      ::u8* pb = &((::u8*)image32())[start];

      for (::i32 x = left; x < right; x++, pb += 4)
      {

         pb[0] = ~pb[0];
         pb[1] = ~pb[1];
         pb[2] = ~pb[2];

      }

   }

   //return true;

}


void pixmap::create_circle2(::pixmap * ppixmap, ::i32 diameter)
{

   create_as_descriptor({diameter, diameter});

   if (::is_null(ppixmap) || ppixmap->area() <= 0)
   {

      clear_argb(255, 0, 0, 0);

   }
   else
   {
   //
   //    auto pgraphics = acquire_graphics();
   //
   //    pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //
   //    ::pixmap::image_source imagesource(ppixmap, ::i32_rectangle_dimension(0, 0, ppixmap->width(), ppixmap->height()));
   //
   //    auto rectangle = f64_rectangle_dimension(0, 0, diameter, diameter);
   //
   //    ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
   //
   //    ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   //    pgraphics->draw(imagedrawing);
   //

      throw todo;
   }



//   clip_circle(1.0);

}


void pixmap::clip_circle(::f64 dWidth)
{

   ::i32_size s = size();

   auto diameter = minimum(s.cx, s.cy);

   image32_t* ppixmap32 = image32();

   ::i32 iScan = m_iScan;

   ::i32 wscan = iScan / sizeof(image32_t);

   ::f64 radius = diameter / 2.0;

   ::f64 dBorder = dWidth;

   ::f64 rmin = radius - dBorder;

   ::f64 rmax = radius;

   ::i32 crA;

   image32_t* ppixmap322;

   for (::i32 y = 0; y < s.cx; y++)
   {

      ppixmap322 = &ppixmap32[y * wscan];

      for (::i32 x = 0; x < s.cx; x++)
      {

         ::f64 Δx = x;

         ::f64 Δy = y;

         ::f64 distance = sqrt((Δx - radius) * (Δx - radius) + (Δy - radius) * (Δy - radius));

         crA = (::i32)((rmin - distance) * 255.0 / dBorder);

         crA = maximum(minimum(crA, 255), 0);

         ppixmap322->m_ua[0] = ((::i32)ppixmap322->m_ua[0] * crA) / 255;
         ppixmap322->m_ua[1] = ((::i32)ppixmap322->m_ua[1] * crA) / 255;
         ppixmap322->m_ua[2] = ((::i32)ppixmap322->m_ua[2] * crA) / 255;
         ppixmap322->m_ua[3] = ((::i32)ppixmap322->m_ua[3] * crA) / 255;

         ppixmap322++;

      }

   }

   //return true;

}


void pixmap::create_framed_square(::pixmap * ppixmap, ::i32 inner, ::i32 outer, ::color::color color)
{

   create_as_descriptor({inner + outer * 2, inner + outer * 2});

   //if (!create({ inner + outer * 2, inner + outer * 2 }))
   //{

   //   return false;

   //}

   clear(color);


   throw todo;
   // ::pixmap::image_source imagesource(ppixmap, ::i32_rectangle_dimension(0, 0, ppixmap->width(), ppixmap->height()));
   //
   // auto rectangle = f64_rectangle_dimension(outer, outer, inner, inner);
   //
   // ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
   //
   // ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   // auto pgraphics = acquire_graphics();
   //
   // pgraphics->draw(imagedrawing);

   //return true;

}


void image_copy(::pixmap * ppixmapthis, ::pixmap * ppixmap)
{

   ppixmapthis->copy_from(ppixmap);

}


//void image_create(::object* pparticle, ::pixmap_pointer& ppixmap)
//{
//
//   constructø(ppixmap, pparticle);
//
//}

//
//void image_create_image(::pixmap * ppixmap, const ::i32_size& size)
//{
//
//   ppixmap->create_as_descriptor(size);
//
//}


::u32* image_get_data(::pixmap * ppixmap)
{

   return (::u32*)ppixmap->image32();

}


//::draw2d::graphics* image_get_graphics(::pixmap * ppixmap)
//{
//
//   if (::is_null(ppixmap))
//   {
//
//      return nullptr;
//
//   }
//
//   return pgraphicsImage;
//
//}


void pixmap::hue_offset(::f64 dRadians)
{

   if (dRadians >= 0.0)
   {

      dRadians = fmod(dRadians, 3.1415 * 2.0);

   }
   else
   {

      dRadians = (3.1415 * 2.0) - fmod(-dRadians, 3.1415 * 2.0);

   }

   //http://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color
   //http://stackoverflow.com/users/630989/jacob-eggers
   ::f64 U = ::cos(dRadians);
   ::f64 W = ::sin(dRadians);


   ::u8* dst = (::u8*)data();

   ::i64 size = scan_area();


   while (size--)
   {
      ::f64 oldr = dst[0];
      ::f64 oldg = dst[1];
      ::f64 oldb = dst[2];
      dst[0] = clampAndConvert((.299 + .701 * U + .168 * W) * oldr
         + (.587 - .587 * U + .330 * W) * oldg
         + (.114 - .114 * U - .497 * W) * oldb);
      dst[1] = clampAndConvert((.299 - .299 * U - .328 * W) * oldr
         + (.587 + .413 * U + .035 * W) * oldg
         + (.114 - .114 * U + .292 * W) * oldb);
      dst[2] = clampAndConvert((.299 - .3 * U + 1.25 * W) * oldr
         + (.587 - .588 * U - 1.05 * W) * oldg
         + (.114 + .886 * U - .203 * W) * oldb);
      dst += 4;
   }

   //return true;

}

//
//
// void pixmap::fast_copy(image32_t* pcolor32)
// {
//
//    data()->copy(rectangle(), scan_size(), pcolor32);
//
// }

void pixmap::on_load_image()
{

   if (m_iExifOrientation != 0)
   {

      on_exif_orientation();

   }

   //return true;

}


void pixmap::on_exif_orientation()
{

   enum_rotate_flip erotateflip = ::exif_orientation_rotate_flip(m_iExifOrientation);

   if (erotateflip == e_rotate_90_flip_none)
   {

      rotate(90_degree);

   }
   else if (erotateflip == e_rotate_180_flip_none)
   {

      rotate(180_degree);

   }
   else if (erotateflip == e_rotate_270_flip_none)
   {

      rotate(270_degree);

   }
   else if (erotateflip == e_rotate_none_flip_x)
   {

      flip_horizontally();

   }
   else if (erotateflip == e_rotate_90_flip_x)
   {

      e_rotate_90_flip_horizontally();

   }
   else if (erotateflip == e_rotate_180_flip_x)
   {

      e_rotate_180_flip_horizontally();

   }
   else if (erotateflip == e_rotate_270_flip_x)
   {

      e_rotate_270_flip_horizontally();

   }

}
//
//
////save_image::save_image(::matter * pmatter)
//save_image::save_image()
//{
//
//   m_eformat = ::draw2d::e_format_png;
//
//   m_iQuality = 100;
//
//   m_iDpi = 96;
//
//}
//

//save_image::save_image(::matter * pmatter, const ::payload & payloadFile, const ::payload & varOptions)
//{
//
//   ::pointer<::aura::system>psystem = system();
//
//   auto eformat = pdraw2d->text_to_format(varOptions["format"]);
//
//   if (eformat != ::draw2d::e_format_none)
//   {
//
//      ::pointer<::aura::system>psystem = system();
//
//      eformat = pdraw2d->file_extension_to_format(payloadFile.get_file_path());
//
//   }
//
//   if (eformat == ::draw2d::e_format_none)
//   {
//
//      m_eformat = ::draw2d::e_format_png;
//
//   }
//
//   if (varOptions["quality"].get_type() == e_type_f64
//      || varOptions["quality"].get_type() == e_type_f32)
//   {
//
//      m_iQuality = (::i32) (varOptions["quality"].get_f64() * 100.0);
//
//   }
//   else
//   {
//
//      m_iQuality = varOptions["quality"].as_i32();
//
//   }
//
//   if (m_iQuality == 0)
//   {
//
//      m_iQuality = 100;
//
//   }
//
//   m_iDpi = varOptions["dpi"];
//
//   if (m_iDpi == 0)
//   {
//
//      m_iDpi = 96;
//
//   }
//
//
//}
//

//void pixmap::load_matter_icon(string_array_base & straMatter, const ::scoped_string & scopedstrIcon)
//{
//
//   ::file::path path;
//
//   for (auto & strMatter : straMatter)
//   {
//
//      path = strMatter;
//
//      path = directory()->matter(path / strIcon);
//
//      if (load_image(path))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//#ifndef  WINDOWS
//
//   void pixmap::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
//   {
//
//      return psystem->imaging().from(m_p, pgraphics, pfi, bUnload);
//
//   }
//
//#endif

/*::i32_size pixmap::size()
{

   if (m_parray.is_set() && m_parray->get_count() > 0 && m_parray->m_dwTotal > 0)
   {

      return m_parray->size();

   }

   return m_p->size();

}*/
//    void pixmap::create_as_descriptor(const ::i32_size &size, ::enum_flag eflagCreate,
//                        ::i32 iGoodStride)
// {
//
//    m_size = size;
//
//    m_eflagElement = eflagCreate;
//
//    m_iScan = iGoodStride;
//
// }

//
// void pixmap::create_bitmap(
//    ::acme::user::interaction * pacmeuserinteractionAffinity, ::draw2d::graphics * pgraphics)
// {
//
//    if (m_pbitmap.ok())
//    {
//
//       return;
//
//    }
//
//    constructø(m_pbitmap);
//
//    if (!pacmeuserinteractionAffinity)
//    {
//
//       pacmeuserinteractionAffinity = m_pacmeuserinteractionAffinity;
//
//    }
//
//    m_pbitmap->create_bitmap_for_image(
//       this,
//       pacmeuserinteractionAffinity,
//       pgraphics);
//
// }
//
//
// ::pixmap::image * pixmap::get_source_image()
// {
//
//    auto pframes = frames();
//
//    if (!pframes)
//    {
//
//       return this;
//
//    }
//
//    auto ppixmap = pframes->calc_current_frame(m_dynamic);
//
//    if (!ppixmap)
//    {
//
//       return this;
//
//    }
//
//    return ppixmap;
//
//    //if (ppixmap
//    //   //&& m_pgraphics != ppixmap->m_pgraphics
//    //   && m_pbitmap != ppixmap->m_pbitmap)
//    //{
//
//    //   _unmap();
//
//    //   ppixmap->_unmap();
//
//    //   ::pixmap * ppixmapDst = this;
//
//    //   ::pixmap * ppixmapSrc = ppixmap;
//
//    //   //m_pgraphics = ppixmap->m_pgraphics;
//
//    //   m_pbitmap = ppixmap->m_pbitmap;
//
//    //   ::memory_copy(ppixmapDst, ppixmapSrc, sizeof(::pixmap));
//
//    //}
//
// }


//void pixmap::defer_create_owned_graphics_lease()
//{
//
//   if (!m_pgraphicsleaseOwned)
//   {
//
//      m_pgraphicsleaseOwned = new ::draw2d::graphics_lease(acquire_graphics());
//
//   }
//
//}


//void pixmap::defer_destroy_owned_graphics_lease()
//{
//
//   if (m_pgraphicsleaseOwned)
//   {
//      
//      auto pgraphicsleaseOwned = m_pgraphicsleaseOwned;
//
//      m_pgraphicsleaseOwned = nullptr;
//
//      try
//      {
//
//         delete pgraphicsleaseOwned;
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//   }
//
//}


//void pixmap::set_owned_graphics()
//{
//
//   if (m_pgraphicsOwned)
//   {
//
//      return;
//
//   }
//
//   constructø(m_pgraphicsOwned);
//
//   m_pgraphicsOwned->create_memory_graphics()
//
//}
//
//
// ::pointer<::pixmap::image>pixmap::get_image(const ::i32_size & size)
// {
//
//    if (size == get_size())
//    {
//
//       return this;
//
//    }
//
//    auto ppixmapNew = ::system()->create_pixmap(size);
//
//    ::pixmap::image_source imagesource(this, this->rectangle());
//
//    auto rectangle = ppixmapNew->rectangle();
//
//    ::pixmap::image_drawing_options imagedrawingoptions(rectangle);
//
//    ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//    auto pgraphicsImageNew = ppixmapNew->acquire_graphics();
//
//    pgraphicsImageNew->draw(imagedrawing);
//
//    return ppixmapNew;
//
// }
//
//
// ::pointer<::pixmap::image>pixmap::get_image(::i32 cx, ::i32 cy)
// {
//
//    auto ppixmapNew = get_image( ::i32_size( cx, cy ));
//
//    return ppixmapNew;
//
// }
//

#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::pixmap::image* m_p, ::i32 Δx, ::i32 Δy, void* pftbitmap, ::i32 xParam, ::i32 yParam)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, i32_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         ::i32 a = bitmap->buffer[q * bitmap->width + i32_point];

         *((image32_t*)&((::u8*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::pixmap::image* m_p, ::i32 Δx, ::i32 Δy, void* pftbitmap, ::i32 xParam, ::i32 yParam, ::u8 aParam, ::u8 rectangle, ::u8 g, ::u8 b)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, i32_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         ::i32 a = bitmap->buffer[q * bitmap->width + i32_point];

         if (a > 0)
         {

            *((image32_t*)&((::u8*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((image32_t*)&((::u8*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = 0;

         }

      }
   }

}

#endif









#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::pixmap::image* m_p, ::i32 Δx, ::i32 Δy, void* pftbitmap, ::i32 xParam, ::i32 yParam)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, i32_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         ::i32 a = bitmap->buffer[q * bitmap->width + i32_point];

         *((image32_t*)&((::u8*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::pixmap::image* m_p, ::i32 Δx, ::i32 Δy, void* pftbitmap, ::i32 xParam, ::i32 yParam, ::u8 aParam, ::u8 rectangle, ::u8 g, ::u8 b)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, i32_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         ::i32 a = bitmap->buffer[q * bitmap->width + i32_point];

         if (a > 0)
         {

            *((image32_t*)&((::u8*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((image32_t*)&((::u8*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = 0;

         }

      }
   }

}


#endif



//stream& pixmap::write(::stream& stream) const
//{
//
//   //throw ::exception(todo("write_link"));
//   //if(stream.write_link(this))
//   //{
//
//   //   return stream;
//
//   //}
//
//   ::i32 iWidth = width();
//
//   stream << (::i32)iWidth;
//
//   ::i32 iHeight = height();
//
//   stream << (::i32)iHeight;
//
//   stream << (::i32)m_sizeAlloc.cx;
//
//   stream << (::i32)m_sizeAlloc.cy;
//
//   stream << (::i32)m_iScan;
//
//   stream << (::i32)m_emipmap;
//
//   if (area() > 0)
//   {
//
//      map();
//
//      stream.write(image32(), m_iScan * height());
//
//   }
//
//   return stream;
//
//}
//
//
//
//stream& pixmap::read(::stream& stream)
//{
//
//   //throw ::exception(todo("write_link"));
//   //string strLink;
//
//   //bool bReadOnly;
//
//   //if (stream.get_object_link(*this, strLink, bReadOnly))
//   //{
//
//   //   stream.read_link(*this);
//
//   //   return stream;
//
//   //}
//
//   ::i32 width;
//
//   stream >> width;
//
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   ::i32 height;
//
//   stream >> height;
//
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   ::i32 widthAlloc;
//   stream >> widthAlloc;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   ::i32 heightAlloc;
//   stream >> heightAlloc;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   ::i32 iScan;
//   stream >> iScan;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   ::i32 iMipmap;
//   stream >> iMipmap;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   if (width <= 0)
//   {
//      //stream.setstate(::file::badbit);
//
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (height <= 0)
//   {
//
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (widthAlloc <= 0)
//   {
//      
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (heightAlloc <= 0)
//   {
//     
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (iScan <= 0)
//   {
//      
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (widthAlloc < width)
//   {
//      
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (heightAlloc < height)
//   {
//     
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   if (iScan < widthAlloc / (::i32)sizeof(image32_t))
//   {
//      
//      throw ::exception(::error_io);
//
//      return stream;
//
//   }
//
//   create({ widthAlloc, heightAlloc });
//
//   //if (!create({ widthAlloc, heightAlloc }))
//   //{
//
//   //   throw ::exception(::error_io);
//
//   //   return stream;
//
//   //}
//
//   map();
//
//   if (iScan == m_iScan)
//   {
//
//      stream.exchange("bitmap", data(), iScan * this->height());
//
//   }
//   else
//   {
//
//      memory mem;
//
//      mem.set_size(iScan * this->height());
//
//      stream.exchange("bitmap", mem.data(), iScan * this->height());
//
//      auto size = stream.m_gcount;
//
//      if (size / iScan < height)
//      {
//
//         // stream.setstate(::file::badbit);
//
//         throw ::exception(error_io);
//
//         return stream;
//
//      }
//
//      ::copy_image32(data(), width, height, m_iScan, (image32_t*)mem.data(), iScan);
//
//   }
//
//   m_size.cx = width;
//
//   m_size.cy = height;
//
//   return stream;
//
//}


::subparticle_pointer pixmap::clone()
{

   auto ppixmap = this->createø<::pixmap>();

   ppixmap->copy_from((::pixmap *) this);

   __refdbg_add_referer

   ppixmap->increment_reference_count();

   return ppixmap;

}


//::draw2d::graphics *pixmap::owned_graphics() const 
//{
//   
//   return ((image *)this)->owned_graphics(); 
//
//}


// ::draw2d::graphics_lease pixmap::acquire_graphics(const ::f64_size &sizeHint)
// {
//
//    return ::transfer(acquire_graphics());
//
// }


//void pixmap::create_image()
//{
//
//   if(::is_null(this))
//   {
//
//      return ::error_failed;
//
//   }
//
//   return ::error_failed;
//
//}


//void     pixmap::create(::i32 cx, ::i32 cy, ::eobject eobjectCreate, ::i32 iGoodStride, bool bPreserve)
//{
//
//   if(!create(cx, cy, uidCreateImage, iGoodStride, bPreserve))
//   {
//
//      return ::error_failed;
//
//   }
//
//   return ::success;
//
//}


//void     pixmap::create(const ::i32_size & size, ::eobject eobjectCreate, ::i32 iGoodStride, bool bPreserve)
//{
//
//   if(!create(size, uidCreateImage))
//   {
//
//      return ::error_failed;
//
//   }
//
//   return ::success;
//
//}




/*
http://www.sparkhound.com/blog/detect-image-file-types-through-::u8-arrays
::payload bmp = Encoding.ASCII.GetBytes("BM"); // BMP
::payload gif = Encoding.ASCII.GetBytes("GIF"); // GIF
::payload png = øallocate_array< ::u8 >(){ 137, 80, 78, 71 }; // PNG
::payload tiff = øallocate_array< ::u8 >(){ 73, 73, 42 }; // TIFF
::payload tiff2 = øallocate_array< ::u8 >(){ 77, 80, 42 }; // TIFF
::payload jpeg = øallocate_array< ::u8 >(){ 255, 216, 255, 224 }; // jpeg
::payload jpeg2 = øallocate_array< ::u8 >(){ 255, 216, 255, 225 }; // jpeg canon
*/


//virtual ::pixmap_pointer ::create_image(::draw2d::e_load eload = ::draw2d::load_none);
//virtual ::pixmap_pointer create_image({::i32 cx,  ::i32 cy});
//virtual ::pixmap_pointer create_image(const ::i32_size & size);




void pixmap::transform(enum_image eimage)
{

   if (eimage == e_image_grayscale)
   {

      return saturation(0.0);

   }

   //return ::error_not_found;

   throw ::exception(error_not_found);

}


//::draw2d::graphics* pixmap::_get_graphics() const
//{
//
//   return nullptr;
//
//}
//
//

//
// void pixmap::_map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform)
// {
//
//    if (has_active_destination_graphics_lease())
//    {
//
//       throw ::exception(error_wrong_state, "cannot map an image with active destination graphics");
//
//    }
//
//    pixmap::_map(rectangle, bApplyAlphaTransform);
//
// }
//
//
// //void pixmap::_unmap()
//{
//
//   //return true;
//
//}


//void pixmap::static_initialize()
//{
//
//   ::f64 dCos;
//   ::f64 dSin;
//   ::f64 d32 = (1U << 31);
//   dPi = atan(1.0) * 4.0;
//   ::i32 i;
//   for (i = 0; i < 360; i++)
//   {
//      dCos = ::cos(i / 180.0 * dPi);
//      dSin = ::sin(i / 180.0 * dPi);
//      Cosines[i] = ::f32(dCos);
//      Sines[i] = ::f32(dSin);
//      CosN[i] = (::i64)(dCos * d32);
//      SinN[i] = (::i64)(dSin * d32);
//   }
//   d32 = (1U << 31);
//   d32 *= 8;
//   for (i = 0; i < 10; i++)
//   {
//      dCos = ::cos(i / 180.0 * dPi);
//      dSin = ::sin(i / 180.0 * dPi);
//      Cos10N[i] = (::i64)(dCos * d32);
//      Sin10N[i] = (::i64)(dSin * d32);
//   }
//
//}
//

//
// ::pixmap::image_extension* pixmap::get_extension()
// {
//
//    if (::is_null(m_pextension))
//    {
//
//       construct_newø(m_pextension);
//
//    }
//
//    return m_pextension;
//
// }
//
//
// bool pixmap::_draw_blend(const ::pixmap::image_drawing& imagedrawing)
// {
//
//    auto pgraphics = acquire_graphics();
//
//    //if (::is_null(pgraphics))
//    //{
//
//    //   return false;
//
//    //}
//
//    return pgraphics->_draw_blend(imagedrawing);
//    //{
//
//    //   return false;
//
//    //}
//
//    //return true;
//
// }
//

//const ::image32_t *pixmap::get_data() const 
//{
//   
//   return ((image *)this)->get_data(); 
//
//}
//
//
//::image32_t *pixmap::get_data()
//{
//
//   if (m_bMapped)
//   {
//
//      return m_pimage32;
//
//   }
//
//   map();
//
//   return image32();
//
//}
//
//
// void pixmap::draw(const ::pixmap::image_drawing & imagedrawing)
// {
//
//    if (imagedrawing.m_bDoForAllFrames)
//    {
//
//       auto ppixmap = imagedrawing.image();
//
//       auto pframes = ppixmap->frames();
//
//       if (pframes && pframes->has_elements())
//       {
//
//          auto pextension = get_extension();
//
//          construct_newø(pextension->m_pframea);
//
//          pextension->m_pframea->m_size = this->m_size;
//
//          pextension->m_pframea->update(this, imagedrawing);
//
//          return;
//
//       }
//
//    }
//
//    image_drawer::draw(imagedrawing);
//    //void defer_update_image();
//
// }
//
//
// void pixmap::_draw_raw(const ::pixmap::image_drawing& imagedrawing)
// {
//
//    auto pgraphics = acquire_graphics();
//
//    //if (::is_null(pgraphics))
//    //{
//
//    //   return false;
//
//    //}
//
//    //if (!
//    pgraphics->_draw_raw(imagedrawing); //;
//   /* {
//
//       return false;
//
//    }
//
//    return true;*/
//
// }

//
// ::pixmap_pointer pixmap::get_resized_image(const ::i32_size & size)
// {
//
//    ::pixmap_pointer ppixmap;
//
//    m_papplication->constructø(ppixmap);
//
//    ppixmap->create_as_descriptor(size);
//
//    ::f64_rectangle rectangleTarget(::f64_point(0, 0), ::f64_size(size));
//
//    ::pixmap::image_source imagesource(this);
//
//    ::pixmap::image_drawing_options imagedrawingoptions(rectangleTarget);
//
//    ::pixmap::image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//    ppixmap->_draw_raw(imagedrawing);
//
//    return ppixmap;
//
// }

//
// ::pixmap_lease pixmap::map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform)
// {
//
//    auto ppixmap = ::transfer(_map(rectangle, bApplyAlphaTransform));
//
//    return ::transfer(ppixmap);
//
// }

//
//::image32_t * pixmap::line_data(::i32 iLine)
//{
//
//   return (::image32_t *) (((::u8*)data()) + (iLine * m_iScan));
//
//}


//} // namespace image



