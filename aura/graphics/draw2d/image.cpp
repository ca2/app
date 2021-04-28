//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "aura/operating_system.h"

double get_default_screen_dpi()
{

   // just a guess lol :D
   return 96.0;

}

#ifdef WINDOWS
#include <wincodec.h>
#include <ShCore.h>
//#elif defined(_UWP)
//#include <ShCore.h>
#endif



#include "aura/graphics/graphics/double_pass_scale.h"


template < typename TYPE >
void sort_image_argb(TYPE & A, TYPE & R, TYPE & G, TYPE & B)
{

#if defined(WINDOWS) || defined(LINUX)

   ::__swap(&R, &B);

#endif

}


template < typename TYPE >
void sort_image_rgb(TYPE & R, TYPE & G, TYPE & B)
{

#if defined(WINDOWS) || defined(LINUX)

   ::__swap(R, B);

#endif

}


/*
byte byte_clip(double d);


inline byte byte_clip(double d)
{
   if(d >= 255.0)
      return 255;
   if(d <= 0.0)
      return 0;
   return (byte) d;
}

inline byte byte_clip(int i)
{
   return minimum(255, maximum(0, i));
}
*/


image::image()
{

}


image::~image()
{

}


//void image::delete_this()
//{
//
//   ::object::delete_this();
//
//}


//void image::common_construct()
//{
//
//
//}


::size_i32 image::get_image_drawer_size() const
{

   return get_size();

}


::draw2d::graphics * image::get_graphics() const
{

   unmap();

   return _get_graphics();

}


::draw2d::bitmap_pointer image::get_bitmap() const
{

   ::exception::throw_interface_only();

   return nullptr;

}



::draw2d::bitmap_pointer image::detach_bitmap()
{

   ::exception::throw_interface_only();

   return nullptr;

}





bool image::realize(::draw2d::graphics * pgraphics) const
{

   UNREFERENCED_PARAMETER(pgraphics);

   return true;

}


bool image::unrealize() const
{

   return true;

}


bool image::is_realized() const
{

   return true;

}


bool image::defer_realize(::draw2d::graphics * pgraphics) const
{

   if (is_realized())
      return true;

   return realize(pgraphics);

}


::e_status image::create(const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
{

   return ::error_interface_only;

}


//::e_status     image::create(i32 width, i32 height, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//{
//
//   return create(::size_i32(width, height), uidCreateImage);
//
//}


bool image::host(const ::pixmap* ppixmap)
{
   // callers should be able to deal with graphics backend that doesn't support "hosting" portions of RAM
   return false;

}


bool image::on_host_read_pixels(const ::pixmap* ppixmap)
{

   return false;

}


bool image::dc_select(bool bSelect)
{

   UNREFERENCED_PARAMETER(bSelect);

   ::exception::throw_interface_only();

   return false;

}


::e_status image::create(::draw2d::graphics * pgraphics)
{

   ::draw2d::bitmap & bitmap = *pgraphics->get_current_bitmap();

   if (::is_null(bitmap))
   {

      return ::error_failed;

   }

   ::exception::throw_not_implemented();

   return ::error_failed;

}

::count image::get_image_count() const
{

   ::count c1 = is_set() ? 1 : 0;

   ::count c2 = 0;

   if (m_pextension && m_pextension->m_pframea)
   {

      c2 = m_pextension->m_pframea->count();

   }

   return maximum(c1, c2);

}


::image_pointer image::get_image(index i)
{

   if (m_pextension && m_pextension->m_pframea && m_pextension->m_pframea->has_element())
   {

      return m_pextension->m_pframea->element_at(i);

   }

   return this;

}


bool image::create_isotropic(::image * pimage)
{

   int cx = (int) (pimage->m_dIsotropicRate * width());

   int cy = (int) (pimage->m_dIsotropicRate * height());

   pimage->create({ cx, cy });

   if (::parallelization::priority() == ::priority_idle)
   {

      map();

      C2PassScale < CBlackmanFilter > scale(1.0);

      scale.Scale(
         pimage->colorref(),
         pimage->width(),
         pimage->height(),
         pimage->scan_size(),
         colorref(),
         width(),
         height(),
         scan_size()
      );

   }
   else
   {

      pimage->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      pimage->g()->stretch(::rect_dim(0, 0, cx, cy), get_graphics(), ::rect_dim(0, 0, width(), height()));

   }

   pimage->set_mipmap(pimage->m_emipmap);

   return true;

}


bool image::create_isotropic(double_array & daRate, ::e_priority epriority)
{

   return false;

   //daRate.sort(false);

   //m_pnext.release();

   //::image * pimageLast = this;

   //image_array imagea;

   //for (const double & dRate : daRate)
   //{

   //   pimageLast->m_pnext.alloc(this);

   //   pimageLast = pimageLast->m_pnext;

   //   pimageLast->m_dIsotropicRate = dRate;

   //   imagea.add(pimageLast);

   //}

   //fork_count_end(get_application(), imagea.get_count(),
   //               [&](index i)
   //{

   //   create_isotropic(imagea[i]);

   //}, 0, epriority);

   //return true;

}


//void image::defer_save_to_cache()
//{
//
//   if (m_pathCache.has_char())
//   {
//
//      ::file::path pathDib = m_pathCache;
//
//      m_pathCache.Empty();
//
//      ::image * pimage = this;
//
//      this->fork([this, pimage, pathDib]()
//      {
//
//         pimage->save_dib(pathDib);
//
//      });
//
//   }
//
//}


bool image::destroy()
{

   m_sizeRaw.cx = 0;
   m_sizeRaw.cy = 0;
   m_size.cx = 0;
   m_size.cy = 0;
   m_sizeAlloc.cx = 0;
   m_sizeAlloc.cy = 0;
   pixmap::reset();
   pixmap::unmap();
   m_eobject = e_object_none;

   return true;

}


//bool image::draw(const ::image * pimage)
//{
//
//   //if (::is_null(pimage))
//   //{
//
//   //   return false;
//
//   //}
//
//   return get_graphics()->draw(::rect_dim(0, 0,
//                                     width(),
//                                     height()),
//                                     pimage->g(),
//                                     ::rect_dim(0, 0,
//                                     pimage->width(),
//                                     pimage->height()));
//
//}


//bool image::to(::draw2d::graphics * pgraphics)
//{
//
//   return to(pgraphics, nullptr, size());
//
//}
//
//
//bool image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point)
//{
//
//   return to(pgraphics, point, size());
//
//}
//
//
//bool image::to(::draw2d::graphics * pgraphics, const ::size_i32 & size)
//{
//
//   return to(pgraphics, nullptr, size);
//
//}
//
//
//bool image::to(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle)
//{
//
//   return to(pgraphics, ::top_left(rectangle), ::size_i32(rectangle));
//
//}
//
//
//bool image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size)
//{
//
//   return to(pgraphics, point, size, nullptr);
//
//}
//
//
//bool image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc)
//{
//
//
//   UNREFERENCED_PARAMETER(pgraphics);
//   UNREFERENCED_PARAMETER(point);
//   UNREFERENCED_PARAMETER(size);
//   UNREFERENCED_PARAMETER(pointSrc);
//   ::exception::throw_interface_only();
//
//   return false;
//
//}


//bool image::stretch(::draw2d::graphics * pgraphics)
//{
//
//   return stretch(pgraphics->m_pimage);
//
//}


bool image::stretch(::image * pimage)
{

   auto pgraphics = get_graphics();

   if (::is_null(pgraphics))
   {

      return false;

   }

   if (this->size().is_empty())
   {

      return false;

   }

   return pgraphics->stretch(::rectangle_f64(this->size()), pimage->g(), ::rectangle_f64(pimage->size()));

}


bool image::_draw_raw(const ::rectangle_i32 & rectDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam)
{

   ::image * pimageDst = this;

   if (
   (!pimageDst->m_bMapped && !pimageSrc->m_bMapped)
   ||
   (
   !(pimageDst->m_bMapped && pimageSrc->m_bMapped)
   &&
   (
   (pimageDst->m_bMapped && !pimageSrc->get_graphics()->prefer_mapped_image_on_mix())
   ||
   (pimageSrc->m_bMapped && !pimageSrc->get_graphics()->prefer_mapped_image_on_mix())
   )
   )
   )
   {

      get_graphics()->set_alpha_mode(m_ealphamode);

      return get_graphics()->draw(rectDstParam, pimageSrc->get_graphics(), pointSrcParam);

   }

   pimageDst->map();

   pimageSrc->map();

   ::rectangle_i32 rectDst(rectDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   rectDst += m_point;

   if (pointSrc.x < 0)
   {
      
      rectDst.left -= pointSrc.x;
      
      pointSrc.x = 0;

   }

   if (pointSrc.y < 0)
   {
      
      rectDst.top -= pointSrc.y;

      pointSrc.y = 0;

   }

   if (rectDst.left < 0)
   {

      rectDst.right += rectDst.left;

      rectDst.left = 0;

   }

   if (rectDst.width() < 0)
   {

      return true;

   }

   if (rectDst.top < 0)
   {

      rectDst.bottom += rectDst.top;

      rectDst.top = 0;

   }

   if (rectDst.height() < 0)
   {

      return true;

   }

   int xEnd = minimum(rectDst.width(), minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectDst.left));

   int yEnd = minimum(rectDst.height(), minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectDst.top));

   if (xEnd < 0)
   {

      return false;

   }

   if (yEnd < 0)
   {

      return false;

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * rectDst.top + rectDst.left * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)];

   color32_t * pdst2;

   color32_t * psrc2;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = (color32_t *)&pdst[scanDst * y];

      psrc2 = (color32_t *)&psrc[scanSrc * y];

      ::memcpy_dup(pdst2, psrc2, xEnd * 4);
      //for(int x = 0; x < xEnd; x++)
      //{

      //   *pdst2 = *psrc2;

      //   pdst2++;

      //   psrc2++;

      //}
      //pdst2 += xEnd;
      //psrc2 += xEnd;

   }

   return true;

}


bool image::blend(const ::rectangle_i32 & rectDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam, byte bA)
{

   ::image * pimageDst = this;

   pimageDst->map();

   pimageSrc->map();

   ::rectangle_i32 rectDst(rectDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(rectDst.size());

   rectDst +=m_point;

   if (pointSrc.x < 0)
   {

      rectDst.left-= pointSrc.x;

      pointSrc.x = 0;

   }

   if (pointSrc.y < 0)
   {

      rectDst.top -= pointSrc.y;

      pointSrc.y = 0;

   }

   if (rectDst.left < 0)
   {

      size.cx += rectDst.left;

      rectDst.left = 0;

   }

   if (size.cx < 0)
   {

      return true;

   }

   if (rectDst.top < 0)
   {

      size.cy += rectDst.top;

      rectDst.top = 0;

   }

   if (size.cy < 0)
   {

      return true;

   }

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectDst.left));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectDst.top));

   if (xEnd < 0)
   {

      return false;

   }

   if (yEnd < 0)
   {

      return false;

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * rectDst.top + rectDst.left * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)];

   u8 * pdst2;

   u8 * psrc2;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = &pdst[scanDst * y];

      psrc2 = &psrc[scanSrc * y];

      for (int x = 0; x < xEnd; x++)
      {

         pdst2[0] = (psrc2[0] * bA) >> 8;
         pdst2[1] = (psrc2[1] * bA) >> 8;
         pdst2[2] = (psrc2[2] * bA) >> 8;
         pdst2[3] = (psrc2[3] * bA) >> 8;

         pdst2 += 4;

         psrc2 += 4;

      }

   }

   return true;

}


bool image::blend2(const ::point_i32 & pointDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam, const ::size_i32 & sizeParam, byte bA)
{

   ::image * pimageDst = this;

   pimageDst->map();

   pimageSrc->map();

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);

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
      return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return true;

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)];

   u8 * pdst2;

   u8 * psrc2;

   if (bA == 0)
   {

   }
   else if (bA == 255)
   {

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         for (int x = 0; x < xEnd; x++)
         {

            int  aDst = pdst2[3];

            int  aSrc = psrc2[3];

            if (aDst == 0)
            {

            }
            else if (aSrc == 0)
            {

               *((color32_t *)pdst2) = 0;

            }
            else
            {

               int r = pdst2[0];
               int g = pdst2[1];
               int b = pdst2[2];

               r = (r << 8) / aDst;
               g = (g << 8) / aDst;
               b = (b << 8) / aDst;

               int a = aSrc * aDst;

               pdst2[0] = (r * a) >> 16;
               pdst2[1] = (g * a) >> 16;
               pdst2[2] = (b * a) >> 16;
               pdst2[3] = a >> 8;

            }

            pdst2 += 4;

            psrc2 += 4;

         }

      }

   }
   else
   {
      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memcpy_dup(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
         {

            //*pdst2 = *psrc2;

            //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
            //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
            //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
            //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
            //byte acomplement = (~psrc2[3] * bA) >> 8;
            //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
            //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
            //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
            //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
            byte acomplement = (~psrc2[3] * bA) >> 8;
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

   return true;

}

bool image::blend(const ::point_i32 & pointDst, ::image * pimageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size)
{

   return blend(pointDst, pimageSrc, pointSrc, size, 255);

}


bool image::blend(const ::point_i32 & pointDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam, const ::size_i32 & sizeParam, byte bA)
{

   ::image * pimageDst = this;

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);


   pimageDst->map();

   pimageSrc->map();

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
      return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return true;

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;


   u8 * pdst2;

   u8 * psrc2;

#ifdef __APPLE__
   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * (pimageDst->height() - pointDst.y - yEnd) + pointDst.x * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * (pimageSrc->height() - pointSrc.y - yEnd) + pointSrc.x * sizeof(color32_t)];

#else

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc *  pointSrc.y + pointSrc.x * sizeof(color32_t)];

