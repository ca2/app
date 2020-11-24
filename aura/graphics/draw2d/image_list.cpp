#include "framework.h"

#ifndef _UWP
//#include "freeimage/Source/FreeImage.h"
#endif


image_list::image_list()
{

   //defer_create_mutex();
   m_iSize = 0;
   m_iGrow = 1;
   m_size.cx = 0;
   m_size.cy = 0;

}


image_list::image_list(const image_list & imagelist):
   ::object(imagelist.get_context_object())
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

   sync_lock sl(mutex());

   m_iSize = 0;
   m_iGrow = nGrow;

   m_size.cx = cx;
   m_size.cy = cy;

   __defer_compose(m_pimage);

   m_pimage->create(::size(m_size.cx * m_iSize, m_size.cy));

   return true;

}


bool image_list::realize(::draw2d::graphics * pgraphics) const
{

   sync_lock sl(mutex());

   return m_pimage->realize(pgraphics);

}


image_list & image_list::operator=(const image_list & imagelist)
{

   sync_lock sl(mutex());

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


bool image_list::draw(::draw2d::graphics* pgraphics, i32 iImage, const ::point & point, i32 iFlag)
{

   sync_lock sl(mutex());

   try
   {

      UNREFERENCED_PARAMETER(iFlag);

      return pgraphics->draw(
         { point, m_size },
         m_pimage->get_graphics(), 
         {iImage * m_size.cx, 0});

   }
   catch(...)
   {


   }

   return true;

}


bool image_list::draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point & point, i32 iFlag, byte alpha)
{

   sync_lock sl(mutex());

   UNREFERENCED_PARAMETER(iFlag);

   if(alpha == 255)
      return draw(pgraphics, iImage, point, iFlag);

   return System.imaging().color_blend(pgraphics, point, m_size, m_pimage->g(), ::point(iImage * m_size.cx, 0), alpha / 255.0);

}


bool image_list::draw(::draw2d::graphics * pgraphics, i32 iImage, const ::point & point, size sz, const ::point & pointOffsetParam, i32 iFlag)
{

   ::point pointOffset(pointOffsetParam);

   //ASSERT(iImage >= 0 && iImage < get_image_count());

   if(iImage < 0)
   {

      return false;

   }

   sync_lock sl(mutex());

   if(iImage >= get_image_count())
   {

      return false;

   }

   UNREFERENCED_PARAMETER(iFlag);

   sz.cx = min(m_size.cx, sz.cx);
   sz.cy = min(m_size.cy, sz.cy);
   pointOffset.x = min(m_size.cx, pointOffset.x);
   pointOffset.y = min(m_size.cy, pointOffset.y);

   return pgraphics->draw({ point, sz }, m_pimage, {iImage * m_size.cx + pointOffset.x, pointOffset.y});

}


i32 image_list::add_icon_os_data(void * p, int iItem)
{

   ::draw2d::icon icon;

   icon.initialize(this);

   icon.attach_os_data(p, false);

   return add(&icon, iItem);

}


i32 image_list::reserve_image(int iItem)
{

   sync_lock sl(mutex());

   if (iItem < 0)
   {

      iItem = get_image_count();

   }

   if (iItem >= _get_alloc_count())
   {

      _grow(iItem + 1);

   }

   m_iSize = max(iItem + 1, m_iSize);

   return iItem;


}


i32 image_list::add(::draw2d::icon * picon, int iItem)
{

   if (is_null(picon))
   {

      return -1;

   }

   sync_lock sl(mutex());

   iItem = reserve_image(iItem);

   m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_pimage->g()->fill_solid_rect_dim(iItem * m_size.cx, 0, m_size.cx, m_size.cy, 0);

#ifdef _UWP

   m_pimage->get_graphics()->DrawIcon(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, nullptr, 0);

#else

   m_pimage->get_graphics()->draw({ iItem * m_size.cx , 0 }, picon, m_size);

#endif

   return iItem;

}


