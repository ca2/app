//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "frame_array.h"
#include "drawing.h"
#include "save_image.h"
#include "context_image.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/draw2d/image32.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/task_tool.h"
#include "aura/graphics/draw2d/draw2d.h"


//#include "acme/_operating_system.h"


double get_default_screen_dpi()
{

   // just a guess lol :D
   return 96.0;

}

//
//#ifdef WINDOWS
//#include <wincodec.h>
//#include <ShCore.h>
////#elif defined(UNIVERSAL_WINDOWS)
////#include <ShCore.h>
//#endif



#include "aura/graphics/graphics/double_pass_scale.h"


template < typename TYPE >
void sort_image_argb(TYPE& A, TYPE& R, TYPE& G, TYPE& B)
{

#if defined(WINDOWS) || defined(LINUX)

   ::__swap(&R, &B);

#endif

}


template < typename TYPE >
void sort_image_rgb(TYPE& R, TYPE& G, TYPE& B)
{

#if defined(WINDOWS) || defined(LINUX)

   ::__swap(R, B);

#endif

}


image::image()
{
   
}


image::~image()
{
   
   auto psystem = acmesystem();

   if (::is_set(psystem))
   {
      
      auto paurasystem = psystem->m_paurasystem;
      
      if(::is_set(paurasystem))
      {
         
         auto pdraw2d = paurasystem->draw2d();
         
         if(::is_set(pdraw2d))
         {
            
            pdraw2d->erase_image(this);
            
         }
         
      }

   }

}


void image::on_initialize_particle()
{

   acmesystem()->m_paurasystem->draw2d()->add_image(this);

   ::particle::on_initialize_particle();

}


::size_i32 image::get_image_drawer_size() const
{

   return get_size();

}


::image_pointer image::image_source_image(const ::size_i32 &)
{
   
   return this; 

}


::size_i32 image::image_source_size(const ::size_f64 &, enum_image_selection) const
{ 
   
   return get_size(); 

}


::size_i32 image::image_source_size() const 
{
   
   return get_size(); 

}


bool image::_is_ok() const
{ 
   
   return ::pixmap::is_ok() && ::particle::has_ok_flag(); 

}


::draw2d::graphics* image::get_graphics() const
{

   unmap();

   return _get_graphics();

}


::draw2d::bitmap_pointer image::get_bitmap() const
{

   throw ::interface_only();

   return nullptr;

}



::draw2d::bitmap_pointer image::detach_bitmap()
{

   throw ::interface_only();

   return nullptr;

}





void image::realize(::draw2d::graphics* pgraphics) const
{

   UNREFERENCED_PARAMETER(pgraphics);

   //return true;

}


void image::unrealize() const
{

   //return true;

}


bool image::is_realized() const
{

   return true;

}


void image::defer_realize(::draw2d::graphics* pgraphics) const
{

   if (is_realized())
      return;

   realize(pgraphics);

}


void image::create_ex(const ::size_i32 & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate, int iGoodStride, bool bPreserve)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void image::create(const ::size_i32& size, ::enum_flag eflagCreate, int iGoodStride, bool bPreserve)
{

   return create_ex(size, nullptr, 0, eflagCreate, iGoodStride, bPreserve);

}


void image::initialize(const ::size_i32 & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate)
{

   return create_ex(size, pimage32, iScan, eflagCreate);

}


//void image::initialize(const ::size_i32 & size, ::image32_t * pimage32, int iScan, ::eobject eobjectCreate)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}


//void     image::create(i32 width, i32 height, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
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


bool image::on_host_read_pixels(::pixmap* ppixmapHost) const
{

   //map();

   //::copy_image32(ppixmapHost, this);

   return false;

}


void image::dc_select(bool bSelect)
{

   UNREFERENCED_PARAMETER(bSelect);

   throw ::interface_only();

   //return false;

}


void image::create(::draw2d::graphics* pgraphics)
{

   ::draw2d::bitmap& bitmap = *pgraphics->get_current_bitmap();

   if (::is_reference_null(bitmap))
   {

      throw ::exception(error_null_pointer);

   }

   throw ::interface_only();

   //return ::error_failed;

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


void image::create_isotropic(::image* pimage)
{

   int cx = (int)(pimage->m_dIsotropicRate * width());

   int cy = (int)(pimage->m_dIsotropicRate * height());

   pimage->create({ cx, cy });

   if (::parallelization::get_priority() == ::e_priority_idle)
   {

      map();

      C2PassScale < CBlackmanFilter > scale(1.0);

      scale.Scale(
         pimage->image32(),
         pimage->color_indexes(),
         pimage->width(),
         pimage->height(),
         pimage->scan_size(),
         image32(),
         width(),
         height(),
         scan_size()
      );

   }
   else
   {

      pimage->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      image_source imagesource(get_graphics(), ::rectangle_i32_dimension(0, 0, width(), height()));

      image_drawing_options imagedrawingoptions(::rectangle_i32_dimension(0, 0, cx, cy));

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimage->g()->draw(imagedrawing);

   }

   pimage->set_mipmap(pimage->m_emipmap);

   //return true;

}


void image::create_isotropic(double_array& daRate, ::enum_priority epriority)
{

   //return false;

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

   //fork_count_end(get_app(), imagea.get_count(),
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
//      m_pathCache.empty();
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


void image::destroy()
{

   m_sizeRaw.cx() = 0;
   m_sizeRaw.cy() = 0;
   m_size.cx() = 0;
   m_size.cy() = 0;
   m_sizeAlloc.cx() = 0;
   m_sizeAlloc.cy() = 0;
   pixmap::reset();
   pixmap::unmap();
   clear_flag(e_flag_success);
   clear_flag(e_flag_failure);

   //return ::success;

}


void image::destroy_os_data()
{

}


//void image::draw(const ::image * pimage)
//{
//
//   //if (::is_null(pimage))
//   //{
//
//   //   return false;
//
//   //}
//
//   return get_graphics()->draw(rectangle_i32_dimension(0, 0,
//                                     width(),
//                                     height()),
//                                     pimage->g(),
//                                     rectangle_i32_dimension(0, 0,
//                                     pimage->width(),
//                                     pimage->height()));
//
//}


//void image::to(::draw2d::graphics * pgraphics)
//{
//
//   return to(pgraphics, nullptr, size());
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point)
//{
//
//   return to(pgraphics, point, size());
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::size_i32 & size)
//{
//
//   return to(pgraphics, nullptr, size);
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle)
//{
//
//   return to(pgraphics, ::top_left(rectangle), ::size_i32(rectangle));
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size)
//{
//
//   return to(pgraphics, point, size, nullptr);
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc)
//{
//
//
//   UNREFERENCED_PARAMETER(pgraphics);
//   UNREFERENCED_PARAMETER(point);
//   UNREFERENCED_PARAMETER(size);
//   UNREFERENCED_PARAMETER(pointSrc);
//   throw ::interface_only();
//
//   return false;
//
//}


//void image::stretch(::draw2d::graphics * pgraphics)
//{
//
//   return stretch(pgraphics->m_pimage);
//
//}


void image::stretch_image(::image* pimage)
{

   auto pgraphics = get_graphics();

   if (::is_null(pgraphics))
   {

      throw ::exception(error_null_pointer);

   }

   if (this->size().is_empty())
   {

      throw ::exception(error_null_pointer);

   }

   image_source imagesource(pimage->g(), ::rectangle_f64(pimage->size()));

   image_drawing_options imagedrawingoptions(rectangle());

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   return pgraphics->draw(imagedrawing);

}


void image::_draw_raw(const ::rectangle_i32& rectangleDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam)
{

   ::image* pimageDst = this;

   if (!pimageDst->m_bMapped || !pimageSrc->m_bMapped)
   {

      //get_graphics()->set_alpha_mode(m_ealphamode);

      image_source imagesource(pimageSrc, { pointSrcParam, rectangleDstParam.size() } );

      rectangle_f64 rectangle(rectangleDstParam);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      return get_graphics()->draw(imagedrawing);

   }

   pimageDst->map();

   pimageSrc->map();

   ::rectangle_i32 rectangleTarget(rectangleDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   rectangleTarget += m_point;

   if (pointSrc.x() < 0)
   {

      rectangleTarget.left -= pointSrc.x();

      pointSrc.x() = 0;

   }

   if (pointSrc.y() < 0)
   {

      rectangleTarget.top -= pointSrc.y();

      pointSrc.y() = 0;

   }

   if (rectangleTarget.left < 0)
   {

      rectangleTarget.right += rectangleTarget.left;

      rectangleTarget.left = 0;

   }

   if (rectangleTarget.width() < 0)
   {

      return;

   }

   if (rectangleTarget.top < 0)
   {

      rectangleTarget.bottom += rectangleTarget.top;

      rectangleTarget.top = 0;

   }

   if (rectangleTarget.height() < 0)
   {

      return;

   }

   int xEnd = minimum(rectangleTarget.width(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - rectangleTarget.left));

   int yEnd = minimum(rectangleTarget.height(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - rectangleTarget.top));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * rectangleTarget.top + rectangleTarget.left * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)];

   image32_t* pdst2;

   image32_t* psrc2;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = (image32_t*)&pdst[scanDst * y];

      psrc2 = (image32_t*)&psrc[scanSrc * y];

      ::memory_copy(pdst2, psrc2, xEnd * 4);
      //for(int x = 0; x < xEnd; x++)
      //{

      //   *pdst2 = *psrc2;

      //   pdst2++;

      //   psrc2++;

      //}
      //pdst2 += xEnd;
      //psrc2 += xEnd;

   }

   //return true;

}


void image::blend(const ::rectangle_i32& rectangleDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, ::u8 bA)
{

   ::image* pimageDst = this;

   pimageDst->map();

   pimageSrc->map();

   ::rectangle_i32 rectangleTarget(rectangleDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(rectangleTarget.size());

   rectangleTarget += m_point;

   if (pointSrc.x() < 0)
   {

      rectangleTarget.left -= pointSrc.x();

      pointSrc.x() = 0;

   }

   if (pointSrc.y() < 0)
   {

      rectangleTarget.top -= pointSrc.y();

      pointSrc.y() = 0;

   }

   if (rectangleTarget.left < 0)
   {

      size.cx() += rectangleTarget.left;

      rectangleTarget.left = 0;

   }

   if (size.cx() < 0)
   {

      //return true;

      return;

   }

   if (rectangleTarget.top < 0)
   {

      size.cy() += rectangleTarget.top;

      rectangleTarget.top = 0;

   }

   if (size.cy() < 0)
   {

      //return true;

      return;

   }

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - rectangleTarget.left));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - rectangleTarget.top));

   if (xEnd < 0)
   {

      //return false;

      return;

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * rectangleTarget.top + rectangleTarget.left * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)];

   u8* pdst2;

   u8* psrc2;

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

   //return true;

}


void image::blend2(const ::point_i32& pointDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, const ::size_i32& sizeParam, ::u8 bA)
{

   ::image* pimageDst = this;

   pimageDst->map();

   pimageSrc->map();

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);

   pointDst += m_point;

   if (pointSrc.x() < 0)
   {
      pointDst.x() -= pointSrc.x();
      pointSrc.x() = 0;
   }

   if (pointSrc.y() < 0)
   {
      pointDst.y() -= pointSrc.y();
      pointSrc.y() = 0;
   }

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {

      return;

   }
      //return true;

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {
   //   return true;

      return;
   }

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - pointDst.y()));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   ::u8 * pdst = ((::u8 *)pimageDst->image32()) + (scanDst * pointDst.y()) + (pointDst.x() * sizeof(image32_t));

   ::u8 * psrc = ((::u8 *)pimageSrc->image32()) + (scanSrc * pointSrc.y()) + (pointSrc.x() * sizeof(image32_t));

   ::u8 * pdst2;

   ::u8 * psrc2;

   if (bA == 0)
   {

   }
   else if (bA == 255)
   {

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = pdst + (scanDst * y);

         psrc2 = psrc + (scanSrc * y);

         for (int x = 0; x < xEnd; x++)
         {

            int aDst = pdst2[3];

            int aSrc = psrc2[3];

            if (aDst == 0)
            {

            }
            else if (aSrc == 0)
            {

               *((image32_t *)pdst2) = {};

            }
            else
            {

               //int r = (pdst2[0] * 255) / aDst;
               //int g = (pdst2[1] * 255) / aDst;
               //int b = (pdst2[2] * 255) / aDst;

               //int a = aSrc * aDst;

               //pdst2[0] = (r * a) >> 16;
               //pdst2[1] = (g * a) >> 16;
               //pdst2[2] = (b * a) >> 16;
               //pdst2[3] = a >> 8;
               pdst2[0] = ((int) pdst2[0] * aSrc) / 255;
               pdst2[1] = ((int) pdst2[1] * aSrc) / 255;
               pdst2[2] = ((int) pdst2[2] * aSrc) / 255;
               pdst2[3] = (aDst * aSrc) / 255;

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

         //::memory_copy(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
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
            pdst2[0] = u8_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
            pdst2[1] = u8_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
            pdst2[2] = u8_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
            pdst2[3] = u8_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);

            pdst2 += 4;

            psrc2 += 4;

         }
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }

   }

   //return true;

}


void image::blend(const ::point_i32& pointDst, ::image* pimageSrc, const ::point_i32& pointSrc, const ::size_i32& size)
{

   return blend(pointDst, pimageSrc, pointSrc, size, 255);

}


void image::blend(const ::point_i32& pointDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, const ::size_i32& sizeParam, ::u8 bA)
{

   ::image* pimageDst = this;

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);


   pimageDst->map();

   pimageSrc->map();

   pointDst += m_point;

   if (pointSrc.x() < 0)
   {
      pointDst.x() -= pointSrc.x();
      pointSrc.x() = 0;
   }

   if (pointSrc.y() < 0)
   {
      pointDst.y() -= pointSrc.y();
      pointSrc.y() = 0;
   }

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {

      //  return true;

      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      //return true;

      return;

   }

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - pointDst.y()));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;


   u8* pdst2;

   u8* psrc2;

#ifdef __APPLE__
   u8* pdst = &((u8*)pimageDst->image32())[scanDst * (pimageDst->height() - pointDst.y() - yEnd) + pointDst.x() * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * (pimageSrc->height() - pointSrc.y() - yEnd) + pointSrc.x() * sizeof(image32_t)];

#else

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)];

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

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
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
         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
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
               pdst2[0] = u8_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
               pdst2[1] = u8_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
               pdst2[2] = u8_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
               pdst2[3] = u8_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



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

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
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

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
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
               pdst2[0] = u8_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
               pdst2[1] = u8_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
               pdst2[2] = u8_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
               pdst2[3] = u8_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



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


void image::precision_blend(const ::point_i32& pointDst, ::image* pimageSrc, const ::point_i32& pointSrc, const ::size_i32& size)
{

   return precision_blend(pointDst, pimageSrc, pointSrc, size, 255);

}


void image::precision_blend(const ::point_i32& pointDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, const ::size_i32& sizeParam, ::u8 bA)
{

   ::image* pimageDst = this;

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);

   pimageDst->map();

   pimageSrc->map();

   pointDst += m_point;

   if (pointSrc.x() < 0)
   {
      pointDst.x() -= pointSrc.x();
      pointSrc.x() = 0;
   }

   if (pointSrc.y() < 0)
   {
      pointDst.y() -= pointSrc.y();
      pointSrc.y() = 0;
   }

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {

      //return true;

      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      //return true;

      return;

   }

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - pointDst.y()));

   if (xEnd < 0)
   {
    
      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)];

   u8* pdst2;

   u8* psrc2;

   if (bA == 0)
   {

   }
   else if (bA == 255)
   {

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memory_copy(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
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
      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //::memory_copy(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
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
            pdst2[0] = u8_clip(((psrc2[0] * bA) + (pdst2[0] * acomplement)) / 255);
            pdst2[1] = u8_clip(((psrc2[1] * bA) + (pdst2[1] * acomplement)) / 255);
            pdst2[2] = u8_clip(((psrc2[2] * bA) + (pdst2[2] * acomplement)) / 255);
            pdst2[3] = u8_clip(((psrc2[3] * bA) + (pdst2[3] * acomplement)) / 255);



            pdst2 += 4;

            psrc2 += 4;

         }
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }

   }

   //return true;

}


