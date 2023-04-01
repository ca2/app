#include "framework.h"
#include "list.h"
#include "image.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/graphics/image/drawing.h"
#include "context_image.h"

/*


::image_source imagesource();

::image_drawing_options imagedrawingoptions();

::image_drawing imagedrawing(imagedrawingoptions, imagesource);


*/


image_list::image_list()
{

   //defer_create_synchronization();
   m_iSize = 0;
   m_iGrow = 16;
   m_size.cx = 0;
   m_size.cy = 0;

}


image_list::image_list(const image_list & imagelist)
{

   defer_create_synchronization();
   m_iSize = 0;
   m_iGrow = imagelist.m_iGrow;
   m_size.cx = 0;
   m_size.cy = 0;

   operator = (imagelist);

}


image_list::~image_list()
{

}


bool image_list::create(i32 cx, i32 cy)
{

   return create(cx, cy, 0, 0, 0);

}


bool image_list::create(i32 cx, i32 cy, ::u32 nFlags, i32 nInitial, i32 nGrow)
{

   __UNREFERENCED_PARAMETER(nFlags);

   if(cx <= 0)
      return false;

   if(cy <= 0)
      return false;

   if(nInitial < 0)
      return false;

   if(nGrow < 1)
      nGrow = 1;

   defer_create_synchronization();

   synchronous_lock synchronouslock(this->synchronization());

   m_iSize = 0;
   m_iGrow = nGrow;

   m_size.cx = cx;
   m_size.cy = cy;

   __defer_construct(m_pimage);

   if (m_iSize > 0)
   {

      m_pimage->create(::size_i32(m_size.cx * m_iSize, m_size.cy));

   }

   return true;

}


void image_list::realize(::draw2d::graphics * pgraphics) const
{

   synchronous_lock synchronouslock(this->synchronization());

   m_pimage->realize(pgraphics);

}


image_list & image_list::operator=(const image_list & imagelist)
{

   synchronous_lock synchronouslock(this->synchronization());

   if(this != &imagelist)
   {

      copy_from(&imagelist);

   }

   return *this;

}


i32 image_list::get_image_count() const
{

   return m_iSize;

}


void image_list::draw(::draw2d::graphics* pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag)
{

   synchronous_lock synchronouslock(this->synchronization());

   __UNREFERENCED_PARAMETER(iFlag);

   point_f64 pointSource((double)(iImage * m_size.cx), 0.);

   rectangle_f64 rectangleSource(pointSource, m_size);

   image_source imagesource(m_pimage, rectangleSource);

   rectangle_f64 rectangleTarget(point, m_size);

   image_drawing_options imagedrawingoptions(rectangleTarget);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pgraphics->draw(imagedrawing);

}


void image_list::draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag, const ::opacity & opacity)
{

   synchronous_lock synchronouslock(this->synchronization());

   if (m_pimage->is_ok())
   {

      return;

   }

   __UNREFERENCED_PARAMETER(iFlag);

   if (opacity.is_opaque())
   {

      return draw(pgraphics, iImage, point, iFlag);

   }

   point_f64 pointSource((double)(iImage * m_size.cx), 0.);

   rectangle_f64 rectangleSource(pointSource, m_size);

   image_source imagesource(m_pimage, rectangleSource);

   rectangle_f64 rectangleTarget(point, m_size);

   image_drawing_options imagedrawingoptions(rectangleTarget);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   imagedrawing.opacity(opacity);

   pgraphics->draw(imagedrawing);

}


void image_list::color_blend(image_list* pimagelistSource, const ::color::color& color, const ::opacity & opacity)
{

   copy_from(pimagelistSource);

   if (m_pimage.ok())
   {

      m_pimage->g()->fill_rectangle(m_pimage->rectangle(), color & opacity);

   }

}


void image_list::draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, ::size_f64 sz, const ::point_f64 & pointOffsetParam, i32 iFlag)
{

   if (iImage < 0)
   {

      return;

   }

   synchronous_lock synchronouslock(this->synchronization());

   if (iImage >= get_image_count())
   {

      return;

   }

   _draw(pgraphics, iImage, point, sz, pointOffsetParam, iFlag);

}


void image_list::_draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, ::size_f64 sz, const ::point_f64 & pointOffsetParam, i32 iFlag)
{

   ::point_f64 pointOffset(pointOffsetParam);

   __UNREFERENCED_PARAMETER(iFlag);

   pointOffset.x = minimum(m_size.cx, pointOffset.x);
   pointOffset.y = minimum(m_size.cy, pointOffset.y);
   sz.cx = maximum(0, minimum(m_size.cx-pointOffset.x, sz.cx));
   sz.cy = maximum(0, minimum(m_size.cy-pointOffset.y, sz.cy));

   point_f64 pointSource((double)(iImage * m_size.cx), 0.);

   rectangle_f64 rectangleSource(pointSource, sz);

   image_source imagesource(m_pimage, rectangleSource);

   rectangle_f64 rectangleTarget(point, sz);

   image_drawing_options imagedrawingoptions(rectangleTarget);

   image_drawing imagedrawing(imagedrawingoptions, imagesource);

   pgraphics->draw(imagedrawing);

}


