//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "frame_array.h"
#include "drawing.h"
#include "context.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/_exif.h"
#include "acme/graphics/image/image32.h"
#include "acme/platform/application.h"
#include "acme/prototype/mathematics/mathematics.h"
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


namespace image
{


image::image()
{
   
   m_item.m_eelement = e_element_image;

}


image::~image()
{
   
   auto psystem = system();

   if (::is_set(psystem))
   {
      
      auto paurasystem = psystem;
      
      if(::is_set(paurasystem))
      {
         
         auto pdraw2d = paurasystem->m_pdraw2d;
         
         if(::is_set(pdraw2d))
         {
            
            pdraw2d->erase_image(this);
            
         }
         
      }

   }

}


void image::on_initialize_particle()
{

   system()->draw2d()->add_image(this);

   ::particle::on_initialize_particle();

}


::int_size image::get_image_drawer_size() const
{

   return get_size();

}


::image::image_pointer image::image::image_source_image(const ::int_size &)
{
   
   return this; 

}


::int_size image::image::image_source_size(const ::double_size &, enum_image_selection) const
{ 
   
   return get_size(); 

}


::int_size image::image::image_source_size() const 
{
   
   return get_size(); 

}


bool image::_is_set() const
{

   return m_item.m_eelement != e_element_none || m_item.m_iItem >= 0;

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

   __UNREFERENCED_PARAMETER(pgraphics);

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


void image::create_ex(const ::int_size & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate, int iGoodStride, bool bPreserve)
{

   create(size, eflagCreate, iGoodStride, bPreserve);

   if (::is_set(pimage32))
   {

      m_pimage32->copy(size, m_iScan, pimage32, iScan);

   }


}


void image::create(const ::int_size& size, ::enum_flag eflagCreate, int iGoodStride, bool bPreserve)
{

   return create_ex(size, nullptr, 0, eflagCreate, iGoodStride, bPreserve);

}


void image::initialize(const ::int_size & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate)
{

   return create_ex(size, pimage32, iScan, eflagCreate);

}


//void image::initialize(const ::int_size & size, ::image32_t * pimage32, int iScan, ::eobject eobjectCreate)
//{
//
//   throw ::interface_only();
//
//   throw ::interface_only();
//
//}


//void     image::create(int width, int height, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//{
//
//   return create(::int_size(width, height), uidCreateImage);
//
//}


bool image::host(::pixmap* ppixmap, ::windowing::window * pwindow)
{
   //// callers should be able to deal with graphics backend that doesn't support "hosting" portions of RAM
   //return false;

   if (!ppixmap->is_ok())
   {

      return false;

      //throw ::exception(error_failed);

   }

   if (m_pbitmap.is_set()
         && m_pbitmap->get_os_data() != nullptr
         && ppixmap->m_sizeRaw == this->m_sizeRaw
         && ppixmap->image32() == image32()
         && ppixmap->scan_size() == scan_size())
   {

      if (ppixmap->size() != size())
      {

         m_size = ppixmap->size();

      }

      return true;

      //return;

   }

   //destroy();

   ødefer_construct(m_pbitmap);

   ødefer_construct(m_pgraphics);

   //if (m_pbitmap.is_null())
   //{

   //   m_sizeRaw.cx = 0;

   //   m_sizeRaw.cy = 0;

   //   m_sizeAlloc.cx = 0;

   //   m_sizeAlloc.cy = 0;

   //   m_iScan = 0;

   //   return false;

   //}


   if(!m_pbitmap->host_bitmap(nullptr, ppixmap))
   {

      return false;
      //m_pbitmap->create_bitmap(pgraphics, size, )

   }
   //if (!)
   //{

   //   m_sizeRaw.cx = 0;

   //   m_sizeRaw.cy = 0;

   //   m_sizeAlloc.cx = 0;

   //   m_sizeAlloc.cy = 0;

   //   m_iScan = 0;

   //   return false;

   //}
      //throw ::exception(error_failed);
   //if (m_pbitmap->get_os_data() == nullptr)
   //{

   //   destroy();

   //   return false;

   //}

   initialize(ppixmap->size(), ppixmap->image32(), ppixmap->m_iScan);

   m_pgraphics->set(m_pbitmap);

   m_pgraphics->m_pimage = this;

   m_pgraphics->place_impact_area(0., 0., m_size.cx, m_size.cy);

   m_sizeRaw = ppixmap->size();

   set_ok_flag();

   return true;



}


bool image::on_host_read_pixels(::pixmap* ppixmapHost) const
{

   //map();

   //::copy_image32(ppixmapHost, this);

   return false;

}


void image::dc_select(bool bSelect)
{

   __UNREFERENCED_PARAMETER(bSelect);

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

::collection::count image::get_image_count() const
{

   ::collection::count c1 = is_set() ? 1 : 0;

   ::collection::count c2 = 0;

   if (m_pextension && m_pextension->m_pframea)
   {

      c2 = m_pextension->m_pframea->count();

   }

   return maximum(c1, c2);

}


::image::image_pointer image::get_image(::collection::index i)
{

   if (m_pextension && m_pextension->m_pframea && m_pextension->m_pframea->has_element())
   {

      return m_pextension->m_pframea->element_at(i);

   }

   return this;

}


void image::create_isotropic(::image::image* pimage)
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

      ::image::image_source imagesource(get_graphics(), ::int_rectangle_dimension(0, 0, width(), height()));

      ::image::image_drawing_options imagedrawingoptions(::int_rectangle_dimension(0, 0, cx, cy));

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

   //::image::image *pimageLast = this;

   //image_array imagea;

   //for (const double & dRate : daRate)
   //{

   //   pimageLast->m_pnext.alloc(this);

   //   pimageLast = pimageLast->m_pnext;

   //   pimageLast->m_dIsotropicRate = dRate;

   //   imagea.add(pimageLast);

   //}

   //fork_count_end(get_app(), imagea.get_count(),
   //               [&](::collection::index i)
   //{

   //   create_isotropic(imagea[i]);

   //}, 0, epriority);

   //return true;

}


//void image::defer_save_to_cache()
//{
//
//   if (m_pathCache.has_character())
//   {
//
//      ::file::path pathDib = m_pathCache;
//
//      m_pathCache.empty();
//
//      ::image::image *pimage = this;
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

   m_sizeRaw.cx = 0;
   m_sizeRaw.cy = 0;
   m_size.cx = 0;
   m_size.cy = 0;
   pixmap::reset();
   pixmap::unmap();
   clear_flag(e_flag_success);
   clear_flag(e_flag_failure);
   m_pgraphics.defer_destroy();
   m_pbitmap.defer_destroy();
   //return ::success;

}


void image::destroy_os_data()
{

}


//void image::draw(const ::image::image *pimage)
//{
//
//   //if (::is_null(pimage))
//   //{
//
//   //   return false;
//
//   //}
//
//   return get_graphics()->draw(int_rectangle_dimension(0, 0,
//                                     width(),
//                                     height()),
//                                     pimage->g(),
//                                     int_rectangle_dimension(0, 0,
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
//void image::to(::draw2d::graphics * pgraphics, const ::int_point & point)
//{
//
//   return to(pgraphics, point, size());
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::int_size & size)
//{
//
//   return to(pgraphics, nullptr, size);
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::int_rectangle & rectangle)
//{
//
//   return to(pgraphics, ::top_left(rectangle), ::int_size(rectangle));
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size)
//{
//
//   return to(pgraphics, point, size, nullptr);
//
//}
//
//
//void image::to(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size, const ::int_point & pointSrc)
//{
//
//
//   __UNREFERENCED_PARAMETER(pgraphics);
//   __UNREFERENCED_PARAMETER(point);
//   __UNREFERENCED_PARAMETER(size);
//   __UNREFERENCED_PARAMETER(pointSrc);
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


void image::stretch_image(::image::image* pimage)
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

   ::image::image_source imagesource(pimage->g(), ::double_rectangle(pimage->size()));

   ::image::image_drawing_options imagedrawingoptions(rectangle());

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   return pgraphics->draw(imagedrawing);

}


void image::_draw_raw(const ::int_rectangle& rectangleDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam)
{

   ::image::image* pimageDst = this;

   if (!pimageDst->m_bMapped || !pimageSrc->m_bMapped)
   {

      //get_graphics()->set_alpha_mode(m_ealphamode);

      ::image::image_source imagesource(pimageSrc, { pointSrcParam, rectangleDstParam.size() } );

      double_rectangle rectangle(rectangleDstParam);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      return get_graphics()->draw(imagedrawing);

   }

   pimageDst->map();

   pimageSrc->map();

   ::int_rectangle rectangleTarget(rectangleDstParam);

   ::int_point pointSrc(pointSrcParam);

   rectangleTarget += m_point;

   if (pointSrc.x < 0)
   {

      rectangleTarget.left -= pointSrc.x;

      pointSrc.x = 0;

   }

   if (pointSrc.y < 0)
   {

      rectangleTarget.top -= pointSrc.y;

      pointSrc.y = 0;

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

   int xEnd = minimum(rectangleTarget.width(), minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectangleTarget.left));

   int yEnd = minimum(rectangleTarget.height(), minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectangleTarget.top));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * rectangleTarget.top + rectangleTarget.left * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

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