#endif

   bool bFontListBlend = true;

   if (bFontListBlend)
   {

      if (bA == 0)
      {

      }
      else if (bA == 255)
      {

         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memcpy_dup(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               byte acomplement = ~psrc2[3];
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
         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memcpy_dup(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               //byte acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               byte acomplement = (~psrc2[3] * bA) >> 8;
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

         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memcpy_dup(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               byte a = pdst2[3];
               byte alpha = psrc2[3];
               if (a == 0)
               {

               }
               else if(alpha == 0)
               {

                  *((color32_t *)pdst2) = 0;

               }
               else
               {

                  //int d0 = pdst2[0] * 255 / a;
                  //int d1 = pdst2[1] * 255 / a;
                  //int d2 = pdst2[2] * 255 / a;

                  //int s0 = psrc2[0] * 255 / alpha;
                  //int s1 = psrc2[1] * 255 / alpha;
                  //int s2 = psrc2[2] * 255 / alpha;

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
         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memcpy_dup(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               //byte acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               byte acomplement = (~psrc2[3] * bA) >> 8;
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

   return true;

}


bool image::precision_blend(const ::point_i32 & pointDst, ::image * pimageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size)
{

   return precision_blend(pointDst, pimageSrc, pointSrc, size, 255);

}


bool image::precision_blend(const ::point_i32 & pointDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam, const ::size_i32 & sizeParam, byte bA)
{

   ::image * pimageDst = this;

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);

   pimageDst->map();

   pimageSrc->map();

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
      return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return true;

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)];

   u8 * pdst2;

   u8 * psrc2;

   if (bA == 0)
   {

   }
   else if (bA == 255)
   {

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memcpy_dup(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
         {

            //*pdst2 = *psrc2;

            //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
            //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
            //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
            //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
            byte acomplement = ~psrc2[3];
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
      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memcpy_dup(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
         {

            //*pdst2 = *psrc2;

            //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
            //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
            //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
            //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
            //byte acomplement = (~psrc2[3] * bA) >> 8;
            //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
            //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
            //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
            //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
            byte acomplement = (~psrc2[3] * bA) / 255;
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

   return true;

}






bool image::fork_blend(const ::point_i32 & pointDst, ::image * pimageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size)
{

   return fork_blend(pointDst, pimageSrc, pointSrc, size, 255);

}


bool image::fork_blend(const ::point_i32 & pointDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam, const ::size_i32 & sizeParam, byte bA)
{

   if (bA == 0)
   {


      return true;

   }

   ::image * pimageDst = this;

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);

   pimageDst->map();

   pimageSrc->map();

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
      return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointSrc.y -= pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return true;

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd <= 0)
      return false;

   if (yEnd <= 0)
      return false;

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)];

   //u8 * pdst5; // dst opacity map if available // opacity map does not make sense for images that machine

   u8 * psrcOpacity; // src opacity map if available

   u8 * psrcTransparency; // src transparency map if available

   if (pimageSrc->m_memoryMap.size() == pimageSrc->area() * 2)
   {

      psrcOpacity = &pimageSrc->m_memoryMap.get_data()[pimageSrc->width() * pointSrc.y + pointSrc.x];

   }
   else
   {

      psrcOpacity = nullptr;

   }

   if (pimageSrc->m_memoryMap.size() == pimageSrc->area() * 2)
   {

      psrcTransparency = &pimageSrc->m_memoryMap.get_data()[pimageSrc->area() + pimageSrc->width() * pointSrc.y + pointSrc.x];

   }
   else
   {

      psrcTransparency = nullptr;

   }

   __pointer(::aura::system) psystem = m_psystem;

   auto pgroup = psystem->task_group();

   synchronous_lock slGroup(pgroup->mutex());

   auto ptool = psystem->task_tool(::e_task_tool_draw2d);

   synchronous_lock slTool(ptool->mutex());

   if(!pgroup || !ptool)
   {

      return blend(pointDst, pimageSrc, pointSrc, size, bA);

   }

   int y = 0;

   pgroup->select_tool(ptool);

   pgroup->prepare(::e_task_op_tool, yEnd);

   for(auto & ptoolitem : ptool->m_itema)
   {

      __pointer(::draw2d::task_tool_item) pitem = ptoolitem;

      pitem->m_eop = ::draw2d::task_tool_item::op_blend;

      pitem->m_w = pimageSrc->width();

      pitem->m_h = pimageSrc->height();

      pitem->m_ySkip = (int) (pgroup->task_count());

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

   (*pgroup)();

   return true;

}


bool image::draw_ignore_alpha(const ::point_i32 & pointDstParam, ::image * pimage, const ::rectangle_i32 & rectSrcParam)
{

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(rectSrcParam.top_left());

   ::size_i32 size(rectSrcParam.size());

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

   int xEnd = minimum(size.cx, minimum(pimage->width() - pointSrc.x, width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimage->height() - pointSrc.y, height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;

   i32 s1 = m_iScan / sizeof(color32_t);

   i32 s2 = pimage->m_iScan / sizeof(color32_t);

   color32_t * pdst = &colorref()[s1 * pointDst.y] + pointDst.x;

   color32_t * psrc = &pimage->colorref()[s2 * pointSrc.y] + pointSrc.x;

   color32_t * pdst2;

   color32_t * psrc2;

   int i = 0;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = &pdst[s1 * y];

      psrc2 = &psrc[s2 * y];

      for (int x = 0; x < xEnd; x++)
      {

         if (colorref_get_a_value(*psrc2) == 0)
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

   return true;

}


bool image::blend(const ::point_i32 & pointDstParam, ::image * pimageSrc, const ::point_i32 & pointSrcParam, ::image * pimageAlf, const ::point_i32 & pointDstAlfParam, const ::size_i32 & sizeParam)
{

   ::image * pimageDst = this;

   pimageDst->map();
   pimageSrc->map();
   pimageAlf->map();

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::point_i32 pointDstAlf(pointDstAlfParam);

   ::size_i32 size(sizeParam);

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
      return true;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return true;

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;


   if (pointDstAlf.x < 0)
   {
   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   i32 scanAlf = pimageAlf->m_iScan;

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)];

   u8 * palf = &((u8 *)pimageAlf->colorref())[-scanAlf * pointDstAlf.y - pointDstAlf.x * sizeof(color32_t)] + 3;

   u8 * pdst2;

   u8 * psrc2;

   u8 * palf2;

   int x1;
   int x2;
   int y1;
   int y2;

   x1 = pointDstAlf.x;
   x2 = pimageAlf->width() + x1;
   y1 = pointDstAlf.y;
   y2 = pimageAlf->height() + y1;


   //int a;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = (u8 *)&pdst[scanDst * y];

      psrc2 = (u8 *)&psrc[scanSrc * y];

      palf2 = (u8 *)&palf[scanAlf * y];

      for (int x = 0; x < xEnd; x++)
      {

         if (psrc2[3] > 0)
         {
//               if (false && x >= x1 && x < x2 && y >= y1 && y < y2)
//               {
//
//                  a = (*palf2 * psrc2[3]) / 255;
//                  a = psrc2[3];
//                  //a = (int) (byte) sqrt((float) (*palf2 * psrc2[3]));
//                  pdst2[3] = (byte)maximum(a, pdst2[3]);
//                  //pdst2[3] = (byte)((((int)psrc2[3] - (int)pdst2[3]) * a + ((int)pdst2[3] * 255)) / 255);
//                  pdst2[3] = (byte)(maximum(psrc2[3], pdst2[3]));
//
//                  //                  if (a > 0)
//                  {
//
//                     pdst2[0] = (byte)((((int)psrc2[0] - (int)pdst2[0]) * a + ((int)pdst2[0] * 255)) / 255);
//                     pdst2[1] = (byte)((((int)psrc2[1] - (int)pdst2[1]) * a + ((int)pdst2[1] * 255)) / 255);
//                     pdst2[2] = (byte)((((int)psrc2[2] - (int)pdst2[2]) * a + ((int)pdst2[2] * 255)) / 255);
//
//                  }
//
//               }
//               else
            {

               //pdst2[3] = (byte)(maximum(psrc2[3], pdst2[3]));
               //pdst2[3] = (byte)((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255);
               //pdst2[0] = (byte)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
               //pdst2[1] = (byte)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
               //pdst2[2] = (byte)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);
               pdst2[3] = (byte)(maximum(((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255), pdst2[3]));
               pdst2[0] = (byte)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
               pdst2[1] = (byte)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
               pdst2[2] = (byte)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);

            }
         }


         pdst2 += 4;

         psrc2 += 4;

         palf2 += 4;


      }

   }

   return true;

}

/*
bool image::blend(const ::point_i32 & pointDst,::image * pimageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size)
{

   ::image * pimageDst = this;

   pimageDst->map();
   pimageSrc->map();


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

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;



   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

#ifdef __APPLE__

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * (pimageDst->height() - pointDst.y - 1) + pointDst.x * sizeof(color32_t)] + 3;

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * (pimageSrc->height() - pointSrc.y - 1) + pointSrc.x * sizeof(color32_t)] + 3;

#else

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)] + 3;

   u8 * psrc = &((u8 *)pimageSrc->colorref())[scanSrc * pointSrc.y + pointSrc.x * sizeof(color32_t)] + 3;

#endif

   u8 * pdst2;

   u8 * psrc2;

   pimageDst->div_alpha(pointDst, ::size_i32(xEnd, yEnd));
   pimageSrc->div_alpha(pointSrc, ::size_i32(xEnd, yEnd));


   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (u8 *) &pdst[scanDst * (-y)];

      psrc2 = (u8 *) &psrc[scanSrc * (-y)];

#else

      pdst2 = (u8 *) &pdst[scanDst * y];

      psrc2 = (u8 *) &psrc[scanSrc * y];

#endif

      for (int x = 0; x < xEnd; x++)
      {

         *pdst2 = *psrc2 * *pdst2 / 255;

         pdst2+=4;

         psrc2+=4;

      }

   }
   pimageDst->mult_alpha(pointDst, ::size_i32(xEnd, yEnd));
   pimageSrc->mult_alpha(pointSrc, ::size_i32(xEnd, yEnd));

   return true;

}
*/


bool image::set_rgb(i32 R, i32 G, i32 B)
{

   i64 size = scan_area();

   color32_t * pcr = get_data();

   if (pcr == nullptr)
   {

      return false;

   }

   sort_image_rgb(R, G, B);

   for (i32 i = 0; i < size; i++)
   {

      ((u8 *)pcr)[0] = R;
      ((u8 *)pcr)[1] = G;
      ((u8 *)pcr)[2] = B;

      pcr++;

   }

   return true;

}


/*   bool image::Fill ( i32 R, i32 G, i32 B )
   {
      color32_t color=rgb ( B, G, R );
      i64 size = area();

      color32_t * pcr;

      i64 iSize32 = size / 32;
      i32 i;
      for (i=0; i < iSize32; i+=32 )
      {
         pcr = &get_data()[i];
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

      for (i=0; i<size_i32; i++ )
      {
         get_data()[i]=color;
      }
   }
   */


bool image::flip_vertical(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   int w = width();

   int h = height();

   int sw = w * 4;

   int dsw = m_iScan / 4;

   int ssw = pimage->m_iScan / 4;

   for (index y = 0; y < h; y++)
   {

      ::memcpy_dup(&colorref()[y * dsw], &pimage->colorref()[(h - y - 1) * ssw], sw);

   }

   return true;

}


bool image::flip_horizontal(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   int half = -1;

   int dsw = m_iScan / 4;

   int ssw = pimage->m_iScan / 4;

   int w = width();

   auto pcolorref = colorref();

   auto pcolorrefSrc = pimage->colorref();

   for (index y = 0; y < pimage->height(); y++)
   {

      for (index x = 0; x < w; x++)
      {

         pcolorref[y * dsw + x] = pcolorrefSrc[y * ssw + w - x - 1];

      }

   }

   return true;

}


bool image::flipx(::image * pimage)
{

   return flip_horizontal(pimage);

}


bool image::flipy(::image * pimage)
{

   return flip_vertical(pimage);

}


::image * image::flipx()
{

   ::image_pointer pimage = clone();

   flipx(pimage);

   return this;

}


::image * image::flipy()
{

   ::image_pointer pimage = clone();

   flipy(pimage);

   return this;

}


bool image::ToAlpha(i32 i)
{
   u8 * dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[3] = dst[i];
      dst += 4;
   }

   return true;

}


bool image::from_alpha()
{

   u8 *dst = (u8 *)get_data();

   i64 size = scan_area();

   while (size--)
   {
      dst[0] = dst[3];
      dst[1] = dst[3];
      dst[2] = dst[3];
      dst += 4;
   }

   return true;

}


bool image::mult_alpha(::image * pimage, bool bPreserveAlpha)
{
   UNREFERENCED_PARAMETER(pimage);
   UNREFERENCED_PARAMETER(bPreserveAlpha);

   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = LOBYTE(((i32)dst[0] * (i32)dst[3]) >> 8);
      dst[1] = LOBYTE(((i32)dst[1] * (i32)dst[3]) >> 8);
      dst[2] = LOBYTE(((i32)dst[2] * (i32)dst[3]) >> 8);

      dst[4 + 0] = LOBYTE(((i32)dst[4 + 0] * (i32)dst[4 + 3]) >> 8);
      dst[4 + 1] = LOBYTE(((i32)dst[4 + 1] * (i32)dst[4 + 3]) >> 8);
      dst[4 + 2] = LOBYTE(((i32)dst[4 + 2] * (i32)dst[4 + 3]) >> 8);

      dst[8 + 0] = LOBYTE(((i32)dst[8 + 0] * (i32)dst[8 + 3]) >> 8);
      dst[8 + 1] = LOBYTE(((i32)dst[8 + 1] * (i32)dst[8 + 3]) >> 8);
      dst[8 + 2] = LOBYTE(((i32)dst[8 + 2] * (i32)dst[8 + 3]) >> 8);

      dst[12 + 0] = LOBYTE(((i32)dst[12 + 0] * (i32)dst[12 + 3]) >> 8);
      dst[12 + 1] = LOBYTE(((i32)dst[12 + 1] * (i32)dst[12 + 3]) >> 8);
      dst[12 + 2] = LOBYTE(((i32)dst[12 + 2] * (i32)dst[12 + 3]) >> 8);

      dst[16 + 0] = LOBYTE(((i32)dst[16 + 0] * (i32)dst[16 + 3]) >> 8);
      dst[16 + 1] = LOBYTE(((i32)dst[16 + 1] * (i32)dst[16 + 3]) >> 8);
      dst[16 + 2] = LOBYTE(((i32)dst[16 + 2] * (i32)dst[16 + 3]) >> 8);

      dst[20 + 0] = LOBYTE(((i32)dst[20 + 0] * (i32)dst[20 + 3]) >> 8);
      dst[20 + 1] = LOBYTE(((i32)dst[20 + 1] * (i32)dst[20 + 3]) >> 8);
      dst[20 + 2] = LOBYTE(((i32)dst[20 + 2] * (i32)dst[20 + 3]) >> 8);

      dst[24 + 0] = LOBYTE(((i32)dst[24 + 0] * (i32)dst[24 + 3]) >> 8);
      dst[24 + 1] = LOBYTE(((i32)dst[24 + 1] * (i32)dst[24 + 3]) >> 8);
      dst[24 + 2] = LOBYTE(((i32)dst[24 + 2] * (i32)dst[24 + 3]) >> 8);

      dst[28 + 0] = LOBYTE(((i32)dst[28 + 0] * (i32)dst[28 + 3]) >> 8);
      dst[28 + 1] = LOBYTE(((i32)dst[28 + 1] * (i32)dst[28 + 3]) >> 8);
      dst[28 + 2] = LOBYTE(((i32)dst[28 + 2] * (i32)dst[28 + 3]) >> 8);

      dst += 4 * 8;
      size -= 8;
   }
   while (size--)
   {
      dst[0] = LOBYTE(((i32)dst[0] * (i32)dst[3]) >> 8);
      dst[1] = LOBYTE(((i32)dst[1] * (i32)dst[3]) >> 8);
      dst[2] = LOBYTE(((i32)dst[2] * (i32)dst[3]) >> 8);
      dst += 4;
   }

   return true;

}


#define byte_clip2(i) (i)
bool image::mult_alpha()
{
   map();

   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();


   //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
      dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
      dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);

      dst[4 + 0] = byte_clip2(((i32)dst[4 + 0] * (i32)dst[4 + 3]) / 255);
      dst[4 + 1] = byte_clip2(((i32)dst[4 + 1] * (i32)dst[4 + 3]) / 255);
      dst[4 + 2] = byte_clip2(((i32)dst[4 + 2] * (i32)dst[4 + 3]) / 255);

      dst[8 + 0] = byte_clip2(((i32)dst[8 + 0] * (i32)dst[8 + 3]) / 255);
      dst[8 + 1] = byte_clip2(((i32)dst[8 + 1] * (i32)dst[8 + 3]) / 255);
      dst[8 + 2] = byte_clip2(((i32)dst[8 + 2] * (i32)dst[8 + 3]) / 255);

      dst[12 + 0] = byte_clip2(((i32)dst[12 + 0] * (i32)dst[12 + 3]) / 255);
      dst[12 + 1] = byte_clip2(((i32)dst[12 + 1] * (i32)dst[12 + 3]) / 255);
      dst[12 + 2] = byte_clip2(((i32)dst[12 + 2] * (i32)dst[12 + 3]) / 255);

      dst[16 + 0] = byte_clip2(((i32)dst[16 + 0] * (i32)dst[16 + 3]) / 255);
      dst[16 + 1] = byte_clip2(((i32)dst[16 + 1] * (i32)dst[16 + 3]) / 255);
      dst[16 + 2] = byte_clip2(((i32)dst[16 + 2] * (i32)dst[16 + 3]) / 255);

      dst[20 + 0] = byte_clip2(((i32)dst[20 + 0] * (i32)dst[20 + 3]) / 255);
      dst[20 + 1] = byte_clip2(((i32)dst[20 + 1] * (i32)dst[20 + 3]) / 255);
      dst[20 + 2] = byte_clip2(((i32)dst[20 + 2] * (i32)dst[20 + 3]) / 255);

      dst[24 + 0] = byte_clip2(((i32)dst[24 + 0] * (i32)dst[24 + 3]) / 255);
      dst[24 + 1] = byte_clip2(((i32)dst[24 + 1] * (i32)dst[24 + 3]) / 255);
      dst[24 + 2] = byte_clip2(((i32)dst[24 + 2] * (i32)dst[24 + 3]) / 255);

      dst[28 + 0] = byte_clip2(((i32)dst[28 + 0] * (i32)dst[28 + 3]) / 255);
      dst[28 + 1] = byte_clip2(((i32)dst[28 + 1] * (i32)dst[28 + 3]) / 255);
      dst[28 + 2] = byte_clip2(((i32)dst[28 + 2] * (i32)dst[28 + 3]) / 255);

      dst += 4 * 8;
      size -= 8;
   }
   while (size--)
   {
      dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
      dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
      dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);
      dst += 4;
   }

   return true;

}


bool image::mult_alpha_fast()
{
   map();

   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();


   //  >> 2 instead of >> 2 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size--)
   {
      if (dst[3] == 0)
      {
         *((color32_t*)dst) = 0;
      }
      else if (dst[3] != 255)
      {
         dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) >> 8);
         dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) >> 8);
         dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) >> 8);
      }
      dst += 4;
   }

   return true;

}


bool image::mult_alpha(const ::point_i32 & pointDstParam, const ::size_i32 & sizeParam)
{

   ::point_i32 pointDst(pointDstParam);

   ::size_i32 size(sizeParam);

   ::image * pimageDst = this;

   pimageDst->map();

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
      return false;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return false;

   int xEnd = minimum(size.cx, pimageDst->width() - pointDst.x);

   int yEnd = minimum(size.cy, pimageDst->height() - pointDst.y);

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;

   i32 scanDst = pimageDst->m_iScan;

#ifdef __APPLE__

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * (height() - pointDst.y - 1) + pointDst.x * sizeof(color32_t)];

#else

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

#endif

   u8 * pdst2;

   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (u8 *)&pdst[scanDst * (-y)];

#else

      pdst2 = (u8 *)&pdst[scanDst * y];

#endif

      for (int x = 0; x < xEnd; x++)
      {

         pdst2[0] = byte_clip(((i32)pdst2[0] * (i32)pdst2[3]) / 255);
         pdst2[1] = byte_clip(((i32)pdst2[1] * (i32)pdst2[3]) / 255);
         pdst2[2] = byte_clip(((i32)pdst2[2] * (i32)pdst2[3]) / 255);

         pdst2 += 4;

      }

   }

   return true;

}


bool image::create_thumbnail(const char * psz)
{

   return false;

}