//i32 image_list::add_icon_os_data(void * p, int iItem)
//{
//
//   ::draw2d::icon icon;
//
//   icon.initialize(this);
//
//   icon.attach_os_data(p, false);
//
//   return add(&icon, iItem);
//
//}


i32 image_list::reserve_image(int iItem)
{

   ::draw2d::lock draw2dlock(this);

   synchronous_lock synchronouslock(this->synchronization());

   if (iItem < 0)
   {

      iItem = get_image_count();

   }

   if (iItem >= _get_alloc_count())
   {

      _grow(iItem + 1);

   }

   m_iSize = maximum(iItem + 1, m_iSize);

   return iItem;


}


//i32 image_list::set(int iItem, ::draw2d::icon * picon)
//{
//
//   if (is_null(picon))
//   {
//
//      return -1;
//
//   }
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   iItem = reserve_image(iItem);
//
//   auto rectangle = ::rectangle_f64_dimension(iItem * m_size.cx, 0, m_size.cx, m_size.cy);
//   
//   m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//   m_pimage->g()->fill_rectangle(rectangle, 0);
//
//
////#ifdef UNIVERSAL_WINDOWS
////
////   m_pimage->get_graphics()->draw(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, nullptr, 0);
////
////#else
//
//   auto pointDst = ::point_f64((iItem * m_size.cx), 0.);
//
//   auto sizeDst = m_size;
//
//   auto rectangleTarget = ::rectangle_f64(pointDst, sizeDst);
//
//   m_pimage->get_graphics()->draw(rectangleTarget, picon);
//
////#endif
//
//   return iItem;
//
//}

//
//i32 image_list::set(int iItem, ::windowing::icon * picon)
//{
//
//   if (is_null(picon))
//   {
//
//      return -1;
//
//   }
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   iItem = reserve_image(iItem);
//
//   auto rectangle = ::rectangle_f64_dimension(iItem * m_size.cx, 0, m_size.cx, m_size.cy);
//
//   m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//   m_pimage->g()->fill_rectangle(rectangle, 0);
//
//   auto pointDst = ::point_f64((iItem * m_size.cx), 0.);
//
//   auto sizeDst = m_size;
//
//   auto rectangleTarget = ::rectangle_f64(pointDst, sizeDst);
//
//   auto pdraw2dicon = __create < ::draw2d::icon >();
//
//   pdraw2dicon->initialize_with_windowing_icon(picon);
//
//   m_pimage->get_graphics()->draw(rectangleTarget, pdraw2dicon);
//
//   return iItem;
//
//}


//i32 image_list::add_icon(::payload payloadFile, int iItem)
//{
//
//   auto picon = __create < ::windowing::icon >();
//
//   if (!picon)
//   {
//
//      return -1;
//
//   }
//
//   if (!picon->load_file(payloadFile))
//   {
//
//      return -1;
//
//   }
//
////#ifdef WINDOWS_DESKTOP
////
////   i32 iSize = minimum(m_size.cx, m_size.cy);
////
////   ::file::path path = payloadFile.get_file_path();
////
////   path = pcontext->m_papexcontext->defer_process_matter_path(path);
////
////   icon.attach_os_data((hicon) ::LoadImageW(nullptr, wstring(path)
////      , IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE));
////
////#endif
////
//   
//   auto iIcon = add(picon);
//   
//   if(iIcon < -1)
//   {
//
//      return -1;
//
//   }
//
//   return iIcon;
//
//}
//

//i32 image_list::add_matter_icon(const ::string & pszMatter, int iItem)
//{
//
//   auto pcontext = get_context();
//
//   return add_icon(dir()->matter(pszMatter));
//
//}
//

//i32 image_list::add_file(::payload payloadFile, int iItem)
//{
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   iItem = reserve_image(iItem);
//
//   fork([this, payloadFile, iItem]()
//      {
//
//         auto pcontext = m_pcontext->m_pauracontext;
//
//         auto pcontextimage = pcontext->context_image();
//
//         auto pimage = pcontextimage->load_image(payloadFile, true);
//
//         if (pimage.nok())
//         {
//
//            return;
//
//         }
//
//         m_pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//
//         m_pimage->draw(
//            ::rectangle_f64(::point_i32(iItem * m_size.cx, 0),  m_size ),
//            pimage);
//
//      });
//
//   return iItem;
//
//}