i32 image_list::add_icon(payload varFile, int iItem)
{

   ::draw2d::icon icon;

   icon.initialize(this);

#ifdef WINDOWS_DESKTOP

   i32 iSize = min(m_size.cx, m_size.cy);

   ::file::path path = varFile.get_file_path();

   path = Context.defer_process_matter_path(path);

   icon.attach_os_data((HICON) ::LoadImageW(nullptr, wstring(path)
      , IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE));

#endif

   return add(&icon);

}


i32 image_list::add_matter_icon(const char * pszMatter, int iItem)
{

   return add_icon(Context.dir().matter(pszMatter));

}


i32 image_list::add_file(payload varFile, int iItem)
{

   sync_lock sl(mutex());

   iItem = reserve_image(iItem);

   fork([this, varFile, iItem]()
      {

         auto pimage = Application.image().load_image(varFile, true);

         if (!pimage)
         {

            return;

         }

         m_pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_pimage->get_graphics()->draw(
            { ::point(iItem * m_size.cx, 0),  m_size },
            pimage->get_graphics());

      });

   return iItem;

}


i32 image_list::add_image(::image * pimage, int x, int y, int iItem)
{

   sync_lock sl(mutex());

   iItem = reserve_image(iItem);

   if (!m_pimage)
   {

      return -1;

   }

   m_pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_pimage->get_graphics()->fill_solid_rect_dim(iItem * m_size.cx, 0, m_size.cx, m_size.cy, ARGB(0, 0, 0, 0));

   m_pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

   m_pimage->get_graphics()->draw(
      {::point(iItem * m_size.cx, 0), m_size}, pimage, {x, y});

   return iItem;

}


//i32 image_list::add_matter(const char * pcsz, ::layered * pobjectContext, int iItem)
//{
//
//   ::file::path path;
//
//   if(pobjectContext == nullptr)
//   {
//
//      auto & dir = Context.dir();
//
//      path = dir.matter(pcsz);
//
//   }
//   else
//   {
//
//      auto & dir = Ctx(pobjectContext).dir();
//
//      path = dir.matter(pcsz);
//
//   }
//
//   return add_file(path, iItem);
//
//}

i32 image_list::add_image(image_list * pil, int iImage, int iItem)
{

   sync_lock sl(pil->mutex());

   return add_image(pil->m_pimage, iImage * pil->m_size.cx, 0, iItem);

}


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

   return add_file(Context.dir().matter(pcsz), iItem);


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

   sync_lock sl(mutex());

   i32 cx = m_size.cx;

   i32 cy = m_size.cy;

   int iGrow = m_iGrow;

   if (iAddUpHint > 0)
   {

      iGrow += iAddUpHint;

   }

   i32 iAllocSize = _get_alloc_count() + iGrow;

   m_pimage->preserve(::size(cx * iAllocSize, cy));

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


bool image_list::get_image_info(i32 nImage, info * pinfo) const
{

   try
   {

      ASSERT(pinfo != nullptr);

      bool bOk = true;

      if(nImage < 0 || nImage >= get_image_count())
      {

         bOk = false;

         nImage = 0;

      }

      if(bOk && m_pimage->is_null())
      {

         bOk = false;

      }

      if(bOk && m_pimage->get_bitmap().is_null())
      {

         bOk = false;

      }

      pinfo->m_rect.left      = nImage * m_size.cx;
      pinfo->m_rect.right     = pinfo->m_rect.left + m_size.cx;
      pinfo->m_rect.top       = 0;
      pinfo->m_rect.bottom    = m_size.cy;

      ((image_list*)this)->__construct(pinfo->m_pimage);

      pinfo->m_pimage->copy_from(m_pimage);

      return bOk;

   }
   catch(...)
   {

   }

   return false;

}


void image_list::remove_all()
{
   m_iSize = 0;
}