bool image::div_alpha()
{

   map();

   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   /*      while (size >= 8)
         {
            dst[0] = LOBYTE(((i32)dst[0] * (i32)dst[3])>> 8);
            dst[1] = LOBYTE(((i32)dst[1] * (i32)dst[3])>> 8);
            dst[2] = LOBYTE(((i32)dst[2] * (i32)dst[3])>> 8);

            dst[4+0] = LOBYTE(((i32)dst[4+0] * (i32)dst[4+3])>> 8);
            dst[4+1] = LOBYTE(((i32)dst[4+1] * (i32)dst[4+3])>> 8);
            dst[4+2] = LOBYTE(((i32)dst[4+2] * (i32)dst[4+3])>> 8);

            dst[8+0] = LOBYTE(((i32)dst[8+0] * (i32)dst[8+3])>> 8);
            dst[8+1] = LOBYTE(((i32)dst[8+1] * (i32)dst[8+3])>> 8);
            dst[8+2] = LOBYTE(((i32)dst[8+2] * (i32)dst[8+3])>> 8);

            dst[12+0] = LOBYTE(((i32)dst[12+0] * (i32)dst[12+3])>> 8);
            dst[12+1] = LOBYTE(((i32)dst[12+1] * (i32)dst[12+3])>> 8);
            dst[12+2] = LOBYTE(((i32)dst[12+2] * (i32)dst[12+3])>> 8);

            dst[16+0] = LOBYTE(((i32)dst[16+0] * (i32)dst[16+3])>> 8);
            dst[16+1] = LOBYTE(((i32)dst[16+1] * (i32)dst[16+3])>> 8);
            dst[16+2] = LOBYTE(((i32)dst[16+2] * (i32)dst[16+3])>> 8);

            dst[20+0] = LOBYTE(((i32)dst[20+0] * (i32)dst[20+3])>> 8);
            dst[20+1] = LOBYTE(((i32)dst[20+1] * (i32)dst[20+3])>> 8);
            dst[20+2] = LOBYTE(((i32)dst[20+2] * (i32)dst[20+3])>> 8);

            dst[24+0] = LOBYTE(((i32)dst[24+0] * (i32)dst[24+3])>> 8);
            dst[24+1] = LOBYTE(((i32)dst[24+1] * (i32)dst[24+3])>> 8);
            dst[24+2] = LOBYTE(((i32)dst[24+2] * (i32)dst[24+3])>> 8);

            dst[28+0] = LOBYTE(((i32)dst[28+0] * (i32)dst[28+3])>> 8);
            dst[28+1] = LOBYTE(((i32)dst[28+1] * (i32)dst[28+3])>> 8);
            dst[28+2] = LOBYTE(((i32)dst[28+2] * (i32)dst[28+3])>> 8);

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
         dst[0] = byte_clip((i32)dst[0] * 255 / (i32)dst[3]);
         dst[1] = byte_clip((i32)dst[1] * 255 / (i32)dst[3]);
         dst[2] = byte_clip((i32)dst[2] * 255 / (i32)dst[3]);
      }

      dst += 4;

   }

   return true;

}


bool image::div_alpha(const ::point_i32 & pointDstParam, const ::size_i32 & sizeParam)
{

   ::point_i32 pointDst(pointDstParam);

   ::size_i32 size(sizeParam);


   ::image * pimageDst = this;

   pimageDst->map();

   if (pointDst.x < 0)
   {
      size.cx += pointDst.x;
      pointDst.x = 0;
   }

   if (size.cx < 0)
      return false;

   if (pointDst.y < 0)
   {
      size.cy += pointDst.y;
      pointDst.y = 0;
   }

   if (size.cy < 0)
      return false;

   int xEnd = minimum(size.cx, pimageDst->width() - pointDst.x);

   int yEnd = minimum(size.cy, pimageDst->height() - pointDst.y);

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;

   i32 scanDst = pimageDst->m_iScan;

#ifdef __APPLE__

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * (height() - pointDst.y - 1) + pointDst.x * sizeof(color32_t)];

#else

   u8 * pdst = &((u8 *)pimageDst->colorref())[scanDst * pointDst.y + pointDst.x * sizeof(color32_t)];

#endif

   u8 * pdst2;

   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (u8 *)&pdst[scanDst * (-y)];

#else

      pdst2 = (u8 *)&pdst[scanDst * y];

#endif

      for (int x = 0; x < xEnd; x++)
      {

         if (pdst2[3] == 0)
         {
            pdst2[0] = 0;
            pdst2[1] = 0;
            pdst2[2] = 0;
         }
         else
         {
            pdst2[0] = byte_clip((i32)pdst2[0] * 255 / (i32)pdst2[3]);
            pdst2[1] = byte_clip((i32)pdst2[1] * 255 / (i32)pdst2[3]);
            pdst2[2] = byte_clip((i32)pdst2[2] * 255 / (i32)pdst2[3]);
         }

         pdst2 += 4;

      }

   }

   return true;

}


bool image::Map(i32 ToRgb, i32 FromRgb)
{

   u8 * dst = (u8 *)get_data();

   i64 size = scan_area();

   while (size--)
   {

      *dst = (byte)(*dst == FromRgb ? ToRgb : *dst);

      dst += 4;

   }

   return true;

}


bool image::ToAlphaAndFill(i32 i, color32_t cr)
{

   u8 *dst = (u8 *)get_data();

   i64 size = scan_area();

   byte uchB = ::blue(cr);
   byte uchG = ::green(cr);
   byte uchR = ::red(cr);

   while (size--)
   {
      dst[3] = dst[i];
      dst[0] = uchB;
      dst[1] = uchG;
      dst[2] = uchR;
      dst += 4;
   }

   return true;

}


bool image::GrayToARGB(color32_t cr)
{

   u8 *dst = (u8 *)get_data();

   i64 size = scan_area();

   u32 dwB = ::blue(cr);
   u32 dwG = ::green(cr);
   u32 dwR = ::red(cr);

   while (size-- > 0)
   {
      dst[3] = dst[0];
      dst[0] = (byte)(((dwB * dst[3]) / 256) & 0xff);
      dst[1] = (byte)(((dwG * dst[3]) / 256) & 0xff);
      dst[2] = (byte)(((dwR * dst[3]) / 256) & 0xff);
      dst += 4;
   }

   return true;

}


bool image::BitBlt(::image * pimage, i32 op)
{

   if (op == 123) // zero dest rgb, invert alpha, and OR src rgb
   {

      __throw(todo);
      //stretch(pimage);

   }

   return true;

}


bool image::BitBlt(int cxParam, int cyParam, ::image * pimage, i32 op)
{

   map();

   pimage->map();

   if (op == 1 && size() == pimage->size() && pimage->m_iScan == m_iScan) // op == 1 indicates can ignore cxParam and cyParam and perform full ::memcpy_dup
   {

      if (cyParam <= 0)
         return false;

      cyParam = minimum(cyParam, minimum(pimage->height(), height()));

#if defined(__APPLE__)

      ::memcpy_dup(&colorref()[m_iScan / 4 * (pimage->height() - cyParam)], &pimage->colorref()[m_iScan / 4 * (pimage->height() - cyParam)], cyParam * m_iScan);

#else

      ::memcpy_dup(colorref(), pimage->colorref(), cyParam * m_iScan);

#endif

   }
   else if (op == 0 || op == 1)
   {

      if (cxParam <= 0)
         return false;

      if (cyParam <= 0)
         return false;

      cxParam = minimum(cxParam, minimum(pimage->width(), width()));

      cyParam = minimum(cyParam, minimum(pimage->height(), height()));

      int iStrideSrc = pimage->m_iScan;

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(color32_t);

      }

      if (m_iScan == iStrideSrc && m_iScan == pimage->m_iScan)
      {

         ::memcpy_dup(colorref(), pimage->colorref(), cyParam * m_iScan);

      }
      else
      {

         int wsrc = iStrideSrc / sizeof(color32_t);
         int wdst = m_iScan / sizeof(color32_t);
         int cw = minimum(cxParam, width()) * sizeof(color32_t);

         int h = minimum(cyParam, height());


         color32_t * psrc = pimage->colorref();
         color32_t * pdst = colorref();

         for (int i = 0; i < h; i++)
         {

            ::memcpy_dup(pdst, psrc, cw);

            pdst += wdst;

            psrc += wsrc;

         }

      }

   }

   return true;

}


bool image::invert()
{

   map();

   i64 size = scan_area();
   byte * pb = (byte *)get_data();

   for (i32 i = 0; i < size; i++)
   {
      pb[0] = 255 - pb[0];

      pb[1] = 255 - pb[1];

      pb[2] = 255 - pb[2];

      pb += 4;


   }

   return true;

}


bool image::channel_invert(::color::enum_channel echannel)
{

   i64 size = scan_area();

   byte * pb = (byte *)get_data();


   pb += ((i32)echannel) % 4;


   for (i32 i = 0; i < size; i++)
   {

      *pb = 255 - *pb;


      pb += 4;


   }

   return true;

}


bool image::channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult)
{

   if (dRate < 0)
   {

      return false;

   }

   //#ifdef __APPLE__
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_alpha)
   {

      div_alpha();

   }
   //#endif
   i64 size = scan_area();
   byte * pb = (byte *)get_data();

   pb += ((i32)echannel) % 4;

   i32 iDiv = 256 * 256;
   i32 iMul = (i32)(dRate * ((double)iDiv));
   i32 iRes;
   for (i64 i = 0; i < size; i++)
   {
      iRes = *pb * iMul / iDiv;

      *pb = (byte)(iRes > 255 ? 255 : iRes);

      pb += 4;

   }
   //#ifdef __APPLE__
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_alpha)
   {
      mult_alpha();
   }
   //#endif

   return true;

}


bool image::channel_multiply(::color::enum_channel echannel, ::image * pimage, bool bIfAlphaIgnorePreDivPosMult)
{

   //      i64 size = area();

   map();

   pimage->map();
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_alpha)
   {
      div_alpha();
   }

   byte * pb1 = (byte *)get_data();


   byte * pb2 = (byte *)pimage->get_data();


   pb1 += ((i32)echannel) % 4;


   pb2 += ((i32)echannel) % 4;


   for (i32 y = 0; y < height(); y++)
   {

      byte * pb1_2 = pb1 + (m_iScan * y);


      byte * pb2_2 = pb2 + (pimage->m_iScan * y);


      for (i32 x = 0; x < width(); x++)
      {

         int i = (byte)(((u32)*pb1_2 * (u32)*pb2_2) / 255);

         *pb2 = i;


         pb1_2 += 4;


         pb2_2 += 4;


      }

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_alpha)
   {

      mult_alpha();

   }

   return true;

}


bool image::channel_darken(::color::enum_channel echannel, ::image * pimage)
{

   i64 size = scan_area();

   byte * pb1 = (byte *)get_data();

   byte * pb2 = (byte *)pimage->get_data();

   pb1 += ((i32)echannel) % 4;

   pb2 += ((i32)echannel) % 4;

   for (i64 i = 0; i < size; i++)
   {
      *pb1 = *pb1 < *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   return true;

}


bool image::channel_lighten(::color::enum_channel echannel, ::image * pimage)
{

   i64 size = scan_area();
   byte * pb1 = (byte *)get_data();

   byte * pb2 = (byte *)pimage->get_data();

   pb1 += ((i32)echannel) % 4;

   pb2 += ((i32)echannel) % 4;

   for (i64 i = 0; i < size; i++)
   {
      *pb1 = *pb1 > *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   return true;

}


bool image::channel_from(::color::enum_channel echannel, ::image * pimage)
{
   
   map();
   
   pimage->map();
   
   i64 size = m_iScan * height() / sizeof(color32_t);
   
   i64 size_i64 = size / 64;

   byte * pb1 = (byte *)get_data();

   byte * pb2 = (byte *)pimage->get_data();

   pb1 += ((i32)echannel) % 4;

   pb2 += ((i32)echannel) % 4;

   i64 i = 0;
   for (; i < size_i64; i++)
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

   return true;

}


bool image::channel_from(::color::enum_channel echannel, ::image * pimage, const ::rectangle_i32 & rectParam)
{

   map();

   pimage->map();

   ::rectangle_i32 rectangle;

   if (!rectangle.intersect(this->rectangle(), rectParam))

   {

      return false;

   }

   if (!rectangle.intersect(pimage->rectangle(), rectangle))

   {

      return false;

   }

   byte * pb1 = ((byte *)get_data()) + (rectangle.left * sizeof(color32_t) + rectangle.top * m_iScan);


   byte * pb2 = ((byte *)pimage->get_data()) + (rectangle.left * sizeof(color32_t) + rectangle.top * pimage->m_iScan);


   pb1 += ((i32)echannel) % 4;


   pb2 += ((i32)echannel) % 4;


   int h = rectangle.height();

   int w = rectangle.width();

   for (int i = 0; i < h; i++)
   {

      byte * pb1_2 = pb1;


      byte * pb2_2 = pb2;


      for (int j = 0; j < w; j++)
      {

         *pb1_2 = *pb2_2;


         pb1_2 += 4;


         pb2_2 += 4;


      }

      pb1 += m_iScan;


      pb2 += pimage->m_iScan;


   }

   return true;

}



bool image::channel_multiply(::color::enum_channel echannel, ::image * pimage, const ::rectangle_i32 & rectParam, bool bIfAlphaIgnorePreDivPosMult)
{

   map();

   pimage->map();

   ::rectangle_i32 rectangle;

   if (!rectangle.intersect(this->rectangle(), rectParam))

   {

      return false;

   }

   if (!rectangle.intersect(pimage->rectangle(), rectangle))

   {

      return false;

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_alpha)
   {

      div_alpha(rectangle.top_left(), rectangle.size());

   }

#ifdef __APPLE__

   byte * pb1 = ((byte *)get_data()) + (rectangle.left * sizeof(color32_t) + (height() - rectangle.top - 1) * m_iScan);


   byte * pb2 = ((byte *)pimage->get_data()) + (rectangle.left * sizeof(color32_t) + (pimage->height() - rectangle.top - 1) * pimage->m_iScan);


#else

   byte * pb1 = ((byte *)get_data()) + (rectangle.left * sizeof(color32_t) + rectangle.top * m_iScan);


   byte * pb2 = ((byte *)pimage->get_data()) + (rectangle.left * sizeof(color32_t) + rectangle.top * pimage->m_iScan);


#endif

   pb1 += ((i32)echannel) % 4;


   pb2 += ((i32)echannel) % 4;


   int h = rectangle.height();

   int w = rectangle.width();

   for (int i = 0; i < h; i++)
   {

      byte * pb1_2 = pb1;


      byte * pb2_2 = pb2;


      for (int j = 0; j < w; j++)
      {

         *pb1_2 = *pb2_2 * *pb1_2 / 255;


         pb1_2 += 4;


         pb2_2 += 4;


      }

#ifdef __APPLE__

      pb1 -= m_iScan;


      pb2 -= pimage->m_iScan;


#else

      pb1 += m_iScan;


      pb2 += pimage->m_iScan;


#endif

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_alpha)
   {

      mult_alpha(rectangle.top_left(), rectangle.size());

   }

   return true;

}


bool image::fill_glass(i32 R, i32 G, i32 B, i32 A)
{

   u8 *dst = (u8 *)get_data();

   i64 size = scan_area();

   while (size--)
   {

      dst[0] = (byte)(((B - dst[0])*A + (dst[0] << 8)) >> 8);
      dst[1] = (byte)(((G - dst[1])*A + (dst[1] << 8)) >> 8);
      dst[2] = (byte)(((R - dst[2])*A + (dst[2] << 8)) >> 8);
      dst += 4;

   }

   return true;

}


bool image::fill_stippled_glass(i32 R, i32 G, i32 B)
{

   color32_t color = rgb(B, G, R);
   i32 w = width();
   i32 h = height();

   for (i32 j = 0; j < w; j++)
   {
      for (i32 i = 0; i < h; i++)
      {
         get_data()[j*w + i] = ((i + j) & 0x1) ? get_data()[j*w + i] : color;
      }
   }

   return true;

}


//bool image::to(::image * pimage) const
//{
//
//   if (::is_null(pimage))
//   {
//
//      return false;
//
//   }
//
//   return pimage->from(this);
//
//}


bool image::copy(const ::image * pimage, ::eobject eobjectCreate)
{

   if (size() != pimage->size())
   {

      create(pimage->size(), eobjectCreate);

   }
   else
   {

      m_eobject = eobjectCreate;

   }

   //pimage->defer_realize(pimage->get_graphics());
   //defer_realize(pimage->get_graphics());

   map();

   ((::image *) pimage)->map();
   // If DibSize Wrong Re-create image_impl
   // do Paste

   if (m_iScan == pimage->m_iScan)
   {

      ::memcpy_dup(get_data(), pimage->get_data(), height() * m_iScan);

   }
   else
   {

      int iScan = minimum(m_iScan, pimage->m_iScan);

      for (int i = 0; i < height(); i++)
      {

         ::memcpy_dup(&((u8 *)get_data())[m_iScan * i], &((u8 *)pimage->get_data())[pimage->m_iScan * i], iScan);

      }

   }

   return true;

}


bool image::bitmap_blend(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle)
{

   return pgraphics->stretch(rectangle, get_graphics()) != false;


}


bool image::color_blend(color32_t cr, byte bAlpha)
{

   u8 *dst = (u8 *)get_data();

   i64 size = scan_area();

   u32 dwB = ::blue(cr);
   u32 dwG = ::green(cr);
   u32 dwR = ::red(cr);

   u32 dwB_ = dwB << 8;
   u32 dwG_ = dwG << 8;
   u32 dwR_ = dwR << 8;

   while (size--)
   {
      dst[0] = (byte)(((dst[0] - dwB)*bAlpha + dwB_) >> 8);
      dst[1] = (byte)(((dst[1] - dwG)*bAlpha + dwG_) >> 8);
      dst[2] = (byte)(((dst[2] - dwG)*bAlpha + dwR_) >> 8);
      dst += 4;
   }

   return true;

}


bool image::op(string str)
{

   if (str == "horz-__swap")
   {

      map();

      // half width
      int hx = width() / 2;
      // aligned scan
      int as = m_iScan / sizeof(color32_t);

      for (index i = 0; i < height(); i++)
      {
         for (index j = 0; j < hx; j++)
         {
            __swap(colorref()[i * as + j], colorref()[i * as + width() - j]);
         }
      }

      return true;
   }

   return false;

}


bool image::Blend(::image * pimage, i32 A)
{

   if (size() != pimage->size())
   {

      return false;

   }

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] = (byte)(((src[0] - dst[0])*A + (dst[0] << 8)) >> 8);
      dst[1] = (byte)(((src[1] - dst[1])*A + (dst[1] << 8)) >> 8);
      dst[2] = (byte)(((src[2] - dst[2])*A + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
   }

   return true;

}


bool image::Blend(::image *pDib, ::image *DibA, i32 A)
{
   if (size() != pDib->size() ||
         size() != DibA->size())
      return false;

   u8 *src = (u8 *)pDib->get_data();
   u8 *dst = (u8 *)get_data();
   u8 *alf = (u8 *)DibA->get_data();
   i64 size = scan_area();

   A = 2 - A;

   while (size--)
   {
      dst[0] = (byte)(((src[0] - dst[0])*alf[A] + (dst[0] << 8)) >> 8);
      dst[1] = (byte)(((src[1] - dst[1])*alf[A] + (dst[1] << 8)) >> 8);
      dst[2] = (byte)(((src[2] - dst[2])*alf[A] + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
      alf += 4;
   }

   return true;

}


bool image::Blend(::image *pDib, ::image *DibA)
{
   if (size() != pDib->size() ||
         size() != DibA->size())
      return false;

   map();
   pDib->map();
   DibA->map();

   u8 *src = (u8 *)pDib->get_data();
   u8 *dst = (u8 *)get_data();
   u8 *alf = ((u8 *)DibA->get_data()) + 3;
   i64 size = scan_area();

   while (size--)
   {
      dst[0] = (byte)(((src[0] - dst[0])* (*alf) + (dst[0] << 8)) >> 8);
      dst[1] = (byte)(((src[1] - dst[1])* (*alf) + (dst[1] << 8)) >> 8);
      dst[2] = (byte)(((src[2] - dst[2])* (*alf) + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
      alf += 4;
   }

   return true;

}



bool image::blend(::image * pimage, ::image * pimageRate)
{
   if (size() != pimage->size() ||
         size() != pimageRate->size())
      return false;

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   u8 *alf = (u8 *)pimageRate->get_data();
   i64 size = scan_area();

   while (size >= 2)
   {
      dst[00] = (byte)(((((i32)src[00] - (i32)dst[00]) * (i32)alf[00]) + (i32)dst[00] * (i32)255) / 255);
      dst[01] = (byte)(((((i32)src[01] - (i32)dst[01]) * (i32)alf[01]) + (i32)dst[01] * (i32)255) / 255);
      dst[02] = (byte)(((((i32)src[02] - (i32)dst[02]) * (i32)alf[02]) + (i32)dst[02] * (i32)255) / 255);
      dst[03] = (byte)(((((i32)src[03] - (i32)dst[03]) * (i32)alf[03]) + (i32)dst[03] * (i32)255) / 255);
      dst[04] = (byte)(((((i32)src[04] - (i32)dst[04]) * (i32)alf[04]) + (i32)dst[04] * (i32)255) / 255);
      dst[05] = (byte)(((((i32)src[05] - (i32)dst[05]) * (i32)alf[05]) + (i32)dst[05] * (i32)255) / 255);
      dst[06] = (byte)(((((i32)src[06] - (i32)dst[06]) * (i32)alf[06]) + (i32)dst[06] * (i32)255) / 255);
      dst[07] = (byte)(((((i32)src[07] - (i32)dst[07]) * (i32)alf[07]) + (i32)dst[07] * (i32)255) / 255);
      dst += 4 * 2;
      src += 4 * 2;
      alf += 4 * 2;
      size -= 2;
   }
   while (size > 0)
   {
      dst[00] = (byte)(((((i32)src[00] - (i32)dst[00]) * (i32)alf[00]) + (i32)dst[00] * (i32)255) / 255);
      dst[01] = (byte)(((((i32)src[01] - (i32)dst[01]) * (i32)alf[01]) + (i32)dst[01] * (i32)255) / 255);
      dst[02] = (byte)(((((i32)src[02] - (i32)dst[02]) * (i32)alf[02]) + (i32)dst[02] * (i32)255) / 255);
      dst[03] = (byte)(((((i32)src[03] - (i32)dst[03]) * (i32)alf[03]) + (i32)dst[03] * (i32)255) / 255);
      dst += 4;
      src += 4;
      alf += 4;
      size--;
   }

   return true;
}


bool image::Darken(::image * pimage)
{

   if (size() != pimage->size())
   {

      return false;

   }

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] = (byte)((src[0] < dst[0]) ? src[0] : dst[0]);
      dst[1] = (byte)((src[1] < dst[1]) ? src[1] : dst[1]);
      dst[2] = (byte)((src[2] < dst[2]) ? src[2] : dst[2]);
      dst += 4;
      src += 4;
   }

   return true;

}


bool image::Difference(::image * pimage)
{

   if (size() != pimage->size())
   {

      return false;

   }

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      i32 Difference;
      Difference = src[0] - dst[0];
      dst[0] = (byte)((Difference < 0) ? -Difference : Difference);
      Difference = src[1] - dst[1];
      dst[1] = (byte)((Difference < 0) ? -Difference : Difference);
      Difference = src[2] - dst[2];
      dst[2] = (byte)((Difference < 0) ? -Difference : Difference);
      dst += 4;
      src += 4;
   }

   return true;

}


bool image::Lighten(::image * pimage)
{

   if (size() != pimage->size())
   {

      return false;

   }

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] = (byte)((src[0] > dst[0]) ? src[0] : dst[0]);
      dst[1] = (byte)((src[1] > dst[1]) ? src[1] : dst[1]);
      dst[2] = (byte)((src[2] > dst[2]) ? src[2] : dst[2]);
      dst += 4;
      src += 4;
   }

   return true;

}


/// centered on 0.
/// > 0 lighter (safe)
/// < 0 darker (non safe)
bool image::lighten(double dRate)
{
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] += (byte) ((dst[3] - dst[0]) * dRate);
      dst[1] += (byte) ((dst[3] - dst[1]) * dRate);
      dst[2] += (byte) ((dst[3] - dst[2]) * dRate);
      dst += 4;
   }

   return true;

}


bool image::Multiply(::image * pimage)
{

   if (size() != pimage->size())
   {

      return false;

   }

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] = (byte)(((src[0])*(dst[0])) >> 8);
      dst[1] = (byte)(((src[1])*(dst[1])) >> 8);
      dst[2] = (byte)(((src[2])*(dst[2])) >> 8);
      dst += 4;
      src += 4;
   }

   return true;

}


bool image::Screen(::image * pimage)
{

   if (size() != pimage->size())
   {

      return false;

   }

   u8 *src = (u8 *)pimage->get_data();
   u8 *dst = (u8 *)get_data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] = (byte)(255 - (((255 - src[0])*(255 - dst[0])) >> 8));
      dst[1] = (byte)(255 - (((255 - src[1])*(255 - dst[1])) >> 8));
      dst[2] = (byte)(255 - (((255 - src[2])*(255 - dst[2])) >> 8));
      dst += 4;
      src += 4;
   }

   return true;

}


//////////////////////////////////////////////////////////////////////
// rectangle_i32 Functions
//////////////////////////////////////////////////////////////////////

bool image::copy_from(::image * pimage, i32 x, i32 y)
{

   ::size_i32 s(pimage->width() - x, pimage->height());

   if (size() != s)
   {

      if (!create(s))
      {

         return false;

      }

   }

   if (s.area() > 0)
   {

      if (!g()->draw(::rectangle_f64(s), pimage, ::point_f64(x, y)))
      {

         return false;

      }

   }

   return true;

}


bool image::copy_to(::image * pimage, i32 x, i32 y)
{

   return pimage->copy_from(this);

}


bool image::fill_rectangle(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B)
{

   i32 x = rectangle.left;

   i32 y = rectangle.top;

   i32 w = rectangle.width();

   i32 h = rectangle.height();

   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + w) < width()) ? w : width() - x;
   i32 dy = ((y + h) < height()) ? h : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Fill return
   if ((dx <= 0) || (dy <= 0))
   {

      return false;

   }

   map();

   color32_t *dst = get_data() + (py*width()) + px;

   while (dy--)
   {

      for (i32 i = 0; i < dx; i++)
      {

         ((u8 *)&dst[i])[0] = R;
         ((u8 *)&dst[i])[1] = G;
         ((u8 *)&dst[i])[2] = B;

      }

      dst += m_iScan / sizeof(color32_t);

   }

   return true;

}


bool image::fill_rectangle(const ::rectangle_i32 & rectangle, color32_t cr)

{

   if (m_bMapped)
   {

      i32 x = rectangle.left;

      i32 y = rectangle.top;

      i32 w = rectangle.width();

      i32 h = rectangle.height();

      // Clip Rect
      i32 px = x;
      if (w < 0)
      {
         px += w;
         w = -w;
      }

      px = (px >= 0) ? px : 0;
      i32 py = y;
      if (h < 0)
      {
         py += h;
         h = -h;
      }
      py = (py >= 0) ? py : 0;
      i32 dx;
      dx = ((px + w) < width()) ? w : width() - px;
      i32 dy;
      dy = ((py + h) < height()) ? h : height() - py;
      dx = (px >= 0) ? dx : dx + x;
      dy = (py >= 0) ? dy : dy + y;

      // If Nothing to Fill return
      if ((dx <= 0) || (dy <= 0))
         return false;

      // Prepare buffer Address
      color32_t *dst = get_data() + (py*width()) + px;

      while (dy--)
      {

         for (i32 i = 0; i < dx; i++)
         {

            dst[i] = cr;

         }

         dst += m_iScan / sizeof(color32_t);

      }

   }
   else
   {

      ::draw2d::enum_alpha_mode emodeOld = get_graphics()->m_ealphamode;

      if (get_graphics()->m_ealphamode != ::draw2d::alpha_mode_set)
      {

         get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      }

      get_graphics()->fill_rectangle(rectangle, cr);


      if (get_graphics()->m_ealphamode != emodeOld)
      {

         get_graphics()->set_alpha_mode(emodeOld);

      }

   }

   return true;

}


bool image::fill_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B, i32 A)

{

   i32 x = rectangle.left;

   i32 y = rectangle.top;

   i32 w = rectangle.width();

   i32 h = rectangle.height();


   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + w) < width()) ? w : width() - x;
   i32 dy = ((y + h) < height()) ? h : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to FillGlass return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Address
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do FillGlass
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[0] = (byte)(((B - dst[0])*A + (dst[0] << 8)) >> 8);
         dst[1] = (byte)(((G - dst[1])*A + (dst[1] << 8)) >> 8);
         dst[2] = (byte)(((R - dst[2])*A + (dst[2] << 8)) >> 8);
         dst += 4;
      }

      dst += (width() - dx) << 2;

   }

   return true;

}


bool image::fill_stippled_glass_rect(const ::rectangle_i32 & rectangle, i32 R, i32 G, i32 B)

{

   i32 x = rectangle.left;

   i32 y = rectangle.top;

   i32 w = rectangle.width();

   i32 h = rectangle.height();


   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + w) < width()) ? w : width() - x;
   i32 dy = ((y + h) < height()) ? h : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to FillStippledGlass return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Address
   color32_t *dst = get_data() + (py*width()) + px;
   color32_t color = rgb(B, G, R);

   // Do FillStippledGlass
   for (i32 j = 0; j < dy; j++)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[i] = ((i + j) & 0x1) ? dst[i] : color;
      }
      dst += width();
   }

   return true;

}

bool image::BlendRect(::image * pimage, i32 x, i32 y, i32 A)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 dy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Blend return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Addresses
   u8 *src = (u8 *)pimage->get_data() + (((py - y)*pimage->width()) + px - x) * 4;
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do Blend
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[0] = (byte)(((src[0] - dst[0])*A + (dst[0] << 8)) >> 8);
         dst[1] = (byte)(((src[1] - dst[1])*A + (dst[1] << 8)) >> 8);
         dst[2] = (byte)(((src[2] - dst[2])*A + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - dx) << 2;
      src += (pimage->width() - dx) << 2;
   }

   return true;

}


bool image::DarkenRect(::image * pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 dy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Darken return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Addresses
   u8 *src = (u8 *)pimage->get_data() + (((py - y)*pimage->width()) + px - x) * 4;
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do Darken
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[0] = (byte)((src[0] < dst[0]) ? src[0] : dst[0]);
         dst[1] = (byte)((src[1] < dst[1]) ? src[1] : dst[1]);
         dst[2] = (byte)((src[2] < dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - dx) << 2;
      src += (pimage->width() - dx) << 2;
   }

   return true;

}


bool image::DifferenceRect(::image * pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 dy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Difference return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Addresses
   u8 *src = (u8 *)pimage->get_data() + (((py - y)*pimage->width()) + px - x) * 4;
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do Difference
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         i32 Difference;
         Difference = src[0] - dst[0];
         dst[0] = (byte)((Difference < 0) ? -Difference : Difference);
         Difference = src[1] - dst[1];
         dst[1] = (byte)((Difference < 0) ? -Difference : Difference);
         Difference = src[2] - dst[2];
         dst[2] = (byte)((Difference < 0) ? -Difference : Difference);
         dst += 4;
         src += 4;
      }
      dst += (width() - dx) << 2;
      src += (pimage->width() - dx) << 2;
   }

   return true;

}


bool image::LightenRect(::image * pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 dy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Lighten return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Addresses
   u8 *src = (u8 *)pimage->get_data() + (((py - y)*pimage->width()) + px - x) * 4;
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do Lighten
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[0] = (byte)((src[0] > dst[0]) ? src[0] : dst[0]);
         dst[1] = (byte)((src[1] > dst[1]) ? src[1] : dst[1]);
         dst[2] = (byte)((src[2] > dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - dx) << 2;
      src += (pimage->width() - dx) << 2;
   }

   return true;

}


bool image::MultiplyRect(::image * pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 dy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Multiply return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Addresses
   u8 *src = (u8 *)pimage->get_data() + (((py - y)*pimage->width()) + px - x) * 4;
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do Multiply
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[0] = (byte)(((src[0])*(dst[0])) >> 8);
         dst[1] = (byte)(((src[1])*(dst[1])) >> 8);
         dst[2] = (byte)(((src[2])*(dst[2])) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - dx) << 2;
      src += (pimage->width() - dx) << 2;
   }

   return true;

}


bool image::ScreenRect(::image * pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 dx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 dy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   dx = (x >= 0) ? dx : dx + x;
   dy = (y >= 0) ? dy : dy + y;

   // If Nothing to Screen return
   if ((dx <= 0) || (dy <= 0))
      return false;

   // Prepare buffer Addresses
   u8 *src = (u8 *)pimage->get_data() + (((py - y)*pimage->width()) + px - x) * 4;
   u8 *dst = (u8 *)get_data() + ((py*width()) + px) * 4;

   // Do Screen
   while (dy--)
   {
      for (i32 i = 0; i < dx; i++)
      {
         dst[0] = (byte)(255 - (((255 - src[0])*(255 - dst[0])) >> 8));
         dst[1] = (byte)(255 - (((255 - src[1])*(255 - dst[1])) >> 8));
         dst[2] = (byte)(255 - (((255 - src[2])*(255 - dst[2])) >> 8));
         dst += 4;
         src += 4;
      }
      dst += (width() - dx) << 2;
      src += (pimage->width() - dx) << 2;
   }

   return true;

}


//////////////////////////////////////////////////////////////////////
// Line Functions
//////////////////////////////////////////////////////////////////////

/*bool image::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
{
i32 dx, dy, k1, k2, d, x, y;
color32_t color=rgb ( B, G, R );

dx=x2-x1;
dy=y2-y1;
d=(dy<<1)-dx;
k1=dy<<1;
k2=(dy-dx)<<1;
x=x1;
y=y1;

get_data()[y*width()+x]=color;
while (x<dx)
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
get_data()[y*width()+x]=color;
}
}*/


bool image::horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A, i32 x1, i32 x2)
{
   map();
   if (width() == 0)
      return false;
   x1 %= width();
   x2 %= width();
   if (x2 < 0)
      x2 += width();
   if (x1 < 0)
      x1 += width();
   color32_t color = rgb(B, G, R) | (A << 24);

#ifdef __APPLE__

   color32_t * pdata = get_data() + (height() - y - 1) * (m_iScan / sizeof(color32_t));

#else

   color32_t * pdata = get_data() + y * (m_iScan / sizeof(color32_t));

#endif

   for (i32 x = x1; x <= x2; x++)
   {

      *pdata = color;

      pdata++;

   }

   return true;

}