i32 image_list::set(int iItem, const image_drawing & imagedrawing)
{

   ::draw2d::lock draw2dlock(this);

   synchronous_lock synchronouslock(this->synchronization());

   iItem = reserve_image(iItem);

   if (!m_pimage)
   {

      return -1;

   }

   m_pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   ::image_drawing imagedrawingTarget(imagedrawing);

   imagedrawingTarget.m_rectangleTarget.set(::point_f64(iItem * m_size.cx, 0), m_size);

   m_pimage->get_graphics()->draw(imagedrawingTarget);

   return iItem;

}


//i32 image_list::set_file(int iItem, ::file::file * pfile)
//{
//
//   auto pcontextimage = pobjectContext->m_pcontext->context_image();
//
//   auto pimage = pcontextimage->get_image(pfile);
//
//   if(pimage.nok())
//   {
//
//      return -1;
//
//   }
//
//   image_source imagesource(pimage);
//
//   rectangle_f64 rectangle(m_size);
//
//   image_drawing_options imagedrawingoptions(rectangle);
//
//   image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//   i32 iImage = this->set(iItem, imagedrawing);
//
//   return iImage;
//
//}
//
//
//i32 image_list::set_icon(int iItem, ::object * pobjectContext, const ::payload & payload)
//{
//
//   auto pcontextimage = pobjectContext->m_pcontext->context_image();
//
//   auto pimage = pcontextimage->get_image(payload);
//
//   image_source imagesource(pimage);
//
//   rectangle_f64 rectangle(m_size);
//
//   image_drawing_options imagedrawingoptions(rectangle);
//
//   image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//   i32 iImage = this->set(iItem, imagedrawing);
//
//   return iImage;
//
//}


//i32 image_list::add_matter(const ::string & pcsz, ::particle * pparticle, int iItem)
//{
//
//   ::file::path path;
//
//   if(pparticle == nullptr)
//   {
//
//      auto & dir = dir();
//
//      path = dir.matter(pcsz);
//
//   }
//   else
//   {
//
//      auto & dir = Ctx(pparticle).dir();
//
//      path = dir.matter(pcsz);
//
//   }
//
//   return add_file(path, iItem);
//
//}

//i32 image_list::add_image(image_list * pil, int iImage, int iItem)
//{
//
//   synchronous_lock synchronouslock(pil->synchronization());
//
//   return add_image(pil->m_pimage, iImage * pil->m_size.cx, 0, iItem);
//
//}


::image_pointer image_list::get_image(int iImage)
{

   ::image_pointer pimage = m_pcontext->m_pauracontext->create_image(m_size);

   if (!pimage)
   {

      return nullptr;

   }

   draw(pimage->get_graphics(), iImage, nullptr, 0);

   return pimage;

}


//i32 image_list::add_std_matter(const ::string & pcsz, int iItem)
//{
//
//   auto pcontext = get_context();
//
//   return add_file(dir()->matter(pcsz), iItem);
//
//}


i32 image_list::_get_alloc_count()
{

   if(m_size.cx <= 0)
   {

      return 0;

   }

   return m_pimage->width() / m_size.cx;

}


bool image_list::_grow(int iAddUpHint)
{

   synchronous_lock synchronouslock(this->synchronization());

   i32 cx = m_size.cx;

   i32 cy = m_size.cy;

   int iGrow = m_iGrow;

   if (iAddUpHint > 0)
   {

      iGrow += iAddUpHint;

   }

   i32 iAllocSize = _get_alloc_count() + iGrow;

   m_pimage->preserve(::size_i32(cx * iAllocSize, cy));

   return true;

}


void image_list::copy_from(const ::image_list * plist)
{

   __construct(m_pimage, ::pointer_transfer(plist->m_pimage->clone()));
   m_size = plist->m_size;
   m_iSize = plist->m_iSize;
   m_iGrow = plist->m_iGrow;
   m_size = plist->m_size;

}


void image_list::get_image_info(i32 nImage, info * pinfo) const
{

   ASSERT(pinfo != nullptr);

   if(nImage < 0 || nImage >= get_image_count())
   {

      throw ::exception(error_index_out_of_bounds);

   }

   if(::is_null(m_pimage))
   {

      throw ::exception(error_null_pointer);

   }

   if (m_pimage.nok())
   {

      throw ::exception(error_null_pointer);

   }

   pinfo->m_rectangle.left       = nImage * m_size.cx;
   pinfo->m_rectangle.right      = pinfo->m_rectangle.left + m_size.cx;
   pinfo->m_rectangle.top        = 0;
   pinfo->m_rectangle.bottom     = m_size.cy;

   pinfo->m_pimage               = m_pimage;

   //auto estatus = ((image_list*)this)->__construct(pinfo->m_pimage);

   //pinfo->m_pimage->copy_from(m_pimage);

   //return ::success;

}


void image_list::erase_all()
{

   m_iSize = 0;

}