void image::fork_blend(const ::point_i32& pointDst, ::image* pimageSrc, const ::point_i32& pointSrc, const ::size_i32& size)
{

   //return 
   
   fork_blend(pointDst, pimageSrc, pointSrc, size, 255);

}


void image::fork_blend(const ::point_i32& pointDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, const ::size_i32& sizeParam, ::u8 bA)
{

   if (bA == 0)
   {

      //return true;

      return;

   }

   ::image* pimageDst = this;

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::size_i32 size(sizeParam);

   pimageDst->map();

   pimageSrc->map();

   pointDst += m_point;

   if (pointSrc.x() < 0)
   {
      pointDst.x() -= pointSrc.x();
      pointSrc.x() = 0;
   }

   if (pointSrc.y() < 0)
   {
      pointDst.y() -= pointSrc.y();
      pointSrc.y() = 0;
   }

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointSrc.x() -= pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {

      //return true;

      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointSrc.y() -= pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      //return true;

   }

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - pointDst.y()));

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

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)];

   //u8 * pdst5; // dst opacity map if available // opacity map does not make sense for images that machine

   u8* psrcOpacity; // src opacity map if available

   u8* psrcTransparency; // src transparency map if available

   if (pimageSrc->m_memoryMap.size() == pimageSrc->area() * 2)
   {

      psrcOpacity = &pimageSrc->m_memoryMap.data()[pimageSrc->width() * pointSrc.y() + pointSrc.x()];

   }
   else
   {

      psrcOpacity = nullptr;

   }

   if (pimageSrc->m_memoryMap.size() == pimageSrc->area() * 2)
   {

      psrcTransparency = &pimageSrc->m_memoryMap.data()[pimageSrc->area() + pimageSrc->width() * pointSrc.y() + pointSrc.x()];

   }
   else
   {

      psrcTransparency = nullptr;

   }

   ::pointer<::aura::system>psystem = acmesystem();

   auto pgroup = psystem->task_group();

   synchronous_lock slGroup(pgroup->synchronization());

   auto ptool = psystem->task_tool(::e_task_tool_draw2d);

   synchronous_lock slTool(ptool->synchronization());

   if (!pgroup || !ptool)
   {

      return blend(pointDst, pimageSrc, pointSrc, size, bA);

   }

   int y = 0;

   pgroup->select_tool(ptool);

   pgroup->prepare(::e_task_op_tool, yEnd);

   for (auto& ptoolitem : ptool->m_itema)
   {

      ::pointer<::draw2d::task_tool_item>pitem = ptoolitem;

      pitem->m_eop = ::draw2d::task_tool_item::op_blend;

      pitem->m_w = pimageSrc->width();

      pitem->m_h = pimageSrc->height();

      pitem->m_ySkip = (int)(pgroup->task_count());

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

   pgroup->call_run();

   //return true;

}


void image::draw_ignore_alpha(const ::point_i32& pointDstParam, ::image* pimage, const ::rectangle_i32& rectangleSrcParam)
{

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(rectangleSrcParam.top_left());

   ::size_i32 size(rectangleSrcParam.size());

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {
    
      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      return;

   }

   int xEnd = minimum(size.cx(), minimum(pimage->width() - pointSrc.x(), width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimage->height() - pointSrc.y(), height() - pointDst.y()));

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   i32 s1 = m_iScan / sizeof(image32_t);

   i32 s2 = pimage->m_iScan / sizeof(image32_t);

   image32_t* pdst = &image32()[s1 * pointDst.y()] + pointDst.x();

   image32_t* psrc = &pimage->image32()[s2 * pointSrc.y()] + pointSrc.x();

   image32_t* pdst2;

   image32_t* psrc2;

   int i = 0;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = &pdst[s1 * y];

      psrc2 = &psrc[s2 * y];

      for (int x = 0; x < xEnd; x++)
      {

         if (psrc2->u8_opacity(pimage->color_indexes()) == 0)
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


void image::blend(const ::point_i32& pointDstParam, ::image* pimageSrc, const ::point_i32& pointSrcParam, ::image* pimageAlf, const ::point_i32& pointDstAlfParam, const ::size_i32& sizeParam)
{

   ::image* pimageDst = this;

   pimageDst->map();
   pimageSrc->map();
   pimageAlf->map();

   ::point_i32 pointDst(pointDstParam);

   ::point_i32 pointSrc(pointSrcParam);

   ::point_i32 pointDstAlf(pointDstAlfParam);

   ::size_i32 size(sizeParam);

   if (pointSrc.x() < 0)
   {
      pointDst.x() -= pointSrc.x();
      pointDstAlf.x() -= pointSrc.x();
      pointSrc.x() = 0;
   }

   if (pointSrc.y() < 0)
   {
      pointDst.y() -= pointSrc.y();
      pointDstAlf.y() -= pointSrc.y();
      pointSrc.y() = 0;
   }

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {
    
      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      return;

   }

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - pointDst.y()));

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   if (pointDstAlf.x() < 0)
   {

   }

   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

   i32 scanAlf = pimageAlf->m_iScan;

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)];

   u8* psrc = &((u8*)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)];

   u8* palf = &((u8*)pimageAlf->image32())[-scanAlf * pointDstAlf.y() - pointDstAlf.x() * sizeof(image32_t)] + 3;

   u8* pdst2;

   u8* psrc2;

   u8* palf2;

   int x1;
   int x2;
   int y1;
   int y2;

   x1 = pointDstAlf.x();
   x2 = pimageAlf->width() + x1;
   y1 = pointDstAlf.y();
   y2 = pimageAlf->height() + y1;


   //int a;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = (u8*)&pdst[scanDst * y];

      psrc2 = (u8*)&psrc[scanSrc * y];

      palf2 = (u8*)&palf[scanAlf * y];

      for (int x = 0; x < xEnd; x++)
      {

         if (psrc2[3] > 0)
         {
            //               if (false && x >= x1 && x < x2 && y >= y1 && y < y2)
            //               {
            //
            //                  a = (*palf2 * psrc2[3]) / 255;
            //                  a = psrc2[3];
            //                  //a = (int) (::u8) sqrt((float) (*palf2 * psrc2[3]));
            //                  pdst2[3] = (::u8)maximum(a, pdst2[3]);
            //                  //pdst2[3] = (::u8)((((int)psrc2[3] - (int)pdst2[3]) * a + ((int)pdst2[3] * 255)) / 255);
            //                  pdst2[3] = (::u8)(maximum(psrc2[3], pdst2[3]));
            //
            //                  //                  if (a > 0)
            //                  {
            //
            //                     pdst2[0] = (::u8)((((int)psrc2[0] - (int)pdst2[0]) * a + ((int)pdst2[0] * 255)) / 255);
            //                     pdst2[1] = (::u8)((((int)psrc2[1] - (int)pdst2[1]) * a + ((int)pdst2[1] * 255)) / 255);
            //                     pdst2[2] = (::u8)((((int)psrc2[2] - (int)pdst2[2]) * a + ((int)pdst2[2] * 255)) / 255);
            //
            //                  }
            //
            //               }
            //               else
            {

               //pdst2[3] = (::u8)(maximum(psrc2[3], pdst2[3]));
               //pdst2[3] = (::u8)((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255);
               //pdst2[0] = (::u8)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
               //pdst2[1] = (::u8)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
               //pdst2[2] = (::u8)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);
               pdst2[3] = (::u8)(maximum(((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255), pdst2[3]));
               pdst2[0] = (::u8)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
               pdst2[1] = (::u8)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
               pdst2[2] = (::u8)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);

            }
         }


         pdst2 += 4;

         psrc2 += 4;

         palf2 += 4;


      }

   }

   //return true;

}

/*
void image::blend(const ::point_i32 & pointDst,::image * pimageSrc, const ::point_i32 & pointSrc, const ::size_i32 & size)
{

   ::image * pimageDst = this;

   pimageDst->map();
   pimageSrc->map();


   if (pointSrc.x() < 0)
   {
      pointDst.x() -= pointSrc.x();
      pointSrc.x() = 0;
   }

   if (pointSrc.y() < 0)
   {
      pointDst.y() -= pointSrc.y();
      pointSrc.y() = 0;
   }

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
      return true;

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
      return true;

   int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x(), pimageDst->width() - pointDst.x()));

   int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y(), pimageDst->height() - pointDst.y()));

   if (xEnd < 0)
      return false;

   if (yEnd < 0)
      return false;



   i32 scanDst = pimageDst->m_iScan;

   i32 scanSrc = pimageSrc->m_iScan;

#ifdef __APPLE__

   u8 * pdst = &((u8 *)pimageDst->image32())[scanDst * (pimageDst->height() - pointDst.y() - 1) + pointDst.x() * sizeof(image32_t)] + 3;

   u8 * psrc = &((u8 *)pimageSrc->image32())[scanSrc * (pimageSrc->height() - pointSrc.y() - 1) + pointSrc.x() * sizeof(image32_t)] + 3;

#else

   u8 * pdst = &((u8 *)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)] + 3;

   u8 * psrc = &((u8 *)pimageSrc->image32())[scanSrc * pointSrc.y() + pointSrc.x() * sizeof(image32_t)] + 3;

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


//void image::set_rgb(i32 R, i32 G, i32 B)
//{
//
//   i64 size = scan_area();
//
//   image32_t* pcr = data();
//
//   if (pcr == nullptr)
//   {
//
//      //return false;
//
//      return;
//
//   }
//
//   sort_image_rgb(R, G, B);
//
//   for (i32 i = 0; i < size; i++)
//   {
//
//      ((u8*)pcr)[0] = R;
//      ((u8*)pcr)[1] = G;
//      ((u8*)pcr)[2] = B;
//
//      pcr++;
//
//   }
//
//   //return true;
//
//}


/*   void image::Fill ( i32 R, i32 G, i32 B )
   {
      image32_t color=rgb ( B, G, R );
      i64 size = area();

      image32_t * pcr;

      i64 iSize32 = size / 32;
      i32 i;
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

      for (i=0; i<size_i32; i++ )
      {
         data()[i]=color;
      }
   }
   */


//void image::flip_vertical(::image* pimage)
//{
//
//   create(pimage->size());
//
//   //if (!create(pimage->size()))
//   //{
//
//   //   //return false;
//
//   //   return;
//
//   //}
//
//   int w = width();
//
//   int h = height();
//
//   int sw = w * 4;
//
//   int dsw = m_iScan / 4;
//
//   int ssw = pimage->m_iScan / 4;
//
//   for (index y = 0; y < h; y++)
//   {
//
//      ::memory_copy(&image32()[y * dsw], &pimage->image32()[(h - y - 1) * ssw], sw);
//
//   }
//
////   return true;
//
//}
//
//
//void image::flip_horizontal(::image* pimageSource)
//{
//
//   if (pimageSource == this)
//   {
//
//      return flip_horizontal();
//
//   }
//
//   create(pimageSource->size());
//
//   //if (!create(pimageSource->size()))
//   //{
//
//   //   return false;
//
//   //}
//
//   int half = -1;
//
//   int dsw = m_iScan / 4;
//
//   int ssw = pimageSource->m_iScan / 4;
//
//   int w = width();
//
//   int h = height();
//
//   auto pimage32 = image32();
//
//   auto pimage32Source = pimageSource->image32();
//
//   for (index y = 0; y < h; y++)
//   {
//
//      for (index x = 0; x < w; x++)
//      {
//
//         pimage32[y * dsw + x] = pimage32Source[y * ssw + w - x - 1];
//
//      }
//
//   }
//
////   return true;
//
//}


void image::flip_horizontally()
{

   map();

   int half = -1;

   int sw = m_iScan / 4;

   int w = width();

   int halfw = w / 2;

   int h = height();

   auto pimage32 = image32();

   for (index y = 0; y < h; y++)
   {

      for (index x = 0; x < halfw; x++)
      {

         __swap(pimage32[y * sw + x], pimage32[y * sw + w - x - 1]);

      }

   }

   //return true;

}


void image::flip_vertically()
{

   map();

   int half = -1;

   int sw = m_iScan / 4;

   int h = height();

   int halfh = h / 2;

   int w = width();

   auto pimage32 = image32();

   memory line;

   line.set_size(m_iScan);

   for (index y = 0; y < halfh; y++)
   {

      auto plineFirstHalf = pimage32 + (y * sw);

      auto plineSecondHalf = pimage32 + ((h - y - 1) * sw);

      memcpy(line.data(), plineFirstHalf, m_iScan);
      memcpy(plineFirstHalf, plineSecondHalf, m_iScan);
      memcpy(plineSecondHalf, line.data(), m_iScan);

   }

   //return true;

}


//void image::flipx(::image* pimage)
//{
//
//   //return 
//   
//   flip_horizontal(pimage);
//
//}
//
//
//void image::flipy(::image* pimage)
//{
//
//   //return 
//   
//   flip_vertical(pimage);
//
//}
//


::image_pointer image::horizontally_flipped()
{

   ::image_pointer pimage = this->clone();

   pimage->flip_horizontally();

   return pimage;

}


::image_pointer image::vertically_flipped()
{

   ::image_pointer pimage = this->clone();

   pimage->flip_vertically();

   return pimage;

}


void image::ToAlpha(i32 i)
{
   u8* dst = (u8*)data();
   i64 size = scan_area();

   while (size--)
   {
      dst[3] = dst[i];
      dst += 4;
   }

   //return true;

}


void image::from_alpha()
{

   u8* dst = (u8*)data();

   i64 size = scan_area();

   while (size--)
   {
      dst[0] = dst[3];
      dst[1] = dst[3];
      dst[2] = dst[3];
      dst += 4;
   }

   //return true;

}


