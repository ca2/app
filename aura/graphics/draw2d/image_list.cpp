#include "framework.h"


image_list::image_list()
{

   //defer_create_mutex();
   m_iSize = 0;
   m_iGrow = 1;
   m_size.cx = 0;
   m_size.cy = 0;

}


image_list::image_list(const image_list & imagelist)
{

   defer_create_mutex();
   m_iSize = 0;
   m_iGrow = 1;
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

   UNREFERENCED_PARAMETER(nFlags);

   if(cx <= 0)
      return false;

   if(cy <= 0)
      return false;

   if(nInitial < 0)
      return false;

   if(nGrow < 1)
      nGrow = 1;

   defer_create_mutex();

   synchronous_lock synchronouslock(mutex());

   m_iSize = 0;
   m_iGrow = nGrow;

   m_size.cx = cx;
   m_size.cy = cy;

   __defer_compose(m_pimage);

   m_pimage->create(::size_i32(m_size.cx * m_iSize, m_size.cy));

   return true;

}


bool image_list::realize(::draw2d::graphics * pgraphics) const
{

   synchronous_lock synchronouslock(mutex());

   return m_pimage->realize(pgraphics);

}


image_list & image_list::operator=(const image_list & imagelist)
{

   synchronous_lock synchronouslock(mutex());

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


bool image_list::draw(::draw2d::graphics* pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag)
{

   synchronous_lock synchronouslock(mutex());

   try
   {

      UNREFERENCED_PARAMETER(iFlag);

      return pgraphics->draw(
         rectangle_f64(point, m_size ),
         m_pimage, 
         point_f64((double) (iImage * m_size.cx), 0.));

   }
   catch(...)
   {


   }

   return true;

}


bool image_list::draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, i32 iFlag, const ::opacity & opacity)
{

   synchronous_lock synchronouslock(mutex());

   UNREFERENCED_PARAMETER(iFlag);

   if (opacity.is_opaque())
   {

      return draw(pgraphics, iImage, point, iFlag);

   }

   class ::image_drawing imagedrawing;

   imagedrawing.set(::rectangle_i32(point, m_size), m_pimage, ::point_i32(iImage * m_size.cx, 0));

   imagedrawing = ::color_filter(opacity);

   return pgraphics->draw(imagedrawing);

}


bool image_list::color_blend(image_list* pimagelistSource, const ::color::color& color, const ::opacity & opacity)
{

   copy_from(pimagelistSource);

   m_pimage->g()->fill_rectangle(m_pimage->rectangle(), color & opacity);

   return true;

}