bool image::Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B)
{
   i32 d, x, y, aura, ay, sx, sy, dx, dy;
   color32_t color = rgb(B, G, R);

   dx = x2 - x1;
   aura = abs(dx) << 1;
   sx = (dx < 0) ? -1 : 1;
   dy = y2 - y1;
   ay = abs(dy) << 1;
   sy = (dy < 0) ? -1 : 1;
   x = x1;
   y = y1;

   if (aura > ay)
   {
      d = ay - (aura >> 1);
      while (x != x2)
      {
         get_data()[y*(m_iScan / sizeof(color32_t)) + x] = color;
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
         get_data()[y*(m_iScan / sizeof(color32_t)) + x] = color;
         if (d >= 0)
         {
            x += sx;
            d -= ay;
         }
         y += sy;
         d += aura;
      }
   }

   return true;

}


bool image::LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A)
{
   i32 d, x, y, aura, ay, sx, sy, dx, dy;
   //      color32_t color=rgb ( B, G, R );
   u8 *dst = (u8 *)get_data();

   dx = x2 - x1;
   aura = abs(dx) << 1;
   sx = (dx < 0) ? -1 : 1;
   dy = y2 - y1;
   ay = abs(dy) << 1;
   sy = (dy < 0) ? -1 : 1;
   x = x1;
   y = y1;

   if (aura > ay)
   {
      d = ay - (aura >> 1);
      while (x != x2)
      {
         dst[(y*(m_iScan / sizeof(color32_t)) + x) << 2] = (byte)(((B - dst[(y*(m_iScan / sizeof(color32_t)) + x) << 2])*A + (dst[(y*(m_iScan / sizeof(color32_t)) + x) << 2] << 8)) >> 8);
         dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 1] = (byte)(((G - dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 1])*A + (dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 1] << 8)) >> 8);
         dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 2] = (byte)(((R - dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 2])*A + (dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 2] << 8)) >> 8);
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
         dst[(y*(m_iScan / sizeof(color32_t)) + x) << 2] = (byte)(((B - dst[(y*(m_iScan / sizeof(color32_t)) + x) << 2])*A + (dst[(y*(m_iScan / sizeof(color32_t)) + x) << 2] << 8)) >> 8);
         dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 1] = (byte)(((G - dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 1])*A + (dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 1] << 8)) >> 8);
         dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 2] = (byte)(((R - dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 2])*A + (dst[((y*(m_iScan / sizeof(color32_t)) + x) << 2) + 2] << 8)) >> 8);
         if (d >= 0)
         {
            x += sx;
            d -= ay;
         }
         y += sy;
         d += aura;
      }
   }

   return true;

}


bool image::Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask)
{
   color32_t crFind = rgb(::blue(crMask), ::green(crMask), ::red(crMask));
   color32_t crSet = rgb(::blue(crInMask), ::green(crInMask), ::red(crInMask));
   color32_t crUnset = rgb(::blue(crOutMask), ::green(crOutMask), ::red(crOutMask));

   i64 size = scan_area();

   for (i32 i = 0; i < size; i++)
      if (get_data()[i] == crFind)
         get_data()[i] = crSet;
      else
         get_data()[i] = crUnset;

   return true;

}


bool image::transparent_color(::color::color color)
{
   color32_t crFind = color.get_rgb();
   i64 iSize = scan_area();

   for (i32 i = 0; i < iSize; i++)
      if ((get_data()[i] & 0x00ffffff) == crFind)
         ((byte *)&get_data()[i])[3] = 255;
      else
         ((byte *)&get_data()[i])[3] = 0;

   return true;

}


bool image::channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, ::color::enum_channel echannel)
{

   i32 size = (m_iScan / sizeof(color32_t)) * height();

   uchar * puch = (uchar *)get_data();

   puch += ((i32)echannel) % 4;

   for (i32 i = 0; i < size; i++)
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

   return true;

}

u32 image::GetPixel(i32 x, i32 y)
{

   map();

   u32 u = *(get_data() + x + line(y) * (m_iScan / sizeof(color32_t)));

   u8 * p = (u8 *) &u;

   int iA = p[IMAGE_A_BYTE_INDEX];

   if (iA == 0)
   {

      return rgb(p[IMAGE_R_BYTE_INDEX], p[IMAGE_G_BYTE_INDEX], p[IMAGE_B_BYTE_INDEX]);

   }
   else
   {

      return argb(iA, p[IMAGE_R_BYTE_INDEX] * 255 / iA, p[IMAGE_G_BYTE_INDEX] * 255 / iA, p[IMAGE_B_BYTE_INDEX] * 255 / iA);

   }

}