void image::mult_alpha(::image* pimage, bool bPreserveAlpha)
{
   UNREFERENCED_PARAMETER(pimage);
   UNREFERENCED_PARAMETER(bPreserveAlpha);

   u8* dst = (u8*)data();
   i64 size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = lower_u8(((i32)dst[0] * (i32)dst[3]) >> 8);
      dst[1] = lower_u8(((i32)dst[1] * (i32)dst[3]) >> 8);
      dst[2] = lower_u8(((i32)dst[2] * (i32)dst[3]) >> 8);

      dst[4 + 0] = lower_u8(((i32)dst[4 + 0] * (i32)dst[4 + 3]) >> 8);
      dst[4 + 1] = lower_u8(((i32)dst[4 + 1] * (i32)dst[4 + 3]) >> 8);
      dst[4 + 2] = lower_u8(((i32)dst[4 + 2] * (i32)dst[4 + 3]) >> 8);

      dst[8 + 0] = lower_u8(((i32)dst[8 + 0] * (i32)dst[8 + 3]) >> 8);
      dst[8 + 1] = lower_u8(((i32)dst[8 + 1] * (i32)dst[8 + 3]) >> 8);
      dst[8 + 2] = lower_u8(((i32)dst[8 + 2] * (i32)dst[8 + 3]) >> 8);

      dst[12 + 0] = lower_u8(((i32)dst[12 + 0] * (i32)dst[12 + 3]) >> 8);
      dst[12 + 1] = lower_u8(((i32)dst[12 + 1] * (i32)dst[12 + 3]) >> 8);
      dst[12 + 2] = lower_u8(((i32)dst[12 + 2] * (i32)dst[12 + 3]) >> 8);

      dst[16 + 0] = lower_u8(((i32)dst[16 + 0] * (i32)dst[16 + 3]) >> 8);
      dst[16 + 1] = lower_u8(((i32)dst[16 + 1] * (i32)dst[16 + 3]) >> 8);
      dst[16 + 2] = lower_u8(((i32)dst[16 + 2] * (i32)dst[16 + 3]) >> 8);

      dst[20 + 0] = lower_u8(((i32)dst[20 + 0] * (i32)dst[20 + 3]) >> 8);
      dst[20 + 1] = lower_u8(((i32)dst[20 + 1] * (i32)dst[20 + 3]) >> 8);
      dst[20 + 2] = lower_u8(((i32)dst[20 + 2] * (i32)dst[20 + 3]) >> 8);

      dst[24 + 0] = lower_u8(((i32)dst[24 + 0] * (i32)dst[24 + 3]) >> 8);
      dst[24 + 1] = lower_u8(((i32)dst[24 + 1] * (i32)dst[24 + 3]) >> 8);
      dst[24 + 2] = lower_u8(((i32)dst[24 + 2] * (i32)dst[24 + 3]) >> 8);

      dst[28 + 0] = lower_u8(((i32)dst[28 + 0] * (i32)dst[28 + 3]) >> 8);
      dst[28 + 1] = lower_u8(((i32)dst[28 + 1] * (i32)dst[28 + 3]) >> 8);
      dst[28 + 2] = lower_u8(((i32)dst[28 + 2] * (i32)dst[28 + 3]) >> 8);

      dst += 4 * 8;
      size -= 8;
   }
   while (size--)
   {
      dst[0] = lower_u8(((i32)dst[0] * (i32)dst[3]) >> 8);
      dst[1] = lower_u8(((i32)dst[1] * (i32)dst[3]) >> 8);
      dst[2] = lower_u8(((i32)dst[2] * (i32)dst[3]) >> 8);
      dst += 4;
   }

   //return true;

}


#define byte_clip2(i) (i)
void image::mult_alpha()
{
   map();

   u8* dst = (u8*)data();
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
   while (size > 0)
   {
      dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
      dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
      dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);
      dst += 4;
      size--;
   }

   //return true;

}


void image::mult_alpha_fast()
{
   map();

   u8* dst = (u8*)data();
   i64 size = scan_area();


   //  >> 2 instead of >> 2 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size--)
   {
      if (dst[3] == 0)
      {
         *((image32_t *)dst) = {};
      }
      else if (dst[3] != 255)
      {
         dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) >> 8);
         dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) >> 8);
         dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) >> 8);
      }
      dst += 4;
   }

   //return true;

}


void image::mult_alpha(const ::point_i32& pointDstParam, const ::size_i32& sizeParam)
{

   ::point_i32 pointDst(pointDstParam);

   ::size_i32 size(sizeParam);

   ::image* pimageDst = this;

   pimageDst->map();

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {


      //return false;

      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      //return false;

      return;

   }

   int xEnd = minimum(size.cx(), pimageDst->width() - pointDst.x());

   int yEnd = minimum(size.cy(), pimageDst->height() - pointDst.y());

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

   i32 scanDst = pimageDst->m_iScan;

#ifdef __APPLE__

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * (height() - pointDst.y() - 1) + pointDst.x() * sizeof(image32_t)];

#else

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)];

#endif

   u8* pdst2;

   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (u8*)&pdst[scanDst * (-y)];

#else

      pdst2 = (u8*)&pdst[scanDst * y];

#endif

      for (int x = 0; x < xEnd; x++)
      {

         pdst2[0] = u8_clip(((i32)pdst2[0] * (i32)pdst2[3]) / 255);
         pdst2[1] = u8_clip(((i32)pdst2[1] * (i32)pdst2[3]) / 255);
         pdst2[2] = u8_clip(((i32)pdst2[2] * (i32)pdst2[3]) / 255);

         pdst2 += 4;

      }

   }

   //return true;

}


void image::create_thumbnail(const ::string & psz)
{

   //return false;

}


