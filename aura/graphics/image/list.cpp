#include "framework.h"
#include "list.h"
#include "context.h"
#include "image.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/graphics/image/drawing.h"

/*


::image::image_source imagesource();

::image::image_drawing_options imagedrawingoptions();

::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);


*/
namespace image
{


   image_list::image_list()
   {

      //defer_create_synchronization();
      m_iSize = 0;
      m_iGrow = 16;
      m_size.cx() = 0;
      m_size.cy() = 0;

   }


   image_list::image_list(const image_list & imagelist)
   {

      defer_create_synchronization();
      m_iSize = 0;
      m_iGrow = imagelist.m_iGrow;
      m_size.cx() = 0;
      m_size.cy() = 0;

      operator = (imagelist);

   }


   image_list::~image_list()
   {

   }


   bool image_list::create(int cx, int cy)
   {

      return create(cx, cy, 0, 0, 0);

   }


   bool image_list::create(int cx, int cy, unsigned int nFlags, int nInitial, int nGrow)
   {

      __UNREFERENCED_PARAMETER(nFlags);

      if (cx <= 0)
         return false;

      if (cy <= 0)
         return false;

      if (nInitial < 0)
         return false;

      if (nGrow < 1)
         nGrow = 1;

      defer_create_synchronization();

      _synchronous_lock synchronouslock(this->synchronization());

      m_iSize = 0;
      m_iGrow = nGrow;

      m_size.cx() = cx;
      m_size.cy() = cy;

      system()->draw2d();

      __defer_construct(m_pimage);

      if (m_iSize > 0)
      {

         m_pimage->create(::int_size(m_size.cx() * m_iSize, m_size.cy()));

      }

      return true;

   }