void image::blend(const ::int_rectangle& rectangleDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam, unsigned char bA)
{

   ::image::image* pimageDst = this;

   pimageDst->map();

   pimageSrc->map();

   ::int_rectangle rectangleTarget(rectangleDstParam);

   ::int_point pointSrc(pointSrcParam);

   ::int_size size(rectangleTarget.size());

   rectangleTarget += m_point;

   if (pointSrc.x < 0)
   {

      rectangleTarget.left -= pointSrc.x;

      pointSrc.x = 0;

   }

   if (pointSrc.y < 0)
   {

      rectangleTarget.top -= pointSrc.y;

      pointSrc.y = 0;

   }

   if (rectangleTarget.left < 0)
   {

      size.cx += rectangleTarget.left;

      rectangleTarget.left = 0;

   }

   if (size.cx < 0)
   {

      //return true;

      return;

   }

   if (rectangleTarget.top < 0)
   {

      size.cy += rectangleTarget.top;

      rectangleTarget.top = 0;

   }

   if (size.cy < 0)
   {

      //return true;

      return;

   }

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectangleTarget.left));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectangleTarget.top));

   if (xEnd < 0)
   {

      //return false;

      return;

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * rectangleTarget.top + rectangleTarget.left * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   unsigned char* pdst2;

   unsigned char* psrc2;

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


void image::blend2(const ::int_point& pointDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam, const ::int_size& sizeParam, unsigned char bA)
{

   ::image::image* pimageDst = this;

   pimageDst->map();

   pimageSrc->map();

   ::int_point pointDst(pointDstParam);

   ::int_point pointSrc(pointSrcParam);

   ::int_size size(sizeParam);

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

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

   unsigned char * pdst = ((unsigned char *)pimageDst->image32()) + (scanDst * pointDst.y) + (pointDst.x * sizeof(image32_t));

   unsigned char * psrc = ((unsigned char *)pimageSrc->image32()) + (scanSrc * pointSrc.y) + (pointSrc.x * sizeof(image32_t));

   unsigned char * pdst2;

   unsigned char * psrc2;

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
            //unsigned char acomplement = (~psrc2[3] * bA) >> 8;
            //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
            //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
            //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
            //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
            unsigned char acomplement = (~psrc2[3] * bA) >> 8;
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


void image::blend(const ::int_point& pointDst, ::image::image* pimageSrc, const ::int_point& pointSrc, const ::int_size& size)
{

   return blend(pointDst, pimageSrc, pointSrc, size, 255);

}


void image::blend(const ::int_point& pointDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam, const ::int_size& sizeParam, unsigned char bA)
{

   ::image::image* pimageDst = this;

   ::int_point pointDst(pointDstParam);

   ::int_point pointSrc(pointSrcParam);

   ::int_size size(sizeParam);


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

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
   {

      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;


   unsigned char* pdst2;

   unsigned char* psrc2;

#ifdef __APPLE__
   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * (pimageDst->height() - pointDst.y - yEnd) + pointDst.x * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * (pimageSrc->height() - pointSrc.y - yEnd) + pointSrc.x * sizeof(image32_t)];

#else

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

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
               unsigned char acomplement = ~psrc2[3];
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
               //unsigned char acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               unsigned char acomplement = (~psrc2[3] * bA) >> 8;
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

            //::memory_copy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               unsigned char a = pdst2[3];
               unsigned char alpha = psrc2[3];
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
               //unsigned char acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               unsigned char acomplement = (~psrc2[3] * bA) >> 8;
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


void image::precision_blend(const ::int_point& pointDst, ::image::image* pimageSrc, const ::int_point& pointSrc, const ::int_size& size)
{

   return precision_blend(pointDst, pimageSrc, pointSrc, size, 255);

}


void image::precision_blend(const ::int_point& pointDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam, const ::int_size& sizeParam, unsigned char bA)
{

   ::image::image* pimageDst = this;

   ::int_point pointDst(pointDstParam);

   ::int_point pointSrc(pointSrcParam);

   ::int_size size(sizeParam);

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

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

   if (xEnd < 0)
   {
    
      throw ::exception(error_failed);

   }

   if (yEnd < 0)
   {

      throw ::exception(error_failed);

   }

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   unsigned char* pdst2;

   unsigned char* psrc2;

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
            unsigned char acomplement = ~psrc2[3];
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
            //unsigned char acomplement = (~psrc2[3] * bA) >> 8;
            //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
            //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
            //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
            //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
            unsigned char acomplement = (~psrc2[3] * bA) / 255;
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


void image::fork_blend(const ::int_point& pointDst, ::image::image* pimageSrc, const ::int_point& pointSrc, const ::int_size& size)
{

   //return 
   
   fork_blend(pointDst, pimageSrc, pointSrc, size, 255);

}


void image::fork_blend(const ::int_point& pointDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam, const ::int_size& sizeParam, unsigned char bA)
{

   if (bA == 0)
   {

      //return true;

      return;

   }

   ::image::image* pimageDst = this;

   ::int_point pointDst(pointDstParam);

   ::int_point pointSrc(pointSrcParam);

   ::int_size size(sizeParam);

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

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

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

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   //unsigned char * pdst5; // dst opacity map if available // opacity map does not make sense for images that machine

   unsigned char* psrcOpacity; // src opacity map if available

   unsigned char* psrcTransparency; // src transparency map if available

   if (pimageSrc->m_memoryMap.size() == pimageSrc->area() * 2)
   {

      psrcOpacity = &pimageSrc->m_memoryMap.data()[pimageSrc->width() * pointSrc.y + pointSrc.x];

   }
   else
   {

      psrcOpacity = nullptr;

   }

   if (pimageSrc->m_memoryMap.size() == pimageSrc->area() * 2)
   {

      psrcTransparency = &pimageSrc->m_memoryMap.data()[pimageSrc->area() + pimageSrc->width() * pointSrc.y + pointSrc.x];

   }
   else
   {

      psrcTransparency = nullptr;

   }

   ::pointer<::aura::system>psystem = system();

   auto pgroup = psystem->task_group();

   synchronous_lock slGroup(pgroup->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto ptool = psystem->task_tool(::e_task_tool_draw2d);

   synchronous_lock slTool(ptool->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

   pgroup->call();

   //return true;

}


void image::draw_ignore_alpha(const ::int_point& pointDstParam, ::image::image* pimage, const ::int_rectangle& rectangleSrcParam)
{

   ::int_point pointDst(pointDstParam);

   ::int_point pointSrc(rectangleSrcParam.top_left());

   ::int_size size(rectangleSrcParam.size());

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

   int xEnd = minimum(size.cx, minimum(pimage->width() - pointSrc.x, width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimage->height() - pointSrc.y, height() - pointDst.y));

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   int s1 = m_iScan / sizeof(image32_t);

   int s2 = pimage->m_iScan / sizeof(image32_t);

   image32_t* pdst = &image32()[s1 * pointDst.y] + pointDst.x;

   image32_t* psrc = &pimage->image32()[s2 * pointSrc.y] + pointSrc.x;

   image32_t* pdst2;

   image32_t* psrc2;

   int i = 0;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = &pdst[s1 * y];

      psrc2 = &psrc[s2 * y];

      for (int x = 0; x < xEnd; x++)
      {

         if (psrc2->byte_opacity(pimage->color_indexes()) == 0)
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


void image::blend(const ::int_point& pointDstParam, ::image::image* pimageSrc, const ::int_point& pointSrcParam, ::image::image* pimageAlf, const ::int_point& pointDstAlfParam, const ::int_size& sizeParam)
{

   ::image::image* pimageDst = this;

   pimageDst->map();
   pimageSrc->map();
   pimageAlf->map();

   ::int_point pointDst(pointDstParam);

   ::int_point pointSrc(pointSrcParam);

   ::int_point pointDstAlf(pointDstAlfParam);

   ::int_size size(sizeParam);

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

   int xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - pointDst.x));

   int yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - pointDst.y));

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

   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

   int scanAlf = pimageAlf->m_iScan;

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

   unsigned char* psrc = &((unsigned char*)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)];

   unsigned char* palf = &((unsigned char*)pimageAlf->image32())[-scanAlf * pointDstAlf.y - pointDstAlf.x * sizeof(image32_t)] + 3;

   unsigned char* pdst2;

   unsigned char* psrc2;

   //unsigned char* palf2;

   //int x1;
   //int x2;
   //int y1;
   //int y2;

   //x1 = pointDstAlf.x;
   //x2 = pimageAlf->width() + x1;
   //y1 = pointDstAlf.y;
   //y2 = pimageAlf->height() + y1;


   //int a;

   for (int y = 0; y < yEnd; y++)
   {

      pdst2 = (unsigned char*)&pdst[scanDst * y];

      psrc2 = (unsigned char*)&psrc[scanSrc * y];

      //palf2 = (unsigned char*)&palf[scanAlf * y];

      for (int x = 0; x < xEnd; x++)
      {

         if (psrc2[3] > 0)
         {
            //               if (false && x >= x1 && x < x2 && y >= y1 && y < y2)
            //               {
            //
            //                  a = (*palf2 * psrc2[3]) / 255;
            //                  a = psrc2[3];
            //                  //a = (int) (unsigned char) sqrt((float) (*palf2 * psrc2[3]));
            //                  pdst2[3] = (unsigned char)maximum(a, pdst2[3]);
            //                  //pdst2[3] = (unsigned char)((((int)psrc2[3] - (int)pdst2[3]) * a + ((int)pdst2[3] * 255)) / 255);
            //                  pdst2[3] = (unsigned char)(maximum(psrc2[3], pdst2[3]));
            //
            //                  //                  if (a > 0)
            //                  {
            //
            //                     pdst2[0] = (unsigned char)((((int)psrc2[0] - (int)pdst2[0]) * a + ((int)pdst2[0] * 255)) / 255);
            //                     pdst2[1] = (unsigned char)((((int)psrc2[1] - (int)pdst2[1]) * a + ((int)pdst2[1] * 255)) / 255);
            //                     pdst2[2] = (unsigned char)((((int)psrc2[2] - (int)pdst2[2]) * a + ((int)pdst2[2] * 255)) / 255);
            //
            //                  }
            //
            //               }
            //               else
            {

               //pdst2[3] = (unsigned char)(maximum(psrc2[3], pdst2[3]));
               //pdst2[3] = (unsigned char)((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255);
               //pdst2[0] = (unsigned char)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
               //pdst2[1] = (unsigned char)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
               //pdst2[2] = (unsigned char)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);
               pdst2[3] = (unsigned char)(maximum(((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255), pdst2[3]));
               pdst2[0] = (unsigned char)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
               pdst2[1] = (unsigned char)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
               pdst2[2] = (unsigned char)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);

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
void image::blend(const ::int_point & pointDst,::image::image *pimageSrc, const ::int_point & pointSrc, const ::int_size & size)
{

   ::image::image *pimageDst = this;

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



   int scanDst = pimageDst->m_iScan;

   int scanSrc = pimageSrc->m_iScan;

#ifdef __APPLE__

   unsigned char * pdst = &((unsigned char *)pimageDst->image32())[scanDst * (pimageDst->height() - pointDst.y - 1) + pointDst.x * sizeof(image32_t)] + 3;

   unsigned char * psrc = &((unsigned char *)pimageSrc->image32())[scanSrc * (pimageSrc->height() - pointSrc.y - 1) + pointSrc.x * sizeof(image32_t)] + 3;

#else

   unsigned char * pdst = &((unsigned char *)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)] + 3;

   unsigned char * psrc = &((unsigned char *)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(image32_t)] + 3;

#endif

   unsigned char * pdst2;

   unsigned char * psrc2;

   pimageDst->div_alpha(pointDst, ::int_size(xEnd, yEnd));
   pimageSrc->div_alpha(pointSrc, ::int_size(xEnd, yEnd));


   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (unsigned char *) &pdst[scanDst * (-y)];

      psrc2 = (unsigned char *) &psrc[scanSrc * (-y)];

#else

      pdst2 = (unsigned char *) &pdst[scanDst * y];

      psrc2 = (unsigned char *) &psrc[scanSrc * y];

#endif

      for (int x = 0; x < xEnd; x++)
      {

         *pdst2 = *psrc2 * *pdst2 / 255;

         pdst2+=4;

         psrc2+=4;

      }

   }
   pimageDst->mult_alpha(pointDst, ::int_size(xEnd, yEnd));
   pimageSrc->mult_alpha(pointSrc, ::int_size(xEnd, yEnd));

   return true;

}
*/


void image::set_rgb(int R, int G, int B)
{

   long long size = scan_area();

   image32_t* pcr = data();

   if (pcr == nullptr)
   {

      //return false;

      return;

   }

   sort_image_rgb(R, G, B);

   for (int i = 0; i < size; i++)
   {

      ((unsigned char*)pcr)[0] = R;
      ((unsigned char*)pcr)[1] = G;
      ((unsigned char*)pcr)[2] = B;

      pcr++;

   }

   //return true;

}


/*   void image::Fill ( int R, int G, int B )
   {
      image32_t color=rgb ( B, G, R );
      long long size = area();

      image32_t * pcr;

      long long iSize32 = size / 32;
      int i;
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

      for (i=0; i<int_size; i++ )
      {
         data()[i]=color;
      }
   }
   */


//void image::flip_vertical(::image::image* pimage)
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
//   for (::collection::index y = 0; y < h; y++)
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
//void image::flip_horizontal(::image::image* pimageSource)
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
//   for (::collection::index y = 0; y < h; y++)
//   {
//
//      for (::collection::index x = 0; x < w; x++)
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

   for (::collection::index y = 0; y < h; y++)
   {

      for (::collection::index x = 0; x < halfw; x++)
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

   for (::collection::index y = 0; y < halfh; y++)
   {

      auto plineFirstHalf = pimage32 + (y * sw);

      auto plineSecondHalf = pimage32 + ((h - y - 1) * sw);

      memory_copy(line.data(), plineFirstHalf, m_iScan);
      memory_copy(plineFirstHalf, plineSecondHalf, m_iScan);
      memory_copy(plineSecondHalf, line.data(), m_iScan);

   }

   //return true;

}


//void image::flipx(::image::image* pimage)
//{
//
//   //return 
//   
//   flip_horizontal(pimage);
//
//}
//
//
//void image::flipy(::image::image* pimage)
//{
//
//   //return 
//   
//   flip_vertical(pimage);
//
//}
//


::image::image_pointer image::horizontally_flipped()
{

   ::image::image_pointer pimage = this->clone();

   pimage->flip_horizontally();

   return pimage;

}


::image::image_pointer image::vertically_flipped()
{

   ::image::image_pointer pimage = this->clone();

   pimage->flip_vertically();

   return pimage;

}


void image::ToAlpha(int i)
{
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[3] = dst[i];
      dst += 4;
   }

   //return true;

}


void image::from_alpha()
{

   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();

   while (size--)
   {
      dst[0] = dst[3];
      dst[1] = dst[3];
      dst[2] = dst[3];
      dst += 4;
   }

   //return true;

}


void image::mult_alpha(::image::image* pimage, bool bPreserveAlpha)
{
   __UNREFERENCED_PARAMETER(pimage);
   __UNREFERENCED_PARAMETER(bPreserveAlpha);

   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = lower_byte(((int)dst[0] * (int)dst[3]) >> 8);
      dst[1] = lower_byte(((int)dst[1] * (int)dst[3]) >> 8);
      dst[2] = lower_byte(((int)dst[2] * (int)dst[3]) >> 8);

      dst[4 + 0] = lower_byte(((int)dst[4 + 0] * (int)dst[4 + 3]) >> 8);
      dst[4 + 1] = lower_byte(((int)dst[4 + 1] * (int)dst[4 + 3]) >> 8);
      dst[4 + 2] = lower_byte(((int)dst[4 + 2] * (int)dst[4 + 3]) >> 8);

      dst[8 + 0] = lower_byte(((int)dst[8 + 0] * (int)dst[8 + 3]) >> 8);
      dst[8 + 1] = lower_byte(((int)dst[8 + 1] * (int)dst[8 + 3]) >> 8);
      dst[8 + 2] = lower_byte(((int)dst[8 + 2] * (int)dst[8 + 3]) >> 8);

      dst[12 + 0] = lower_byte(((int)dst[12 + 0] * (int)dst[12 + 3]) >> 8);
      dst[12 + 1] = lower_byte(((int)dst[12 + 1] * (int)dst[12 + 3]) >> 8);
      dst[12 + 2] = lower_byte(((int)dst[12 + 2] * (int)dst[12 + 3]) >> 8);

      dst[16 + 0] = lower_byte(((int)dst[16 + 0] * (int)dst[16 + 3]) >> 8);
      dst[16 + 1] = lower_byte(((int)dst[16 + 1] * (int)dst[16 + 3]) >> 8);
      dst[16 + 2] = lower_byte(((int)dst[16 + 2] * (int)dst[16 + 3]) >> 8);

      dst[20 + 0] = lower_byte(((int)dst[20 + 0] * (int)dst[20 + 3]) >> 8);
      dst[20 + 1] = lower_byte(((int)dst[20 + 1] * (int)dst[20 + 3]) >> 8);
      dst[20 + 2] = lower_byte(((int)dst[20 + 2] * (int)dst[20 + 3]) >> 8);

      dst[24 + 0] = lower_byte(((int)dst[24 + 0] * (int)dst[24 + 3]) >> 8);
      dst[24 + 1] = lower_byte(((int)dst[24 + 1] * (int)dst[24 + 3]) >> 8);
      dst[24 + 2] = lower_byte(((int)dst[24 + 2] * (int)dst[24 + 3]) >> 8);

      dst[28 + 0] = lower_byte(((int)dst[28 + 0] * (int)dst[28 + 3]) >> 8);
      dst[28 + 1] = lower_byte(((int)dst[28 + 1] * (int)dst[28 + 3]) >> 8);
      dst[28 + 2] = lower_byte(((int)dst[28 + 2] * (int)dst[28 + 3]) >> 8);

      dst += 4 * 8;
      size -= 8;
   }
   while (size--)
   {
      dst[0] = lower_byte(((int)dst[0] * (int)dst[3]) >> 8);
      dst[1] = lower_byte(((int)dst[1] * (int)dst[3]) >> 8);
      dst[2] = lower_byte(((int)dst[2] * (int)dst[3]) >> 8);
      dst += 4;
   }

   //return true;

}


#define byte_clip2(i) (i)
void image::mult_alpha()
{
   map();

   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();


   //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size >= 8)
   {
      dst[0] = byte_clip2(((int)dst[0] * (int)dst[3]) / 255);
      dst[1] = byte_clip2(((int)dst[1] * (int)dst[3]) / 255);
      dst[2] = byte_clip2(((int)dst[2] * (int)dst[3]) / 255);

      dst[4 + 0] = byte_clip2(((int)dst[4 + 0] * (int)dst[4 + 3]) / 255);
      dst[4 + 1] = byte_clip2(((int)dst[4 + 1] * (int)dst[4 + 3]) / 255);
      dst[4 + 2] = byte_clip2(((int)dst[4 + 2] * (int)dst[4 + 3]) / 255);

      dst[8 + 0] = byte_clip2(((int)dst[8 + 0] * (int)dst[8 + 3]) / 255);
      dst[8 + 1] = byte_clip2(((int)dst[8 + 1] * (int)dst[8 + 3]) / 255);
      dst[8 + 2] = byte_clip2(((int)dst[8 + 2] * (int)dst[8 + 3]) / 255);

      dst[12 + 0] = byte_clip2(((int)dst[12 + 0] * (int)dst[12 + 3]) / 255);
      dst[12 + 1] = byte_clip2(((int)dst[12 + 1] * (int)dst[12 + 3]) / 255);
      dst[12 + 2] = byte_clip2(((int)dst[12 + 2] * (int)dst[12 + 3]) / 255);

      dst[16 + 0] = byte_clip2(((int)dst[16 + 0] * (int)dst[16 + 3]) / 255);
      dst[16 + 1] = byte_clip2(((int)dst[16 + 1] * (int)dst[16 + 3]) / 255);
      dst[16 + 2] = byte_clip2(((int)dst[16 + 2] * (int)dst[16 + 3]) / 255);

      dst[20 + 0] = byte_clip2(((int)dst[20 + 0] * (int)dst[20 + 3]) / 255);
      dst[20 + 1] = byte_clip2(((int)dst[20 + 1] * (int)dst[20 + 3]) / 255);
      dst[20 + 2] = byte_clip2(((int)dst[20 + 2] * (int)dst[20 + 3]) / 255);

      dst[24 + 0] = byte_clip2(((int)dst[24 + 0] * (int)dst[24 + 3]) / 255);
      dst[24 + 1] = byte_clip2(((int)dst[24 + 1] * (int)dst[24 + 3]) / 255);
      dst[24 + 2] = byte_clip2(((int)dst[24 + 2] * (int)dst[24 + 3]) / 255);

      dst[28 + 0] = byte_clip2(((int)dst[28 + 0] * (int)dst[28 + 3]) / 255);
      dst[28 + 1] = byte_clip2(((int)dst[28 + 1] * (int)dst[28 + 3]) / 255);
      dst[28 + 2] = byte_clip2(((int)dst[28 + 2] * (int)dst[28 + 3]) / 255);

      dst += 4 * 8;
      size -= 8;
   }
   while (size > 0)
   {
      dst[0] = byte_clip2(((int)dst[0] * (int)dst[3]) / 255);
      dst[1] = byte_clip2(((int)dst[1] * (int)dst[3]) / 255);
      dst[2] = byte_clip2(((int)dst[2] * (int)dst[3]) / 255);
      dst += 4;
      size--;
   }

   //return true;

}


void image::mult_alpha_fast()
{
   map();

   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();


   //  >> 2 instead of >> 2 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   while (size--)
   {
      if (dst[3] == 0)
      {
         *((image32_t *)dst) = {};
      }
      else if (dst[3] != 255)
      {
         dst[0] = byte_clip2(((int)dst[0] * (int)dst[3]) >> 8);
         dst[1] = byte_clip2(((int)dst[1] * (int)dst[3]) >> 8);
         dst[2] = byte_clip2(((int)dst[2] * (int)dst[3]) >> 8);
      }
      dst += 4;
   }

   //return true;

}


void image::mult_alpha(const ::int_point& pointDstParam, const ::int_size& sizeParam)
{

   ::int_point pointDst(pointDstParam);

   ::int_size size(sizeParam);

   ::image::image* pimageDst = this;

   pimageDst->map();

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

   int xEnd = minimum(size.cx, pimageDst->width() - pointDst.x);

   int yEnd = minimum(size.cy, pimageDst->height() - pointDst.y);

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

   int scanDst = pimageDst->m_iScan;

#ifdef __APPLE__

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * (height() - pointDst.y - 1) + pointDst.x * sizeof(image32_t)];

#else

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

#endif

   unsigned char* pdst2;

   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (unsigned char*)&pdst[scanDst * (-y)];

#else

      pdst2 = (unsigned char*)&pdst[scanDst * y];

#endif

      for (int x = 0; x < xEnd; x++)
      {

         pdst2[0] = byte_clip(((int)pdst2[0] * (int)pdst2[3]) / 255);
         pdst2[1] = byte_clip(((int)pdst2[1] * (int)pdst2[3]) / 255);
         pdst2[2] = byte_clip(((int)pdst2[2] * (int)pdst2[3]) / 255);

         pdst2 += 4;

      }

   }

   //return true;

}


void image::create_thumbnail(const ::scoped_string & scopedstr)
{

   //return false;

}


void image::div_alpha()
{

   map();

   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();


   // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


   /*      while (size >= 8)
         {
            dst[0] = lower_byte(((int)dst[0] * (int)dst[3])>> 8);
            dst[1] = lower_byte(((int)dst[1] * (int)dst[3])>> 8);
            dst[2] = lower_byte(((int)dst[2] * (int)dst[3])>> 8);

            dst[4+0] = lower_byte(((int)dst[4+0] * (int)dst[4+3])>> 8);
            dst[4+1] = lower_byte(((int)dst[4+1] * (int)dst[4+3])>> 8);
            dst[4+2] = lower_byte(((int)dst[4+2] * (int)dst[4+3])>> 8);

            dst[8+0] = lower_byte(((int)dst[8+0] * (int)dst[8+3])>> 8);
            dst[8+1] = lower_byte(((int)dst[8+1] * (int)dst[8+3])>> 8);
            dst[8+2] = lower_byte(((int)dst[8+2] * (int)dst[8+3])>> 8);

            dst[12+0] = lower_byte(((int)dst[12+0] * (int)dst[12+3])>> 8);
            dst[12+1] = lower_byte(((int)dst[12+1] * (int)dst[12+3])>> 8);
            dst[12+2] = lower_byte(((int)dst[12+2] * (int)dst[12+3])>> 8);

            dst[16+0] = lower_byte(((int)dst[16+0] * (int)dst[16+3])>> 8);
            dst[16+1] = lower_byte(((int)dst[16+1] * (int)dst[16+3])>> 8);
            dst[16+2] = lower_byte(((int)dst[16+2] * (int)dst[16+3])>> 8);

            dst[20+0] = lower_byte(((int)dst[20+0] * (int)dst[20+3])>> 8);
            dst[20+1] = lower_byte(((int)dst[20+1] * (int)dst[20+3])>> 8);
            dst[20+2] = lower_byte(((int)dst[20+2] * (int)dst[20+3])>> 8);

            dst[24+0] = lower_byte(((int)dst[24+0] * (int)dst[24+3])>> 8);
            dst[24+1] = lower_byte(((int)dst[24+1] * (int)dst[24+3])>> 8);
            dst[24+2] = lower_byte(((int)dst[24+2] * (int)dst[24+3])>> 8);

            dst[28+0] = lower_byte(((int)dst[28+0] * (int)dst[28+3])>> 8);
            dst[28+1] = lower_byte(((int)dst[28+1] * (int)dst[28+3])>> 8);
            dst[28+2] = lower_byte(((int)dst[28+2] * (int)dst[28+3])>> 8);

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
         dst[0] = byte_clip((int)dst[0] * 255 / (int)dst[3]);
         dst[1] = byte_clip((int)dst[1] * 255 / (int)dst[3]);
         dst[2] = byte_clip((int)dst[2] * 255 / (int)dst[3]);
      }

      dst += 4;

   }

   //return true;

}


void image::div_alpha(const ::int_point& pointDstParam, const ::int_size& sizeParam)
{

   ::int_point pointDst(pointDstParam);

   ::int_size size(sizeParam);


   ::image::image* pimageDst = this;

   pimageDst->map();

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


   int xEnd = minimum(size.cx, pimageDst->width() - pointDst.x);

   int yEnd = minimum(size.cy, pimageDst->height() - pointDst.y);

   if (xEnd < 0)
   {

      return;

   }

   if (yEnd < 0)
   {

      return;

   }

   int scanDst = pimageDst->m_iScan;

#ifdef __APPLE__

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * (height() - pointDst.y - 1) + pointDst.x * sizeof(image32_t)];

#else

   unsigned char* pdst = &((unsigned char*)pimageDst->image32())[scanDst * pointDst.y + pointDst.x * sizeof(image32_t)];

#endif

   unsigned char* pdst2;

   for (int y = 0; y < yEnd; y++)
   {

#ifdef __APPLE__

      pdst2 = (unsigned char*)&pdst[scanDst * (-y)];

#else

      pdst2 = (unsigned char*)&pdst[scanDst * y];

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
            pdst2[0] = byte_clip((int)pdst2[0] * 255 / (int)pdst2[3]);
            pdst2[1] = byte_clip((int)pdst2[1] * 255 / (int)pdst2[3]);
            pdst2[2] = byte_clip((int)pdst2[2] * 255 / (int)pdst2[3]);
         }

         pdst2 += 4;

      }

   }

   //return true;

}


void image::Map(int ToRgb, int FromRgb)
{

   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();

   while (size--)
   {

      *dst = (unsigned char)(*dst == FromRgb ? ToRgb : *dst);

      dst += 4;

   }

   //return true;

}


void image::ToAlphaAndFill(int i, ::color::color color)
{

   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();

   unsigned char uchB = color.byte_blue();
   unsigned char uchG = color.byte_green();
   unsigned char uchR = color.byte_red();

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

   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();

   unsigned int dwB = color.byte_blue();
   unsigned int dwG = color.byte_green();
   unsigned int dwR = color.byte_red();

   while (size-- > 0)
   {
      dst[3] = dst[0];
      dst[0] = (unsigned char)(((dwB * dst[3]) / 256) & 0xff);
      dst[1] = (unsigned char)(((dwG * dst[3]) / 256) & 0xff);
      dst[2] = (unsigned char)(((dwR * dst[3]) / 256) & 0xff);
      dst += 4;
   }

   //return true;

}


void image::BitBlt(::image::image* pimage, int op)
{

   if (op == 123) // zero dest rgb, invert alpha, and OR src rgb
   {

      throw ::exception(todo);
      //stretch(pimage);

   }

   //return true;

}


void image::BitBlt(int cxParam, int cyParam, ::image::image* pimage, int op)
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

   long long size = scan_area();
   unsigned char* pb = (unsigned char*)data();

   for (int i = 0; i < size; i++)
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

   long long size = scan_area();

   unsigned char* pb = (unsigned char*)data();


   pb += ((int)echannel) % 4;


   for (int i = 0; i < size; i++)
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
   long long size = scan_area();
   unsigned char* pb = (unsigned char*)data();

   pb += ((int)echannel) % 4;

   int iDiv = 256 * 256;
   int iMul = (int)(dRate * ((double)iDiv));
   int iRes;
   for (long long i = 0; i < size; i++)
   {
      iRes = *pb * iMul / iDiv;

      *pb = (unsigned char)(iRes > 255 ? 255 : iRes);

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


void image::channel_multiply(::color::enum_channel echannel, ::image::image* pimage, bool bIfAlphaIgnorePreDivPosMult)
{

   //      long long size = area();

   map();

   pimage->map();
   if (!bIfAlphaIgnorePreDivPosMult && echannel == ::color::e_channel_opacity)
   {
      div_alpha();
   }

   unsigned char* pb1 = (unsigned char*)data();


   unsigned char* pb2 = (unsigned char*)pimage->data();


   pb1 += ((int)echannel) % 4;


   pb2 += ((int)echannel) % 4;


   for (int y = 0; y < height(); y++)
   {

      unsigned char* pb1_2 = pb1 + (m_iScan * y);


      unsigned char* pb2_2 = pb2 + (pimage->m_iScan * y);


      for (int x = 0; x < width(); x++)
      {

         int i = (unsigned char)(((unsigned int)*pb1_2 * (unsigned int)*pb2_2) / 255);

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


void image::channel_darken(::color::enum_channel echannel, ::image::image* pimage)
{

   long long size = scan_area();

   unsigned char* pb1 = (unsigned char*)data();

   unsigned char* pb2 = (unsigned char*)pimage->data();

   pb1 += ((int)echannel) % 4;

   pb2 += ((int)echannel) % 4;

   for (long long i = 0; i < size; i++)
   {
      *pb1 = *pb1 < *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void image::channel_lighten(::color::enum_channel echannel, ::image::image* pimage)
{

   long long size = scan_area();
   unsigned char* pb1 = (unsigned char*)data();

   unsigned char* pb2 = (unsigned char*)pimage->data();

   pb1 += ((int)echannel) % 4;

   pb2 += ((int)echannel) % 4;

   for (long long i = 0; i < size; i++)
   {
      *pb1 = *pb1 > *pb2 ? *pb1 : *pb2;

      pb1 += 4;

      pb2 += 4;

   }

   //return true;

}


void image::channel_from(::color::enum_channel echannel, ::image::image* pimage)
{

   map();

   pimage->map();

   long long size = m_iScan * height() / sizeof(image32_t);

   long long long_long_size = size / 64;

   unsigned char* pb1 = (unsigned char*)data();

   unsigned char* pb2 = (unsigned char*)pimage->data();

   pb1 += ((int)echannel) % 4;

   pb2 += ((int)echannel) % 4;

   long long i = 0;
   for (; i < long_long_size; i++)
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


void image::channel_from(::color::enum_channel echannel, ::image::image* pimage, const ::int_rectangle& rectangleParam)
{

   map();

   pimage->map();

   ::int_rectangle rectangle;

   if (!rectangle.intersect(this->rectangle(), rectangleParam))
   {

      return;

   }

   if (!rectangle.intersect(pimage->rectangle(), rectangle))
   {

      return;

   }

   unsigned char* pb1 = ((unsigned char*)data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * m_iScan);


   unsigned char* pb2 = ((unsigned char*)pimage->data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * pimage->m_iScan);


   pb1 += ((int)echannel) % 4;


   pb2 += ((int)echannel) % 4;


   int h = rectangle.height();

   int w = rectangle.width();

   for (int i = 0; i < h; i++)
   {

      unsigned char* pb1_2 = pb1;


      unsigned char* pb2_2 = pb2;


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



void image::channel_multiply(::color::enum_channel echannel, ::image::image* pimage, const ::int_rectangle& rectangleParam, bool bIfAlphaIgnorePreDivPosMult)
{

   map();

   pimage->map();

   ::int_rectangle rectangle;

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

   unsigned char* pb1 = ((unsigned char*)data()) + (rectangle.left * sizeof(image32_t) + (height() - rectangle.top - 1) * m_iScan);


   unsigned char* pb2 = ((unsigned char*)pimage->data()) + (rectangle.left * sizeof(image32_t) + (pimage->height() - rectangle.top - 1) * pimage->m_iScan);


#else

   unsigned char* pb1 = ((unsigned char*)data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * m_iScan);


   unsigned char* pb2 = ((unsigned char*)pimage->data()) + (rectangle.left * sizeof(image32_t) + rectangle.top * pimage->m_iScan);


#endif

   pb1 += ((int)echannel) % 4;


   pb2 += ((int)echannel) % 4;


   int h = rectangle.height();

   int w = rectangle.width();

   for (int i = 0; i < h; i++)
   {

      unsigned char* pb1_2 = pb1;


      unsigned char* pb2_2 = pb2;


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


void image::fill_glass(int R, int G, int B, int A)
{

   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();

   while (size--)
   {

      dst[0] = (unsigned char)(((B - dst[0]) * A + (dst[0] << 8)) >> 8);
      dst[1] = (unsigned char)(((G - dst[1]) * A + (dst[1] << 8)) >> 8);
      dst[2] = (unsigned char)(((R - dst[2]) * A + (dst[2] << 8)) >> 8);
      dst += 4;

   }

   //return true;

}


void image::fill_stippled_glass(int R, int G, int B)
{

   image32_t color(rgb(B, G, R), color_indexes());
   int w = width();
   int h = height();

   for (int j = 0; j < w; j++)
   {
      for (int i = 0; i < h; i++)
      {
         data()[j * w + i] = ((i + j) & 0x1) ? data()[j * w + i] : color;
      }
   }

   //return true;

}


//void image::to(::image::image *pimage) const
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


//void image::copy_from(::image::image* pimage, ::eobject eobjectCreate)
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
//   ((::image::image*)pimage)->map();
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
//         ::memory_copy(&((unsigned char*)data())[m_iScan * i], &((unsigned char*)pimage->data())[pimage->m_iScan * i], iScan);
//
//      }
//
//   }
//
//   return true;
//
//}


//void image::bitmap_blend(::draw2d::graphics* pgraphics, const ::int_rectangle& rectangle)
//{
//
//   ::image::image_source imagesource(pgraphics);
//
//
//   return pgraphics->stretch(rectangle, get_graphics()) != false;
//
//
//}


void image::color_blend(::color::color color, unsigned char bAlpha)
{

   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();

   unsigned int dwB = color.byte_blue();
   unsigned int dwG = color.byte_green();
   unsigned int dwR = color.byte_red();

   unsigned int dwB_ = dwB << 8;
   unsigned int dwG_ = dwG << 8;
   unsigned int dwR_ = dwR << 8;

   while (size--)
   {
      dst[0] = (unsigned char)(((dst[0] - dwB) * bAlpha + dwB_) >> 8);
      dst[1] = (unsigned char)(((dst[1] - dwG) * bAlpha + dwG_) >> 8);
      dst[2] = (unsigned char)(((dst[2] - dwG) * bAlpha + dwR_) >> 8);
      dst += 4;
   }

   //return true;

}


void image::op(const ::scoped_string & scopedstr)
{

   if (scopedstr == "horz-__swap")
   {

      map();

      // half width
      int hx = width() / 2;
      // aligned scan
      int as = m_iScan / sizeof(image32_t);

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


::memory image::copy_with_no_stride()
{
   
   memory m;
   m.set_size(area() * 4);
   auto pimage32Target = (image32_t *) m.data();
   pimage32Target->copy(this->width(), this->height(), this->width() * 4, this->data(), this->m_iScan);
   return ::transfer(m);
   
}


::memory image::vertical_swap_copy_with_no_stride()
{
   
   memory m;
   m.set_size(area() * 4);
   auto pimage32Target = (image32_t *) m.data();
   pimage32Target->vertical_swap_copy(this->width(), this->height(), this->width() * 4, this->data(), this->m_iScan);
   return ::transfer(m);
   
}


void image::Blend(::image::image* pimage, int A)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[0] = (unsigned char)(((src[0] - dst[0]) * A + (dst[0] << 8)) >> 8);
      dst[1] = (unsigned char)(((src[1] - dst[1]) * A + (dst[1] << 8)) >> 8);
      dst[2] = (unsigned char)(((src[2] - dst[2]) * A + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
   }

   //return true;

}


void image::Blend(::image::image* pDib, ::image::image* DibA, int A)
{
   if (size() != pDib->size() ||
      size() != DibA->size())
      throw ::exception(error_wrong_state);

   unsigned char* src = (unsigned char*)pDib->data();
   unsigned char* dst = (unsigned char*)data();
   unsigned char* alf = (unsigned char*)DibA->data();
   long long size = scan_area();

   A = 2 - A;

   while (size--)
   {
      dst[0] = (unsigned char)(((src[0] - dst[0]) * alf[A] + (dst[0] << 8)) >> 8);
      dst[1] = (unsigned char)(((src[1] - dst[1]) * alf[A] + (dst[1] << 8)) >> 8);
      dst[2] = (unsigned char)(((src[2] - dst[2]) * alf[A] + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
      alf += 4;
   }

   //return true;

}


void image::Blend(::image::image* pDib, ::image::image* DibA)
{
   if (size() != pDib->size() ||
      size() != DibA->size())
      throw ::exception(error_wrong_state);

   map();
   pDib->map();
   DibA->map();

   unsigned char* src = (unsigned char*)pDib->data();
   unsigned char* dst = (unsigned char*)data();
   unsigned char* alf = ((unsigned char*)DibA->data()) + 3;
   long long size = scan_area();

   while (size--)
   {
      dst[0] = (unsigned char)(((src[0] - dst[0]) * (*alf) + (dst[0] << 8)) >> 8);
      dst[1] = (unsigned char)(((src[1] - dst[1]) * (*alf) + (dst[1] << 8)) >> 8);
      dst[2] = (unsigned char)(((src[2] - dst[2]) * (*alf) + (dst[2] << 8)) >> 8);
      dst += 4;
      src += 4;
      alf += 4;
   }

   //return true;

}



void image::blend(::image::image* pimage, ::image::image* pimageRate)
{
   if (size() != pimage->size() ||
      size() != pimageRate->size())
      throw ::exception(error_wrong_state);

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   unsigned char* alf = (unsigned char*)pimageRate->data();
   long long size = scan_area();

   while (size >= 2)
   {
      dst[00] = (unsigned char)(((((int)src[00] - (int)dst[00]) * (int)alf[00]) + (int)dst[00] * (int)255) / 255);
      dst[01] = (unsigned char)(((((int)src[01] - (int)dst[01]) * (int)alf[01]) + (int)dst[01] * (int)255) / 255);
      dst[02] = (unsigned char)(((((int)src[02] - (int)dst[02]) * (int)alf[02]) + (int)dst[02] * (int)255) / 255);
      dst[03] = (unsigned char)(((((int)src[03] - (int)dst[03]) * (int)alf[03]) + (int)dst[03] * (int)255) / 255);
      dst[04] = (unsigned char)(((((int)src[04] - (int)dst[04]) * (int)alf[04]) + (int)dst[04] * (int)255) / 255);
      dst[05] = (unsigned char)(((((int)src[05] - (int)dst[05]) * (int)alf[05]) + (int)dst[05] * (int)255) / 255);
      dst[06] = (unsigned char)(((((int)src[06] - (int)dst[06]) * (int)alf[06]) + (int)dst[06] * (int)255) / 255);
      dst[07] = (unsigned char)(((((int)src[07] - (int)dst[07]) * (int)alf[07]) + (int)dst[07] * (int)255) / 255);
      dst += 4 * 2;
      src += 4 * 2;
      alf += 4 * 2;
      size -= 2;
   }
   while (size > 0)
   {
      dst[00] = (unsigned char)(((((int)src[00] - (int)dst[00]) * (int)alf[00]) + (int)dst[00] * (int)255) / 255);
      dst[01] = (unsigned char)(((((int)src[01] - (int)dst[01]) * (int)alf[01]) + (int)dst[01] * (int)255) / 255);
      dst[02] = (unsigned char)(((((int)src[02] - (int)dst[02]) * (int)alf[02]) + (int)dst[02] * (int)255) / 255);
      dst[03] = (unsigned char)(((((int)src[03] - (int)dst[03]) * (int)alf[03]) + (int)dst[03] * (int)255) / 255);
      dst += 4;
      src += 4;
      alf += 4;
      size--;
   }

   //return true;
}


void image::Darken(::image::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[0] = (unsigned char)((src[0] < dst[0]) ? src[0] : dst[0]);
      dst[1] = (unsigned char)((src[1] < dst[1]) ? src[1] : dst[1]);
      dst[2] = (unsigned char)((src[2] < dst[2]) ? src[2] : dst[2]);
      dst += 4;
      src += 4;
   }

   //return true;

}


void image::Difference(::image::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      int Difference;
      Difference = src[0] - dst[0];
      dst[0] = (unsigned char)((Difference < 0) ? -Difference : Difference);
      Difference = src[1] - dst[1];
      dst[1] = (unsigned char)((Difference < 0) ? -Difference : Difference);
      Difference = src[2] - dst[2];
      dst[2] = (unsigned char)((Difference < 0) ? -Difference : Difference);
      dst += 4;
      src += 4;
   }

   //return true;

}


void image::Lighten(::image::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[0] = (unsigned char)((src[0] > dst[0]) ? src[0] : dst[0]);
      dst[1] = (unsigned char)((src[1] > dst[1]) ? src[1] : dst[1]);
      dst[2] = (unsigned char)((src[2] > dst[2]) ? src[2] : dst[2]);
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
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[0] += (unsigned char)((dst[3] - dst[0]) * dRate);
      dst[1] += (unsigned char)((dst[3] - dst[1]) * dRate);
      dst[2] += (unsigned char)((dst[3] - dst[2]) * dRate);
      dst += 4;
   }

   //return true;

}


void image::Multiply(::image::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[0] = (unsigned char)(((src[0]) * (dst[0])) >> 8);
      dst[1] = (unsigned char)(((src[1]) * (dst[1])) >> 8);
      dst[2] = (unsigned char)(((src[2]) * (dst[2])) >> 8);
      dst += 4;
      src += 4;
   }

   //return true;

}


void image::Screen(::image::image* pimage)
{

   if (size() != pimage->size())
   {

      throw ::exception(error_wrong_state);

   }

   unsigned char* src = (unsigned char*)pimage->data();
   unsigned char* dst = (unsigned char*)data();
   long long size = scan_area();

   while (size--)
   {
      dst[0] = (unsigned char)(255 - (((255 - src[0]) * (255 - dst[0])) >> 8));
      dst[1] = (unsigned char)(255 - (((255 - src[1]) * (255 - dst[1])) >> 8));
      dst[2] = (unsigned char)(255 - (((255 - src[2]) * (255 - dst[2])) >> 8));
      dst += 4;
      src += 4;
   }

   //return true;

}


void image::copy_from_no_create(::image::image *pimage, const ::int_point & point)
{

   ::int_size s(pimage->size() - point);

   auto sizeCopy = ::int_size(::minimum(size().cx, s.cx), ::minimum(size().cy, s.cy));

   if (sizeCopy.area() > 0)
   {

      ::image::image_source imagesource(pimage, { point, sizeCopy });

      ::double_rectangle rectangle(sizeCopy);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

      g()->draw(imagedrawing);
      //{

      //   return false;

      //}

   }

   //return true;

}


void image::copy_from_no_create(::image::image *pimage)
{

   return copy_from_no_create(pimage, {});

}



void image::copy_from(::image::image* pimage, const ::int_point  & point, ::enum_flag eflagCreate)
{

   ::int_size s(pimage->size() - point);

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


void image::copy_from(::image::image *pimage, enum_flag eflagCreate)
{

   return copy_from(pimage, {}, eflagCreate);

}


//void image::copy_to(::image::image* pimage, const int_point & point)
//{
//
//   return pimage->copy_from(this);
//
//}


void image::fill_rectangle(const ::int_rectangle& rectangle, int R, int G, int B)
{

   int x = rectangle.left;

   int y = rectangle.top;

   int w = rectangle.width();

   int h = rectangle.height();

   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + w) < width()) ? w : width() - x;
   int Δy = ((y + h) < height()) ? h : height() - y;
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

      for (int i = 0; i < Δx; i++)
      {

         ((unsigned char*)&dst[i])[0] = R;
         ((unsigned char*)&dst[i])[1] = G;
         ((unsigned char*)&dst[i])[2] = B;

      }

      dst += m_iScan / sizeof(image32_t);

   }

   //return true;

}


void image::fill_rectangle(const ::int_rectangle& rectangle, ::color::color color)
{

   if (m_bMapped)
   {

      int x = rectangle.left;

      int y = rectangle.top;

      int w = rectangle.width();

      int h = rectangle.height();

      ::image32_t u32Color(color, color_indexes());

      // Clip Rect
      int px = x;
      if (w < 0)
      {
         px += w;
         w = -w;
      }

      px = (px >= 0) ? px : 0;
      int py = y;
      if (h < 0)
      {
         py += h;
         h = -h;
      }
      py = (py >= 0) ? py : 0;
      int Δx;
      Δx = ((px + w) < width()) ? w : width() - px;
      int Δy;
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

         for (int i = 0; i < Δx; i++)
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


void image::fill_glass_rect(const ::int_rectangle& rectangle, int R, int G, int B, int A)

{

   int x = rectangle.left;

   int y = rectangle.top;

   int w = rectangle.width();

   int h = rectangle.height();


   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + w) < width()) ? w : width() - x;
   int Δy = ((y + h) < height()) ? h : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to FillGlass return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Address
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do FillGlass
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[0] = (unsigned char)(((B - dst[0]) * A + (dst[0] << 8)) >> 8);
         dst[1] = (unsigned char)(((G - dst[1]) * A + (dst[1] << 8)) >> 8);
         dst[2] = (unsigned char)(((R - dst[2]) * A + (dst[2] << 8)) >> 8);
         dst += 4;
      }

      dst += (width() - Δx) << 2;

   }

   //return true;

}


void image::fill_stippled_glass_rect(const ::int_rectangle& rectangle, int R, int G, int B)

{

   int x = rectangle.left;

   int y = rectangle.top;

   int w = rectangle.width();

   int h = rectangle.height();


   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + w) < width()) ? w : width() - x;
   int Δy = ((y + h) < height()) ? h : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to FillStippledGlass return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Address
   image32_t* dst = data() + (py * width()) + px;
   image32_t color(rgb(B, G, R), color_indexes());

   // Do FillStippledGlass
   for (int j = 0; j < Δy; j++)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[i] = ((i + j) & 0x1) ? dst[i] : color;
      }
      dst += width();
   }

   //return true;

}


void image::BlendRect(::image::image* pimage, int x, int y, int A)
{
   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   int Δy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Blend return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   unsigned char* src = (unsigned char*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do Blend
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[0] = (unsigned char)(((src[0] - dst[0]) * A + (dst[0] << 8)) >> 8);
         dst[1] = (unsigned char)(((src[1] - dst[1]) * A + (dst[1] << 8)) >> 8);
         dst[2] = (unsigned char)(((src[2] - dst[2]) * A + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (pimage->width() - Δx) << 2;
   }

   //return true;

}


void image::DarkenRect(::image::image* pimage, int x, int y)
{
   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   int Δy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Darken return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   unsigned char* src = (unsigned char*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do Darken
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[0] = (unsigned char)((src[0] < dst[0]) ? src[0] : dst[0]);
         dst[1] = (unsigned char)((src[1] < dst[1]) ? src[1] : dst[1]);
         dst[2] = (unsigned char)((src[2] < dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (pimage->width() - Δx) << 2;
   }

   //return true;

}


void image::DifferenceRect(::image::image* pimage, int x, int y)
{
   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   int Δy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Difference return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   unsigned char* src = (unsigned char*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do Difference
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         int Difference;
         Difference = src[0] - dst[0];
         dst[0] = (unsigned char)((Difference < 0) ? -Difference : Difference);
         Difference = src[1] - dst[1];
         dst[1] = (unsigned char)((Difference < 0) ? -Difference : Difference);
         Difference = src[2] - dst[2];
         dst[2] = (unsigned char)((Difference < 0) ? -Difference : Difference);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (pimage->width() - Δx) << 2;
   }

   //return true;

}


void image::LightenRect(::image::image* pimage, int x, int y)
{
   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   int Δy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Lighten return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   unsigned char* src = (unsigned char*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do Lighten
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[0] = (unsigned char)((src[0] > dst[0]) ? src[0] : dst[0]);
         dst[1] = (unsigned char)((src[1] > dst[1]) ? src[1] : dst[1]);
         dst[2] = (unsigned char)((src[2] > dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (pimage->width() - Δx) << 2;
   }

   return;

}


void image::MultiplyRect(::image::image* pimage, int x, int y)
{
   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   int Δy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Multiply return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   unsigned char* src = (unsigned char*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do Multiply
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[0] = (unsigned char)(((src[0]) * (dst[0])) >> 8);
         dst[1] = (unsigned char)(((src[1]) * (dst[1])) >> 8);
         dst[2] = (unsigned char)(((src[2]) * (dst[2])) >> 8);
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (pimage->width() - Δx) << 2;
   }

   //return true;

}


void image::ScreenRect(::image::image* pimage, int x, int y)
{
   // Clip Rect
   int px = (x >= 0) ? x : 0;
   int py = (y >= 0) ? y : 0;
   int Δx = ((x + pimage->width()) < width()) ? pimage->width() : width() - x;
   int Δy = ((y + pimage->height()) < height()) ? pimage->height() : height() - y;
   Δx = (x >= 0) ? Δx : Δx + x;
   Δy = (y >= 0) ? Δy : Δy + y;

   // If Nothing to Screen return
   if ((Δx <= 0) || (Δy <= 0))
      return;

   // Prepare buffer Addresses
   unsigned char* src = (unsigned char*)pimage->data() + (((py - y) * pimage->width()) + px - x) * 4;
   unsigned char* dst = (unsigned char*)data() + ((py * width()) + px) * 4;

   // Do Screen
   while (Δy--)
   {
      for (int i = 0; i < Δx; i++)
      {
         dst[0] = (unsigned char)(255 - (((255 - src[0]) * (255 - dst[0])) >> 8));
         dst[1] = (unsigned char)(255 - (((255 - src[1]) * (255 - dst[1])) >> 8));
         dst[2] = (unsigned char)(255 - (((255 - src[2]) * (255 - dst[2])) >> 8));
         dst += 4;
         src += 4;
      }
      dst += (width() - Δx) << 2;
      src += (pimage->width() - Δx) << 2;
   }

   //return true;

}


//////////////////////////////////////////////////////////////////////
// Line Functions
//////////////////////////////////////////////////////////////////////

/*void image::Line ( int x1, int y1, int x2, int y2, int R, int G, int B )
{
int Δx, Δy, k1, k2, d, x, y;
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


void image::horizontal_line(int y, ::color::color color, int x1, int x2)
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

   image32_t* pdata = (image32_t*)((unsigned char *) data() + x1 * sizeof(image32_t) +  yflipped * (m_iScan));

#else

   image32_t* pdata = (image32_t*)((unsigned char *) data() + x1 * sizeof(image32_t) + y * (m_iScan));

#endif

   for (int x = x1; x <= x2; x++)
   {

      *pdata = u32ImageColor;

      pdata++;

   }

   //return true;

}


void image::vertical_line(int x, ::color::color color, int y1, int y2)
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

   image32_t* pdata = (image32_t*)((unsigned char*)data() + x *sizeof(image32_t) + ((height() - y2 - 1) * m_iScan));

#else

   image32_t* pdata = (image32_t*)((unsigned char*)data() + x *sizeof(image32_t) + (y1 * m_iScan));
   
#endif

   for (int y = y1; y <= y2; y++)
   {

      *pdata = u32ImageColor;

      ((unsigned char*&)pdata)+=m_iScan;

   }

   //return true;

}


void image::frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color)
{

   horizontal_line(y, color, x, x + w - 1);

   vertical_line(x, color, y + 1, y + h - 2);

   horizontal_line(y + h - 1, color, x, x + w - 1);

   vertical_line(x + w - 1, color, y + 1, y + h - 2);

}

void image::frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width)
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


void image::Line(int x1, int y1, int x2, int y2, int R, int G, int B)
{
   int d, x, y, aura, ay, sx, sy, Δx, Δy;
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


void image::LineGlass(int x1, int y1, int x2, int y2, int R, int G, int B, int A)
{
   int d, x, y, aura, ay, sx, sy, Δx, Δy;
   //      image32_t color=rgb ( B, G, R );
   unsigned char* dst = (unsigned char*)data();

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
         dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] = (unsigned char)(((B - dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2]) * A + (dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] = (unsigned char)(((G - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] = (unsigned char)(((R - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] << 8)) >> 8);
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
         dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] = (unsigned char)(((B - dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2]) * A + (dst[(y * (m_iScan / sizeof(image32_t)) + x) << 2] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] = (unsigned char)(((G - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 1] << 8)) >> 8);
         dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] = (unsigned char)(((R - dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2]) * A + (dst[((y * (m_iScan / sizeof(image32_t)) + x) << 2) + 2] << 8)) >> 8);
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

   long long size = scan_area();

   for (int i = 0; i < size; i++)
      if (data()[i] == crFind)
         data()[i] = crSet;
      else
         data()[i] = crUnset;

   //return true;

}


void image::transparent_color(::color::color color)
{

   image32_t crFind(color, color_indexes());

   long long iSize = scan_area();

   for (int i = 0; i < iSize; i++)
   {

      if (data()[i].rgb(color_indexes()) == crFind.rgb(color_indexes()))
      {

         ((unsigned char*)&data()[i])[3] = 255;

      }
      else
      {

         ((unsigned char*)&data()[i])[3] = 0;

      }

   }

   //return true;

}


void image::channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, ::color::enum_channel echannel)
{

   int size = (m_iScan / sizeof(image32_t)) * height();

   uchar* puch = (uchar*)data();

   puch += ((int)echannel) % 4;

   for (int i = 0; i < size; i++)
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


::color::color image::GetPixel(int x, int y)
{

   map();

   unsigned int ui = (data() + x + line(y) * (m_iScan / sizeof(image32_t)))->m_ui;

   unsigned char* p = (unsigned char*)&ui;

   int iOpacity = p[m_colorindexes.m_uchIndexOpacity];

   if (iOpacity == 0)
   {

      return rgb(
         p[m_colorindexes.m_uchIndexRed], 
         p[m_colorindexes.m_uchIndexGreen], 
         p[m_colorindexes.m_uchIndexBlue]);
                            
   }
   else
   {

      return argb(iOpacity,
         p[m_colorindexes.m_uchIndexRed] * 255 / iOpacity,
         p[m_colorindexes.m_uchIndexGreen] * 255 / iOpacity,
         p[m_colorindexes.m_uchIndexBlue] * 255 / iOpacity);

   }

}


// too slow for animation on AMD XP gen_hon.
// TOP SUGGESTION:
// The gradient can't have more then 256 levels of the most bright color
// (white). So creating a radial fill of radius 256 and then using fasting
// stretching algorithms is much faster than calculating radial fill.
void image::RadialFill(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue, int xCenter, int yCenter, int iRadius)
{

   if (iRadius == 0)
   {

      //return false;

      return;

   }

   /*if(version == 0)
   {

   int iR = iRadius - 1;

   int xL = xCenter - iR;
   int xU = xCenter + iR;
   int yL = yCenter - iR;
   int yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(image32_t))) xU = m_Size.(m_iScan / sizeof(image32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   unsigned char *dst = ((unsigned char *)(data() + xL + yL * m_Size.(m_iScan / sizeof(image32_t))));
   unsigned int dwAdd = ((m_Size.(m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
   int size=m_Size.(m_iScan / sizeof(image32_t))*m_Size.height();
   double iLevel;

   int Δx, Δy;
   int dx0, dy0;
   int dx1, dy1;
   int dx2, dy2;
   int dx3, dy3;
   int dx4, dy4;
   int dx5, dy5;
   int dx6, dy6;
   int dx7, dy7;
   int dx8, dy8;
   int dx9, dy9;
   int dxA, dyA;
   int dxB, dyB;
   int dxC, dyC;
   int dxD, dyD;
   int dxE, dyE;
   int dxF, dyF;

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
   int x, y;

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

      unsigned char* pbAlloc = (unsigned char*)malloc(iRadius * iRadius);

      unsigned char* pb = pbAlloc;



      int x, y;
      int b;

      //         int r2 = iRadius * iRadius;

      for (y = 0; y < iRadius; y++)
      {
         for (x = y; x < iRadius; x++)
         {
            b = (int)(sqrt((double)(x * x) + (y * y)) * 255 / iRadius);
            if (b > 255)
               b = 0;
            else
               b = 255 - b;


            pb[x + y * iRadius] = (unsigned char)b;

            pb[y + x * iRadius] = (unsigned char)b;

         }
      }


      int iR = iRadius - 1;

      int xL = xCenter - iR;
      int xU = xCenter + iR;
      int yL = yCenter - iR;
      int yU = yCenter + iR;


      if (xL < 0) xL = 0;
      if (xU >= width()) xU = width() - 1;
      if (yL < 0) yL = 0;
      if (yU >= height()) yU = height() - 1;


      unsigned char* dst = ((unsigned char*)(data() + xL + yL * (m_iScan / sizeof(image32_t))));
      unsigned int dwAdd = (((m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
      //         long long size = area();

      int Δx, Δy;

      // Top Left

      for (y = yL; y <= yU; y++)
      {
         for (x = xL; x <= xU; x++)
         {
            Δx = abs(x - xCenter);
            Δy = abs(y - yCenter);
            b = pb[Δx + Δy * iRadius];

            dst[0] = (unsigned char)(blue * b / 255);
            dst[1] = (unsigned char)(green * b / 255);
            dst[2] = (unsigned char)(red * b / 255);
            dst[3] = (unsigned char)(alpha * b / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

      free(pbAlloc);

   }

   //return true;

}


void image::RadialFill(
   unsigned char alpha1, unsigned char red1, unsigned char green1, unsigned char blue1,
   unsigned char alpha2, unsigned char red2, unsigned char green2, unsigned char blue2,
   int xCenter, int yCenter, int iRadius)
{
   if (iRadius == 0)
      //return false;
      return;

   map();
   /*if(version == 0)
   {

   int iR = iRadius - 1;

   int xL = xCenter - iR;
   int xU = xCenter + iR;
   int yL = yCenter - iR;
   int yU = yCenter + iR;


   if(xL < 0) xL = 0;
   if(xU >= m_Size.(m_iScan / sizeof(image32_t))) xU = m_Size.(m_iScan / sizeof(image32_t)) - 1;
   if(yL < 0) yL = 0;
   if(yU >= m_Size.height()) yU = m_Size.height() - 1;


   unsigned char *dst = ((unsigned char *)(data() + xL + yL * m_Size.(m_iScan / sizeof(image32_t))));
   unsigned int dwAdd = ((m_Size.(m_iScan / sizeof(image32_t)) - 1 - xU) + xL) * 4;
   int size=m_Size.(m_iScan / sizeof(image32_t))*m_Size.height();
   double iLevel;

   int Δx, Δy;
   int dx0, dy0;
   int dx1, dy1;
   int dx2, dy2;
   int dx3, dy3;
   int dx4, dy4;
   int dx5, dy5;
   int dx6, dy6;
   int dx7, dy7;
   int dx8, dy8;
   int dx9, dy9;
   int dxA, dyA;
   int dxB, dyB;
   int dxC, dyC;
   int dxD, dyD;
   int dxE, dyE;
   int dxF, dyF;

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
   int x, y;

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
      //         unsigned char * pbAlloc = mem.data();

      //
      //         unsigned char * pb = pbAlloc;

      //
      //
      //         int x, y;
      //         int b;
      //
      ////         int r2 = iRadius * iRadius;
      //
      //         for(y = 0; y < iRadius; y++)
      //         {
      //            for(x = y; x < iRadius; x++)
      //            {
      //
      //               b = (int) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
      //
      //               if(b > 255)
      //                  b = 255;
      //
      //
      //               pb[x + y * iRadius] = (unsigned char) b;

      //               pb[y + x * iRadius] = (unsigned char) b;

      //            }
      //         }


      int iR = iRadius;

      int xL = xCenter - iR;
      int xU = xCenter + iR;
      int yL = yCenter - iR;
      int yU = yCenter + iR;


      if (xL < 0) xL = 0;
      if (xU > width()) xU = width();
      if (yL < 0) yL = 0;
      if (yU > height()) yU = height();


      unsigned char* dst = ((unsigned char*)(data() + xL + yL * (m_iScan / sizeof(image32_t))));
      unsigned int dwAdd = (((m_iScan / sizeof(image32_t)) - xU) + xL) * 4;
      //         long long size = area();

      double Δx, Δy;

      double dRadius = 255.0 / (double)iRadius;

      unsigned char bComp;

      int b;

      // Top Left

      int y;
      int x;

      for (y = yL; y < yU; y++)
      {
         for (x = xL; x < xU; x++)
         {
            Δx = abs(x - xCenter);
            Δy = abs(y - yCenter);
            b = (int)(sqrt((Δx * Δx) + (Δy * Δy)) * dRadius);

            if (b > 255)
            {
               b = 255;
            }

            bComp = 255 - b;
            dst[0] = (unsigned char)(((blue1 * bComp) + (blue2 * b)) / 255);
            dst[1] = (unsigned char)(((green1 * bComp) + (green2 * b)) / 255);
            dst[2] = (unsigned char)(((red1 * bComp) + (red2 * b)) / 255);
            dst[3] = (unsigned char)(((alpha1 * bComp) + (alpha2 * b)) / 255);
            dst += 4;
         }
         dst += dwAdd;
      }

   }

   //return true;

}



void image::SetIconMask(::image::icon* picon, int cx, int cy)
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
   //      unsigned char * r1 = (unsigned char *)pimage1->data();
   //      unsigned char * r2 = (unsigned char *)pimage2->data();
   //      unsigned char * srcM = (unsigned char *)imageM.data();
   //      unsigned char * dest = (unsigned char *)data();
   //      int iSize = width()*height();
   //
   //      unsigned char b;
   //      unsigned char bMax;
   //      while (iSize-- > 0)
   //      {
   //         if (srcM[0] == 255)
   //         {
   //            bMax = 0;
   //         }
   //         else
   //         {
   //            bMax = 0;
   //            b = (unsigned char)(r1[0] - r2[0]);
   //            bMax = maximum(b, bMax);
   //            b = (unsigned char)(r1[1] - r2[1]);
   //            bMax = maximum(b, bMax);
   //            b = (unsigned char)(r1[2] - r2[2]);
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


void image::rotate(const ::double_angle & angle, double dScale)
{

   ::image::image_pointer pimage = this->clone();

   rotate(pimage, angle, dScale);

}


void image::rotate(::image::image *pimage, const ::double_angle & angle, double dScale)
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

         int cx = pimage->width();

         int cy = pimage->height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (int i = 0; i < cx; i++)
         {

            for (int j = 0; j < cy; j++)
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

         int cx = width();

         int cy = height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (int i = 0; i < cy; i++)
         {

            for (int j = 0; j < cx; j++)
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

         int cx = pimage->width();

         int cy = pimage->height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (int i = 0; i < cx; i++)
         {

            for (int j = 0; j < cy; j++)
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

   int l = maximum(wTarget, hTarget);

   int jmax = minimum(l, hTarget / 2);

   int jmin = -jmax;

   int imax = minimum(l, wTarget / 2);

   int imin = -imax;

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

   for (int j = jmin; j < jmax; j++)
   {

      for (int i = imin; i < imax; i++)
      {

         x = (int)fabs((dCos * i - dSin * j) + xoff);

         y = (int)fabs((dSin * i + dCos * j) + yoff);

         x %= wSource;

         y %= hSource;

         pdataTarget[(j + joff) * dsw + (i + ioff)] = pdataSource[y * ssw + x];

      }

   }

}


::image::image_pointer image::rotated(const ::double_angle & angle, double dScale)
{

   if (dScale == 1.0)
   {

      if (angle.degree() == 90.0)
      {

            auto pimage = ::particle::image()->create_image({height(), width() });

            //if (!create({ pimage->height(), pimage->width() }))
            //{

            //   return false;

            //}

            map();

            pimage->map();

            int cx = width();

            int cy = height();

            int s = m_iScan / sizeof(image32_t);

            int srcS = pimage->m_iScan / sizeof(image32_t);

            for (int i = 0; i < cx; i++)
            {

               for (int j = 0; j < cy; j++)
               {

                  pimage->image32()[i * s + j] = image32()[(cy - j - 1) * srcS + i];

               }

            }

            return pimage;

         }

      else  if (angle.degree() == 180.0)
      {

         auto pimage = ::particle::image()->create_image(size());



         map();

         pimage->map();

         int cx = width();

         int cy = height();

         int s = m_iScan / sizeof(image32_t);

         int srcS = pimage->m_iScan / sizeof(image32_t);

         for (int i = 0; i < cy; i++)
         {

            for (int j = 0; j < cx; j++)
            {

               pimage->image32()[(cy - i - 1) * s + (cx - j - 1)] = image32()[i * srcS + j];

            }

         }

         return pimage;
      }
      else if (angle.degree() ==270.0)
      {

               auto pimage = ::particle::image()->create_image({ height(), width() });

            map();

            pimage->map();

            int cx = width();

            int cy = height();

            int s = m_iScan / sizeof(image32_t);

            int srcS = pimage->m_iScan / sizeof(image32_t);

            for (int i = 0; i < cx; i++)
            {

               for (int j = 0; j < cy; j++)
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

   auto pimage = ::particle::image()->create_image({ b, a });

   map();

   pimage->map();

   int wSource = width();

   int hSource = height();

   auto pdataSource = image32();

   int wTarget = pimage->width();

   int hTarget = pimage->height();

   auto pdataTarget = pimage->image32();

   int l = maximum(wTarget, hTarget);

   int jmax = minimum(l, hTarget / 2);

   int jmin = -jmax;

   int imax = minimum(l, wTarget / 2);

   int imin = -imax;

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

   for (int j = jmin; j < jmax; j++)
   {

      for (int i = imin; i < imax; i++)
      {

         x = (int)fabs((dCos * i - dSin * j) + xoff);

         y = (int)fabs((dSin * i + dCos * j) + yoff);

         x %= wSource;

         y %= hSource;

         pdataTarget[(j + joff) * dsw + (i + ioff)] = pdataSource[y * ssw + x];

      }

   }

   return pimage;

}


//::image::image_pointer image::rotated(const angle& angle, double dScale)
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
//   int l = maximum(wTarget, hTarget);
//
//   int jmax = minimum(l, hTarget / 2);
//
//   int jmin = -jmax;
//
//   int imax = minimum(l, wTarget / 2);
//
//   int imin = -imax;
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
//   for (int j = jmin; j < jmax; j++)
//   {
//
//      for (int i = imin; i < imax; i++)
//      {
//
//         x = (int)fabs((dCos * i - dSin * j) + xoff);
//
//         y = (int)fabs((dSin * i + dCos * j) + yoff);
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

void image::Rotate034(::image::image* pimage, double dAngle, double dScale)
{

   map();
   pimage->map();

   auto hdst = height();
   auto wdst = width();

   auto hsrc = pimage->height();
   auto wsrc = pimage->width();

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

   int ihdstmid = (int)hdstmid;

   auto hsrcmid = hsrc / 2.0;
   auto wsrcmid = wsrc / 2.0;

   //int l = maximum(w, h);

   int jdstmin = (int)-hdstmid;
   int jdstmax = jdstmin + hdst;
   int idstmin = (int)-wdstmid;
   int idstmax = idstmin + wdst;

   int k = 0;

   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;

   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;

   auto pdataSrc = pimage->data();

   auto pdataDst = data();

   int strideSrc = pimage->m_iScan / sizeof(image32_t);

   int strideDst = m_iScan / sizeof(image32_t);

   for (int jdst = jdstmin; jdst < jdstmax; jdst++)
   {

      int lineDst = (int)(jdst + ihdstmid);

      if (lineDst < 0)
      {

         informationf("image::Rotate034 lineDst < 0");

      }

      image32_t* pline = pdataDst + (lineDst * strideDst);

      for (int idst = idstmin; idst < idstmax; idst++)
      {

         int xsrc, ysrc;

         double dj = jdst;
         double di = idst;

         xsrc = (int)((dCos * di - dSin * dj) + wsrcmid);
         ysrc = (int)((dSin * di + dCos * dj) + hsrcmid);

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


//void image::rotated(::image::image* pimage, const ::int_rectangle& rectangle, double dAngle, double dScale)
//
//{
//
//   int l = maximum(width(), height());
//
//   int jmax = minimum(l, height() / 2);
//   int jmin = -jmax;
//   int imax = minimum(l, width() / 2);
//   int imin = -imax;
//
//   int joff = height() / 2 + rectangle.left;
//
//   int ioff = width() / 2 + rectangle.top;
//
//   int stride_unit = m_iScan / sizeof(image32_t);
//   //int iAngle = iStep % 360;
//   //int iAngle = iStep;
//   //int iAngle = 1;
//   //int k = 0;
//
//   /*     for ( int j=jmin; j<jmax; j++ )
//   {
//   for ( int i=imin; i<imax; i++ )
//   {
//   int x, y;
//
//   // A Combination of a 2d Translation/rotation/Scale Matrix
//   x=int(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
//   y=int(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
//   data()[(j+joff)*width()+(i+ioff)]=
//   pimage->data()[abs(y%height())*width()+abs(x%width())];
//   //k++;
//   }
//   (j+joff)*width()+(i+ioff)
//   }*/
//
//   int k = 0;
//   double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
//   double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
//   int cx1 = width() - 1;
//   int cy1 = height() - 1;
//   for (int j = jmin; j < jmax; j++)
//   {
//      for (int i = imin; i < imax; i++)
//      {
//         int x, y;
//
//         // A Combination of a 2d Translation/rotation/Scale Matrix
//         //x=abs((int(dCos * i - dSin * j) + ioff) % width());
//         //y=abs((int(dSin * i + dCos * j) + joff) % height());
//
//         x = (int)fabs((dCos * i - dSin * j) + ioff);
//         y = (int)fabs((dSin * i + dCos * j) + joff);
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
//   ::image::image_pointer pimage = clone();
//
//   return rotate90(pimage);
//
//}
//
//
//void image::rotate180()
//{
//
//   ::image::image_pointer pimage = clone();
//
//   return rotate180(pimage);
//
//}
//
//
//void image::rotate270()
//{
//
//   ::image::image_pointer pimage = clone();
//
//   return rotate270(pimage);
//
//}


void image::e_rotate_90_flip_horizontally(::image::image* pimage)
{

   create(pimage->size());

   map();

   pimage->map();

   int cx = pimage->width();

   int cy = pimage->height();

   int s = m_iScan / sizeof(image32_t);

   int srcS = pimage->m_iScan / sizeof(image32_t);

   for (int i = 0; i < cx; i++)
   {

      for (int j = 0; j < cy; j++)
      {

         image32()[i * s + j] = pimage->image32()[j * srcS + i];

      }

   }

}


void image::e_rotate_180_flip_horizontally(::image::image* pimage)
{

   create(pimage->size());
   
   map();

   pimage->map();

   int cx = width();

   int cy = height();

   int s = m_iScan / sizeof(image32_t);

   int srcS = pimage->m_iScan / sizeof(image32_t);

   for (int i = 0; i < cy; i++)
   {

      for (int j = 0; j < cx; j++)
      {

         image32()[i * s + j] = pimage->image32()[(cy - i - 1) * srcS + j];

      }

   }

}


void image::e_rotate_270_flip_horizontally(::image::image* pimage)
{

   create(pimage->size());

   map();

   pimage->map();

   int cx = pimage->width();

   int cy = pimage->height();

   int s = m_iScan / sizeof(image32_t);

   int srcS = pimage->m_iScan / sizeof(image32_t);

   for (int i = 0; i < cx; i++)
   {

      for (int j = 0; j < cy; j++)
      {

         image32()[i * s + j] = pimage->image32()[(cy - j - 1) * srcS + (cx - i - 1)];

      }

   }

}


void image::e_rotate_90_flip_horizontally()
{

   ::image::image_pointer pimage = this->clone();

   return e_rotate_90_flip_horizontally(pimage);

}


void image::e_rotate_180_flip_horizontally()
{

   ::image::image_pointer pimage = this->clone();

   return e_rotate_180_flip_horizontally(pimage);

}


void image::e_rotate_270_flip_horizontally()
{

   ::image::image_pointer pimage = this->clone();

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

      int iHeight = get_size().cy;

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

      g()->fill_rectangle(::double_rectangle(m_size), color);

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

      long long size = scan_area();

      unsigned char a = color.byte_opacity();
      unsigned char r = color.byte_red();
      unsigned char g = color.byte_green();
      unsigned char b = color.byte_blue();

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

      for (long long i = 0; i < size; i++)
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


void image::clear_argb(int a, int r, int g, int b)
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

   long long iRLine;

   long long iGLine;

   long long iBLine;

   long long iDiv = width() * height();

   if (iDiv > 0)
   {

      iRLine = 0;

      iGLine = 0;

      iBLine = 0;

      for (int y = 0; y < height(); y++)
      {

         unsigned char* pb = ((unsigned char*)data()) + m_iScan * y;


         for (int x = 0; x < width(); x++)
         {

            iRLine += pb[2];


            iGLine += pb[1];


            iBLine += pb[0];


            pb += 4;


         }

      }

      int iR = (int)(iRLine / iDiv);

      int iG = (int)(iGLine / iDiv);

      int iB = (int)(iBLine / iDiv);

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

   int iRLine;
   int iGLine;
   int iBLine;

   double dDiv = width() * height();

   if (dDiv > 0)
   {

      for (int y = 0; y < height(); y++)
      {
         iRLine = 0;
         iGLine = 0;
         iBLine = 0;
         unsigned char* pb = ((unsigned char*)data()) + m_iScan * y;

         for (int x = 0; x < width(); x++)
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
      int iR = (int)dR;
      int iG = (int)dG;
      int iB = (int)dB;
      return rgb(iR, iG, iB);
   }
   else
   {
      
      return {};

   }

}


void image::do_xor(::image::image* pimage)
{

   if (width() != pimage->width()
      || height() != pimage->height())
   {

      //return false;

      return;

   }

   int iCount = width() * height();
   unsigned int* pd1 = (unsigned int*)data();

   unsigned int* pd2 = (unsigned int*)pimage->data();

   for (int i = 0; i < iCount; i++)
   {
      *pd1 = *pd1 ^ *pd2;

      pd1++;

      pd2++;

   }

   //return true;

}


void image::create_frame(const ::int_size& size, int iFrameCount)
{

   int iSliceCount = (int)sqrt((double)iFrameCount);

   return create(size / iSliceCount);

}


void image::set_frame1(void* pdata, int iFrame, int iFrameCount)

{
   int iSliceCount = (int)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   int iFrameWidth = width() / iSliceCount;
   int iFrameHeight = height() / iSliceCount;
   int iX = iFrame % iSliceCount;
   int iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (int y = 0; y < iFrameHeight; y++)
   {
      pdstline = &pdst[y * width()];

      for (int x = 0; x < iFrameWidth; x++)
      {
         *pdstline = *psrc;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void image::set_frame2(void* pdata, int iFrame, int iFrameCount)

{

   int iSliceCount = (int)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   int iFrameWidth = width() / iSliceCount;
   int iFrameHeight = height() / iSliceCount;
   int iX = iFrame % iSliceCount;
   int iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (int y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (int x = 0; x < iFrameWidth; x++)
      {
         *pdstline = *psrc;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void image::xor_image_frame2(void* pdata, int iFrame, int iFrameCount)

{
   int iSliceCount = (int)sqrt((double)iFrameCount);
   if (iSliceCount == 0)
      iSliceCount = 1;
   int iFrameWidth = width() / iSliceCount;
   int iFrameHeight = height() / iSliceCount;
   int iX = iFrame % iSliceCount;
   int iY = iFrame / iSliceCount;
   image32_t* pdst = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* psrc = (image32_t*)pdata;

   image32_t* pdstline;

   for (int y = iFrameHeight - 1; y >= 0; y--)
   {
      pdstline = &pdst[y * width()];

      for (int x = 0; x < iFrameWidth; x++)
      {
         pdstline->m_ui ^= psrc->m_ui;

         pdstline++;

         psrc++;

      }
   }

   //return true;

}


void image::get_frame(void* pdata, int iFrame, int iFrameCount)

{
   int iSliceCount = (int)sqrt((double)iFrameCount);
   int iFrameWidth = width() / iSliceCount;
   int iFrameHeight = height() / iSliceCount;
   int iX = iFrame % iSliceCount;
   int iY = iFrame / iSliceCount;
   image32_t* psrc = &data()[iFrameWidth * iX + iY * iFrameHeight * width()];

   image32_t* pdst = (image32_t*)pdata;

   image32_t* psrcline;

   for (int y = 0; y < iFrameHeight; y++)
   {
      psrcline = &psrc[y * width()];

      for (int x = 0; x < iFrameWidth; x++)
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

   int iSize = width() * height();

   image32_t* p = data();

   for (int i = 0; i < iSize; i++)
   {

      if ((p->m_ui & 0x00FFFFFF) != 0)
      {

         return false;

      }

      p++;

   }

   return true;

}


void image::DivideRGB(int iDivide)
{

   if (iDivide == 0)
   {

      return;

   }

   int iCount = width() * height();

   unsigned char* p = ((unsigned char*)data());

   int i = 0;

   int iCount1 = iCount - iCount % 8;

   for (; i < iCount1; i++)
   {

      p[0] /= (unsigned char)iDivide;

      p[1] /= (unsigned char)iDivide;

      p[2] /= (unsigned char)iDivide;


      p[4] /= (unsigned char)iDivide;

      p[5] /= (unsigned char)iDivide;

      p[6] /= (unsigned char)iDivide;


      p[8] /= (unsigned char)iDivide;

      p[9] /= (unsigned char)iDivide;

      p[10] /= (unsigned char)iDivide;


      p[12] /= (unsigned char)iDivide;

      p[13] /= (unsigned char)iDivide;

      p[14] /= (unsigned char)iDivide;


      p[16] /= (unsigned char)iDivide;

      p[17] /= (unsigned char)iDivide;

      p[28] /= (unsigned char)iDivide;


      p[20] /= (unsigned char)iDivide;

      p[21] /= (unsigned char)iDivide;

      p[22] /= (unsigned char)iDivide;


      p[24] /= (unsigned char)iDivide;

      p[25] /= (unsigned char)iDivide;

      p[26] /= (unsigned char)iDivide;


      p[28] /= (unsigned char)iDivide;

      p[29] /= (unsigned char)iDivide;

      p[30] /= (unsigned char)iDivide;


      p += 4 * 8;

   }
   for (; i < iCount; i++)
   {
      p[0] /= (unsigned char)iDivide;

      p[1] /= (unsigned char)iDivide;

      p[2] /= (unsigned char)iDivide;

      p += 4;

   }

   //return true;

}


void image::DivideARGB(int iDivide)
{

   if (iDivide == 0)
   {

      return;

   }

   int iCount = width() * height();

   unsigned char* p = ((unsigned char*)data());

   for (int i = 0; i < iCount; i++)
   {
      p[0] /= (unsigned char)iDivide;

      p[1] /= (unsigned char)iDivide;

      p[2] /= (unsigned char)iDivide;

      p[3] /= (unsigned char)iDivide;

      p += 4;

   }

   //return true;

}


void image::DivideA(int iDivide)
{

   if (iDivide == 0)
   {

      //return false;

      return;

   }

   int iCount = width() * height();

   unsigned char* p = ((unsigned char*)data());

   for (int i = 0; i < iCount; i++)
   {
      p[3] /= (unsigned char)iDivide;

      p += 4;

   }

   //return true;

}




void image::set_mipmap(::image::enum_mipmap emipmap)
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


void image::_set_mipmap(::image::enum_mipmap emipmap)
{

   ASSERT(emipmap != ::image::e_mipmap_none);

   ::image::image_pointer pimage = this->clone();

   int cxSource = pimage->width();

   int cySource = pimage->width();

   int iSourceScan = pimage->scan_size();

   double cx = cxSource;

   double cy = cySource;

   if (emipmap == ::image::e_mipmap_isotropic)
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

      ::image::image_source imagesource(pimage);

      double_rectangle rectangle(::double_size(cxSource, cySource));

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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
               (unsigned int)cx,
               (unsigned int)cy,
               m_iScan,
               pimage->data(),
               cxSource,
               cySource,
               iSourceScan
            );

         }
         else
         {

            ::image::image_source imagesource(pimage, ::int_rectangle_dimension(0, 0, (int)cx, (int)cy));

            auto rectangle = double_rectangle_dimension(x, y, cx, cy);

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            get_graphics()->draw(imagedrawing);

         }

         y += (int)cy;

      }

      m_emipmap = ::image::e_mipmap_isotropic;

   }
   else
   {

      double newcx = cx * 2.0 - 1.0;

      double newcy = cy * 2.0 - 1.0;

      create({ (int)newcx, (int)newcy });

      //if (!create({ (int)newcx, (int)newcy }))
      //{

      //   throw ::exception(error_resource);

      //}

      int Δx;

      int x = 0;

      int xPrevious;
      int yPrevious;
      int cxPrevious;
      int cyPrevious;

      xPrevious = 0;
      cxPrevious = cxSource;

      for (Δx = (int)cx; Δx > 0; x += Δx, Δx /= 2)
      {

         yPrevious = 0;
         cyPrevious = pimage->height();

         for (int y = 0, Δy = (int)cy; Δy > 0; y += Δy, Δy /= 2)
         {

            if (::parallelization::get_priority() == ::e_priority_idle)
            {

               map();

               C2PassScale < CBlackmanFilter > scale(1.0);

               scale.Scale(
                  &image32()[x + y * m_iScan / sizeof(image32_t)],
                  color_indexes(),
                  Δx,
                  Δy,
                  m_iScan,
                  &pimage->image32()[xPrevious + yPrevious * pimage->m_iScan / sizeof(image32_t)],
                  cxPrevious,
                  cyPrevious,
                  pimage->m_iScan
               );

               yPrevious = y;
               cyPrevious = Δy;
               pimage = this;

            }
            else
            {

               ::image::image_source imagesource(pimage, ::int_rectangle_dimension(0, 0, pimage->width(), pimage->height()));

               auto rectangle = double_rectangle_dimension(x, y, Δx, Δy);

               ::image::image_drawing_options imagedrawingoptions(rectangle);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               get_graphics()->draw(imagedrawing);

            }

         }

         xPrevious = x;
         cxPrevious = Δx;

      }

      m_emipmap = ::image::e_mipmap_anisotropic;

   }

   size() = pimage->get_size();

   //return true;

}


void image::set_origin(const ::int_point& point)
{

   m_point = point;

   if (!m_bMapped)
   {

      get_graphics()->place_impact_area(point, m_size);

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


   ::collection::index a;

   a = (::collection::index)(area());

   //return true;

   ::collection::index jNextBoundary;
   ::collection::index jStart;
   unsigned char* pdata = (unsigned char*)image32();

   if (pdata == nullptr || a <= 0)
   {

      //return false;

      return;

   }

   ::collection::index w = width();
   ::collection::index h = height();
   ::collection::index sw = w * sizeof(image32_t);
   ::collection::index aa = w * h;
   {

      m_memoryMap.set_size(a * 2);

      m_memoryMap.set(0);
      unsigned char* opacity = m_memoryMap.data();

      for (::collection::index i = 0; i < height(); i++)
      {

         for (::collection::index j = 0; j < sw; j += 4)
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

               ::collection::index c = (j - jStart) >> 2;

               ::collection::index m = j >> 2;

               unsigned char n = 1;

               unsigned char* o = &opacity[(int)(i * w)];

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

      unsigned char* transparency = m_memoryMap.data() + a;

      for (::collection::index i = 0; i < height(); i++)
      {

         for (::collection::index j = 0; j < sw; j += 4)
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

               ::collection::index c = (j - jStart) >> 2;

               ::collection::index m = j >> 2;

               unsigned char n = 1;

               unsigned char* t = &transparency[(int)(i * w)];

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

//int image::cos(int i, int iAngle)
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
//int image::sin(int i, int iAngle)
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
//int image::cos10(int i, int iAngle)
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
//int image::sin10(int i, int iAngle)
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

/*   int image::width()
   {
      throw ::interface_only();
   }

   int image::height()
   {
      throw ::interface_only();
   }

   long long image::area()
   {
      return ((long long) width()) * ((long long)height());
   }

   int_size image::size()
   {
      return long_long_size(width(), height());
   }*/


double image::pi() const
{

   return atan(1.0) * 4.0;

}


void image::fill_channel(int intensity, ::color::enum_channel echannel)
{
   map();
   int offset = ((int)echannel) % 4;
   long long size = scan_area();

   image32_t* pcr = (image32_t*)&((unsigned char*)image32())[offset];

   unsigned char* pb;

   long long iSize32 = size / 32;
   int i;
   for (i = 0; i < iSize32; i += 32)
   {
      pb = (unsigned char*)&pcr[i];
      pb[0 * 4] = (unsigned char)intensity;
      pb[1 * 4] = (unsigned char)intensity;
      pb[2 * 4] = (unsigned char)intensity;
      pb[3 * 4] = (unsigned char)intensity;
      pb[4 * 4] = (unsigned char)intensity;
      pb[5 * 4] = (unsigned char)intensity;
      pb[6 * 4] = (unsigned char)intensity;
      pb[7 * 4] = (unsigned char)intensity;
      pb[8 * 4] = (unsigned char)intensity;
      pb[9 * 4] = (unsigned char)intensity;
      pb[10 * 4] = (unsigned char)intensity;
      pb[11 * 4] = (unsigned char)intensity;
      pb[12 * 4] = (unsigned char)intensity;
      pb[13 * 4] = (unsigned char)intensity;
      pb[14 * 4] = (unsigned char)intensity;
      pb[15 * 4] = (unsigned char)intensity;
      pb[16 * 4] = (unsigned char)intensity;
      pb[17 * 4] = (unsigned char)intensity;
      pb[18 * 4] = (unsigned char)intensity;
      pb[19 * 4] = (unsigned char)intensity;
      pb[20 * 4] = (unsigned char)intensity;
      pb[21 * 4] = (unsigned char)intensity;
      pb[22 * 4] = (unsigned char)intensity;
      pb[23 * 4] = (unsigned char)intensity;
      pb[24 * 4] = (unsigned char)intensity;
      pb[25 * 4] = (unsigned char)intensity;
      pb[26 * 4] = (unsigned char)intensity;
      pb[27 * 4] = (unsigned char)intensity;
      pb[28 * 4] = (unsigned char)intensity;
      pb[29 * 4] = (unsigned char)intensity;
      pb[30 * 4] = (unsigned char)intensity;
      pb[31 * 4] = (unsigned char)intensity;
   }

   for (i = 0; i < size; i++)
   {
      *((unsigned char*)&pcr[i]) = (unsigned char)intensity;
   }

   //return true;

}


void image::white_fill_channel(int intensity, ::color::enum_channel echannel)
{
   map();
   int offset = ((int)echannel) % 4;
   long long size = scan_area();

   image32_t* pcr = (image32_t*)&((unsigned char*)image32())[offset];

   //      unsigned char * pb;

   long long iSize32 = size / 32;
   int i;
   //      for (i=0; i < iSize32; i+=32 )
   //      {
   //         pb = (unsigned char *) &pcr[i];
   //         pb[0 * 4] = (unsigned char) intensity;
   //         pb[1 * 4] = (unsigned char) intensity;
   //         pb[2 * 4] = (unsigned char) intensity;
   //         pb[3 * 4] = (unsigned char) intensity;
   //         pb[4 * 4] = (unsigned char) intensity;
   //         pb[5 * 4] = (unsigned char) intensity;
   //         pb[6 * 4] = (unsigned char) intensity;
   //         pb[7 * 4] = (unsigned char) intensity;
   //         pb[8 * 4] = (unsigned char) intensity;
   //         pb[9 * 4] = (unsigned char) intensity;
   //         pb[10 * 4] = (unsigned char) intensity;
   //         pb[11 * 4] = (unsigned char) intensity;
   //         pb[12 * 4] = (unsigned char) intensity;
   //         pb[13 * 4] = (unsigned char) intensity;
   //         pb[14 * 4] = (unsigned char) intensity;
   //         pb[15 * 4] = (unsigned char) intensity;
   //         pb[16 * 4] = (unsigned char) intensity;
   //         pb[17 * 4] = (unsigned char) intensity;
   //         pb[18 * 4] = (unsigned char) intensity;
   //         pb[19 * 4] = (unsigned char) intensity;
   //         pb[20 * 4] = (unsigned char) intensity;
   //         pb[21 * 4] = (unsigned char) intensity;
   //         pb[22 * 4] = (unsigned char) intensity;
   //         pb[23 * 4] = (unsigned char) intensity;
   //         pb[24 * 4] = (unsigned char) intensity;
   //         pb[25 * 4] = (unsigned char) intensity;
   //         pb[26 * 4] = (unsigned char) intensity;
   //         pb[27 * 4] = (unsigned char) intensity;
   //         pb[28 * 4] = (unsigned char) intensity;
   //         pb[29 * 4] = (unsigned char) intensity;
   //         pb[30 * 4] = (unsigned char) intensity;
   //         pb[31 * 4] = (unsigned char) intensity;
   //      }


   for (i = 0; i < size; i++)
   {

      *((unsigned char*)&pcr) = (unsigned char)(((int)intensity * (int)*((unsigned char*)&pcr)) / 255);

      pcr++;

   }

   //return true;

}


void image::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc)
{

   map();

   echannelDst = (::color::enum_channel)(((int)echannelDst) % 4);
   echannelSrc = (::color::enum_channel)(((int)echannelSrc) % 4);

   if (echannelDst == echannelSrc)
   {

      //return true;
      return;

   }

   unsigned char* pdataDst = (unsigned char*)data() + ((int)echannelDst);

   unsigned char* pdataSrc = (unsigned char*)data() + ((int)echannelSrc);

   for (int y = 0; y < height(); y++)
   {

      unsigned char* pdst = &pdataDst[m_iScan * y];

      unsigned char* psrc = &pdataSrc[m_iScan * y];

      for (int x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}


void image::channel_copy(::color::enum_channel echannelDst, ::color::enum_channel echannelSrc, ::image::image* pimage)
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

   echannelDst = (::color::enum_channel)(((int)echannelDst) % 4);
   echannelSrc = (::color::enum_channel)(((int)echannelSrc) % 4);

   unsigned char* pdataDst = (unsigned char*)data() + ((int)echannelDst);

   unsigned char* pdataSrc = (unsigned char*)pimage->data() + ((int)echannelSrc);

   for (int y = 0; y < height(); y++)
   {

      unsigned char* pdst = &pdataDst[m_iScan * y];

      unsigned char* psrc = &pdataSrc[pimage->m_iScan * y];

      for (int x = 0; x < width(); x++)
      {

         *pdst = *psrc;

         pdst += 4;

         psrc += 4;

      }

   }

   //return true;

}


void image::all_channels_copy(::color::enum_channel echannelSrc, ::image::image *pimage)
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

   echannelSrc = (::color::enum_channel)(((int)echannelSrc) % 4);

   unsigned char * pdataDst = (unsigned char *)data();

   unsigned char * pdataSrc = (unsigned char *)pimage->data() + ((int)echannelSrc);

   for (int y = 0; y < height(); y++)
   {

      unsigned char * pdst = &pdataDst[m_iScan * y];

      unsigned char * psrc = &pdataSrc[pimage->m_iScan * y];

      for (int x = 0; x < width(); x++)
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


void image::tint(::image::image* pimage, ::color::color color)
{

   create(pimage->size());


   /*{

      return false;

   }*/

   map();

   unsigned char* src = (unsigned char*)pimage->image32();
   unsigned char* dst = (unsigned char*)image32();
   long long size = scan_area();

   unsigned char uchR = (unsigned char)color.byte_red();
   unsigned char uchG = (unsigned char)color.byte_green();
   unsigned char uchB = (unsigned char)color.byte_blue();

   //      int i = 0;;


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
   //unsigned char tableR[256];
   //unsigned char tableG[256];
   //unsigned char tableB[256];
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

      unsigned char bA = src[3];

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

   unsigned char* dst = (unsigned char*)image32();

   long long size = scan_area();

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
      unsigned char* puch = (unsigned char*)data();
      long long iArea = scan_area();
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


void image::set_rgb_pre_alpha(int R, int G, int B, int A)
{

   map();

   unsigned char* dst = (unsigned char*)image32();
   long long size = scan_area();

   unsigned char uchB = (unsigned char)R;
   unsigned char uchG = (unsigned char)G;
   unsigned char uchR = (unsigned char)B;

   //      int i = 0;;

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


void image::set_rgb(::color::color color)
{

   return set_rgb(color.byte_red(), color.byte_green(), color.byte_blue());

}


//void image::set_rgb(int R, int G, int B)
//{
//
//   return set(R, G, B);
//
//}


long long image::get_rgba_area(::color::color color) const
{

   long long areaRgba = 0;

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


long long image::get_rgba_area(::color::color color, const ::int_rectangle &rect) const
{

   ::int_rectangle r(rect);

   if (r.intersect(this->rectangle()).is_empty())
   {

      return 0;

   }

   ::collection::count areaRgba = 0;

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


long long image::_001GetTopLeftWeightedOpaqueArea(int iAlphaMin) const
{

   auto r = this->rectangle();

   return _001GetTopLeftWeightedOpaqueArea(iAlphaMin, r);

}


long long image::_001GetTopLeftWeightedOpaqueArea(int iAlphaMin, const ::int_rectangle &rect) const
{

   map();

   if(::is_null(this->data()))
   {

      return 0;

   }

   ::int_rectangle r(rect);

   ::int_rectangle rTotal(this->rectangle());

   if (r.intersect(rTotal).is_empty())
   {

      return 0;

   }

   long long areaRgba = 0;

   int wscan = m_iScan / sizeof(image32_t);

   int w = r.width();

   int h = r.height();

   long long areaRgbaLast = 0;

   const image32_t* p = this->data() + r.left + wscan * r.top;

   areaRgba++;

   for (int y = r.top; y < r.bottom; y++)
   {

      auto ysq = (rTotal.bottom - y);

      auto pbyte = &((unsigned char*)p)[m_colorindexes.m_uchIndexOpacity];

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

         informationf("_001GetTopLeftWeightedOpaqueArea areaRgba < areaRgbaLast");

      }

      areaRgbaLast = areaRgba;

   }

   return areaRgba;

}


void image::multiply_rgb_by_source_alpha(::color::color color)
{

   auto u8Red = color.byte_red();
   auto u8Green = color.byte_green();
   auto u8Blue = color.byte_blue();
   unsigned char u8Opacity;

   auto u8IndexOpacity = m_colorindexes.m_uchIndexOpacity;
   auto u8IndexRed = m_colorindexes.m_uchIndexRed;
   auto u8IndexGreen = m_colorindexes.m_uchIndexGreen;
   auto u8IndexBlue = m_colorindexes.m_uchIndexBlue;

   unsigned char* puch = (unsigned char*)data();
   long long iArea = scan_area();
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


void image::rgb_from(::image::image* pimage)
{

   //if (!
   create(pimage->size());
   //{

   //   return false;

   //}

   //try
   //{

      unsigned char* puchSrc = (unsigned char*)data();
      unsigned char* puchDst = (unsigned char*)pimage->data();
      long long iArea = pimage->scan_area();
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


void image::pixelate(int iSize)
{

   if (iSize <= 1)
   {

      //return true;

      return;

   }

   map();

   int w = width();
   int h = height();
   int s = m_iScan / sizeof(image32_t);

   int xCount = w / iSize;
   int yCount = h / iSize;

   int iDiv;
   int iDiv2;

   int a;
   int r;
   int g;
   int b;
   int a2;
   int r2;
   int g2;
   int b2;
   //bool bFirst;
   image32_t* pdata = data();
   int x1;
   int y1;
   for (int x = 0; x < xCount; x++)
   {
      x1 = x * iSize;
      for (int y = 0; y < yCount; y++)
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
         for (int i = 0; i < iSize; i++)
         {
            for (int j = 0; j < iSize; j++)
            {
               image32_t cr = pdata[x1 + i + (y1 + j) * s];
               a += cr.byte_opacity(color_indexes());
               r += cr.byte_red(color_indexes());
               g += cr.byte_green(color_indexes());
               b += cr.byte_blue(color_indexes());
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
         for (int i = 0; i < iSize; i++)
         {
            for (int j = 0; j < iSize; j++)
            {

               pdata[x1 + i + (y1 + j) * s] = cr;

            }

         }

      }

   }

   if (w % iSize != 0)
   {
      int x = xCount;
      int x1 = x * iSize;
      int iMax = w - xCount * iSize;
      for (int y = 0; y < yCount; y++)
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
         for (int i = 0; i < iMax; i++)
         {
            for (int j = 0; j < iSize; j++)
            {
               image32_t cr = pdata[x1 + i + (y1 + j) * w];
               a += cr.byte_opacity(color_indexes());
               r += cr.byte_red(color_indexes());
               g += cr.byte_green(color_indexes());
               b += cr.byte_blue(color_indexes());
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
         for (int i = 0; i < iMax; i++)
         {
            for (int j = 0; j < iSize; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

   }

   if (h % iSize != 0)
   {
      int y = yCount;
      int y1 = y * iSize;
      int jMax = h - yCount * iSize;
      for (int x = 0; x < xCount; x++)
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
         for (int i = 0; i < iSize; i++)
         {
            for (int j = 0; j < jMax; j++)
            {
               image32_t cr = pdata[x1 + i + (y1 + j) * w];
               a += cr.byte_opacity(color_indexes());
               r += cr.byte_red(color_indexes());
               g += cr.byte_green(color_indexes());
               b += cr.byte_blue(color_indexes());
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
         for (int i = 0; i < iSize; i++)
         {
            for (int j = 0; j < jMax; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

   }

   if (w % iSize != 0)
   {
      int x = xCount;
      int x1 = x * iSize;
      int iMax = w - xCount * iSize;
      int y = yCount;
      int y1 = y * iSize;
      int jMax = h - yCount * iSize;
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
      for (int i = 0; i < iMax; i++)
      {
         for (int j = 0; j < jMax; j++)
         {
            image32_t cr = pdata[x1 + i + (y1 + j) * w];
            a += cr.byte_opacity(color_indexes());
            r += cr.byte_red(color_indexes());
            g += cr.byte_green(color_indexes());
            b += cr.byte_blue(color_indexes());
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

      for (int i = 0; i < iMax; i++)
      {

         for (int j = 0; j < jMax; j++)
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
      unsigned char* puch = (unsigned char*)data();
      long long iArea = scan_area();
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
      ((::image::image*)this)->_map(bApplyAlphaTransform);

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

      ((::image::image*)this)->_unmap();

      if (_get_graphics() != nullptr)
      {

         ::int_rectangle rectangleThis(m_size);

         ::int_rectangle rectangleMap(rectangle());

         if (rectangleThis.contains(rectangleMap.origin()))
         {

            _get_graphics()->place_impact_area(rectangleMap);

         }
         else
         {

            _get_graphics()->place_impact_area(0, 0, m_sizeRaw.width(), m_sizeRaw.height());

         }

      }

      ((::image::image*)this)->m_bMapped = false;

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


//void image::print_window(::aura::draw_interface * puserinteraction,::message::message * pmessage)
//{

//   __UNREFERENCED_PARAMETER(puserinteraction);
//   __UNREFERENCED_PARAMETER(pmessage);

//   throw ::interface_only();

//   return false;

//}


void image::gradient_fill(::color::color color1, ::color::color color2, const int_point& point1, const int_point& point2)
{

   double Δx = point2.x - point1.x;

   double Δy = point1.y - point2.y;

   if (Δx == 0.0 && Δy == 0.0)
   {

      clear_argb(
         byte_clip(color1.byte_opacity() * 0.5 + color2.byte_opacity() * 0.5),
         byte_clip(color1.byte_red() * 0.5 + color2.byte_red() * 0.5),
         byte_clip(color1.byte_green() * 0.5 + color2.byte_green() * 0.5),
         byte_clip(color1.byte_blue() * 0.5 + color2.byte_blue() * 0.5));

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

      auto angle = ::geometry::atan2(Δy, Δx);

      ::image::image_pointer pimage;

      auto pmathematics = mathematics();

      if (fabs(Δx) > fabs(Δy))
      {

         double sin = ::sin(angle);

         //auto estatus =
         
         øconstruct(pimage);

         //if (!estatus)
         //{

         //   return false;

         //}

         //estatus = 
         
         pimage->create({ (int)(dim / sin), (int)(dim / sin) });

         //if (!estatus)
         //{

         //   return false;

         //}

         pimage->gradient_horizontal_fill(color1, color2, point1.y, point2.y);

         pimage->rotate(this, -angle, 1.0);

      }
      else
      {

         double cos = ::cos(angle);

         //auto estatus =
         
         øconstruct(pimage);

         //if (!estatus)
         //{

         //   return false;

         //}

         //estatus = 
         pimage->create({ (int)(dim / cos), (int)(dim / cos) });

         //if (!estatus)
         //{

         //   return false;

         //}

         pimage->gradient_vertical_fill(color1, color2, point1.x, point2.x);

         pimage->rotate(this, π - angle, 1.0);

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
   unsigned char* pb = (unsigned char*)image32();
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
         byte_clip(color1.byte_opacity() * (1.0 - d) + color2.byte_opacity() * d),
         byte_clip(color1.byte_red() * (1.0 - d) + color2.byte_red() * d),
         byte_clip(color1.byte_green() * (1.0 - d) + color2.byte_green() * d),
         byte_clip(color1.byte_blue() * (1.0 - d) + color2.byte_blue() * d)), color_indexes());

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
   
   unsigned char* pb = (unsigned char*)image32();
   
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
         byte_clip(color1.byte_opacity() * (1.0 - d) + color2.byte_opacity() * d),
         byte_clip(color1.byte_red() * (1.0 - d) + color2.byte_red() * d),
         byte_clip(color1.byte_green() * (1.0 - d) + color2.byte_green() * d),
         byte_clip(color1.byte_blue() * (1.0 - d) + color2.byte_blue() * d)), 
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


void image::invert_rgb(const ::int_rectangle& rectangle)

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

      unsigned char* pb = &((unsigned char*)image32())[start];

      for (int x = left; x < right; x++, pb += 4)
      {

         pb[0] = ~pb[0];
         pb[1] = ~pb[1];
         pb[2] = ~pb[2];

      }

   }

   //return true;

}


void image::create_circle(::image::image* pimage, int diameter)
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

      ::image::image_source imagesource(pimage, ::int_rectangle_dimension(0, 0, pimage->width(), pimage->height()));

      auto rectangle = double_rectangle_dimension(0, 0, diameter, diameter);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      get_graphics()->draw(imagedrawing);

   }

   ::int_size s = size();

   image32_t* pimage32 = image32();

   int iScan = m_iScan;

   int wscan = iScan / sizeof(image32_t);

   double radius = diameter / 2.0;

   double dBorder = 1.0;

   double rmin = radius - dBorder;

   double rmax = radius;

   int crA;

   image32_t* pimage322;

   for (int y = 0; y < s.cx; y++)
   {

      pimage322 = &pimage32[y * wscan];

      for (int x = 0; x < s.cx; x++)
      {

         double Δx = x;

         double Δy = y;

         double distance = sqrt((Δx - radius) * (Δx - radius) + (Δy - radius) * (Δy - radius));

         crA = (int)((rmin - distance) * 255.0 / dBorder);

         crA = maximum(minimum(crA, 255), 0);

         pimage322->m_ui = (pimage322->m_ui & 0x00ffffff) | (crA << 24);

         pimage322++;

      }

   }

   //return true;

}


void image::create_framed_square(::image::image* pimage, int inner, int outer, ::color::color color)
{

   create({ inner + outer * 2, inner + outer * 2 });

   //if (!create({ inner + outer * 2, inner + outer * 2 }))
   //{

   //   return false;

   //}

   clear(color);

   ::image::image_source imagesource(pimage, ::int_rectangle_dimension(0, 0, pimage->width(), pimage->height()));

   auto rectangle = double_rectangle_dimension(outer, outer, inner, inner);

   ::image::image_drawing_options imagedrawingoptions(rectangle);

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   get_graphics()->draw(imagedrawing);

   //return true;

}


void image_copy(::image::image* pimagethis, ::image::image* pimage)
{

   pimagethis->copy_from(pimage);

}


//void image_create(::object* pparticle, ::image::image_pointer& pimage)
//{
//
//   øconstruct(pimage, pparticle);
//
//}

//
//void image_create_image(::image::image* pimage, const ::int_size& size)
//{
//
//   pimage->create(size);
//
//}


unsigned int* image_get_data(::image::image* pimage)
{

   return (unsigned int*)pimage->image32();

}


::draw2d::graphics* image_get_graphics(::image::image* pimage)
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


   unsigned char* dst = (unsigned char*)data();

   long long size = scan_area();


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

   data()->copy(rectangle(), scan_size(), pcolor32);

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
//      m_iQuality = varOptions["quality"].as_int();
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

//void image::load_matter_icon(string_array_base & straMatter, const ::scoped_string & scopedstrIcon)
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
//   void image::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
//   {
//
//      return psystem->imaging().from(m_p, pgraphics, pfi, bUnload);
//
//   }
//
//#endif

/*::int_size image::size()
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

      ::memory_copy(ppixmapDst, ppixmapSrc, sizeof(::pixmap));

   }

}


::pointer<::image::image>image::get_image(const ::int_size & size)
{

   if (size == get_size())
   {

      return this;

   }

   auto pimageNew = ::particle::image()->create_image(size);

   ::image::image_source imagesource(this, this->rectangle());

   auto rectangle = pimageNew->rectangle();

   ::image::image_drawing_options imagedrawingoptions(rectangle);

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pimageNew->g()->draw(imagedrawing);

   return pimageNew;

}


::pointer<::image::image>image::get_image(int cx, int cy)
{

   auto pimageNew = get_image( ::int_size( cx, cy ));

   return pimageNew;

}


#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::image::image* m_p, int Δx, int Δy, void* pftbitmap, int xParam, int yParam)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, int_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         int a = bitmap->buffer[q * bitmap->width + int_point];

         *((image32_t*)&((unsigned char*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::image::image* m_p, int Δx, int Δy, void* pftbitmap, int xParam, int yParam, unsigned char aParam, unsigned char rectangle, unsigned char g, unsigned char b)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, int_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         int a = bitmap->buffer[q * bitmap->width + int_point];

         if (a > 0)
         {

            *((image32_t*)&((unsigned char*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((image32_t*)&((unsigned char*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = 0;

         }

      }
   }

}

#endif









#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::image::image* m_p, int Δx, int Δy, void* pftbitmap, int xParam, int yParam)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, int_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         int a = bitmap->buffer[q * bitmap->width + int_point];

         *((image32_t*)&((unsigned char*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::image::image* m_p, int Δx, int Δy, void* pftbitmap, int xParam, int yParam, unsigned char aParam, unsigned char rectangle, unsigned char g, unsigned char b)
{

   FT_Bitmap* bitmap = (FT_Bitmap*)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, point, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, point = 0; i < x_max; i++, int_point++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->width() || j >= m_p->height())
            continue;

         int a = bitmap->buffer[q * bitmap->width + int_point];

         if (a > 0)
         {

            *((image32_t*)&((unsigned char*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = argb(a * aParam / 255, rectangle, g, b);

         }
         else
         {

            *((image32_t*)&((unsigned char*)m_p->data())[(Δy + j) * m_p->m_iScan + (Δx + i) * 4]) = 0;

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
//   int iWidth = width();
//
//   stream << (int)iWidth;
//
//   int iHeight = height();
//
//   stream << (int)iHeight;
//
//   stream << (int)m_sizeAlloc.cx;
//
//   stream << (int)m_sizeAlloc.cy;
//
//   stream << (int)m_iScan;
//
//   stream << (int)m_emipmap;
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
//   int width;
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
//   int height;
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
//   int widthAlloc;
//   stream >> widthAlloc;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   int heightAlloc;
//   stream >> heightAlloc;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   int iScan;
//   stream >> iScan;
//   //if (stream.fail())
//   //{
//
//   //   return stream;
//
//   //}
//
//   int iMipmap;
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
//   if (iScan < widthAlloc / (int)sizeof(image32_t))
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


::subparticle_pointer image::clone()
{

   auto pimage = this->øcreate<::image::image>();

   pimage->copy_from((::image::image *) this);

   __refdbg_add_referer

   pimage->increment_reference_count();

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


//void     image::create(const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
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
http://www.sparkhound.com/blog/detect-image-file-types-through-unsigned char-arrays
::payload bmp = Encoding.ASCII.GetBytes("BM"); // BMP
::payload gif = Encoding.ASCII.GetBytes("GIF"); // GIF
::payload png = øallocate_array< unsigned char >(){ 137, 80, 78, 71 }; // PNG
::payload tiff = øallocate_array< unsigned char >(){ 73, 73, 42 }; // TIFF
::payload tiff2 = øallocate_array< unsigned char >(){ 77, 80, 42 }; // TIFF
::payload jpeg = øallocate_array< unsigned char >(){ 255, 216, 255, 224 }; // jpeg
::payload jpeg2 = øallocate_array< unsigned char >(){ 255, 216, 255, 225 }; // jpeg canon
*/


//virtual ::image::image_pointer ::create_image(::draw2d::e_load eload = ::draw2d::load_none);
//virtual ::image::image_pointer create_image({int cx,  int cy});
//virtual ::image::image_pointer create_image(const ::int_size & size);




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
//   int i;
//   for (i = 0; i < 360; i++)
//   {
//      dCos = ::cos(i / 180.0 * dPi);
//      dSin = ::sin(i / 180.0 * dPi);
//      Cosines[i] = float(dCos);
//      Sines[i] = float(dSin);
//      CosN[i] = (long long)(dCos * d32);
//      SinN[i] = (long long)(dSin * d32);
//   }
//   d32 = (1U << 31);
//   d32 *= 8;
//   for (i = 0; i < 10; i++)
//   {
//      dCos = ::cos(i / 180.0 * dPi);
//      dSin = ::sin(i / 180.0 * dPi);
//      Cos10N[i] = (long long)(dCos * d32);
//      Sin10N[i] = (long long)(dSin * d32);
//   }
//
//}
//


::image::image_extension* image::get_extension()
{

   if (::is_null(m_pextension))
   {

      øconstruct_new(m_pextension);

   }

   return m_pextension;

}


bool image::_draw_blend(const ::image::image_drawing& imagedrawing)
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


void image::draw(const ::image::image_drawing & imagedrawing)
{

   if (imagedrawing.m_bDoForAllFrames)
   {

      auto pimage = imagedrawing.image();

      auto pframes = pimage->frames();

      if (pframes && pframes->has_elements())
      {

         auto pextension = get_extension();

         øconstruct_new(pextension->m_pframea);

         pextension->m_pframea->m_size = this->m_size;

         pextension->m_pframea->update(this, imagedrawing);

         return;

      }

   }

   image_drawer::draw(imagedrawing);
   //void defer_update_image();

}


void image::_draw_raw(const ::image::image_drawing& imagedrawing)
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


::image::image_pointer image::get_resized_image(const ::int_size & size)
{

   ::image::image_pointer pimage;

   m_papplication->øconstruct(pimage);

   pimage->create(size);

   ::double_rectangle rectangleTarget(double_point(0, 0), ::double_size(size));

   ::image::image_source imagesource(this);

   ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pimage->_draw_raw(imagedrawing);

   return pimage;

}



::image32_t * image::line_data(int iLine)
{

   return (::image32_t *) (((unsigned char*)data()) + (iLine * m_iScan));

}


} // namespace image