void image::div_alpha()
{

   map();

   u8* dst = (u8*)data();
   i64 size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   /*      while (size >= 8)
         {
            dst[0] = lower_u8(((i32)dst[0] * (i32)dst[3])>> 8);
            dst[1] = lower_u8(((i32)dst[1] * (i32)dst[3])>> 8);
            dst[2] = lower_u8(((i32)dst[2] * (i32)dst[3])>> 8);

            dst[4+0] = lower_u8(((i32)dst[4+0] * (i32)dst[4+3])>> 8);
            dst[4+1] = lower_u8(((i32)dst[4+1] * (i32)dst[4+3])>> 8);
            dst[4+2] = lower_u8(((i32)dst[4+2] * (i32)dst[4+3])>> 8);

            dst[8+0] = lower_u8(((i32)dst[8+0] * (i32)dst[8+3])>> 8);
            dst[8+1] = lower_u8(((i32)dst[8+1] * (i32)dst[8+3])>> 8);
            dst[8+2] = lower_u8(((i32)dst[8+2] * (i32)dst[8+3])>> 8);

            dst[12+0] = lower_u8(((i32)dst[12+0] * (i32)dst[12+3])>> 8);
            dst[12+1] = lower_u8(((i32)dst[12+1] * (i32)dst[12+3])>> 8);
            dst[12+2] = lower_u8(((i32)dst[12+2] * (i32)dst[12+3])>> 8);

            dst[16+0] = lower_u8(((i32)dst[16+0] * (i32)dst[16+3])>> 8);
            dst[16+1] = lower_u8(((i32)dst[16+1] * (i32)dst[16+3])>> 8);
            dst[16+2] = lower_u8(((i32)dst[16+2] * (i32)dst[16+3])>> 8);

            dst[20+0] = lower_u8(((i32)dst[20+0] * (i32)dst[20+3])>> 8);
            dst[20+1] = lower_u8(((i32)dst[20+1] * (i32)dst[20+3])>> 8);
            dst[20+2] = lower_u8(((i32)dst[20+2] * (i32)dst[20+3])>> 8);

            dst[24+0] = lower_u8(((i32)dst[24+0] * (i32)dst[24+3])>> 8);
            dst[24+1] = lower_u8(((i32)dst[24+1] * (i32)dst[24+3])>> 8);
            dst[24+2] = lower_u8(((i32)dst[24+2] * (i32)dst[24+3])>> 8);

            dst[28+0] = lower_u8(((i32)dst[28+0] * (i32)dst[28+3])>> 8);
            dst[28+1] = lower_u8(((i32)dst[28+1] * (i32)dst[28+3])>> 8);
            dst[28+2] = lower_u8(((i32)dst[28+2] * (i32)dst[28+3])>> 8);

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
         dst[0] = u8_clip((i32)dst[0] * 255 / (i32)dst[3]);
         dst[1] = u8_clip((i32)dst[1] * 255 / (i32)dst[3]);
         dst[2] = u8_clip((i32)dst[2] * 255 / (i32)dst[3]);
      }

      dst += 4;

   }

   //return true;

}


void image::div_alpha(const ::point_i32& pointDstParam, const ::size_i32& sizeParam)
{

   ::point_i32 pointDst(pointDstParam);

   ::size_i32 size(sizeParam);


   ::image* pimageDst = this;

   pimageDst->map();

   if (pointDst.x() < 0)
   {
      size.cx() += pointDst.x();
      pointDst.x() = 0;
   }

   if (size.cx() < 0)
   {
    
      return;

   }

   if (pointDst.y() < 0)
   {
      size.cy() += pointDst.y();
      pointDst.y() = 0;
   }

   if (size.cy() < 0)
   {

      return;

   }


   int xEnd = minimum(size.cx(), pimageDst->width() - pointDst.x());

   int yEnd = minimum(size.cy(), pimageDst->height() - pointDst.y());

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   i32 scanDst = pimageDst->m_iScan;

#ifdef __APPLE__

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * (height() - pointDst.y() - 1) + pointDst.x() * sizeof(image32_t)];

#else

   u8* pdst = &((u8*)pimageDst->image32())[scanDst * pointDst.y() + pointDst.x() * sizeof(image32_t)];

#endif

   u8* pdst2;

   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (u8*)&pdst[scanDst * (-y)];

#else

      pdst2 = (u8*)&pdst[scanDst * y];

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
            pdst2[0] = u8_clip((i32)pdst2[0] * 255 / (i32)pdst2[3]);
            pdst2[1] = u8_clip((i32)pdst2[1] * 255 / (i32)pdst2[3]);
            pdst2[2] = u8_clip((i32)pdst2[2] * 255 / (i32)pdst2[3]);
         }

         pdst2 += 4;

      }

   }

   //return true;

}


void image::Map(i32 ToRgb, i32 FromRgb)
{

   u8* dst = (u8*)data();

   i64 size = scan_area();

   while (size--)
   {

      *dst = (::u8)(*dst == FromRgb ? ToRgb : *dst);

      dst += 4;

   }

   //return true;

}


void image::ToAlphaAndFill(i32 i, ::color::color color)
{

   u8* dst = (u8*)data();

   i64 size = scan_area();

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


void image::GrayToARGB(::color::color color)
{

   u8* dst = (u8*)data();

   i64 size = scan_area();

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


void image::BitBlt(::image* pimage, i32 op)
{

   if (op == 123) // zero dest rgb, invert alpha, and OR src rgb
   {

      throw ::exception(todo);
      //stretch(pimage);

   }

   //return true;

}


void image::BitBlt(int cxParam, int cyParam, ::image* pimage, i32 op)
{

   map();

   pimage->map();

   if (op == 1 && size() == pimage->size() && pimage->m_iScan == m_iScan) // op == 1 indicates can ignore cxParam and cyParam and perform full ::memory_copy
   {

      if (cyParam <= 0)
      {
       //  return false;

         return;

      }

      cyParam = minimum(cyParam, minimum(pimage->height(), height()));

#if defined(__APPLE__)

      ::memory_copy(&image32()[m_iScan / 4 * (pimage->height() - cyParam)], &pimage->image32()[m_iScan / 4 * (pimage->height() - cyParam)], cyParam * m_iScan);

#else

      ::memory_copy(image32(), pimage->image32(), cyParam * m_iScan);

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

      cxParam = minimum(cxParam, minimum(pimage->width(), width()));

      cyParam = minimum(cyParam, minimum(pimage->height(), height()));

      int iStrideSrc = pimage->m_iScan;

      if (iStrideSrc <= 0)
      {

         iStrideSrc = cxParam * sizeof(image32_t);

      }

      if (m_iScan == iStrideSrc && m_iScan == pimage->m_iScan)
      {

         ::memory_copy(image32(), pimage->image32(), cyParam * m_iScan);

      }
      else
      {

         int wsrc = iStrideSrc / sizeof(image32_t);
         int wdst = m_iScan / sizeof(image32_t);
         int cw = minimum(cxParam, width()) * sizeof(image32_t);

         int h = minimum(cyParam, height());


         image32_t* psrc = pimage->image32();
         image32_t* pdst = image32();

         for (int i = 0; i < h; i++)
         {

            ::memory_copy(pdst, psrc, cw);

            pdst += wdst;

            psrc += wsrc;

         }

      }

   }

   //return true;

}


void image::invert()
{

   map();

   i64 size = scan_area();
   ::u8* pb = (::u8*)data();

   for (i32 i = 0; i < size; i++)
   {
      pb[0] = 255 - pb[0];

      pb[1] = 255 - pb[1];

      pb[2] = 255 - pb[2];

      pb += 4;


   }

   //return true;

}


void image::channel_invert(::color::enum_channel echannel)
{

   i64 size = scan_area();

   ::u8* pb = (::u8*)data();


   pb += ((i32)echannel) % 4;


   for (i32 i = 0; i < size; i++)
   {

      *pb = 255 - *pb;


      pb += 4;


   }

   //return true;

}


void image::channel_multiply(double dRate, ::color::enum_channel echannel, bool bIfAlphaIgnorePreDivPosMult)
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
   i64 size = scan_area();
   ::u8* pb = (::u8*)data();

   pb += ((i32)echannel) % 4;

   i32 iDiv = 256 * 256;
   i32 iMul = (i32)(dRate * ((double)iDiv));
   i32 iRes;
   for (i64 i = 0; i < size; i++)
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


void image::channel_multiply(::color::enum_channel echannel, ::image* pimage, bool bIfAlphaIgnorePreDivPosMult)
{

   //      i64 size = area();

   map();

   pimage->map();
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {
      div_alpha();
   }

   ::u8* pb1 = (::u8*)data();


   ::u8* pb2 = (::u8*)pimage->data();


   pb1 += ((i32)echannel) % 4;


   pb2 += ((i32)echannel) % 4;


   for (i32 y = 0; y < height(); y++)
   {

      ::u8* pb1_2 = pb1 + (m_iScan * y);


      ::u8* pb2_2 = pb2 + (pimage->m_iScan * y);


      for (i32 x = 0; x < width(); x++)
      {

         int i = (::u8)(((u32)*pb1_2 * (u32)*pb2_2) / 255);

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


void image::channel_darken(::color::enum_channel echannel, ::image* pimage)
{

   i64 size = scan_area();

   ::u8* pb1 = (::u8*)data();

   ::u8* pb2 = (::u8*)pimage->data();

   pb1 += ((i32)echannel) % 4;

   pb2 += ((i32)echannel) % 4;

   for (i64 i = 0; i < size; i++)
   {
      *pb1 = *pb1 < *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void image::channel_lighten(::color::enum_channel echannel, ::image* pimage)
{

   i64 size = scan_area();
   ::u8* pb1 = (::u8*)data();

   ::u8* pb2 = (::u8*)pimage->data();

   pb1 += ((i32)echannel) % 4;

   pb2 += ((i32)echannel) % 4;

   for (i64 i = 0; i < size; i++)
   {
      *pb1 = *pb1 > *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void image::channel_from(::color::enum_channel echannel, ::image* pimage)
{

   map();

   pimage->map();

   i64 size = m_iScan * height() / sizeof(image32_t);

   i64 size_i64 = size / 64;

   ::u8* pb1 = (::u8*)data();

   ::u8* pb2 = (::u8*)pimage->data();

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

   //return true;

}


void image::channel_from(::color::enum_channel echannel, ::image* pimage, const ::rectangle_i32& rectangleParam)
{

   map();

   pimage->map();

   ::rectangle_i32 rectangle;

   if (!rectangle.intersect(this->rectangle(), rectangleParam))
   {

      return;

   }

   if (!rectangle.intersect(pimage->rectangle(), rectangle))
   {

      return;

   }

   ::u8* pb1 = ((::u8*)data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * m_iScan);


   ::u8* pb2 = ((::u8*)pimage->data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * pimage->m_iScan);


   pb1 += ((i32)echannel) % 4;


   pb2 += ((i32)echannel) % 4;


   int h = rectangle.height();

   int w = rectangle.width();

   for (int i = 0; i < h; i++)
   {

      ::u8* pb1_2 = pb1;


      ::u8* pb2_2 = pb2;


      for (int j = 0; j < w; j++)
      {

         *pb1_2 = *pb2_2;


         pb1_2 += 4;


         pb2_2 += 4;


      }

      pb1 += m_iScan;


      pb2 += pimage->m_iScan;


   }

   //return true;

}



void image::channel_multiply(::color::enum_channel echannel, ::image* pimage, const ::rectangle_i32& rectangleParam, bool bIfAlphaIgnorePreDivPosMult)
{

   map();

   pimage->map();

   ::rectangle_i32 rectangle;

   if (!rectangle.intersect(this->rectangle(), rectangleParam))
   {

      return;

   }

   if (!rectangle.intersect(pimage->rectangle(), rectangle))
   {

      return;

   }

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {

      div_alpha(rectangle.top_left(), rectangle.size());

   }

#ifdef __APPLE__

   ::u8* pb1 = ((::u8*)data()) + (rectangle.left * sizeof(image32_t) + (height() - rectangle.top - 1) * m_iScan);


   ::u8* pb2 = ((::u8*)pimage->data()) + (rectangle.left * sizeof(image32_t) + (pimage->height() - rectangle.top - 1) * pimage->m_iScan);


#else

   ::u8* pb1 = ((::u8*)data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * m_iScan);


   ::u8* pb2 = ((::u8*)pimage->data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * pimage->m_iScan);


#endif

   pb1 += ((i32)echannel) % 4;


   pb2 += ((i32)echannel) % 4;


   int h = rectangle.height();

   int w = rectangle.width();

   for (int i = 0; i < h; i++)
   {

      ::u8* pb1_2 = pb1;


      ::u8* pb2_2 = pb2;


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

   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {

      mult_alpha(rectangle.top_left(), rectangle.size());

   }

   //return true;

}


void image::fill_glass(i32 R, i32 G, i32 B, i32 A)
{

   u8* dst = (u8*)data();

   i64 size = scan_area();

   while (size--)
   {

      dst[0] = (::u8)(((B - dst[0]) * A + (dst[0] << 8)) >> 8);
      dst[1] = (::u8)(((G - dst[1]) * A + (dst[1] << 8)) >> 8);
      dst[2] = (::u8)(((R - dst[2]) * A + (dst[2] << 8)) >> 8);
      dst += 4;

   }

   //return true;

}


void image::fill_stippled_glass(i32 R, i32 G, i32 B)
{

   image32_t color(rgb(B, G, R), color_indexes());
   i32 w = width();
   i32 h = height();

   for (i32 j = 0; j < w; j++)
   {
      for (i32 i = 0; i < h; i++)
      {
         data()[j * w + i] = ((i + j) & 0x1) ? data()[j * w + i] : color;
      }
   }

   //return true;

}


//void image::to(::image * pimage) const
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


//void image::copy_from(::image* pimage, ::eobject eobjectCreate)
//{
//
//   if (size() != pimage->size())
//   {
//
//      create(pimage->size(), eobjectCreate);
//
//   }
//   else
//   {
//
//      m_eobject = eobjectCreate;
//
//   }
//
//   //pimage->defer_realize(pimage->get_graphics());
//   //defer_realize(pimage->get_graphics());
//
//   map();
//
//   ((::image*)pimage)->map();
//   // If DibSize Wrong Re-create image_impl
//   // do Paste
//
//   if (m_iScan == pimage->m_iScan)
//   {
//
//      ::memory_copy(data(), pimage->data(), height() * m_iScan);
//
//   }
//   else
//   {
//
//      int iScan = minimum(m_iScan, pimage->m_iScan);
//
//      for (int i = 0; i < height(); i++)
//      {
//
//         ::memory_copy(&((u8*)data())[m_iScan * i], &((u8*)pimage->data())[pimage->m_iScan * i], iScan);
//
//      }
//
//   }
//
//   return true;
//
//}


//void image::bitmap_blend(::draw2d::graphics* pgraphics, const ::rectangle_i32& rectangle)
//{
//
//   image_source imagesource(pgraphics);
//
//
//   return pgraphics->stretch(rectangle, get_graphics()) != false;
//
//
//}


void image::color_blend(::color::color color, ::u8 bAlpha)
{

   u8* dst = (u8*)data();

   i64 size = scan_area();

   ::u32 dwB = color.u8_blue();
   ::u32 dwG = color.u8_green();
   ::u32 dwR = color.u8_red();

   u32 dwB_ = dwB << 8;
   u32 dwG_ = dwG << 8;
   u32 dwR_ = dwR << 8;

   while (size--)
   {
      dst[0] = (::u8)(((dst[0] - dwB) * bAlpha + dwB_) >> 8);
      dst[1] = (::u8)(((dst[1] - dwG) * bAlpha + dwG_) >> 8);
      dst[2] = (::u8)(((dst[2] - dwG) * bAlpha + dwR_) >> 8);
      dst += 4;
   }

   //return true;

}


void image::op(string str)
{

   if (str == "horz-__swap")
   {

      map();

      // half width
      int hx = width() / 2;
      // aligned scan
      int as = m_iScan / sizeof(image32_t);

      for (index i = 0; i < height(); i++)
      {
         for (index j = 0; j < hx; j++)
         {
            __swap(image32()[i * as + j], image32()[i * as + width() - j]);
         }
      }

      //return true;
   }

   //return false;

}


void image::Blend(::image* pimage, i32 A)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   i64 size = scan_area();

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


void image::Blend(::image* pDib, ::image* DibA, i32 A)
{
   if (size() != pDib->size() ||
      size() != DibA->size())
      throw ::exception(error_wrong_state);

   u8* src = (u8*)pDib->data();
   u8* dst = (u8*)data();
   u8* alf = (u8*)DibA->data();
   i64 size = scan_area();

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


void image::Blend(::image* pDib, ::image* DibA)
{
   if (size() != pDib->size() ||
      size() != DibA->size())
      throw ::exception(error_wrong_state);

   map();
   pDib->map();
   DibA->map();

   u8* src = (u8*)pDib->data();
   u8* dst = (u8*)data();
   u8* alf = ((u8*)DibA->data()) + 3;
   i64 size = scan_area();

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



void image::blend(::image* pimage, ::image* pimageRate)
{
   if (size() != pimage->size() ||
      size() != pimageRate->size())
      throw ::exception(error_wrong_state);

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   u8* alf = (u8*)pimageRate->data();
   i64 size = scan_area();

   while (size >= 2)
   {
      dst[00] = (::u8)(((((i32)src[00] - (i32)dst[00]) * (i32)alf[00]) + (i32)dst[00] * (i32)255) / 255);
      dst[01] = (::u8)(((((i32)src[01] - (i32)dst[01]) * (i32)alf[01]) + (i32)dst[01] * (i32)255) / 255);
      dst[02] = (::u8)(((((i32)src[02] - (i32)dst[02]) * (i32)alf[02]) + (i32)dst[02] * (i32)255) / 255);
      dst[03] = (::u8)(((((i32)src[03] - (i32)dst[03]) * (i32)alf[03]) + (i32)dst[03] * (i32)255) / 255);
      dst[04] = (::u8)(((((i32)src[04] - (i32)dst[04]) * (i32)alf[04]) + (i32)dst[04] * (i32)255) / 255);
      dst[05] = (::u8)(((((i32)src[05] - (i32)dst[05]) * (i32)alf[05]) + (i32)dst[05] * (i32)255) / 255);
      dst[06] = (::u8)(((((i32)src[06] - (i32)dst[06]) * (i32)alf[06]) + (i32)dst[06] * (i32)255) / 255);
      dst[07] = (::u8)(((((i32)src[07] - (i32)dst[07]) * (i32)alf[07]) + (i32)dst[07] * (i32)255) / 255);
      dst += 4 * 2;
      src += 4 * 2;
      alf += 4 * 2;
      size -= 2;
   }
   while (size > 0)
   {
      dst[00] = (::u8)(((((i32)src[00] - (i32)dst[00]) * (i32)alf[00]) + (i32)dst[00] * (i32)255) / 255);
      dst[01] = (::u8)(((((i32)src[01] - (i32)dst[01]) * (i32)alf[01]) + (i32)dst[01] * (i32)255) / 255);
      dst[02] = (::u8)(((((i32)src[02] - (i32)dst[02]) * (i32)alf[02]) + (i32)dst[02] * (i32)255) / 255);
      dst[03] = (::u8)(((((i32)src[03] - (i32)dst[03]) * (i32)alf[03]) + (i32)dst[03] * (i32)255) / 255);
      dst += 4;
      src += 4;
      alf += 4;
      size--;
   }

   //return true;
}


void image::Darken(::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   i64 size = scan_area();

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


void image::Difference(::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   i64 size = scan_area();

   while (size--)
   {
      i32 Difference;
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


void image::Lighten(::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   i64 size = scan_area();

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
void image::lighten(double dRate)
{
   u8* dst = (u8*)data();
   i64 size = scan_area();

   while (size--)
   {
      dst[0] += (::u8)((dst[3] - dst[0]) * dRate);
      dst[1] += (::u8)((dst[3] - dst[1]) * dRate);
      dst[2] += (::u8)((dst[3] - dst[2]) * dRate);
      dst += 4;
   }

   //return true;

}


void image::Multiply(::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   i64 size = scan_area();

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


void image::Screen(::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   u8* src = (u8*)pimage->data();
   u8* dst = (u8*)data();
   i64 size = scan_area();

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


void image::copy_from_no_create(::image * pimage, const ::point_i32 & point)
{

   ::size_i32 s(pimage->size() - point);

   auto sizeCopy = ::size_i32(::minimum(size().cx(), s.cx()), ::minimum(size().cy(), s.cy()));

   if (sizeCopy.area() > 0)
   {

      image_source imagesource(pimage, { point, sizeCopy });

      ::rectangle_f64 rectangle(sizeCopy);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      g()->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   //return true;

}


void image::copy_from_no_create(::image * pimage)
{

   return copy_from_no_create(pimage, {});

}



void image::copy_from(::image* pimage, const ::point_i32  & point, ::enum_flag eflagCreate)
{

   ::size_i32 s(pimage->size() - point);

   if (size() != s)
   {

      create(s, eflagCreate);
      //if (!create(s))
      //{

      //   return false;

      //}

   }

   copy_from_no_create(pimage, point);

}


void image::copy_from(::image * pimage, enum_flag eflagCreate)
{

   return copy_from(pimage, {}, eflagCreate);

}


//void image::copy_to(::image* pimage, const point_i32 & point)
//{
//
//   return pimage->copy_from(this);
//
//}


void image::fill_rectangle(const ::rectangle_i32& rectangle, i32 R, i32 G, i32 B)
{

   i32 x = rectangle.left;

   i32 y = rectangle.top;

   i32 w = rectangle.width();

   i32 h = rectangle.height();

   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + w) < width()) ? w : width() - x;
   i32 greekdeltay = ((y + h) < height()) ? h : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Fill return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
   {

      return;

   }

   map();

   image32_t* dst = data() + (py * width()) + px;

   while (greekdeltay--)
   {

      for (i32 i = 0; i < greekdeltax; i++)
      {

         ((u8*)&dst[i])[0] = R;
         ((u8*)&dst[i])[1] = G;
         ((u8*)&dst[i])[2] = B;

      }

      dst += m_iScan / sizeof(image32_t);

   }

   //return true;

}


void image::fill_rectangle(const ::rectangle_i32& rectangle, ::color::color color)
{

   if (m_bMapped)
   {

      i32 x = rectangle.left;

      i32 y = rectangle.top;

      i32 w = rectangle.width();

      i32 h = rectangle.height();

      ::image32_t u32Color(color, color_indexes());

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
      i32 greekdeltax;
      greekdeltax = ((px + w) < width()) ? w : width() - px;
      i32 greekdeltay;
      greekdeltay = ((py + h) < height()) ? h : height() - py;
      greekdeltax = (px >= 0) ? greekdeltax : greekdeltax + x;
      greekdeltay = (py >= 0) ? greekdeltay : greekdeltay + y;

      // If Nothing to Fill return
      if ((greekdeltax <= 0) || (greekdeltay <= 0))
         return;

      // Prepare buffer Address
      image32_t* dst = data() + (py * width()) + px;

      while (greekdeltay--)
      {

         for (i32 i = 0; i < greekdeltax; i++)
         {

            dst[i] = u32Color;

         }

         dst += m_iScan / sizeof(image32_t);

      }

   }
   else
   {

      ::draw2d::enum_alpha_mode emodeOld = get_graphics()->alpha_mode();

      if (get_graphics()->alpha_mode() != ::draw2d::e_alpha_mode_set)
      {

         get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      }

      get_graphics()->fill_rectangle(rectangle, color);

      if (get_graphics()->alpha_mode() != emodeOld)
      {

         get_graphics()->set_alpha_mode(emodeOld);

      }

   }

   //return true;

}


void image::fill_glass_rect(const ::rectangle_i32& rectangle, i32 R, i32 G, i32 B, i32 A)

{

   i32 x = rectangle.left;

   i32 y = rectangle.top;

   i32 w = rectangle.width();

   i32 h = rectangle.height();


   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + w) < width()) ? w : width() - x;
   i32 greekdeltay = ((y + h) < height()) ? h : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to FillGlass return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Address
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do FillGlass
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[0] = (::u8)(((B - dst[0]) * A + (dst[0] << 8)) >> 8);
         dst[1] = (::u8)(((G - dst[1]) * A + (dst[1] << 8)) >> 8);
         dst[2] = (::u8)(((R - dst[2]) * A + (dst[2] << 8)) >> 8);
         dst += 4;
      }

      dst += (width() - greekdeltax) << 2;

   }

   //return true;

}


void image::fill_stippled_glass_rect(const ::rectangle_i32& rectangle, i32 R, i32 G, i32 B)

{

   i32 x = rectangle.left;

   i32 y = rectangle.top;

   i32 w = rectangle.width();

   i32 h = rectangle.height();


   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + w) < width()) ? w : width() - x;
   i32 greekdeltay = ((y + h) < height()) ? h : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to FillStippledGlass return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Address
   image32_t* dst = data() + (py * width()) + px;
   image32_t color(rgb(B, G, R), color_indexes());

   // Do FillStippledGlass
   for (i32 j = 0; j < greekdeltay; j++)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[i] = ((i + j) & 0x1) ? dst[i] : color;
      }
      dst += width();
   }

   //return true;

}


void image::BlendRect(::image* pimage, i32 x, i32 y, i32 A)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 greekdeltay = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Blend return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Addresses
   u8* src = (u8*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do Blend
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[0] = (::u8)(((src[0] - dst[0]) * A + (dst[0] << 8)) >> 8);
         dst[1] = (::u8)(((src[1] - dst[1]) * A + (dst[1] << 8)) >> 8);
         dst[2] = (::u8)(((src[2] - dst[2]) * A + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - greekdeltax) << 2;
      src += (pimage->width() - greekdeltax) << 2;
   }

   //return true;

}


void image::DarkenRect(::image* pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 greekdeltay = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Darken return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Addresses
   u8* src = (u8*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do Darken
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[0] = (::u8)((src[0] < dst[0]) ? src[0] : dst[0]);
         dst[1] = (::u8)((src[1] < dst[1]) ? src[1] : dst[1]);
         dst[2] = (::u8)((src[2] < dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - greekdeltax) << 2;
      src += (pimage->width() - greekdeltax) << 2;
   }

   //return true;

}


void image::DifferenceRect(::image* pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 greekdeltay = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Difference return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Addresses
   u8* src = (u8*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do Difference
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         i32 Difference;
         Difference = src[0] - dst[0];
         dst[0] = (::u8)((Difference < 0) ? -Difference : Difference);
         Difference = src[1] - dst[1];
         dst[1] = (::u8)((Difference < 0) ? -Difference : Difference);
         Difference = src[2] - dst[2];
         dst[2] = (::u8)((Difference < 0) ? -Difference : Difference);
         dst += 4;
         src += 4;
      }
      dst += (width() - greekdeltax) << 2;
      src += (pimage->width() - greekdeltax) << 2;
   }

   //return true;

}


void image::LightenRect(::image* pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 greekdeltay = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Lighten return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Addresses
   u8* src = (u8*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do Lighten
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[0] = (::u8)((src[0] > dst[0]) ? src[0] : dst[0]);
         dst[1] = (::u8)((src[1] > dst[1]) ? src[1] : dst[1]);
         dst[2] = (::u8)((src[2] > dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - greekdeltax) << 2;
      src += (pimage->width() - greekdeltax) << 2;
   }

   return;

}


void image::MultiplyRect(::image* pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 greekdeltay = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Multiply return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Addresses
   u8* src = (u8*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do Multiply
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[0] = (::u8)(((src[0]) * (dst[0])) >> 8);
         dst[1] = (::u8)(((src[1]) * (dst[1])) >> 8);
         dst[2] = (::u8)(((src[2]) * (dst[2])) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - greekdeltax) << 2;
      src += (pimage->width() - greekdeltax) << 2;
   }

   //return true;

}


void image::ScreenRect(::image* pimage, i32 x, i32 y)
{
   // Clip Rect
   i32 px = (x >= 0) ? x : 0;
   i32 py = (y >= 0) ? y : 0;
   i32 greekdeltax = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   i32 greekdeltay = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   greekdeltax = (x >= 0) ? greekdeltax : greekdeltax + x;
   greekdeltay = (y >= 0) ? greekdeltay : greekdeltay + y;

   // If Nothing to Screen return
   if ((greekdeltax <= 0) || (greekdeltay <= 0))
      return;

   // Prepare buffer Addresses
   u8* src = (u8*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   u8* dst = (u8*)data() + ((py * width()) + px) * 4;

   // Do Screen
   while (greekdeltay--)
   {
      for (i32 i = 0; i < greekdeltax; i++)
      {
         dst[0] = (::u8)(255 - (((255 - src[0]) * (255 - dst[0])) >> 8));
         dst[1] = (::u8)(255 - (((255 - src[1]) * (255 - dst[1])) >> 8));
         dst[2] = (::u8)(255 - (((255 - src[2]) * (255 - dst[2])) >> 8));
         dst += 4;
         src += 4;
      }
      dst += (width() - greekdeltax) << 2;
      src += (pimage->width() - greekdeltax) << 2;
   }

   //return true;

}


//////////////////////////////////////////////////////////////////////
// Line Functions
//////////////////////////////////////////////////////////////////////

/*void image::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
{
i32 greekdeltax, greekdeltay, k1, k2, d, x, y;
image32_t color=rgb ( B, G, R );

greekdeltax=x2-x1;
greekdeltay=y2-y1;
d=(greekdeltay<<1)-greekdeltax;
k1=greekdeltay<<1;
k2=(greekdeltay-greekdeltax)<<1;
x=x1;
y=y1;

data()[y*width()+x]=color;
while (x<greekdeltax)
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


void image::horizontal_line(i32 y, ::color::color color, i32 x1, i32 x2)
{
   if (width() == 0)
      return;
   map();
   x1 %= width();
   x2 %= width();
   if (x2 < 0)
      x2 += width();
   if (x1 < 0)
      x1 += width();
   image32_t u32ImageColor(color, color_indexes());

#ifdef __APPLE__

   image32_t* pdata = (image32_t*)((::u8 *) data() + (height() - y - 1) * (m_iScan));

#else

   image32_t* pdata = (image32_t*)((::u8 *) data() + y * (m_iScan));

#endif

   for (i32 x = x1; x <= x2; x++)
   {

      *pdata = u32ImageColor;

      pdata++;

   }

   //return true;

}


void image::Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B)
{
   i32 d, x, y, aura, ay, sx, sy, greekdeltax, greekdeltay;
   image32_t color(rgb(B, G, R), color_indexes());

   greekdeltax = x2 - x1;
   aura = abs(greekdeltax) << 1;
   sx = (greekdeltax < 0) ? -1 : 1;
   greekdeltay = y2 - y1;
   ay = abs(greekdeltay) << 1;
   sy = (greekdeltay < 0) ? -1 : 1;
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


void image::LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A)
{
   i32 d, x, y, aura, ay, sx, sy, greekdeltax, greekdeltay;
   //      image32_t color=rgb ( B, G, R );
   u8* dst = (u8*)data();

   greekdeltax = x2 - x1;
   aura = abs(greekdeltax) << 1;
   sx = (greekdeltax < 0) ? -1 : 1;
   greekdeltay = y2 - y1;
   ay = abs(greekdeltay) << 1;
   sy = (greekdeltay < 0) ? -1 : 1;
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


void image::Mask(::color::color colorMask, ::color::color colorInMask, ::color::color colorOutMask)
{
   image32_t crFind(colorMask, color_indexes());
   image32_t crSet(colorInMask, color_indexes());
   image32_t crUnset(colorOutMask, color_indexes());

   i64 size = scan_area();

   for (i32 i = 0; i < size; i++)
      if (data()[i] == crFind)
         data()[i] = crSet;
      else
         data()[i] = crUnset;

   //return true;

}


void image::transparent_color(::color::color color)
{

   image32_t crFind(color, color_indexes());

   i64 iSize = scan_area();

   for (i32 i = 0; i < iSize; i++)
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


void image::channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, ::color::enum_channel echannel)
{

   i32 size = (m_iScan / sizeof(image32_t)) * height();

   uchar* puch = (uchar*)data();

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

   //return true;

}


::color::color image::GetPixel(i32 x, i32 y)
{

   map();

   ::u32 u32 = (data() + x + line(y) * (m_iScan / sizeof(image32_t)))->m_u32;

   u8* p = (u8*)&u32;

   int iOpacity = p[m_colorindexes.m_u8IndexOpacity];

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
void image::RadialFill(::u8 alpha, ::u8 red, ::u8 green, ::u8 blue, i32 xCenter, i32 yCenter, i32 iRadius)
{

   if (iRadius == 0)
   {

      //return false;

      return;

   }

   /*if(version == 0)
   {

   i32 iR = iRadius - 1;

   i32 xL = xCenter - iR;
   i32 xU = xCenter + iR;
   i32 yL = yCenter - iR;
   i32 yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(image32_t))) xU = m_Size.(m_iScan / sizeof(image32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   u8 *dst = ((u8 *)(data() + xL + yL * m_Size.(m_iScan / sizeof(image32_t))));
   u32 dwAdd = ((m_Size.(m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
   i32 size=m_Size.(m_iScan / sizeof(image32_t))*m_Size.height();
   double iLevel;

   i32 greekdeltax, greekdeltay;
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
   greekdeltax = abs(x - xCenter);
   greekdeltay = abs(y - yCenter);
   isqrt((greekdeltax * greekdeltax) + (greekdeltay * greekdeltay), &dr, &dq);
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


            pb[x + y * iRadius] = (::u8)b;

            pb[y + x * iRadius] = (::u8)b;

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


      u8* dst = ((u8*)(data() + xL + yL * (m_iScan / sizeof(image32_t))));
      u32 dwAdd = (((m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
      //         i64 size = area();

      i32 greekdeltax, greekdeltay;

      // Top Left

      for (y = yL; y <= yU; y++)
      {
         for (x = xL; x <= xU; x++)
         {
            greekdeltax = abs(x - xCenter);
            greekdeltay = abs(y - yCenter);
            b = pb[greekdeltax + greekdeltay * iRadius];

            dst[0] = ::u8(blue * b / 255);
            dst[1] = ::u8(green * b / 255);
            dst[2] = ::u8(red * b / 255);
            dst[3] = ::u8(alpha * b / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

      free(pbAlloc);

   }

   //return true;

}


void image::RadialFill(
   ::u8 alpha1, ::u8 red1, ::u8 green1, ::u8 blue1,
   ::u8 alpha2, ::u8 red2, ::u8 green2, ::u8 blue2,
   i32 xCenter, i32 yCenter, i32 iRadius)
{
   if (iRadius == 0)
      //return false;
      return;

   map();
   /*if(version == 0)
   {

   i32 iR = iRadius - 1;

   i32 xL = xCenter - iR;
   i32 xU = xCenter + iR;
   i32 yL = yCenter - iR;
   i32 yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(image32_t))) xU = m_Size.(m_iScan / sizeof(image32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   u8 *dst = ((u8 *)(data() + xL + yL * m_Size.(m_iScan / sizeof(image32_t))));
   u32 dwAdd = ((m_Size.(m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
   i32 size=m_Size.(m_iScan / sizeof(image32_t))*m_Size.height();
   double iLevel;

   i32 greekdeltax, greekdeltay;
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
   greekdeltax = abs(x - xCenter);
   greekdeltay = abs(y - yCenter);
   isqrt((greekdeltax * greekdeltax) + (greekdeltay * greekdeltay), &dr, &dq);
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
      //               pb[x + y * iRadius] = (::u8) b;

      //               pb[y + x * iRadius] = (::u8) b;

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


      u8* dst = ((u8*)(data() + xL + yL * (m_iScan / sizeof(image32_t))));
      u32 dwAdd = (((m_iScan / sizeof(image32_t)) - xU) + xL) * 4;
      //         i64 size = area();

      double greekdeltax, greekdeltay;

      double dRadius = 255.0 / (double)iRadius;

      ::u8 bComp;

      int b;

      // Top Left

      int y;
      int x;

      for (y = yL; y < yU; y++)
      {
         for (x = xL; x < xU; x++)
         {
            greekdeltax = abs(x - xCenter);
            greekdeltay = abs(y - yCenter);
            b = (int)(sqrt((greekdeltax * greekdeltax) + (greekdeltay * greekdeltay)) * dRadius);

            if (b > 255)
            {
               b = 255;
            }

            bComp = 255 - b;
            dst[0] = ::u8(((blue1 * bComp) + (blue2 * b)) / 255);
            dst[1] = ::u8(((green1 * bComp) + (green2 * b)) / 255);
            dst[2] = ::u8(((red1 * bComp) + (red2 * b)) / 255);
            dst[3] = ::u8(((alpha1 * bComp) + (alpha2 * b)) / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

   }

   //return true;

}



void image::SetIconMask(::draw2d::icon* picon, i32 cx, i32 cy)
{

   //      throw ::exception(todo);
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
   //      throw ::exception(todo);
   //
   //      // xxx todo pimage1->create(width(), height());
   //
   //      pimage1->Fill(0, 255, 255, 255);
   //
   //#ifdef UNIVERSAL_WINDOWS
   //
   //      throw ::interface_only();
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
   //      throw ::exception(todo);
   //
   //      // xxx todo pimage2->create(width(), height());
   //      pimage2->Fill(0, 0, 0, 0);
   //
   //#ifdef UNIVERSAL_WINDOWS
   //
   //      throw ::interface_only();
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
   //      throw ::exception(todo);
   //
   //      // xxx todo imageM.create(width(), height());
   //
   //#ifdef UNIVERSAL_WINDOWS
   //
   //      throw ::interface_only();
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
   //      u8 * r1 = (u8 *)pimage1->data();
   //      u8 * r2 = (u8 *)pimage2->data();
   //      u8 * srcM = (u8 *)imageM.data();
   //      u8 * dest = (u8 *)data();
   //      i32 iSize = width()*height();
   //
   //      ::u8 b;
   //      ::u8 bMax;
   //      while (iSize-- > 0)
   //      {
   //         if (srcM[0] == 255)
   //         {
   //            bMax = 0;
   //         }
   //         else
   //         {
   //            bMax = 0;
   //            b = (::u8)(r1[0] - r2[0]);
   //            bMax = maximum(b, bMax);
   //            b = (::u8)(r1[1] - r2[1]);
   //            bMax = maximum(b, bMax);
   //            b = (::u8)(r1[2] - r2[2]);
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

   //return true;

}


void image::rotate(const ::angle_f64 & angle, double dScale)
{

   image_pointer pimage = this->clone();

   rotate(pimage, angle, dScale);

}


void image::rotate(image * pimage, const ::angle_f64 & angle, double dScale)
{

   if (dScale == 1.0)
   {

      if (angle.degree() == 90.0)
      {

         create({ pimage->height(), pimage->width() });

         //if (!create({ pimage->height(), pimage->width() }))
         //{

         //   return false;

         //}

         map();

         pimage->map();

         i32 cx = pimage->width();

         i32 cy = pimage->height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (i32 i = 0; i < cx; i++)
         {

            for (i32 j = 0; j < cy; j++)
            {

               image32()[i * s + j] = pimage->image32()[(cy - j - 1) * srcS + i];

            }

         }

         //return pimage;

         return;

      }
      else if (angle.degree() == 180.0)
      {

         create(pimage->size());

         map();

         pimage->map();

         i32 cx = width();

         i32 cy = height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (i32 i = 0; i < cy; i++)
         {

            for (i32 j = 0; j < cx; j++)
            {

               image32()[(cy - i - 1) * s + (cx - j - 1)] = pimage->image32()[i * srcS + j];

            }

         }

         return;

      }
      else if (angle.degree() == 270.0)
      {

         create({ pimage->height(), pimage->width() });

         map();

         pimage->map();

         i32 cx = pimage->width();

         i32 cy = pimage->height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (i32 i = 0; i < cx; i++)
         {

            for (i32 j = 0; j < cy; j++)
            {

               image32()[i * s + j] = pimage->image32()[j * srcS + (cx - i - 1)];

            }

         }

         return;

      }

   }

   double o = angle.radian();

   int a = (int)(::fabs((double)pimage->width() * ::sin(o)) + ::fabs((double)pimage->height() * ::cos(o)));

   int b = (int)(::fabs((double)pimage->width() * ::cos(o)) + ::fabs((double)pimage->height() * ::sin(o)));

   a = (int)(a * dScale);

   b = (int)(b * dScale);

   if (a <= 0 || b <= 0)
   {

      //return nullptr;

      return;

   }

   create({ b, a });

   map();

   pimage->map();

   int wSource = pimage->width();

   int hSource = pimage->height();

   auto pdataSource = pimage->image32();

   int wTarget = width();

   int hTarget = height();

   auto pdataTarget = image32();

   i32 l = maximum(wTarget, hTarget);

   i32 jmax = minimum(l, hTarget / 2);

   i32 jmin = -jmax;

   i32 imax = minimum(l, wTarget / 2);

   i32 imin = -imax;

   int xoff = wSource / 2;

   int yoff = hSource / 2;

   //double o = dAngle * pi() / 180.0;

   int ioff = wTarget / 2;

   int joff = hTarget / 2;

   int dsw = m_iScan / sizeof(image32_t);

   int ssw = pimage->m_iScan / sizeof(image32_t);

   double dCos = ::cos(o) * dScale;

   double dSin = ::sin(o) * dScale;

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

}


image_pointer image::rotated(const ::angle_f64 & angle, double dScale)
{

   if (dScale == 1.0)
   {

      if (angle.degree() == 90.0)
      {

            auto pimage = m_pcontext->m_pauracontext->create_image({height(), width() });

            //if (!create({ pimage->height(), pimage->width() }))
            //{

            //   return false;

            //}

            map();

            pimage->map();

            i32 cx = width();

            i32 cy = height();

            int s = m_iScan / sizeof(image32_t);

            int srcS = pimage->m_iScan / sizeof(image32_t);

            for (i32 i = 0; i < cx; i++)
            {

               for (i32 j = 0; j < cy; j++)
               {

                  pimage->image32()[i * s + j] = image32()[(cy - j - 1) * srcS + i];

               }

            }

            return pimage;

         }

      else  if (angle.degree() == 180.0)
      {

         auto pimage = m_pcontext->m_pauracontext->create_image(size());



         map();

         pimage->map();

         i32 cx = width();

         i32 cy = height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (i32 i = 0; i < cy; i++)
         {

            for (i32 j = 0; j < cx; j++)
            {

               pimage->image32()[(cy - i - 1) * s + (cx - j - 1)] = image32()[i * srcS + j];

            }

         }

         return pimage;
      }
      else if (angle.degree() ==270.0)
      {

               auto pimage = m_pcontext->m_pauracontext->create_image({ height(), width() });

            map();

            pimage->map();

            i32 cx = width();

            i32 cy = height();

            int s = m_iScan / sizeof(image32_t);

            int srcS = pimage->m_iScan / sizeof(image32_t);

            for (i32 i = 0; i < cx; i++)
            {

               for (i32 j = 0; j < cy; j++)
               {

                  pimage->image32()[i * s + j] = image32()[j * srcS + (cx - i - 1)];

               }

            }

            return pimage;

         }

   }

   double o = angle.radian();

   int a = (int)(::fabs((double)width() * ::sin(o)) + ::fabs((double)height() * ::cos(o)));

   int b = (int)(::fabs((double)width() * ::cos(o)) + ::fabs((double)height() * ::sin(o)));

   a = (int) (a * dScale);

   b = (int) (b * dScale);

   if (a <= 0 || b <= 0)
   {

      return nullptr;

   }

   auto pimage = m_pcontext->m_pauracontext->create_image({ b, a });

   map();

   pimage->map();

   int wSource = width();

   int hSource = height();

   auto pdataSource = image32();

   int wTarget = pimage->width();

   int hTarget = pimage->height();

   auto pdataTarget = pimage->image32();

   i32 l = maximum(wTarget, hTarget);

   i32 jmax = minimum(l, hTarget / 2);

   i32 jmin = -jmax;

   i32 imax = minimum(l, wTarget / 2);

   i32 imin = -imax;

   int xoff = wSource / 2;

   int yoff = hSource / 2;

   //double o = dAngle * pi() / 180.0;

   int ioff = wTarget / 2;

   int joff = hTarget / 2;

   int dsw = m_iScan / sizeof(image32_t);

   int ssw = pimage->m_iScan / sizeof(image32_t);

   double dCos = ::cos(o) * dScale;

   double dSin = ::sin(o) * dScale;

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

   return pimage;

}


//image_pointer image::rotated(const angle& angle, double dScale)
//{
//
//   map();
//
//   pimage->map();
//
//   int wSource = pimage->width();
//
//   int hSource = pimage->height();
//
//   auto pdataSource = pimage->image32();
//
//   int wTarget = width();
//
//   int hTarget = height();
//
//   auto pdataTarget = image32();
//
//   if (wSource < 2 || hSource < 2 || ::is_null(pdataSource)) return;
//
//   if (wTarget < 2 || hTarget < 2 || ::is_null(pdataTarget)) return;
//
//   i32 l = maximum(wTarget, hTarget);
//
//   i32 jmax = minimum(l, hTarget / 2);
//
//   i32 jmin = -jmax;
//
//   i32 imax = minimum(l, wTarget / 2);
//
//   i32 imin = -imax;
//
//   int xoff = wSource / 2;
//
//   int yoff = hSource / 2;
//
//   double o = dAngle * pi() / 180.0;
//
//   int ioff = wTarget / 2;
//
//   int joff = hTarget / 2;
//
//   int dsw = m_iScan / sizeof(image32_t);
//
//   int ssw = pimage->m_iScan / sizeof(image32_t);
//
//   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
//
//   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
//
//   int x;
//
//   int y;
//
//   for (i32 j = jmin; j < jmax; j++)
//   {
//
//      for (i32 i = imin; i < imax; i++)
//      {
//
//         x = (i32)fabs((dCos * i - dSin * j) + xoff);
//
//         y = (i32)fabs((dSin * i + dCos * j) + yoff);
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

void image::Rotate034(::image* pimage, double dAngle, double dScale)
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

   i32 ihdstmid = (::i32)hdstmid;

   auto hsrcmid = hsrc / 2.0;
   auto wsrcmid = wsrc / 2.0;

   //i32 l = maximum(w, h);

   i32 jdstmin = (::i32)-hdstmid;
   i32 jdstmax = jdstmin + hdst;
   i32 idstmin = (::i32)-wdstmid;
   i32 idstmax = idstmin + wdst;

   i32 k = 0;

   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;

   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;

   auto pdataSrc = pimage->data();

   auto pdataDst = data();

   int strideSrc = pimage->m_iScan / sizeof(image32_t);

   int strideDst = m_iScan / sizeof(image32_t);

   for (i32 jdst = jdstmin; jdst < jdstmax; jdst++)
   {

      int lineDst = (i32)(jdst + ihdstmid);

      if (lineDst < 0)
      {

         output_debug_string("image::Rotate034 lineDst < 0");

      }

      image32_t* pline = pdataDst + (lineDst * strideDst);

      for (i32 idst = idstmin; idst < idstmax; idst++)
      {

         i32 xsrc, ysrc;

         double dj = jdst;
         double di = idst;

         xsrc = (i32)((dCos * di - dSin * dj) + wsrcmid);
         ysrc = (i32)((dSin * di + dCos * dj) + hsrcmid);

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


//void image::rotated(::image* pimage, const ::rectangle_i32& rectangle, double dAngle, double dScale)
//
//{
//
//   i32 l = maximum(width(), height());
//
//   i32 jmax = minimum(l, height() / 2);
//   i32 jmin = -jmax;
//   i32 imax = minimum(l, width() / 2);
//   i32 imin = -imax;
//
//   i32 joff = height() / 2 + rectangle.left;
//
//   i32 ioff = width() / 2 + rectangle.top;
//
//   int stride_unit = m_iScan / sizeof(image32_t);
//   //i32 iAngle = iStep % 360;
//   //i32 iAngle = iStep;
//   //i32 iAngle = 1;
//   //i32 k = 0;
//
//   /*     for ( i32 j=jmin; j<jmax; j++ )
//   {
//   for ( i32 i=imin; i<imax; i++ )
//   {
//   i32 x, y;
//
//   // A Combination of a 2d Translation/rotation/Scale Matrix
//   x=i32(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
//   y=i32(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
//   data()[(j+joff)*width()+(i+ioff)]=
//   pimage->data()[abs(y%height())*width()+abs(x%width())];
//   //k++;
//   }
//   (j+joff)*width()+(i+ioff)
//   }*/
//
//   i32 k = 0;
//   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
//   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
//   i32 cx1 = width() - 1;
//   i32 cy1 = height() - 1;
//   for (i32 j = jmin; j < jmax; j++)
//   {
//      for (i32 i = imin; i < imax; i++)
//      {
//         i32 x, y;
//
//         // A Combination of a 2d Translation/rotation/Scale Matrix
//         //x=abs((i32(dCos * i - dSin * j) + ioff) % width());
//         //y=abs((i32(dSin * i + dCos * j) + joff) % height());
//
//         x = (i32)fabs((dCos * i - dSin * j) + ioff);
//         y = (i32)fabs((dSin * i + dCos * j) + joff);
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
//         data()[(j + joff) * stride_unit + (i + ioff)] = pimage->data()[y * stride_unit + x];
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



//void image::rotate90()
//{
//
//   ::image_pointer pimage = clone();
//
//   return rotate90(pimage);
//
//}
//
//
//void image::rotate180()
//{
//
//   ::image_pointer pimage = clone();
//
//   return rotate180(pimage);
//
//}
//
//
//void image::rotate270()
//{
//
//   ::image_pointer pimage = clone();
//
//   return rotate270(pimage);
//
//}


void image::e_rotate_90_flip_horizontally(::image* pimage)
{

   create(pimage->size());

   map();

   pimage->map();

   i32 cx = pimage->width();

   i32 cy = pimage->height();

   int s = m_iScan / sizeof(image32_t);

   int srcS = pimage->m_iScan / sizeof(image32_t);

   for (i32 i = 0; i < cx; i++)
   {

      for (i32 j = 0; j < cy; j++)
      {

         image32()[i * s + j] = pimage->image32()[j * srcS + i];

      }

   }

}


void image::e_rotate_180_flip_horizontally(::image* pimage)
{

   create(pimage->size());
   
   map();

   pimage->map();

   i32 cx = width();

   i32 cy = height();

   int s = m_iScan / sizeof(image32_t);

   int srcS = pimage->m_iScan / sizeof(image32_t);

   for (i32 i = 0; i < cy; i++)
   {

      for (i32 j = 0; j < cx; j++)
      {

         image32()[i * s + j] = pimage->image32()[(cy - i - 1) * srcS + j];

      }

   }

}


void image::e_rotate_270_flip_horizontally(::image* pimage)
{

   create(pimage->size());

   map();

   pimage->map();

   i32 cx = pimage->width();

   i32 cy = pimage->height();

   int s = m_iScan / sizeof(image32_t);

   int srcS = pimage->m_iScan / sizeof(image32_t);

   for (i32 i = 0; i < cx; i++)
   {

      for (i32 j = 0; j < cy; j++)
      {

         image32()[i * s + j] = pimage->image32()[(cy - j - 1) * srcS + (cx - i - 1)];

      }

   }

}


void image::e_rotate_90_flip_horizontally()
{

   ::image_pointer pimage = this->clone();

   return e_rotate_90_flip_horizontally(pimage);

}


void image::e_rotate_180_flip_horizontally()
{

   ::image_pointer pimage = this->clone();

   return e_rotate_180_flip_horizontally(pimage);

}


void image::e_rotate_270_flip_horizontally()
{

   ::image_pointer pimage = this->clone();

   return e_rotate_270_flip_horizontally(pimage);

}


void image::fill_byte(uchar uch)
{

   if (m_bMapped)
   {

      if (area() <= 0 || data() == nullptr)
      {

         return;

      }

      int iScan = m_iScan;

      int iHeight = get_size().cy();

      if (iScan <= 0 || iHeight <= 0)
      {

         return;

      }

      memory_set(data(), uch, (memsize)(iScan * iHeight));

   }
   else if (g())
   {

      auto color = argb(uch, uch, uch, uch);

      auto ealphamode = g()->alpha_mode();

      if (ealphamode != ::draw2d::e_alpha_mode_set)
      {

         g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      }

      g()->fill_rectangle(::rectangle_f64(m_size), color);

      if (ealphamode != ::draw2d::e_alpha_mode_set)
      {

         g()->set_alpha_mode(ealphamode);

      }

   }

   //return true;

}


void image::clear(::color::color color)
{

   if (m_bMapped)
   {

      image32_t u32Color(color, color_indexes());

      i64 size = scan_area();

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

      for (i64 i = 0; i < size; i++)
      {

         pcr[i] = u32ColorImage;

      }

   }
   else if (get_graphics() != nullptr)
   {

      auto ealphamode = get_graphics()->alpha_mode();

      if (ealphamode != ::draw2d::e_alpha_mode_set)
      {

         get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      }

      get_graphics()->fill_rectangle(rectangle(), color);

      if (ealphamode != ::draw2d::e_alpha_mode_set)
      {

         get_graphics()->set_alpha_mode(ealphamode);

      }

   }

   //return true;

}


//void image::clear(const ::color::color & colorFill)
//{
//   
//   fill(colorFill);
//   
//}


void image::clear_argb(i32 a, i32 r, i32 g, i32 b)
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


::color::color image::GetAverageColor()
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

         ::u8* pb = ((::u8*)data()) + m_iScan * y;


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

      return {};

   }

}