bool image_list::draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point_f64 & point, ::size_f64 sz, const ::point_f64 & pointOffsetParam, i32 iFlag)
{

   ::point_f64 pointOffset(pointOffsetParam);

   if(iImage < 0)
   {

      return false;

   }

   synchronous_lock synchronouslock(mutex());

   if(iImage >= get_image_count())
   {

      return false;

   }

   UNREFERENCED_PARAMETER(iFlag);

   sz.cx = minimum(m_size.cx, sz.cx);
   sz.cy = minimum(m_size.cy, sz.cy);
   pointOffset.x = minimum(m_size.cx, pointOffset.x);
   pointOffset.y = minimum(m_size.cy, pointOffset.y);

   return pgraphics->draw(
      rectangle_f64(point, sz ), 
      m_pimage,
      point_f64(iImage * m_size.cx + pointOffset.x, pointOffset.y));

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

   synchronous_lock synchronouslock(mutex());

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


i32 image_list::add(::draw2d::icon * picon, int iItem)
{

   if (is_null(picon))
   {

      return -1;

   }

   synchronous_lock synchronouslock(mutex());

   iItem = reserve_image(iItem);

   auto rectangle = ::rectangle_f64_dimension(iItem * m_size.cx, 0, m_size.cx, m_size.cy);
   
   m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_pimage->g()->fill_rectangle(rectangle, 0);


//#ifdef _UWP
//
//   m_pimage->get_graphics()->draw(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, nullptr, 0);
//
//#else

   auto pointDst = ::point_f64((iItem * m_size.cx), 0.);

   auto sizeDst = m_size;

   auto rectDst = ::rectangle_f64(pointDst, sizeDst);

   m_pimage->get_graphics()->draw(rectDst, picon);

//#endif

   return iItem;

}


i32 image_list::add(::windowing::icon * picon, int iItem)
{

   if (is_null(picon))
   {

      return -1;

   }

   synchronous_lock synchronouslock(mutex());

   iItem = reserve_image(iItem);

   auto rectangle = ::rectangle_f64_dimension(iItem * m_size.cx, 0, m_size.cx, m_size.cy);

   m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_pimage->g()->fill_rectangle(rectangle, 0);

   auto pointDst = ::point_f64((iItem * m_size.cx), 0.);

   auto sizeDst = m_size;

   auto rectDst = ::rectangle_f64(pointDst, sizeDst);

   auto pdraw2dicon = __create < ::draw2d::icon >();

   m_pimage->get_graphics()->draw(rectDst, pdraw2dicon);

   return iItem;

}


i32 image_list::add_icon(::payload varFile, int iItem)
{

   auto picon = __create < ::windowing::icon >();

   if (!picon)
   {

      return -1;

   }

   if (!picon->load_file(varFile))
   {

      return -1;

   }

//#ifdef WINDOWS_DESKTOP
//
//   i32 iSize = minimum(m_size.cx, m_size.cy);
//
//   ::file::path path = varFile.get_file_path();
//
//   path = pcontext->m_papexcontext->defer_process_matter_path(path);
//
//   icon.attach_os_data((hicon) ::LoadImageW(nullptr, wstring(path)
//      , IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE));
//
//#endif
//
   
   auto iIcon = add(picon);
   
   if(iIcon < -1)
   {

      return -1;

   }

   return iIcon;

}


i32 image_list::add_matter_icon(const char * pszMatter, int iItem)
{

   auto pcontext = get_context();

   return add_icon(pcontext->m_papexcontext->dir().matter(pszMatter));

}


i32 image_list::add_file(::payload varFile, int iItem)
{

   synchronous_lock synchronouslock(mutex());

   iItem = reserve_image(iItem);

   fork([this, varFile, iItem]()
      {

         auto pcontext = m_pcontext->m_pauracontext;

         auto pcontextimage = pcontext->context_image();

         auto pimage = pcontextimage->load_image(varFile, true);

         if (!::is_ok(pimage))
         {

            return;

         }

         m_pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_pimage->draw(
            ::rectangle_f64(::point_i32(iItem * m_size.cx, 0),  m_size ),
            pimage);

      });

   return iItem;

}


i32 image_list::add_image(::image * pimage, int x, int y, int iItem)
{

   synchronous_lock synchronouslock(mutex());

   iItem = reserve_image(iItem);

   if (!m_pimage)
   {

      return -1;

   }

   m_pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

   auto rectangle = rectangle_f64_dimension(iItem * m_size.cx, 0, m_size.cx, m_size.cy);

   m_pimage->get_graphics()->fill_rectangle(rectangle, argb(0, 0, 0, 0));

   m_pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

   m_pimage->get_graphics()->draw(
      ::rectangle_f64(::point_f64(iItem * m_size.cx, 0), m_size), pimage, ::point_f64((double) x, (double) y));

   return iItem;

}


//i32 image_list::add_matter(const char * pcsz, ::object * pobject, int iItem)
//{
//
//   ::file::path path;
//
//   if(pobject == nullptr)
//   {
//
//      auto & dir = pcontext->m_papexcontext->dir();
//
//      path = dir.matter(pcsz);
//
//   }
//   else
//   {
//
//      auto & dir = Ctx(pobject).dir();
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
//   synchronous_lock synchronouslock(pil->mutex());
//
//   return add_image(pil->m_pimage, iImage * pil->m_size.cx, 0, iItem);
//
//}


::image_pointer image_list::get_image(int iImage)
{

   ::image_pointer pimage = create_image(m_size);

   if (!pimage)
   {

      return nullptr;

   }

   draw(pimage->get_graphics(), iImage, nullptr, 0);

   return pimage;

}


i32 image_list::add_std_matter(const char * pcsz, int iItem)
{

   auto pcontext = get_context();

   return add_file(pcontext->m_papexcontext->dir().matter(pcsz), iItem);

}


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

   synchronous_lock synchronouslock(mutex());

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

   __compose(m_pimage, plist->m_pimage->clone());
   m_size = plist->m_size;
   m_iSize = plist->m_iSize;
   m_iGrow = plist->m_iGrow;
   m_size = plist->m_size;

}


::e_status image_list::get_image_info(i32 nImage, info * pinfo) const
{

   try
   {

      ASSERT(pinfo != nullptr);

      if(nImage < 0 || nImage >= get_image_count())
      {

         return error_index_out_of_bounds;

      }

      if(::is_null(m_pimage))
      {

         return error_null_pointer;

      }

      if (!m_pimage->is_ok())
      {

         return error_null_pointer;

      }

      pinfo->m_rectangle.left       = nImage * m_size.cx;
      pinfo->m_rectangle.right      = pinfo->m_rectangle.left + m_size.cx;
      pinfo->m_rectangle.top        = 0;
      pinfo->m_rectangle.bottom     = m_size.cy;

      pinfo->m_pimage               = m_pimage;

      //auto estatus = ((image_list*)this)->__construct(pinfo->m_pimage);

      //pinfo->m_pimage->copy_from(m_pimage);

      return ::success;

   }
   catch(...)
   {

   }

   return error_exception;

}


void image_list::erase_all()
{
   m_iSize = 0;
}