   void image_list::realize(::draw2d::graphics * pgraphics) const
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_pimage->realize(pgraphics);

   }


   image_list & image_list::operator=(const image_list & imagelist)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (this != &imagelist)
      {

         copy_from(&imagelist);

      }

      return *this;

   }


   int image_list::get_image_count() const
   {

      return m_iSize;

   }


   void image_list::draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, int iFlag)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      __UNREFERENCED_PARAMETER(iFlag);

      double_point pointSource((double)(iImage * m_size.cx()), 0.);

      double_rectangle rectangleSource(pointSource, m_size);

      ::image::image_source imagesource(m_pimage, rectangleSource);

      double_rectangle rectangleTarget(point, m_size);

      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pgraphics->draw(imagedrawing);

   }


   void image_list::draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, int iFlag, const class ::opacity & opacity)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pimage->nok())
      {

         return;

      }

      __UNREFERENCED_PARAMETER(iFlag);

      if (opacity.is_opaque())
      {

         return draw(pgraphics, iImage, point, iFlag);

      }

      double_point pointSource((double)(iImage * m_size.cx()), 0.);

      double_rectangle rectangleSource(pointSource, m_size);

      ::image::image_source imagesource(m_pimage, rectangleSource);

      double_rectangle rectangleTarget(point, m_size);

      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      imagedrawing.opacity(opacity);

      pgraphics->draw(imagedrawing);

   }


   void image_list::color_blend(image_list * pimagelistSource, const ::color::color & color, const class ::opacity & opacity)
   {

      copy_from(pimagelistSource);

      if (m_pimage.ok())
      {

         m_pimage->g()->fill_rectangle(m_pimage->rectangle(), color & opacity);

      }

   }


   void image_list::draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, ::double_size sz, const ::double_point & pointOffsetParam, int iFlag)
   {

      if (iImage < 0)
      {

         return;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      if (iImage >= get_image_count())
      {

         return;

      }

      _draw(pgraphics, iImage, point, sz, pointOffsetParam, iFlag);

   }


   void image_list::_draw(::draw2d::graphics * pgraphics, int iImage, const ::double_point & point, ::double_size sz, const ::double_point & pointOffsetParam, int iFlag)
   {

      ::double_point pointOffset(pointOffsetParam);

      __UNREFERENCED_PARAMETER(iFlag);

      pointOffset.x() = minimum(m_size.cx(), pointOffset.x());
      pointOffset.y() = minimum(m_size.cy(), pointOffset.y());
      sz.cx() = maximum(0, minimum(m_size.cx() - pointOffset.x(), sz.cx()));
      sz.cy() = maximum(0, minimum(m_size.cy() - pointOffset.y(), sz.cy()));

      double_point pointSource((double)(iImage * m_size.cx()), 0.);

      double_rectangle rectangleSource(pointSource, sz);

      ::image::image_source imagesource(m_pimage, rectangleSource);

      double_rectangle rectangleTarget(point, sz);

      ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pgraphics->draw(imagedrawing);

   }


   //int image_list::add_icon_os_data(void * p, int iItem)
   //{
   //
   //   ::image::icon icon;
   //
   //   icon.initialize(this);
   //
   //   icon.attach_os_data(p, false);
   //
   //   return add(&icon, iItem);
   //
   //}


   int image_list::reserve_image(int iItem)
   {

      ::draw2d::lock draw2dlock(this);

      _synchronous_lock synchronouslock(this->synchronization());

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


   //int image_list::set(int iItem, ::image::icon * picon)
   //{
   //
   //   if (is_null(picon))
   //   {
   //
   //      return -1;
   //
   //   }
   //
   //   _synchronous_lock synchronouslock(this->synchronization());
   //
   //   iItem = reserve_image(iItem);
   //
   //   auto rectangle = ::double_rectangle_dimension(iItem * m_size.cx(), 0, m_size.cx(), m_size.cy());
   //   
   //   m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //
   //   m_pimage->g()->fill_rectangle(rectangle, 0);
   //
   //
   ////#ifdef UNIVERSAL_WINDOWS
   ////
   ////   m_pimage->get_graphics()->draw(iItem * m_size.cx(), 0, picon, m_size.cx(), m_size.cy(), 0, nullptr, 0);
   ////
   ////#else
   //
   //   auto pointDst = ::double_point((iItem * m_size.cx()), 0.);
   //
   //   auto sizeDst = m_size;
   //
   //   auto rectangleTarget = ::double_rectangle(pointDst, sizeDst);
   //
   //   m_pimage->get_graphics()->draw(rectangleTarget, picon);
   //
   ////#endif
   //
   //   return iItem;
   //
   //}

   //
   //int image_list::set(int iItem, ::windowing::icon * picon)
   //{
   //
   //   if (is_null(picon))
   //   {
   //
   //      return -1;
   //
   //   }
   //
   //   _synchronous_lock synchronouslock(this->synchronization());
   //
   //   iItem = reserve_image(iItem);
   //
   //   auto rectangle = ::double_rectangle_dimension(iItem * m_size.cx(), 0, m_size.cx(), m_size.cy());
   //
   //   m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //
   //   m_pimage->g()->fill_rectangle(rectangle, 0);
   //
   //   auto pointDst = ::double_point((iItem * m_size.cx()), 0.);
   //
   //   auto sizeDst = m_size;
   //
   //   auto rectangleTarget = ::double_rectangle(pointDst, sizeDst);
   //
   //   auto pdraw2dicon = __øcreate < ::image::icon >();
   //
   //   pdraw2dicon->initialize_with_windowing_icon(picon);
   //
   //   m_pimage->get_graphics()->draw(rectangleTarget, pdraw2dicon);
   //
   //   return iItem;
   //
   //}


   //int image_list::add_icon(::payload payloadFile, int iItem)
   //{
   //
   //   auto picon = __øcreate < ::windowing::icon >();
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
   ////   int iSize = minimum(m_size.cx(), m_size.cy());
   ////
   ////   ::file::path path = payloadFile.get_file_path();
   ////
   ////   path = m_papplication->defer_process_matter_path(path);
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

   //int image_list::add_matter_icon(const ::scoped_string & scopedstrMatter, int iItem)
   //{
   //
   //   // auto pcontext = get_context();
   //
   //   return add_icon(directory()->matter(scopedstrMatter));
   //
   //}
   //

   //int image_list::add_file(::payload payloadFile, int iItem)
   //{
   //
   //   _synchronous_lock synchronouslock(this->synchronization());
   //
   //   iItem = reserve_image(iItem);
   //
   //   fork([this, payloadFile, iItem]()
   //      {
   //
   //         auto papplication = m_papplication;
   //
   //         auto pimagecontext = pcontext->image_context();
   //
   //         auto pimage = image()->load_image(payloadFile, true);
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
   //            ::double_rectangle(::int_point(iItem * m_size.cx(), 0),  m_size ),
   //            pimage);
   //
   //      });
   //
   //   return iItem;
   //
   //}


   int image_list::set(int iItem, const ::image::image_drawing & imagedrawing)
   {

      ::draw2d::lock draw2dlock(this);

      _synchronous_lock synchronouslock(this->synchronization());

      iItem = reserve_image(iItem);

      if (!::is_ok(m_pimage))
      {

         return -1;

      }

      try
      {

         m_pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         ::image::image_drawing imagedrawingTarget(imagedrawing);

         imagedrawingTarget.m_rectangleTarget.set(::double_point(iItem * m_size.cx(), 0), m_size);

         m_pimage->get_graphics()->draw(imagedrawingTarget);

      }
      catch (...)
      {

      }

      return iItem;

   }


   //int image_list::set_file(int iItem, ::file::file * pfile)
   //{
   //
   //   auto pimagecontext = pobjectContext->image();
   //
   //   auto pimage = image()->get_image(pfile);
   //
   //   if(pimage.nok())
   //   {
   //
   //      return -1;
   //
   //   }
   //
   //   ::image::image_source imagesource(pimage);
   //
   //   double_rectangle rectangle(m_size);
   //
   //   ::image::image_drawing_options imagedrawingoptions(rectangle);
   //
   //   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   //   int iImage = this->set(iItem, imagedrawing);
   //
   //   return iImage;
   //
   //}
   //
   //
   //int image_list::set_icon(int iItem, ::object * pobjectContext, const ::payload & payload)
   //{
   //
   //   auto pimagecontext = pobjectContext->image();
   //
   //   auto pimage = image()->get_image(payload);
   //
   //   ::image::image_source imagesource(pimage);
   //
   //   double_rectangle rectangle(m_size);
   //
   //   ::image::image_drawing_options imagedrawingoptions(rectangle);
   //
   //   ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   //   int iImage = this->set(iItem, imagedrawing);
   //
   //   return iImage;
   //
   //}


   //int image_list::add_matter(const ::string & pcsz, ::particle * pparticle, int iItem)
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

   //int image_list::add_image(image_list * pil, int iImage, int iItem)
   //{
   //
   //   _synchronous_lock synchronouslock(pil->synchronization());
   //
   //   return add_image(pil->m_pimage, iImage * pil->m_size.cx(), 0, iItem);
   //
   //}


   ::image::image_pointer image_list::get_image(int iImage)
   {

      ::image::image_pointer pimage = image()->create_image(m_size);

      if (!pimage)
      {

         return nullptr;

      }

      draw(pimage->get_graphics(), iImage, {}, 0);

      return pimage;

   }


   //int image_list::add_std_matter(const ::string & pcsz, int iItem)
   //{
   //
   //   // auto pcontext = get_context();
   //
   //   return add_file(directory()->matter(pcsz), iItem);
   //
   //}


   int image_list::_get_alloc_count()
   {

      if (m_size.cx() <= 0)
      {

         return 0;

      }

      return m_pimage->width() / m_size.cx();

   }


   bool image_list::_grow(int iAddUpHint)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      int cx = m_size.cx();

      int cy = m_size.cy();

      int iGrow = m_iGrow;

      if (iAddUpHint > 0)
      {

         iGrow += iAddUpHint;

      }

      int iAllocSize = _get_alloc_count() + iGrow;

      m_pimage->preserve(::int_size(cx * iAllocSize, cy));

      return true;

   }


   void image_list::copy_from(const ::image::image_list * plist)
   {

      m_pimage = plist->m_pimage->clone();
      m_size = plist->m_size;
      m_iSize = plist->m_iSize;
      m_iGrow = plist->m_iGrow;
      m_size = plist->m_size;

   }


   void image_list::get_image_info(int nImage, info * pinfo) const
   {

      ASSERT(pinfo != nullptr);

      if (nImage < 0 || nImage >= get_image_count())
      {

         throw ::exception(error_index_out_of_bounds);

      }

      if (::is_null(m_pimage))
      {

         throw ::exception(error_null_pointer);

      }

      if (m_pimage.nok())
      {

         throw ::exception(error_null_pointer);

      }

      pinfo->m_rectangle.left() = nImage * m_size.cx();
      pinfo->m_rectangle.right() = pinfo->m_rectangle.left() + m_size.cx();
      pinfo->m_rectangle.top() = 0;
      pinfo->m_rectangle.bottom() = m_size.cy();

      pinfo->m_pimage = m_pimage;

      //auto estatus = ((image_list*)this)->__øconstruct(pinfo->m_pimage);

      //pinfo->m_pimage->copy_from(m_pimage);

      //return ::success;

   }


   void image_list::erase_all()
   {

      m_iSize = 0;

   }


} // namespace image