// too slow for animation on AMD XP gen_hon.
// TOP SUGGESTION:
// The gradient can´t have more then 256 levels of the most bright color
// (white). So creating a radial fill of radius 256 and then using fasting
// stretching algorithms is much faster than calculating radial fill.
bool image::RadialFill(byte alpha, byte red, byte green, byte blue, i32 xCenter, i32 yCenter, i32 iRadius)
{

   if (iRadius == 0)
   {

      return false;

   }

   /*if(version == 0)
   {

   i32 iR = iRadius - 1;

   i32 xL = xCenter - iR;
   i32 xU = xCenter + iR;
   i32 yL = yCenter - iR;
   i32 yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(color32_t))) xU = m_Size.(m_iScan / sizeof(color32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   u8 *dst = ((u8 *)(get_data() + xL + yL * m_Size.(m_iScan / sizeof(color32_t))));
   u32 dwAdd = ((m_Size.(m_iScan / sizeof(color32_t)) - 1 - xU) + xL) * 4;
   i32 size=m_Size.(m_iScan / sizeof(color32_t))*m_Size.height();
   double iLevel;

   i32 dx, dy;
   i32 dx0, dy0;
   i32 dx1, dy1;
   i32 dx2, dy2;
   i32 dx3, dy3;
   i32 dx4, dy4;
   i32 dx5, dy5;
   i32 dx6, dy6;
   i32 dx7, dy7;
   i32 dx8, dy8;
   i32 dx9, dy9;
   i32 dxA, dyA;
   i32 dxB, dyB;
   i32 dxC, dyC;
   i32 dxD, dyD;
   i32 dxE, dyE;
   i32 dxF, dyF;

   unsigned long dr;
   unsigned long dq;
   unsigned long dr0, dq0;
   unsigned long dr1, dq1;
   unsigned long dr2, dq2;
   unsigned long dr3, dq3;
   unsigned long dr4, dq4;
   unsigned long dr5, dq5;
   unsigned long dr6, dq6;
   unsigned long dr7, dq7;
   unsigned long dr8, dq8;
   unsigned long dr9, dq9;
   unsigned long drA, dqA;
   unsigned long drB, dqB;
   unsigned long drC, dqC;
   unsigned long drD, dqD;
   unsigned long drE, dqE;
   unsigned long drF, dqF;
   i32 x, y;

   {
   for(y = yL; y <= yU; y++)
   {
   for(x = xL; x <= xU; x++)
   {
   dx = abs(x - xCenter);
   dy = abs(y - yCenter);
   isqrt((dx * dx) + (dy * dy), &dr, &dq);
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

      byte * pbAlloc = (byte *)malloc(iRadius * iRadius);

      byte * pb = pbAlloc;



      i32 x, y;
      i32 b;

      //         i32 r2 = iRadius * iRadius;

      for (y = 0; y < iRadius; y++)
      {
         for (x = y; x < iRadius; x++)
         {
            b = (i32)(sqrt((double)(x * x) + (y * y)) * 255 / iRadius);
            if (b > 255)
               b = 0;
            else
               b = 255 - b;


            pb[x + y * iRadius] = (byte)b;

            pb[y + x * iRadius] = (byte)b;

         }
      }


      i32 iR = iRadius - 1;

      i32 xL = xCenter - iR;
      i32 xU = xCenter + iR;
      i32 yL = yCenter - iR;
      i32 yU = yCenter + iR;


      if (xL < 0) xL = 0;
      if (xU >= width()) xU = width() - 1;
      if (yL < 0) yL = 0;
      if (yU >= height()) yU = height() - 1;


      u8 *dst = ((u8 *)(get_data() + xL + yL * (m_iScan / sizeof(color32_t))));
      u32 dwAdd = (((m_iScan / sizeof(color32_t)) - 1 - xU) + xL) * 4;
      //         i64 size = area();

      i32 dx, dy;

      // Top Left

      for (y = yL; y <= yU; y++)
      {
         for (x = xL; x <= xU; x++)
         {
            dx = abs(x - xCenter);
            dy = abs(y - yCenter);
            b = pb[dx + dy * iRadius];

            dst[0] = byte(blue     * b / 255);
            dst[1] = byte(green    * b / 255);
            dst[2] = byte(red      * b / 255);
            dst[3] = byte(alpha    * b / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

      free(pbAlloc);

   }

   return true;

}


bool image::RadialFill(
byte alpha1, byte red1, byte green1, byte blue1,
byte alpha2, byte red2, byte green2, byte blue2,
i32 xCenter, i32 yCenter, i32 iRadius)
{
   if (iRadius == 0)
      return false;

   map();
   /*if(version == 0)
   {

   i32 iR = iRadius - 1;

   i32 xL = xCenter - iR;
   i32 xU = xCenter + iR;
   i32 yL = yCenter - iR;
   i32 yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(color32_t))) xU = m_Size.(m_iScan / sizeof(color32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   u8 *dst = ((u8 *)(get_data() + xL + yL * m_Size.(m_iScan / sizeof(color32_t))));
   u32 dwAdd = ((m_Size.(m_iScan / sizeof(color32_t)) - 1 - xU) + xL) * 4;
   i32 size=m_Size.(m_iScan / sizeof(color32_t))*m_Size.height();
   double iLevel;

   i32 dx, dy;
   i32 dx0, dy0;
   i32 dx1, dy1;
   i32 dx2, dy2;
   i32 dx3, dy3;
   i32 dx4, dy4;
   i32 dx5, dy5;
   i32 dx6, dy6;
   i32 dx7, dy7;
   i32 dx8, dy8;
   i32 dx9, dy9;
   i32 dxA, dyA;
   i32 dxB, dyB;
   i32 dxC, dyC;
   i32 dxD, dyD;
   i32 dxE, dyE;
   i32 dxF, dyF;

   unsigned long dr;
   unsigned long dq;
   unsigned long dr0, dq0;
   unsigned long dr1, dq1;
   unsigned long dr2, dq2;
   unsigned long dr3, dq3;
   unsigned long dr4, dq4;
   unsigned long dr5, dq5;
   unsigned long dr6, dq6;
   unsigned long dr7, dq7;
   unsigned long dr8, dq8;
   unsigned long dr9, dq9;
   unsigned long drA, dqA;
   unsigned long drB, dqB;
   unsigned long drC, dqC;
   unsigned long drD, dqD;
   unsigned long drE, dqE;
   unsigned long drF, dqF;
   i32 x, y;

   {
   for(y = yL; y <= yU; y++)
   {
   for(x = xL; x <= xU; x++)
   {
   dx = abs(x - xCenter);
   dy = abs(y - yCenter);
   isqrt((dx * dx) + (dy * dy), &dr, &dq);
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
      //         byte * pbAlloc = mem.get_data();

      //
      //         byte * pb = pbAlloc;

      //
      //
      //         i32 x, y;
      //         i32 b;
      //
      ////         i32 r2 = iRadius * iRadius;
      //
      //         for(y = 0; y < iRadius; y++)
      //         {
      //            for(x = y; x < iRadius; x++)
      //            {
      //
      //               b = (i32) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
      //
      //               if(b > 255)
      //                  b = 255;
      //
      //
      //               pb[x + y * iRadius] = (byte) b;

      //               pb[y + x * iRadius] = (byte) b;

      //            }
      //         }


      i32 iR = iRadius;

      i32 xL = xCenter - iR;
      i32 xU = xCenter + iR;
      i32 yL = yCenter - iR;
      i32 yU = yCenter + iR;


      if (xL < 0) xL = 0;
      if (xU > width()) xU = width();
      if (yL < 0) yL = 0;
      if (yU > height()) yU = height();


      u8 *dst = ((u8 *)(get_data() + xL + yL * (m_iScan / sizeof(color32_t))));
      u32 dwAdd = (((m_iScan / sizeof(color32_t)) - xU) + xL) * 4;
      //         i64 size = area();

      double dx, dy;

      double dRadius = 255.0 / (double)iRadius;

      byte bComp;

      int b;

      // Top Left

      int y;
      int x;

      for (y = yL; y < yU; y++)
      {
         for (x = xL; x < xU; x++)
         {
            dx = abs(x - xCenter);
            dy = abs(y - yCenter);
            b = (int)(sqrt((dx * dx) + (dy * dy)) * dRadius);

            if (b > 255)
            {
               b = 255;
            }

            bComp = 255 - b;
            dst[0] = byte(((blue1  * bComp) + (blue2  * b)) / 255);
            dst[1] = byte(((green1 * bComp) + (green2 * b)) / 255);
            dst[2] = byte(((red1   * bComp) + (red2   * b)) / 255);
            dst[3] = byte(((alpha1 * bComp) + (alpha2 * b)) / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

   }

   return true;

}



::e_status image::SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy)
{

//      __throw(todo);
//
//      // xxx todo create(width(), height());
//
//      if (width() <= 0 || height() <= 0)
//         return;
//
//
//
//
//      // White blend image_impl
//      image_impl pimage1;
//
//      __throw(todo);
//
//      // xxx todo pimage1->create(width(), height());
//
//      pimage1->Fill(0, 255, 255, 255);
//
//#ifdef _UWP
//
//      ::exception::throw_not_implemented();
//
//#else
//
//      pimage1->get_graphics()->DrawIcon(
//         0, 0,
//         picon,
//         width(), height(),
//         0,
//         nullptr,
//         DI_IMAGE | DI_MASK);
//
//#endif
//
//      // Black blend image_impl
//      image_impl pimage2;
//
//
//      __throw(todo);
//
//      // xxx todo pimage2->create(width(), height());
//      pimage2->Fill(0, 0, 0, 0);
//
//#ifdef _UWP
//
//      ::exception::throw_not_implemented();
//
//#else
//
//      pimage2->get_graphics()->DrawIcon(
//         0, 0,
//         picon,
//         width(), height(),
//         0,
//         nullptr,
//         DI_IMAGE | DI_MASK);
//
//#endif
//
//      // Mask image_impl
//      image_impl imageM;
//      __throw(todo);
//
//      // xxx todo imageM.create(width(), height());
//
//#ifdef _UWP
//
//      ::exception::throw_not_implemented();
//
//#else
//
//      imageM.get_graphics()->DrawIcon(
//         0, 0,
//         picon,
//         width(), height(),
//         0,
//         nullptr,
//         DI_MASK);
//
//#endif
//
//      u8 * r1 = (u8 *)pimage1->get_data();
//      u8 * r2 = (u8 *)pimage2->get_data();
//      u8 * srcM = (u8 *)imageM.get_data();
//      u8 * dest = (u8 *)get_data();
//      i32 iSize = width()*height();
//
//      byte b;
//      byte bMax;
//      while (iSize-- > 0)
//      {
//         if (srcM[0] == 255)
//         {
//            bMax = 0;
//         }
//         else
//         {
//            bMax = 0;
//            b = (byte)(r1[0] - r2[0]);
//            bMax = maximum(b, bMax);
//            b = (byte)(r1[1] - r2[1]);
//            bMax = maximum(b, bMax);
//            b = (byte)(r1[2] - r2[2]);
//            bMax = maximum(b, bMax);
//            bMax = 255 - bMax;
//         }
//         dest[0] = bMax;
//         dest[1] = bMax;
//         dest[2] = bMax;
//         dest += 4;
//         srcM += 4;
//         r1 += 4;
//         r2 += 4;
//      }
//

   return true;

}


bool image::rotate(::image * pimage, double dAngle)
{

   double o = dAngle * pi() / 180.0;

   int a = (int)(::fabs((double)pimage->width() * ::sin(o)) + ::fabs((double)pimage->height() * ::cos(o)));

   int b = (int)(::fabs((double)pimage->width() * ::cos(o)) + ::fabs((double)pimage->height() * ::sin(o)));

   if (!create({ b, a }))
   {

      return false;

   }

   rotate(pimage, dAngle, 1.0);

   return true;

}


bool image::rotate(::image * pimage, double dAngle, double dScale)
{

   map();

   pimage->map();

   int wSource = pimage->width();

   int hSource = pimage->height();

   auto pdataSource = pimage->colorref();

   int wTarget = width();

   int hTarget = height();

   auto pdataTarget = colorref();

   if (wSource < 2 || hSource < 2 || ::is_null(pdataSource)) return false;

   if (wTarget < 2 || hTarget < 2 || ::is_null(pdataTarget)) return false;

   i32 l = maximum(wTarget, hTarget);

   i32 jmax = minimum(l, hTarget / 2);

   i32 jmin = -jmax;

   i32 imax = minimum(l, wTarget / 2);

   i32 imin = -imax;

   int xoff = wSource / 2;

   int yoff = hSource / 2;

   double o = dAngle * pi() / 180.0;

   int ioff = wTarget / 2;

   int joff = hTarget / 2;

   int dsw = m_iScan / sizeof(color32_t);

   int ssw = pimage->m_iScan / sizeof(color32_t);

   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;

   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;

   int x;

   int y;

   for (i32 j = jmin; j < jmax; j++)
   {

      for (i32 i = imin; i < imax; i++)
      {

         x = (i32)fabs((dCos * i - dSin * j) + xoff);

         y = (i32)fabs((dSin * i + dCos * j) + yoff);

         x %= wSource;

         y %= hSource;

         pdataTarget[(j + joff) * dsw + (i + ioff)] = pdataSource[y * ssw + x];

      }

   }

   return true;

}


bool image::Rotate034(::image * pimage, double dAngle, double dScale)
{

   map();
   pimage->map();

   auto hdst = height();
   auto wdst = width();

   auto hsrc = pimage->height();
   auto wsrc = pimage->width();

   if (hdst != hsrc)
   {

      output_debug_string("different height");

   }

   if (wdst != wsrc)
   {

      output_debug_string("different width");

   }

   auto hdstmid = hdst / 2.0;
   auto wdstmid = wdst / 2.0;

   i32 ihdstmid = (::i32) hdstmid;

   auto hsrcmid = hsrc / 2.0;
   auto wsrcmid = wsrc / 2.0;

   //i32 l = maximum(w, h);

   i32 jdstmin = (::i32) -hdstmid;
   i32 jdstmax = jdstmin + hdst;
   i32 idstmin = (::i32)-wdstmid;
   i32 idstmax = idstmin + wdst;

   i32 k = 0;
   
   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
   
   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;

   auto pdataSrc = pimage->get_data();

   auto pdataDst = get_data();

   int strideSrc = pimage->m_iScan / sizeof(color32_t);

   int strideDst = m_iScan / sizeof(color32_t);

   for (i32 jdst = jdstmin; jdst < jdstmax; jdst++)
   {

      int lineDst = (i32)(jdst + ihdstmid);

      if (lineDst < 0)
      {

         output_debug_string("test");

      }

      color32_t * pline = pdataDst + (lineDst * strideDst);
      
      for (i32 idst = idstmin; idst < idstmax; idst++)
      {

         i32 xsrc, ysrc;

         double dj = jdst;
         double di = idst;

         xsrc = (i32)((dCos * di - dSin * dj) + wsrcmid);
         ysrc = (i32)((dSin * di + dCos * dj) + hsrcmid);

         color32_t colorSrc = 0xff000000;

         if(xsrc >= 0 && xsrc < wsrc && ysrc >= 0 && ysrc < hsrc)
         {

            colorSrc = pdataSrc[ysrc * strideSrc + xsrc];

         }

         *pline = colorSrc;

         pline++;

      }

   }

   return true;

}


bool image::rotate(::image * pimage, const ::rectangle_i32 & rectangle, double dAngle, double dScale)

{

   i32 l = maximum(width(), height());

   i32 jmax = minimum(l, height() / 2);
   i32 jmin = -jmax;
   i32 imax = minimum(l, width() / 2);
   i32 imin = -imax;

   i32 joff = height() / 2 + rectangle.left;

   i32 ioff = width() / 2 + rectangle.top;

   int stride_unit = m_iScan / sizeof(color32_t);
   //i32 iAngle = iStep % 360;
   //i32 iAngle = iStep;
   //i32 iAngle = 1;
   //i32 k = 0;

   /*     for ( i32 j=jmin; j<jmax; j++ )
   {
   for ( i32 i=imin; i<imax; i++ )
   {
   i32 x, y;

   // A Combination of a 2d Translation/rotation/Scale Matrix
   x=i32(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
   y=i32(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
   get_data()[(j+joff)*width()+(i+ioff)]=
   pimage->get_data()[abs(y%height())*width()+abs(x%width())];
   //k++;
   }
   (j+joff)*width()+(i+ioff)
   }*/

   i32 k = 0;
   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
   i32 cx1 = width() - 1;
   i32 cy1 = height() - 1;
   for (i32 j = jmin; j < jmax; j++)
   {
      for (i32 i = imin; i < imax; i++)
      {
         i32 x, y;

         // A Combination of a 2d Translation/rotation/Scale Matrix
         //x=abs((i32(dCos * i - dSin * j) + ioff) % width());
         //y=abs((i32(dSin * i + dCos * j) + joff) % height());

         x = (i32)fabs((dCos * i - dSin * j) + ioff);
         y = (i32)fabs((dSin * i + dCos * j) + joff);

         if ((x / width()) % 2 == 0)
         {
            x %= width();
         }
         else
         {
            x = cx1 - (x % width());
         }

         if ((y / height()) % 2 == 0)
         {
            y %= height();
         }
         else
         {
            y = cy1 - (y % height());
         }

         get_data()[(j + joff)*stride_unit + (i + ioff)] =  pimage->get_data()[y * stride_unit + x];

         k++;

      }

   }

   return true;

}


bool image::rotate90(::image * pimage)
{

   if (!create({ pimage->height(), pimage->width() }))
   {

      return false;

   }

   map();

   pimage->map();

   i32 cx = pimage->width();

   i32 cy = pimage->height();

   int s = m_iScan / sizeof(color32_t);

   int srcS = pimage->m_iScan / sizeof(color32_t);

   for (i32 i = 0; i < cx; i++)
   {

      for (i32 j = 0; j < cy; j++)
      {

         colorref()[i * s + j] = pimage->colorref()[(cy - j - 1) * srcS + i];

      }

   }

   return true;

}


bool image::rotate180(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   map();

   pimage->map();

   i32 cx = width();

   i32 cy = height();

   int s = m_iScan / sizeof(color32_t);

   int srcS = pimage->m_iScan / sizeof(color32_t);

   for (i32 i = 0; i < cy; i++)
   {

      for (i32 j = 0; j < cx; j++)
      {

         colorref()[(cy - i - 1) * s + (cx - j - 1)] = pimage->colorref()[i * srcS + j];

      }

   }

   return true;

}


bool image::rotate270(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   map();

   pimage->map();

   i32 cx = pimage->width();

   i32 cy = pimage->height();

   int s = m_iScan / sizeof(color32_t);

   int srcS = pimage->m_iScan / sizeof(color32_t);

   for (i32 i = 0; i < cx; i++)
   {

      for (i32 j = 0; j < cy; j++)
      {

         colorref()[i * s + j] = pimage->colorref()[j * srcS + (cx - i - 1)];

      }

   }

   return true;

}


bool image::rotate90()
{

   ::image_pointer pimage = clone();

   return rotate90(pimage);

}


bool image::rotate180()
{

   ::image_pointer pimage = clone();

   return rotate180(pimage);

}


bool image::rotate270()
{

   ::image_pointer pimage = clone();

   return rotate270(pimage);

}