::color::color image::GetAverageOpaqueColor()
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
         ::u8* pb = ((::u8*)data()) + m_iScan * y;

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
      
      return {};

   }

}


void image::do_xor(::image* pimage)
{

   if (width() != pimage->width()
      || height() != pimage->height())
   {

      //return false;

      return;

   }

   i32 iCount = width() * height();
   ::u32* pd1 = (::u32*)data();

   ::u32* pd2 = (::u32*)pimage->data();

   for (i32 i = 0; i < iCount; i++)
   {
      *pd1 = *pd1 ^ *pd2;

      pd1++;

      pd2++;

   }

   //return true;

}


void image::create_frame(const ::size_i32& size, i32 iFrameCount)
{

   i32 iSliceCount = (i32)sqrt((double)iFrameCount);

   return create(size / iSliceCount);

}


void image::set_frame1(void* pdata, i32 iFrame, i32 iFrameCount)

{
   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

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

   //return true;

}


void image::set_frame2(void* pdata, i32 iFrame, i32 iFrameCount)

{

   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

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

   //return true;

}


void image::xor_image_frame2(void* pdata, i32 iFrame, i32 iFrameCount)

{
   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (i32 y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (i32 x = 0; x < iFrameWidth; x++)
      {
         pdstline->m_u32 ^= psrc->m_u32;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void image::get_frame(void* pdata, i32 iFrame, i32 iFrameCount)

{
   i32 iSliceCount = (i32)sqrt((double)iFrameCount);
   i32 iFrameWidth = width() / iSliceCount;
   i32 iFrameHeight = height() / iSliceCount;
   i32 iX = iFrame % iSliceCount;
   i32 iY = iFrame / iSliceCount;
   image32_t* psrc = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* pdst = (image32_t*)pdata;

   image32_t* psrcline;

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

   //return true;

}


bool image::is_rgb_black()
{

   i32 iSize = width() * height();

   image32_t* p = data();

   for (i32 i = 0; i < iSize; i++)
   {

      if ((p->m_u32 & 0x00FFFFFF) != 0)
      {

         return false;

      }

      p++;

   }

   return true;

}


void image::DivideRGB(i32 iDivide)
{

   if (iDivide == 0)
   {

      return;

   }

   i32 iCount = width() * height();

   ::u8* p = ((::u8*)data());

   i32 i = 0;

   i32 iCount1 = iCount - iCount % 8;

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


void image::DivideARGB(i32 iDivide)
{

   if (iDivide == 0)
   {

      return;

   }

   i32 iCount = width() * height();

   ::u8* p = ((::u8*)data());

   for (i32 i = 0; i < iCount; i++)
   {
      p[0] /= (::u8)iDivide;

      p[1] /= (::u8)iDivide;

      p[2] /= (::u8)iDivide;

      p[3] /= (::u8)iDivide;

      p += 4;

   }

   //return true;

}


void image::DivideA(i32 iDivide)
{

   if (iDivide == 0)
   {

      //return false;

      return;

   }

   i32 iCount = width() * height();

   ::u8* p = ((::u8*)data());

   for (i32 i = 0; i < iCount; i++)
   {
      p[3] /= (::u8)iDivide;

      p += 4;

   }

   //return true;

}




void image::set_mipmap(::draw2d::enum_mipmap emipmap)
{

   if (m_emipmap == emipmap)
   {

      //return true;

      return;

   }

   if (emipmap != ::draw2d::e_mipmap_none)
   {

      return _set_mipmap(emipmap);

   }

   //return true;

}


void image::_set_mipmap(::draw2d::enum_mipmap emipmap)
{

   ASSERT(emipmap != ::draw2d::e_mipmap_none);

   ::image_pointer pimage = this->clone();

   int cxSource = pimage->width();

   int cySource = pimage->width();

   int iSourceScan = pimage->scan_size();

   double cx = cxSource;

   double cy = cySource;

   if (emipmap == ::draw2d::e_mipmap_isotropic)
   {

      double newcx = cx + cx / 2.0 - 1.0;

      double newcy = cy;

      create({ (int)newcx, (int)newcy });

      //if (!create({ (int)newcx, (int)newcy }))
      //{

      //   throw ::exception(error_resource);

      //}

      get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      int x = cxSource;

      int y = 0;

      image_source imagesource(pimage);

      rectangle_f64 rectangle(::size_f64(cxSource, cySource));

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      get_graphics()->draw(imagedrawing);

      while (cx >= 1.0 && cy >= 1.0)
      {

         cx /= 2.0;

         cy /= 2.0;

         if (::parallelization::get_priority() == ::e_priority_idle)
         {

            map();

            C2PassScale < CBlackmanFilter > scale(1.0);

            scale.Scale(
               &image32()[x + y * m_iScan / sizeof(image32_t)],
               color_indexes(),
               (::u32)cx,
               (::u32)cy,
               m_iScan,
               pimage->data(),
               cxSource,
               cySource,
               iSourceScan
            );

         }
         else
         {

            image_source imagesource(pimage, ::rectangle_i32_dimension(0, 0, (i32)cx, (i32)cy));

            auto rectangle = rectangle_f64_dimension(x, y, cx, cy);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            get_graphics()->draw(imagedrawing);

         }

         y += (i32)cy;

      }

      m_emipmap = ::draw2d::e_mipmap_isotropic;

   }
   else
   {

      double newcx = cx * 2.0 - 1.0;

      double newcy = cy * 2.0 - 1.0;

      create({ (i32)newcx, (i32)newcy });

      //if (!create({ (i32)newcx, (i32)newcy }))
      //{

      //   throw ::exception(error_resource);

      //}

      int greekdeltax;

      int x = 0;

      int xPrevious;
      int yPrevious;
      int cxPrevious;
      int cyPrevious;

      xPrevious = 0;
      cxPrevious = cxSource;

      for (greekdeltax = (i32)cx; greekdeltax > 0; x += greekdeltax, greekdeltax /= 2)
      {

         yPrevious = 0;
         cyPrevious = pimage->height();

         for (int y = 0, greekdeltay = (i32)cy; greekdeltay > 0; y += greekdeltay, greekdeltay /= 2)
         {

            if (::parallelization::get_priority() == ::e_priority_idle)
            {

               map();

               C2PassScale < CBlackmanFilter > scale(1.0);

               scale.Scale(
                  &image32()[x + y * m_iScan / sizeof(image32_t)],
                  color_indexes(),
                  greekdeltax,
                  greekdeltay,
                  m_iScan,
                  &pimage->image32()[xPrevious + yPrevious * pimage->m_iScan / sizeof(image32_t)],
                  cxPrevious,
                  cyPrevious,
                  pimage->m_iScan
               );

               yPrevious = y;
               cyPrevious = greekdeltay;
               pimage = this;

            }
            else
            {

               image_source imagesource(pimage, ::rectangle_i32_dimension(0, 0, pimage->width(), pimage->height()));

               auto rectangle = rectangle_f64_dimension(x, y, greekdeltax, greekdeltay);

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               get_graphics()->draw(imagedrawing);

            }

         }

         xPrevious = x;
         cxPrevious = greekdeltax;

      }

      m_emipmap = ::draw2d::e_mipmap_anisotropic;

   }

   size() = pimage->get_size();

   //return true;

}


void image::set_origin(const ::point_i32& point)
{

   m_point = point;

   if (!m_bMapped)
   {

      get_graphics()->set_origin(point);

   }

   //return true;

}


void image::create_helper_map()
{

   if (m_pextension && m_pextension->m_pframea)
   {

      for (auto& pframe : *m_pextension->m_pframea)
      {

         if (pframe != this)
         {

            pframe->m_pimage->create_helper_map();

         }

      }

   }

   _create_helper_map();

   //return true;

}


void image::_create_helper_map()
{


   index a;

   a = (index)(area());

   //return true;

   index jNextBoundary;
   index jStart;
   u8* pdata = (u8*)image32();

   if (pdata == nullptr || a <= 0)
   {

      //return false;

      return;

   }

   index w = width();
   index h = height();
   index sw = w * sizeof(image32_t);
   index aa = w * h;
   {

      m_memoryMap.set_size(a * 2);

      m_memoryMap.set(0);
      u8* opacity = m_memoryMap.data();

      for (index i = 0; i < height(); i++)
      {

         for (index j = 0; j < sw; j += 4)
         {

            if (pdata[i * m_iScan + j + 3] == 255)
            {
               jStart = j;
               jNextBoundary = minimum(j + 960, sw);
               for (j += 4; j < jNextBoundary; j += 4)
               {
                  if (pdata[i * m_iScan + j + 3] != 255)
                  {
                     break;
                  }
               }

               j -= 4;

               index c = (j - jStart) >> 2;

               index m = j >> 2;

               ::u8 n = 1;

               u8* o = &opacity[(int)(i * w)];

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

      u8* transparency = m_memoryMap.data() + a;

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

               ::u8 n = 1;

               u8* t = &transparency[(int)(i * w)];

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

   //return true;

}


void image::set_font_factor(double dFactor)
{

   m_dFontFactor = dFactor;

   if (!m_bMapped)
   {

      get_graphics()->m_dFontFactor = dFactor;

   }

   //return true;

}


//void image::set_alpha_mode(::draw2d::enum_alpha_mode emode)
//{
//
//   m_ealphamode = emode;
//
//   if (!m_bMapped)
//   {
//
//      get_graphics()->set_alpha_mode(emode);
//
//   }
//
//   //return true;
//
//}
//

//i32 image::cos(i32 i, i32 iAngle)
//{
//
//   UNREFERENCED_PARAMETER(i);
//   UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   return 0;
//
//}
//
//
//i32 image::sin(i32 i, i32 iAngle)
//{
//
//   UNREFERENCED_PARAMETER(i);
//   UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   //return 0;
//
//}
//
//
//i32 image::cos10(i32 i, i32 iAngle)
//{
//
//   UNREFERENCED_PARAMETER(i);
//   UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   return 0;
//
//}
//
//
//i32 image::sin10(i32 i, i32 iAngle)
//{
//
//   UNREFERENCED_PARAMETER(i);
//   UNREFERENCED_PARAMETER(iAngle);
//
//   throw ::interface_only();
//
//   return 0;
//
//}

/*   i32 image::width()
   {
      throw ::interface_only();
   }

   i32 image::height()
   {
      throw ::interface_only();
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

   return atan(1.0) * 4.0;

}


void image::fill_channel(i32 intensity, ::color::enum_channel echannel)
{
   map();
   i32 offset = ((i32)echannel) % 4;
   i64 size = scan_area();

   image32_t* pcr = (image32_t*)&((u8*)image32())[offset];

   u8* pb;

   i64 iSize32 = size / 32;
   i32 i;
   for (i = 0; i < iSize32; i += 32)
   {
      pb = (u8*)&pcr[i];
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
      *((u8*)&pcr[i]) = (::u8)intensity;
   }

   //return true;

}


void image::white_fill_channel(i32 intensity, ::color::enum_channel echannel)
{
   map();
   i32 offset = ((i32)echannel) % 4;
   i64 size = scan_area();

   image32_t* pcr = (image32_t*)&((u8*)image32())[offset];

   //      u8 * pb;

   i64 iSize32 = size / 32;
   i32 i;
   //      for (i=0; i < iSize32; i+=32 )
   //      {
   //         pb = (u8 *) &pcr[i];
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

      *((u8*)&pcr) = (::u8)(((int)intensity * (int)*((u8*)&pcr)) / 255);

      pcr++;

   }

   //return true;

}


void image::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc)
{

   map();

   echannelDst = (::color::enum_channel)(((i32)echannelDst) % 4);
   echannelSrc = (::color::enum_channel)(((i32)echannelSrc) % 4);

   if (echannelDst == echannelSrc)
   {

      //return true;
      return;

   }

   u8* pdataDst = (u8*)data() + ((i32)echannelDst);

   u8* pdataSrc = (u8*)data() + ((i32)echannelSrc);

   for (i32 y = 0; y < height(); y++)
   {

      u8* pdst = &pdataDst[m_iScan * y];

      u8* psrc = &pdataSrc[m_iScan * y];

      for (i32 x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}


void image::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image* pimage)
{

   if (size() != pimage->size())
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   map();

   if (image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   pimage->map();

   if (pimage->image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   echannelDst = (::color::enum_channel)(((i32)echannelDst) % 4);
   echannelSrc = (::color::enum_channel)(((i32)echannelSrc) % 4);

   u8* pdataDst = (u8*)data() + ((i32)echannelDst);

   u8* pdataSrc = (u8*)pimage->data() + ((i32)echannelSrc);

   for (i32 y = 0; y < height(); y++)
   {

      u8* pdst = &pdataDst[m_iScan * y];

      u8* psrc = &pdataSrc[pimage->m_iScan * y];

      for (i32 x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}


void image::all_channels_copy(::color::enum_channel echannelSrc, ::image * pimage)
{

   if (size() != pimage->size())
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   map();

   if (image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   pimage->map();

   if (pimage->image32() == nullptr)
   {

      //return false;

      throw ::exception(error_wrong_state);

   }

   echannelSrc = (::color::enum_channel)(((i32)echannelSrc) % 4);

   u8 * pdataDst = (u8 *)data();

   u8 * pdataSrc = (u8 *)pimage->data() + ((i32)echannelSrc);

   for (i32 y = 0; y < height(); y++)
   {

      u8 * pdst = &pdataDst[m_iScan * y];

      u8 * psrc = &pdataSrc[pimage->m_iScan * y];

      for (i32 x = 0; x < width(); x++)
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


void image::tint(::image* pimage, ::color::color color)
{

   create(pimage->size());


   /*{

      return false;

   }*/

   map();

   u8* src = (u8*)pimage->image32();
   u8* dst = (u8*)image32();
   i64 size = scan_area();

   ::u8 uchR = (::u8)color.u8_red();
   ::u8 uchG = (::u8)color.u8_green();
   ::u8 uchB = (::u8)color.u8_blue();

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
   //::u8 tableR[256];
   //::u8 tableG[256];
   //::u8 tableB[256];
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


void image::saturation(double dRate)
{

   map();

   u8* dst = (u8*)image32();

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

   //return true;

}


void image::lightness(double dRate)
{

   rate_rgb(as_byte(dRate * 255.0), 255);

   //return true;

}


void image::opacity(double dRate)
{

   int iA = as_byte(255. * dRate);

   map();

   try
   {
      u8* puch = (u8*)data();
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

   //return true;

}


void image::set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A)
{

   map();

   u8* dst = (u8*)image32();
   i64 size = scan_area();

   ::u8 uchB = (::u8)R;
   ::u8 uchG = (::u8)G;
   ::u8 uchR = (::u8)B;

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

   //return true;

}


//void image::set_rgb(image32_t cr)
//{
//
//   return set_rgb(color32_u8_red(cr), color32_u8_green(cr), color32_u8_blue(cr));
//
//}


//void image::set_rgb(i32 R, i32 G, i32 B)
//{
//
//   return set(R, G, B);
//
//}


::i64 image::get_rgba_area(::color::color color) const
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


::i64 image::get_rgba_area(::color::color color, const ::rectangle_i32 &rect) const
{

   ::rectangle_i32 r(rect);

   if (r.intersect(this->rectangle()).is_empty())
   {

      return 0;

   }

   ::count areaRgba = 0;

   image32_t u32ColorImage(color, color_indexes());

   int wscan = m_iScan / sizeof(image32_t);

   int w = r.width();

   int h = r.height();

   int scanadvance = wscan - w;

   const image32_t* p = this->data() + r.left + wscan * r.top;

   areaRgba++;

   while (h > 0)
   {

      for (int x = 0; x < w; x++)
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


::i64 image::_001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const
{

   auto r = this->rectangle();

   return _001GetTopLeftWeightedOpaqueArea(iAlphaMin, r);

}


::i64 image::_001GetTopLeftWeightedOpaqueArea(int iAlphaMin, const ::rectangle_i32 &rect) const
{

   ::rectangle_i32 r(rect);

   ::rectangle_i32 rTotal(this->rectangle());

   if (r.intersect(rTotal).is_empty())
   {

      return 0;

   }

   ::i64 areaRgba = 0;

   int wscan = m_iScan / sizeof(image32_t);

   int w = r.width();

   int h = r.height();

   ::i64 areaRgbaLast = 0;

   const image32_t* p = this->data() + r.left + wscan * r.top;

   areaRgba++;

   for (int y = r.top; y < r.bottom; y++)
   {

      auto ysq = (rTotal.bottom - y);

      auto pbyte = &((::u8*)p)[m_colorindexes.m_u8IndexOpacity];

      for (int x = r.left; x < r.right; x++)
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

         output_debug_string("_001GetTopLeftWeightedOpaqueArea areaRgba < areaRgbaLast");

      }

      areaRgbaLast = areaRgba;

   }

   return areaRgba;

}


void image::multiply_rgb_by_source_alpha(::color::color color)
{

   auto u8Red = color.u8_red();
   auto u8Green = color.u8_green();
   auto u8Blue = color.u8_blue();
   ::u8 u8Opacity;

   auto u8IndexOpacity = m_colorindexes.m_u8IndexOpacity;
   auto u8IndexRed = m_colorindexes.m_u8IndexRed;
   auto u8IndexGreen = m_colorindexes.m_u8IndexGreen;
   auto u8IndexBlue = m_colorindexes.m_u8IndexBlue;

   u8* puch = (u8*)data();
   i64 iArea = scan_area();
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


void image::rgb_from(::image* pimage)
{

   //if (!
   create(pimage->size());
   //{

   //   return false;

   //}

   //try
   //{

      u8* puchSrc = (u8*)data();
      u8* puchDst = (u8*)pimage->data();
      i64 iArea = pimage->scan_area();
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


void image::pixelate(i32 iSize)
{

   if (iSize <= 1)
   {

      //return true;

      return;

   }

   map();

   i32 w = width();
   i32 h = height();
   i32 s = m_iScan / sizeof(image32_t);

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
   image32_t* pdata = data();
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

      for (i32 i = 0; i < iMax; i++)
      {

         for (i32 j = 0; j < jMax; j++)
         {

            pdata[x1 + i + (y1 + j) * w] = cr;

         }

      }

   }

   //return true;

}


void image::rate_rgb(int iMul, int iDiv)
{

   map();

   try
   {
      u8* puch = (u8*)data();
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

   //return true;

}


void image::map(bool bApplyAlphaTransform) const
{

   if (!m_bMapped)
   {

      //if (
      ((::image*)this)->_map(bApplyAlphaTransform);

      //{

         pixmap::map();

         m_bMapped = true;

      //}

   }

   //return true;

}


void image::unmap() const
{

   if (m_bMapped)
   {

      ((::image*)this)->_unmap();

      if (_get_graphics() != nullptr)
      {

         ::rectangle_i32 rectangleThis(m_size);

         ::rectangle_i32 rectangleMap(rectangle());

         if (rectangleThis.contains(rectangleMap.origin()))
         {

            _get_graphics()->set_origin(rectangleMap.origin());

         }
         else
         {

            _get_graphics()->set_origin(0, 0);

         }

      }

      ((::image*)this)->m_bMapped = false;

   }

   //return true;

}


void image::set_mapped()
{

   m_bMapped = false;

//   return true;

}

//
//   void image::update_window(::aura::draw_interface * puserinteraction,::message::message * pmessage,bool bTransferBuffer)
//   {
//
//      UNREFERENCED_PARAMETER(puserinteraction);
//      UNREFERENCED_PARAMETER(pmessage);
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


//void image::print_window(::aura::draw_interface * puserinteraction,::message::message * pmessage)
//{

//   UNREFERENCED_PARAMETER(puserinteraction);
//   UNREFERENCED_PARAMETER(pmessage);

//   throw ::interface_only();

//   return false;

//}


void image::gradient_fill(::color::color color1, ::color::color color2, const point_i32& point1, const point_i32& point2)
{

   double greekdeltax = point2.x() - point1.x();

   double greekdeltay = point1.y() - point2.y();

   if (greekdeltax == 0.0 && greekdeltay == 0.0)
   {

      clear_argb(
         u8_clip(color1.u8_opacity() * 0.5 + color2.u8_opacity() * 0.5),
         u8_clip(color1.u8_red() * 0.5 + color2.u8_red() * 0.5),
         u8_clip(color1.u8_green() * 0.5 + color2.u8_green() * 0.5),
         u8_clip(color1.u8_blue() * 0.5 + color2.u8_blue() * 0.5));

   }
   else if (greekdeltax == 0.0)
   {

      gradient_horizontal_fill(color1, color2, point1.y(), point2.y());

   }
   else if (greekdeltay == 0.0)
   {

      gradient_vertical_fill(color1, color2, point1.x(), point2.x());

   }
   else
   {

      //         int x1 = minimum(point1.x(), point2.x());

      //       int x2 = maximum(point1.x(), point2.x());

      //     int y1 = minimum(point1.y(), point2.y());

      //   int y2 = maximum(point1.y(), point2.y());

      //         int top = y1;
      //
      //       int left = x1;
      //
      //       int right = width() - x2;
      //
      //  int bottom = height() - y2;

      int dim = maximum(width(), height());

      auto angle = radians(atan2(greekdeltay, greekdeltax));

      ::image_pointer pimage;

      auto pmathematics = ::mathematics::mathematics();

      if (fabs(greekdeltax) > fabs(greekdeltay))
      {

         double sin = ::sin(angle);

         //auto estatus =
         
         __construct(pimage);

         //if (!estatus)
         //{

         //   return false;

         //}

         //estatus = 
         
         pimage->create({ (i32)(dim / sin), (i32)(dim / sin) });

         //if (!estatus)
         //{

         //   return false;

         //}

         pimage->gradient_horizontal_fill(color1, color2, point1.y(), point2.y());

         pimage->rotate(this, -angle, 1.0);

      }
      else
      {

         double cos = ::cos(angle);

         //auto estatus =
         
         __construct(pimage);

         //if (!estatus)
         //{

         //   return false;

         //}

         //estatus = 
         pimage->create({ (i32)(dim / cos), (i32)(dim / cos) });

         //if (!estatus)
         //{

         //   return false;

         //}

         pimage->gradient_vertical_fill(color1, color2, point1.x(), point2.x());

         pimage->rotate(this, radians(pmathematics->get_pi() - angle), 1.0);

      }

   }

   //return true;

}


void image::gradient_horizontal_fill(::color::color color1, ::color::color color2, int start, int end)
{

   if (end < start)
   {
      ::__swap(start, end);
      ::__swap(color1, color2);
   }

   end = minimum(end, height() - 1);
   image32_t clr(color1, color_indexes());
   u8* pb = (u8*)image32();
   image32_t* pdata;
   int line = 0;
   for (; line < start; line++)
   {
      pdata = (image32_t*)&pb[m_iScan * line];
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

      clr.assign(argb(
         u8_clip(color1.u8_opacity() * (1.0 - d) + color2.u8_opacity() * d),
         u8_clip(color1.u8_red() * (1.0 - d) + color2.u8_red() * d),
         u8_clip(color1.u8_green() * (1.0 - d) + color2.u8_green() * d),
         u8_clip(color1.u8_blue() * (1.0 - d) + color2.u8_blue() * d)), color_indexes());

      pdata = (image32_t*)&pb[m_iScan * line];
      for (int row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }
   clr.assign(color2, color_indexes());
   for (; line < height(); line++)
   {
      pdata = (image32_t*)&pb[m_iScan * line];
      for (int row = 0; row < width(); row++)
      {
         *pdata = clr;
         pdata++;
      }
   }

   //return true;

}


void image::gradient_vertical_fill(::color::color color1, ::color::color color2, int start, int end)
{

   if (end < start)
   {
      ::__swap(start, end);
      ::__swap(color1, color2);
   }

   end = minimum(end, width() - 1);

   image32_t clr(color1, color_indexes());
   
   u8* pb = (u8*)image32();
   
   image32_t* pdata;
   
   int row = 0;

   for (; row < start; row++)
   {
      pdata = (image32_t*)&pb[sizeof(image32_t) * row];
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

      clr.assign(argb(
         u8_clip(color1.u8_opacity() * (1.0 - d) + color2.u8_opacity() * d),
         u8_clip(color1.u8_red() * (1.0 - d) + color2.u8_red() * d),
         u8_clip(color1.u8_green() * (1.0 - d) + color2.u8_green() * d),
         u8_clip(color1.u8_blue() * (1.0 - d) + color2.u8_blue() * d)), 
         color_indexes());

      pdata = (image32_t*)&pb[sizeof(image32_t) * row];

      for (int line = 0; line < width(); line++)
      {

         *pdata = clr;

         pdata += m_iScan;

      }

   }
   
   clr.assign(color2, color_indexes());

   for (; row < width(); row++)
   {
      
      pdata = (image32_t*)&pb[sizeof(image32_t) * row];

      for (int line = 0; line < width(); line++)
      {
         
         *pdata = clr;

         pdata += m_iScan;

      }

   }

  // return true;
//
}


void image::gradient_horizontal_fill(::color::color color1, ::color::color color2)
{

   gradient_horizontal_fill(color1, color2, 0, height() - 1);

   //return true;

}


void image::gradient_vertical_fill(::color::color color1, ::color::color color2)
{

   gradient_vertical_fill(color1, color2, 0, width() - 1);

   //return true;

}


void image::invert_rgb()
{

   return invert_rgb(rectangle());

}


void image::invert_rgb(const ::rectangle_i32& rectangle)

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

      u8* pb = &((u8*)image32())[start];

      for (int x = left; x < right; x++, pb += 4)
      {

         pb[0] = ~pb[0];
         pb[1] = ~pb[1];
         pb[2] = ~pb[2];

      }

   }

   //return true;

}


void image::create_circle(::image* pimage, int diameter)
{


   create({ diameter, diameter });
   //if (!)
   //{

   //   return false;

   //}

   if (::is_null(pimage) || pimage->area() <= 0)
   {

      clear_argb(255, 0, 0, 0);

   }
   else
   {

      get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      image_source imagesource(pimage, ::rectangle_i32_dimension(0, 0, pimage->width(), pimage->height()));

      auto rectangle = rectangle_f64_dimension(0, 0, diameter, diameter);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      get_graphics()->draw(imagedrawing);

   }

   ::size_i32 s = size();

   image32_t* pimage32 = image32();

   int iScan = m_iScan;

   int wscan = iScan / sizeof(image32_t);

   double radius = diameter / 2.0;

   double dBorder = 1.0;

   double rmin = radius - dBorder;

   double rmax = radius;

   int crA;

   image32_t* pimage322;

   for (int y = 0; y < s.cx(); y++)
   {

      pimage322 = &pimage32[y * wscan];

      for (int x = 0; x < s.cx(); x++)
      {

         double greekdeltax = x;

         double greekdeltay = y;

         double distance = sqrt((greekdeltax - radius) * (greekdeltax - radius) + (greekdeltay - radius) * (greekdeltay - radius));

         crA = (int)((rmin - distance) * 255.0 / dBorder);

         crA = maximum(minimum(crA, 255), 0);

         pimage322->m_u32 = (pimage322->m_u32 & 0x00ffffff) | (crA << 24);

         pimage322++;

      }

   }

   //return true;

}


void image::create_framed_square(::image* pimage, int inner, int outer, ::color::color color)
{

   create({ inner + outer * 2, inner + outer * 2 });

   //if (!create({ inner + outer * 2, inner + outer * 2 }))
   //{

   //   return false;

   //}

   clear(color);

   image_source imagesource(pimage, ::rectangle_i32_dimension(0, 0, pimage->width(), pimage->height()));

   auto rectangle = rectangle_f64_dimension(outer, outer, inner, inner);

   image_drawing_options imagedrawingoptions(rectangle);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   get_graphics()->draw(imagedrawing);

   //return true;

}


void image_copy(::image* pimagethis, ::image* pimage)
{

   pimagethis->copy_from(pimage);

}


//void image_create(::object* pparticle, ::image_pointer& pimage)
//{
//
//   __construct(pimage, pparticle);
//
//}

//
//void image_create_image(::image* pimage, const ::size_i32& size)
//{
//
//   pimage->create(size);
//
//}


unsigned int* image_get_data(::image* pimage)
{

   return (unsigned int*)pimage->image32();

}


::draw2d::graphics* image_get_graphics(::image* pimage)
{

   if (::is_null(pimage))
   {

      return nullptr;

   }

   return pimage->g();

}


void image::hue_offset(double dRadians)
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


   u8* dst = (u8*)data();

   i64 size = scan_area();


   while (size--)
   {
      double oldr = dst[0];
      double oldg = dst[1];
      double oldb = dst[2];
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



void image::fast_copy(image32_t* pcolor32)
{

   ::copy_image32(data(), rectangle(), scan_size(), pcolor32);

}

void image::on_load_image()
{

   if (m_iExifOrientation != 0)
   {

      on_exif_orientation();

   }

   //return true;

}


void image::on_exif_orientation()
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


//save_image::save_image(::matter * pmatter)
save_image::save_image()
{

   m_eformat = ::draw2d::e_format_png;

   m_iQuality = 100;

   m_iDpi = 96;

}


//save_image::save_image(::matter * pmatter, const ::payload & payloadFile, const ::payload & varOptions)
//{
//
//   ::pointer<::aura::system>psystem = acmesystem();
//
//   auto eformat = pdraw2d->text_to_format(varOptions["format"]);
//
//   if (eformat != ::draw2d::e_format_none)
//   {
//
//      ::pointer<::aura::system>psystem = acmesystem();
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

//void image::load_matter_icon(string_array & straMatter, string strIcon)
//{
//
//   ::file::path path;
//
//   for (auto & strMatter : straMatter)
//   {
//
//      path = strMatter;
//
//      path = dir()->matter(path / strIcon);
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
//   void image::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
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

   if (pimage 
      && m_pgraphics != pimage->m_pgraphics
      && m_pbitmap != pimage->m_pbitmap)
   {

      unmap();

      pimage->unmap();

      ::pixmap * ppixmapDst = this;

      ::pixmap * ppixmapSrc = pimage;

      m_pgraphics = pimage->m_pgraphics;

      m_pbitmap = pimage->m_pbitmap;

      ::memcpy(ppixmapDst, ppixmapSrc, sizeof(::pixmap));

   }

}


::pointer<::image>image::get_image(const ::size_i32 & size)
{

   if (size == get_size())
   {

      return this;

   }

   auto pimageNew = m_pcontext->m_pauracontext->create_image(size);

   image_source imagesource(this, this->rectangle());

   auto rectangle = pimageNew->rectangle();

   image_drawing_options imagedrawingoptions(rectangle);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pimageNew->g()->draw(imagedrawing);

   return pimageNew;

}


::pointer<::image>image::get_image(::i32 cx, ::i32 cy)
{

   auto pimageNew = get_image( ::size_i32( cx, cy ));

   return pimageNew;

}


#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::image* m_p, i32 greekdeltax, i32 greekdeltay, void* pftbitmap, int xParam, int yParam)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
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

         *((image32_t*)&((u8*)m_p->data())[(greekdeltay + j) * m_p->m_iScan + (greekdeltax + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::image* m_p, i32 greekdeltax, i32 greekdeltay, void* pftbitmap, int xParam, int yParam, ::u8 aParam, ::u8 rectangle, ::u8 g, ::u8 b)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
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

            *((image32_t*)&((u8*)m_p->data())[(greekdeltay + j) * m_p->m_iScan + (greekdeltax + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((image32_t*)&((u8*)m_p->data())[(greekdeltay + j) * m_p->m_iScan + (greekdeltax + i) * 4]) = 0;

         }

      }
   }

}

#endif









#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::image* m_p, i32 greekdeltax, i32 greekdeltay, void* pftbitmap, int xParam, int yParam)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
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

         *((image32_t*)&((u8*)m_p->data())[(greekdeltay + j) * m_p->m_iScan + (greekdeltax + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::image* m_p, i32 greekdeltax, i32 greekdeltay, void* pftbitmap, int xParam, int yParam, ::u8 aParam, ::u8 rectangle, ::u8 g, ::u8 b)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
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

            *((image32_t*)&((u8*)m_p->data())[(greekdeltay + j) * m_p->m_iScan + (greekdeltax + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((image32_t*)&((u8*)m_p->data())[(greekdeltay + j) * m_p->m_iScan + (greekdeltax + i) * 4]) = 0;

         }

      }
   }

}


#endif



//stream& image::write(::stream& stream) const
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
//   i32 iWidth = width();
//
//   stream << (::i32)iWidth;
//
//   i32 iHeight = height();
//
//   stream << (::i32)iHeight;
//
//   stream << (::i32)m_sizeAlloc.cx();
//
//   stream << (::i32)m_sizeAlloc.cy();
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
//stream& image::read(::stream& stream)
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
//   i32 width;
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
//   i32 height;
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
//   i32 widthAlloc;
//   stream >> widthAlloc;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   i32 heightAlloc;
//   stream >> heightAlloc;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   i32 iScan;
//   stream >> iScan;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   i32 iMipmap;
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
//   if (iScan < widthAlloc / (i32)sizeof(image32_t))
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
//   m_size.cx() = width;
//
//   m_size.cy() = height;
//
//   return stream;
//
//}


::particle_pointer image::clone() const
{

   auto pimage = ((::image*)this)->__create<::image>();

   pimage->copy_from((::image *) this);

   pimage->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

   return pimage;

}


//void image::create_image()
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


//void     image::create(int cx, int cy, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
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


//void     image::create(const ::size_i32 & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
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
::payload png = memory_new ::u8[]{ 137, 80, 78, 71 }; // PNG
::payload tiff = memory_new ::u8[]{ 73, 73, 42 }; // TIFF
::payload tiff2 = memory_new ::u8[]{ 77, 80, 42 }; // TIFF
::payload jpeg = memory_new ::u8[]{ 255, 216, 255, 224 }; // jpeg
::payload jpeg2 = memory_new ::u8[]{ 255, 216, 255, 225 }; // jpeg canon
*/


//virtual ::image_pointer ::create_image(::draw2d::e_load eload = ::draw2d::load_none);
//virtual ::image_pointer create_image({int cx,  int cy});
//virtual ::image_pointer create_image(const ::size_i32 & size);




void image::transform(enum_image eimage)
{

   if (eimage == e_image_grayscale)
   {

      return saturation(0.0);

   }

   //return ::error_not_found;

   throw ::exception(error_not_found);

}


::draw2d::graphics* image::_get_graphics() const
{

   return nullptr;

}


void image::_map(bool bApplyAlphaTransform)
{

   pixmap::map(this->rectangle());

   //return true;

}


void image::_unmap()
{

   //return true;

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


::image_extension* image::get_extension()
{

   if (::is_null(m_pextension))
   {

      __construct_new(m_pextension);

   }

   return m_pextension;

}


bool image::_draw_blend(const image_drawing& imagedrawing)
{

   auto pgraphics = get_graphics();

   //if (::is_null(pgraphics))
   //{

   //   return false;

   //}

   return pgraphics->_draw_blend(imagedrawing);
   //{

   //   return false;

   //}

   //return true;

}


void image::draw(const image_drawing & imagedrawing)
{

   if (imagedrawing.m_bDoForAllFrames)
   {

      auto pimage = imagedrawing.image();

      auto pframes = pimage->frames();

      if (pframes && pframes->has_elements())
      {

         auto pextension = get_extension();

         __construct_new(pextension->m_pframea);

         pextension->m_pframea->m_size = this->m_size;

         pextension->m_pframea->update(this, imagedrawing);

         return;

      }

   }

   image_drawer::draw(imagedrawing);
   //void defer_update_image();

}


void image::_draw_raw(const image_drawing& imagedrawing)
{

   auto pgraphics = get_graphics();

   //if (::is_null(pgraphics))
   //{

   //   return false;

   //}

   //if (!
   pgraphics->_draw_raw(imagedrawing); //;
  /* {

      return false;

   }

   return true;*/

}



image_pointer image::get_resized_image(const ::size_i32 & size)
{

   image_pointer pimage;

   m_pcontext->__construct(pimage);

   pimage->create(size);

   ::rectangle_f64 rectangleTarget(point_f64(0, 0), ::size_f64(size));

   ::image_source imagesource(this);

   ::image_drawing_options imagedrawingoptions(rectangleTarget);

   ::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pimage->_draw_raw(imagedrawing);

   return pimage;

}



::image32_t * image::line_data(int iLine)
{

   return (::image32_t *) (((::u8*)data()) + (iLine * m_iScan));

}