bool image::rotate90flipx(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   map();

   pimage->map();

   i32 cx = pimage->width();

   i32 cy = pimage->height();

   int s = m_iScan / sizeof(color32_t);

   int srcS = pimage->m_iScan / sizeof(color32_t);

   for (i32 i = 0; i < cx; i++)
   {

      for (i32 j = 0; j < cy; j++)
      {

         colorref()[i * s + j] = pimage->colorref()[j * srcS + i];

      }

   }

   return true;

}


bool image::rotate180flipx(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   map();

   pimage->map();

   i32 cx = width();

   i32 cy = height();

   int s = m_iScan / sizeof(color32_t);

   int srcS = pimage->m_iScan / sizeof(color32_t);

   for (i32 i = 0; i < cy; i++)
   {

      for (i32 j = 0; j < cx; j++)
      {

         colorref()[i * s + j] = pimage->colorref()[(cy - i - 1) * srcS + j];

      }

   }

   return true;

}


bool image::rotate270flipx(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   map();

   pimage->map();

   i32 cx = pimage->width();

   i32 cy = pimage->height();

   int s = m_iScan / sizeof(color32_t);

   int srcS = pimage->m_iScan / sizeof(color32_t);

   for (i32 i = 0; i < cx; i++)
   {

      for (i32 j = 0; j < cy; j++)
      {

         colorref()[i * s + j] = pimage->colorref()[(cy - j - 1) * srcS + (cx - i - 1)];

      }

   }

   return true;

}


bool image::rotate90flipx()
{

   ::image_pointer pimage = clone();

   return rotate90flipx(pimage);

}


bool image::rotate180flipx()
{

   ::image_pointer pimage = clone();

   return rotate180flipx(pimage);

}


bool image::rotate270flipx()
{

   ::image_pointer pimage = clone();

   return rotate270flipx(pimage);

}


bool image::fill_byte(uchar uch)
{
   
   if(m_bMapped)
   {

      if (area() <= 0 || get_data() == nullptr)
      {

         return false;

      }

      int iScan = m_iScan;

      int iHeight = get_size().cy;

      if (iScan <= 0 || iHeight <= 0)
      {

         return false;

      }

      __memset(get_data(), uch, (memsize)(iScan * iHeight));
      
   }
   else if(g())
   {
   
      auto color = __acolor(uch, uch, uch, uch);
      
      auto ealphamode = g()->m_ealphamode;
      
      if(ealphamode != ::draw2d::alpha_mode_set)
      {
      
         g()->set_alpha_mode(::draw2d::alpha_mode_set);
         
      }
      
      g()->fill_rectangle(::rectangle_f64(m_size), color);
      
      if(ealphamode != ::draw2d::alpha_mode_set)
      {
         
         g()->set_alpha_mode(ealphamode);
         
      }
   
   }

   return true;

}


bool image::fill(color32_t cr)
{

   if (m_bMapped)
   {

      i64 size = scan_area();

      byte a = colorref_get_a_value(cr);
      byte r = colorref_get_r_value(cr);
      byte g = colorref_get_g_value(cr);
      byte b = colorref_get_b_value(cr);

      r = r * a / 255;

      g = g * a / 255;

      b = b * a / 255;

      if (a == r && a == g && a == b)
      {

         __memset(colorref(), a, m_iScan * height());

         return true;

      }

      cr = IMAGE_ARGB(a, r, g, b);

      color32_t * pcr = colorref();

      for (i64 i = 0; i < size; i++)
      {

         pcr[i] = cr;

      }

   }
   else if(get_graphics() != nullptr)
   {

      get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      get_graphics()->fill_rectangle(rectangle(), cr);

   }

   return true;

}




bool image::fill(i32 a, i32 r, i32 g, i32 b)
{

   if (a == r && a == g && a == b)
   {

      fill_byte(a);

   }
   else
   {

      color32_t color = make_colorref(a, r, g, b);

      fill(color);

   }

   return true;

}


color32_t image::GetAverageColor()
{

   map();

   i64 iRLine;

   i64 iGLine;

   i64 iBLine;

   i64 iDiv = width() * height();

   if (iDiv > 0)
   {

      iRLine = 0;

      iGLine = 0;

      iBLine = 0;

      for (i32 y = 0; y < height(); y++)
      {

         byte * pb = ((byte *)get_data()) + m_iScan * y;


         for (i32 x = 0; x < width(); x++)
         {

            iRLine += pb[2];


            iGLine += pb[1];


            iBLine += pb[0];


            pb += 4;


         }

      }

      i32 iR = (i32)(iRLine / iDiv);

      i32 iG = (i32)(iGLine / iDiv);

      i32 iB = (i32)(iBLine / iDiv);

      return rgb(iR, iG, iB);

   }
   else
   {

      return 0;

   }

}


color32_t image::GetAverageOpaqueColor()
{
   map();
   double dR = 0.0;
   double dG = 0.0;
   double dB = 0.0;
   i32 iRLine;
   i32 iGLine;
   i32 iBLine;
   double dDiv = width() * height();
   if (dDiv > 0)
   {

      for (i32 y = 0; y < height(); y++)
      {
         iRLine = 0;
         iGLine = 0;
         iBLine = 0;
         byte * pb = ((byte *)get_data()) + m_iScan * y;

         for (i32 x = 0; x < width(); x++)
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
      i32 iR = (i32)dR;
      i32 iG = (i32)dG;
      i32 iB = (i32)dB;
      return rgb(iR, iG, iB);
   }
   else
   {
      return 0;
   }

}


bool image::do_xor(::image * pimage)
{

   if (width() != pimage->width()
         || height() != pimage->height())
   {

      return false;

   }

   i32 iCount = width() * height();
   ::u32* pd1 = (::u32*)get_data();

   ::u32* pd2 = (::u32 *)pimage->get_data();

   for (i32 i = 0; i < iCount; i++)
   {
      *pd1 = *pd1 ^ *pd2;

      pd1++;

      pd2++;

   }

   return true;

}


bool image::create_frame(const ::size_i32 & size, i32 iFrameCount)
{

   i32 iSliceCount = (i32)sqrt((double)iFrameCount);

   return create(size /iSliceCount);

}


bool image::set_frame1(void * pdata, i32 iFrame, i32 iFrameCount)

{
   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   color32_t * pdst = &get_data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   color32_t * psrc = (color32_t *)pdata;

   color32_t * pdstline;

   for (i32 y = 0; y < iFrameHeight; y++)
   {
      pdstline = &pdst[y * width()];

      for (i32 x = 0; x < iFrameWidth; x++)
      {
         *pdstline = *psrc;

         pdstline++;

         psrc++;

      }
   }

   return true;

}


bool image::set_frame2(void * pdata, i32 iFrame, i32 iFrameCount)

{

   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   color32_t * pdst = &get_data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   color32_t * psrc = (color32_t *)pdata;

   color32_t * pdstline;

   for (i32 y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (i32 x = 0; x < iFrameWidth; x++)
      {
         *pdstline = *psrc;

         pdstline++;

         psrc++;

      }
   }

   return true;

}


bool image::xor_image_frame2(void * pdata, i32 iFrame, i32 iFrameCount)

{
   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   color32_t * pdst = &get_data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   color32_t * psrc = (color32_t *)pdata;

   color32_t * pdstline;

   for (i32 y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (i32 x = 0; x < iFrameWidth; x++)
      {
         *pdstline ^= *psrc;

         pdstline++;

         psrc++;

      }
   }

   return true;

}


bool image::get_frame(void * pdata, i32 iFrame, i32 iFrameCount)

{
   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   color32_t * psrc = &get_data()[iFrameWidth * iX + iY * iFrameHeight *  width()];

   color32_t * pdst = (color32_t *)pdata;

   color32_t * psrcline;

   for (i32 y = 0; y < iFrameHeight; y++)
   {
      psrcline = &psrc[y * width()];

      for (i32 x = 0; x < iFrameWidth; x++)
      {
         *pdst = *psrcline;

         pdst++;

         psrcline++;

      }
   }

   return true;

}


bool image::is_rgb_black()
{
   
   i32 iSize = width() * height();
   
   color32_t * p = get_data();

   for (i32 i = 0; i < iSize; i++)
   {

      if ((*p & 0x00FFFFFF) != 0)
      {

         return false;

      }

      p++;

   }

   return true;

}


bool image::DivideRGB(i32 iDivide)
{

   if (iDivide == 0)
   {

      return false;

   }

   i32 iCount = width() * height();

   byte * p = ((byte *)get_data());

   i32 i = 0;
   
   i32 iCount1 = iCount - iCount % 8;

   for (; i < iCount1; i++)
   {
      
      p[0] /= (byte)iDivide;

      p[1] /= (byte)iDivide;

      p[2] /= (byte)iDivide;


      p[4] /= (byte)iDivide;

      p[5] /= (byte)iDivide;

      p[6] /= (byte)iDivide;


      p[8] /= (byte)iDivide;

      p[9] /= (byte)iDivide;

      p[10] /= (byte)iDivide;


      p[12] /= (byte)iDivide;

      p[13] /= (byte)iDivide;

      p[14] /= (byte)iDivide;


      p[16] /= (byte)iDivide;

      p[17] /= (byte)iDivide;

      p[28] /= (byte)iDivide;


      p[20] /= (byte)iDivide;

      p[21] /= (byte)iDivide;

      p[22] /= (byte)iDivide;


      p[24] /= (byte)iDivide;

      p[25] /= (byte)iDivide;

      p[26] /= (byte)iDivide;


      p[28] /= (byte)iDivide;

      p[29] /= (byte)iDivide;

      p[30] /= (byte)iDivide;


      p += 4 * 8;

   }
   for (; i < iCount; i++)
   {
      p[0] /= (byte)iDivide;

      p[1] /= (byte)iDivide;

      p[2] /= (byte)iDivide;

      p += 4;

   }

   return true;

}


bool image::DivideARGB(i32 iDivide)
{

   if (iDivide == 0)
   {

      return false;

   }

   i32 iCount = width() * height();

   byte * p = ((byte *)get_data());

   for (i32 i = 0; i < iCount; i++)
   {
      p[0] /= (byte)iDivide;

      p[1] /= (byte)iDivide;

      p[2] /= (byte)iDivide;

      p[3] /= (byte)iDivide;

      p += 4;

   }

   return true;

}


bool image::DivideA(i32 iDivide)
{

   if (iDivide == 0)
   {

      return false;

   }

   i32 iCount = width() * height();

   byte * p = ((byte *)get_data());

   for (i32 i = 0; i < iCount; i++)
   {
      p[3] /= (byte)iDivide;

      p += 4;

   }

   return true;

}




bool image::set_mipmap(::draw2d::e_mipmap emipmap)
{

   if (m_emipmap == emipmap)
   {

      return true;

   }

   if (emipmap != ::draw2d::mipmap_none)
   {

      return _set_mipmap(emipmap);

   }

   return true;

}


bool image::_set_mipmap(::draw2d::e_mipmap emipmap)
{

   ASSERT(emipmap != ::draw2d::mipmap_none);

   ::image_pointer pimage(clone());

   int cxSource = pimage->width();

   int cySource = pimage->width();

   int iSourceScan = pimage->scan_size();

   double cx = cxSource;

   double cy = cySource;

   if (emipmap == ::draw2d::mipmap_isotropic)
   {

      double newcx = cx + cx / 2.0 - 1.0;

      double newcy = cy;

      if (!create({ (int) newcx, (int) newcy}))
      {

         __throw(error_resource);

      }

      get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      int x = cxSource;

      int y = 0;

      get_graphics()->stretch(::size_f64(cxSource, cySource), pimage->g());

      while (cx >= 1.0 && cy >= 1.0)
      {

         cx /= 2.0;

         cy /= 2.0;

         if (::parallelization::priority() == ::priority_idle)
         {

            map();

            C2PassScale < CBlackmanFilter > scale(1.0);

            scale.Scale(
            &colorref()[x + y * m_iScan / sizeof(color32_t)],
            (::u32) cx,
            (::u32)cy,
            m_iScan,
            pimage->get_data(),
            cxSource,
            cySource,
            iSourceScan
            );

         }
         else
         {

            get_graphics()->stretch(::rect_dim((i32)x, (i32)y, (i32)cx, (i32)cy ), pimage->g(), ::rect_dim(0, 0, (i32)cx, (i32)cy ));

         }

         y += (i32) cy;

      }

      m_emipmap = ::draw2d::mipmap_isotropic;

   }
   else
   {

      double newcx = cx * 2.0 - 1.0;

      double newcy = cy * 2.0 - 1.0;

      if (!create({ (i32)newcx, (i32)newcy }))
      {

         __throw(error_resource);

      }

      int dx;

      int x = 0;

      int xPrevious;
      int yPrevious;
      int cxPrevious;
      int cyPrevious;

      xPrevious = 0;
      cxPrevious = cxSource;

      for (dx = (i32) cx; dx > 0; x += dx, dx /= 2)
      {

         yPrevious = 0;
         cyPrevious = pimage->height();

         for (int y = 0, dy = (i32) cy; dy > 0; y += dy, dy /= 2)
         {

            if (::parallelization::priority() == ::priority_idle)
            {

               map();

               C2PassScale < CBlackmanFilter > scale(1.0);

               scale.Scale(
               &colorref()[x + y * m_iScan / sizeof(color32_t)],
               dx,
               dy,
               m_iScan,
               &pimage->colorref()[xPrevious + yPrevious * pimage->m_iScan / sizeof(color32_t)],
               cxPrevious,
               cyPrevious,
               pimage->m_iScan
               );

               yPrevious = y;
               cyPrevious = dy;
               pimage = this;

            }
            else
            {

               get_graphics()->stretch(::rect_dim( x, y, dx, dy ), pimage->get_graphics(), ::rect_dim( 0, 0, pimage->width(), pimage->height() ));

            }

         }

         xPrevious = x;
         cxPrevious = dx;

      }

      m_emipmap = ::draw2d::mipmap_anisotropic;

   }

   size() = pimage->get_size();

   return true;

}


bool image::SetViewportOrg(const ::point_i32 & point)
{

   m_point = point;

   if (!m_bMapped)
   {

      get_graphics()->SetViewportOrg(point);

   }

   return true;

}


bool image::create_helper_map()
{

   if (m_pextension && m_pextension->m_pframea)
   {

      for (auto & pframe : *m_pextension->m_pframea)
      {

         if (pframe != this)
         {

            pframe->m_pimage->create_helper_map();

         }

      }

   }

   _create_helper_map();

   return true;

}


bool image::_create_helper_map()
{


   index a;

   a = (index)(area());

   //return true;

   index jNextBoundary;
   index jStart;
   u8 * pdata = (u8 *)colorref();

   if (pdata == nullptr || a <= 0)
   {

      return false;

   }

   index w = width();
   index h = height();
   index sw = w * sizeof(color32_t);
   index aa = w * h;
   {

      m_memoryMap.set_size(a * 2);

      m_memoryMap.set(0);
      u8 * opacity = m_memoryMap.get_data();

      for (index i = 0; i < height(); i++)
      {

         for (index j = 0; j < sw; j += 4)
         {

            if (pdata[i*m_iScan + j + 3] == 255)
            {
               jStart = j;
               jNextBoundary = minimum(j + 960, sw);
               for (j += 4; j < jNextBoundary; j += 4)
               {
                  if (pdata[i*m_iScan + j + 3] != 255)
                  {
                     break;
                  }
               }

               j-=4;

               index c = (j - jStart) >> 2;

               index m = j >> 2;

               byte n = 1;

               u8 * o = &opacity[(int)(i * w)];

               while (c >= 0)
               {

                  o[m] = n;

                  m--;

                  n++;

                  c--;

               }

            }

         }

      }

   }

   {

      u8 * transparency = m_memoryMap.get_data() + a;

      for (index i = 0; i < height(); i++)
      {

         for (index j = 0; j < sw; j += 4)
         {

            if (pdata[i * m_iScan + j + 3] == 0)
            {

               jStart = j;

               jNextBoundary = minimum(j + 960, sw);

               for (j += 4; j < jNextBoundary; j += 4)
               {

                  if (pdata[i * m_iScan + j + 3] != 0)
                  {

                     break;

                  }

               }

               j -= 4;

               index c = (j - jStart) >> 2;

               index m = j >> 2;

               byte n = 1;

               u8 * t = &transparency[(int)(i * w)];

               while (c >= 0)
               {

                  t[m] = n;

                  m--;

                  n++;

                  c--;

               }

            }

         }

      }

   }

   return true;

}


bool image::set_font_factor(double dFactor)
{

   m_dFontFactor = dFactor;

   if (!m_bMapped)
   {

      get_graphics()->m_dFontFactor = dFactor;

   }

   return true;

}


bool image::set_alpha_mode(::draw2d::enum_alpha_mode emode)
{

   m_ealphamode = emode;

   if (!m_bMapped)
   {

      get_graphics()->set_alpha_mode(emode);

   }

   return true;

}


i32 image::cos(i32 i, i32 iAngle)
{

   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(iAngle);

   ::exception::throw_interface_only();

   return 0;

}


i32 image::sin(i32 i, i32 iAngle)
{

   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(iAngle);

   ::exception::throw_interface_only();

   return 0;

}


i32 image::cos10(i32 i, i32 iAngle)
{

   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(iAngle);

   ::exception::throw_interface_only();

   return 0;

}


i32 image::sin10(i32 i, i32 iAngle)
{

   UNREFERENCED_PARAMETER(i);
   UNREFERENCED_PARAMETER(iAngle);

   ::exception::throw_interface_only();

   return 0;

}

/*   i32 image::width()
   {
      ::exception::throw_interface_only();
   }

   i32 image::height()
   {
      ::exception::throw_interface_only();
   }

   i64 image::area()
   {
      return ((i64) width()) * ((i64)height());
   }

   size_i32 image::size()
   {
      return size_i64(width(), height());
   }*/


double image::pi() const
{

   return atan(1.0)*4.0;

}


bool image::fill_channel(i32 intensity, ::color::enum_channel echannel)
{
   map();
   i32 offset = ((i32)echannel) % 4;
   i64 size = scan_area();

   color32_t * pcr = (color32_t *) &((u8 *)colorref())[offset];

   u8 * pb;

   i64 iSize32 = size / 32;
   i32 i;
   for (i = 0; i < iSize32; i += 32)
   {
      pb = (u8 *)&pcr[i];
      pb[0 * 4] = (byte)intensity;
      pb[1 * 4] = (byte)intensity;
      pb[2 * 4] = (byte)intensity;
      pb[3 * 4] = (byte)intensity;
      pb[4 * 4] = (byte)intensity;
      pb[5 * 4] = (byte)intensity;
      pb[6 * 4] = (byte)intensity;
      pb[7 * 4] = (byte)intensity;
      pb[8 * 4] = (byte)intensity;
      pb[9 * 4] = (byte)intensity;
      pb[10 * 4] = (byte)intensity;
      pb[11 * 4] = (byte)intensity;
      pb[12 * 4] = (byte)intensity;
      pb[13 * 4] = (byte)intensity;
      pb[14 * 4] = (byte)intensity;
      pb[15 * 4] = (byte)intensity;
      pb[16 * 4] = (byte)intensity;
      pb[17 * 4] = (byte)intensity;
      pb[18 * 4] = (byte)intensity;
      pb[19 * 4] = (byte)intensity;
      pb[20 * 4] = (byte)intensity;
      pb[21 * 4] = (byte)intensity;
      pb[22 * 4] = (byte)intensity;
      pb[23 * 4] = (byte)intensity;
      pb[24 * 4] = (byte)intensity;
      pb[25 * 4] = (byte)intensity;
      pb[26 * 4] = (byte)intensity;
      pb[27 * 4] = (byte)intensity;
      pb[28 * 4] = (byte)intensity;
      pb[29 * 4] = (byte)intensity;
      pb[30 * 4] = (byte)intensity;
      pb[31 * 4] = (byte)intensity;
   }

   for (i = 0; i < size; i++)
   {
      *((u8 *)&pcr[i]) = (byte)intensity;
   }

   return true;

}


bool image::white_fill_channel(i32 intensity, ::color::enum_channel echannel)
{
   map();
   i32 offset = ((i32)echannel) % 4;
   i64 size = scan_area();

   color32_t * pcr = (color32_t *) &((u8 *)colorref())[offset];

   //      u8 * pb;

   i64 iSize32 = size / 32;
   i32 i;
   //      for (i=0; i < iSize32; i+=32 )
   //      {
   //         pb = (u8 *) &pcr[i];
   //         pb[0 * 4] = (byte) intensity;
   //         pb[1 * 4] = (byte) intensity;
   //         pb[2 * 4] = (byte) intensity;
   //         pb[3 * 4] = (byte) intensity;
   //         pb[4 * 4] = (byte) intensity;
   //         pb[5 * 4] = (byte) intensity;
   //         pb[6 * 4] = (byte) intensity;
   //         pb[7 * 4] = (byte) intensity;
   //         pb[8 * 4] = (byte) intensity;
   //         pb[9 * 4] = (byte) intensity;
   //         pb[10 * 4] = (byte) intensity;
   //         pb[11 * 4] = (byte) intensity;
   //         pb[12 * 4] = (byte) intensity;
   //         pb[13 * 4] = (byte) intensity;
   //         pb[14 * 4] = (byte) intensity;
   //         pb[15 * 4] = (byte) intensity;
   //         pb[16 * 4] = (byte) intensity;
   //         pb[17 * 4] = (byte) intensity;
   //         pb[18 * 4] = (byte) intensity;
   //         pb[19 * 4] = (byte) intensity;
   //         pb[20 * 4] = (byte) intensity;
   //         pb[21 * 4] = (byte) intensity;
   //         pb[22 * 4] = (byte) intensity;
   //         pb[23 * 4] = (byte) intensity;
   //         pb[24 * 4] = (byte) intensity;
   //         pb[25 * 4] = (byte) intensity;
   //         pb[26 * 4] = (byte) intensity;
   //         pb[27 * 4] = (byte) intensity;
   //         pb[28 * 4] = (byte) intensity;
   //         pb[29 * 4] = (byte) intensity;
   //         pb[30 * 4] = (byte) intensity;
   //         pb[31 * 4] = (byte) intensity;
   //      }


   for (i = 0; i < size; i++)
   {

      *((u8 *)&pcr) = (byte)(((int)intensity * (int)*((u8 *)&pcr)) / 255);

      pcr++;

   }

   return true;

}


bool image::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc)
{

   map();

   echannelDst = (::color::enum_channel) (((i32)echannelDst) % 4);
   echannelSrc = (::color::enum_channel) (((i32)echannelSrc) % 4);

   if (echannelDst == echannelSrc)
   {

      return true;

   }

   u8 * pdataDst = (u8 *)get_data() + ((i32)echannelDst);

   u8 * pdataSrc = (u8 *)get_data() + ((i32)echannelSrc);

   for (i32 y = 0; y < height(); y++)
   {

      u8 * pdst = &pdataDst[m_iScan * y];

      u8 * psrc = &pdataSrc[m_iScan * y];

      for (i32 x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   return true;

}


bool image::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image * pimage)
{

   if (size() != pimage->size())
   {

      return false;

   }

   map();

   if (colorref() == nullptr)
   {

      return false;

   }

   pimage->map();

   if (pimage->colorref() == nullptr)
   {

      return false;

   }

   echannelDst = (::color::enum_channel) (((i32)echannelDst) % 4);
   echannelSrc = (::color::enum_channel) (((i32)echannelSrc) % 4);

   u8 * pdataDst = (u8 *)get_data() + ((i32)echannelDst);

   u8 * pdataSrc = (u8 *)pimage->get_data() + ((i32)echannelSrc);

   for (i32 y = 0; y < height(); y++)
   {

      u8 * pdst = &pdataDst[m_iScan * y];

      u8 * psrc = &pdataSrc[pimage->m_iScan * y];

      for (i32 x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   return true;

}


bool image::tint(::image * pimage, const ::color::color & color32)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   map();

   u8 *src = (u8 *)pimage->colorref();
   u8 *dst = (u8 *)colorref();
   i64 size = scan_area();

   byte uchR = (byte)color32.red;
   byte uchG = (byte)color32.green;
   byte uchB = (byte)color32.blue;

   //      i32 i = 0;;


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
   //byte tableR[256];
   //byte tableG[256];
   //byte tableB[256];
   //for (index i = 0; i < 255; i++)
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

   color32_t o = argb(255, uchR, uchG, uchB);

   while (size > 0)
   {

      byte bA = src[3];

      if (bA == 0)
      {

         *((color32_t *)dst) = 0;

      }
      else if (bA == 255)
      {

         *((color32_t *)dst) = o;

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

   return true;

}


bool image::saturation(double dRate)
{

   map();

   u8 * dst = (u8 *) colorref();

   i64 size = scan_area();

   int iDiv = 255 * 255;

   int iMul = (int)(dRate * (double)iDiv);

   while (size > 0)
   {

      int iMax = maximum(maximum(dst[0], dst[1]), dst[2]);

      int iMin = minimum(minimum(dst[0], dst[1]), dst[2]);

      int iMid = (iMax + iMin) / 2;

      dst[0] = ((dst[0] - iMid) * iMul / iDiv) + iMid;

      dst[1] = ((dst[1] - iMid) * iMul / iDiv) + iMid;

      dst[2] = ((dst[2] - iMid) * iMul / iDiv) + iMid;

      dst += 4;

      size--;

   }

   return true;

}


bool image::lightness(double dRate)
{

   rate_rgb(__byte(dRate * 255.0), 255);

   return true;

}


bool image::opacity(double dRate)
{

   int iA = __byte(255. * dRate);

   map();

   try
   {
      u8 * puch = (u8 *)get_data();
      i64 iArea = scan_area();
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

   return true;

}


bool image::set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A)
{

   map();

   u8 *dst = (u8 *)colorref();
   i64 size = scan_area();

   byte uchB = (byte)R;
   byte uchG = (byte)G;
   byte uchR = (byte)B;

   //      i32 i = 0;;

   while (size > 0)
   {
      //dst[3] = dst[i];
      dst[0] = ((int)uchB * (int)dst[3] * A) >> 16;
      dst[1] = ((int)uchG * (int)dst[3] * A) >> 16;
      dst[2] = ((int)uchR * (int)dst[3] * A) >> 16;
      dst[3] = ((int)dst[3] * A) >> 8;
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

   return true;

}


bool image::set_rgb(color32_t cr)
{

   return set_rgb(colorref_get_r_value(cr), colorref_get_g_value(cr), colorref_get_b_value(cr));

}


//bool image::set_rgb(i32 R, i32 G, i32 B)
//{
//
//   return set(R, G, B);
//
//}


::i64 image::get_rgba_area(const ::color::color & color32) const
{

   ::i64 areaRgba = 0;

   color32_t cr = IMAGE_ARGB(color32.alpha, color32.red, color32.green, color32.blue);

   const color32_t* p = this->get_data();

   areaRgba++;

   auto area = this->area();

   while (area > 0)
   {

      if (*p == cr)
      {

         areaRgba++;

      }

      area--;

      p++;

   }

   return areaRgba;

}


::i64 image::get_rgba_area(const ::color::color & color32, const RECTANGLE_I32 * lpcrect) const
{

   ::rectangle_i32 r(lpcrect);

   if (!r.intersect(this->rectangle()))
   {

      return 0;

   }

   ::count areaRgba = 0;

   color32_t cr = IMAGE_ARGB(color32.alpha, color32.red, color32.green, color32.blue);

   int wscan = m_iScan / sizeof(color32_t);

   int w = r.width();

   int h = r.height();

   int scanadvance = wscan - w;

   const color32_t* p = this->get_data() + r.left + wscan * r.top;

   areaRgba++;

   while (h > 0)
   {

      for (int x = 0; x < w; x++)
      {

         if (*p == cr)
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


::i64 image::_001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const
{

   auto r = this->rectangle();

   return _001GetTopLeftWeightedOpaqueArea(iAlphaMin, r);

}


::i64 image::_001GetTopLeftWeightedOpaqueArea(int iAlphaMin, const RECTANGLE_I32 * lpcrect) const
{

   ::rectangle_i32 r(lpcrect);

   ::rectangle_i32 rTotal(this->rectangle());

   if (!r.intersect(rTotal))
   {

      return 0;

   }

   ::i64 areaRgba = 0;

   int wscan = m_iScan / sizeof(color32_t);

   int w = r.width();

   int h = r.height();

   ::i64 areaRgbaLast = 0;

   const color32_t* p = this->get_data() + r.left + wscan * r.top;

   areaRgba++;

   for(int y = r.top; y < r.bottom; y++)
   {

      auto ysq = (rTotal.bottom-y);

      auto pbyte = &((byte*)p)[IMAGE_A_BYTE_INDEX];

      for (int x = r.left; x < r.right; x++)
      {

         if (*pbyte > iAlphaMin)
         {

            areaRgba+=((rTotal.right-x) + ysq);

         }

         pbyte += sizeof(color32_t);

      }

      p += wscan;

      h--;
      if (areaRgba < areaRgbaLast)
      {

         output_debug_string("test");

      }

      areaRgbaLast = areaRgba;

   }

   return areaRgba;

}


bool image::paint_rgb(::color::color color)
{

   int R = color.red;
   int G = color.green;
   int B = color.blue;
   int A;

   u8 * puch = (u8 *)get_data();
   i64 iArea = scan_area();
   while (iArea > 0)
   {

      A = puch[IMAGE_A_BYTE_INDEX];

      puch[IMAGE_R_BYTE_INDEX] = R * A / 255;
      puch[IMAGE_G_BYTE_INDEX] = G * A / 255;
      puch[IMAGE_B_BYTE_INDEX] = B * A / 255;

      puch += 4;

      iArea--;

   }

   return true;

}


bool image::rgb_from(::image * pimage)
{

   if (!create(pimage->size()))
   {

      return false;

   }

   try
   {

      u8 * puchSrc = (u8 *)get_data();
      u8 * puchDst = (u8 *)pimage->get_data();
      i64 iArea = pimage->scan_area();
      while (iArea > 0)
      {
         puchDst[0] = puchSrc[0];
         puchDst[1] = puchSrc[1];
         puchDst[2] = puchSrc[2];
         puchDst+=4;
         puchSrc+=4;
         iArea--;
      }

   }
   catch (...)
   {

      return false;

   }

   return true;

}


bool image::pixelate(i32 iSize)
{

   if (iSize <= 1)
   {

      return true;

   }

   i32 w = width();
   i32 h = height();
   i32 s = m_iScan / sizeof(color32_t);

   i32 xCount = w / iSize;
   i32 yCount = h / iSize;

   i32 iDiv;
   i32 iDiv2;

   i32 a;
   i32 r;
   i32 g;
   i32 b;
   i32 a2;
   i32 r2;
   i32 g2;
   i32 b2;
   //bool bFirst;
   color32_t * pdata = get_data();
   i32 x1;
   i32 y1;
   for (i32 x = 0; x < xCount; x++)
   {
      x1 = x * iSize;
      for (i32 y = 0; y < yCount; y++)
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
         for (i32 i = 0; i < iSize; i++)
         {
            for (i32 j = 0; j < iSize; j++)
            {
               color32_t cr = pdata[x1 + i + (y1 + j) * s];
               a += colorref_get_a_value(cr);
               r += colorref_get_r_value(cr);
               g += colorref_get_g_value(cr);
               b += colorref_get_b_value(cr);
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
         color32_t cr = argb(a2, r2, g2, b2);
         for (i32 i = 0; i < iSize; i++)
         {
            for (i32 j = 0; j < iSize; j++)
            {

               pdata[x1 + i + (y1 + j) * s] = cr;

            }

         }

      }

   }

   if (w % iSize != 0)
   {
      i32 x = xCount;
      i32 x1 = x * iSize;
      i32 iMax = w - xCount * iSize;
      for (i32 y = 0; y < yCount; y++)
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
         for (i32 i = 0; i < iMax; i++)
         {
            for (i32 j = 0; j < iSize; j++)
            {
               color32_t cr = pdata[x1 + i + (y1 + j) * w];
               a += colorref_get_a_value(cr);
               r += colorref_get_r_value(cr);
               g += colorref_get_g_value(cr);
               b += colorref_get_b_value(cr);
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
         color32_t cr = argb(a2, r2, g2, b2);
         for (i32 i = 0; i < iMax; i++)
         {
            for (i32 j = 0; j < iSize; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

   }

   if (h % iSize != 0)
   {
      i32 y = yCount;
      i32 y1 = y * iSize;
      i32 jMax = h - yCount * iSize;
      for (i32 x = 0; x < xCount; x++)
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
         for (i32 i = 0; i < iSize; i++)
         {
            for (i32 j = 0; j < jMax; j++)
            {
               color32_t cr = pdata[x1 + i + (y1 + j) * w];
               a += colorref_get_a_value(cr);
               r += colorref_get_r_value(cr);
               g += colorref_get_g_value(cr);
               b += colorref_get_b_value(cr);
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
         color32_t cr = argb(a2, r2, g2, b2);
         for (i32 i = 0; i < iSize; i++)
         {
            for (i32 j = 0; j < jMax; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

   }

   if (w % iSize != 0)
   {
      i32 x = xCount;
      i32 x1 = x * iSize;
      i32 iMax = w - xCount * iSize;
      i32 y = yCount;
      i32 y1 = y * iSize;
      i32 jMax = h - yCount * iSize;
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
      for (i32 i = 0; i < iMax; i++)
      {
         for (i32 j = 0; j < jMax; j++)
         {
            color32_t cr = pdata[x1 + i + (y1 + j) * w];
            a += colorref_get_a_value(cr);
            r += colorref_get_r_value(cr);
            g += colorref_get_g_value(cr);
            b += colorref_get_b_value(cr);
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

      color32_t cr = argb(a2, r2, g2, b2);

      for (i32 i = 0; i < iMax; i++)
      {

         for (i32 j = 0; j < jMax; j++)
         {

            pdata[x1 + i + (y1 + j) * w] = cr;

         }

      }

   }

   return true;

}


bool image::rate_rgb(int iMul, int iDiv)
{

   map();

   try
   {
      u8 * puch = (u8 *)get_data();
      i64 iArea = scan_area();
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

   return true;

}


bool image::map(bool bApplyAlphaTransform) const
{

   if (!m_bMapped)
   {

      ((::image *)this)->map(bApplyAlphaTransform);

      pixmap::map();

      m_bMapped = true;

   }

   return true;

}


bool image::unmap() const
{

   if (m_bMapped)
   {

      ((::image *)this)->_unmap();

      if (_get_graphics() != nullptr)
      {

         ::rectangle_i32 rectThis(m_size);

         ::rectangle_i32 rectMap(rectangle());

         if (rectThis.contains(rectMap.origin()))
         {

            _get_graphics()->SetViewportOrg(rectMap.origin());

         }
         else
         {

            _get_graphics()->SetViewportOrg(0, 0);

         }

      }

      ((::image *)this)->m_bMapped = false;

   }

   return true;

}


bool image::set_mapped()
{

   m_bMapped = false;

   return true;

}

//
//   bool image::update_window(::aura::draw_interface * puserinteraction,::message::message * pmessage,bool bTransferBuffer)
//   {
//
//      UNREFERENCED_PARAMETER(puserinteraction);
//      UNREFERENCED_PARAMETER(pmessage);
//
//      // default implementation does nothing, image_impl should be now updated (before calling update interaction_impl)
//      // and ready to be queried if post queried
//
////      ::exception::throw_interface_only();
//
//
//      return true;
//
//   }


//bool image::print_window(::aura::draw_interface * puserinteraction,::message::message * pmessage)
//{

//   UNREFERENCED_PARAMETER(puserinteraction);
//   UNREFERENCED_PARAMETER(pmessage);

//   ::exception::throw_interface_only();

//   return false;

//}



bool image::gradient_fill(color32_t clr1, color32_t clr2, const point_i32 & point1, const point_i32 & point2)
{

   double dx = point2.x - point1.x;

   double dy = point1.y - point2.y;

   if (dx == 0.0 && dy == 0.0)
   {
      fill(
      byte_clip(colorref_get_a_value(clr1) * 0.5 + colorref_get_a_value(clr2) * 0.5),
      byte_clip(colorref_get_r_value(clr1) * 0.5 + colorref_get_r_value(clr2) * 0.5),
      byte_clip(colorref_get_g_value(clr1) * 0.5 + colorref_get_g_value(clr2) * 0.5),
      byte_clip(colorref_get_b_value(clr1) * 0.5 + colorref_get_b_value(clr2) * 0.5));
   }
   else if (dx == 0.0)
   {

      gradient_horizontal_fill(clr1, clr2, point1.y, point2.y);

   }
   else if (dy == 0.0)
   {

      gradient_vertical_fill(clr1, clr2, point1.x, point2.x);

   }
   else
   {

      //         int x1 = minimum(point1.x, point2.x);

      //       int x2 = maximum(point1.x, point2.x);

      //     int y1 = minimum(point1.y, point2.y);

      //   int y2 = maximum(point1.y, point2.y);

      //         int top = y1;
      //
      //       int left = x1;
      //
      //       int right = width() - x2;
      //
      //  int bottom = height() - y2;

      int dim = maximum(width(), height());

      double angle = atan2(dy, dx);

      ::image_pointer pimage;

      auto pmathematics = ::mathematics::mathematics();

      if (fabs(dx) > fabs(dy))
      {

         double sin = ::sin(angle);

         auto estatus = __construct(pimage);

         if (!estatus)
         {

            return false;

         }

         estatus = pimage->create({ (i32)(dim / sin), (i32)(dim / sin) });

         if (!estatus)
         {

            return false;

         }

         pimage->gradient_horizontal_fill(clr1, clr2, point1.y, point2.y);

         pimage->rotate(this, -angle, 1.0);

      }
      else
      {

         double cos = ::cos(angle);

         auto estatus = __construct(pimage);

         if (!estatus)
         {

            return false;

         }

         estatus = pimage->create({ (i32)(dim / cos), (i32)(dim / cos) });

         if (!estatus)
         {

            return false;

         }

         pimage->gradient_vertical_fill(clr1, clr2, point1.x, point2.x);

         pimage->rotate(this, pmathematics->get_pi() - angle, 1.0);

      }

   }

   return true;

}


bool image::gradient_horizontal_fill(color32_t clr1, color32_t clr2, int start, int end)
{

   if (end < start)
   {
      ::__swap(start, end);
      ::__swap(clr1, clr2);
   }

   end = minimum(end, height() - 1);
   color32_t clr = clr1;
   u8 * pb = (u8 *)colorref();
   color32_t * pdata;
   int line = 0;
   for (; line < start; line++)
   {
      pdata = (color32_t *)&pb[m_iScan * line];
      for (int row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }
   double d;
   for (; line < end; line++)
   {

      d = ((double)(line - start)) / ((double)(end - start));

      clr = argb(
            byte_clip(colorref_get_a_value(clr1) * (1.0 - d) + colorref_get_a_value(clr2) * d),
            byte_clip(colorref_get_r_value(clr1) * (1.0 - d) + colorref_get_r_value(clr2) * d),
            byte_clip(colorref_get_g_value(clr1) * (1.0 - d) + colorref_get_g_value(clr2) * d),
            byte_clip(colorref_get_b_value(clr1) * (1.0 - d) + colorref_get_b_value(clr2) * d));

      pdata = (color32_t *)&pb[m_iScan * line];
      for (int row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }
   clr = clr2;
   for (; line < height(); line++)
   {
      pdata = (color32_t *)&pb[m_iScan * line];
      for (int row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }

   return true;

}


bool image::gradient_vertical_fill(color32_t clr1, color32_t clr2, int start, int end)
{

   if (end < start)
   {
      ::__swap(start, end);
      ::__swap(clr1, clr2);
   }

   end = minimum(end, width() - 1);
   color32_t clr = clr1;
   u8 * pb = (u8 *)colorref();
   color32_t * pdata;
   int row = 0;
   for (; row < start; row++)
   {
      pdata = (color32_t *)&pb[sizeof(color32_t) * row];
      for (int line = 0; line < height(); line++)
      {
         *pdata = clr;
         pdata += m_iScan;
      }
   }
   double d;
   for (; row < end; row++)
   {

      d = ((double)(row - start)) / ((double)(end - start));

      clr = argb(
            byte_clip(colorref_get_a_value(clr1) * (1.0 - d) + colorref_get_a_value(clr2) * d),
            byte_clip(colorref_get_r_value(clr1) * (1.0 - d) + colorref_get_r_value(clr2) * d),
            byte_clip(colorref_get_g_value(clr1) * (1.0 - d) + colorref_get_g_value(clr2) * d),
            byte_clip(colorref_get_b_value(clr1) * (1.0 - d) + colorref_get_b_value(clr2) * d));

      pdata = (color32_t *)&pb[sizeof(color32_t) * row];
      for (int line = 0; line < width(); line++)
      {
         *pdata = clr;
         pdata += m_iScan;
      }
   }
   clr = clr2;
   for (; row < width(); row++)
   {
      pdata = (color32_t *)&pb[sizeof(color32_t) * row];
      for (int line = 0; line < width(); line++)
      {
         *pdata = clr;
         pdata += m_iScan;
      }
   }

   return true;

}


bool image::gradient_horizontal_fill(color32_t clr1, color32_t clr2)
{

   gradient_horizontal_fill(clr1, clr2, 0, height() - 1);

   return true;

}


bool image::gradient_vertical_fill(color32_t clr1, color32_t clr2)
{

   gradient_vertical_fill(clr1, clr2, 0, width() - 1);

   return true;

}


bool image::invert_rgb()
{

   return invert_rgb(rectangle());

}

bool image::invert_rgb(const ::rectangle_i32 & rectangle)

{

   int s = m_iScan;

   int left;
   int right;
   int top;
   int bottom;

   left = minimum(maximum(0, rectangle.left), width());


   right = minimum(maximum(0, rectangle.right), width());


   top = minimum(maximum(0, rectangle.top), height());


   bottom = minimum(maximum(0, rectangle.bottom), height());

   int start = left * 4 + top * s;

   for (int y = top; y < bottom; y++, start += s)
   {

      u8 * pb = &((u8 *)colorref())[start];

      for (int x = left; x < right; x++, pb += 4)
      {

         pb[0] = ~pb[0];
         pb[1] = ~pb[1];
         pb[2] = ~pb[2];

      }

   }

   return true;

}


bool image::create_circle(::image * pimage, int diameter)
{

   if (!create({ diameter, diameter }))
   {

      return false;

   }

   if (::is_null(pimage) || pimage->area() <= 0)
   {

      fill(255, 0, 0, 0);

   }
   else
   {

      get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      get_graphics()->stretch(rect_dim(0, 0, diameter, diameter), pimage->g(), rect_dim(0, 0, pimage->width(), pimage->height()));

   }

   ::size_i32 s = size();

   color32_t * pcolorref = colorref();

   int iScan = m_iScan;

   int wscan = iScan / sizeof(color32_t);

   double radius = diameter / 2.0;

   double dBorder = 1.0;

   double rmin = radius - dBorder;

   double rmax = radius;

   int crA;

   color32_t * pcolorref2;

   for (int y = 0; y < s.cx; y++)
   {

      pcolorref2 = &pcolorref[y * wscan];

      for (int x = 0; x < s.cx; x++)
      {

         double dx = x;

         double dy = y;

         double distance = sqrt((dx - radius) * (dx - radius) + (dy - radius) * (dy - radius));

         crA = (int)((rmin - distance) * 255.0 / dBorder);

         crA = maximum(minimum(crA, 255), 0);

         *pcolorref2 = (*pcolorref2 & 0x00ffffff) | (crA << 24);

         pcolorref2++;

      }

   }

   return true;

}


bool image::create_framed_square(::image * pimage, int inner, int outer, color32_t cr)
{

   if (!create({ inner + outer * 2, inner + outer * 2 }))
   {

      return false;

   }

   fill(cr);

   get_graphics()->stretch(::rect_dim(outer, outer, inner, inner), pimage->g(), ::rect_dim(0, 0, pimage->width(), pimage->height()));

   return true;

}


void image_copy(::image * pimagethis, ::image * pimage)
{

   pimagethis->copy(pimage);

}


void image_create(::object * pobject, ::image_pointer & pimage)
{

   __construct(pimage, pobject);

}


void image_create_image(::image * pimage,  const ::size_i32 & size)
{

   pimage->create(size);

}


unsigned int * image_get_data(::image * pimage)
{

   return (unsigned int *)pimage->colorref();

}


::draw2d::graphics * image_get_graphics(::image * pimage)
{

   if (::is_null(pimage))
   {

      return nullptr;

   }

   return pimage->g();

}


bool image::hue_offset(double dRadians)
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
   double U = ::cos(dRadians);
   double W = ::sin(dRadians);


   u8 *dst = (u8 *)get_data();

   i64 size = scan_area();


   while (size--)
   {
      double oldr = dst[0];
      double oldg = dst[1];
      double oldb = dst[2];
      dst[0] = clampAndConvert((.299 + .701*U + .168*W)*oldr
                               + (.587 - .587*U + .330*W)*oldg
                               + (.114 - .114*U - .497*W)*oldb);
      dst[1] = clampAndConvert((.299 - .299*U - .328*W)*oldr
                               + (.587 + .413*U + .035*W)*oldg
                               + (.114 - .114*U + .292*W)*oldb);
      dst[2] = clampAndConvert((.299 - .3*U + 1.25*W)*oldr
                               + (.587 - .588*U - 1.05*W)*oldg
                               + (.114 + .886*U - .203*W)*oldb);
      dst += 4;
   }

   return true;

}



void image::fast_copy(color32_t * p)
{

   ::copy_colorref(get_data(), rectangle(), scan_size(), p);

}

bool image::on_load_image()
{

   if (m_iExifOrientation != 0)
   {

      on_exif_orientation();

   }

   return true;

}


bool image::on_exif_orientation()
{

   e_rotate_flip erotateflip = ::exif_orientation_rotate_flip(m_iExifOrientation);

   if (erotateflip == rotate_90_flip_none)
   {

      rotate90();

   }
   else if (erotateflip == rotate_180_flip_none)
   {

      rotate180();

   }
   else if (erotateflip == rotate_270_flip_none)
   {

      rotate270();

   }
   else if (erotateflip == rotate_none_flip_x)
   {

      flipx();

   }
   else if (erotateflip == rotate_90_flip_x)
   {

      rotate90flipx();

   }
   else if (erotateflip == rotate_180_flip_x)
   {

      rotate180flipx();

   }
   else if (erotateflip == rotate_270_flip_x)
   {

      rotate270flipx();

   }

   return true;

}



//save_image::save_image(::matter * pmatter)
save_image::save_image()
{

   m_eformat = ::draw2d::format_png;

   m_iQuality = 100;

   m_iDpi = 96;

}


//save_image::save_image(::matter * pmatter, const ::payload & varFile, const ::payload & varOptions)
//{
//
//   __pointer(::aura::system) psystem = m_psystem;
//
//   auto eformat = pdraw2d->text_to_format(varOptions["format"]);
//
//   if (eformat != ::draw2d::format_none)
//   {
//
//      __pointer(::aura::system) psystem = m_psystem;
//
//      eformat = pdraw2d->file_extension_to_format(varFile.get_file_path());
//
//   }
//
//   if (eformat == ::draw2d::format_none)
//   {
//
//      m_eformat = ::draw2d::format_png;
//
//   }
//
//   if (varOptions["quality"].get_type() == e_type_double
//      || varOptions["quality"].get_type() == e_type_float)
//   {
//
//      m_iQuality = (int) (varOptions["quality"].get_double() * 100.0);
//
//   }
//   else
//   {
//
//      m_iQuality = varOptions["quality"].i32();
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

//bool image::load_matter_icon(string_array & straMatter, string strIcon)
//{
//
//   ::file::path path;
//
//   for (auto & strMatter : straMatter)
//   {
//
//      path = strMatter;
//
//      path = pcontext->m_papexcontext->dir().matter(path / strIcon);
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
//   bool image::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
//   {
//
//      return psystem->imaging().from(m_p, pgraphics, pfi, bUnload);
//
//   }
//
//#endif

/*::size_i32 image::size()
{

   if (m_parray.is_set() && m_parray->get_count() > 0 && m_parray->m_dwTotal > 0)
   {

      return m_parray->size();

   }

   return m_p->size();

}*/


void image::defer_update_image()
{

   auto pframes = frames();

   if (!pframes)
   {

      return;

   }

   auto pimage = pframes->calc_current_frame(m_dynamic);

   if (pimage)
   {

      ::pixmap * ppixmapDst = this;

      ::pixmap * ppixmapSrc = pimage;
      
      pimage->unmap();

      m_pgraphics = pimage->m_pgraphics;

      m_pbitmap = pimage->m_pbitmap;

      ::memcpy(ppixmapDst, ppixmapSrc, sizeof(::pixmap));

   }

}





#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::image * m_p, i32 dx, i32 dy, void * pftbitmap, int xParam, int yParam)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, point_i32++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         i32 a = bitmap->buffer[q * bitmap->width + point_i32];

         *((color32_t *)&((u8 *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::image * m_p, i32 dx, i32 dy, void * pftbitmap, int xParam, int yParam, byte aParam, byte rectangle, byte g, byte b)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, point_i32++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         i32 a = bitmap->buffer[q * bitmap->width + point_i32];

         if (a > 0)
         {

            *((color32_t *)&((u8 *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((color32_t *)&((u8 *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;

         }

      }
   }

}

#endif









#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::image * m_p, i32 dx, i32 dy, void * pftbitmap, int xParam, int yParam)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, point_i32++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         i32 a = bitmap->buffer[q * bitmap->width + point_i32];

         *((color32_t *)&((u8 *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::image * m_p, i32 dx, i32 dy, void * pftbitmap, int xParam, int yParam, byte aParam, byte rectangle, byte g, byte b)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, point_i32++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         i32 a = bitmap->buffer[q * bitmap->width + point_i32];

         if (a > 0)
         {

            *((color32_t *)&((u8 *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((color32_t *)&((u8 *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;

         }

      }
   }

}


#endif



stream & image::write(::stream & stream) const
{

   //__throw(todo("write_link"));
   //if(stream.write_link(this))
   //{

   //   return stream;

   //}

   i32 iWidth = width();

   stream << (::i32) iWidth;

   i32 iHeight = height();

   stream << (::i32) iHeight;

   stream << (::i32) m_sizeAlloc.cx;

   stream << (::i32) m_sizeAlloc.cy;

   stream << (::i32) m_iScan;

   stream << (::i32) m_emipmap;

   if (area() > 0)
   {

      map();

      stream.write(colorref(), m_iScan * height());

   }

   return stream;

}



stream & image::read(::stream & stream)
{

   //__throw(todo("write_link"));
   //string strLink;

   //bool bReadOnly;

   //if (stream.get_object_link(*this, strLink, bReadOnly))
   //{

   //   stream.read_link(*this);

   //   return stream;

   //}

   i32 width;

   stream >> width;

   if (stream.fail())
   {

      return stream;

   }

   i32 height;

   stream >> height;

   if (stream.fail())
   {

      return stream;

   }

   i32 widthAlloc;
   stream >> widthAlloc;
   if (stream.fail())
   {

      return stream;

   }

   i32 heightAlloc;
   stream >> heightAlloc;
   if (stream.fail())
   {

      return stream;

   }

   i32 iScan;
   stream >> iScan;
   if (stream.fail())
   {

      return stream;

   }

   i32 iMipmap;
   stream >> iMipmap;
   if (stream.fail())
   {

      return stream;

   }

   if (width <= 0)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (height <= 0)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (widthAlloc <= 0)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (heightAlloc <= 0)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (iScan <= 0)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (widthAlloc < width)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (heightAlloc < height)
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (iScan < widthAlloc / (i32)sizeof(color32_t))
   {
      stream.setstate(::file::badbit);

      return stream;

   }

   if (!create({ widthAlloc, heightAlloc }))
   {

      stream.setstate(::file::badbit);

      return stream;

   }

   map();

   if (iScan == m_iScan)
   {

      stream.exchange("bitmap", get_data(), iScan * this->height());

   }
   else
   {

      memory mem;

      mem.set_size(iScan * this->height());

      stream.exchange("bitmap", mem.get_data(), iScan * this->height());

      auto size = stream.m_gcount;

      if (size / iScan < height)
      {

         stream.setstate(::file::badbit);

         return stream;

      }

      ::copy_colorref(get_data(), width, height, m_iScan, (color32_t *)mem.get_data(), iScan);

   }

   m_size.cx = width;

   m_size.cy = height;

   return stream;

}


::matter * image::clone() const
{

   auto pimage = ((::image *)this)->__create<::image>();

   pimage->copy(this);

   pimage->add_ref(OBJ_REF_DBG_THIS);

   return pimage;

}


//::e_status image::create_image()
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


//::e_status     image::create(int cx, int cy, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
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


//::e_status     image::create(const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
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
http://www.sparkhound.com/blog/detect-image-file-types-through-byte-arrays
::payload bmp = Encoding.ASCII.GetBytes("BM"); // BMP
::payload gif = Encoding.ASCII.GetBytes("GIF"); // GIF
::payload png = new byte[]{ 137, 80, 78, 71 }; // PNG
::payload tiff = new byte[]{ 73, 73, 42 }; // TIFF
::payload tiff2 = new byte[]{ 77, 80, 42 }; // TIFF
::payload jpeg = new byte[]{ 255, 216, 255, 224 }; // jpeg
::payload jpeg2 = new byte[]{ 255, 216, 255, 225 }; // jpeg canon
*/


//virtual ::image_pointer ::create_image(::draw2d::e_load eload = ::draw2d::load_none);
//virtual ::image_pointer create_image({int cx,  int cy});
//virtual ::image_pointer create_image(const ::size_i32 & size);




::e_status image::transform(enum_image eimage)
{

if (eimage == image_grayscale)
{

   return saturation(0.0);

}

return ::error_not_found;

}


::draw2d::graphics * image::_get_graphics() const
{

   return nullptr;

}





bool image::map(bool bApplyAlphaTransform)
{

   pixmap::map(bApplyAlphaTransform);

   return true;

}


bool image::_unmap()
{

   return true;

}


//void image::static_initialize()
//{
//
//   double dCos;
//   double dSin;
//   double d32 = (1U << 31);
//   dPi = atan(1.0) * 4.0;
//   i32 i;
//   for (i = 0; i < 360; i++)
//   {
//      dCos = ::cos(i / 180.0 * dPi);
//      dSin = ::sin(i / 180.0 * dPi);
//      Cosines[i] = float(dCos);
//      Sines[i] = float(dSin);
//      CosN[i] = (i64)(dCos * d32);
//      SinN[i] = (i64)(dSin * d32);
//   }
//   d32 = (1U << 31);
//   d32 *= 8;
//   for (i = 0; i < 10; i++)
//   {
//      dCos = ::cos(i / 180.0 * dPi);
//      dSin = ::sin(i / 180.0 * dPi);
//      Cos10N[i] = (i64)(dCos * d32);
//      Sin10N[i] = (i64)(dSin * d32);
//   }
//
//}
//


::image_extension * image::get_extension()
{

   if (::is_null(m_pextension))
   {

      m_pextension = new image_extension();

   }

   return m_pextension;

}


bool image::_draw_blend(const image_drawing & imagedrawing)
{

   auto pgraphics = get_graphics();

   if (::is_null(pgraphics))
   {

      return false;

   }

   if(!pgraphics->_draw_blend(imagedrawing))
   {

      return false;

   }

   return true;

}


bool image::_draw_raw(const image_drawing & imagedrawing)
{

   auto pgraphics = get_graphics();

   if (::is_null(pgraphics))
   {

      return false;

   }

   if(!pgraphics->_draw_raw(imagedrawing))
   {

      return false;

   }

   return true;

}


